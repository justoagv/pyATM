"""Python port of TelCalResults/Libraries/ATM/test/AbInitioTest.cpp."""
import re

from pyatm import (Angle, AtmProfile, DSB, Frequency, Humidity, LSB, Length, Percent, Pressure,
                   RefractiveIndexProfile, SkyStatus, SpectralGrid, Temperature, WVRMeasurement,
                   WaterVaporRadiometer)
from refcompare import DATA_DIR, assert_matches_ref, cformat as f

STRLEN = 40  # Max length of a row in a tpoint file
_ATOF = re.compile(r"\s*([-+]?(?:\d+\.?\d*|\.\d+)(?:[eE][-+]?\d+)?)")


def atof(s: str) -> float:
    m = _ATOF.match(s)
    return float(m.group(1)) if m else 0.0


class CFile:
    """Minimal emulation of C stdio fgets/feof on a text file."""

    def __init__(self, path):
        self.data = path.read_bytes().decode("latin-1")
        self.pos = 0
        self.eof = False

    def fgets(self, n: int):
        if self.pos >= len(self.data):
            self.eof = True
            return None
        limit = n - 1
        end = self.data.find("\n", self.pos, self.pos + limit)
        if end != -1:
            row = self.data[self.pos:end + 1]
        else:
            row = self.data[self.pos:self.pos + limit]
            if len(row) < limit:
                self.eof = True
        self.pos += len(row)
        return row

    def feof(self) -> int:
        return int(self.eof)


class Strtok:
    """Emulation of strtok(row, delim) followed by strtok(NULL, delim) calls."""

    def __init__(self, row: str):
        self.s = row
        self.pos = 0

    def __call__(self, delim: str):
        n = len(self.s)
        while self.pos < n and self.s[self.pos] in delim:
            self.pos += 1
        if self.pos >= n:
            return None
        start = self.pos
        while self.pos < n and self.s[self.pos] not in delim:
            self.pos += 1
        token = self.s[start:self.pos]
        if self.pos < n:
            self.pos += 1  # the delimiter is replaced by '\0'
        return token


