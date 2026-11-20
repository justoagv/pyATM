"""Python port of TelCalResults/Libraries/ATM/test/SkyStatusTest_TINV.cpp.

Reads the temperature-inversion profile ``invt.dat`` (C++: ../test/T-INVERSION/invt.dat).
"""
import re

from pyatm import (AtmProfile, Frequency, Humidity, Length, Pressure, RefractiveIndexProfile,
                   SkyStatus, SpectralGrid, Temperature)
from refcompare import DATA_DIR, assert_matches_ref, cformat as f

STRLEN = 40


def _atof(s: str) -> float:
    """C atof: leading whitespace skipped, longest numeric prefix parsed, 0.0 if none."""
    m = re.match(r"\s*([-+]?(?:\d+\.?\d*|\.\d+)(?:[eE][-+]?\d+)?)", s)
    return float(m.group(1)) if m else 0.0


def read_invt(path=DATA_DIR / "invt.dat"):
    """Reproduce the fgets/strtok parsing loop of the C++ test."""
    heights, temperatures = [], []
    with open(path) as fp:
        lines = fp.read().splitlines(keepends=True)
    # fgets(aRow, STRLEN, fp) twice (header), then one row per fgets until EOF
    for row in lines[2:]:
        row = row[:STRLEN - 1]
        height, _, rest = row.partition(",")
        heights.append(Length(_atof(height), "m"))
        temperatures.append(Temperature(_atof(rest.lstrip(" ").split(" ")[0]), "K"))
    return heights, temperatures


