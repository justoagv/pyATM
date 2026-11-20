"""Dump the public C++ API of the ATM headers (development helper)."""
import sys
from pathlib import Path

import clang.cindex as ci

sys.path.insert(0, str(Path(__file__).parent))
from generate_bindings import parse_api  # noqa: E402

api = parse_api()
for cls in api.classes:
    print(f"class {cls.name} bases={cls.bases}")
    for m in cls.methods:
        print("   ", m.kind, m.signature)
for f in api.functions:
    print("func", f.signature)
for e in api.enums:
    print("enum", e.qualname, e.values)