def _observables(out, sky, astro_band):
    am = sky.getAirMass()
    out.append(f" AbInitioTest: Zenith water vapor column above Antenna 1: {f(sky.getUserWH2O().get('mm'))} mm")
    out.append(f" AbInitioTest: Air Mass for Antenna 1: {f(sky.getAirMass())}")
    out.append(f" AbInitioTest: AVERAGE TEBB={f(sky.getAverageTebbSky(astro_band).get('K'))} K")
    out.append(" AbInitioTest: TEBB DERIVATIVE="
               f"{f(sky.getAverageTebbSky(astro_band, Length(sky.getUserWH2O().get('mm') + 0.001, 'mm')).get('K') - sky.getAverageTebbSky(astro_band).get('K'))}"
               " K/(micron H2O)")
    out.append(f" AbInitioTest: AVERAGE WET OPACITY ALONG LINE OF SIGHT={f(sky.getAverageWetOpacity(astro_band).get('np') * am)} np")
    out.append(f" AbInitioTest:        AVERAGE H2O Lines OPACITY ALONG LINE OF SIGHT={f(sky.getAverageH2OLinesOpacity(astro_band).get('np') * am)} np")
    out.append(f" AbInitioTest:        AVERAGE H2O Cont. OPACITY ALONG LINE OF SIGHT={f(sky.getAverageH2OContOpacity(astro_band).get('np') * am)} np")
    out.append(f" AbInitioTest: AVERAGE DRY OPACITY ALONG LINE OF SIGHT={f(sky.getAverageDryOpacity(astro_band).get('np') * am)} np")
    out.append(f" AbInitioTest:        AVERAGE O2  Lines OPACITY ALONG LINE OF SIGHT={f(sky.getAverageO2LinesOpacity(astro_band).get('np') * am)} np")
    out.append(f" AbInitioTest:        AVERAGE Dry Cont. OPACITY ALONG LINE OF SIGHT={f(sky.getAverageDryContOpacity(astro_band).get('np') * am)} np")
    out.append(f" AbInitioTest:        AVERAGE O3  Lines OPACITY ALONG LINE OF SIGHT={f(sky.getAverageO3LinesOpacity(astro_band).get('np') * am)} np")
    out.append(f" AbInitioTest:        AVERAGE N2O Lines OPACITY ALONG LINE OF SIGHT={f(sky.getAverageN2OLinesOpacity(astro_band).get('np') * am)} np")
    out.append(f" AbInitioTest:        AVERAGE CO  Lines OPACITY ALONG LINE OF SIGHT={f(sky.getAverageCOLinesOpacity(astro_band).get('np') * am)} np")
    out.append(f" AbInitioTest: AVERAGE H2O DISPERSIVE PATHLENGTH ALONG LINE OF SIGHT={f(sky.getAverageDispersiveH2OPathLength(astro_band).get('microns') * am)} microns")
    out.append(f" AbInitioTest: AVERAGE H2O NON-DISPER PATHLENGTH ALONG LINE OF SIGHT={f(sky.getAverageNonDispersiveH2OPathLength(astro_band).get('microns') * am)} microns")
    out.append(f" AbInitioTest: AVERAGE H2O PATHLENGTH DERIVATIVE (ZENITH VALUE)={f(sky.getAverageH2OPathLengthDerivative(astro_band))} microns/micron_H2O")
    out.append(f" AbInitioTest: AVERAGE DRY DISPERSIVE PATHLENGTH ALONG LINE OF SIGHT={f(sky.getAverageDispersiveDryPathLength(astro_band).get('microns') * am)} microns")
    out.append(f" AbInitioTest:        AVERAGE O2  DISPERSIVE PATHLENGTH ALONG LINE OF SIGHT={f(sky.getAverageO2LinesPathLength(astro_band).get('microns') * am)} microns")
    out.append(f" AbInitioTest:        AVERAGE O3  DISPERSIVE PATHLENGTH ALONG LINE OF SIGHT={f(sky.getAverageO3LinesPathLength(astro_band).get('microns') * am)} microns")
    out.append(f" AbInitioTest:        AVERAGE N2O DISPERSIVE PATHLENGTH ALONG LINE OF SIGHT={f(sky.getAverageN2OLinesPathLength(astro_band).get('microns') * am)} microns")
    out.append(f" AbInitioTest:        AVERAGE CO  DISPERSIVE PATHLENGTH ALONG LINE OF SIGHT={f(sky.getAverageCOLinesPathLength(astro_band).get('microns') * am)} microns")
    out.append(" AbInitioTest: AVERAGE DRY DISPERSIVE PATHLENGTH Pr_DERIVATIVE  (ZENITH VALUE microns/mb)="
               f"{f(sky.getAverageDispersiveDryPathLength_GroundPressureDerivative(astro_band))} microns/mb")
    out.append(" AbInitioTest: AVERAGE DRY DISPERSIVE PATHLENGTH Temp_DERIVATIVE (ZENITH VALUE microns/K)="
               f"{f(sky.getAverageDispersiveDryPathLength_GroundTemperatureDerivative(astro_band))} microns/K")
    out.append(f" AbInitioTest: AVERAGE DRY NON-DISPER PATHLENGTH ALONG LINE OF SIGHT={f(sky.getAverageNonDispersiveDryPathLength(astro_band).get('microns') * am)} microns")
    out.append(" AbInitioTest: AVERAGE DRY NON-DISPER PATHLENGTH Pr_DERIVATIVE  (ZENITH VALUE microns/mb)="
               f"{f(sky.getAverageNonDispersiveDryPathLength_GroundPressureDerivative(astro_band))} microns/mb")
    out.append(" AbInitioTest: AVERAGE DRY NON-DISPER PATHLENGTH Temp_DERIVATIVE (ZENITH VALUE microns/K)="
               f"{f(sky.getAverageNonDispersiveDryPathLength_GroundTemperatureDerivative(astro_band))} microns/K")