def run() -> list[str]:
    out = []
    v_ProfileHeightLevels, v_ProfileTemperatureLevels = read_invt()

    atmType = 1  # TROPICAL
    T = Temperature(265.54, "K")
    P = Pressure(560.0, "mb")
    H = Humidity(20.0, "%")
    Alt = Length(5000, "m")
    WVL = Length(2.0, "km")
    TLR = -5.6
    topAtm = Length(48.0, "km")
    Pstep = Pressure(3.0, "mb")
    PstepFact = 1.05

    out.append(" SkyStatusTest: BASIC ATMOSPHERIC PARAMETERS TO GENERATE REFERENCE ATMOSPHERIC PROFILE")
    out.append(" SkyStatusTest:   ")
    out.append(f" SkyStatusTest: Ground temperature T:         {f(T.get())} K")
    out.append(f" SkyStatusTest: Ground pressure P:            {f(P.get('mb'))} mb")
    out.append(f" SkyStatusTest: Relative humidity rh:         {f(H.get('%'))} %")
    out.append(f" SkyStatusTest: Scale height h0:              {f(WVL.get('km'))} km")
    out.append(f" SkyStatusTest: Pressure step dp:             {f(Pstep.get('mb'))} mb")
    out.append(f" SkyStatusTest: Altitude alti:                {f(Alt.get())} m")
    out.append(f" SkyStatusTest: Attitude top atm profile atmh:{f(topAtm.get('km'))} km")
    out.append(f" SkyStatusTest: Pressure step factordp1:      {f(PstepFact)} ")
    out.append(f" SkyStatusTest: Tropospherique lapse rate:    {f(TLR)} K/km")

    myProfile = AtmProfile(Alt, P, T, TLR, H, WVL, Pstep, PstepFact, topAtm, atmType,
                           v_ProfileHeightLevels, v_ProfileTemperatureLevels)

    out.append(f" SkyStatusTest: Atmospheric type:             {myProfile.getAtmosphereType()}")
    out.append(" SkyStatusTest:   ")
    out.append(" SkyStatusTest:   ")

    out.append(" SkyStatusTest: Object myProfile built with the AtmProfile CONSTRUCTOR and the above entries")
    out.append(" SkyStatusTest:   ")
    out.append(f" SkyStatusTest: Number of layers returned:  {myProfile.getNumLayer()}")
    out.append(" SkyStatusTest: Layer parameters:  ")

    out.append(f" SkyStatusTest: size of Temperature Profile: {len(myProfile.getTemperatureProfile())}")
    out.append(" SkyStatusTest actual profile:")
    out.append("!  P0       P       P1        T0        T         T1        H0          H1       lyr tck    H2O_0     H2O_1      H2O")
    out.append("! (mb)     (mb)    (mb)      (K)       (K)       (K)       (m)         (m)         (m)     (g m^-3)  (g m^-3)  (g m^-3)")

    # cout.setf(ios::fixed); cout.precision(4): from here on doubles are printed as %.4f
    def g(x):
        return f"{x:.4f}"

    for i in range(myProfile.getNumLayer()):
        out.append(
            f"{g(myProfile.getLayerBottomPressure(i).get('mb'))} "
            f"{g(myProfile.getLayerPressure(i).get('mb'))} "
            f"{g(myProfile.getLayerTopPressure(i).get('mb'))} "
            f"{g(myProfile.getLayerBottomTemperature(i).get('K'))}  "
            f"{g(myProfile.getLayerTemperature(i).get('K'))}  "
            f"{g(myProfile.getLayerTopTemperature(i).get('K'))}  "
            f"{g(myProfile.getLayerBottomHeightAboveSeaLevel(i).get('m'))}   "
            f"{g(myProfile.getLayerTopHeightAboveSeaLevel(i).get('m'))}   "
            f"{g(myProfile.getLayerThickness(i).get('m'))}   "
            f"{g(myProfile.getLayerBottomWaterVaporMassDensity(i).get('gm**-3'))}    "
            f"{g(myProfile.getLayerTopWaterVaporMassDensity(i).get('gm**-3'))}    "
            f"{g(myProfile.getLayerWaterVaporMassDensity(i).get('gm**-3'))} ")

    out.append(f" SkyStatusTest: First guess precipitable water vapor content: {g(myProfile.getGroundWH2O().get('mm'))}mm")
    out.append(" SkyStatusTest: (This value is estimated from the relative humidity at ground level and the water vapor scale height)")
    out.append(" SkyStatusTest:   ")
    out.append(" SkyStatusTest:   ")

    out.append(" SkyStatusTest:    TEST FOR JUST 1 FREQUENCY  ")
    out.append(" SkyStatusTest:    =========================  ")
    out.append(" SkyStatusTest:  ")

    mySingleFreq = Frequency(850, "GHz")
    myRefractiveIndexProfile = RefractiveIndexProfile(mySingleFreq, myProfile)
    mySky_siglefreq = SkyStatus(myRefractiveIndexProfile)

    new_wh2o0 = Length(1.0, "mm")
    mySky_siglefreq.setUserWH2O(new_wh2o0)

    for i in range(mySky_siglefreq.getNumSpectralWindow()):
        for j in range(mySky_siglefreq.getNumChan(i)):
            out.append(f" SkyStatusTest: Frequency      : {g(mySky_siglefreq.getChanFreq(j).get('GHz'))} GHz")
            out.append(f" SkyStatusTest: Wet opacity    : {g(mySky_siglefreq.getWetOpacity(j).get())} nepers, for "
                       f"{g(mySky_siglefreq.getUserWH2O().get('mm'))} mm H2O")
            out.append(f" SkyStatusTest: Dry opacity    : {g(mySky_siglefreq.getDryOpacity(j).get())} nepers ")
            out.append(f" SkyStatusTest: Sky brightness : {g(mySky_siglefreq.getAverageTebbSky(j).get('K'))} K")

    new_wh2o = Length(0.45, "mm")
    out.append(f" SkyStatusTest: (EXTERNAL CHANGE) water vapor column:           {g(new_wh2o.get('mm'))} mm")
    out.append(f" SkyStatusTest: (NEW OUTPUT) T_EBB =                         {g(mySky_siglefreq.getAverageTebbSky(new_wh2o).get('K'))} K ")
    out.append(f" SkyStatusTest: Current water vapor column in Radiance Class:{g(mySky_siglefreq.getUserWH2O().get('mm'))} mm")
    out.append(" SkyStatusTest:  ")

    mySky_siglefreq.setAirMass(2.0)

    out.append(f" SkyStatusTest: (INTERNAL CHANGE) Air mass:                     {g(mySky_siglefreq.getAirMass())}   ")
    out.append(f" SkyStatusTest: (NEW OUTPUT) T_EBB =                         {g(mySky_siglefreq.getAverageTebbSky().get('K'))} K ")
    out.append("")

    new_wh2o1 = Length(0.8, "mm")
    mySky_siglefreq.setUserWH2O(new_wh2o1)

    out.append(f" SkyStatusTest: (INTERNAL CHANGE) water vapor column:           {g(mySky_siglefreq.getUserWH2O().get('mm'))} mm")
    out.append(f" SkyStatusTest: (NEW OUTPUT) T_EBB =                         {g(mySky_siglefreq.getAverageTebbSky().get('K'))} K ")
    out.append("")

    out.append(" SkyStatusTest:    TEST FOR ONE SPECTRAL WINDOW WITH SEVERAL CHANNELS  ")
    out.append(" SkyStatusTest:    =====================================================  ")
    out.append(" SkyStatusTest:  ")

    numchan = 399
    refchan = 200
    reffreq = Frequency(650.00, "GHz")
    chansep = Frequency(0.10, "GHz")

    band = SpectralGrid(numchan, refchan, reffreq, chansep)
    abs_band = RefractiveIndexProfile(band, myProfile)
    mySky_1band_8channels = SkyStatus(abs_band)
    sky = mySky_1band_8channels

    out.append(f" SkyStatusTest: water vapor column: {g(sky.getUserWH2O().get('mm'))} mm")
    out.append(f" SkyStatusTest: Air mass          : {g(sky.getAirMass())}")
    out.append(" ")
    for i in range(sky.getNumChan(0)):
        out.append(f" SkyStatusTest: Freq: {g(sky.getChanFreq(i).get('GHz'))} GHz  /  T_EBB={g(sky.getTebbSky(i).get('K'))} K ")
    out.append(" SkyStatusTest:  ")

    sky.setAirMass(1.0)
    sky.setUserWH2O(0.45, "mm")
    mySky_siglefreq.setUserWH2O(0.45, "mm")

    out.append(f" SkyStatusTest: water vapor column: {g(sky.getUserWH2O().get('mm'))} mm")
    out.append(f" SkyStatusTest: Air mass          : {g(sky.getAirMass())}")
    out.append(" ")

    for i in range(sky.getNumChan(0)):
        out.append(f" SkyStatusTest: Freq: {g(sky.getChanFreq(i).get('GHz'))} GHz  /  T_EBB={g(sky.getTebbSky(i).get('K'))}"
                   f" Dry opacity: {g(sky.getDryOpacity(i).get('np'))} np "
                   f" Wet opacity: {g(sky.getWetOpacity(i).get('np'))} np "
                   f" Total opacity: {g(sky.getTotalOpacity(i).get('np'))} np ")
    return out


def test_SkyStatusTest_TINV():
    assert_matches_ref(run(), "SkyStatusTest_TINV")
