#!/usr/bin/env python3
"""Generate the pybind11 bindings of the ATM C++ library.

The public API of every class, enumeration and free function declared in
``cpp/ATM/include/*.h`` is extracted with libclang and turned into pybind11
code (``src/bindings/atm_generated.cpp``).  Re-run this script after
``tools/sync_from_telcal.sh`` to keep the bindings in sync with ATM.

    python tools/generate_bindings.py            # write src/bindings/atm_generated.cpp
    python tools/generate_bindings.py --report   # also list skipped methods

Requirements (development only): ``pip install libclang``.

Mapping rules
-------------
* constructors          -> ``py::init<...>()`` (copy constructors -> ``__copy__``/``__deepcopy__``)
* methods / statics     -> ``.def`` / ``.def_static`` with an explicit member pointer cast
                           (so that every C++ overload becomes a Python overload)
* default arguments     -> ``py::arg("name") = <C++ default expression>``
* arithmetic/comparison operators of the unit classes -> Python dunder methods
* nested/namespace enums -> ``py::enum_`` (values also exported to the enclosing scope)
* single ``double`` argument constructors of the unit classes -> implicit conversion
  from Python ``float``/``int`` (mirrors the implicit C++ conversion)
* ``double *`` arrays     -> any Python sequence / numpy array of floats
* non-const ``C &``      -> the Python object is modified in place
* non-const ``std::vector<C> &`` -> Python list whose elements are updated in place
* other raw pointer / non-const reference parameters are skipped (``--report``);
  ``AtmException`` is registered as a Python exception in ``src/bindings/atm_module.cpp``.
"""
from __future__ import annotations

import argparse
import re
import subprocess
import sys
from dataclasses import dataclass, field
from pathlib import Path

import clang.cindex as ci

ROOT = Path(__file__).resolve().parents[1]
INCLUDE_DIR = ROOT / "cpp" / "ATM" / "include"
OUTPUT = ROOT / "src" / "bindings" / "atm_generated.cpp"

# Headers that are not part of the API (documentation only)
EXCLUDED_HEADERS = {"mainpage.h"}
NAMESPACE = "atm"
# C arrays passed as 'double *' are exposed as sequences (list / numpy array) of floats
ARRAY_PTR = "double *"
# Non-const references to ATM objects are modified in place (pybind11 passes bound objects by reference)
CLASS_REF = re.compile(r"^([A-Z]\w*) &$")
# Non-const std::vector<ATM class> & are exposed as Python lists whose elements are updated in place
VECTOR_REF = re.compile(r"^std::vector<([A-Z]\w*)> &$")
# Classes bound by hand in src/bindings/atm_module.cpp (AtmException -> Python exception)
EXCLUDED_CLASSES = {"AtmException"}
# Methods declared in the headers but not implemented in ATM (class, name, number of parameters).
# Found with: nm -C -D -u _atm*.so | grep atm::  vs  nm -C -D --defined-only lib/libATM.so
NOT_IMPLEMENTED = {
    ("Length", "get", 2),
    ("RefractiveIndex", "getRefractivity_hh18o", 6),
    ("RefractiveIndex", "getSpecificRefractivity_o2", 4),
}

OPERATORS = {
    "operator+": ("__add__", "+"),
    "operator-": ("__sub__", "-"),
    "operator*": ("__mul__", "*"),
    "operator/": ("__truediv__", "/"),
    "operator<": ("__lt__", "<"),
    "operator>": ("__gt__", ">"),
    "operator<=": ("__le__", "<="),
    "operator>=": ("__ge__", ">="),
    "operator==": ("__eq__", "=="),
    "operator!=": ("__ne__", "!="),
}


# --------------------------------------------------------------------------- model
@dataclass
class Param:
    type: str
    name: str
    default: str | None


@dataclass
class Method:
    kind: str  # "ctor", "method", "static", "operator"
    name: str
    result: str
    params: list[Param]
    const: bool
    doc: str
    skip_reason: str | None = None

    @property
    def signature(self) -> str:
        args = ", ".join(f"{p.type} {p.name}" + (f" = {p.default}" if p.default else "") for p in self.params)
        return f"{self.result} {self.name}({args}){' const' if self.const else ''}"


