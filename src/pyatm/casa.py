"""Emulation of the CASA ``casatools.atmosphere`` tool on top of the pyatm bindings.

The behaviour (defaults, units, returned values, warnings) follows CASA's
``atmosphere_cmpt.cc``::

    from pyatm.casa import atmosphere, quantity as qa_quantity
    at = atmosphere()
    print(at.initAtmProfile(altitude=qa_quantity(5000, 'm'), humidity=20.0))
    nchan = at.initSpectralWindow(1, qa_quantity(90, 'GHz'), qa_quantity(0.64, 'GHz'), qa_quantity(0.01, 'GHz'))
    at.getTebbSky()            # {'value': array([...]), 'unit': 'K'}

Quantities may be given as CASA quantity dictionaries (``{'value': v, 'unit': u}``,
e.g. from ``casatools.quanta.quantity`` or :func:`quantity`), as strings
(``'5000m'``, ``'0.5 GHz'``) or as plain numbers in the default unit of the parameter.
Quantities are returned as ``{'value': numpy.ndarray, 'unit': str}``; methods
with output parameters return a tuple ``(return value, output 1, output 2, ...)``.
"""
from __future__ import annotations

import logging
import math
import re
from typing import Any

import numpy as np

from . import _atm as atm

__all__ = ["atmosphere", "quantity"]

_log = logging.getLogger(__name__)

# Unit scale factors relative to the base unit of each dimension (as casacore's unit factors)
_UNITS: dict[str, tuple[str, float]] = {}
for _dim, _table in {
    "length": {"m": 1.0, "km": 1e3, "cm": 1e-2, "mm": 1e-3, "um": 1e-6, "micron": 1e-6, "nm": 1e-9},
    "pressure": {"Pa": 1.0, "hPa": 1e2, "kPa": 1e3, "mbar": 1e2, "mb": 1e2, "bar": 1e5, "atm": 101325.0},
    "temperature": {"K": 1.0, "mK": 1e-3},
    "frequency": {"Hz": 1.0, "kHz": 1e3, "MHz": 1e6, "GHz": 1e9, "THz": 1e12},
    "lapse_rate": {"K/m": 1.0, "K/km": 1e-3},
}.items():
    for _u, _f in _table.items():
        _UNITS[_u] = (_dim, _f)

_QSTRING = re.compile(r"^\s*([-+]?(?:\d+\.?\d*|\.\d+)(?:[eE][-+]?\d+)?)\s*(\S*)\s*$")


def quantity(value: Any, unit: str = "") -> dict:
    """Equivalent of ``casatools.quanta.quantity``: ``quantity(5000, 'm')`` or ``quantity('5000m')``."""
    if isinstance(value, str) and not unit:
        m = _QSTRING.match(value)
        if not m:
            raise ValueError(f"Cannot parse quantity '{value}'")
        return {"value": float(m.group(1)), "unit": m.group(2)}
    if isinstance(value, (list, tuple, np.ndarray)):
        return {"value": np.asarray(value, dtype=float), "unit": unit}
    return {"value": float(value), "unit": unit}


def _q(x: Any, default_unit: str) -> tuple[np.ndarray, str]:
    """Normalise an input quantity to (values, unit)."""
    if isinstance(x, dict):
        unit = x.get("unit", x.get("units", "")) or default_unit
        return np.atleast_1d(np.asarray(x["value"], dtype=float)), unit
    if isinstance(x, str):
        d = quantity(x)
        return np.atleast_1d(np.asarray(d["value"], dtype=float)), d["unit"] or default_unit
    return np.atleast_1d(np.asarray(x, dtype=float)), default_unit


def _factor(unit_from: str, unit_to: str) -> float:
    try:
        dim_from, f_from = _UNITS[unit_from]
        dim_to, f_to = _UNITS[unit_to]
    except KeyError as e:
        raise ValueError(f"Unknown unit {e}") from None
    if dim_from != dim_to:
        raise ValueError(f"Incompatible units '{unit_from}' and '{unit_to}'")
    return f_from / f_to


def _value(x: Any, default_unit: str, unit: str) -> np.ndarray:
    """Values of the input quantity ``x`` converted to ``unit`` (casacore ``Quantity::getValue``)."""
    v, u = _q(x, default_unit)
    return v * _factor(u, unit)


def _qout(values, unit: str) -> dict:
    return {"value": np.atleast_1d(np.asarray(values, dtype=float)), "unit": unit}


