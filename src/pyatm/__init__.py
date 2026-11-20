"""pyatm - Python bindings of the ALMA Atmospheric Transmission at Microwaves (ATM) C++ library.

The C++ classes (``SkyStatus``, ``RefractiveIndexProfile``, ``AtmProfile``,
``SpectralGrid``, the unit classes ``Length``, ``Frequency`` ...) are exposed
with the same names, methods and overloads as in C++.

* :mod:`pyatm.casa` provides ``atmosphere``, an emulation of the CASA
  ``casatools.atmosphere`` tool.
* :mod:`pyatm.config` locates the shipped C++ headers and library
  (``pyatm-config --cflags --libs``, ``pyatm.get_cmake_dir()``).
"""
from ._atm import *  # noqa: F401,F403
from ._atm import AtmException, __version__  # noqa: F401
from . import _build_info
from .config import get_cmake_dir, get_include, get_library_dir  # noqa: F401

CXX_NAMESPACE = _build_info.CXX_NAMESPACE