@dataclass
class Enum:
    qualname: str  # e.g. "Frequency::Units" or "SidebandSide"
    name: str
    scope: str | None  # owning class or None
    values: list[str]
    doc: str


@dataclass
class Class:
    name: str
    bases: list[str]
    doc: str
    methods: list[Method] = field(default_factory=list)
    enums: list[Enum] = field(default_factory=list)
    has_copy_ctor: bool = False

    @property
    def is_unit(self) -> bool:
        return any(e.name == "Units" for e in self.enums)


@dataclass
class Api:
    classes: list[Class]
    enums: list[Enum]
    functions: list[Method]
    typedefs: dict[str, str]


# --------------------------------------------------------------------------- parsing
def system_includes() -> list[str]:
    out = subprocess.run(["c++", "-x", "c++", "-E", "-v", "-"], input="", capture_output=True, text=True).stderr
    inc, on = [], False
    for line in out.splitlines():
        if line.startswith("#include <...> search starts here"):
            on = True
        elif line.startswith("End of search list"):
            break
        elif on:
            inc.append("-isystem" + line.strip())
    return inc


def clean_type(spelling: str) -> str:
    s = spelling.replace(f"{NAMESPACE}::", "")
    s = re.sub(r"\bstd::__cxx11::", "std::", s)
    s = re.sub(r"std::basic_string<char>", "std::string", s)
    s = re.sub(r"(?<![:\w])string\b", "std::string", s)
    s = re.sub(r"(?<![:\w])vector<", "std::vector<", s)
    return s


def clean_doc(raw: str | None) -> str:
    if not raw:
        return ""
    lines = []
    for line in raw.splitlines():
        line = line.strip()
        line = re.sub(r"^/\*[*!]?<?", "", line)
        line = re.sub(r"\*/$", "", line)
        line = re.sub(r"^//[/!]<?", "", line)
        line = re.sub(r"^\*\s?", "", line)
        lines.append(line.rstrip())
    text = "\n".join(lines).strip()
    text = text.replace("\\brief ", "").replace("\\f$", "$").replace("\\f[", "$$").replace("\\f]", "$$")
    return text.replace(")doc\"", ")doc \"")


def default_value(parm: ci.Cursor) -> str | None:
    toks = [t.spelling for t in parm.get_tokens()]
    if "=" not in toks:
        return None
    expr = " ".join(toks[toks.index("=") + 1:])
    return clean_type(expr)


def method_from_cursor(c: ci.Cursor, kind: str) -> Method:
    params = []
    for i, p in enumerate(c.get_arguments()):
        params.append(Param(clean_type(p.type.spelling), p.spelling or f"arg{i}", default_value(p)))
    result = "" if kind == "ctor" else clean_type(c.result_type.spelling)
    m = Method(kind, c.spelling, result, params, c.is_const_method() if kind != "ctor" else False,
               clean_doc(c.raw_comment))
    for p in params:
        if p.type in ("const char *", ARRAY_PTR) or CLASS_REF.match(p.type) or VECTOR_REF.match(p.type):
            continue
        if "*" in p.type:
            m.skip_reason = f"pointer parameter '{p.type} {p.name}'"
        elif "&" in p.type and not p.type.startswith("const "):
            m.skip_reason = f"output (non-const reference) parameter '{p.type} {p.name}'"
    if "*" in result and result != "const char *":
        m.skip_reason = f"returns pointer '{result}'"
    return m


def enum_from_cursor(c: ci.Cursor, scope: str | None) -> Enum:
    values = [v.spelling for v in c.get_children() if v.kind == ci.CursorKind.ENUM_CONSTANT_DECL]
    q = f"{scope}::{c.spelling}" if scope else c.spelling
    return Enum(q, c.spelling, scope, values, clean_doc(c.raw_comment))


