#!/usr/bin/env python3
"""Check that every ATM class / method used by C++ client code is available in pyatm.

    python tools/check_coverage.py <TELCAL>/TelCalResults/Libraries/ATM/test/*.cpp \
                                   <TELCAL>/TelCalResults/Engines/src/*Scan*.cpp ...

For each source file, the identifiers called as ``obj.name(``, ``obj->name(`` or
``Class::name(`` that are part of the ATM API (parsed from cpp/ATM/include with
libclang, see generate_bindings.py) are looked up in the installed ``pyatm``
module.  Exits with status 1 if something is missing.
"""
from __future__ import annotations

import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import generate_bindings as gb  # noqa: E402

import pyatm  # noqa: E402

CALL = re.compile(r"(?:\.|->|::)\s*(\w+)\s*\(")
WORD = re.compile(r"\b([A-Z]\w+)\b")


def main(files: list[str]) -> int:
    api = gb.parse_api()
    classes = {c.name for c in api.classes} | set(api.typedefs) | {"AtmException"}
    methods: dict[str, set[str]] = {}
    for c in api.classes:
        for m in c.methods:
            if m.kind in ("method", "static"):
                methods.setdefault(m.name, set()).add(c.name)
    for f in api.functions:
        methods.setdefault(f.name, set()).add("")

    def bound(name: str, owners: set[str]) -> bool:
        return any(hasattr(getattr(pyatm, o) if o else pyatm, name) for o in owners)

    missing = 0
    for path in files:
        text = Path(path).read_text(errors="replace")
        text = re.sub(r"//.*", "", text)
        used_methods = {n for n in CALL.findall(text) if n in methods}
        used_classes = {n for n in WORD.findall(text) if n in classes}
        miss = sorted([f"{n} ({'/'.join(sorted(methods[n]))})" for n in used_methods if not bound(n, methods[n])]
                      + [c for c in used_classes if not hasattr(pyatm, c)])
        status = "OK " if not miss else "MISSING"
        print(f"{status} {Path(path).name}: {len(used_classes)} classes, {len(used_methods)} methods"
              + (f" -> {', '.join(miss)}" if miss else ""))
        missing += len(miss)
    return 1 if missing else 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
