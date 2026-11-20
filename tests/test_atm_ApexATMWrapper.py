"""Python port of TelCalResults/Libraries/ATM/test/ApexATMWrapper.cpp.

The C++ test defines a wrapper class ``ApexATMWrapper`` on top of ATM and then uses it in main();
the class is ported here as a Python class with the same members and methods.
"""
from pyatm import (DSB, LSB, USB, Angle, AtmProfile, Frequency, Humidity, Length, Percent, Pressure,
                   RefractiveIndexProfile, SkyStatus, SpectralGrid, Temperature, WVRMeasurement,
                   WaterVaporRadiometer)
from refcompare import assert_matches_ref, cformat as f


class ApexATMWrapper:

    def __init__(self, out, temperature, pressure, humidity, lapseRate, siteAltitude, scaleHeight, topAtmHeight,
                 initialPressureStep, initialPressureStepFactor, atmType):
        self._out = out  # replaces std::cout
        self.apex_AtmProfile = None
        self.apex_SpectralGrid = None
        self.apex_RefractiveIndexProfile = None
        self.apex_SkyStatus = None
        self.wvr183ghz = None
        self.singleRadiometerData = None

        T = Temperature(temperature, "K")         # Ground temperature
        P = Pressure(pressure, "mb")              # Ground Pressure
        H = Humidity(humidity, "%")               # Ground Relative Humidity (indication)
        Alt = Length(siteAltitude, "m")           # Altitude of the site
        WVL = Length(scaleHeight, "km")           # Water vapor scale height
        TLR = lapseRate                           # Tropospheric lapse rate (must be in K/km)
        topAtm = Length(topAtmHeight, "km")       # Upper atm. boundary for calculations
        Pstep = Pressure(initialPressureStep, "mb")  # Primary pressure step (5.0 mb)
        PstepFact = initialPressureStepFactor     # Pressure step ratio between two consecutive layers

        self.apex_AtmProfile = AtmProfile(Alt, P, T, TLR, H, WVL, Pstep, PstepFact, topAtm, atmType)

    def setupRadiometerSpectralSetup(self):
        numchan3, refchan3 = 25, 13
        reffreq3, chansep3, intfreq3 = Frequency(182.01, "GHz"), Frequency(0.02, "GHz"), Frequency(1.30, "GHz")
        sidebandside3, sidebandtype3 = LSB, DSB
        apex_SpectralGrid = SpectralGrid(numchan3, refchan3, reffreq3, chansep3, intfreq3, sidebandside3, sidebandtype3)
        WVR_signalId = []

        WVR_signalId.append(0)  # Id of the 1st spectral window of the 1st pair (WVR channel 1)

        self.apex_RefractiveIndexProfile = RefractiveIndexProfile(apex_SpectralGrid, self.apex_AtmProfile)

        numchan4, refchan4 = 25, 13
        reffreq4, chansep4, intfreq4 = Frequency(179.11, "GHz"), Frequency(0.04, "GHz"), Frequency(4.20, "GHz")
        sidebandside4, sidebandtype4 = LSB, DSB

        WVR_signalId.append(self.apex_RefractiveIndexProfile.getNumSpectralWindow())  # WVR channel 2

        self.apex_RefractiveIndexProfile.addNewSpectralWindow(numchan4, refchan4, reffreq4, chansep4, intfreq4,
                                                              sidebandside4, sidebandtype4)

        numchan5, refchan5 = 25, 13
        reffreq5, chansep5, intfreq5 = Frequency(176.81, "GHz"), Frequency(0.04, "GHz"), Frequency(6.50, "GHz")
        sidebandside5, sidebandtype5 = LSB, DSB

        WVR_signalId.append(self.apex_RefractiveIndexProfile.getNumSpectralWindow())  # WVR channel 3

        self.apex_RefractiveIndexProfile.addNewSpectralWindow(numchan5, refchan5, reffreq5, chansep5, intfreq5,
                                                              sidebandside5, sidebandtype5)

        self.apex_SkyStatus = SkyStatus(self.apex_RefractiveIndexProfile)

        self._out.append("setting sky coupling")
        skycouplingastro = []
        signalgainastro = []
        for _ in range(1):
            skycouplingastro.append(1.0)
            signalgainastro.append(Percent(50.0, "%"))

        skycoupling183 = []
        signalgain183 = []
        skyCoupling_1stGuess = 0.935

        tspill = Temperature(273.576, "K")  # Spillover Temperature seen by the WVR

        for _ in range(len(WVR_signalId)):
            skycoupling183.append(skyCoupling_1stGuess)
            signalgain183.append(Percent(50.0, "%"))

        self.wvr183ghz = WaterVaporRadiometer(WVR_signalId, skycoupling183, signalgain183, tspill)

        self.apex_SkyStatus.setWaterVaporRadiometer(self.wvr183ghz)

    def calculateWVR(self, temperature, pressure, humidity, elevation, radiometerSkyTemp):
        calculatedWater = -99.9

        radiometerElevation = []
        v_tsky = []

        aaa = Angle(elevation, "deg")
        radiometerElevation.append(aaa)

        for i in range(3):
            v_tsky.append(Temperature(radiometerSkyTemp[i], "K"))

        singleRadiometerData = WVRMeasurement(aaa, v_tsky)

        tt = Temperature(temperature, "K")
        self.apex_SkyStatus.setBasicAtmosphericParameters(tt)
        ppp = Pressure(pressure, "mb")
        self.apex_SkyStatus.setBasicAtmosphericParameters(ppp)
        hhh = Humidity(humidity, "%")
        self.apex_SkyStatus.setBasicAtmosphericParameters(hhh)

        # std::vector<WVRMeasurement>::push_back stores copies of singleRadiometerData
        RadiometerData = []
        RadiometerData.append(WVRMeasurement(singleRadiometerData))
        RadiometerData.append(WVRMeasurement(singleRadiometerData))

        self.apex_SkyStatus.updateSkyCoupling_fromWVR(RadiometerData, 0, self.wvr183ghz)
        self.apex_SkyStatus.WaterVaporRetrieval_fromWVR(singleRadiometerData)

        wvr_retrieved = singleRadiometerData.getretrievedWaterVaporColumn()
        calculatedWater = wvr_retrieved.get("mm")

        self._out.append(f"Sigma Fit = {f(singleRadiometerData.getSigmaFit().get('K'))} K")

        return calculatedWater

    def setupAstroSpectralSetup(self, refFreq, refChan, freqIF, bandwidth, resolution, sideband, sidebandType):
        numchan = 25
        refchan = 13

        if (bandwidth / resolution) <= 1.0:  # for negative resolution ?
            numchan = int(abs(bandwidth / resolution + 0.5))  # C++ (unsigned int)(abs(double))
            refchan = int(numchan / 2.0 + 0.5)
        else:
            numchan = int(bandwidth / resolution + 0.5)
            refchan = int(refChan)

        reffreq = Frequency(refFreq, "GHz")
        chansep = Frequency(resolution, "GHz")
        intfreq = Frequency(freqIF, "GHz")

        apex_SpectralGrid = SpectralGrid(numchan, refchan, reffreq, chansep, intfreq, sideband, sidebandType)
        astro_signalId = []

        astro_signalId.append(0)

        self.apex_RefractiveIndexProfile = RefractiveIndexProfile(apex_SpectralGrid, self.apex_AtmProfile)
        self.apex_SkyStatus = SkyStatus(self.apex_RefractiveIndexProfile)

    def calculateWaterFromScalarAstro(self, temperature, pressure, humidity, airmass, skyTemp, gainImage, forwardEff,
                                      Tspill):
        calculatedWater = -99.9

        spillover_t = Temperature(Tspill, "K")

        # value between 0.0 and 1.0 for the signal band
        signalgain = Percent(1.0 - gainImage)

        v_tsky = Temperature(skyTemp, "K")

        tt = Temperature(temperature, "K")
        self.apex_SkyStatus.setBasicAtmosphericParameters(tt)
        ppp = Pressure(pressure, "mb")
        self.apex_SkyStatus.setBasicAtmosphericParameters(ppp)

        # As in C++, the double Tspill is implicitly converted to 'const Temperature &tspill' (Temperature(double), K).
        water_retrieved = self.apex_SkyStatus.WaterVaporRetrieval_fromTEBB(0, signalgain, v_tsky, airmass, forwardEff,
                                                                           Tspill)
        calculatedWater = water_retrieved.get("mm")

        return calculatedWater

    def calculateSignalOpacity(self, numberChannels):
        Id_signal = 0
        channelIndex = 0
        # As in C++, getWetOpacity(Id_signal, channelIndex) resolves to getWetOpacity(const Length&, unsigned int nc)
        # through the implicit conversion int -> Length(double).
        totalOpacity_signal = (self.apex_RefractiveIndexProfile.getWetOpacity(Id_signal, channelIndex)
                               + self.apex_RefractiveIndexProfile.getDryOpacity(Id_signal, channelIndex))
        return totalOpacity_signal.get()

    def calculateImageOpacity(self, numberChannels):
        Id_image = 1
        channelIndex = 0
        totalOpacity_image = (self.apex_RefractiveIndexProfile.getWetOpacity(Id_image, channelIndex)
                              + self.apex_RefractiveIndexProfile.getDryOpacity(Id_image, channelIndex))
        return totalOpacity_image.get()

    def calculateWaterFromVectorAstro(self, temperature, pressure, humidity, elevation, skyTemp):
        return 0