def parse_api(include_dir: Path = INCLUDE_DIR) -> Api:
    headers = sorted(h for h in include_dir.glob("*.h") if h.name not in EXCLUDED_HEADERS)
    umbrella = "\n".join(f'#include "{h.name}"' for h in headers)
    args = ["-x", "c++", "-std=c++17", f"-I{include_dir}", *system_includes()]
    tu = ci.Index.create().parse("pyatm_umbrella.cpp", args=args, unsaved_files=[("pyatm_umbrella.cpp", umbrella)],
                                 options=ci.TranslationUnit.PARSE_SKIP_FUNCTION_BODIES)
    errors = [d for d in tu.diagnostics if d.severity >= ci.Diagnostic.Error]
    if errors:
        raise RuntimeError("libclang errors:\n" + "\n".join(str(e) for e in errors))

    api = Api([], [], [], {})
    seen = set()

    def in_atm(c: ci.Cursor) -> bool:
        return c.location.file is not None and Path(c.location.file.name).parent == include_dir

    for ns in tu.cursor.get_children():
        if ns.kind != ci.CursorKind.NAMESPACE or ns.spelling != NAMESPACE:
            continue
        for c in ns.get_children():
            if not in_atm(c):
                continue
            if (c.kind == ci.CursorKind.CLASS_DECL and c.is_definition() and c.spelling not in seen
                    and c.spelling not in EXCLUDED_CLASSES):
                seen.add(c.spelling)
                api.classes.append(parse_class(c))
            elif c.kind == ci.CursorKind.ENUM_DECL and c.is_definition():
                api.enums.append(enum_from_cursor(c, None))
            elif c.kind == ci.CursorKind.FUNCTION_DECL and c.spelling not in {f.name for f in api.functions}:
                api.functions.append(method_from_cursor(c, "static"))
            elif c.kind == ci.CursorKind.TYPEDEF_DECL:
                api.typedefs[c.spelling] = clean_type(c.underlying_typedef_type.spelling)
    return api


def parse_class(c: ci.Cursor) -> Class:
    cls = Class(c.spelling, [], clean_doc(c.raw_comment))
    for ch in c.get_children():
        if ch.kind == ci.CursorKind.CXX_BASE_SPECIFIER:
            if ch.access_specifier == ci.AccessSpecifier.PUBLIC and not ch.type.spelling.startswith("std::"):
                cls.bases.append(clean_type(ch.type.spelling))
            continue
        if ch.access_specifier != ci.AccessSpecifier.PUBLIC:
            continue
        if ch.kind == ci.CursorKind.ENUM_DECL:
            cls.enums.append(enum_from_cursor(ch, cls.name))
        elif ch.kind == ci.CursorKind.CONSTRUCTOR:
            if ch.is_copy_constructor():
                cls.has_copy_ctor = True
            elif not ch.is_move_constructor():
                cls.methods.append(method_from_cursor(ch, "ctor"))
        elif ch.kind == ci.CursorKind.CXX_METHOD:
            if ch.spelling in OPERATORS:
                cls.methods.append(method_from_cursor(ch, "operator"))
            elif ch.spelling.startswith("operator"):
                continue  # assignment etc.
            else:
                cls.methods.append(method_from_cursor(ch, "static" if ch.is_static_method() else "method"))
    # libclang spells nested enums unqualified inside their class ("Units"): qualify them ("Angle::Units")
    for m in cls.methods:
        if (cls.name, m.name, len(m.params)) in NOT_IMPLEMENTED:
            m.skip_reason = "declared but not implemented in ATM"
    for e in cls.enums:
        pat = re.compile(rf"(?<![:\w]){e.name}\b")
        for m in cls.methods:
            m.result = pat.sub(f"{cls.name}::{e.name}", m.result)
            for p in m.params:
                p.type = pat.sub(f"{cls.name}::{e.name}", p.type)
                if p.default is not None:
                    p.default = re.sub(rf"(?<![:\w])({'|'.join(e.values)})\b", rf"{cls.name}::\1", p.default)
    return cls


# --------------------------------------------------------------------------- emission
def cpp_str(s: str) -> str:
    return 'R"doc(' + s + ')doc"' if s else '""'


def py_args(m: Method) -> str:
    out = []
    for p in m.params:
        a = f'py::arg("{p.name}")'
        if p.default is not None:
            a += f" = {p.default}"
        out.append(a)
    return "".join(", " + a for a in out)