def run() -> list[str]:
    out = []
    out.append(" AbInitioTest: STEP 1: CREATES REFERENCE ATMOSPHERIC PROFILE CORRESTONDING TO ATMOSPHERIC CONDITIONS AT THE GROUND:")
    out.append(" AbInitioTest: Atmosphere Type: TROPICAL")
    out.append(" AbInitioTest: Site Altitude: 4100 m above sea level")
    out.append(" AbInitioTest: Ground Temperature: 268.15 K")
    out.append(" AbInitioTest: Ground Pressure: 623.0 mb")
    out.append(" AbInitioTest: Relative Humidity at ground level: 11.3 % ")
    out.append(" AbInitioTest: Water vapor scale height: 2.2 km")
    out.append(" AbInitioTest: Tropospheric Temperature lapse rate: -5.6 K/km")
    out.append(" AbInitioTest: Top of the atmosphere for calculations: 48 km")
    out.append(" AbInitioTest: Primary pressure step: 10 mb (please check the above reference)")
    out.append(" AbInitioTest: Pressure step factor: 1.2 (please check the above reference)")

    atmType = 1  # TROPICAL
    T = Temperature(268.15, "K")     # Ground temperature
    P = Pressure(623.0, "mb")        # Ground Pressure
    H = Humidity(11.30, "%")         # Ground Relative Humidity (indication)
    Alt = Length(4100, "m")          # Altitude of the site
    WVL = Length(2.2, "km")          # Water vapor scale height
    TLR = -5.6                       # Tropospheric lapse rate (must be in K/km)
    topAtm = Length(48.0, "km")      # Upper atm. boundary for calculations
    Pstep = Pressure(5.0, "mb")      # Primary pressure step (5.0 mb)
    PstepFact = 1.1                  # Pressure step ratio between two consecutive layers

    myProfile = AtmProfile(Alt, P, T, TLR, H, WVL, Pstep, PstepFact, topAtm, atmType)

    out.append(f" AbInitioTest: First guess precipitable water vapor content: {f(myProfile.getGroundWH2O().get('mm'))} mm")
    out.append(" AbInitioTest:  ")

    out.append(" AbInitioTest: STEP 2: CREATES SpectralGrid and RefractiveIndexProfile OBJECTS CONTAINING")
    out.append(" AbInitioTest:       3 WATER VAPOR RADIOMETER CHANNELS + 1 ASTRONOMICAL BAND       ")
    out.append(" AbInitioTest:         (Negative frequency resolutions are used for image side bands)    ")

    WVR_signalId = []

    numchan1, refchan1 = 11, 6
    reffreq1, chansep1, intfreq1 = Frequency(182.11, "GHz"), Frequency(0.04, "GHz"), Frequency(1.20, "GHz")
    sidebandside1, sidebandtype1 = LSB, DSB
    alma_SpectralGrid = SpectralGrid(numchan1, refchan1, reffreq1, chansep1, intfreq1, sidebandside1, sidebandtype1)
    WVR_signalId.append(0)

    alma_RefractiveIndexProfile = RefractiveIndexProfile(alma_SpectralGrid, myProfile)

    numchan2, refchan2 = 11, 6
    reffreq2, chansep2, intfreq2 = Frequency(179.11, "GHz"), Frequency(0.09, "GHz"), Frequency(4.20, "GHz")
    sidebandside2, sidebandtype2 = LSB, DSB
    WVR_signalId.append(alma_RefractiveIndexProfile.getNumSpectralWindow())
    alma_RefractiveIndexProfile.addNewSpectralWindow(numchan2, refchan2, reffreq2, chansep2, intfreq2,
                                                     sidebandside2, sidebandtype2)

    numchan3, refchan3 = 11, 6
    reffreq3, chansep3, intfreq3 = Frequency(175.51, "GHz"), Frequency(0.10, "GHz"), Frequency(7.80, "GHz")
    sidebandside3, sidebandtype3 = LSB, DSB
    WVR_signalId.append(alma_RefractiveIndexProfile.getNumSpectralWindow())
    alma_RefractiveIndexProfile.addNewSpectralWindow(numchan3, refchan3, reffreq3, chansep3, intfreq3,
                                                     sidebandside3, sidebandtype3)

    mySingleFreq_astro2, chanSep_astro2 = Frequency(467.75, "GHz"), Frequency(0.050, "GHz")
    numChan_astro2, refChan_astro2 = 31, 16

    alma_RefractiveIndexProfile.addNewSpectralWindow(numChan_astro2, refChan_astro2, mySingleFreq_astro2, chanSep_astro2)

    astro_band = alma_RefractiveIndexProfile.getNumSpectralWindow() - 1

    for j in range(alma_RefractiveIndexProfile.getNumSpectralWindow()):
        out.append(f" AbInitioTest: Spectral Window {j}"
                   f" Central Frequency: {f(alma_RefractiveIndexProfile.getRefFreq(j).get('GHz'))} GHz, "
                   f" Freq. Resolution: {f(alma_RefractiveIndexProfile.getChanSep(j).get('MHz'))} MHz, "
                   f" Num. of channels: {alma_RefractiveIndexProfile.getNumChan(j)}")

    out.append(" AbInitioTest: Spectral windows associations:    ")
    for j in range(alma_RefractiveIndexProfile.getNumSpectralWindow()):
        if len(alma_RefractiveIndexProfile.getAssocSpwId(j)) == 1:
            out.append(f" AbInitioTest: Spectral Window {j} associated to spectral window: "
                       f"{alma_RefractiveIndexProfile.getAssocSpwId(j)[0]} (double band)")
        else:
            out.append(f" AbInitioTest: Spectral Window {j} associated to spectral window: {j} (single band)")
    out.append(" AbInitioTest:  ")

    out.append(" AbInitioTest: STEP 4: CREATES SkyStatus object and associates a WaterVaporRadiometer to it ")

    skyAntenna1 = SkyStatus(alma_RefractiveIndexProfile)
    skycoupling183 = []
    signalgain183 = []
    skyCoupling_1stGuess = 0.8
    tspill = Temperature(285.15, "K")
    for _ in range(len(WVR_signalId)):
        skycoupling183.append(skyCoupling_1stGuess)
        signalgain183.append(Percent(50.0, "%"))
    wvr183ghz = WaterVaporRadiometer(WVR_signalId, skycoupling183, signalgain183, tspill)
    skyAntenna1.setWaterVaporRadiometer(wvr183ghz)

    out.append(" AbInitioTest:  ")

    out.append(" AbInitioTest: WaterVaporRadiometer characteristics: ")
    for i in range(len(skyAntenna1.getWaterVaporRadiometer().getIdChannels())):
        Ids = skyAntenna1.getWaterVaporRadiometer().getIdChannels()[i]
        out.append(f" AbInitioTest: WVR Channel {i} SpectralGrid Id of Signal sideband: {Ids}"
                   f" / SpectralGrid Id of Image sideband: {skyAntenna1.getAssocSpwId(Ids)[0]}")
        out.append(f" AbInitioTest:  Sky Coupling: {f(skyAntenna1.getWaterVaporRadiometerSkyCoupling(i))}"
                   f" / Gain of Signal sideband: {f(skyAntenna1.getWaterVaporRadiometerSignalGain(i).get('%'))} %")

    out.append(" AbInitioTest:  ")
    out.append(" AbInitioTest: STEP 5: Reads a block of real WVRMeasurements taken at Mauna Kea on March 3, 2002 (local code)")

    RadiometerData = []
    time = []
    aaa = Angle()
    fp = CFile(DATA_DIR / "radiometer_data.dat")
    v_tsky = []
    numWVRChannels = 0
    aRow = fp.fgets(STRLEN)
    inilen = len(aRow)
    lacum = 0
    tok = Strtok(aRow)
    token = tok(",")
    time.append(atof(token))
    lacum = lacum + len(token) + 1
    token = tok(",")
    aaa = Angle(atof(token), "deg")
    lacum = lacum + len(token) + 1
    while lacum <= inilen:
        numWVRChannels += 1
        token = tok(",")
        v_tsky.append(Temperature(atof(token), "K"))
        lacum = lacum + len(token) + 1
    singleRadiometerData = WVRMeasurement(aaa, v_tsky)
    RadiometerData.append(singleRadiometerData)
    aRow = fp.fgets(STRLEN) or aRow
    while fp.feof() == 0:
        if aRow.startswith(" "):
            tok = Strtok(aRow)
            time.append(atof(tok(",")))
            aaa = Angle(atof(tok(",")), "deg")
            for j in range(numWVRChannels - 1):
                v_tsky[j] = Temperature(atof(tok(",")), "K")
            v_tsky[numWVRChannels - 1] = Temperature(atof(tok("\n")), "K")
        singleRadiometerData = WVRMeasurement(aaa, v_tsky)
        RadiometerData.append(singleRadiometerData)
        aRow = fp.fgets(STRLEN) or aRow

    out.append(f" AbInitioTest: Total number of WVR data: {len(RadiometerData)}")
    out.append(" AbInitioTest:  ")

    FirstMeasurementAnalyzed = 9300
    NumberofMeasurementsAnalyzed = 1  # 7
    NumberofMeasurementsforSkyCoupligRetrieval = 5

    out.append(f" AbInitioTest: STEP 6: Performing Water Vapor Retrieval over {NumberofMeasurementsAnalyzed}"
               f" WVR measurements starting at {FirstMeasurementAnalyzed // 3600} UT on March/3/2002 ")

    skyAntenna1.WaterVaporRetrieval_fromWVR(RadiometerData, FirstMeasurementAnalyzed,
                                            FirstMeasurementAnalyzed + NumberofMeasurementsAnalyzed)
    out.append(" AbInitioTest: The average Sigma of this ensemble of fits is: "
               f"{f(skyAntenna1.getWVRAverageSigmaTskyFit(RadiometerData, FirstMeasurementAnalyzed, FirstMeasurementAnalyzed + NumberofMeasurementsAnalyzed).get('K'))}"
               " K")
    out.append(f" AbInitioTest: User Water Vapor Column: {f(skyAntenna1.getUserWH2O().get('mm'))} mm")

    out.append(" AbInitioTest:  ")

    out.append(f" AbInitioTest: STEP 7: RETRIEVES THE BEST SKY COUPLING OF THE WVR CHANNELS USING DATA {FirstMeasurementAnalyzed}"
               f" TO {FirstMeasurementAnalyzed + NumberofMeasurementsforSkyCoupligRetrieval}")

    skyAntenna1.updateSkyCoupling_fromWVR(RadiometerData, FirstMeasurementAnalyzed,
                                          FirstMeasurementAnalyzed + NumberofMeasurementsforSkyCoupligRetrieval)

    out.append(" AbInitioTest: The best sky coupling is: ")
    for i in range(len(skyAntenna1.getWaterVaporRadiometer().getIdChannels())):
        out.append(f" AbInitioTest: WVR Channel {i}: {f(skyAntenna1.getWaterVaporRadiometerSkyCoupling(i))}: ")
    out.append(" AbInitioTest: For which the AverageSigmaTskyFit over those measurements is: "
               f"{f(skyAntenna1.getWVRAverageSigmaTskyFit(RadiometerData, FirstMeasurementAnalyzed, FirstMeasurementAnalyzed + NumberofMeasurementsforSkyCoupligRetrieval).get('K'))}"
               " K")
    out.append(f" AbInitioTest: User Water Vapor Column: {f(skyAntenna1.getUserWH2O().get('mm'))} mm")
    out.append(" AbInitioTest:")

    out.append(" AbInitioTest: STEP 8: DATA ANALYSIS USING THE NEW SKY COUPLING ")

    skyAntenna1.WaterVaporRetrieval_fromWVR(RadiometerData, FirstMeasurementAnalyzed,
                                            FirstMeasurementAnalyzed + NumberofMeasurementsAnalyzed)

    for i in range(FirstMeasurementAnalyzed, FirstMeasurementAnalyzed + NumberofMeasurementsAnalyzed):
        out.append(f" AbInitioTest: Data point {i} (UT time: {f(time[i] / 3600)} hours on 2002, March 3)")
        out.append(" AbInitioTest: Measured and fitted Sky Tebb's (in K): ")
        for j in range(len(RadiometerData[i].getmeasuredSkyBrightness())):
            out.append(f" AbInitioTest:   Channel {j}: {f(RadiometerData[i].getmeasuredSkyBrightness()[j].get('K'))}"
                       f"  {f(RadiometerData[i].getfittedSkyBrightness()[j].get('K'))}")
        out.append(" AbInitioTest:   Retrieved Zenith Water Vapor Column: "
                   f"{f(RadiometerData[i].getretrievedWaterVaporColumn().get('mm'))} mm /"
                   f" Sigma Fit: {f(RadiometerData[i].getSigmaFit().get('K'))} K")

        skyAntenna1.setUserWH2O(Length(2.0, "mm"))

        out.append(" AbInitioTest: Alternative method: Retrieved Zenith Water Vapor Column: "
                   f"{f(skyAntenna1.WaterVaporRetrieval_fromTEBB(WVR_signalId, Percent(50.0, '%'), RadiometerData[i].getmeasuredSkyBrightness(), RadiometerData[i].getAirMass(), skyAntenna1.getWaterVaporRadiometerSkyCoupling(0), Temperature(285.15, 'K')).get('mm'))}"
                   " mm")

    out.append(" AbInitioTest: ")
    out.append(f" AbInitioTest: STEP 9: ATMOSPHERE OBSERVABLES IN ASTRONOMICAL BAND (ID={astro_band})"
               f" CENTRAL FREQUENCY={f(skyAntenna1.getRefFreq(astro_band).get('GHz'))} GHz")

    out.append(" AbInitioTest: ")
    _observables(out, skyAntenna1, astro_band)

    skyAntenna1.setUserWH2O(0.5, "mm")
    skyAntenna1.setAirMass(2.0)
    out.append(" AbInitioTest: ")
    _observables(out, skyAntenna1, astro_band)

    return out


def test_AbInitioTest():
    assert_matches_ref(run(), "AbInitioTest")
