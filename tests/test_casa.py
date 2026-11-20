"""Tests of pyatm.casa.atmosphere (emulation of casatools.atmosphere) against direct ATM calls."""
import logging

import numpy as np
import pytest

import pyatm
from pyatm.casa import atmosphere, quantity


def reference_objects(fc_ghz=90.0, fw_ghz=0.64, fr_ghz=0.01):
    """ATM objects built as CASA's initAtmProfile/initSpectralWindow do with the default parameters."""
    profile = pyatm.AtmProfile(pyatm.Length(5000, "m"), pyatm.Pressure(560, "mb"), pyatm.Temperature(270, "K"),
                               -5.6, pyatm.Percent(20, "%"), pyatm.Length(2, "km"), pyatm.Pressure(10, "mb"), 1.2,
                               pyatm.Length(48, "km"), 1)
    nchan = int(np.ceil(fw_ghz / fr_ghz))
    ref_freq = pyatm.Frequency(fc_ghz, "GHz")
    chan_sep = pyatm.Frequency(fr_ghz, "GHz")
    if nchan % 2 == 0:
        ref_freq = ref_freq - chan_sep * 0.5
    grid = pyatm.SpectralGrid(nchan, (nchan - 1) // 2, ref_freq, chan_sep)
    rip = pyatm.RefractiveIndexProfile(grid, profile)
    sky = pyatm.SkyStatus(rip)
    sky.setUserWH2O(sky.getGroundWH2O())
    return profile, grid, rip, sky


@pytest.fixture
def at():
    tool = atmosphere()
    tool.initAtmProfile()
    tool.initSpectralWindow(1, quantity(90, "GHz"), quantity(0.64, "GHz"), quantity(0.01, "GHz"))
    yield tool
    tool.done()


def test_quantity_parsing():
    assert quantity("5000m") == {"value": 5000.0, "unit": "m"}
    assert quantity("-5.6 K/km") == {"value": -5.6, "unit": "K/km"}
    assert quantity(0.5, "GHz") == {"value": 0.5, "unit": "GHz"}
    assert np.array_equal(quantity([1, 2], "mm")["value"], [1.0, 2.0])


def test_version_and_types():
    at = atmosphere()
    assert at.getAtmVersion() == pyatm.getTag()
    assert at.listAtmosphereTypes() == ["1 - TROPICAL", "2 - MIDLATSUMMER", "3 - MIDLATWINTER",
                                        "4 - SUBARTSUMMER", "5 - SUBARTWINTER"]


def test_init_profile_report_and_parameters():
    at = atmosphere()
    text = at.initAtmProfile()
    assert text.startswith("BASIC ATMOSPHERIC PARAMETERS TO GENERATE REFERENCE ATMOSPHERIC PROFILE")
    assert "Atmospheric type:             TROPICAL" in text
    profile = reference_objects()[0]
    assert f"Built atmospheric profile with {profile.getNumLayer()} layers." in text
    assert at.getNumLayers() == profile.getNumLayer()
    _, alt, temp, pres, top, hum, tlr, dp, dpm, h0, atm_type = at.getBasicAtmParms()
    assert (alt["value"][0], alt["unit"]) == (5000.0, "m")
    assert (temp["value"][0], temp["unit"]) == (270.0, "K")
    assert (pres["value"][0], pres["unit"]) == (pytest.approx(560.0), "mbar")
    assert (top["value"][0], top["unit"]) == (pytest.approx(48.0), "km")
    assert hum == pytest.approx(20.0)
    assert (tlr["value"][0], tlr["unit"]) == (-5.6, "K/km")
    assert dp["value"][0] == pytest.approx(10.0)
    assert dpm == 1.2
    assert h0["value"][0] == pytest.approx(2.0)
    assert atm_type == "TROPICAL"
    assert at.getGroundWH2O()["value"][0] == pytest.approx(profile.getGroundWH2O().get("mm"))


def test_init_profile_units_are_converted():
    a, b = atmosphere(), atmosphere()
    a.initAtmProfile(altitude="5.059km", temperature=quantity(269, "K"), pressure="55450Pa", maxAltitude="48000m",
                     dTem_dh=quantity(-0.0056, "K/m"), dP="1000Pa", h0="2000m")
    b.initAtmProfile(altitude=5059, temperature=269, pressure=554.5, maxAltitude=48, dTem_dh=-5.6, dP=10, h0=2)
    pa, pb = a.getProfile(), b.getProfile()
    for qa_, qb_ in zip(pa[1:], pb[1:]):
        assert qa_["unit"] == qb_["unit"]
        np.testing.assert_allclose(qa_["value"], qb_["value"], rtol=1e-12)


def test_user_defined_temperature_profile():
    at = atmosphere()
    text = at.initAtmProfile(layerBoundaries=quantity([5500, 6000], "m"), layerTemperature=[265, 262])
    assert "User-defined temperature profile: ON" in text
    with pytest.raises(RuntimeError):
        at.initAtmProfile(layerBoundaries=[5500, 6000], layerTemperature=[265])
    with pytest.raises(RuntimeError):
        at.initAtmProfile(atmType=6)


def test_profile_matches_atm():
    at = atmosphere()
    at.initAtmProfile()
    profile = reference_objects()[0]
    text, thickness, temperature, wmd, water, pressure, o3, co, n2o = at.getProfile()
    n = profile.getNumLayer()
    assert text.startswith(f"Number of layers returned: {n}")
    assert [q["unit"] for q in (thickness, temperature, wmd, water, pressure, o3, co, n2o)] == \
        ["m", "K", "kg m-3", "m-3", "mb", "m-3", "m-3", "m-3"]
    np.testing.assert_array_equal(pressure["value"], [profile.getLayerPressure(i).get("mb") for i in range(n)])
    np.testing.assert_array_equal(temperature["value"], [profile.getLayerTemperature(i).get() for i in range(n)])
    np.testing.assert_array_equal(wmd["value"], [profile.getLayerWaterVaporMassDensity(i).get() for i in range(n)])


def test_spectral_window(at):
    profile, grid, rip, sky = reference_objects()
    assert at.getNumSpectralWindows() == 1
    assert at.getNumChan() == grid.getNumChan(0) == 64
    assert at.getRefChan() == grid.getRefChan(0)
    assert at.getRefFreq() == {"value": pytest.approx([grid.getRefFreq(0).get("GHz")]), "unit": "GHz"}
    assert at.getChanSep()["value"][0] == pytest.approx(10.0) and at.getChanSep()["unit"] == "MHz"
    assert at.getBandwidth()["value"][0] == pytest.approx(grid.getBandwidth(0).get("GHz"))
    assert at.getMinFreq()["value"][0] == pytest.approx(grid.getMinFreq(0).get("GHz"))
    assert at.getMaxFreq()["value"][0] == pytest.approx(grid.getMaxFreq(0).get("GHz"))
    assert at.getChanFreq(5)["value"][0] == pytest.approx(grid.getChanFreq(0, 5).get("GHz"))
    np.testing.assert_array_equal(at.getSpectralWindow()["value"], grid.getSpectralWindow(0))
    assert at.getChanNum("90.005GHz") == grid.getChanNum(0, 90.005e9)


def test_odd_and_multiple_windows():
    at = atmosphere()
    at.initAtmProfile()
    assert at.initSpectralWindow(2, quantity([90, 230], "GHz"), quantity([0.1, 2], "GHz"),
                                 quantity([10, 500], "MHz")) == 10
    assert at.getNumChan(1) == 4
    assert at.addSpectralWindow("350GHz", "0.008GHz", "0.002GHz") == 4
    assert at.getNumSpectralWindows() == 3
    assert at.initSpectralWindow(1, 183, 0, 0) == 1  # fRes = 0: one channel
    assert at.initSpectralWindow(2, [90], [1], [0.1]) == -1  # sizes != nbands
    assert at.addSpectralWindow(350, 0.008, 0) == -1  # fRes = 0 not allowed


def test_opacities_path_lengths_and_temperatures(at):
    profile, grid, rip, sky = reference_objects()
    ref = grid.getRefChan(0)
    assert at.getDryOpacity() == rip.getDryOpacity(0, ref).get()
    assert at.getDryOpacity(3) == rip.getDryOpacity(0, 3).get()
    assert at.getDryContOpacity(3) == rip.getDryContOpacity(0, 3).get()
    assert at.getO2LinesOpacity(3) == rip.getO2LinesOpacity(0, 3).get()
    assert at.getH2OLinesOpacity(3) == sky.getH2OLinesOpacity(0, 3).get()
    assert at.getWetOpacity(3) == {"value": [sky.getWetOpacity(0, 3).get()], "unit": "neper"}
    n, dry = at.getDryOpacitySpec()
    assert n == 64 and np.array_equal(dry, [rip.getDryOpacity(0, i).get() for i in range(64)])
    n, wet = at.getWetOpacitySpec()
    assert wet["unit"] == "neper" and wet["value"][3] == sky.getWetOpacity(0, 3).get()
    assert at.getDispersivePhaseDelay(3)["value"][0] == sky.getDispersiveH2OPhaseDelay(0, 3).get("deg")
    assert at.getNonDispersiveDryPathLength(3) == {"value": [rip.getNonDispersiveDryPathLength(0, 3).get()],
                                                   "unit": "m"}
    assert at.getNonDispersiveWetPathLength(3)["value"][0] == \
        rip.getNonDispersiveH2OPathLength(rip.getGroundWH2O(), 0, 3).get()
    assert at.getAbsTotalWet(2, 3) == {"value": [rip.getAbsTotalWet(0, 3, 2).get()], "unit": "m-1"}
    assert at.getTebbSky(3)["value"][0] == sky.getTebbSky(0, 3).get()
    assert at.getTebbSky(3, wh2o="2mm")["value"][0] == sky.getTebbSky(0, 3, pyatm.Length(2, "mm")).get()
    assert at.getTrjSky(3)["value"][0] == sky.getTrjSky(0, 3).get()
    assert at.getAverageTebbSky()["value"][0] == sky.getAverageTebbSky(0).get()
    n, tebb = at.getTebbSkySpec()
    assert tebb["value"][7] == sky.getTebbSky(0, 7).get()


def test_sky_status_setters(at):
    assert at.getUserWH2O()["value"][0] == pytest.approx(at.getGroundWH2O()["value"][0])
    t1 = at.getTebbSky()["value"][0]
    assert at.setUserWH2O("2mm") and at.getUserWH2O() == {"value": [2.0], "unit": "mm"}
    assert at.setAirMass(2.0) and at.getAirMass() == 2.0
    assert at.setSkyBackgroundTemperature(quantity(3, "K"))
    assert at.getSkyBackgroundTemperature() == {"value": [3.0], "unit": "K"}
    assert at.getTebbSky()["value"][0] > t1


def test_update_profile(at):
    t1 = at.getTebbSky()["value"][0]
    text = at.updateAtmProfile(temperature=280, humidity=20)
    assert text.startswith("UPDATED BASIC ATMOSPHERIC PARAMETERS")
    assert at.getBasicAtmParms()[2]["value"][0] == 280
    assert at.getTebbSky()["value"][0] != t1


def test_errors_and_warnings(caplog):
    at = atmosphere()
    with caplog.at_level(logging.WARNING):
        assert at.getNumLayers() == -1
        assert at.initSpectralWindow() == -1
    assert "initAtmProfile" in caplog.text
    with pytest.raises(RuntimeError, match="Spectral window is not defined yet"):
        at.getDryOpacity()
    at.initAtmProfile()
    at.initSpectralWindow()
    with pytest.raises(RuntimeError, match="Spw ID out of range."):
        at.getRefChan(1)
    with pytest.raises(RuntimeError, match="Channel ID out of range."):
        at.getChanFreq(1)  # default window has a single channel
    with pytest.raises(RuntimeError):
        at.getAbsTotalDry(-1)
    with pytest.raises(IndexError):
        at.getAbsTotalDry(at.getNumLayers())
    assert at.close()
