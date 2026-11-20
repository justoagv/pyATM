"""Python port of TelCalResults/Libraries/ATM/test/RefractiveIndexProfileTest.cpp."""
from pyatm import (AtmProfile, Frequency, Humidity, Length, Pressure, RefractiveIndexProfile,
                   Temperature)
from refcompare import assert_matches_ref, cformat as f

TAG = " RefractiveIndexProfileTest:"


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

    out.append(f"{TAG} BASIC ATMOSPHERIC PARAMETERS TO GENERATE REFERENCE ATMOSPHERIC PROFILE")
    out.append("  ")
    out.append(f"{TAG} Ground temperature T:         {f(T.get())} K")
    out.append(f"{TAG} Ground pressure P:            {f(P.get('mb'))} mb")
    out.append(f"{TAG} Relative humidity rh:         {f(H.get('%'))} %")
    out.append(f"{TAG} Scale height h0:              {f(WVL.get('km'))} km")
    out.append(f"{TAG} Pressure step dp:             {f(Pstep.get('mb'))} mb")
    out.append(f"{TAG} Altitude alti:                {f(Alt.get())} m")
    out.append(f"{TAG} Attitude top atm profile atmh:{f(topAtm.get('km'))} km")
    out.append(f"{TAG} Pressure step factordp1:      {f(PstepFact)} ")
    out.append(f"{TAG} Tropospherique lapse rate:    {f(TLR)} K/km")

    myProfile = AtmProfile(Alt, P, T, TLR, H, WVL, Pstep, PstepFact, topAtm, atmType)

    out.append(f"{TAG} Atmospheric type:             {myProfile.getAtmosphereType()}")
    out.append(f"{TAG}   ")
    out.append(f"{TAG}   ")
    out.append(f"{TAG} Object myProfile built with the AtmProfile CONSTRUCTOR and the above entries")
    out.append(f"{TAG}   ")
    out.append(f"{TAG} Number of layers returned:  {myProfile.getNumLayer()}")
    out.append(f"{TAG} Layer parameters:  ")

    for i in range(myProfile.getNumLayer()):
        out.append(
            f"{TAG}  P: {f(myProfile.getLayerPressure(i).get('mb'))} mb"
            f" T: {f(myProfile.getLayerTemperature(i).get('K'))} K"
            f" Thickness: {f(myProfile.getLayerThickness(i).get('m'))} m"
            f" WaterVapor: {f(myProfile.getLayerWaterVaporMassDensity(i).get('kgm**-3'))} kg m-3"
            f" WaterVapor: {f(myProfile.getLayerWaterVaporNumberDensity(i).get('m**-3'))} m-3"
            f" CO: {f(myProfile.getLayerCO(i).get('m**-3'))} m-3"
            f" O3: {f(myProfile.getLayerO3(i).get('m**-3'))} m-3"
            f" N2O: {f(myProfile.getLayerN2O(i).get('m**-3'))} m-3")

    out.append(f"{TAG} First guess precipitable water vapor content: "
               f"{f(myProfile.getGroundWH2O().get('mm'))}mm")
    out.append(f"{TAG} (This value is estimated from the relative humidity at ground level "
               "and the water vapor scale height)")
    out.append(f"{TAG}   ")
    out.append(f"{TAG}   ")

    mySingleFreq = Frequency(850, "GHz")
    fghz = f(mySingleFreq.get("GHz"))
    out.append(f"{TAG} Example 1: Absorption profile for a single frequency: {fghz} GHz")
    out.append("  ")

    rip = RefractiveIndexProfile(mySingleFreq, myProfile)

    out.append(f"{TAG} Absorption Profile built from RefractiveIndexProfile CONSTRUCTOR. Summary of results:")
    out.append("")
    am = " GHz for 1.0 air mass: "
    out.append(f"{TAG} Total Dry Opacity at      {fghz}{am}{f(rip.getDryOpacity().get())}")
    out.append("")
    out.append(f"{TAG} Total Dry Cont Opacity at      {fghz}{am}{f(rip.getDryContOpacity().get())}")
    out.append(f"{TAG} Total O2 lines Opacity at      {fghz}{am}{f(rip.getO2LinesOpacity().get())}")
    out.append(f"{TAG} Total O3 lines Opacity at      {fghz}{am}{f(rip.getO3LinesOpacity().get())}")
    out.append(f"{TAG} Total CO lines Opacity at      {fghz}{am}{f(rip.getCOLinesOpacity().get())}")
    out.append(f"{TAG} Total N2O lines Opacity at      {fghz}{am}{f(rip.getN2OLinesOpacity().get())}")
    out.append("")
    out.append(f"{TAG} Total Wet Opacity at      {fghz}{am}{f(rip.getWetOpacity().get())}")
    out.append("")
    out.append(f"{TAG} Total H2O lines Opacity at      {fghz}{am}{f(rip.getH2OLinesOpacity().get())}")
    out.append(f"{TAG} Total H2O Cont Opacity at      {fghz}{am}{f(rip.getH2OContOpacity().get())}")
    out.append("")
    out.append("")
    out.append(f"{TAG} Total Dispersive PathLength at {fghz}{am}"
               f"{f(rip.getDispersiveH2OPathLength().get())} meters ")
    out.append(f"{TAG} Total Non-Dispersive PathLength at {fghz}{am}"
               f"{f(rip.getNonDispersiveH2OPathLength().get())} meters ")
    out.append(f"{TAG} Ratio Dispersive/Non-Dispersive PathLength at {fghz}{am}"
               f"{f(rip.getDispersiveH2OPathLength().get() / rip.getNonDispersiveH2OPathLength().get())}")
    out.append(f"{TAG} Total Dry PathLength at {fghz}{am}"
               f"{f(rip.getNonDispersiveDryPathLength().get())} meters ")
    out.append(f"{TAG} Total O2 lines PathLength at {fghz}{am}{f(rip.getO2LinesPathLength().get())} meters ")
    out.append(f"{TAG} Total O3 lines PathLength at {fghz}{am}{f(rip.getO3LinesPathLength().get())} meters ")
    out.append(f"{TAG} Total CO lines PathLength at {fghz}{am}{f(rip.getCOLinesPathLength().get())} meters ")
    out.append(f"{TAG} Total N2O lines PathLength at {fghz}{am}{f(rip.getN2OLinesPathLength().get())} meters ")
    out.append("")
    out.append("")
    out.append(f"{TAG} (your actual water vapor column is {f(myProfile.getGroundWH2O().get('mm'))} mm; "
               f"{f(rip.getGroundWH2O().get('mm'))} mm")
    out.append("")
    return out


def test_RefractiveIndexProfileTest():
    assert_matches_ref(run(), "RefractiveIndexProfileTest")