def run() -> list[str]:
    out = []
    lapseRate = -6.5
    siteAltitude = 5105
    scaleHeight = 3.0
    topAtmHeight = 48.0
    initialPressureStep = 5.0
    initialPressureStepFactor = 1.1
    atmType = 1
    radiometerSkyTemp = [0.0] * 3

    temperature = 270.22
    pressure = 557.13
    humidity = 9.31
    elevation = 47.39119977

    radiometerSkyTemp[0] = 214.689
    radiometerSkyTemp[1] = 83.316
    radiometerSkyTemp[2] = 50.029

    elevation = elevation + 7.8

    out.append("creating ApexATMWrapper for Radiometer")

    myRadiometerATM = ApexATMWrapper(out, temperature, pressure, humidity, lapseRate, siteAltitude, scaleHeight,
                                     topAtmHeight, initialPressureStep, initialPressureStepFactor, atmType)

    out.append("setupRadiometerSpectralSetup for radiometer")

    myRadiometerATM.setupRadiometerSpectralSetup()

    out.append("calculateWVR")

    water = myRadiometerATM.calculateWVR(temperature, pressure, humidity, elevation, radiometerSkyTemp)

    out.append(f"calculated water from ALMA ATM: {f(water)}")

    out.append("creating ApexATMWrapper for astro bands")

    temperature = 270.22
    pressure = 557.13
    humidity = 9.31

    myAstroATM = ApexATMWrapper(out, temperature, pressure, humidity, lapseRate, siteAltitude, scaleHeight,
                                topAtmHeight, initialPressureStep, initialPressureStepFactor, atmType)

    out.append("setupAstroSpectralSetup for astro bands")

    refFreq = 345.31440179
    refChan = 13
    freqIF = 6.0
    bandwidth = 1.
    resolution = bandwidth / 25.0
    sideband = USB
    sidebandType = DSB
    airmass = 1.35821286
    gainImage = 0.5
    forwardEff = 0.95
    Tspill = 273.576
    skyTemp = 54.61

    myAstroATM.setupAstroSpectralSetup(refFreq, refChan, freqIF, bandwidth, resolution, sideband, sidebandType)

    out.append("calculateWaterFromScalarAstro")

    water = myAstroATM.calculateWaterFromScalarAstro(temperature, pressure, humidity, airmass, skyTemp, gainImage,
                                                     forwardEff, Tspill)

    out.append(f"calculated water from ALMA ATM: {f(water)}")
    return out


def test_ApexATMWrapper():
    assert_matches_ref(run(), "ApexATMWrapper")
