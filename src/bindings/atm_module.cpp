// pyatm._atm extension module: hand-written parts complementing atm_generated.cpp
#include "pyatm_bindings.h"

#include "ATMException.h"
#include "ATMVersion.h"

#include <sstream>

namespace py = pybind11;

PYBIND11_MODULE(_atm, m)
{
  m.doc() = "Python bindings of the ALMA Atmospheric Transmission at Microwaves (ATM) C++ library";

  // C++ ATM_NAMESPACE::AtmException -> Python pyatm.AtmException (a RuntimeError)
  static py::exception<ATM_NAMESPACE::AtmException> atmException(m, "AtmException", PyExc_RuntimeError);
  py::register_exception_translator([](std::exception_ptr p) {
    try {
      if (p) std::rethrow_exception(p);
    } catch (const ATM_NAMESPACE::AtmException &e) {
      py::set_error(atmException, e.what());
    }
  });

  pyatm_register_generated(m);

#ifdef ALMA_TELCAL
  m.attr("CXX_NAMESPACE") = "telcal::atm";
#else
  m.attr("CXX_NAMESPACE") = "atm";
#endif
  m.attr("__version__") = ATM_NAMESPACE::getVersion();
  m.attr("ATM_VERSION") = ATM_VERSION;  // macro of ATMVersion.h

  // Human readable representation of the unit classes; float() gives the value in internal (SI) units
  auto addRepr = [&m](const char *cls, const char *unit) {
    py::object c = m.attr(cls);
    std::string name(cls), u(unit);
    c.attr("__repr__") = py::cpp_function(
        [name, u](py::object self) {
          std::ostringstream os;
          os.precision(10);
          os << name << "(" << self.attr("get")(u).cast<double>() << ", '" << u << "')";
          return os.str();
        },
        py::is_method(c));
    c.attr("__float__") = py::cpp_function([](py::object self) { return self.attr("get")().cast<double>(); },
                                           py::is_method(c));
  };
  addRepr("Angle", "rad");
  addRepr("Frequency", "Hz");
  addRepr("InverseLength", "m-1");
  addRepr("Length", "m");
  addRepr("MassDensity", "kgm**-3");
  addRepr("NumberDensity", "m**-3");
  addRepr("Opacity", "np");
  addRepr("Percent", "%");
  addRepr("Pressure", "Pa");
  addRepr("Temperature", "K");
}
