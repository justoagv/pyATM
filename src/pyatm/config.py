"""Location of the ATM C++ headers, library and CMake/pkg-config files shipped with pyatm.

Command line usage::

    pyatm-config --cflags            # -I<include dir> [-DALMA_TELCAL]
    pyatm-config --libs              # -L<lib dir> -Wl,-rpath,<lib dir> -lATM
    pyatm-config --cmakedir          # use with -Dpyatm_DIR=... and find_package(pyatm)
    pyatm-config --pkgconfigdir      # use with PKG_CONFIG_PATH=...
    pyatm-config --namespace         # telcal::atm or atm
"""
from __future__ import annotations

import argparse
from pathlib import Path

from . import _build_info

_ROOT = Path(__file__).resolve().parent


def get_include() -> str:
    """Directory containing the ATM C++ headers (``ATMSkyStatus.h`` ...)."""
    return str(_ROOT / "include")


def get_library_dir() -> str:
    """Directory containing the ATM shared library (``libATM.so``)."""
    return str(_ROOT / "lib")


def get_cmake_dir() -> str:
    """Directory containing ``pyatmConfig.cmake`` (imported target ``pyatm::ATM``)."""
    return str(_ROOT / "lib" / "cmake" / "pyatm")


def get_pkgconfig_dir() -> str:
    """Directory containing ``pyatm.pc``."""
    return str(_ROOT / "lib" / "pkgconfig")


def get_cflags() -> str:
    return " ".join(f for f in (f"-I{get_include()}", _build_info.CFLAGS_NAMESPACE) if f)


def get_libs() -> str:
    lib = get_library_dir()
    return f"-L{lib} -Wl,-rpath,{lib} -lATM"


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(prog="pyatm-config", description=__doc__.splitlines()[0])
    options = {
        "--cflags": get_cflags,
        "--libs": get_libs,
        "--includedir": get_include,
        "--libdir": get_library_dir,
        "--cmakedir": get_cmake_dir,
        "--pkgconfigdir": get_pkgconfig_dir,
        "--namespace": lambda: _build_info.CXX_NAMESPACE,
        "--version": lambda: _build_info.ATM_VERSION,
    }
    for opt in options:
        parser.add_argument(opt, action="store_true")
    args = parser.parse_args(argv)
    selected = [fn() for opt, fn in options.items() if getattr(args, opt[2:])]
    if not selected:
        parser.print_help()
        return 1
    print(" ".join(selected))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
