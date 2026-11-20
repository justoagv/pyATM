"""Python port of TelCalResults/Libraries/ATM/test/atm651.cpp.

The C++ test also writes ``atm651.dat``; atm651 is run directly by TAT and the file is not printed,
so its content is not part of the reference. It is written to pytest's ``tmp_path``.
"""
import math
from pathlib import Path

from pyatm import (AtmProfile, Frequency, Humidity, Length, Pressure, RefractiveIndexProfile,
                   SkyStatus, SpectralGrid, Temperature)
from refcompare import assert_matches_ref, cformat as f


def run(outdir: Path) -> list[str]:
    out = []
    atmType = 3
    T = Temperature(269., "K")
    P = Pressure(55450., "Pa")
    H = Humidity(7., "%")
    Alt = Length(5059, "m")
    WVL = Length(2.0, "km")
    TLR = -5.6
    topAtm = Length(48.0, "km")
    Pstep = Pressure(10.0, "mb")
    PstepFact = 1.2

    myProfile = AtmProfile(Alt, P, T, TLR, H, WVL, Pstep, PstepFact, topAtm, atmType)

    out.append("BASIC ATMOSPHERIC PARAMETERS TO GENERATE REFERENCE ATMOSPHERIC PROFILE")
    out.append("Ground temperature T:          %.1f K " % T.get())
    out.append("Ground pressure P:             %.0f Pa " % P.get("Pa"))
    out.append("Relative humidity rh:          %.0f percent " % H.get("%"))
    out.append("Scale height h0:               %.0f m " % WVL.get("m"))
    out.append("Pressure step dp:              %.0f mbar " % Pstep.get("mbar"))
    out.append("Altitude alti:                 %.0f m " % Alt.get())
    out.append("Altitude top atm profile atmh: %.0f m " % topAtm.get("m"))
    out.append("Pressure step factordp1:       %.2f " % PstepFact)
    out.append("Tropospherique lapse rate:     %.1f K/km " % TLR)

    out.append(f"Number of layers :{myProfile.getNumLayer()}")
    out.append(f"First guess precipitable water vapor content: {f(myProfile.getGroundWH2O().get('mm'))} mm")

    refFreqAstro = 650.75 * 1.e9
    chanWidthAstro = 0.002 * 1e9
    numChanAstro = 1500
    refChanAstro = numChanAstro // 2 + 1

    spGrid = SpectralGrid(numChanAstro, refChanAstro, Frequency(refFreqAstro), Frequency(chanWidthAstro))

    out.append("-----------------------------------------------")
    for j in range(spGrid.getNumSpectralWindow()):
        out.append(f"Spectral Window {j}"
                   f" Reference Frequency: {f(spGrid.getRefFreq(j).get('GHz'))} GHz, "
                   f" Reference Channel: {spGrid.getRefChan(j)}"
                   f" Freq. Resolution: {f(spGrid.getChanSep(j).get('MHz'))} MHz, "
                   f" LO frequency: {f(spGrid.getLoFrequency(j) / 1.e9)} GHz, "
                   f" Num. of channels: {spGrid.getNumChan(j)}")
        out.append(f" {f(spGrid.getChanFreq(j, 0).get())}"
                   f" {f(spGrid.getChanFreq(j, numChanAstro - 1).get())}")
    out.append("-----------------------------------------------")

    out.append("Create SkyStatus object")
    absProfile = RefractiveIndexProfile(spGrid, myProfile)

    skyStatus = SkyStatus(absProfile)
    skyStatus.setAirMass(1.)
    skyStatus.setUserWH2O(myProfile.getGroundWH2O())

    filename = "atm651.dat"
    spwid = 0
    with open(outdir / filename, "w") as resultFile:
        for i in range(numChanAstro):
            dryOpa = skyStatus.getDryOpacity(spwid, i).get()
            wetOpa = skyStatus.getWetOpacity(spwid, i).get()
            resultFile.write(f"{f(spGrid.getChanFreq(spwid, i).get())} {f(math.exp(-wetOpa - dryOpa))} "
                             f"{f(math.exp(-wetOpa))} {f(math.exp(-dryOpa))}\n")

    out.append("")
    out.append(f"Transmission from {f(spGrid.getChanFreq(spwid, 0).get())}Ghz to "
               f"{f(spGrid.getChanFreq(spwid, numChanAstro - 1).get())}Ghz stored in file {filename}")
    return out


def test_atm651(tmp_path):
    assert_matches_ref(run(tmp_path), "atm651")
    assert len((tmp_path / "atm651.dat").read_text().splitlines()) == 1500
