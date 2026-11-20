"""Binding specific behaviour not covered by the ports of the ATM unit tests."""
import copy

import pytest

import pyatm


def test_version_and_namespace():
    assert pyatm.__version__ == pyatm.getVersion() == pyatm.ATM_VERSION
    assert pyatm.CXX_NAMESPACE in ("telcal::atm", "atm")


def test_units_repr_float_and_implicit_conversion():
    assert repr(pyatm.Length(1, "mm")) == "Length(0.001, 'm')"
    assert float(pyatm.Temperature(270, "K")) == 270.0
    assert pyatm.Percent(20, "%").get() == pytest.approx(0.2)
    # C++ implicit conversion double -> Length (SI) is available
    assert pyatm.Length(3.0) + 2.0 == pyatm.Length(5.0)


def test_copy_constructor():
    m = pyatm.WVRMeasurement(pyatm.Angle(30, "deg"), [pyatm.Temperature(100, "K")])
    for c in (pyatm.WVRMeasurement(m), copy.copy(m), copy.deepcopy(m)):
        assert c is not m
        assert c.getElevation().get("deg") == pytest.approx(30)


def test_integer_overloads_preferred():
    # SpectralGrid(numChan, refChan, chanFreq, units) must not resolve to (numChan, double refFreq, ...)
    freqs = [90e9 + i * 1e7 for i in range(64)]
    grid = pyatm.SpectralGrid(64, 32, freqs, pyatm.Frequency.UnitHertz)
    assert grid.getRefChan() == 32
    assert grid.getRefFreq().get("Hz") == freqs[31]  # refChan is 1-based in ATM


def test_static_and_instance_overloads():
    profile = pyatm.AtmProfile(pyatm.Length(5000, "m"), pyatm.Pressure(560, "mb"), pyatm.Temperature(270, "K"),
                               -5.6, pyatm.Humidity(20, "%"), pyatm.Length(2, "km"), 1)
    assert profile.getAtmosphereType() == "TROPICAL"
    assert pyatm.AtmProfile.getAtmosphereType_static(2) == "MIDLATSUMMER"
    assert profile.getAtmosphereType(3) == "MIDLATWINTER"


def test_atm_exception_is_runtime_error():
    assert issubclass(pyatm.AtmException, RuntimeError)
