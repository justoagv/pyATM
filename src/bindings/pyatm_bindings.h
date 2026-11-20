// Common declarations of the pyatm pybind11 extension module.
#ifndef PYATM_BINDINGS_H
#define PYATM_BINDINGS_H

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>

// Generated from cpp/ATM/include/*.h by tools/generate_bindings.py
void pyatm_register_generated(pybind11::module_ &m);

namespace pyatm {

// Exposes a Python list of bound objects as a 'std::vector<T> &' argument: the C++ code works
// on a copy whose elements are assigned back to the Python objects when the call returns.
template <class T>
struct ListRef {
  pybind11::list list;
  std::vector<T> vec;
  explicit ListRef(pybind11::list l) : list(l), vec(l.cast<std::vector<T>>()) {}
  ~ListRef()
  {
    for (size_t i = 0; i < vec.size() && i < list.size(); ++i) list[i].template cast<T &>() = vec[i];
  }
};

} // namespace pyatm

#endif