def array_lambda(cls: str, m: Method) -> str:
    """Lambda replacing 'double *' parameters by std::vector<double> and 'std::vector<C> &' by in-place lists."""
    decl, call, pre = [], [], []
    for p in m.params:
        vec = VECTOR_REF.match(p.type)
        if p.type == ARRAY_PTR:
            decl.append(f"std::vector<double> {p.name}")
            call.append(f"{p.name}.data()")
        elif vec:
            decl.append(f"py::list {p.name}")
            pre.append(f"pyatm::ListRef<{vec.group(1)}> {p.name}_ref({p.name}); ")
            call.append(f"{p.name}_ref.vec")
        else:
            decl.append(f"{p.type} {p.name}")
            call.append(p.name)
    body = "".join(pre)
    if m.kind == "ctor":
        return f"py::init([]({', '.join(decl)}) {{ {body}return new {cls}({', '.join(call)}); }})"
    self_decl = f"{'const ' if m.const else ''}{cls} &self"
    return f"[]({', '.join([self_decl] + decl)}) {{ {body}return self.{m.name}({', '.join(call)}); }}"


def has_array(m: Method) -> bool:
    return any(p.type == ARRAY_PTR or VECTOR_REF.match(p.type) for p in m.params)


def member_ptr(cls: str, m: Method) -> str:
    types = ", ".join(p.type for p in m.params)
    if m.kind == "static":
        return f"static_cast<{m.result} (*)({types})>(&{cls}::{m.name})"
    return f"static_cast<{m.result} ({cls}::*)({types}){' const' if m.const else ''}>(&{cls}::{m.name})"