def _empty_q() -> dict:
    return {"value": np.array([], dtype=float), "unit": ""}


class atmosphere:  # noqa: N801  (CASA tool name)
    """Atmosphere model (emulation of ``casatools.atmosphere``)."""

    _SPW_WARN = "Please set spectral window(s) with initSpectralWindow first."
    _PROFILE_WARN = "Please initialize atmospheric profile with initAtmProfile."

    def __init__(self):
        self._cleanup()

    def _cleanup(self):
        self._profile = None   # AtmProfile
        self._grid = None      # SpectralGrid
        self._rip = None       # RefractiveIndexProfile
        self._sky = None       # SkyStatus
        self._dPm = None       # pressure step factor given to initAtmProfile

    # ------------------------------------------------------------------ helpers
    def _assert_spwid(self, spwid: int):
        if self._grid is None:
            raise RuntimeError("Spectral window is not defined yet")
        if spwid < 0 or spwid >= self._grid.getNumSpectralWindow():
            raise RuntimeError("Spw ID out of range.")

    def _assert_spwid_and_channel(self, spwid: int, chan: int):
        if self._grid is None:
            raise RuntimeError("Spectral window is not defined yet")
        self._assert_spwid(spwid)
        if chan < 0 or chan >= self._grid.getNumChan(spwid):
            raise RuntimeError("Channel ID out of range.")

    def _chan(self, nc: int, spwid: int) -> int:
        return self._grid.getRefChan(spwid) if nc < 0 else nc

    def _two_id(self, obj, func, nc: int, spwid: int, unit=None, get_unit="np"):
        """CASA doTwoIdATMFuncDouble / doTwoIdATMFuncQuantum."""
        self._assert_spwid(spwid)
        if obj is None:
            _log.warning(self._SPW_WARN)
            return -1.0 if unit is None else _empty_q()
        value = func(obj, spwid, self._chan(nc, spwid)).get(get_unit)
        return value if unit is None else _qout(value, unit)

    def _abs(self, method: str, nl: int, nf: int, spwid: int) -> dict:
        """CASA doRIPThreeIdFuncQuantum."""
        if nl < 0:
            raise RuntimeError("Layer number must be >= 0.")
        self._assert_spwid_and_channel(spwid, nf)
        if self._rip is None:
            _log.warning(self._SPW_WARN)
            return {"value": np.array([-1.0]), "unit": ""}
        return _qout(getattr(self._rip, method)(spwid, nf, nl).get("m-1"), "m-1")

    def _rebuild_sky(self):
        self._rip = atm.RefractiveIndexProfile(self._grid, self._profile)
        self._sky = atm.SkyStatus(self._rip)
        # CASA work around: set the 1st guess water column as user water column
        self._sky.setUserWH2O(self._sky.getGroundWH2O())

    # ------------------------------------------------------------------ tool lifecycle / info
    def close(self) -> bool:
        """Destroy the atmosphere tool."""
        self._cleanup()
        return True

    def done(self) -> bool:
        """Destroy the atmosphere tool."""
        self._cleanup()
        return True

    def getAtmVersion(self) -> str:
        """Returns the version of ATM library implemented to this tool."""
        return atm.getTag()

    def listAtmosphereTypes(self) -> list[str]:
        """Returns a list of index numbers and corresponding atmosphere types used by the ATM library."""
        return [f"{i} - {atm.AtmProfile.getAtmosphereType_static(i)}" for i in range(1, int(atm.typeATM_end))]

    # ------------------------------------------------------------------ atmospheric profile
    def initAtmProfile(self, altitude=5000.0, temperature=270.0, pressure=560.0, maxAltitude=48.0, humidity=20.0,
                       dTem_dh=-5.6, dP=10.0, dPm=1.2, h0=2.0, atmType=1,
                       layerBoundaries: Any = "", layerTemperature: Any = "") -> str:
        """Build the atmospheric profile (see casatools.atmosphere.initAtmProfile)."""
        if atmType < 1 or atmType >= int(atm.typeATM_end):
            raise RuntimeError("atmType not in permissive range.")
        alt = atm.Length(float(_value(altitude, "m", "m")[0]), atm.Length.UnitMeter)
        P = atm.Pressure(float(_value(pressure, "mbar", "mbar")[0]), atm.Pressure.UnitMilliBar)
        T = atm.Temperature(float(_value(temperature, "K", "K")[0]), atm.Temperature.UnitKelvin)
        tlr = float(_value(dTem_dh, "K/km", "K/km")[0])
        H = atm.Percent(float(humidity), atm.Percent.UnitPercent)
        wvl = atm.Length(float(_value(h0, "km", "km")[0]), atm.Length.UnitKiloMeter)
        pstep = atm.Pressure(float(_value(dP, "mbar", "mbar")[0]), atm.Pressure.UnitMilliBar)
        top = atm.Length(float(_value(maxAltitude, "km", "m")[0]), atm.Length.UnitMeter)
        # user-defined temperature profile: quantities (default units m and K), '' or [] when not used
        def _layers(x, unit):
            if isinstance(x, str) and not x.strip():
                return []
            if not isinstance(x, (dict, str)) and len(x) == 0:
                return []
            return [float(v) for v in _value(x, unit, unit)]
        layerBoundaries = _layers(layerBoundaries, "m")
        layerTemperature = _layers(layerTemperature, "K")
        if len(layerBoundaries) != len(layerTemperature):
            raise RuntimeError("Size of user-defined layer boundaries and temperature does not match.")
        user_profile = len(layerBoundaries) > 0

        out = ["BASIC ATMOSPHERIC PARAMETERS TO GENERATE REFERENCE ATMOSPHERIC PROFILE", "  ",
               f"Ground temperature T:         {T.get('K'):g} K",
               f"Ground pressure P:            {P.get('mb'):g} mb",
               f"Relative humidity rh:         {H.get('%'):g} %",
               f"Scale height h0:              {wvl.get('km'):g} km",
               f"Pressure step dp:             {pstep.get('mb'):g} mb",
               f"Altitude alti:                {alt.get('m'):g} m",
               f"Attitude top atm profile:     {top.get('km'):g} km",
               f"Pressure step factor:         {float(dPm):g} ",
               f"Tropospheric lapse rate:      {tlr:g} K/km"]

        self._cleanup()
        if user_profile:
            self._profile = atm.AtmProfile(alt, P, T, tlr, H, wvl, pstep, float(dPm), top, int(atmType),
                                           [atm.Length(b, atm.Length.UnitMeter) for b in layerBoundaries],
                                           [atm.Temperature(t, atm.Temperature.UnitKelvin) for t in layerTemperature])
        else:
            self._profile = atm.AtmProfile(alt, P, T, tlr, H, wvl, pstep, float(dPm), top, int(atmType))
        self._dPm = float(dPm)
        out += [f"Atmospheric type:             {self._profile.getAtmosphereType()}",
                f"User-defined temperature profile: {'ON' if user_profile else 'OFF'}", "",
                f"Built atmospheric profile with {self._profile.getNumLayer()} layers.", ""]
        return "\n".join(out) + "\n"

    def updateAtmProfile(self, altitude=5000.0, temperature=270.0, pressure=560.0, humidity=20.0, dTem_dh=-5.6,
                         h0=2.0) -> str:
        """Update the basic atmospheric parameters of the profile (and of the spectral computations)."""
        alt = atm.Length(float(_value(altitude, "m", "m")[0]), atm.Length.UnitMeter)
        P = atm.Pressure(float(_value(pressure, "mbar", "mbar")[0]), atm.Pressure.UnitMilliBar)
        T = atm.Temperature(float(_value(temperature, "K", "K")[0]), atm.Temperature.UnitKelvin)
        tlr = float(_value(dTem_dh, "K/km", "K/km")[0])
        H = atm.Percent(float(humidity), atm.Percent.UnitPercent)
        wvl = atm.Length(float(_value(h0, "km", "km")[0]), atm.Length.UnitKiloMeter)
        if self._profile is not None:
            if not self._profile.setBasicAtmosphericParameters(alt, P, T, tlr, H, wvl):
                _log.warning("Atmospheric profile update failed!")
            if self._rip is not None and not self._rip.setBasicAtmosphericParameters(alt, P, T, tlr, H, wvl):
                _log.warning("Refractive index profile update failed!")
            if self._sky is not None:
                if not self._sky.setBasicAtmosphericParameters(alt, P, T, tlr, H, wvl):
                    _log.warning("Skystatus update failed!")
                self._sky.setUserWH2O(self._sky.getGroundWH2O())
        else:
            _log.warning(self._PROFILE_WARN)
        out = ["UPDATED BASIC ATMOSPHERIC PARAMETERS TO GENERATE REFERENCE ATMOSPHERIC PROFILE", "  ",
               f"Ground temperature T:         {T.get('K'):g} K",
               f"Ground pressure P:            {P.get('mb'):g} mb",
               f"Relative humidity rh:         {H.get('%'):g} %",
               f"Scale height h0:              {wvl.get('km'):g} km",
               f"Altitude alti:                {alt.get('m'):g} m",
               f"Tropospheric lapse rate:      {tlr:g} K/km", ""]
        return "\n".join(out) + "\n"

    def getBasicAtmParms(self):
        """Current basic parameters: ``(text, altitude, temperature, pressure, maxAltitude, humidity, dTem_dh,
        dP, dPm, h0, atmType)``.

        ``dPm`` is the value given to :meth:`initAtmProfile` (ATM SEP2024 has no accessor for it).
        """
        if self._profile is None:
            _log.warning(self._PROFILE_WARN)
            e = _empty_q()
            return ("", e, e, e, e, 0.0, e, e, 0.0, e, "")
        p = self._profile
        altitude = _qout(p.getAltitude().get("m"), "m")
        temperature = _qout(p.getGroundTemperature().get("K"), "K")
        pressure = _qout(p.getGroundPressure().get("mb"), "mbar")
        maxAltitude = _qout(p.getTopAtmProfile().get("km"), "km")
        humidity = p.getRelativeHumidity().get("%")
        dTem_dh = _qout(p.getTropoLapseRate(), "K/km")
        dP = _qout(p.getPressureStep().get("mb"), "mbar")
        dPm = self._dPm
        h0 = _qout(p.getWvScaleHeight().get("km"), "km")
        atmType = p.getAtmosphereType()
        out = ["CURRENT ATMOSPHERIC PARAMETERS OF REFERENCE ATMOSPHERIC PROFILE", "  ",
               f"Ground temperature T:         {temperature['value'][0]:g} K",
               f"Ground pressure P:            {pressure['value'][0]:g} mbar",
               f"Relative humidity rh:         {humidity:g} %",
               f"Scale height h0:              {h0['value'][0]:g} km",
               f"Pressure step dp:             {dP['value'][0]:g} mbar",
               f"Altitude alti:                {altitude['value'][0]:g} m",
               f"Attitude top atm profile      {maxAltitude['value'][0]:g} km",
               f"Pressure step factor          {dPm:g} ",
               f"Tropospheric lapse rate       {dTem_dh['value'][0]:g} K/km",
               f"Atmospheric type:             {atmType}", "",
               f"Atmospheric profile has {p.getNumLayer()} layers.", ""]
        return ("\n".join(out) + "\n", altitude, temperature, pressure, maxAltitude, humidity, dTem_dh, dP, dPm,
                h0, atmType)

    def getNumLayers(self) -> int:
        """Number of layers of the atmospheric profile (-1 if not initialised)."""
        if self._profile is None:
            _log.warning(self._PROFILE_WARN)
            return -1
        return self._profile.getNumLayer()

    def getGroundWH2O(self) -> dict:
        """Zenith water vapour column of the profile (mm)."""
        if self._profile is None:
            _log.warning(self._PROFILE_WARN)
            return _empty_q()
        return _qout(self._profile.getGroundWH2O().get("mm"), "mm")

    def getProfile(self):
        """Layer profile: ``(text, thickness, temperature, watermassdensity, water, pressure, O3, CO, N2O)``."""
        if self._profile is None:
            _log.warning(self._PROFILE_WARN)
            e = _empty_q()
            return ("", e, e, e, e, e, e, e, e)
        p = self._profile
        nl = p.getNumLayer()
        units = {"thickness": "m", "temperature": "K", "watermassdensity": "kg m-3", "water": "m-3",
                 "pressure": "mb", "O3": "m-3", "CO": "m-3", "N2O": "m-3"}
        getters = {"thickness": p.getLayerThickness, "temperature": p.getLayerTemperature,
                   "watermassdensity": p.getLayerWaterVaporMassDensity,
                   "water": p.getLayerWaterVaporNumberDensity, "pressure": p.getLayerPressure,
                   "O3": p.getLayerO3, "CO": p.getLayerCO, "N2O": p.getLayerN2O}
        v = {k: np.array([getters[k](i).get(units[k]) for i in range(nl)]) for k in units}
        lines = [f"Number of layers returned: {nl}", "Layer parameters: "]
        for i in range(nl):
            lines.append(f" P: {v['pressure'][i]:g} mb  T: {v['temperature'][i]:g} K"
                         f"  Thickness: {v['thickness'][i]:g} m  WaterVapor: {v['watermassdensity'][i]:g} kg m-3"
                         f"  WaterVapor: {v['water'][i]:g} m-3  CO: {v['CO'][i]:g} m-3"
                         f"  O3: {v['O3'][i]:g} m-3  N2O: {v['N2O'][i]:g} m-3")
        q = {k: {"value": v[k], "unit": units[k]} for k in units}
        return ("\n".join(lines) + "\n", q["thickness"], q["temperature"], q["watermassdensity"], q["water"],
                q["pressure"], q["O3"], q["CO"], q["N2O"])

    # ------------------------------------------------------------------ spectral windows
    @staticmethod
    def _window(fc: float, fc_unit: str, fw: float, fw_unit: str, fr: float, fr_unit: str):
        """numChan, refChan, refFreq, chanSep as computed by CASA (BW = nchan * resolution)."""
        num_chan = 1 if fr == 0 else int(math.ceil(fw * _factor(fw_unit, fr_unit) / fr))
        ref_chan = (num_chan - 1) // 2
        ref_freq = atm.Frequency(fc * _factor(fc_unit, "Hz"), "Hz")
        chan_sep = atm.Frequency(fr * _factor(fr_unit, "Hz"), "Hz")
        if num_chan % 2 == 0:
            # even number of channels: the band centre is a channel boundary
            ref_freq = ref_freq - chan_sep * 0.5
        return num_chan, ref_chan, ref_freq, chan_sep

    def initSpectralWindow(self, nbands=1, fCenter=90, fWidth=0.64, fRes=0.0) -> int:
        """Define ``nbands`` spectral windows and compute absorption/emission; returns the channels of spw 0."""
        if nbands < 1:
            raise RuntimeError("nbands should be > 0.")
        if self._profile is None:
            _log.warning("Initialize atmospheric profile with initAtmProfile first.")
            return -1
        fc, ufc = _q(fCenter, "GHz")
        fw, ufw = _q(fWidth, "GHz")
        fr, ufr = _q(fRes, "GHz")
        if len(fc) != nbands or len(fw) != nbands or len(fr) != nbands:
            _log.warning("Dimensions of fCenter, fWidth and fRes != nbands!")
            return -1
        windows = [self._window(fc[i], ufc, fw[i], ufw, fr[i], ufr) for i in range(nbands)]
        self._grid = atm.SpectralGrid(*windows[0])
        for w in windows[1:]:
            self._grid.add(*w)
        self._rebuild_sky()
        return windows[0][0]

    def addSpectralWindow(self, fCenter=350, fWidth=0.008, fRes=0.002) -> int:
        """Add a spectral window (no sideband); returns its number of channels."""
        if self._grid is None:
            _log.warning("Initialize spectral window with initSpectralWindow first.")
            return -1
        fc, ufc = _q(fCenter, "GHz")
        fw, ufw = _q(fWidth, "GHz")
        fr, ufr = _q(fRes, "GHz")
        if fr[0] == 0:
            _log.warning("Resolution of band cannot be 0,0 GHz!")
            return -1
        w = self._window(fc[0], ufc, fw[0], ufw, fr[0], ufr)
        self._grid.add(*w)
        self._rebuild_sky()
        return w[0]

    def getNumSpectralWindows(self) -> int:
        if self._grid is None:
            _log.warning("Please set spectral window(s) with initSpectralWindow.")
            return -1
        return self._grid.getNumSpectralWindow()

    def _grid_int(self, method: str, spwid: int) -> int:
        if self._grid is None:
            _log.warning("Please set spectral window(s) with initSpectralWindow.")
            return -1
        self._assert_spwid(spwid)
        return getattr(self._grid, method)(spwid)

    def _grid_freq(self, method: str, spwid: int, unit: str) -> dict:
        if self._grid is None:
            _log.warning("Please set spectral window(s) with initSpectralWindow.")
            return _empty_q()
        self._assert_spwid(spwid)
        return _qout(getattr(self._grid, method)(spwid).get(unit), unit)

    def getNumChan(self, spwid=0) -> int:
        return self._grid_int("getNumChan", spwid)

    def getRefChan(self, spwid=0) -> int:
        return self._grid_int("getRefChan", spwid)

    def getRefFreq(self, spwid=0) -> dict:
        return self._grid_freq("getRefFreq", spwid, "GHz")

    def getChanSep(self, spwid=0) -> dict:
        return self._grid_freq("getChanSep", spwid, "MHz")

    def getBandwidth(self, spwid=0) -> dict:
        return self._grid_freq("getBandwidth", spwid, "GHz")

    def getMinFreq(self, spwid=0) -> dict:
        return self._grid_freq("getMinFreq", spwid, "GHz")

    def getMaxFreq(self, spwid=0) -> dict:
        return self._grid_freq("getMaxFreq", spwid, "GHz")

    def getChanFreq(self, chanNum=0, spwid=0) -> dict:
        if self._grid is None:
            _log.warning("Please set spectral window(s) with initSpectralWindow.")
            return _empty_q()
        self._assert_spwid_and_channel(spwid, chanNum)
        return _qout(self._grid.getChanFreq(spwid, chanNum).get("GHz"), "GHz")

    def getChanNum(self, freq, spwid=0) -> float:
        if self._grid is None:
            _log.warning("Please set spectral window(s) with initSpectralWindow.")
            return -1.0
        self._assert_spwid(spwid)
        return self._grid.getChanNum(spwid, float(_value(freq, "GHz", "Hz")[0]))

    def getSpectralWindow(self, spwid=0) -> dict:
        if self._grid is None:
            _log.warning("Please set spectral window(s) with initSpectralWindow.")
            return _empty_q()
        self._assert_spwid(spwid)
        return _qout(self._grid.getSpectralWindow(spwid), "Hz")

    # ------------------------------------------------------------------ opacities
    def getDryOpacity(self, nc=-1, spwid=0) -> float:
        return self._two_id(self._rip, lambda o, s, c: o.getDryOpacity(s, c), nc, spwid)

    def getDryContOpacity(self, nc=-1, spwid=0) -> float:
        return self._two_id(self._rip, lambda o, s, c: o.getDryContOpacity(s, c), nc, spwid)

    def getO2LinesOpacity(self, nc=-1, spwid=0) -> float:
        return self._two_id(self._rip, lambda o, s, c: o.getO2LinesOpacity(s, c), nc, spwid)

    def getO3LinesOpacity(self, nc=-1, spwid=0) -> float:
        return self._two_id(self._rip, lambda o, s, c: o.getO3LinesOpacity(s, c), nc, spwid)

    def getCOLinesOpacity(self, nc=-1, spwid=0) -> float:
        return self._two_id(self._rip, lambda o, s, c: o.getCOLinesOpacity(s, c), nc, spwid)

    def getN2OLinesOpacity(self, nc=-1, spwid=0) -> float:
        return self._two_id(self._rip, lambda o, s, c: o.getN2OLinesOpacity(s, c), nc, spwid)

    def getWetOpacity(self, nc=-1, spwid=0) -> dict:
        return self._two_id(self._sky, lambda o, s, c: o.getWetOpacity(s, c), nc, spwid, "neper")

    def getH2OLinesOpacity(self, nc=-1, spwid=0) -> float:
        return self._two_id(self._sky, lambda o, s, c: o.getH2OLinesOpacity(s, c), nc, spwid)

    def getH2OContOpacity(self, nc=-1, spwid=0) -> float:
        return self._two_id(self._sky, lambda o, s, c: o.getH2OContOpacity(s, c), nc, spwid)

    def getDryOpacitySpec(self, spwid=0):
        """``(nchan, numpy array of dry opacities [neper])``."""
        self._assert_spwid(spwid)
        if self._rip is None:
            _log.warning(self._SPW_WARN)
            return -1, np.array([])
        n = self._grid.getNumChan(spwid)
        return n, np.array([self._rip.getDryOpacity(spwid, i).get("np") for i in range(n)])

    def getWetOpacitySpec(self, spwid=0):
        """``(nchan, quantity of wet opacities [neper])``."""
        self._assert_spwid(spwid)
        if self._sky is None:
            _log.warning(self._SPW_WARN)
            return -1, _empty_q()
        n = self._grid.getNumChan(spwid)
        return n, _qout([self._sky.getWetOpacity(spwid, i).get("np") for i in range(n)], "neper")

    # ------------------------------------------------------------------ phase delays and path lengths
    def getDispersivePhaseDelay(self, nc=-1, spwid=0) -> dict:
        return self._two_id(self._sky, lambda o, s, c: o.getDispersiveH2OPhaseDelay(s, c), nc, spwid, "deg", "deg")

    def getDispersiveWetPhaseDelay(self, nc=-1, spwid=0) -> dict:
        return self._two_id(self._rip, lambda o, s, c: o.getDispersiveH2OPhaseDelay(o.getGroundWH2O(), s, c),
                            nc, spwid, "deg", "deg")

    def getNonDispersiveWetPhaseDelay(self, nc=-1, spwid=0) -> dict:
        return self._two_id(self._rip, lambda o, s, c: o.getNonDispersiveH2OPhaseDelay(o.getGroundWH2O(), s, c),
                            nc, spwid, "deg", "deg")

    def getNonDispersiveDryPhaseDelay(self, nc=-1, spwid=0) -> dict:
        return self._two_id(self._rip, lambda o, s, c: o.getNonDispersiveDryPhaseDelay(s, c),
                            nc, spwid, "deg", "deg")

    def getNonDispersivePhaseDelay(self, nc=-1, spwid=0) -> dict:
        return self._two_id(self._sky, lambda o, s, c: o.getNonDispersiveH2OPhaseDelay(s, c),
                            nc, spwid, "deg", "deg")

    def getDispersivePathLength(self, nc=-1, spwid=0) -> dict:
        return self._two_id(self._sky, lambda o, s, c: o.getDispersiveH2OPathLength(s, c), nc, spwid, "m", "m")

    def getDispersiveWetPathLength(self, nc=-1, spwid=0) -> dict:
        return self._two_id(self._rip, lambda o, s, c: o.getDispersiveH2OPathLength(o.getGroundWH2O(), s, c),
                            nc, spwid, "m", "m")

    def getNonDispersiveWetPathLength(self, nc=-1, spwid=0) -> dict:
        return self._two_id(self._rip, lambda o, s, c: o.getNonDispersiveH2OPathLength(o.getGroundWH2O(), s, c),
                            nc, spwid, "m", "m")

    def getNonDispersiveDryPathLength(self, nc=-1, spwid=0) -> dict:
        return self._two_id(self._rip, lambda o, s, c: o.getNonDispersiveDryPathLength(s, c), nc, spwid, "m", "m")

    def getO2LinesPathLength(self, nc=-1, spwid=0) -> dict:
        return self._two_id(self._rip, lambda o, s, c: o.getO2LinesPathLength(s, c), nc, spwid, "m", "m")

    def getO3LinesPathLength(self, nc=-1, spwid=0) -> dict:
        return self._two_id(self._rip, lambda o, s, c: o.getO3LinesPathLength(s, c), nc, spwid, "m", "m")

    def getCOLinesPathLength(self, nc=-1, spwid=0) -> dict:
        return self._two_id(self._rip, lambda o, s, c: o.getCOLinesPathLength(s, c), nc, spwid, "m", "m")

    def getN2OLinesPathLength(self, nc=-1, spwid=0) -> dict:
        return self._two_id(self._rip, lambda o, s, c: o.getN2OLinesPathLength(s, c), nc, spwid, "m", "m")

    def getNonDispersivePathLength(self, nc=-1, spwid=0) -> dict:
        return self._two_id(self._sky, lambda o, s, c: o.getNonDispersiveH2OPathLength(s, c), nc, spwid, "m", "m")

    # ------------------------------------------------------------------ absorption coefficients
    def getAbsH2OLines(self, nl, nf=0, spwid=0) -> dict:
        return self._abs("getAbsH2OLines", nl, nf, spwid)

    def getAbsH2OCont(self, nl, nf=0, spwid=0) -> dict:
        return self._abs("getAbsH2OCont", nl, nf, spwid)

    def getAbsO2Lines(self, nl, nf=0, spwid=0) -> dict:
        return self._abs("getAbsO2Lines", nl, nf, spwid)

    def getAbsDryCont(self, nl, nf=0, spwid=0) -> dict:
        return self._abs("getAbsDryCont", nl, nf, spwid)

    def getAbsO3Lines(self, nl, nf=0, spwid=0) -> dict:
        return self._abs("getAbsO3Lines", nl, nf, spwid)

    def getAbsCOLines(self, nl, nf=0, spwid=0) -> dict:
        return self._abs("getAbsCOLines", nl, nf, spwid)

    def getAbsN2OLines(self, nl, nf=0, spwid=0) -> dict:
        return self._abs("getAbsN2OLines", nl, nf, spwid)

    def getAbsTotalDry(self, nl, nf=0, spwid=0) -> dict:
        return self._abs("getAbsTotalDry", nl, nf, spwid)

    def getAbsTotalWet(self, nl, nf=0, spwid=0) -> dict:
        return self._abs("getAbsTotalWet", nl, nf, spwid)

    # ------------------------------------------------------------------ sky status
    def setUserWH2O(self, wh2o=0.0) -> bool:
        if self._sky is None:
            _log.warning(self._SPW_WARN)
            return False
        v, u = _q(wh2o, "mm")
        self._sky.setUserWH2O(atm.Length(float(v[0]), u))
        return True

    def getUserWH2O(self) -> dict:
        if self._sky is None:
            _log.warning(self._SPW_WARN)
            return _empty_q()
        return _qout(self._sky.getUserWH2O().get("mm"), "mm")

    def setAirMass(self, airmass) -> bool:
        if self._sky is None:
            _log.warning(self._SPW_WARN)
            return False
        self._sky.setAirMass(float(airmass))
        return True

    def getAirMass(self) -> float:
        if self._sky is None:
            _log.warning(self._SPW_WARN)
            return -1.0
        return self._sky.getAirMass()

    def setSkyBackgroundTemperature(self, tbgr=2.73) -> bool:
        if self._sky is None:
            _log.warning(self._SPW_WARN)
            return False
        v, u = _q(tbgr, "K")
        self._sky.setSkyBackgroundTemperature(atm.Temperature(float(v[0]), u))
        return True

    def getSkyBackgroundTemperature(self) -> dict:
        if self._sky is None:
            _log.warning(self._SPW_WARN)
            return _empty_q()
        return _qout(self._sky.getSkyBackgroundTemperature().get("K"), "K")

    # ------------------------------------------------------------------ sky temperatures
    def _user_wh2o(self, wh2o):
        """None if wh2o is the CASA 'not set' value (-1), otherwise an atm.Length."""
        v, u = _q(wh2o, "mm")
        return None if v[0] == -1 else atm.Length(float(v[0]), u)

    def _sky_temp(self, method: str, args: tuple, wh2o) -> dict:
        if self._sky is None:
            _log.warning(self._SPW_WARN)
            return _empty_q()
        w = self._user_wh2o(wh2o)
        f = getattr(self._sky, method)
        return _qout((f(*args) if w is None else f(*args, w)).get("K"), "K")

    def _sky_spec(self, method: str, spwid: int, wh2o):
        self._assert_spwid(spwid)
        if self._sky is None:
            _log.warning(self._SPW_WARN)
            return 0, _empty_q()
        w = self._user_wh2o(wh2o)
        f = getattr(self._sky, method)
        n = self._grid.getNumChan(spwid)
        vals = [(f(spwid, i) if w is None else f(spwid, i, w)).get("K") for i in range(n)]
        return n, _qout(vals, "K")

    def getAverageTebbSky(self, spwid=0, wh2o=-1) -> dict:
        self._assert_spwid(spwid)
        return self._sky_temp("getAverageTebbSky", (spwid,), wh2o)

    def getTebbSky(self, nc=-1, spwid=0, wh2o=-1) -> dict:
        self._assert_spwid(spwid)
        return self._sky_temp("getTebbSky", (spwid, self._chan(nc, spwid)), wh2o)

    def getTebbSkySpec(self, spwid=0, wh2o=-1):
        """``(nchan, quantity of equivalent blackbody temperatures [K])``."""
        return self._sky_spec("getTebbSky", spwid, wh2o)

    def getAverageTrjSky(self, spwid=0, wh2o=-1) -> dict:
        self._assert_spwid(spwid)
        return self._sky_temp("getAverageTrjSky", (spwid,), wh2o)

    def getTrjSky(self, nc=-1, spwid=0, wh2o=-1) -> dict:
        self._assert_spwid(spwid)
        return self._sky_temp("getTrjSky", (spwid, self._chan(nc, spwid)), wh2o)

    def getTrjSkySpec(self, spwid=0, wh2o=-1):
        """``(nchan, quantity of Rayleigh-Jeans temperatures [K])``."""
        return self._sky_spec("getTrjSky", spwid, wh2o)
