# pyATM
A python wrapper around the ALMA Atmospheric Transmission Model (ATM)

`pip install` gives you:

* `pyatm`: pybind11 bindings for the complete public ATM C++ API (`AtmProfile`, `SpectralGrid`,
  `RefractiveIndexProfile`, `SkyStatus`, `WaterVaporRadiometer`, `WVRMeasurement`, the unit classes, ...).
* `pyatm.casa.atmosphere`: a drop-in for CASA's `casatools.atmosphere` tool.
* The ATM C++ headers and the shared library `libATM`, so C++ code can be compiled against them
  (via `pyatm-config`, CMake `find_package(pyatm)` or pkg-config).

The ATM sources in [cpp/ATM](cpp/ATM) are a copy of `TELCAL/TelCalResults/Libraries/ATM`; the TELCAL
commit they come from is recorded in `cpp/ATM/TELCAL_SOURCE`.

## Installation

```bash
pip install .                                          # C++ namespace telcal::atm (as in TelCal, default)
pip install . -C cmake.define.PYATM_NAMESPACE=atm      # C++ namespace atm (as in CASA)
PYATM_NAMESPACE=atm pip wheel .                        # same option, set through the environment
pip install ".[test,notebooks]"                        # with the test / notebook dependencies
```

You need a C++17 compiler. CMake, ninja, pybind11 and scikit-build-core are pulled in by pip.
The namespace only matters for C++ users; the Python module is the same in both cases
(`pyatm.CXX_NAMESPACE` tells you which one was built).

## Python usage

```python
import pyatm
from pyatm import AtmProfile, Frequency, Humidity, Length, Pressure, RefractiveIndexProfile, SkyStatus, SpectralGrid, Temperature

profile = AtmProfile(Length(5000, "m"), Pressure(560, "mb"), Temperature(270, "K"), -5.6,
                     Humidity(20, "%"), Length(2, "km"), Pressure(10, "mb"), 1.2, Length(48, "km"), 1)
sky = SkyStatus(RefractiveIndexProfile(SpectralGrid(64, 32, Frequency(230, "GHz"), Frequency(31.25, "MHz")), profile))
sky.setUserWH2O(Length(1.0, "mm"))
print(sky.getAverageTebbSky(0).get("K"), sky.getAverageWetOpacity(0).get())
```

The Python API mirrors the C++ one:

* Overloads, default arguments and static methods are kept. Units are passed as strings (`Length(1, "km")`) or
  as the unit enums (`Length.UnitKiloMeter`).
* `std::vector` maps to Python lists and numpy arrays. Arguments passed by non-const reference
  (e.g. `std::vector<WVRMeasurement>&` in `SkyStatus.WaterVaporRetrieval_fromWVR`) are written back
  into the list you pass.
* Every class can be copied: `X(other)`, `copy.copy`, `copy.deepcopy`.
* ATM errors are raised as `pyatm.AtmException`.
* Channel numbers are 0-based: `refFreq` is the frequency of channel `refChan`.

### CASA atmosphere tool

```python
from pyatm.casa import atmosphere, quantity

at = atmosphere()
at.initAtmProfile(altitude=quantity(5059, "m"), temperature="270 K", pressure=quantity(560, "mbar"), humidity=20)
at.initSpectralWindow(nbands=1, fCenter=quantity(230, "GHz"), fWidth=quantity(8, "GHz"), fRes=quantity(0.1, "GHz"))
n, tebb = at.getTebbSkySpec(spwid=0)       # tebb = {'value': numpy array, 'unit': 'K'}
```

The method names, defaults, units, messages and outputs follow CASA's current behaviour.
Methods that return values through output arguments in CASA return tuples here
(for example `getProfile()` and `getBasicAtmParms()`). Warnings go to the `pyatm.casa` logger.

## C++ usage

```bash
pyatm-config --cflags        # -I<include dir> [-DALMA_TELCAL]
pyatm-config --libs          # -L<lib dir> -Wl,-rpath,<lib dir> -lATM
pyatm-config --namespace     # telcal::atm or atm
g++ -std=c++17 $(pyatm-config --cflags) my.cpp $(pyatm-config --libs) -o my

# CMake:  find_package(pyatm REQUIRED)  ...  target_link_libraries(my PRIVATE pyatm::ATM)
cmake -Dpyatm_DIR=$(pyatm-config --cmakedir) ...

# pkg-config
PKG_CONFIG_PATH=$(pyatm-config --pkgconfigdir) pkg-config --cflags --libs pyatm
```

## Notebooks

In [notebooks](notebooks):

* [01_atm_library.ipynb](notebooks/01_atm_library.ipynb): what the ATM unit tests exercise. Covers units,
  profiles, spectral grids, opacities, sky brightness and WVR water-vapour retrieval.
* [02_telcal_calibrations.ipynb](notebooks/02_telcal_calibrations.ipynb): the ATM sequences of the TelCal
  WVR (`WVRScan`), Atmosphere (`AtmosphereScan`) and Sideband-ratio (`SideBandRatioScan`) engines.
* [03_casa_atmosphere.ipynb](notebooks/03_casa_atmosphere.ipynb): the CASA `atmosphere` tool.

## Tests

```bash
pip install ".[test]"
pytest -q tests
```

* `tests/test_atm_*.py` are Python ports of the active ATM unit tests (`TELCAL/.../ATM/test/TestList.lite`).
  Each one is compared number-by-number with the original `.ref` file, which is copied into `tests/atm/ref`.
* `test_bindings.py` checks binding details: units, copies, overload resolution and exceptions.
* `test_cpp_compile.py` compiles C++ against the installed headers/library, using both `pyatm-config` and CMake.
* `test_casa.py` checks the CASA tool against direct ATM calls.

## Updating ATM from TELCAL

```bash
tools/sync_from_telcal.sh [<TELCAL>/TelCalResults/Libraries/ATM]   # copy sources, headers, test refs and data
pip install libclang
python tools/generate_bindings.py                                   # regenerate src/bindings/atm_generated.cpp
pip install .
python tools/check_coverage.py <TELCAL>/TelCalResults/Libraries/ATM/test/*.cpp \
       <TELCAL>/TelCalResults/Engines/src/*Scan*.cpp                # every ATM call used there is bound
pytest -q tests
```

## Notes

* In an ACS/CASA shell, clear the environment first so the venv is not mixed with system packages:
  `env -u PYTHONPATH -u LD_LIBRARY_PATH pip install ...`
* `dPm` (pressure step factor) in the CASA `getBasicAtmParms` output is the value given to `initAtmProfile`,
  because ATM has no accessor for it.
* There is no implicit conversion from a list of `Frequency` to `SpectralGrid`; call `SpectralGrid([...])` explicitly.
* Messages that ATM writes to C++ `std::cout` go straight to the process stdout and are not captured by
  Python's `sys.stdout`.
