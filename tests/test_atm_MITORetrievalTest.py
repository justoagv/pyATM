"""Python port of TelCalResults/Libraries/ATM/test/MITORetrievalTest.cpp."""
import re

from pyatm import (AtmProfile, Frequency, Humidity, Length, Pressure, RefractiveIndexProfile, SkyStatus,
                   SpectralGrid, Temperature)
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


def strtok_split(row: str, delim: str) -> list[str]:
    """Successive strtok(row, delim), strtok(NULL, delim), ... tokens."""
    return [t for t in re.split("[" + re.escape(delim) + "]", row) if t]


def run() -> list[str]:
    out = []
    atmType = 2  # MIDLATSUMMER
    T = Temperature(278.00, "K")       # Ground temperature
    P = Pressure(675.145, "mb")        # Ground Pressure
    H = Humidity(74.85, "%")           # Ground Relative Humidity (indication)
    Alt = Length(3480, "m")            # Altitude of the site
    WVL = Length(2.2, "km")            # Water vapor scale height
    TLR = -5.6                         # Tropospheric lapse rate (must be in K/km)
    topAtm = Length(48.0, "km")        # Upper atm. boundary for calculations
    Pstep = Pressure(5.0, "mb")        # Primary pressure step (5.0 mb)
    PstepFact = 1.1                    # Pressure step ratio between two consecutive layers

    myProfile = AtmProfile(Alt, P, T, TLR, H, WVL, Pstep, PstepFact, topAtm, atmType)

    out.append(f" WVRRetrievalTest: First guess precipitable water vapor content: "
               f"{f(myProfile.getGroundWH2O().get('mm'))} mm")
    out.append(" WVRRetrievalTest:  ")
    out.append(" WVRRetrievalTest: Reading TEBB data file...")

    v_frequency_tebbspec = []
    v_tebbspec = []
    fp = CFile(DATA_DIR / "MITO_AtmoPM_201007160400_ORIGINAL.dat")
    aRow = fp.fgets(STRLEN)
    tok = strtok_split(aRow, ",")
    v_frequency_tebbspec.append(Frequency(atof(tok[0]), "GHz"))
    v_tebbspec.append(Temperature(atof(tok[1]), "K"))
    aRow = fp.fgets(STRLEN) or aRow
    while fp.feof() == 0:
        if aRow.startswith(" "):
            tok = strtok_split(aRow, ",")
            v_frequency_tebbspec.append(Frequency(atof(tok[0]), "GHz"))
            v_tebbspec.append(Temperature(atof(tok[1]), "K"))
        aRow = fp.fgets(STRLEN) or aRow

    out.append(" WVRRetrievalTest: ...done!")

    # C++: RefractiveIndexProfile(v_frequency_tebbspec, myProfile) uses the implicit conversion
    # std::vector<Frequency> -> SpectralGrid (non-explicit SpectralGrid(const std::vector<Frequency>&)).
    MITO_RefractiveIndexProfile = RefractiveIndexProfile(SpectralGrid(v_frequency_tebbspec), myProfile)
    MITOAntenna = SkyStatus(MITO_RefractiveIndexProfile)

    spwId0 = []
    vv_tebb0 = []
    skycoupling0 = []
    tspill0 = []

    skycoupling0.append(1.0)
    spwId0.append(MITOAntenna.getNumSpectralWindow() - 1)
    tspill0.append(Temperature(278.00, "K"))
    vv_tebb0.append(v_tebbspec)
    sk = 1.0

    out.append(f"USER WH2O ={f(MITOAntenna.getUserWH2O().get('mm'))} mm")

    out.append(" MITORetrievalTest: 2nd method: "
               f"{f(MITOAntenna.WaterVaporRetrieval_fromTEBB(MITOAntenna.getNumSpectralWindow() - 1, v_tebbspec, sk, T).get('mm'))} mm ")

    out.append(f"Sigma Fit: {f(MITOAntenna.getSigmaFit(MITOAntenna.getNumSpectralWindow() - 1, v_tebbspec, sk, T).get('K'))} K")

    out.append(" WVRRetrievalTest: ...done 2!")

    out.append(f"USER WH2O ={f(MITOAntenna.getUserWH2O().get('mm'))} mm")
    return out


def test_MITORetrievalTest():
    assert_matches_ref(run(), "MITORetrievalTest")
