"""Python port of TelCalResults/Libraries/ATM/test/AtmProfileTest.cpp."""
from pyatm import AtmProfile, Humidity, Length, Pressure, Temperature
from refcompare import assert_matches_ref, cformat as f


def run() -> list[str]:
    out = []
    atmType = 1  # TROPICAL
    T = Temperature(270.0, "K")
    P = Pressure(560.0, "mb")
    H = Humidity(20.0, "%")
    Alt = Length(5000, "m")
    WVL = Length(2.0, "km")
    TLR = -5.6
    topAtm = Length(48.0, "km")
    Pstep = Pressure(5.0, "mb")
    PstepFact = 1.1

    out.append(" AtmProfileTest: BASIC ATMOSPHERIC PARAMETERS TO GENERATE REFERENCE ATMOSPHERIC PROFILE")
    out.append(" AtmProfileTest:   ")
    out.append(f" AtmProfileTest: Ground temperature T:         {f(T.get())} K")
    out.append(f" AtmProfileTest: Ground pressure P:            {f(P.get('mb'))} mb")
    out.append(f" AtmProfileTest: Relative humidity rh:         {f(H.get('%'))} %")
    out.append(f" AtmProfileTest: Scale height h0:              {f(WVL.get('km'))} km")
    out.append(f" AtmProfileTest: Pressure step dp:             {f(Pstep.get('mb'))} mb")
    out.append(f" AtmProfileTest: Altitude alti:                {f(Alt.get())} m")
    out.append(f" AtmProfileTest: Attitude top atm profile atmh:{f(topAtm.get('km'))} km")
    out.append(f" AtmProfileTest: Pressure step factordp1:      {f(PstepFact)} ")
    out.append(f" AtmProfileTest: Tropospheric lapse rate:    {f(TLR)} K/km")

    myProfile = AtmProfile(Alt, P, T, TLR, H, WVL, Pstep, PstepFact, topAtm, atmType)

    out.append(f" AtmProfileTest: Atmospheric type:             {myProfile.getAtmosphereType()}")
    out.append(" AtmProfileTest:   ")
    out.append(" AtmProfileTest:   ")
    out.append(" AtmProfileTest: Object myProfile built with the AtmProfile CONSTRUCTOR and the above entries")
    out.append("  ")
    out.append(f" AtmProfileTest: Number of layers returned:  {myProfile.getNumLayer()}")
    out.append(" AtmProfileTest: Layer parameters:  ")

    for i in range(myProfile.getNumLayer()):
        out.append(
            f" AtmProfileTest:  P: {f(myProfile.getLayerPressure(i).get('mb'))} mb"
            f"  T: {f(myProfile.getLayerTemperature(i).get('K'))} K"
            f"  Thickness: {f(myProfile.getLayerThickness(i).get('m'))} m"
            f"  WaterVapor: {f(myProfile.getLayerWaterVaporMassDensity(i).get('kgm**-3'))} kg m-3"
            f"  WaterVapor: {f(myProfile.getLayerWaterVaporNumberDensity(i).get('m**-3'))} m-3"
            f"  CO: {f(myProfile.getLayerCO(i).get('m**-3'))} m-3"
            f"  O3: {f(myProfile.getLayerO3(i).get('m**-3'))} m-3"
            f"  N2O: {f(myProfile.getLayerN2O(i).get('m**-3'))} m-3")

    out.append("# altitude [km]\to3 [cm**-3]\tn2 [cm**-3]\tco [cm**-3]\tno2 [cm**-3]\tso2 [cm**-3]")
    alt = [0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0,
           16.0, 17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 23.0, 24.0, 25.0, 27.5, 30.0, 32.5, 35.0,
           37.5, 40.0, 42.5, 45.0, 47.5, 50.0, 55.0, 60.0, 65.0, 70.0, 75.0, 80.0, 85.0, 90.0,
           95.0, 100.0, 105.0, 110.0, 115.0, 120.0]
    for a in alt:
        minorden = myProfile.st76(Length(a, "km"), atmType, 5)
        out.append(f"{f(a)}\t" + "".join(f"{f(minorden[k].get('cm**-3'))}\t" for k in range(5)))
    return out


def test_AtmProfileTest():
    assert_matches_ref(run(), "AtmProfileTest")
