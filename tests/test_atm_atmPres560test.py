"""Python port of TelCalResults/Libraries/ATM/test/atmPres560test.cpp."""
import pyatm
from pyatm import AtmProfile, Humidity, Length, Pressure, Temperature
from refcompare import assert_matches_ref, cformat as f


def run() -> list[str]:
    out = []
    out.append("start setting quantities")
    Alt = Length(5059., "m")
    P = Pressure(554.5, "mb")
    T = Temperature(269.0, "K")
    TLR = -5.6
    H = Humidity(7.0, "%")
    WVL = Length(2.0, "km")
    Pstep = Pressure(10.0, "mb")
    PstepFact = 1.2
    topAtm = Length(48000., "m")
    atmType = 3
    out.append("end setting quantities")

    ATM_VERSION = pyatm.ATM_VERSION  # macro of ATMVersion.h
    out.append("Testing aatm version: ")
    out.append(f" aatm library version: {pyatm.getVersion()}")
    out.append(f" aatm header version: {ATM_VERSION}")
    if pyatm.getVersion() == ATM_VERSION:
        out.append("Version matches OK!")
    else:
        out.append("***ERROR*** Version mismatch!!!")

    out.append("Start creating atm profile")
    pAtmProfile = AtmProfile(Alt, P, T, TLR, H, WVL, Pstep, PstepFact, topAtm, atmType)
    out.append("Finish creating atm profile")

    out.append("BASIC ATMOSPHERIC PARAMETERS TO GENERATE REFERENCE ATMOSPHERIC PROFILE")
    out.append("  ")
    out.append(f"Ground temperature T:         {f(T.get())} K")
    out.append(f"Ground pressure P:            {f(P.get('mb'))} mb")
    out.append(f"Relative humidity rh:         {f(H.get('%'))} %")
    out.append(f"Scale height h0:              {f(WVL.get('km'))} km")
    out.append(f"Pressure step dp:             {f(Pstep.get('mb'))} mb")
    out.append(f"Altitude alti:                {f(Alt.get())} m")
    out.append(f"Attitude top atm profile atmh:{f(topAtm.get('km'))} km")
    out.append(f"Pressure step factordp1:      {f(PstepFact)} ")
    out.append(f"Tropospheric lapse rate:    {f(TLR)} K/km")
    out.append(f"Atmosphere Type:    {pAtmProfile.getAtmosphereType()}")

    out.append(f"Number of layers created: {pAtmProfile.getNumLayer()}")
    return out


def test_atmPres560test():
    out = run()
    assert_matches_ref(out, "atmPres560test")
    assert "Version matches OK!" in out
    assert "Atmosphere Type:    MIDLATWINTER" in out