def emit(api: Api) -> tuple[str, list[str]]:
    skipped: list[str] = []
    L: list[str] = []
    w = L.append
    w("// ---------------------------------------------------------------------------")
    w("// GENERATED FILE - DO NOT EDIT.  Produced by tools/generate_bindings.py from")
    w("// cpp/ATM/include/*.h; re-run the generator after syncing ATM from TELCAL.")
    w("// ---------------------------------------------------------------------------")
    w('#include "pyatm_bindings.h"')
    w("")
    for h in sorted(INCLUDE_DIR.glob("*.h")):
        if h.name not in EXCLUDED_HEADERS:
            w(f'#include "{h.name}"')
    w("")
    w("namespace py = pybind11;")
    w("using namespace ATM_NAMESPACE;")
    w("using std::string;")
    w("using std::vector;")
    w("")
    w("void pyatm_register_generated(py::module_ &m)")
    w("{")

    # 1. namespace level enums
    for e in api.enums:
        w(f'  py::enum_<{e.qualname}>(m, "{e.name}", {cpp_str(e.doc)})')
        for v in e.values:
            w(f'      .value("{v}", {v})')
        w("      .export_values();")
    w("")

    # 2. declare all classes (so that every type is known before default arguments are converted)
    for c in api.classes:
        bases = "".join(", " + b for b in c.bases)
        w(f'  py::class_<{c.name}{bases}> cls_{c.name}(m, "{c.name}", {cpp_str(c.doc)});')
        for e in c.enums:
            w(f'  py::enum_<{e.qualname}>(cls_{c.name}, "{e.name}", {cpp_str(e.doc)})')
            for v in e.values:
                w(f'      .value("{v}", {e.qualname}::{v})')
            w("      .export_values();")
    for alias, target in api.typedefs.items():
        if any(c.name == target for c in api.classes):
            w(f'  m.attr("{alias}") = m.attr("{target}");')
    w("")

    # 3. members
    for c in api.classes:
        cv = f"cls_{c.name}"
        w(f"  // ----- {c.name}")
        # copy constructor (declared or implicit, as all ATM classes are copyable)
        w(f"  {cv}.def(py::init<const {c.name} &>(), py::arg(\"other\"), \"Copy constructor\");")
        w(f'  {cv}.def("__copy__", []({c.name} const &self) {{ return {c.name}(self); }});')
        w(f'  {cv}.def("__deepcopy__", []({c.name} const &self, py::dict) {{ return {c.name}(self); }}, py::arg("memo"));')
        done_ops = set()
        statics = {m.name for m in c.methods if m.kind == "static" and not m.skip_reason}
        mixed = statics & {m.name for m in c.methods if m.kind == "method" and not m.skip_reason}
        # pybind11 tries overloads in registration order and accepts a Python int for a double
        # parameter: register the overloads with fewer floating point parameters first so that
        # f(unsigned spwid, unsigned nc) is chosen before f(unsigned nc, double airmass) for ints
        for m in sorted(c.methods, key=lambda m: sum(p.type in ("double", "float") for p in m.params)):
            if m.skip_reason:
                skipped.append(f"{c.name}::{m.signature}  [{m.skip_reason}]")
                continue
            if m.kind == "ctor" and has_array(m):
                w(f"  {cv}.def({array_lambda(c.name, m)}{py_args(m)}, {cpp_str(m.doc)});")
            elif m.kind == "ctor":
                types = ", ".join(p.type for p in m.params)
                w(f"  {cv}.def(py::init<{types}>(){py_args(m)}, {cpp_str(m.doc)});")
                if c.is_unit and len(m.params) == 1 and m.params[0].type == "double":
                    w(f"  py::implicitly_convertible<py::float_, {c.name}>();")
                    w(f"  py::implicitly_convertible<py::int_, {c.name}>();")
            elif m.kind == "operator":
                pyname, op = OPERATORS[m.name]
                if not m.params:
                    if m.name == "operator-":
                        w(f'  {cv}.def("__neg__", []({c.name} a) {{ return -a; }});')
                    continue
                rhs = m.params[0].type
                if rhs in ("float", "int", "unsigned int"):
                    continue  # the double overload covers all Python numbers
                if (pyname, rhs) in done_ops:
                    continue
                done_ops.add((pyname, rhs))
                rhs_decl = rhs if rhs.endswith("&") else rhs
                w(f'  {cv}.def("{pyname}", []({c.name} a, {rhs_decl} b) {{ return a {op} b; }}, py::is_operator());')
                if pyname == "__mul__" and rhs == "double":
                    w(f'  {cv}.def("__rmul__", []({c.name} a, double b) {{ return a * b; }}, py::is_operator());')
            elif m.kind == "method" and has_array(m):
                w(f'  {cv}.def("{m.name}", {array_lambda(c.name, m)}{py_args(m)}, {cpp_str(m.doc)});')
            elif m.kind == "static" and m.name in mixed:
                # Python cannot overload static and instance methods under one name: the static
                # overload is added as an instance overload and as the static '<name>_static'
                args = ", ".join(f"{p.type} {p.name}" for p in m.params)
                names = ", ".join(p.name for p in m.params)
                w(f'  {cv}.def("{m.name}", [](const {c.name} &, {args}) {{ return {c.name}::{m.name}({names}); }}'
                  f'{py_args(m)}, {cpp_str(m.doc)});')
                w(f'  {cv}.def_static("{m.name}_static", {member_ptr(c.name, m)}{py_args(m)}, {cpp_str(m.doc)});')
            else:
                fn = "def_static" if m.kind == "static" else "def"
                w(f'  {cv}.{fn}("{m.name}", {member_ptr(c.name, m)}{py_args(m)}, {cpp_str(m.doc)});')
        if any(m.name == "operator==" for m in c.methods):
            w(f"  {cv}.attr(\"__hash__\") = py::none();")
        w("")

    # 4. free functions
    for f in api.functions:
        if f.skip_reason:
            skipped.append(f"{f.signature}  [{f.skip_reason}]")
            continue
        w(f'  m.def("{f.name}", {member_ptr("", f).replace("&::", "&")}{py_args(f)}, {cpp_str(f.doc)});')
    w("}")
    return "\n".join(L) + "\n", skipped


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--report", action="store_true", help="print the methods that could not be bound automatically")
    ap.add_argument("-o", "--output", type=Path, default=OUTPUT)
    a = ap.parse_args()
    api = parse_api()
    code, skipped = emit(api)
    a.output.parent.mkdir(parents=True, exist_ok=True)
    a.output.write_text(code)
    n = sum(len(c.methods) for c in api.classes) + len(api.functions)
    print(f"Wrote {a.output} ({len(api.classes)} classes, {n} functions/methods, {len(skipped)} skipped)")
    if a.report:
        print("\n".join("  skipped: " + s for s in skipped))
    return 0


if __name__ == "__main__":
    sys.exit(main())
