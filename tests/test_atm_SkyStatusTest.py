"""Python port of TelCalResults/Libraries/ATM/test/SkyStatusTest.cpp.

The C++ test writes everything to ``results.txt`` (the reference contains the file content).
The ``std::fixed`` / ``std::scientific`` / ``setprecision`` manipulators are sticky on the
stream, so after the layer table the remaining doubles are printed as ``%.5e``.
"""
from pyatm import (AtmProfile, Frequency, Humidity, Length, Pressure, RefractiveIndexProfile,
                   SkyStatus, SpectralGrid, Temperature)
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
    topAtm = Length(95.0, "km")
    Pstep = Pressure(5.0, "mb")

    out.append("! SkyStatusTest: BASIC ATMOSPHERIC PARAMETERS TO GENERATE REFERENCE ATMOSPHERIC PROFILE")
    out.append("! SkyStatusTest:   ")
    out.append(f"! SkyStatusTest: Ground temperature T:         {f(T.get())} K")
    out.append(f"! SkyStatusTest: Ground pressure P:            {f(P.get('mb'))} mb")
    out.append(f"! SkyStatusTest: Relative humidity rh:         {f(H.get('%'))} %")
    out.append(f"! SkyStatusTest: Scale height h0:              {f(WVL.get('km'))} km")
    out.append(f"! SkyStatusTest: Pressure step dp:             {f(Pstep.get('mb'))} mb")
    out.append(f"! SkyStatusTest: Altitude alti:                {f(Alt.get())} m")
    out.append(f"! SkyStatusTest: Attitude top atm profile atmh:{f(topAtm.get('km'))} km")
    out.append(f"! SkyStatusTest: Tropospherique lapse rate:    {f(TLR)} K/km")

    pressureStepFactor = 1.075
    myProfile = AtmProfile(Alt, P, T, TLR, H, WVL, Pstep, pressureStepFactor, topAtm, atmType)

    out.append("! SkyStatusTest: Object myProfile built with the AtmProfile CONSTRUCTOR and the above entries")
    out.append(f"! SkyStatusTest: Atmospheric type:             {myProfile.getAtmosphereType()}")
    out.append(f"! SkyStatusTest: Number of layers returned:  {myProfile.getNumLayer()}")
    out.append("! SkyStatusTest: Layer parameters:  ")

    out.append(f"! SkyStatusTest: size of Temperature Profile: {len(myProfile.getTemperatureProfile())}")
    out.append("!   H0_layer  H1_layer  Layer Thickness   Pressure    Temperature             WaterVapor             O3           CO          N2O          HCl          HCN  ")
    out.append("!      (m)       (m)          (m)           (mb)          (K)            kg m^-3        m^-3        m^-3         m^-3         m^-3         m^-3         m^-3 ")
    alt0 = Alt.get()
    alt1 = alt0
    for i in range(myProfile.getNumLayer()):
        alt1 = alt0 + myProfile.getLayerThickness(i).get("m")
        out.append(
            "!"
            f"{alt0:11.3f}"
            f"{alt1:11.3f}"
            f"{myProfile.getLayerThickness(i).get('m'):11.3f}      "
            f"{myProfile.getLayerPressure(i).get('mb'):9.3f}    "
            f"{myProfile.getLayerTemperature(i).get('K'):9.3f}      "
            f"{myProfile.getLayerWaterVaporMassDensity(i).get('kgm**-3'):13.5e}"
            f"{myProfile.getLayerWaterVaporNumberDensity(i).get('m**-3'):13.5e}"
            f"{myProfile.getLayerO3(i).get('m**-3'):13.5e}"
            f"{myProfile.getLayerCO(i).get('m**-3'):13.5e}"
            f"{myProfile.getLayerN2O(i).get('m**-3'):13.5e}"
            f"{myProfile.getLayerHCl(i).get('m**-3'):13.5e}"
            f"{myProfile.getLayerHCN(i).get('m**-3'):13.5e}")
        alt0 = alt1

    # stream is now in scientific mode with precision 5 (sticky manipulators)
    out.append(f"! SkyStatusTest: First guess precipitable water vapor content: {myProfile.getGroundWH2O().get('mm'):.5e}mm")
    out.append("! SkyStatusTest: (This value is estimated from the relative humidity at ground level and the water vapor scale height)")
    out.append("! SkyStatusTest:   ")

    out.append("! SkyStatusTest:    TEST FOR ONE SPECTRAL WINDOW WITH SEVERAL CHANNELS     ")
    out.append("! SkyStatusTest:    =====================================================  ")
    out.append("! SkyStatusTest:  ")

    numchan = 10000
    refchan = 5001
    reffreq = Frequency(500.10, "GHz")
    chansep = Frequency(0.1, "GHz")

    spectral_band = SpectralGrid(numchan, refchan, reffreq, chansep)
    refractive_index_spectrum = RefractiveIndexProfile(spectral_band, myProfile)
    sky_spectrum = SkyStatus(refractive_index_spectrum)

    sky_spectrum.setAirMass(1.0)
    sky_spectrum.setUserWH2O(0.33, "mm")

    out.append(f"! SkyStatusTest: water vapor column: {sky_spectrum.getUserWH2O().get('mm'):.5e} mm")
    out.append(f"! SkyStatusTest: Air mass          : {sky_spectrum.getAirMass():.5e}")
    out.append("! ")

    out.append("! Frequency         Sky        D_Sky_Trm     T_EBB     < -------------------------------------------------------------------------------------- Total opacities along the atmospheric path ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------->")
    out.append("!   (GHz)       Transmission  (D_nu=100Hz)    (K)       Wet_CIA    Dry_CIA     H2O Line    HH16O_Lin  HH16OV2Lin  HH17O_Lin    HH18O_Lin    HDO_Lin    O2_Lines   16O16O_Lin   16O2Vib_L  16O17O_Lin  16O18O_Lin   O3_Lines    16O3_Lin   16O3_V1_L   16O3_V2_L   16O3_V3_L   16O16O17O   16O16O18O   16O17O16O   16O18O16O       N2O         CO          HCl         HCN  ")

    numchanDF = 3
    refchanDF = 2
    chansepDF = Frequency(0.0000005, "GHz")

    s = sky_spectrum
    for i in range(1, s.getNumChan(0) - 1):
        reffreqDF = s.getChanFreq(i)
        spectral_bandDF = SpectralGrid(numchanDF, refchanDF, reffreqDF, chansepDF)
        refractive_index_spectrumDF = RefractiveIndexProfile(spectral_bandDF, myProfile)
        sky_spectrumDF = SkyStatus(refractive_index_spectrumDF)
        delta_right = sky_spectrumDF.getSkyTransmission(2) - sky_spectrumDF.getSkyTransmission(1)
        delta_left = sky_spectrumDF.getSkyTransmission(0) - sky_spectrumDF.getSkyTransmission(1)
        if abs(delta_right) > abs(delta_left):
            TransmissionVariation = delta_right
        else:
            TransmissionVariation = delta_left

        opacities = (
            s.getH2OContOpacity(i), s.getDryContOpacity(i), s.getH2OLinesOpacity(i),
            s.getHH16OLinesOpacity(i), s.getHH16OV2LinesOpacity(i), s.getHH17OLinesOpacity(i),
            s.getHH18OLinesOpacity(i), s.getHDOLinesOpacity(i), s.getO2LinesOpacity(i),
            s.get16O16OLinesOpacity(i), s.get16O16OVIBLinesOpacity(i), s.get16O17OLinesOpacity(i),
            s.get16O18OLinesOpacity(i), s.getO3LinesOpacity(i), s.get16O16O16OLinesOpacity(i),
            s.get16O16O16OV1LinesOpacity(i), s.get16O16O16OV2LinesOpacity(i),
            s.get16O16O16OV3LinesOpacity(i), s.get16O16O17OLinesOpacity(i),
            s.get16O16O18OLinesOpacity(i), s.get16O17O16OLinesOpacity(i),
            s.get16O18O16OLinesOpacity(i), s.getN2OLinesOpacity(i), s.getCOLinesOpacity(i),
            s.getHClLinesOpacity(i), s.getHCNLinesOpacity(i))
        out.append(
            f"{s.getChanFreq(i).get('GHz'):13.7f}"
            f"{s.getSkyTransmission(i):14.8f}"
            f"{TransmissionVariation:14.8f}"
            f"{s.getTebbSky(i).get('K'):10.4f}"
            + "".join(f"{o.get():12.6f}" for o in opacities))
    return out


def test_SkyStatusTest():
    assert_matches_ref(run(), "SkyStatusTest")
