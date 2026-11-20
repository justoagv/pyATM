"""Python port of TelCalResults/Libraries/ATM/test/AtmBasicTest.cpp.

The C++ test also writes ``path.dat``; AtmBasic.sh does not print it, so its content is not part
of the reference. It is written to pytest's ``tmp_path``.
"""
from pathlib import Path

from pyatm import (AtmProfile, Frequency, Humidity, Length, Pressure, RefractiveIndexProfile,
                   SkyStatus, SpectralGrid, Temperature)
from refcompare import assert_matches_ref, cformat as f


def run(outdir: Path) -> list[str]:
    out = []
    atmType = 1
    T = Temperature(273., "K")
    P = Pressure(55000., "Pa")
    H = Humidity(8., "%")
    Alt = Length(5000, "m")
    WVL = Length(3.0, "km")
    TLR = -6.5
    topAtm = Length(48.0, "km")
    Pstep = Pressure(10.0, "mb")
    PstepFact = 1.2

    myProfile = AtmProfile(Alt, P, T, TLR, H, WVL, Pstep, PstepFact, topAtm, atmType)

    out.append("BASIC ATMOSPHERIC PARAMETERS TO GENERATE REFERENCE ATMOSPHERIC PROFILE")
    out.append("Ground temperature T:          %.1f K " % T.get())
    out.append("Ground pressure P:             %.0f Pa " % P.get("Pa"))
    out.append("Relative humidity rh:          %.0f percent " % H.get("%"))
    out.append("Scale height h0:               %.0f m " % WVL.get("m"))
    out.append("Pressure step dp:              %.0f Pa " % Pstep.get("Pa"))
    out.append("Altitude alti:                 %.0f m " % Alt.get())
    out.append("Altitude top atm profile atmh: %.0f m " % topAtm.get("m"))
    out.append("Pressure step factordp1:       %.2f " % PstepFact)
    out.append("Tropospherique lapse rate:     %.1f K/km " % TLR)

    out.append(f"Number of layers :{myProfile.getNumLayer()}")
    out.append(f"First guess precipitable water vapor content: {f(myProfile.getGroundWH2O().get('mm'))} mm")

    refFreqAstro = 86.3 * 1.e9
    bandWidthAstro = 2. * 1.e9
    chanWidthAstro = 0.1 * 1e9
    numChanAstro = int(bandWidthAstro / chanWidthAstro)
    refChanAstro = numChanAstro // 2 + 1

    spGrid = SpectralGrid(numChanAstro, refChanAstro, Frequency(refFreqAstro), Frequency(chanWidthAstro))

    out.append("-----------------------------------------------")
    for j in range(spGrid.getNumSpectralWindow()):
        out.append(f"Spectral Window {j}"
                   f" Central Frequency: {f(spGrid.getChanFreq(j, spGrid.getNumChan(j) // 2).get('GHz'))} GHz, "
                   f" Freq. Resolution: {f(spGrid.getChanSep(j).get('MHz'))} MHz, "
                   f" LO frequency: {f(spGrid.getLoFrequency(j) / 1.e9)} GHz, "
                   f" Num. of channels: {spGrid.getNumChan(j)}")
    out.append("-----------------------------------------------")

    out.append("Create SkyStatus object")
    absProfile = RefractiveIndexProfile(spGrid, myProfile)

    skyStatus = SkyStatus(absProfile)
    skyStatus.setAirMass(1.)
    skyStatus.setUserWH2O(myProfile.getGroundWH2O())

    out.append("end")

    deltaPressure = 100.
    startPressure = 49000.
    endPressure = 61000.
    numPressure = int((endPressure - startPressure) / deltaPressure)

    spwid = spGrid.getNumSpectralWindow() - 1

    with open(outdir / "path.dat", "w") as resultFile:
        resultFile.write("! Pressure TotalPath H2OPathLength DispersiveDryPathLength NonDispersiveDryPathLength\n")
        for i in range(numPressure):
            skyStatus.setBasicAtmosphericParameters(Pressure(startPressure + i * deltaPressure, "Pa"))

            out.append(f"Number of layers :{skyStatus.getNumLayer()}")
            out.append(f"First guess precipitable water vapor content: {f(skyStatus.getGroundWH2O().get('mm'))} mm")
            out.append(f"Ground Pressure: {f(skyStatus.getGroundPressure().get('Pa'))} Pa")
            out.append(f"Ground Temperature: {f(skyStatus.getGroundTemperature().get('K'))} K")
            for ii in range(skyStatus.getNumLayer()):
                out.append(f"Pressure in Layer {ii} = {f(skyStatus.getLayerPressure(ii).get('Pa'))} Pa "
                           f"Temperature: {f(skyStatus.getLayerTemperature(ii).get('K'))} K ")

            path = (skyStatus.getAverageH2OPathLength(spwid)
                    + skyStatus.getAverageDispersiveDryPathLength(spwid)
                    + skyStatus.getAverageNonDispersiveDryPathLength(spwid))

            resultFile.write(f"{f(startPressure + i * deltaPressure)} "
                             f"{f(path.get())} "
                             f"{f(skyStatus.getAverageH2OPathLength(spwid).get())} "
                             f"{f(skyStatus.getAverageDispersiveDryPathLength(spwid).get())} "
                             f"{f(skyStatus.getAverageNonDispersiveDryPathLength(spwid).get())}\n")
    return out


def test_AtmBasicTest(tmp_path):
    assert_matches_ref(run(tmp_path), "AtmBasicTest")
    assert len((tmp_path / "path.dat").read_text().splitlines()) == 1 + 120
