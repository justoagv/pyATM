// ---------------------------------------------------------------------------
// GENERATED FILE - DO NOT EDIT.  Produced by tools/generate_bindings.py from
// cpp/ATM/include/*.h; re-run the generator after syncing ATM from TELCAL.
// ---------------------------------------------------------------------------
#include "pyatm_bindings.h"

#include "ATMAngle.h"
#include "ATMCommon.h"
#include "ATMConstants.h"
#include "ATMEnumerations.h"
#include "ATMError.h"
#include "ATMException.h"
#include "ATMFrequency.h"
#include "ATMHumidity.h"
#include "ATMInverseLength.h"
#include "ATMLength.h"
#include "ATMMassDensity.h"
#include "ATMNumberDensity.h"
#include "ATMOpacity.h"
#include "ATMPercent.h"
#include "ATMPressure.h"
#include "ATMProfile.h"
#include "ATMRefractiveIndex.h"
#include "ATMRefractiveIndexProfile.h"
#include "ATMSkyStatus.h"
#include "ATMSpectralGrid.h"
#include "ATMTemperature.h"
#include "ATMVersion.h"
#include "ATMWVRMeasurement.h"
#include "ATMWaterVaporRadiometer.h"

namespace py = pybind11;
using namespace ATM_NAMESPACE;
using std::string;
using std::vector;

void pyatm_register_generated(py::module_ &m)
{
  py::enum_<SidebandSide>(m, "SidebandSide", R"doc(Defines the side of a sideband.

 Heterodyne receivers have two sidebands, a lower and an upper sideband. On the
 other hand the detectors do not have sidebands. The Science Data Model assign
 one spectral window per sideband. Hence, with detectors, there is a single
 spectral window. SidebandSide differentiates between these various cases.<br>

 The codes have the following meaning:
   <ul>
    <li> 0  No sideband (eg for a detector)
    <li> 1  Lower sideband (LSB)
    <li> 2  Upper sideband (USB)
   </ul>)doc")
      .value("NOSB", NOSB)
      .value("LSB", LSB)
      .value("USB", USB)
      .export_values();
  py::enum_<SidebandType>(m, "SidebandType", R"doc(Defines the kind of sideband separations.

 With heterodyne receivers there are always two sidebands. In the
 interferometric case it is possible to separate these two sidebands.
 When there is no sideband separation two types are considered,
 single sideband (SSB) when the image sideband has been rejected
 and double sideband (DSB) when the siband gain ratio is about
 half half. In the case of DSB only one sideband is retained
 for the data because the other sideband has identical data.
 When modeling the atmospheric contribution both sidebands need to be
 considered because the contribution is not the same in the two
 sidebands. <br>

 The codes have the following meaning:
  <ul>
    <li> -1 No type (NOTYPE): type is not relevant with a SidebandSide equal to NOSB
    <li> 0  Double sidebands (DSB): Case with no sideband rejection
    <li> 1  Single sideband (SSB): Case with sideband rejection
    <li> 2  Two sideband (TWOSB): Case with sideband separation (only for interferometric modes)
   </ul>
 </ul>)doc")
      .value("NOTYPE", NOTYPE)
      .value("DSB", DSB)
      .value("SSB", SSB)
      .value("TWOSB", TWOSB)
      .export_values();
  py::enum_<typeAtm_t>(m, "typeAtm_t", R"doc(Defines the type of atmosphere



 The codes have the following meaning:
  <ul>
    <li> 1  Tropical (tropical)
    <li> 2  Mid-latitude Summer (midlatSummer)
    <li> 3  Mid-latitude Winter (midlatWinter)
    <li> 4  Sub-arctic Summer (subarcticSummer)
    <li> 5  Sub-arctic Winter (subarcticWinter)
    <li> 6  typeATM_end
   </ul>
 </ul>)doc")
      .value("tropical", tropical)
      .value("midlatSummer", midlatSummer)
      .value("midlatWinter", midlatWinter)
      .value("subarcticSummer", subarcticSummer)
      .value("subarcticWinter", subarcticWinter)
      .value("typeATM_end", typeATM_end)
      .export_values();
  py::enum_<ErrorLevel>(m, "ErrorLevel", R"doc(Definition of the sequence of error levels sorted by ascending severity.)doc")
      .value("NOERROR", NOERROR)
      .value("WARNING", WARNING)
      .value("MINOR", MINOR)
      .value("SERIOUS", SERIOUS)
      .value("FATAL", FATAL)
      .export_values();

  py::class_<Angle> cls_Angle(m, "Angle", R"doc(Defines a Class for those parameters being angles.

  Defines a Class for those physical parameters having units of angle. For
  example the Total Phase Delay can be expressed as an angle (but also as a length).)doc");
  py::enum_<Angle::Units>(cls_Angle, "Units", "")
      .value("UnitRadian", Angle::Units::UnitRadian)
      .value("UnitDegree", Angle::Units::UnitDegree)
      .value("NumAngleUnits", Angle::Units::NumAngleUnits)
      .export_values();
  py::class_<Error> cls_Error(m, "Error", R"doc(The Error class represents a list of exceptions that may happen when errors occur.
To every error is associated a severity level. There is at any time an acceptable level
of severity. If an error occurs at that level or a more severe level, an exception is thrown.
The critical level of severity below which errors are tolerated can be modified.)doc");
  py::class_<Frequency> cls_Frequency(m, "Frequency", R"doc(Defines a frequency value with units

  Objects of type Frequency has a value in Hz (International System Units). The
  class Frequency allows clients to instantiate or retrieve Frequency objects with
  values specified in any units within a restricted set of predefined units, namely
  in THz, GHz, MHz, kHz or Hz. Hence units are handled only at the interface.
  If the units is not specified at this interface it is assumed to be Hz.)doc");
  py::enum_<Frequency::Units>(cls_Frequency, "Units", "")
      .value("UnitHertz", Frequency::Units::UnitHertz)
      .value("UnitKiloHertz", Frequency::Units::UnitKiloHertz)
      .value("UnitMegaHertz", Frequency::Units::UnitMegaHertz)
      .value("UnitGigaHertz", Frequency::Units::UnitGigaHertz)
      .value("UnitTeraHertz", Frequency::Units::UnitTeraHertz)
      .value("NumFrequencyUnits", Frequency::Units::NumFrequencyUnits)
      .export_values();
  py::class_<Percent> cls_Percent(m, "Percent", R"doc(Defines a class for quantities that may be expressed in percent.

  This class is aimed at quantities that may be defined in percent. Default is proposed with no units
  (relative to one), and an alternative is considered for units in %.)doc");
  py::enum_<Percent::Units>(cls_Percent, "Units", "")
      .value("UnitPercent", Percent::Units::UnitPercent)
      .value("NumPercentUnits", Percent::Units::NumPercentUnits)
      .export_values();
  py::class_<InverseLength> cls_InverseLength(m, "InverseLength", R"doc(Class for those physical parameters having dimensions of Inverse Length [L^-1]

  This class is defined for those physical parameters that have units of Inverse Length, for example
  the absorption coefficients. Desfault units are m^-1 (International System).)doc");
  py::enum_<InverseLength::Units>(cls_InverseLength, "Units", "")
      .value("UnitInverseMeter", InverseLength::Units::UnitInverseMeter)
      .value("UnitInverseKiloMeter", InverseLength::Units::UnitInverseKiloMeter)
      .value("UnitInverseMilliMeter", InverseLength::Units::UnitInverseMilliMeter)
      .value("UnitInverseMicron", InverseLength::Units::UnitInverseMicron)
      .value("UnitInverseNanoMeter", InverseLength::Units::UnitInverseNanoMeter)
      .value("NumInverseLengthUnits", InverseLength::Units::NumInverseLengthUnits)
      .export_values();
  py::class_<Length> cls_Length(m, "Length", R"doc(Class for those physical parameters having dimensions of Length [L]

  This class is defined for those physical parameters that have units of Length, for example
  the water vapor scale height. Default units are m (International System).)doc");
  py::enum_<Length::Units>(cls_Length, "Units", "")
      .value("UnitKiloMeter", Length::Units::UnitKiloMeter)
      .value("UnitMeter", Length::Units::UnitMeter)
      .value("UnitMilliMeter", Length::Units::UnitMilliMeter)
      .value("UnitMicron", Length::Units::UnitMicron)
      .value("UnitMicrons", Length::Units::UnitMicrons)
      .value("UnitNanoMeter", Length::Units::UnitNanoMeter)
      .value("NumLengthUnits", Length::Units::NumLengthUnits)
      .export_values();
  py::class_<MassDensity> cls_MassDensity(m, "MassDensity", R"doc(Mass Density value with units

  This class defines physical parameters having units of Mass Density.
  For example, the profiles of minor gases, such as O3, are in mass density.
  Default is m**-3 (International System).)doc");
  py::enum_<MassDensity::Units>(cls_MassDensity, "Units", "")
      .value("UnitGramPerCubicCentiMeter", MassDensity::Units::UnitGramPerCubicCentiMeter)
      .value("UnitGramPerCubicMeter", MassDensity::Units::UnitGramPerCubicMeter)
      .value("UnitKiloGramPerCubicMeter", MassDensity::Units::UnitKiloGramPerCubicMeter)
      .value("NumMassDensityUnits", MassDensity::Units::NumMassDensityUnits)
      .export_values();
  py::class_<NumberDensity> cls_NumberDensity(m, "NumberDensity", R"doc(Number Density value with units

  This class defines physical parameters having units of Number Density.
  For example, the profiles of minor gases, such as O3, are in number density.
  Default is m**-3 (International System).)doc");
  py::enum_<NumberDensity::Units>(cls_NumberDensity, "Units", "")
      .value("UnitInverseCubicCentiMeter", NumberDensity::Units::UnitInverseCubicCentiMeter)
      .value("UnitInverseCubicMeter", NumberDensity::Units::UnitInverseCubicMeter)
      .value("NumNumberDensityUnits", NumberDensity::Units::NumNumberDensityUnits)
      .export_values();
  py::class_<Opacity> cls_Opacity(m, "Opacity", R"doc(Class for opacities [no dimensions]

  This class is defined for opacities.
  Default units are np (Transmission=exp(-opacity)).)doc");
  py::enum_<Opacity::Units>(cls_Opacity, "Units", "")
      .value("UnitDeciBel", Opacity::Units::UnitDeciBel)
      .value("UnitNeper", Opacity::Units::UnitNeper)
      .value("NumOpacityUnits", Opacity::Units::NumOpacityUnits)
      .export_values();
  py::class_<Pressure> cls_Pressure(m, "Pressure", R"doc(Defines pressure with units

  This class defines physical parameters having units of Pressure.
  Default is Pa (International System) but the ATM library uses mb (hPa).)doc");
  py::enum_<Pressure::Units>(cls_Pressure, "Units", "")
      .value("UnitPascal", Pressure::Units::UnitPascal)
      .value("UnitHectoPascal", Pressure::Units::UnitHectoPascal)
      .value("UnitBar", Pressure::Units::UnitBar)
      .value("UnitMilliBar", Pressure::Units::UnitMilliBar)
      .value("UnitAtmosphere", Pressure::Units::UnitAtmosphere)
      .value("NumPressureUnits", Pressure::Units::NumPressureUnits)
      .export_values();
  py::class_<Temperature> cls_Temperature(m, "Temperature", R"doc(Temperature value with units

  This class defines physical parameters having units of Temperature.
  For example, the Radiance can be converted into Brightness Temperature.
  Default is K (International System), also used by the ATM library.)doc");
  py::enum_<Temperature::Units>(cls_Temperature, "Units", "")
      .value("UnitKelvin", Temperature::Units::UnitKelvin)
      .value("UnitMilliKelvin", Temperature::Units::UnitMilliKelvin)
      .value("UnitCelsius", Temperature::Units::UnitCelsius)
      .value("UnitFahrenheit", Temperature::Units::UnitFahrenheit)
      .value("NumTemperatureUnits", Temperature::Units::NumTemperatureUnits)
      .export_values();
  py::class_<AtmProfile> cls_AtmProfile(m, "AtmProfile", R"doc(Class for an atmospheric profile object.

        An  atmospheric profile is composed of 4 quantities as a function of altitude z:
        - the layer thickness
        - the pressure P
        - the temperature T and
        - the gas densities for H2O, O3, CO, N2O, NO2, HCl, HCN, SO2.<br>

  This object is needed  for computing the absorption and
  phase coefficients, as well as for performing radiative transfer
  calculations (only layer thickness/T are needed).

  This class builds an atmospheric profile that can be used to
  calculate absorption and phase coefficients, as well as to
  perform forward and/or retrieval radiative transfer calculations.
  It is composed of a set of parameters needed to build a layer thickness/P/T/gas densities
  densities profile from simple parameters currently available at observatories
  (from weather stations for example) using functions from
  the ATM library. The set of input parameters consists of the
  pressure P, the temperature T and the relative humidity at the ground, the altitude of
  the site, the tropospheric temperature lapse rate,... The profile is built as:
  thickness of the considered atmospheric layers above the site, and mean
  P,T,H2O,O3,CO,N2O, NO2, HCl, HCN, SO2 in
  them. The total number of atmospheric layers in the particular profile
  is also available (a negative value indicates an error).<br>
  The zenith column  of water vapor can be calculated
  by simply integrating the H2O profile. $$ column\;\;H_{2}O\;\; (mm) =\sum_{layers} \Delta z \cdot [ H_{2}O ] $$)doc");
  py::class_<RefractiveIndex> cls_RefractiveIndex(m, "RefractiveIndex", R"doc(RefractiveIndex allows to extract absorption and Phase coefficient(s) at
 a given frequency and P/T/gas densities.

 \anchor definitions Definitions to intepret the outputs:
   - Phase and amplitude response of a plane wave propagating a distance $z$ at frequency $\nu$:
     $E(z)=e^{ikz(1+N)}E(0)$
   - $k=2\pi\nu/c$ is the <b>free space wave number</b>.
   - $N=(n-1)=(N_r+iN_i)$ is the <b>Refractivity</b> ($n$ is the <b>Refraction Index</b>). <br>
   - $N=N_{g1}+N_{g2}+N_{g3}+ ...$ ($gi$ are atmospheric gases or account for other mechanisms
     that modify the refractivity such as <br> collision-induced absorption by $O_2-N_2$, $N_2-N_2$,
     $O_2-O_2$, $O_2-H_2O$ or $N_2-H_2O$ pairs.
   - For a given gas $g$:
      -# $N_g=(N_{rg}+iN_{ig})$ is the <b>Refractivity</b> of that gas.
      -# $N_g/\rho_g$, where $\rho_g$ is the <b>number density</b> of gas $g$, is the <b>Specific Refractivity</b> of that gas.
      -# $2\pi\nu N_{rg}/c=\phi_g$ $(rad\cdot m^{-1})$ is the <b>Phase Dispersion Coefficient</b> of gas $g$
      -# $2\pi\nu N_{ig}/c=\kappa_g$ $(m^{-1})$ is the <b>Absorption Coefficient</b> of gas $g$
      -# $2\pi\nu N_{rg}/(c\rho_g)=\phi_g/\rho_{g}$ $(rad\cdot m^2)$ is the <b>Specific Phase Dispersion Coefficient</b> of gas $g$
      -# $2\pi\nu N_{ig}/(c\rho_g)=\kappa_g/\rho_{g}$ $(m^2)$ is the <b>Specific Absorption Coefficient</b> of gas $g$.
      -# $(2\pi\nu/c)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{-1},m^{-1})$ is the result of <b>getRefractivity</b> operators for gas $g$.
      -# $[2\pi\nu/(c\rho_g)]\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^2,m^2)$ is the result og <b>getSpecificRefractivity</b> operators for gas $g$.
   - Therefore in order to obtain Phase Dispersion and Absorption Coefficients:
 -# Absorption Coefficient ($m^{-1}$) = Imaginary part of the result of the <b>getRefractivity</b> operator.
      -# Phase Dispersion Coefficient ($rad\cdot m^{-1}$) = Real part of the result of the <b>getRefractivity</b> operator.
      -# Specific Absorption Coefficient ($m^2$) = Imaginary part of the result of the <b>getSpecificRefractivity</b> operator.
      -# Specific Phase Dispersion Coefficient ($rad\cdot m^2$) = Real part of the result of the <b>getSpecificRefractivity</b> operator.

   - <b>species $(g)$ codes: <b>
      -# $^{16}O^{16}O$
      -# $^{16}O^{16}O vib$
      -# $^{16}O^{18}O$
      -# $^{16}O^{17}O$
      -# $CO $
      -# $N_2O$
      -# $NO_2$
      -# $SO_2$
      -# $CNTH2O $
      -# $CNTDRY $
      -# $HH^{16}O $
      -# $HH^{16}O v2 $
      -# $HH^{18}O $
      -# $HH^{17}O  $
      -# $HDO$
      -# $^{16}O^{16}O^{16}O$
      -# $^{16}O^{16}O^{16}O v2$
      -# $^{16}O^{16}O^{16}O v1$
      -# $^{16}O^{16}O^{16}O v3 $
      -# $^{16}O^{16}O^{18}O   $
      -# $^{16}O^{16}O^{17}O   $
      -# $^{16}O^{18}O^{16}O  $
      -# $^{16}O^{17}O^{16}O $)doc");
  py::class_<SpectralGrid> cls_SpectralGrid(m, "SpectralGrid", R"doc(Spectral grid defined as a list of frequencies with basic complementary
         informations.

 This grid is composed by a set frequency channels (or pixels) which may or may not
 be at a regular interval. The grid is composed of one or more spectral windows.
 A spectral window is defined as a group of channels, this group having the following
 attributes:
 <ul>
 <li> a number of channels
 <li> a reference channel
 <li> the frequency for that reference channel
 <li> a channel separation (it is set to 0 if there is only one channel or when the
     channels are at irregular intervals.
 <li> the intermediate frequency (if NetSideband is greater than -1)
 To every spectral window is assigned an identifier (zero-based) which can be used
 when retrieving the parameters of a given window.<br>
 In case of spectral windows with regularily spaced channels this reference frequency
 can be associated to a position in channel number units.

 There are several different constructors which can be used to define a spectral
 window. One of these must be used to construct the first spectral window. Would
 more than a single spectral be necessary, they are appended with the add methods.
 When there are two sidebands, every of these corresponds to a single spectral window.
 Note that these two sidebands can be constructed using a single method if the intermediate
 frequency is an input parameter.
 \note The Alma Science Data Model (ASDM) spectral windows derive from spectral grids,
 with extra informations such as the channel width, the resolution the noise bandwidth
 etc...)doc");
  py::class_<RefractiveIndexProfile, AtmProfile, SpectralGrid> cls_RefractiveIndexProfile(m, "RefractiveIndexProfile", R"doc(Profile of the absorption and Phase coefficient(s) at given frequency(ies) for an
  atmospheric profile (P/T/gas densities).

  Using the ATM library the vertical profile of the absorption
  coefficient corresponding to an atmospheric P/T/gas profile are build
  The absorption coefficient in each layer can be used
  later for radiative transfer purposes. The atmospheric P/T/gas profile is inherited
  from an object of type AtmProfile. The absorption coefficient profile
  is provided separately for O2 lines, H2O lines, CO lines, O3 lines, N2O lines, NO2, HCl, HCN lines,
  SO2 lines dry and wet continuum. The total absorption coefficient profile (addition of
  those just described) is also available, since it is the only profile really needed
  for the WaterVaporRetrieval class which derives from this
  RefractiveIndexProfile class.)doc");
  py::class_<WaterVaporRadiometer> cls_WaterVaporRadiometer(m, "WaterVaporRadiometer", R"doc(This is an axuliary class to SkyStatus that allows to identify the spectral windows
        that actually correspond to a dedicated water vapor radiometry system, and also to
        associate to those spectral windows some instrumental caracteristics such as the signal
        side band gain, the sky coupling or the spillover temperature.)doc");
  py::class_<WVRMeasurement> cls_WVRMeasurement(m, "WVRMeasurement", R"doc(This is an auxiliary class that allows to create objects corresponding
       to measurements (and their analysis) of a multichannel water vapor radiometer system.)doc");
  py::class_<SkyStatus, RefractiveIndexProfile> cls_SkyStatus(m, "SkyStatus", R"doc(From the layerThickness and layerTemperature arrays (from AtmProfile),
  the RefractiveIndexProfile array, and a brightness temperature measured to
  the sky at the corresponding frequency, this Class retrieves the water vapor
  column that corresponds to the measurement.

  The strating point will therefore be an RefractiveIndexProfile object form
  which the essential information will be inherited: layerThickness,
  layerTemperature vectors (these two inherited themselves from AtmProfile),
  and absTotalDry and absTotalWet arrays. The numerical methods
  will be an iteration wh2o to match the measured brightness temperature)doc");
  m.attr("Humidity") = m.attr("Percent");

  // ----- Angle
  cls_Angle.def(py::init<const Angle &>(), py::arg("other"), "Copy constructor");
  cls_Angle.def("__copy__", [](Angle const &self) { return Angle(self); });
  cls_Angle.def("__deepcopy__", [](Angle const &self, py::dict) { return Angle(self); }, py::arg("memo"));
  cls_Angle.def(py::init<>(), R"doc(Default constructor)doc");
  cls_Angle.def("get", static_cast<double (Angle::*)() const>(&Angle::get), R"doc(Accessor to get the angle value in SI units (rad))doc");
  cls_Angle.def("get", static_cast<double (Angle::*)(const std::string &) const>(&Angle::get), py::arg("units"), R"doc(Accessor to the angle value in specified units. Implemented units are: deg [DEG], rad [RAD] [Rad].
 If none of these implemented units is given, the SI value will be returned.)doc");
  cls_Angle.def("get", static_cast<double (Angle::*)(Angle::Units) const>(&Angle::get), py::arg("units"), "");
  cls_Angle.def("__add__", [](Angle a, const Angle & b) { return a + b; }, py::is_operator());
  cls_Angle.def("__sub__", [](Angle a, const Angle & b) { return a - b; }, py::is_operator());
  cls_Angle.def("__lt__", [](Angle a, const Angle & b) { return a < b; }, py::is_operator());
  cls_Angle.def("__gt__", [](Angle a, const Angle & b) { return a > b; }, py::is_operator());
  cls_Angle.def("__le__", [](Angle a, const Angle & b) { return a <= b; }, py::is_operator());
  cls_Angle.def("__ge__", [](Angle a, const Angle & b) { return a >= b; }, py::is_operator());
  cls_Angle.def("__eq__", [](Angle a, const Angle & b) { return a == b; }, py::is_operator());
  cls_Angle.def("__ne__", [](Angle a, const Angle & b) { return a != b; }, py::is_operator());
  cls_Angle.def(py::init<double>(), py::arg("angle"), R"doc(A full constructor: Angle value in default units (SI: radians))doc");
  py::implicitly_convertible<py::float_, Angle>();
  py::implicitly_convertible<py::int_, Angle>();
  cls_Angle.def(py::init<double, const std::string &>(), py::arg("angle"), py::arg("units"), R"doc(A full constructor: Angle value + units. Implemented units are: deg [DEG], rad [RAD] [Rad])doc");
  cls_Angle.def(py::init<double, Angle::Units>(), py::arg("angle"), py::arg("units"), "");
  cls_Angle.def("__mul__", [](Angle a, double b) { return a * b; }, py::is_operator());
  cls_Angle.def("__rmul__", [](Angle a, double b) { return a * b; }, py::is_operator());
  cls_Angle.def("__truediv__", [](Angle a, double b) { return a / b; }, py::is_operator());
  cls_Angle.attr("__hash__") = py::none();

  // ----- Error
  cls_Error.def(py::init<const Error &>(), py::arg("other"), "Copy constructor");
  cls_Error.def("__copy__", [](Error const &self) { return Error(self); });
  cls_Error.def("__deepcopy__", [](Error const &self, py::dict) { return Error(self); }, py::arg("memo"));
  cls_Error.def(py::init<>(), "");
  cls_Error.def(py::init<ErrorLevel>(), py::arg("errlev"), "");
  cls_Error.def(py::init<ErrorLevel, const std::string &>(), py::arg("errlev"), py::arg("message"), R"doc(Declare the occurrence of an error
 @pre the default level of tolerance for an acceptable error is used or a different critical
 level has been set.
 @param errlev the level of severity for the error being declared
 @param message Error message
 @post the declaration may have or may have not thrown an exception depending on the current
 tolerance about the severity level.)doc");
  cls_Error.def("notify", static_cast<void (Error::*)(ErrorLevel, const std::string &)>(&Error::notify), py::arg("errlev"), py::arg("message"), "");
  cls_Error.def("notify", static_cast<void (Error::*)(const std::string &)>(&Error::notify), py::arg("message"), "");
  cls_Error.def_static("setAcceptableLevel", static_cast<void (*)(ErrorLevel)>(&Error::setAcceptableLevel), py::arg("criticalErrlev"), R"doc(Setter to modify the critical current level of severity below which errors are tolerated.
 @param criticalErrlev critical limit: when errlev >= criticalErrlev an exception will be thrown
 @post  New declarations of errors will be thrown or not according to this new critical limit)doc");
  cls_Error.def_static("getAcceptableLevel", static_cast<ErrorLevel (*)()>(&Error::getAcceptableLevel), R"doc(Accessor to the current limit below wich error are not thrown)doc");
  cls_Error.def_static("getAcceptableLevelToString", static_cast<std::string (*)()>(&Error::getAcceptableLevelToString), R"doc(Accessor to the current limit in the form of a std::string)doc");
  cls_Error.def_static("getLevel", static_cast<ErrorLevel (*)()>(&Error::getLevel), R"doc(Accessor to the severity level of the error which has just been declared)doc");
  cls_Error.def_static("getLevelToString", static_cast<std::string (*)()>(&Error::getLevelToString), R"doc(Accessor to the severity level, in the form of a std::string, of the error which has just been declared)doc");
  cls_Error.def_static("getErrorMessage", static_cast<std::string (*)()>(&Error::getErrorMessage), R"doc(Accessor to the error message for the error which has just been declared)doc");
  cls_Error.def_static("clearMessage", static_cast<void (*)()>(&Error::clearMessage), R"doc(Clear the stack of all the error messages which passed up to the last declaration which has
 finally triggered the exception)doc");
  cls_Error.def_static("clearErrLev", static_cast<void (*)()>(&Error::clearErrLev), R"doc(Clear the stack of all the error levels which passed up to the last declaration which has
 finally triggered the exception)doc");

  // ----- Frequency
  cls_Frequency.def(py::init<const Frequency &>(), py::arg("other"), "Copy constructor");
  cls_Frequency.def("__copy__", [](Frequency const &self) { return Frequency(self); });
  cls_Frequency.def("__deepcopy__", [](Frequency const &self, py::dict) { return Frequency(self); }, py::arg("memo"));
  cls_Frequency.def(py::init<>(), R"doc(Default constructor: Frequency value set to 0 Hz)doc");
  cls_Frequency.def("get", static_cast<double (Frequency::*)() const>(&Frequency::get), R"doc(Accessor to get the numerical value of frequency (in International System units: Hz))doc");
  cls_Frequency.def("get", static_cast<double (Frequency::*)(const std::string &) const>(&Frequency::get), py::arg("units"), R"doc(Accessor to the frequency value in specified units. Implemented units are THz [THZ] [thz], GHz [GHZ] [ghz], MHz [MHZ] [mhz], Hz [HZ] [hz].
 If none of these implemented units is given, the SI value will be returned.)doc");
  cls_Frequency.def("get", static_cast<double (Frequency::*)(Frequency::Units) const>(&Frequency::get), py::arg("units"), "");
  cls_Frequency.def("__add__", [](Frequency a, const Frequency & b) { return a + b; }, py::is_operator());
  cls_Frequency.def("__sub__", [](Frequency a, const Frequency & b) { return a - b; }, py::is_operator());
  cls_Frequency.def("__lt__", [](Frequency a, const Frequency & b) { return a < b; }, py::is_operator());
  cls_Frequency.def("__gt__", [](Frequency a, const Frequency & b) { return a > b; }, py::is_operator());
  cls_Frequency.def("__le__", [](Frequency a, const Frequency & b) { return a <= b; }, py::is_operator());
  cls_Frequency.def("__ge__", [](Frequency a, const Frequency & b) { return a >= b; }, py::is_operator());
  cls_Frequency.def("__eq__", [](Frequency a, const Frequency & b) { return a == b; }, py::is_operator());
  cls_Frequency.def("__ne__", [](Frequency a, const Frequency & b) { return a != b; }, py::is_operator());
  cls_Frequency.def(py::init<double, const std::string &>(), py::arg("frequency"), py::arg("units"), R"doc(A full constructor: Frequency value + units. Valid units are THz [THZ] [thz], GHz [GHZ] [ghz], MHz [MHZ] [mhz], Hz [HZ] [hz])doc");
  cls_Frequency.def(py::init<double, Frequency::Units>(), py::arg("frequency"), py::arg("units"), "");
  cls_Frequency.def(py::init<double>(), py::arg("frequency"), R"doc(A full constructor: Frequency value in default units (International System: Hz))doc");
  py::implicitly_convertible<py::float_, Frequency>();
  py::implicitly_convertible<py::int_, Frequency>();
  cls_Frequency.def("__mul__", [](Frequency a, double b) { return a * b; }, py::is_operator());
  cls_Frequency.def("__rmul__", [](Frequency a, double b) { return a * b; }, py::is_operator());
  cls_Frequency.def("__truediv__", [](Frequency a, double b) { return a / b; }, py::is_operator());
  cls_Frequency.attr("__hash__") = py::none();

  // ----- Percent
  cls_Percent.def(py::init<const Percent &>(), py::arg("other"), "Copy constructor");
  cls_Percent.def("__copy__", [](Percent const &self) { return Percent(self); });
  cls_Percent.def("__deepcopy__", [](Percent const &self, py::dict) { return Percent(self); }, py::arg("memo"));
  cls_Percent.def(py::init<>(), R"doc(Default constructor)doc");
  cls_Percent.def("get", static_cast<double (Percent::*)() const>(&Percent::get), R"doc(Accessor to the percent value in International System units)doc");
  cls_Percent.def("get", static_cast<double (Percent::*)(const std::string &) const>(&Percent::get), py::arg("units"), R"doc(Accessor to the percent value in specified units.)doc");
  cls_Percent.def("get", static_cast<double (Percent::*)(Percent::Units) const>(&Percent::get), py::arg("units"), "");
  cls_Percent.def("__add__", [](Percent a, const Percent & b) { return a + b; }, py::is_operator());
  cls_Percent.def("__sub__", [](Percent a, const Percent & b) { return a - b; }, py::is_operator());
  cls_Percent.def("__lt__", [](Percent a, const Percent & b) { return a < b; }, py::is_operator());
  cls_Percent.def("__gt__", [](Percent a, const Percent & b) { return a > b; }, py::is_operator());
  cls_Percent.def("__le__", [](Percent a, const Percent & b) { return a <= b; }, py::is_operator());
  cls_Percent.def("__ge__", [](Percent a, const Percent & b) { return a >= b; }, py::is_operator());
  cls_Percent.def("__eq__", [](Percent a, const Percent & b) { return a == b; }, py::is_operator());
  cls_Percent.def("__ne__", [](Percent a, const Percent & b) { return a != b; }, py::is_operator());
  cls_Percent.def(py::init<double>(), py::arg("percent"), R"doc(A full constructor: Amount in default units (relative to 1))doc");
  py::implicitly_convertible<py::float_, Percent>();
  py::implicitly_convertible<py::int_, Percent>();
  cls_Percent.def(py::init<double, const std::string &>(), py::arg("percent"), py::arg("units"), R"doc(A full constructor: Amount + units. Valid units are: %)doc");
  cls_Percent.def(py::init<double, Percent::Units>(), py::arg("percent"), py::arg("units"), "");
  cls_Percent.def("__mul__", [](Percent a, double b) { return a * b; }, py::is_operator());
  cls_Percent.def("__rmul__", [](Percent a, double b) { return a * b; }, py::is_operator());
  cls_Percent.def("__truediv__", [](Percent a, double b) { return a / b; }, py::is_operator());
  cls_Percent.attr("__hash__") = py::none();

  // ----- InverseLength
  cls_InverseLength.def(py::init<const InverseLength &>(), py::arg("other"), "Copy constructor");
  cls_InverseLength.def("__copy__", [](InverseLength const &self) { return InverseLength(self); });
  cls_InverseLength.def("__deepcopy__", [](InverseLength const &self, py::dict) { return InverseLength(self); }, py::arg("memo"));
  cls_InverseLength.def(py::init<>(), R"doc(Default constructor: Length value set to 0 m^-1)doc");
  cls_InverseLength.def("get", static_cast<double (InverseLength::*)() const>(&InverseLength::get), R"doc(Accessor to get the numerical value of inverse length (in International System units: m^-1))doc");
  cls_InverseLength.def("get", static_cast<double (InverseLength::*)(const std::string &) const>(&InverseLength::get), py::arg("units"), R"doc(Accessor to the inverse length value in specified units. Implemented units are km-1 [KM-1], m-1 [M-1], mm-1 [MM-1], micron-1 [MICRON-1], nm-1 [NM-1].
 If none of these implemented units is given, the SI value will be returned.)doc");
  cls_InverseLength.def("get", static_cast<double (InverseLength::*)(InverseLength::Units) const>(&InverseLength::get), py::arg("units"), "");
  cls_InverseLength.def("__add__", [](InverseLength a, const InverseLength & b) { return a + b; }, py::is_operator());
  cls_InverseLength.def("__sub__", [](InverseLength a, const InverseLength & b) { return a - b; }, py::is_operator());
  cls_InverseLength.def("__lt__", [](InverseLength a, const InverseLength & b) { return a < b; }, py::is_operator());
  cls_InverseLength.def("__gt__", [](InverseLength a, const InverseLength & b) { return a > b; }, py::is_operator());
  cls_InverseLength.def("__le__", [](InverseLength a, const InverseLength & b) { return a <= b; }, py::is_operator());
  cls_InverseLength.def("__ge__", [](InverseLength a, const InverseLength & b) { return a >= b; }, py::is_operator());
  cls_InverseLength.def("__eq__", [](InverseLength a, const InverseLength & b) { return a == b; }, py::is_operator());
  cls_InverseLength.def("__ne__", [](InverseLength a, const InverseLength & b) { return a != b; }, py::is_operator());
  cls_InverseLength.def(py::init<double>(), py::arg("inverseLength"), R"doc(A full constructor: value in default units (m^-1))doc");
  py::implicitly_convertible<py::float_, InverseLength>();
  py::implicitly_convertible<py::int_, InverseLength>();
  cls_InverseLength.def(py::init<double, const std::string &>(), py::arg("inverseLength"), py::arg("units"), R"doc(A full constructor: value + units. Valid units are:  km-1 [KM-1], m-1 [M-1], mm-1 [MM-1], micron-1 [MICRON-1], nm-1 [NM-1].)doc");
  cls_InverseLength.def(py::init<double, InverseLength::Units>(), py::arg("inverseLength"), py::arg("units"), "");
  cls_InverseLength.def("__mul__", [](InverseLength a, double b) { return a * b; }, py::is_operator());
  cls_InverseLength.def("__rmul__", [](InverseLength a, double b) { return a * b; }, py::is_operator());
  cls_InverseLength.def("__truediv__", [](InverseLength a, double b) { return a / b; }, py::is_operator());
  cls_InverseLength.attr("__hash__") = py::none();

  // ----- Length
  cls_Length.def(py::init<const Length &>(), py::arg("other"), "Copy constructor");
  cls_Length.def("__copy__", [](Length const &self) { return Length(self); });
  cls_Length.def("__deepcopy__", [](Length const &self, py::dict) { return Length(self); }, py::arg("memo"));
  cls_Length.def(py::init<>(), R"doc(Default constructor: Length value set to 0 m)doc");
  cls_Length.def("get", static_cast<double (Length::*)() const>(&Length::get), R"doc(Accessor to get the numerical value of length (in International System units: m))doc");
  cls_Length.def("get", static_cast<double (Length::*)(const std::string &) const>(&Length::get), py::arg("units"), R"doc(Accessor to the length value in specified units. Implemented units are km [KM], m [M], mm [MM], micron [MICRON], nm [NM].
 If none of these implemented units is given, the SI value will be returned.)doc");
  cls_Length.def("get", static_cast<double (Length::*)(const Length::Units) const>(&Length::get), py::arg("units"), "");
  cls_Length.def("__add__", [](Length a, const Length & b) { return a + b; }, py::is_operator());
  cls_Length.def("__sub__", [](Length a, const Length & b) { return a - b; }, py::is_operator());
  cls_Length.def("__lt__", [](Length a, const Length & b) { return a < b; }, py::is_operator());
  cls_Length.def("__gt__", [](Length a, const Length & b) { return a > b; }, py::is_operator());
  cls_Length.def("__le__", [](Length a, const Length & b) { return a <= b; }, py::is_operator());
  cls_Length.def("__ge__", [](Length a, const Length & b) { return a >= b; }, py::is_operator());
  cls_Length.def("__eq__", [](Length a, const Length & b) { return a == b; }, py::is_operator());
  cls_Length.def("__ne__", [](Length a, const Length & b) { return a != b; }, py::is_operator());
  cls_Length.def(py::init<double>(), py::arg("length"), R"doc(A full constructor: value in default units (m))doc");
  py::implicitly_convertible<py::float_, Length>();
  py::implicitly_convertible<py::int_, Length>();
  cls_Length.def(py::init<double, const std::string &>(), py::arg("length"), py::arg("units"), R"doc(A full constructor: value + units. Valid units are:  km [KM], m [M], mm [MM], micron [MICRON], nm [NM].)doc");
  cls_Length.def(py::init<double, Length::Units>(), py::arg("length"), py::arg("units"), "");
  cls_Length.def("__mul__", [](Length a, double b) { return a * b; }, py::is_operator());
  cls_Length.def("__rmul__", [](Length a, double b) { return a * b; }, py::is_operator());
  cls_Length.def("__truediv__", [](Length a, double b) { return a / b; }, py::is_operator());
  cls_Length.attr("__hash__") = py::none();

  // ----- MassDensity
  cls_MassDensity.def(py::init<const MassDensity &>(), py::arg("other"), "Copy constructor");
  cls_MassDensity.def("__copy__", [](MassDensity const &self) { return MassDensity(self); });
  cls_MassDensity.def("__deepcopy__", [](MassDensity const &self, py::dict) { return MassDensity(self); }, py::arg("memo"));
  cls_MassDensity.def(py::init<>(), R"doc(Default constructor)doc");
  cls_MassDensity.def("get", static_cast<double (MassDensity::*)() const>(&MassDensity::get), R"doc(Accessor to the massdensity value in International System units (kgm**-3))doc");
  cls_MassDensity.def("get", static_cast<double (MassDensity::*)(const std::string &) const>(&MassDensity::get), py::arg("units"), R"doc(Accessor to the massdensity value in specified units.
 Valid units are kgm**-3 [kg m**-3, KGM**-3, KG M**-3], gcm**-3 [g cm**-3, GCM**-3, G CM**-3].)doc");
  cls_MassDensity.def("get", static_cast<double (MassDensity::*)(const MassDensity::Units) const>(&MassDensity::get), py::arg("units"), "");
  cls_MassDensity.def("__add__", [](MassDensity a, const MassDensity & b) { return a + b; }, py::is_operator());
  cls_MassDensity.def("__sub__", [](MassDensity a, const MassDensity & b) { return a - b; }, py::is_operator());
  cls_MassDensity.def("__lt__", [](MassDensity a, const MassDensity & b) { return a < b; }, py::is_operator());
  cls_MassDensity.def("__gt__", [](MassDensity a, const MassDensity & b) { return a > b; }, py::is_operator());
  cls_MassDensity.def("__le__", [](MassDensity a, const MassDensity & b) { return a <= b; }, py::is_operator());
  cls_MassDensity.def("__ge__", [](MassDensity a, const MassDensity & b) { return a >= b; }, py::is_operator());
  cls_MassDensity.def("__eq__", [](MassDensity a, const MassDensity & b) { return a == b; }, py::is_operator());
  cls_MassDensity.def("__ne__", [](MassDensity a, const MassDensity & b) { return a != b; }, py::is_operator());
  cls_MassDensity.def(py::init<double>(), py::arg("massdensity"), R"doc(A full constructor: Mass Density value assumed by default to be in kgm**-3 (International System))doc");
  py::implicitly_convertible<py::float_, MassDensity>();
  py::implicitly_convertible<py::int_, MassDensity>();
  cls_MassDensity.def(py::init<double, const std::string &>(), py::arg("massdensity"), py::arg("units"), R"doc(A full constructor: Mass Density value + unit.
 Valid units are kgm**-3 [kg m**-3, KGM**-3, KG M**-3], gcm**-3 [g cm**-3, GCM**-3, G CM**-3].
 If none of these implemented units is given, the SI value will be returned.)doc");
  cls_MassDensity.def(py::init<double, MassDensity::Units>(), py::arg("massdensity"), py::arg("units"), "");
  cls_MassDensity.def("__mul__", [](MassDensity a, double b) { return a * b; }, py::is_operator());
  cls_MassDensity.def("__rmul__", [](MassDensity a, double b) { return a * b; }, py::is_operator());
  cls_MassDensity.def("__truediv__", [](MassDensity a, double b) { return a / b; }, py::is_operator());
  cls_MassDensity.attr("__hash__") = py::none();

  // ----- NumberDensity
  cls_NumberDensity.def(py::init<const NumberDensity &>(), py::arg("other"), "Copy constructor");
  cls_NumberDensity.def("__copy__", [](NumberDensity const &self) { return NumberDensity(self); });
  cls_NumberDensity.def("__deepcopy__", [](NumberDensity const &self, py::dict) { return NumberDensity(self); }, py::arg("memo"));
  cls_NumberDensity.def(py::init<>(), R"doc(Default constructor)doc");
  cls_NumberDensity.def("get", static_cast<double (NumberDensity::*)() const>(&NumberDensity::get), R"doc(Accessor to the numberdensity value in International System units (K))doc");
  cls_NumberDensity.def("get", static_cast<double (NumberDensity::*)(const std::string &) const>(&NumberDensity::get), py::arg("units"), R"doc(Accessor to the numberdensity value in specified units. Valid units are K [k], mK [mk], and C [c])doc");
  cls_NumberDensity.def("get", static_cast<double (NumberDensity::*)(const NumberDensity::Units) const>(&NumberDensity::get), py::arg("units"), "");
  cls_NumberDensity.def("__add__", [](NumberDensity a, const NumberDensity & b) { return a + b; }, py::is_operator());
  cls_NumberDensity.def("__sub__", [](NumberDensity a, const NumberDensity & b) { return a - b; }, py::is_operator());
  cls_NumberDensity.def("__lt__", [](NumberDensity a, const NumberDensity & b) { return a < b; }, py::is_operator());
  cls_NumberDensity.def("__gt__", [](NumberDensity a, const NumberDensity & b) { return a > b; }, py::is_operator());
  cls_NumberDensity.def("__le__", [](NumberDensity a, const NumberDensity & b) { return a <= b; }, py::is_operator());
  cls_NumberDensity.def("__ge__", [](NumberDensity a, const NumberDensity & b) { return a >= b; }, py::is_operator());
  cls_NumberDensity.def("__eq__", [](NumberDensity a, const NumberDensity & b) { return a == b; }, py::is_operator());
  cls_NumberDensity.def("__ne__", [](NumberDensity a, const NumberDensity & b) { return a != b; }, py::is_operator());
  cls_NumberDensity.def(py::init<double>(), py::arg("numberdensity"), R"doc(A full constructor: Number Density value assumed by default to be in m**-3 (International System))doc");
  py::implicitly_convertible<py::float_, NumberDensity>();
  py::implicitly_convertible<py::int_, NumberDensity>();
  cls_NumberDensity.def(py::init<double, const std::string &>(), py::arg("numberdensity"), py::arg("units"), R"doc(A full constructor: Number Density value + unit. Valid units are m**-3 [M**-3], cm**-3 [CM**-3].
 If none of these implented units is given, the SI value will be returned.)doc");
  cls_NumberDensity.def(py::init<double, NumberDensity::Units>(), py::arg("numberdensity"), py::arg("units"), "");
  cls_NumberDensity.def("__mul__", [](NumberDensity a, double b) { return a * b; }, py::is_operator());
  cls_NumberDensity.def("__rmul__", [](NumberDensity a, double b) { return a * b; }, py::is_operator());
  cls_NumberDensity.def("__truediv__", [](NumberDensity a, double b) { return a / b; }, py::is_operator());
  cls_NumberDensity.attr("__hash__") = py::none();

  // ----- Opacity
  cls_Opacity.def(py::init<const Opacity &>(), py::arg("other"), "Copy constructor");
  cls_Opacity.def("__copy__", [](Opacity const &self) { return Opacity(self); });
  cls_Opacity.def("__deepcopy__", [](Opacity const &self, py::dict) { return Opacity(self); }, py::arg("memo"));
  cls_Opacity.def(py::init<>(), R"doc(Default constructor: Opacity value set to 0 np)doc");
  cls_Opacity.def("get", static_cast<double (Opacity::*)() const>(&Opacity::get), R"doc(Accessor to get the numerical value of opacity (in np))doc");
  cls_Opacity.def("get", static_cast<double (Opacity::*)(const std::string &) const>(&Opacity::get), py::arg("units"), R"doc(Accessor to the opacity value in specified units. Implemented units are np [neper] [NP] [NEPER], db [DB].
 If none of these implemented units is given, the value in neper will be returned.)doc");
  cls_Opacity.def("get", static_cast<double (Opacity::*)(Opacity::Units) const>(&Opacity::get), py::arg("units"), "");
  cls_Opacity.def("__add__", [](Opacity a, const Opacity & b) { return a + b; }, py::is_operator());
  cls_Opacity.def("__sub__", [](Opacity a, const Opacity & b) { return a - b; }, py::is_operator());
  cls_Opacity.def("__lt__", [](Opacity a, const Opacity & b) { return a < b; }, py::is_operator());
  cls_Opacity.def("__gt__", [](Opacity a, const Opacity & b) { return a > b; }, py::is_operator());
  cls_Opacity.def("__le__", [](Opacity a, const Opacity & b) { return a <= b; }, py::is_operator());
  cls_Opacity.def("__ge__", [](Opacity a, const Opacity & b) { return a >= b; }, py::is_operator());
  cls_Opacity.def("__eq__", [](Opacity a, const Opacity & b) { return a == b; }, py::is_operator());
  cls_Opacity.def("__ne__", [](Opacity a, const Opacity & b) { return a != b; }, py::is_operator());
  cls_Opacity.def(py::init<double>(), py::arg("opacity"), R"doc(A full constructor: value in default units (np))doc");
  py::implicitly_convertible<py::float_, Opacity>();
  py::implicitly_convertible<py::int_, Opacity>();
  cls_Opacity.def(py::init<double, const std::string &>(), py::arg("opacity"), py::arg("units"), R"doc(A full constructor: value + units. Valid units are:  np [neper] [NP] [NEPER], db [DB].)doc");
  cls_Opacity.def(py::init<double, Opacity::Units>(), py::arg("opacity"), py::arg("units"), "");
  cls_Opacity.def("__mul__", [](Opacity a, double b) { return a * b; }, py::is_operator());
  cls_Opacity.def("__rmul__", [](Opacity a, double b) { return a * b; }, py::is_operator());
  cls_Opacity.def("__truediv__", [](Opacity a, double b) { return a / b; }, py::is_operator());
  cls_Opacity.attr("__hash__") = py::none();

  // ----- Pressure
  cls_Pressure.def(py::init<const Pressure &>(), py::arg("other"), "Copy constructor");
  cls_Pressure.def("__copy__", [](Pressure const &self) { return Pressure(self); });
  cls_Pressure.def("__deepcopy__", [](Pressure const &self, py::dict) { return Pressure(self); }, py::arg("memo"));
  cls_Pressure.def(py::init<>(), R"doc(Default constructor)doc");
  cls_Pressure.def("get", static_cast<double (Pressure::*)() const>(&Pressure::get), R"doc(Accessor to get the value in SI units (Pa))doc");
  cls_Pressure.def("get", static_cast<double (Pressure::*)(const std::string &) const>(&Pressure::get), py::arg("units"), R"doc(Accessor to get the value in the following (implemented) units: hPa [HPA] [hpa], bar [BAR], mb [MB], mbar [MBAR], atm [ATM].
If none of these implemented units is given, the SI value will be returned.)doc");
  cls_Pressure.def("get", static_cast<double (Pressure::*)(Pressure::Units) const>(&Pressure::get), py::arg("units"), "");
  cls_Pressure.def("__add__", [](Pressure a, const Pressure & b) { return a + b; }, py::is_operator());
  cls_Pressure.def("__sub__", [](Pressure a, const Pressure & b) { return a - b; }, py::is_operator());
  cls_Pressure.def("__lt__", [](Pressure a, const Pressure & b) { return a < b; }, py::is_operator());
  cls_Pressure.def("__gt__", [](Pressure a, const Pressure & b) { return a > b; }, py::is_operator());
  cls_Pressure.def("__le__", [](Pressure a, const Pressure & b) { return a <= b; }, py::is_operator());
  cls_Pressure.def("__ge__", [](Pressure a, const Pressure & b) { return a >= b; }, py::is_operator());
  cls_Pressure.def("__eq__", [](Pressure a, const Pressure & b) { return a == b; }, py::is_operator());
  cls_Pressure.def("__ne__", [](Pressure a, const Pressure & b) { return a != b; }, py::is_operator());
  cls_Pressure.def(py::init<double>(), py::arg("pressure"), R"doc(A full constructor: Pressure value in default SI units (Pa))doc");
  py::implicitly_convertible<py::float_, Pressure>();
  py::implicitly_convertible<py::int_, Pressure>();
  cls_Pressure.def(py::init<double, const std::string &>(), py::arg("pressure"), py::arg("units"), R"doc(A full constructor: Pressure value + units. Valid units are hPa [HPA] [hpa], bar [BAR], mb [MB], mbar [MBAR], atm [ATM].)doc");
  cls_Pressure.def(py::init<double, Pressure::Units>(), py::arg("pressure"), py::arg("units"), "");
  cls_Pressure.def("__mul__", [](Pressure a, double b) { return a * b; }, py::is_operator());
  cls_Pressure.def("__rmul__", [](Pressure a, double b) { return a * b; }, py::is_operator());
  cls_Pressure.def("__truediv__", [](Pressure a, double b) { return a / b; }, py::is_operator());
  cls_Pressure.attr("__hash__") = py::none();

  // ----- Temperature
  cls_Temperature.def(py::init<const Temperature &>(), py::arg("other"), "Copy constructor");
  cls_Temperature.def("__copy__", [](Temperature const &self) { return Temperature(self); });
  cls_Temperature.def("__deepcopy__", [](Temperature const &self, py::dict) { return Temperature(self); }, py::arg("memo"));
  cls_Temperature.def(py::init<>(), R"doc(Default constructor)doc");
  cls_Temperature.def("get", static_cast<double (Temperature::*)() const>(&Temperature::get), R"doc(Accessor to the temperature value in International System units (K))doc");
  cls_Temperature.def("get", static_cast<double (Temperature::*)(const std::string &) const>(&Temperature::get), py::arg("units"), R"doc(Accessor to the temperature value in specified units. Valid units are K [k], mK [mk], and C [c])doc");
  cls_Temperature.def("get", static_cast<double (Temperature::*)(Temperature::Units) const>(&Temperature::get), py::arg("units"), "");
  cls_Temperature.def("__add__", [](Temperature a, const Temperature & b) { return a + b; }, py::is_operator());
  cls_Temperature.def("__sub__", [](Temperature a, const Temperature & b) { return a - b; }, py::is_operator());
  cls_Temperature.def("__lt__", [](Temperature a, const Temperature & b) { return a < b; }, py::is_operator());
  cls_Temperature.def("__gt__", [](Temperature a, const Temperature & b) { return a > b; }, py::is_operator());
  cls_Temperature.def("__le__", [](Temperature a, const Temperature & b) { return a <= b; }, py::is_operator());
  cls_Temperature.def("__ge__", [](Temperature a, const Temperature & b) { return a >= b; }, py::is_operator());
  cls_Temperature.def("__eq__", [](Temperature a, const Temperature & b) { return a == b; }, py::is_operator());
  cls_Temperature.def("__ne__", [](Temperature a, const Temperature & b) { return a != b; }, py::is_operator());
  cls_Temperature.def(py::init<double>(), py::arg("temperature"), R"doc(A full constructor: Temperature value assumed by default to be in K (International System))doc");
  py::implicitly_convertible<py::float_, Temperature>();
  py::implicitly_convertible<py::int_, Temperature>();
  cls_Temperature.def(py::init<double, const std::string &>(), py::arg("temperature"), py::arg("units"), R"doc(A full constructor: Temperature value + unit. Valid units are K [k], mK [mk], and C [c].
 If none of these implemented units is given, the SI value will be returned.)doc");
  cls_Temperature.def(py::init<double, Temperature::Units>(), py::arg("temperature"), py::arg("units"), "");
  cls_Temperature.def("__mul__", [](Temperature a, double b) { return a * b; }, py::is_operator());
  cls_Temperature.def("__rmul__", [](Temperature a, double b) { return a * b; }, py::is_operator());
  cls_Temperature.def("__truediv__", [](Temperature a, double b) { return a / b; }, py::is_operator());
  cls_Temperature.attr("__hash__") = py::none();

  // ----- AtmProfile
  cls_AtmProfile.def(py::init<const AtmProfile &>(), py::arg("other"), "Copy constructor");
  cls_AtmProfile.def("__copy__", [](AtmProfile const &self) { return AtmProfile(self); });
  cls_AtmProfile.def("__deepcopy__", [](AtmProfile const &self, py::dict) { return AtmProfile(self); }, py::arg("memo"));
  cls_AtmProfile.def(py::init<unsigned int>(), py::arg("n"), R"doc(A constructor of an empty profile with n layers, that can be filled up later.)doc");
  cls_AtmProfile.def(py::init<const Length &, const std::vector<Length> &, const std::vector<Pressure> &, const std::vector<Temperature> &, const std::vector<MassDensity> &>(), py::arg("altitude"), py::arg("v_layerThickness"), py::arg("v_layerPressure"), py::arg("v_layerTemperature"), py::arg("v_layerWaterVapor"), R"doc(The user provides his own atmospheric profile (basic one: four vectors for layer thickness in m,
average pressure in each layer in mb, average temperature in each layer in K, and average water
vapor density in each layer in kg/m**3). QUESTION: SHOULD O3, CO, N2O, NO2, HCl, HCN, SO2 PROFILES BE FILLED UP
INTERNALLY FROM A STANDARD ATMOSPHERE OR LEFT ITS ABUNDANCES EQUAL TO ZERO ?)doc");
  cls_AtmProfile.def(py::init<const std::vector<Length> &, const std::vector<Pressure> &, const std::vector<Temperature> &, const std::vector<MassDensity> &>(), py::arg("v_layerBoundaries"), py::arg("v_layerPressure"), py::arg("v_layerTemperature"), py::arg("v_layerWaterVapor"), "");
  cls_AtmProfile.def(py::init<const Length &, const std::vector<Length> &, const std::vector<Pressure> &, const std::vector<Temperature> &, const std::vector<NumberDensity> &>(), py::arg("altitude"), py::arg("v_layerThickness"), py::arg("v_layerPressure"), py::arg("v_layerTemperature"), py::arg("v_layerWaterVapor"), "");
  cls_AtmProfile.def(py::init<const std::vector<Length> &, const std::vector<Pressure> &, const std::vector<Temperature> &, const std::vector<NumberDensity> &>(), py::arg("v_layerBoundaries"), py::arg("v_layerPressure"), py::arg("v_layerTemperature"), py::arg("v_layerWaterVapor"), "");
  cls_AtmProfile.def(py::init<const Length &, const std::vector<Length> &, const std::vector<Pressure> &, const std::vector<Temperature> &, const std::vector<MassDensity> &, const std::vector<NumberDensity> &>(), py::arg("altitude"), py::arg("v_layerThickness"), py::arg("v_layerPressure"), py::arg("v_layerTemperature"), py::arg("v_layerWaterVapor"), py::arg("v_layerO3"), R"doc(The user provides his own atmospheric profile (in this case five vectors for layer thickness in m,
average pressure in each layer in mb, average temperature in each layer in K, average water vapor
density in each layer in kg/m**3, and average ozone number density in each layer in molecules/m**3)
QUESTION: SHOULD CO and N2O, NO2, HCl, HCN, SO2 PROFILES BE FILLED UP
INTERNALLY FROM A STANDARD ATMOSPHERE OR LEFT ITS ABUNDANCES EQUAL TO ZERO ?)doc");
  cls_AtmProfile.def(py::init<const Length &, const std::vector<Length> &, const std::vector<Pressure> &, const std::vector<Temperature> &, const std::vector<NumberDensity> &, const std::vector<NumberDensity> &>(), py::arg("altitude"), py::arg("v_layerThickness"), py::arg("v_layerPressure"), py::arg("v_layerTemperature"), py::arg("v_layerWaterVapor"), py::arg("v_layerO3"), "");
  cls_AtmProfile.def(py::init<const Length &, const std::vector<Length> &, const std::vector<Pressure> &, const std::vector<Temperature> &, const std::vector<MassDensity> &, const std::vector<NumberDensity> &, const std::vector<NumberDensity> &, const std::vector<NumberDensity> &, const std::vector<NumberDensity> &, const std::vector<NumberDensity> &, const std::vector<NumberDensity> &, const std::vector<NumberDensity> &>(), py::arg("altitude"), py::arg("v_layerThickness"), py::arg("v_layerPressure"), py::arg("v_layerTemperature"), py::arg("v_layerWaterVapor"), py::arg("v_layerO3"), py::arg("v_layerCO"), py::arg("v_layerN2O"), py::arg("v_layerNO2"), py::arg("v_layerSO2"), py::arg("v_layerHCl"), py::arg("v_layerHCN"), R"doc(The user provides his own atmospheric profile (in this case seven vectors for layer thickness in m,
average pressure in each layer in mb, average temperature in each layer in K, average water vapor
density in each layer in kg/m**3, average ozone number density in each layer in molecules/m**3,
average CO number density in each layer in molecules/m**3, average N2O, NO2, HCl, HCN, SO2 number density in each
layer in molecules/m**3))doc");
  cls_AtmProfile.def(py::init<const Length &, const std::vector<Length> &, const std::vector<Pressure> &, const std::vector<Temperature> &, const std::vector<NumberDensity> &, const std::vector<NumberDensity> &, const std::vector<NumberDensity> &, const std::vector<NumberDensity> &, const std::vector<NumberDensity> &, const std::vector<NumberDensity> &, const std::vector<NumberDensity> &, const std::vector<NumberDensity> &>(), py::arg("altitude"), py::arg("v_layerThickness"), py::arg("v_layerPressure"), py::arg("v_layerTemperature"), py::arg("v_layerWaterVapor"), py::arg("v_layerO3"), py::arg("v_layerCO"), py::arg("v_layerN2O"), py::arg("v_layerNO2"), py::arg("v_layerSO2"), py::arg("v_layerHCl"), py::arg("v_layerHCN"), "");
  cls_AtmProfile.def("getAtmosphereType", static_cast<std::string (AtmProfile::*)() const>(&AtmProfile::getAtmosphereType), R"doc(Accessor to the type of current atmosphere *)doc");
  cls_AtmProfile.def("getAtmosphereType", [](const AtmProfile &, unsigned int typeAtm) { return AtmProfile::getAtmosphereType(typeAtm); }, py::arg("typeAtm"), R"doc(Accessor to the type of atmosphere specified by the number*)doc");
  cls_AtmProfile.def_static("getAtmosphereType_static", static_cast<std::string (*)(unsigned int)>(&AtmProfile::getAtmosphereType), py::arg("typeAtm"), R"doc(Accessor to the type of atmosphere specified by the number*)doc");
  cls_AtmProfile.def("getGroundTemperature", static_cast<Temperature (AtmProfile::*)() const>(&AtmProfile::getGroundTemperature), R"doc(Accessor to the current Ground Temperature used in the object)doc");
  cls_AtmProfile.def("getTropoLapseRate", static_cast<double (AtmProfile::*)() const>(&AtmProfile::getTropoLapseRate), R"doc(Accessor to the current Tropospheric Lapse Rate used in the object (temperature/length units))doc");
  cls_AtmProfile.def("getGroundPressure", static_cast<Pressure (AtmProfile::*)() const>(&AtmProfile::getGroundPressure), R"doc(Accessor to the current Ground Pressure used in the object (pressure units))doc");
  cls_AtmProfile.def("getTropopauseTemperature", static_cast<Temperature (AtmProfile::*)() const>(&AtmProfile::getTropopauseTemperature), R"doc(Accessor to the current Tropopause Temperature used in the object)doc");
  cls_AtmProfile.def("getRelativeHumidity", static_cast<Humidity (AtmProfile::*)() const>(&AtmProfile::getRelativeHumidity), R"doc(Accessor to the current Ground Relative Humidity in the object (humidity units))doc");
  cls_AtmProfile.def("getWvScaleHeight", static_cast<Length (AtmProfile::*)() const>(&AtmProfile::getWvScaleHeight), R"doc(Accessor to the current Water Vapor Scale Height in the object (length units))doc");
  cls_AtmProfile.def("getPressureStep", static_cast<Pressure (AtmProfile::*)() const>(&AtmProfile::getPressureStep), R"doc(Accessor to the current Primary Pressure Step in the object. The Primary Pressure Step
(pressure units) is used to define the thickness of the first layer in the profile.
Pressure difference between the boundaries of first layer will be equal to the
Primary Pressure Step.)doc");
  cls_AtmProfile.def("getAltitude", static_cast<Length (AtmProfile::*)() const>(&AtmProfile::getAltitude), R"doc(Accessor to the ground altitude of site (length units))doc");
  cls_AtmProfile.def("getGroundAltitude", static_cast<Length (AtmProfile::*)() const>(&AtmProfile::getGroundAltitude), R"doc(Alternative accessor to the ground altitude of site (length units))doc");
  cls_AtmProfile.def("setAltitude", static_cast<void (AtmProfile::*)(const Length &)>(&AtmProfile::setAltitude), py::arg("groundaltitude"), R"doc(setter for the ground altitude of site (length units). Careful! It will remove or add layers if necessary.
Ground values of T/P/h would change as well)doc");
  cls_AtmProfile.def("getTropopauseAltitude", static_cast<Length (AtmProfile::*)() const>(&AtmProfile::getTropopauseAltitude), R"doc(Accessor to the altitude of the tropopause (length units))doc");
  cls_AtmProfile.def("getTopAtmProfile", static_cast<Length (AtmProfile::*)() const>(&AtmProfile::getTopAtmProfile), R"doc(Accessor to the Maximum allowed altitude for the Atmospheric Profile above the site (length units))doc");
  cls_AtmProfile.def("getNumLayer", static_cast<unsigned int (AtmProfile::*)() const>(&AtmProfile::getNumLayer), R"doc(Accessor to the number of layers of the atmospheric profile)doc");
  cls_AtmProfile.def("getTemperatureProfile", static_cast<std::vector<Temperature> (AtmProfile::*)() const>(&AtmProfile::getTemperatureProfile), R"doc(Method to access the Temperature Profile)doc");
  cls_AtmProfile.def("getLayerTemperature", static_cast<Temperature (AtmProfile::*)(unsigned int) const>(&AtmProfile::getLayerTemperature), py::arg("i"), R"doc(Method to access the average Temperature in layer i (thickness of layers in ThicknessProfile)
@exception AtmException if the layer is not valid.)doc");
  cls_AtmProfile.def("getLayerBottomTemperature", static_cast<Temperature (AtmProfile::*)(unsigned int) const>(&AtmProfile::getLayerBottomTemperature), py::arg("i"), R"doc(Method to access the Temperature at bottom of layer i (thickness of layers in ThicknessProfile)
@exception AtmException if the layer is not valid.)doc");
  cls_AtmProfile.def("getLayerTopTemperature", static_cast<Temperature (AtmProfile::*)(unsigned int) const>(&AtmProfile::getLayerTopTemperature), py::arg("i"), R"doc(Method to access the Temperature at top of layer i (thickness of layers in ThicknessProfile)
@exception AtmException if the layer is not valid.)doc");
  cls_AtmProfile.def("setLayerTemperature", static_cast<void (AtmProfile::*)(unsigned int, const Temperature &)>(&AtmProfile::setLayerTemperature), py::arg("i"), py::arg("layerTemperature"), R"doc(Setter for the average Temperature in layer i (allows to touch one layer each time once a profile has been defined))doc");
  cls_AtmProfile.def("getThicknessProfile", static_cast<std::vector<Length> (AtmProfile::*)() const>(&AtmProfile::getThicknessProfile), R"doc(Method to retrieve the layer thickness from site altitude upwards.
 Use Altitude to + ThicknessProfile to know the vertical grid.)doc");
  cls_AtmProfile.def("getLayerThickness", static_cast<Length (AtmProfile::*)(unsigned int) const>(&AtmProfile::getLayerThickness), py::arg("i"), R"doc(Method to access the layer thickness of layer i
@exception AtmException if the layer is not valid.)doc");
  cls_AtmProfile.def("setLayerThickness", static_cast<void (AtmProfile::*)(unsigned int, const Length &)>(&AtmProfile::setLayerThickness), py::arg("i"), py::arg("layerThickness"), R"doc(Setter for the thickness of layer i (allows to touch one layer each time once a profile has been defined). We do
 not advise to use this one unless you change P and T accordingly)doc");
  cls_AtmProfile.def("getLayerBottomHeightAboveGround", static_cast<Length (AtmProfile::*)(unsigned int) const>(&AtmProfile::getLayerBottomHeightAboveGround), py::arg("i"), R"doc(Method to access the Bottom Height of layer i above the Ground
@exception AtmException if the layer is not valid.)doc");
  cls_AtmProfile.def("getLayerBottomHeightAboveSeaLevel", static_cast<Length (AtmProfile::*)(unsigned int) const>(&AtmProfile::getLayerBottomHeightAboveSeaLevel), py::arg("i"), R"doc(Method to access the Bottom Height of layer i above the Sea Level
@exception AtmException if the layer is not valid.)doc");
  cls_AtmProfile.def("getLayerTopHeightAboveGround", static_cast<Length (AtmProfile::*)(unsigned int) const>(&AtmProfile::getLayerTopHeightAboveGround), py::arg("i"), R"doc(Method to access the Top Height of layer i above the Ground
@exception AtmException if the layer is not valid.)doc");
  cls_AtmProfile.def("getLayerTopHeightAboveSeaLevel", static_cast<Length (AtmProfile::*)(unsigned int) const>(&AtmProfile::getLayerTopHeightAboveSeaLevel), py::arg("i"), R"doc(Method to access the Top Height of layer i above the Sea Level
@exception AtmException if the layer is not valid.)doc");
  cls_AtmProfile.def("getLayerWaterVaporMassDensity", static_cast<MassDensity (AtmProfile::*)(unsigned int) const>(&AtmProfile::getLayerWaterVaporMassDensity), py::arg("i"), R"doc(Function to retrieve Average Water vapor density in a given layer in kg/m**3
 (thickness of layers in ThicknessProfile)
@exception AtmException if the layer is not valid.)doc");
  cls_AtmProfile.def("getLayerBottomWaterVaporMassDensity", static_cast<MassDensity (AtmProfile::*)(unsigned int) const>(&AtmProfile::getLayerBottomWaterVaporMassDensity), py::arg("i"), "");
  cls_AtmProfile.def("getLayerTopWaterVaporMassDensity", static_cast<MassDensity (AtmProfile::*)(unsigned int) const>(&AtmProfile::getLayerTopWaterVaporMassDensity), py::arg("i"), "");
  cls_AtmProfile.def("getLayerWaterVaporNumberDensity", static_cast<NumberDensity (AtmProfile::*)(unsigned int) const>(&AtmProfile::getLayerWaterVaporNumberDensity), py::arg("i"), "");
  cls_AtmProfile.def("getLayerBottomWaterVaporNumberDensity", static_cast<NumberDensity (AtmProfile::*)(unsigned int) const>(&AtmProfile::getLayerBottomWaterVaporNumberDensity), py::arg("i"), "");
  cls_AtmProfile.def("getLayerTopWaterVaporNumberDensity", static_cast<NumberDensity (AtmProfile::*)(unsigned int) const>(&AtmProfile::getLayerTopWaterVaporNumberDensity), py::arg("i"), "");
  cls_AtmProfile.def("setLayerWaterVaporMassDensity", static_cast<void (AtmProfile::*)(unsigned int, const MassDensity &)>(&AtmProfile::setLayerWaterVaporMassDensity), py::arg("i"), py::arg("layerWaterVapor"), R"doc(Setter for the average Water vapor density in layer i in kg/m**3 (allows to touch one layer each
 time once a profile has been defined))doc");
  cls_AtmProfile.def("setLayerWaterVaporNumberDensity", static_cast<void (AtmProfile::*)(unsigned int, const NumberDensity &)>(&AtmProfile::setLayerWaterVaporNumberDensity), py::arg("i"), py::arg("layerWaterVapor"), "");
  cls_AtmProfile.def("getPressureProfile", static_cast<std::vector<Pressure> (AtmProfile::*)() const>(&AtmProfile::getPressureProfile), R"doc(Method to get the Pressure Profile)doc");
  cls_AtmProfile.def("getLayerPressure", static_cast<Pressure (AtmProfile::*)(unsigned int) const>(&AtmProfile::getLayerPressure), py::arg("i"), R"doc(Method to access the average Pressure in layer i
@exception AtmException if the layer is not valid.)doc");
  cls_AtmProfile.def("getLayerBottomPressure", static_cast<Pressure (AtmProfile::*)(unsigned int) const>(&AtmProfile::getLayerBottomPressure), py::arg("i"), R"doc(Method to access the Pressure at bottom of layer i
@exception AtmException if the layer is not valid.)doc");
  cls_AtmProfile.def("getLayerTopPressure", static_cast<Pressure (AtmProfile::*)(unsigned int) const>(&AtmProfile::getLayerTopPressure), py::arg("i"), R"doc(Method to access the Pressure at top of layer i
@exception AtmException if the layer is not valid.)doc");
  cls_AtmProfile.def("setLayerPressure", static_cast<void (AtmProfile::*)(unsigned int, const Pressure &)>(&AtmProfile::setLayerPressure), py::arg("i"), py::arg("layerPressure"), R"doc(Setter for the average Pressure in layer i (allows to touch one layer each
 time once a profile has been defined))doc");
  cls_AtmProfile.def("getLayerCO", static_cast<NumberDensity (AtmProfile::*)(unsigned int) const>(&AtmProfile::getLayerCO), py::arg("i"), R"doc(Function to retrieve CO density in a given layer (thickness of layers
 in ThicknessProfile))doc");
  cls_AtmProfile.def("setLayerCO", static_cast<void (AtmProfile::*)(unsigned int, const NumberDensity &)>(&AtmProfile::setLayerCO), py::arg("i"), py::arg("layerCO"), R"doc(Setter for the average number density of CO in layer i in molecules/m**3 (allows to touch one layer each
 time once a profile has been defined))doc");
  cls_AtmProfile.def("getLayerO3", static_cast<NumberDensity (AtmProfile::*)(unsigned int) const>(&AtmProfile::getLayerO3), py::arg("i"), R"doc(Function to retrieve O3 density in a given layer (thickness of layers
 in ThicknessProfile))doc");
  cls_AtmProfile.def("setLayerO3", static_cast<void (AtmProfile::*)(unsigned int, const NumberDensity &)>(&AtmProfile::setLayerO3), py::arg("i"), py::arg("layerO3"), R"doc(Setter for the average number density of O3 in layer i in molecules/m**3 (allows to touch one layer each
 time once a profile has been defined))doc");
  cls_AtmProfile.def("getLayerN2O", static_cast<NumberDensity (AtmProfile::*)(unsigned int) const>(&AtmProfile::getLayerN2O), py::arg("i"), R"doc(Function to retrieve N2O density in a given layer (thickness of layers
 in ThicknessProfile))doc");
  cls_AtmProfile.def("setLayerN2O", static_cast<void (AtmProfile::*)(unsigned int, const NumberDensity &)>(&AtmProfile::setLayerN2O), py::arg("i"), py::arg("layerN2O"), R"doc(Setter for the average number density of N2O in layer i in molecules/m**3 (allows to touch one layer each
 time once a profile has been defined))doc");
  cls_AtmProfile.def("getLayerNO2", static_cast<NumberDensity (AtmProfile::*)(unsigned int) const>(&AtmProfile::getLayerNO2), py::arg("i"), R"doc(Function to retrieve NO2 density in a given layer (thickness of layers
 in ThicknessProfile))doc");
  cls_AtmProfile.def("setLayerNO2", static_cast<void (AtmProfile::*)(unsigned int, const NumberDensity &)>(&AtmProfile::setLayerNO2), py::arg("i"), py::arg("layerNO2"), R"doc(Setter for the average number density of NO2 in layer i in molecules/m**3 (allows to touch one layer each
 time once a profile has been defined))doc");
  cls_AtmProfile.def("getLayerSO2", static_cast<NumberDensity (AtmProfile::*)(unsigned int) const>(&AtmProfile::getLayerSO2), py::arg("i"), R"doc(Function to retrieve SO2 density in a given layer (thickness of layers
 in ThicknessProfile))doc");
  cls_AtmProfile.def("setLayerSO2", static_cast<void (AtmProfile::*)(unsigned int, const NumberDensity &)>(&AtmProfile::setLayerSO2), py::arg("i"), py::arg("layerSO2"), R"doc(Setter for the average number density of SO2 in layer i in molecules/m**3 (allows to touch one layer each
 time once a profile has been defined))doc");
  cls_AtmProfile.def("getLayerHCl", static_cast<NumberDensity (AtmProfile::*)(unsigned int) const>(&AtmProfile::getLayerHCl), py::arg("i"), R"doc(Function to retrieve HCl density in a given layer (thickness of layers
 in ThicknessProfile))doc");
  cls_AtmProfile.def("setLayerHCl", static_cast<void (AtmProfile::*)(unsigned int, const NumberDensity &)>(&AtmProfile::setLayerHCl), py::arg("i"), py::arg("layerHCl"), R"doc(Setter for the average number density of HCl in layer i in molecules/m**3 (allows to touch one layer each
 time once a profile has been defined))doc");
  cls_AtmProfile.def("getLayerHCN", static_cast<NumberDensity (AtmProfile::*)(unsigned int) const>(&AtmProfile::getLayerHCN), py::arg("i"), R"doc(Function to retrieve HCN density in a given layer (thickness of layers
 in ThicknessProfile))doc");
  cls_AtmProfile.def("setLayerHCN", static_cast<void (AtmProfile::*)(unsigned int, const NumberDensity &)>(&AtmProfile::setLayerHCN), py::arg("i"), py::arg("layerHCN"), R"doc(Setter for the average number density of HCN in layer i in molecules/m**3 (allows to touch one layer each
 time once a profile has been defined))doc");
  cls_AtmProfile.def("getGroundWH2O", static_cast<Length (AtmProfile::*)() const>(&AtmProfile::getGroundWH2O), R"doc(Method to get the zenith column  of water vapor. It is computed by
 simply integrating the H2O profile:
 $ column\;\;H_{2}O\;\; (mm) =\sum_{layers} \Delta z \cdot [ H_{2}O ] $)doc");
  cls_AtmProfile.def("getAltitudeThreshold", static_cast<Length (AtmProfile::*)() const>(&AtmProfile::getAltitudeThreshold), "");
  cls_AtmProfile.def("getGroundPressureThreshold", static_cast<Pressure (AtmProfile::*)() const>(&AtmProfile::getGroundPressureThreshold), "");
  cls_AtmProfile.def("getGroundTemperatureThreshold", static_cast<Temperature (AtmProfile::*)() const>(&AtmProfile::getGroundTemperatureThreshold), "");
  cls_AtmProfile.def("getTropoLapseRateThreshold", static_cast<double (AtmProfile::*)() const>(&AtmProfile::getTropoLapseRateThreshold), "");
  cls_AtmProfile.def("getRelativeHumidityThreshold", static_cast<Humidity (AtmProfile::*)() const>(&AtmProfile::getRelativeHumidityThreshold), "");
  cls_AtmProfile.def("getWvScaleHeightThreshold", static_cast<Length (AtmProfile::*)() const>(&AtmProfile::getWvScaleHeightThreshold), "");
  cls_AtmProfile.def("setAltitudeThreshold", static_cast<void (AtmProfile::*)(const Length &)>(&AtmProfile::setAltitudeThreshold), py::arg("altitudeThreshold"), "");
  cls_AtmProfile.def("setGroundPressureThreshold", static_cast<void (AtmProfile::*)(const Pressure &)>(&AtmProfile::setGroundPressureThreshold), py::arg("groundPressureThreshold"), "");
  cls_AtmProfile.def("setGroundTemperatureThreshold", static_cast<void (AtmProfile::*)(const Temperature &)>(&AtmProfile::setGroundTemperatureThreshold), py::arg("groundTemperatureThreshold"), "");
  cls_AtmProfile.def("st76", static_cast<std::vector<NumberDensity> (AtmProfile::*)(const Length &, unsigned int, unsigned int) const>(&AtmProfile::st76), py::arg("ha"), py::arg("tip"), py::arg("seasonal_diurnal"), "");
  cls_AtmProfile.def(py::init<const Length &, const Pressure &, const Temperature &, double, const Humidity &, const Length &, unsigned int>(), py::arg("altitude"), py::arg("groundPressure"), py::arg("groundTemperature"), py::arg("tropoLapseRate"), py::arg("relativeHumidity"), py::arg("wvScaleHeight"), py::arg("atmType"), R"doc(A short constructor of the atmospheric profile. With respect to the long constructor, this one considers
the following (recomended) default values: pressureStep = 10 mb,
pressureStepFactor = 1.1, topAtmProfile = 48.0 km)doc");
  cls_AtmProfile.def("setBasicAtmosphericParameters", static_cast<bool (AtmProfile::*)(const Length &, const Pressure &, const Temperature &, double, const Humidity &, const Length &)>(&AtmProfile::setBasicAtmosphericParameters), py::arg("altitude"), py::arg("groundPressure"), py::arg("groundTemperature"), py::arg("tropoLapseRate"), py::arg("relativeHumidity"), py::arg("wvScaleHeight"), R"doc(Setter to update the AtmProfile if some basic atmospheric parameter has changed.
@pre   an atmospheric profile already exists
@param altitude          the new altitude, a Length
@param groundPressure    the Pressure at the ground level
@param groundTemperature the Temperature at the ground level
@param tropoLapseRate    the tropospheric lapse rate
@param relativeHumidity  the relative Humidity
@param wvScaleHeight     the scale height of the water vapor, a Length
@return true if the atmospheric profile has been update, else false because the basic parameters have not changed
@post   the atmospheric profile has been updated, only if at least one of the basic parameters has changed

\note  there is an overriding on this method in the sub-class AbsorptionPhaseProfile which in turn
       has an  overriding in its WaterVaporRetrieval sub-class. Hence this method must not be overloaded
       in this AtmProfile class.)doc");
  cls_AtmProfile.def("setBasicAtmosphericParameterThresholds", static_cast<void (AtmProfile::*)(const Length &, const Pressure &, const Temperature &, double, const Humidity &, const Length &)>(&AtmProfile::setBasicAtmosphericParameterThresholds), py::arg("altitudeThreshold"), py::arg("groundPressureThreshold"), py::arg("groundTemperatureThreshold"), py::arg("tropoLapseRateThreshold"), py::arg("relativeHumidityThreshold"), py::arg("wvScaleHeightThreshold"), "");
  cls_AtmProfile.def(py::init<const Length &, const Pressure &, const Temperature &, double, const Humidity &, const Length &, const Pressure &, double, const Length &, unsigned int>(), py::arg("altitude"), py::arg("groundPressure"), py::arg("groundTemperature"), py::arg("tropoLapseRate"), py::arg("relativeHumidity"), py::arg("wvScaleHeight"), py::arg("pressureStep"), py::arg("pressureStepFactor"), py::arg("topAtmProfile"), py::arg("atmType"), R"doc(A long constructor of the atmospheric profile from the basic set of parameters described above.
Please note that this constructor assumes that the &altitude of the antenna is the SAME of the
weather station that provides: &groundPressure, &groundTemperature, and &relativeHumidity)doc");
  cls_AtmProfile.def(py::init<const Length &, const Pressure &, const Temperature &, double, const Humidity &, const Length &, const Pressure &, double, const Length &, unsigned int, const std::vector<Length> &, const std::vector<Temperature> &>(), py::arg("altitude"), py::arg("groundPressure"), py::arg("groundTemperature"), py::arg("tropoLapseRate"), py::arg("relativeHumidity"), py::arg("wvScaleHeight"), py::arg("pressureStep"), py::arg("pressureStepFactor"), py::arg("topAtmProfile"), py::arg("atmType"), py::arg("v_layerBoundaries"), py::arg("v_layerTemperature"), R"doc(A long constructor of the atmospheric profile from the basic set of parameters described above which,
in addition, includes user-defined temperature profile)doc");

  // ----- RefractiveIndex
  cls_RefractiveIndex.def(py::init<const RefractiveIndex &>(), py::arg("other"), "Copy constructor");
  cls_RefractiveIndex.def("__copy__", [](RefractiveIndex const &self) { return RefractiveIndex(self); });
  cls_RefractiveIndex.def("__deepcopy__", [](RefractiveIndex const &self, py::dict) { return RefractiveIndex(self); }, py::arg("memo"));
  cls_RefractiveIndex.def(py::init<>(), R"doc(The constructor has no arguments)doc");
  cls_RefractiveIndex.def("getEarthSpecificRefractivity_co", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double)>(&RefractiveIndex::getEarthSpecificRefractivity_co), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), R"doc(It returns $(2\pi\nu/c\rho_g)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{2},m^{2})$ for $CO$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, and <b>frequency</b> in GHz.)doc");
  cls_RefractiveIndex.def("getEarthSpecificRefractivity_n2o", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double)>(&RefractiveIndex::getEarthSpecificRefractivity_n2o), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), R"doc(It returns $(2\pi\nu/c\rho_g)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{2},m^{2})$ for $N_2O$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, and <b>frequency</b> in GHz.)doc");
  cls_RefractiveIndex.def("getEarthSpecificRefractivity_no2", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double)>(&RefractiveIndex::getEarthSpecificRefractivity_no2), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), R"doc(It returns $(2\pi\nu/c\rho_g)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{2},m^{2})$ for $NO_2$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, and <b>frequency</b> in GHz.)doc");
  cls_RefractiveIndex.def("getEarthSpecificRefractivity_so2", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double)>(&RefractiveIndex::getEarthSpecificRefractivity_so2), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), R"doc(It returns $(2\pi\nu/c\rho_g)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{2},m^{2})$ for $SO_2$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, and <b>frequency</b> in GHz.)doc");
  cls_RefractiveIndex.def("getEarthSpecificRefractivity_16o16o16o", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double)>(&RefractiveIndex::getEarthSpecificRefractivity_16o16o16o), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), R"doc(It returns $(2\pi\nu/c\rho_g)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{2},m^{2})$ for $^{16}O^{16}O^{16}O$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, and <b>frequency</b> in GHz.)doc");
  cls_RefractiveIndex.def("getEarthSpecificRefractivity_16o16o16o_v2", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double)>(&RefractiveIndex::getEarthSpecificRefractivity_16o16o16o_v2), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), R"doc(It returns $(2\pi\nu/c\rho_g)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{2},m^{2})$ for vibrationally excited (v2 state)
$^{16}O^{16}O^{16}O$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, and <b>frequency</b> in GHz.)doc");
  cls_RefractiveIndex.def("getEarthSpecificRefractivity_16o16o16o_v1", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double)>(&RefractiveIndex::getEarthSpecificRefractivity_16o16o16o_v1), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), R"doc(It returns $(2\pi\nu/c\rho_g)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{2},m^{2})$ for vibrationally excited (v1 state)
$^{16}O^{16}O^{16}O$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, and <b>frequency</b> in GHz.)doc");
  cls_RefractiveIndex.def("getEarthSpecificRefractivity_16o16o16o_v3", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double)>(&RefractiveIndex::getEarthSpecificRefractivity_16o16o16o_v3), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), R"doc(It returns $(2\pi\nu/c\rho_g)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{2},m^{2})$ for vibrationally excited (v3 state)
$^{16}O^{16}O^{16}O$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, and <b>frequency</b> in GHz.)doc");
  cls_RefractiveIndex.def("getEarthSpecificRefractivity_16o16o18o", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double)>(&RefractiveIndex::getEarthSpecificRefractivity_16o16o18o), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), R"doc(It returns $(2\pi\nu/c\rho_g)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{2},m^{2})$ for
$^{16}O^{16}O^{18}O$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, and <b>frequency</b> in GHz.)doc");
  cls_RefractiveIndex.def("getEarthSpecificRefractivity_16o16o17o", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double)>(&RefractiveIndex::getEarthSpecificRefractivity_16o16o17o), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), R"doc(It returns $(2\pi\nu/c\rho_g)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{2},m^{2})$ for
$^{16}O^{16}O^{17}O$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, and <b>frequency</b> in GHz.)doc");
  cls_RefractiveIndex.def("getEarthSpecificRefractivity_16o18o16o", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double)>(&RefractiveIndex::getEarthSpecificRefractivity_16o18o16o), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), R"doc(It returns $(2\pi\nu/c\rho_g)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{2},m^{2})$ for
$^{16}O^{18}O^{16}O$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, and <b>frequency</b> in GHz.)doc");
  cls_RefractiveIndex.def("getEarthSpecificRefractivity_16o17o16o", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double)>(&RefractiveIndex::getEarthSpecificRefractivity_16o17o16o), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), R"doc(It returns $(2\pi\nu/c\rho_g)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{2},m^{2})$ for
$^{16}O^{17}O^{16}O$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, and <b>frequency</b> in GHz.)doc");
  cls_RefractiveIndex.def("getEarthSpecificRefractivity_hcl", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double)>(&RefractiveIndex::getEarthSpecificRefractivity_hcl), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), R"doc(It returns $(2\pi\nu/c\rho_g)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{2},m^{2})$ for $NO_2$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, and <b>frequency</b> in GHz.)doc");
  cls_RefractiveIndex.def("getEarthSpecificRefractivity_hcn", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double)>(&RefractiveIndex::getEarthSpecificRefractivity_hcn), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), R"doc(It returns $(2\pi\nu/c\rho_g)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{2},m^{2})$ for $NO_2$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, and <b>frequency</b> in GHz.)doc");
  cls_RefractiveIndex.def("getEarthSpecificRefractivity", static_cast<std::complex<double> (RefractiveIndex::*)(unsigned int, double, double, double)>(&RefractiveIndex::getEarthSpecificRefractivity), py::arg("species"), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), R"doc(It returns $(2\pi\nu/c\rho_g)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{2},m^{2})$ for
$species$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, and <b>frequency</b> in GHz.)doc");
  cls_RefractiveIndex.def("getRefractivity_o2", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double)>(&RefractiveIndex::getRefractivity_o2), py::arg("temperature"), py::arg("pressure"), py::arg("wvpressure"), py::arg("frequency"), R"doc(It returns $(2\pi\nu/c)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{-1},m^{-1})$ for $g=O_2$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>wvpressure</b> (water vapor partial pressure) in hPa,
and <b>frequency</b> in GHz.)doc");
  cls_RefractiveIndex.def("getRefractivity_16o16o", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double)>(&RefractiveIndex::getRefractivity_16o16o), py::arg("temperature"), py::arg("pressure"), py::arg("wvpressure"), py::arg("frequency"), "");
  cls_RefractiveIndex.def("getRefractivity_16o16o_vib", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double)>(&RefractiveIndex::getRefractivity_16o16o_vib), py::arg("temperature"), py::arg("pressure"), py::arg("wvpressure"), py::arg("frequency"), "");
  cls_RefractiveIndex.def("getRefractivity_16o18o", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double)>(&RefractiveIndex::getRefractivity_16o18o), py::arg("temperature"), py::arg("pressure"), py::arg("wvpressure"), py::arg("frequency"), "");
  cls_RefractiveIndex.def("getRefractivity_16o17o", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double)>(&RefractiveIndex::getRefractivity_16o17o), py::arg("temperature"), py::arg("pressure"), py::arg("wvpressure"), py::arg("frequency"), "");
  cls_RefractiveIndex.def("getRefractivity_h2o", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double)>(&RefractiveIndex::getRefractivity_h2o), py::arg("temperature"), py::arg("pressure"), py::arg("wvpressure"), py::arg("frequency"), R"doc(It returns $(2\pi\nu/c)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{-1},m^{-1})$ for $g=H_2O$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>wvpressure</b> (water vapor partial pressure) in hPa,
and <b>frequency</b> in GHz.)doc");
  cls_RefractiveIndex.def("getRefractivity_hh16o", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double)>(&RefractiveIndex::getRefractivity_hh16o), py::arg("temperature"), py::arg("pressure"), py::arg("wvpressure"), py::arg("frequency"), "");
  cls_RefractiveIndex.def("getRefractivity_hh16ov2", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double)>(&RefractiveIndex::getRefractivity_hh16ov2), py::arg("temperature"), py::arg("pressure"), py::arg("wvpressure"), py::arg("frequency"), "");
  cls_RefractiveIndex.def("getRefractivity_hh18o", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double)>(&RefractiveIndex::getRefractivity_hh18o), py::arg("temperature"), py::arg("pressure"), py::arg("wvpressure"), py::arg("frequency"), "");
  cls_RefractiveIndex.def("getRefractivity_hh17o", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double)>(&RefractiveIndex::getRefractivity_hh17o), py::arg("temperature"), py::arg("pressure"), py::arg("wvpressure"), py::arg("frequency"), "");
  cls_RefractiveIndex.def("getRefractivity_hdo", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double)>(&RefractiveIndex::getRefractivity_hdo), py::arg("temperature"), py::arg("pressure"), py::arg("wvpressure"), py::arg("frequency"), "");
  cls_RefractiveIndex.def("getRefractivity_o3", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double)>(&RefractiveIndex::getRefractivity_o3), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), py::arg("numberdensity"), R"doc(It returns $(2\pi\nu/c)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{-1},m^{-1})$ for $g=O_3$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>frequency</b> in GHz,
and <b>numberdensity</b> in molecules of $O_3$ m$^{-3}$)doc");
  cls_RefractiveIndex.def("getEarthSpecificRefractivity_16o16o", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double)>(&RefractiveIndex::getEarthSpecificRefractivity_16o16o), py::arg("temperature"), py::arg("pressure"), py::arg("wvpressure"), py::arg("frequency"), R"doc(It returns $(2\pi\nu/c\rho_g)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{2},m^{2})$ for $^{16}O^{16}O$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>wvpressure</b> (water vapor partial pressure) in hPa, and <b>frequency</b> in GHz.)doc");
  cls_RefractiveIndex.def("getEarthSpecificRefractivity_16o16o_vib", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double)>(&RefractiveIndex::getEarthSpecificRefractivity_16o16o_vib), py::arg("temperature"), py::arg("pressure"), py::arg("wvpressure"), py::arg("frequency"), R"doc(It returns $(2\pi\nu/c\rho_g)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{2},m^{2})$ for the first vibrationally excited state
of $^{16}O^{16}O$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>wvpressure</b> (water vapor partial pressure) in hPa, and <b>frequency</b> in GHz.)doc");
  cls_RefractiveIndex.def("getEarthSpecificRefractivity_16o18o", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double)>(&RefractiveIndex::getEarthSpecificRefractivity_16o18o), py::arg("temperature"), py::arg("pressure"), py::arg("wvpressure"), py::arg("frequency"), R"doc(It returns $(2\pi\nu/c\rho_g)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{2},m^{2})$ for $^{16}O^{18}O$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>wvpressure</b> (water vapor partial pressure) in hPa, and <b>frequency</b> in GHz.)doc");
  cls_RefractiveIndex.def("getEarthSpecificRefractivity_16o17o", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double)>(&RefractiveIndex::getEarthSpecificRefractivity_16o17o), py::arg("temperature"), py::arg("pressure"), py::arg("wvpressure"), py::arg("frequency"), R"doc(It returns $(2\pi\nu/c\rho_g)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{2},m^{2})$ for $^{16}O^{17}O$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>wvpressure</b> (water vapor partial pressure) in hPa, and <b>frequency</b> in GHz.)doc");
  cls_RefractiveIndex.def("getEarthSpecificRefractivity_co", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double, unsigned int)>(&RefractiveIndex::getEarthSpecificRefractivity_co), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), py::arg("width"), py::arg("n"), R"doc(It returns $(2\pi\nu/c\rho_g)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{2},m^{2})$ for $CO$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>frequency</b> in GHz,
<b>width</b> (channel width around <b>frequency</b>) in GHz, and <b>n</b> (number of frequency points for averaging within <b>width</b>).)doc");
  cls_RefractiveIndex.def("getRefractivity_co", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double)>(&RefractiveIndex::getRefractivity_co), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), py::arg("numberdensity"), R"doc(It returns $(2\pi\nu/c)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{-1},m^{-1})$ for $CO$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>frequency</b> in GHz,
and <b>numberdensity</b> in molecules of $CO$ m$^{-3}$.)doc");
  cls_RefractiveIndex.def("getEarthSpecificRefractivity_n2o", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double, unsigned int)>(&RefractiveIndex::getEarthSpecificRefractivity_n2o), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), py::arg("width"), py::arg("n"), R"doc(It returns $(2\pi\nu/c\rho_g)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{2},m^{2})$ for $N_2O$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>frequency</b> in GHz,
<b>width</b> (channel width around <b>frequency</b>) in GHz, and <b>n</b> (number of frequency points for averaging within <b>width</b>).)doc");
  cls_RefractiveIndex.def("getRefractivity_n2o", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double)>(&RefractiveIndex::getRefractivity_n2o), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), py::arg("numberdensity"), R"doc(It returns $(2\pi\nu/c)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{-1},m^{-1})$ for $N_2O$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>frequency</b> in GHz,
and <b>numberdensity</b> in molecules of $N_2O$ m$^{-3}$.)doc");
  cls_RefractiveIndex.def("getEarthSpecificRefractivity_no2", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double, unsigned int)>(&RefractiveIndex::getEarthSpecificRefractivity_no2), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), py::arg("width"), py::arg("n"), R"doc(It returns $(2\pi\nu/c\rho_g)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{2},m^{2})$ for $NO_2$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>frequency</b> in GHz,
<b>width</b> (channel width around <b>frequency</b>) in GHz, and <b>n</b> (number of frequency points for averaging within <b>width</b>).)doc");
  cls_RefractiveIndex.def("getRefractivity_no2", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double)>(&RefractiveIndex::getRefractivity_no2), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), py::arg("numberdensity"), R"doc(It returns $(2\pi\nu/c)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{-1},m^{-1})$ for $NO_2$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>frequency</b> in GHz,
and <b>numberdensity</b> in molecules of $NO_2$ m$^{-3}$.)doc");
  cls_RefractiveIndex.def("getEarthSpecificRefractivity_so2", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double, unsigned int)>(&RefractiveIndex::getEarthSpecificRefractivity_so2), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), py::arg("width"), py::arg("n"), R"doc(It returns $(2\pi\nu/c\rho_g)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{2},m^{2})$ for $SO_2$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>frequency</b> in GHz,
<b>width</b> (channel width around <b>frequency</b>) in GHz, and <b>n</b> (number of frequency points for averaging within <b>width</b>).)doc");
  cls_RefractiveIndex.def("getRefractivity_so2", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double)>(&RefractiveIndex::getRefractivity_so2), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), py::arg("numberdensity"), R"doc(It returns $(2\pi\nu/c)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{-1},m^{-1})$ for $SO_2$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>frequency</b> in GHz,
and <b>numberdensity</b> in molecules of $SO_2$ m$^{-3}$.)doc");
  cls_RefractiveIndex.def("getRefractivity_cnth2o", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double)>(&RefractiveIndex::getRefractivity_cnth2o), py::arg("temperature"), py::arg("pressure"), py::arg("wvpressure"), py::arg("frequency"), R"doc(It returns $(2\pi\nu/c\rho_g)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{2},m^{2})$ corresponding to the contribution of
the "wet" collision induced ($O_2-H_2O$ and $N_2-H_2O$) processes (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>wvpressure</b> (water vapor partial pressure) in hPa, and <b>frequency</b> in GHz.)doc");
  cls_RefractiveIndex.def("getRefractivity_cntdry", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double)>(&RefractiveIndex::getRefractivity_cntdry), py::arg("temperature"), py::arg("pressure"), py::arg("wvpressure"), py::arg("frequency"), R"doc(It returns $(2\pi\nu/c\rho_g)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{2},m^{2})$ corresponding to the contribution of
the "dry" collision induced ($O_2-O_2$, $N_2-N_2$ and $N_2-O_2$) processes (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>wvpressure</b> (water vapor partial pressure) in hPa, and <b>frequency</b> in GHz.)doc");
  cls_RefractiveIndex.def("getEarthSpecificRefractivity_hh16o", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double)>(&RefractiveIndex::getEarthSpecificRefractivity_hh16o), py::arg("temperature"), py::arg("pressure"), py::arg("wvpressure"), py::arg("frequency"), R"doc(It returns $(2\pi\nu/c\rho_g)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{2},m^{2})$ for $H_2^{16}$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>wvpressure</b> (water vapor partial pressure) in hPa, and <b>frequency</b> in GHz.)doc");
  cls_RefractiveIndex.def("getEarthSpecificRefractivity_hh16ov2", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double)>(&RefractiveIndex::getEarthSpecificRefractivity_hh16ov2), py::arg("temperature"), py::arg("pressure"), py::arg("wvpressure"), py::arg("frequency"), R"doc(It returns $(2\pi\nu/c\rho_g)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{2},m^{2})$ for the v2 vibrational state of $H_2^{16}$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>wvpressure</b> (water vapor partial pressure) in hPa, and <b>frequency</b> in GHz.)doc");
  cls_RefractiveIndex.def("getEarthSpecificRefractivity_hh18o", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double)>(&RefractiveIndex::getEarthSpecificRefractivity_hh18o), py::arg("temperature"), py::arg("pressure"), py::arg("wvpressure"), py::arg("frequency"), R"doc(It returns $(2\pi\nu/c\rho_g)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{2},m^{2})$ for $H_2^{18}$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>wvpressure</b> (water vapor partial pressure) in hPa, and <b>frequency</b> in GHz.)doc");
  cls_RefractiveIndex.def("getEarthSpecificRefractivity_hh17o", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double)>(&RefractiveIndex::getEarthSpecificRefractivity_hh17o), py::arg("temperature"), py::arg("pressure"), py::arg("wvpressure"), py::arg("frequency"), R"doc(It returns $(2\pi\nu/c\rho_g)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{2},m^{2})$ for $H_2^{17}$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>wvpressure</b> (water vapor partial pressure) in hPa, and <b>frequency</b> in GHz.)doc");
  cls_RefractiveIndex.def("getEarthSpecificRefractivity_hdo", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double)>(&RefractiveIndex::getEarthSpecificRefractivity_hdo), py::arg("temperature"), py::arg("pressure"), py::arg("wvpressure"), py::arg("frequency"), R"doc(It returns $(2\pi\nu/c\rho_g)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{2},m^{2})$ for $HDO$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>wvpressure</b> (water vapor partial pressure) in hPa, and <b>frequency</b> in GHz.)doc");
  cls_RefractiveIndex.def("getEarthSpecificRefractivity_16o16o16o", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double, unsigned int)>(&RefractiveIndex::getEarthSpecificRefractivity_16o16o16o), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), py::arg("width"), py::arg("n"), R"doc(It returns $(2\pi\nu/c\rho_g)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{2},m^{2})$ for $^{16}O^{16}O^{16}O$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>frequency</b> in GHz,
<b>width</b> (channel width around <b>frequency</b>) in GHz, and <b>n</b> (number of frequency points for averaging within <b>width</b>).)doc");
  cls_RefractiveIndex.def("getRefractivity_16o16o16o", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double)>(&RefractiveIndex::getRefractivity_16o16o16o), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), py::arg("numberdensity"), R"doc(It returns $(2\pi\nu/c)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{-1},m^{-1})$ for $^{16}O^{16}O^{16}O$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>frequency</b> in GHz,
and <b>numberdensity</b> in molecules of $O_3$ m$^{-3}$.)doc");
  cls_RefractiveIndex.def("getEarthSpecificRefractivity_16o16o16o_v2", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double, unsigned int)>(&RefractiveIndex::getEarthSpecificRefractivity_16o16o16o_v2), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), py::arg("width"), py::arg("n"), R"doc(It returns $(2\pi\nu/c\rho_g)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{2},m^{2})$ for vibrationally excited (v2 state)
$^{16}O^{16}O^{16}O$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>frequency</b> in GHz,
<b>width</b> (channel width around <b>frequency</b>) in GHz, and <b>n</b> (number of frequency points for averaging within <b>width</b>).)doc");
  cls_RefractiveIndex.def("getRefractivity_16o16o16o_v2", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double)>(&RefractiveIndex::getRefractivity_16o16o16o_v2), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), py::arg("numberdensity"), R"doc(It returns $(2\pi\nu/c)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{-1},m^{-1})$ for vibrationally excited (v2 state)
$^{16}O^{16}O^{16}O$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>frequency</b> in GHz,
and <b>numberdensity</b> in molecules of $^{16}O^{16}O^{16}O$  $v=2$    m$^{-3}$.)doc");
  cls_RefractiveIndex.def("getEarthSpecificRefractivity_16o16o16o_v1", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double, unsigned int)>(&RefractiveIndex::getEarthSpecificRefractivity_16o16o16o_v1), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), py::arg("width"), py::arg("n"), R"doc(It returns $(2\pi\nu/c\rho_g)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{2},m^{2})$ for vibrationally excited (v1 state)
$^{16}O^{16}O^{16}O$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>frequency</b> in GHz,
<b>width</b> (channel width around <b>frequency</b>) in GHz, and <b>n</b> (number of frequency points for averaging within <b>width</b>).)doc");
  cls_RefractiveIndex.def("getRefractivity_16o16o16o_v1", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double)>(&RefractiveIndex::getRefractivity_16o16o16o_v1), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), py::arg("numberdensity"), R"doc(It returns $(2\pi\nu/c)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{-1},m^{-1})$ for vibrationally excited (v1 state)
$^{16}O^{16}O^{16}O$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>frequency</b> in GHz,
and <b>numberdensity</b> in molecules of $^{16}O^{16}O^{16}O$  $v=1$   m$^{-3}$.)doc");
  cls_RefractiveIndex.def("getEarthSpecificRefractivity_16o16o16o_v3", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double, unsigned int)>(&RefractiveIndex::getEarthSpecificRefractivity_16o16o16o_v3), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), py::arg("width"), py::arg("n"), R"doc(It returns $(2\pi\nu/c\rho_g)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{2},m^{2})$ for vibrationally excited (v3 state)
$^{16}O^{16}O^{16}O$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>frequency</b> in GHz,
<b>width</b> (channel width around <b>frequency</b>) in GHz, and <b>n</b> (number of frequency points for averaging within <b>width</b>).)doc");
  cls_RefractiveIndex.def("getRefractivity_16o16o16o_v3", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double)>(&RefractiveIndex::getRefractivity_16o16o16o_v3), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), py::arg("numberdensity"), R"doc(It returns $(2\pi\nu/c)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{-1},m^{-1})$ for vibrationally excited (v3 state)
$^{16}O^{16}O^{16}O$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>frequency</b> in GHz,
and <b>numberdensity</b> in molecules of $^{16}O^{16}O^{16}O$ $v=3$  m$^{-3}$.)doc");
  cls_RefractiveIndex.def("getEarthSpecificRefractivity_16o16o18o", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double, unsigned int)>(&RefractiveIndex::getEarthSpecificRefractivity_16o16o18o), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), py::arg("width"), py::arg("n"), R"doc(It returns $(2\pi\nu/c\rho_g)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{2},m^{2})$ for
$^{16}O^{16}O^{18}O$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>frequency</b> in GHz,
<b>width</b> (channel width around <b>frequency</b>) in GHz, and <b>n</b> (number of frequency points for averaging within <b>width</b>).)doc");
  cls_RefractiveIndex.def("getRefractivity_16o16o18o", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double)>(&RefractiveIndex::getRefractivity_16o16o18o), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), py::arg("numberdensity"), R"doc(It returns $(2\pi\nu/c)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{-1},m^{-1})$ for
$^{16}O^{16}O^{18}O$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>frequency</b> in GHz,
and <b>numberdensity</b> in molecules of $^{16}O^{16}O^{18}O$ m$^{-3}$.)doc");
  cls_RefractiveIndex.def("getEarthSpecificRefractivity_16o16o17o", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double, unsigned int)>(&RefractiveIndex::getEarthSpecificRefractivity_16o16o17o), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), py::arg("width"), py::arg("n"), R"doc(It returns $(2\pi\nu/c\rho_g)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{2},m^{2})$ for
$^{16}O^{16}O^{17}O$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>frequency</b> in GHz,
<b>width</b> (channel width around <b>frequency</b>) in GHz, and <b>n</b> (number of frequency points for averaging within <b>width</b>).)doc");
  cls_RefractiveIndex.def("getRefractivity_16o16o17o", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double)>(&RefractiveIndex::getRefractivity_16o16o17o), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), py::arg("numberdensity"), R"doc(It returns $(2\pi\nu/c)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{-1},m^{-1})$ for
$^{16}O^{16}O^{17}O$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>frequency</b> in GHz,
and <b>numberdensity</b> in molecules of $^{16}O^{16}O^{17}O$ m$^{-3}$.)doc");
  cls_RefractiveIndex.def("getEarthSpecificRefractivity_16o18o16o", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double, unsigned int)>(&RefractiveIndex::getEarthSpecificRefractivity_16o18o16o), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), py::arg("width"), py::arg("n"), R"doc(It returns $(2\pi\nu/c\rho_g)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{2},m^{2})$ for
$^{16}O^{18}O^{16}O$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>frequency</b> in GHz,
<b>width</b> (channel width around <b>frequency</b>) in GHz, and <b>n</b> (number of frequency points for averaging within <b>width</b>).)doc");
  cls_RefractiveIndex.def("getRefractivity_16o18o16o", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double)>(&RefractiveIndex::getRefractivity_16o18o16o), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), py::arg("numberdensity"), R"doc(It returns $(2\pi\nu/c)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{-1},m^{-1})$ for
$^{16}O^{18}O^{16}O$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>frequency</b> in GHz,
and <b>numberdensity</b> in molecules of $^{16}O^{18}O^{16}O$ m$^{-3}$.)doc");
  cls_RefractiveIndex.def("getEarthSpecificRefractivity_16o17o16o", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double, unsigned int)>(&RefractiveIndex::getEarthSpecificRefractivity_16o17o16o), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), py::arg("width"), py::arg("n"), R"doc(It returns $(2\pi\nu/c\rho_g)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{2},m^{2})$ for
$^{16}O^{17}O^{16}O$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>frequency</b> in GHz,
<b>width</b> (channel width around <b>frequency</b>) in GHz, and <b>n</b> (number of frequency points for averaging within <b>width</b>).)doc");
  cls_RefractiveIndex.def("getRefractivity_16o17o16o", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double)>(&RefractiveIndex::getRefractivity_16o17o16o), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), py::arg("numberdensity"), R"doc(It returns $(2\pi\nu/c)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{-1},m^{-1})$ for
$^{16}O^{17}O^{16}O$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>frequency</b> in GHz,
and <b>numberdensity</b> in molecules of $^{16}O^{17}O^{16}O$ m$^{-3}$.)doc");
  cls_RefractiveIndex.def("getEarthSpecificRefractivity_hcl", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double, unsigned int)>(&RefractiveIndex::getEarthSpecificRefractivity_hcl), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), py::arg("width"), py::arg("n"), R"doc(It returns $(2\pi\nu/c\rho_g)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{2},m^{2})$ for $NO_2$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>frequency</b> in GHz,
<b>width</b> (channel width around <b>frequency</b>) in GHz, and <b>n</b> (number of frequency points for averaging within <b>width</b>).)doc");
  cls_RefractiveIndex.def("getRefractivity_hcl", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double)>(&RefractiveIndex::getRefractivity_hcl), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), py::arg("numberdensity"), R"doc(It returns $(2\pi\nu/c)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{-1},m^{-1})$ for $NO_2$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>frequency</b> in GHz,
and <b>numberdensity</b> in molecules of $NO_2$ m$^{-3}$.)doc");
  cls_RefractiveIndex.def("getEarthSpecificRefractivity_hcn", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double, unsigned int)>(&RefractiveIndex::getEarthSpecificRefractivity_hcn), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), py::arg("width"), py::arg("n"), R"doc(It returns $(2\pi\nu/c\rho_g)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{2},m^{2})$ for $NO_2$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>frequency</b> in GHz,
<b>width</b> (channel width around <b>frequency</b>) in GHz, and <b>n</b> (number of frequency points for averaging within <b>width</b>).)doc");
  cls_RefractiveIndex.def("getRefractivity_hcn", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double)>(&RefractiveIndex::getRefractivity_hcn), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), py::arg("numberdensity"), R"doc(It returns $(2\pi\nu/c)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{-1},m^{-1})$ for $NO_2$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>frequency</b> in GHz,
and <b>numberdensity</b> in molecules of $NO_2$ m$^{-3}$.)doc");
  cls_RefractiveIndex.def("getRefractivity", static_cast<std::complex<double> (RefractiveIndex::*)(unsigned int, double, double, double, double)>(&RefractiveIndex::getRefractivity), py::arg("species"), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), py::arg("numberdensity"), R"doc(It returns $(2\pi\nu/c)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{-1},m^{-1})$ for
$species$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>frequency</b> in GHz,
and <b>numberdensity</b> in molecules of $species$ m$^{-3}$.)doc");
  cls_RefractiveIndex.def("getRefractivity_o2", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double, double, unsigned int)>(&RefractiveIndex::getRefractivity_o2), py::arg("temperature"), py::arg("pressure"), py::arg("wvpressure"), py::arg("frequency"), py::arg("width"), py::arg("n"), R"doc(It returns $(2\pi\nu/c)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{-1},m^{-1})$ for $g=O_2$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>wvpressure</b> (water vapor partial pressure) in hPa,
<b>frequency</b> in GHz, <b>width</b> (channel width around <b>frequency</b>) in GHz,
and <b>n</b> (number of frequency points for averaging within <b>width</b>).)doc");
  cls_RefractiveIndex.def("getRefractivity_16o16o", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double, double, unsigned int)>(&RefractiveIndex::getRefractivity_16o16o), py::arg("temperature"), py::arg("pressure"), py::arg("wvpressure"), py::arg("frequency"), py::arg("width"), py::arg("n"), "");
  cls_RefractiveIndex.def("getRefractivity_16o16o_vib", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double, double, unsigned int)>(&RefractiveIndex::getRefractivity_16o16o_vib), py::arg("temperature"), py::arg("pressure"), py::arg("wvpressure"), py::arg("frequency"), py::arg("width"), py::arg("n"), "");
  cls_RefractiveIndex.def("getRefractivity_16o18o", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double, double, unsigned int)>(&RefractiveIndex::getRefractivity_16o18o), py::arg("temperature"), py::arg("pressure"), py::arg("wvpressure"), py::arg("frequency"), py::arg("width"), py::arg("n"), "");
  cls_RefractiveIndex.def("getRefractivity_16o17o", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double, double, unsigned int)>(&RefractiveIndex::getRefractivity_16o17o), py::arg("temperature"), py::arg("pressure"), py::arg("wvpressure"), py::arg("frequency"), py::arg("width"), py::arg("n"), "");
  cls_RefractiveIndex.def("getRefractivity_h2o", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double, double, unsigned int)>(&RefractiveIndex::getRefractivity_h2o), py::arg("temperature"), py::arg("pressure"), py::arg("wvpressure"), py::arg("frequency"), py::arg("width"), py::arg("n"), R"doc(It returns $(2\pi\nu/c)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{-1},m^{-1})$ for $g=H_2O$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>wvpressure</b> (water vapor partial pressure) in hPa,
<b>frequency</b> in GHz, <b>width</b> (channel width around <b>frequency</b>) in GHz,
and <b>n</b> (number of frequency points for averaging within <b>width</b>).)doc");
  cls_RefractiveIndex.def("getRefractivity_hh16o", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double, double, unsigned int)>(&RefractiveIndex::getRefractivity_hh16o), py::arg("temperature"), py::arg("pressure"), py::arg("wvpressure"), py::arg("frequency"), py::arg("width"), py::arg("n"), "");
  cls_RefractiveIndex.def("getRefractivity_hh16ov2", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double, double, unsigned int)>(&RefractiveIndex::getRefractivity_hh16ov2), py::arg("temperature"), py::arg("pressure"), py::arg("wvpressure"), py::arg("frequency"), py::arg("width"), py::arg("n"), "");
  cls_RefractiveIndex.def("getRefractivity_hh17o", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double, double, unsigned int)>(&RefractiveIndex::getRefractivity_hh17o), py::arg("temperature"), py::arg("pressure"), py::arg("wvpressure"), py::arg("frequency"), py::arg("width"), py::arg("n"), "");
  cls_RefractiveIndex.def("getRefractivity_hdo", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double, double, unsigned int)>(&RefractiveIndex::getRefractivity_hdo), py::arg("temperature"), py::arg("pressure"), py::arg("wvpressure"), py::arg("frequency"), py::arg("width"), py::arg("n"), "");
  cls_RefractiveIndex.def("getRefractivity_o3", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double, unsigned int, double)>(&RefractiveIndex::getRefractivity_o3), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), py::arg("width"), py::arg("n"), py::arg("numberdensity"), R"doc(It returns $(2\pi\nu/c)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{-1},m^{-1})$ for $g=O_3$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>frequency</b> in GHz,
<b>width</b> (channel width around <b>frequency</b>) in GHz, <b>n</b> (number of frequency points for averaging within <b>width</b>),
and <b>numberdensity</b> in molecules of $O_3$ m$^{-3}$)doc");
  cls_RefractiveIndex.def("getEarthSpecificRefractivity_16o16o", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double, double, unsigned int)>(&RefractiveIndex::getEarthSpecificRefractivity_16o16o), py::arg("temperature"), py::arg("pressure"), py::arg("wvpressure"), py::arg("frequency"), py::arg("width"), py::arg("n"), R"doc(It returns $(2\pi\nu/c\rho_g)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{2},m^{2})$ for $^{16}O^{16}O$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>wvpressure</b> (water vapor partial pressure) in hPa, <b>frequency</b> in GHz,
<b>width</b> (channel width around <b>frequency</b>) in GHz, and <b>n</b> (number of frequency points for averaging within <b>width</b>).)doc");
  cls_RefractiveIndex.def("getEarthSpecificRefractivity_16o16o_vib", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double, double, unsigned int)>(&RefractiveIndex::getEarthSpecificRefractivity_16o16o_vib), py::arg("temperature"), py::arg("pressure"), py::arg("wvpressure"), py::arg("frequency"), py::arg("width"), py::arg("n"), R"doc(It returns $(2\pi\nu/c\rho_g)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{2},m^{2})$ for the first vibrationally excited state
of $^{16}O^{16}O$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>wvpressure</b> (water vapor partial pressure) in hPa, <b>frequency</b> in GHz,
<b>width</b> (channel width around <b>frequency</b>) in GHz, and <b>n</b> (number of frequency points for averaging within <b>width</b>).)doc");
  cls_RefractiveIndex.def("getEarthSpecificRefractivity_16o18o", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double, double, unsigned int)>(&RefractiveIndex::getEarthSpecificRefractivity_16o18o), py::arg("temperature"), py::arg("pressure"), py::arg("wvpressure"), py::arg("frequency"), py::arg("width"), py::arg("n"), R"doc(It returns $(2\pi\nu/c\rho_g)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{2},m^{2})$ for $^{16}O^{18}O$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>wvpressure</b> (water vapor partial pressure) in hPa, <b>frequency</b> in GHz,
<b>width</b> (channel width around <b>frequency</b>) in GHz, and <b>n</b> (number of frequency points for averaging within <b>width</b>).)doc");
  cls_RefractiveIndex.def("getEarthSpecificRefractivity_16o17o", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double, double, unsigned int)>(&RefractiveIndex::getEarthSpecificRefractivity_16o17o), py::arg("temperature"), py::arg("pressure"), py::arg("wvpressure"), py::arg("frequency"), py::arg("width"), py::arg("n"), R"doc(It returns $(2\pi\nu/c\rho_g)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{2},m^{2})$ for $^{16}O^{17}O$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>wvpressure</b> (water vapor partial pressure) in hPa, <b>frequency</b> in GHz,
<b>width</b> (channel width around <b>frequency</b>) in GHz, and <b>n</b> (number of frequency points for averaging within <b>width</b>).)doc");
  cls_RefractiveIndex.def("getRefractivity_co", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double, unsigned int, double)>(&RefractiveIndex::getRefractivity_co), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), py::arg("width"), py::arg("n"), py::arg("numberdensity"), R"doc(It returns $(2\pi\nu/c)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{-1},m^{-1})$ for $CO$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>frequency</b> in GHz,
<b>width</b> (channel width around <b>frequency</b>) in GHz, <b>n</b> (number of frequency points for averaging within <b>width</b>),
and <b>numberdensity</b> in molecules of $CO$ m$^{-3}$.)doc");
  cls_RefractiveIndex.def("getRefractivity_n2o", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double, unsigned int, double)>(&RefractiveIndex::getRefractivity_n2o), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), py::arg("width"), py::arg("n"), py::arg("numberdensity"), R"doc(It returns $(2\pi\nu/c)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{-1},m^{-1})$ for $N_2O$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>frequency</b> in GHz,
<b>width</b> (channel width around <b>frequency</b>) in GHz, <b>n</b> (number of frequency points for averaging within <b>width</b>),
and <b>numberdensity</b> in molecules of $N_2O$ m$^{-3}$.)doc");
  cls_RefractiveIndex.def("getRefractivity_no2", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double, unsigned int, double)>(&RefractiveIndex::getRefractivity_no2), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), py::arg("width"), py::arg("n"), py::arg("numberdensity"), R"doc(It returns $(2\pi\nu/c)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{-1},m^{-1})$ for $NO_2$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>frequency</b> in GHz,
<b>width</b> (channel width around <b>frequency</b>) in GHz, <b>n</b> (number of frequency points for averaging within <b>width</b>),
and <b>numberdensity</b> in molecules of $NO_2$ m$^{-3}$.)doc");
  cls_RefractiveIndex.def("getRefractivity_so2", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double, unsigned int, double)>(&RefractiveIndex::getRefractivity_so2), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), py::arg("width"), py::arg("n"), py::arg("numberdensity"), R"doc(It returns $(2\pi\nu/c)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{-1},m^{-1})$ for $SO_2$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>frequency</b> in GHz,
<b>width</b> (channel width around <b>frequency</b>) in GHz, <b>n</b> (number of frequency points for averaging within <b>width</b>),
and <b>numberdensity</b> in molecules of $SO_2$ m$^{-3}$.)doc");
  cls_RefractiveIndex.def("getRefractivity_cnth2o", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double, double, unsigned int)>(&RefractiveIndex::getRefractivity_cnth2o), py::arg("temperature"), py::arg("pressure"), py::arg("wvpressure"), py::arg("frequency"), py::arg("width"), py::arg("n"), R"doc(It returns $(2\pi\nu/c\rho_g)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{2},m^{2})$ corresponding to the contribution of
the "wet" collision induced ($O_2-H_2O$ and $N_2-H_2O$) processes (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>wvpressure</b> (water vapor partial pressure) in hPa, <b>frequency</b> in GHz,
<b>width</b> (channel width around <b>frequency</b>) in GHz, and <b>n</b> (number of frequency points for averaging within <b>width</b>).)doc");
  cls_RefractiveIndex.def("getRefractivity_cntdry", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double, double, unsigned int)>(&RefractiveIndex::getRefractivity_cntdry), py::arg("temperature"), py::arg("pressure"), py::arg("wvpressure"), py::arg("frequency"), py::arg("width"), py::arg("n"), R"doc(It returns $(2\pi\nu/c\rho_g)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{2},m^{2})$ corresponding to the contribution of
the "dry" collision induced ($O_2-O_2$, $N_2-N_2$ and $N_2-O_2$) processes (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>wvpressure</b> (water vapor partial pressure) in hPa, <b>frequency</b> in GHz,
<b>width</b> (channel width around <b>frequency</b>) in GHz, and <b>n</b> (number of frequency points for averaging within <b>width</b>).)doc");
  cls_RefractiveIndex.def("getEarthSpecificRefractivity_hh16o", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double, double, unsigned int)>(&RefractiveIndex::getEarthSpecificRefractivity_hh16o), py::arg("temperature"), py::arg("pressure"), py::arg("wvpressure"), py::arg("frequency"), py::arg("width"), py::arg("n"), R"doc(It returns $(2\pi\nu/c\rho_g)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{2},m^{2})$ for $H_2^{16}$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>wvpressure</b> (water vapor partial pressure) in hPa, <b>frequency</b> in GHz,
<b>width</b> (channel width around <b>frequency</b>) in GHz, and <b>n</b> (number of frequency points for averaging within <b>width</b>).)doc");
  cls_RefractiveIndex.def("getEarthSpecificRefractivity_hh16ov2", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double, double, unsigned int)>(&RefractiveIndex::getEarthSpecificRefractivity_hh16ov2), py::arg("temperature"), py::arg("pressure"), py::arg("wvpressure"), py::arg("frequency"), py::arg("width"), py::arg("n"), R"doc(It returns $(2\pi\nu/c\rho_g)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{2},m^{2})$ for the v2 vibrational state of $H_2^{16}$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>wvpressure</b> (water vapor partial pressure) in hPa, <b>frequency</b> in GHz,
<b>width</b> (channel width around <b>frequency</b>) in GHz, and <b>n</b> (number of frequency points for averaging within <b>width</b>).)doc");
  cls_RefractiveIndex.def("getEarthSpecificRefractivity_hh18o", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double, double, unsigned int)>(&RefractiveIndex::getEarthSpecificRefractivity_hh18o), py::arg("temperature"), py::arg("pressure"), py::arg("wvpressure"), py::arg("frequency"), py::arg("width"), py::arg("n"), R"doc(It returns $(2\pi\nu/c\rho_g)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{2},m^{2})$ for $H_2^{18}$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>wvpressure</b> (water vapor partial pressure) in hPa, <b>frequency</b> in GHz,
<b>width</b> (channel width around <b>frequency</b>) in GHz, and <b>n</b> (number of frequency points for averaging within <b>width</b>).)doc");
  cls_RefractiveIndex.def("getEarthSpecificRefractivity_hh17o", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double, double, unsigned int)>(&RefractiveIndex::getEarthSpecificRefractivity_hh17o), py::arg("temperature"), py::arg("pressure"), py::arg("wvpressure"), py::arg("frequency"), py::arg("width"), py::arg("n"), R"doc(It returns $(2\pi\nu/c\rho_g)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{2},m^{2})$ for $H_2^{17}$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>wvpressure</b> (water vapor partial pressure) in hPa, <b>frequency</b> in GHz,
<b>width</b> (channel width around <b>frequency</b>) in GHz, and <b>n</b> (number of frequency points for averaging within <b>width</b>).)doc");
  cls_RefractiveIndex.def("getEarthSpecificRefractivity_hdo", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double, double, unsigned int)>(&RefractiveIndex::getEarthSpecificRefractivity_hdo), py::arg("temperature"), py::arg("pressure"), py::arg("wvpressure"), py::arg("frequency"), py::arg("width"), py::arg("n"), R"doc(It returns $(2\pi\nu/c\rho_g)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{2},m^{2})$ for $HDO$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>wvpressure</b> (water vapor partial pressure) in hPa, <b>frequency</b> in GHz,
<b>width</b> (channel width around <b>frequency</b>) in GHz, and <b>n</b> (number of frequency points for averaging within <b>width</b>).)doc");
  cls_RefractiveIndex.def("getRefractivity_16o16o16o", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double, unsigned int, double)>(&RefractiveIndex::getRefractivity_16o16o16o), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), py::arg("width"), py::arg("n"), py::arg("numberdensity"), R"doc(It returns $(2\pi\nu/c)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{-1},m^{-1})$ for $^{16}O^{16}O^{16}O$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>frequency</b> in GHz,
<b>width</b> (channel width around <b>frequency</b>) in GHz, <b>n</b> (number of frequency points for averaging within <b>width</b>),
and <b>numberdensity</b> in molecules of $O_3$ m$^{-3}$.)doc");
  cls_RefractiveIndex.def("getRefractivity_16o16o16o_v2", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double, unsigned int, double)>(&RefractiveIndex::getRefractivity_16o16o16o_v2), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), py::arg("width"), py::arg("n"), py::arg("numberdensity"), R"doc(It returns $(2\pi\nu/c)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{-1},m^{-1})$ for vibrationally excited (v2 state)
$^{16}O^{16}O^{16}O$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>frequency</b> in GHz,
<b>width</b> (channel width around <b>frequency</b>) in GHz, <b>n</b> (number of frequency points for averaging within <b>width</b>),
and <b>numberdensity</b> in molecules of $^{16}O^{16}O^{16}O$  $v=2$   m$^{-3}$.)doc");
  cls_RefractiveIndex.def("getRefractivity_16o16o16o_v1", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double, unsigned int, double)>(&RefractiveIndex::getRefractivity_16o16o16o_v1), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), py::arg("width"), py::arg("n"), py::arg("numberdensity"), R"doc(It returns $(2\pi\nu/c)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{-1},m^{-1})$ for vibrationally excited (v1 state)
$^{16}O^{16}O^{16}O$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>frequency</b> in GHz,
<b>width</b> (channel width around <b>frequency</b>) in GHz, <b>n</b> (number of frequency points for averaging within <b>width</b>),
and <b>numberdensity</b> in molecules of $^{16}O^{16}O^{16}O$ $v=1$  m$^{-3}$.)doc");
  cls_RefractiveIndex.def("getRefractivity_16o16o16o_v3", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double, unsigned int, double)>(&RefractiveIndex::getRefractivity_16o16o16o_v3), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), py::arg("width"), py::arg("n"), py::arg("numberdensity"), R"doc(It returns $(2\pi\nu/c)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{-1},m^{-1})$ for vibrationally excited (v3 state)
$^{16}O^{16}O^{16}O$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>frequency</b> in GHz,
<b>width</b> (channel width around <b>frequency</b>) in GHz, <b>n</b> (number of frequency points for averaging within <b>width</b>),
and <b>numberdensity</b> in molecules of $^{16}O^{16}O^{16}O$ $v=3$  m$^{-3}$.)doc");
  cls_RefractiveIndex.def("getRefractivity_16o16o18o", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double, unsigned int, double)>(&RefractiveIndex::getRefractivity_16o16o18o), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), py::arg("width"), py::arg("n"), py::arg("numberdensity"), R"doc(It returns $(2\pi\nu/c)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{-1},m^{-1})$ for
$^{16}O^{16}O^{18}O$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>frequency</b> in GHz,
<b>width</b> (channel width around <b>frequency</b>) in GHz, <b>n</b> (number of frequency points for averaging within <b>width</b>),
and <b>numberdensity</b> in molecules of $^{16}O^{16}O^{18}O$ m$^{-3}$.)doc");
  cls_RefractiveIndex.def("getRefractivity_16o16o17o", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double, unsigned int, double)>(&RefractiveIndex::getRefractivity_16o16o17o), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), py::arg("width"), py::arg("n"), py::arg("numberdensity"), R"doc(It returns $(2\pi\nu/c)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{-1},m^{-1})$ for
$^{16}O^{16}O^{17}O$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>frequency</b> in GHz,
<b>width</b> (channel width around <b>frequency</b>) in GHz, <b>n</b> (number of frequency points for averaging within <b>width</b>),
and <b>numberdensity</b> in molecules of $^{16}O^{16}O^{17}O$ m$^{-3}$.)doc");
  cls_RefractiveIndex.def("getRefractivity_16o18o16o", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double, unsigned int, double)>(&RefractiveIndex::getRefractivity_16o18o16o), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), py::arg("width"), py::arg("n"), py::arg("numberdensity"), R"doc(It returns $(2\pi\nu/c)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{-1},m^{-1})$ for
$^{16}O^{18}O^{16}O$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>frequency</b> in GHz,
<b>width</b> (channel width around <b>frequency</b>) in GHz, <b>n</b> (number of frequency points for averaging within <b>width</b>),
and <b>numberdensity</b> in molecules of $^{16}O^{18}O^{16}O$ m$^{-3}$.)doc");
  cls_RefractiveIndex.def("getRefractivity_16o17o16o", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double, unsigned int, double)>(&RefractiveIndex::getRefractivity_16o17o16o), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), py::arg("width"), py::arg("n"), py::arg("numberdensity"), R"doc(It returns $(2\pi\nu/c)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{-1},m^{-1})$ for
$^{16}O^{17}O^{16}O$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>frequency</b> in GHz,
<b>width</b> (channel width around <b>frequency</b>) in GHz, <b>n</b> (number of frequency points for averaging within <b>width</b>),
and <b>numberdensity</b> in molecules of $^{16}O^{17}O^{16}O$ m$^{-3}$.)doc");
  cls_RefractiveIndex.def("getRefractivity_hcl", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double, unsigned int, double)>(&RefractiveIndex::getRefractivity_hcl), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), py::arg("width"), py::arg("n"), py::arg("numberdensity"), R"doc(It returns $(2\pi\nu/c)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{-1},m^{-1})$ for $NO_2$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>frequency</b> in GHz,
<b>width</b> (channel width around <b>frequency</b>) in GHz, <b>n</b> (number of frequency points for averaging within <b>width</b>),
and <b>numberdensity</b> in molecules of $NO_2$ m$^{-3}$.)doc");
  cls_RefractiveIndex.def("getRefractivity_hcn", static_cast<std::complex<double> (RefractiveIndex::*)(double, double, double, double, unsigned int, double)>(&RefractiveIndex::getRefractivity_hcn), py::arg("temperature"), py::arg("pressure"), py::arg("frequency"), py::arg("width"), py::arg("n"), py::arg("numberdensity"), R"doc(It returns $(2\pi\nu/c)\cdot(N_{rg}+iN_{ig})$ with units $(rad\cdot m^{-1},m^{-1})$ for $NO_2$ (see \ref definitions) <br>
The parameters are <b>temperature</b> in K, <b>pressure</b> in hPa, <b>frequency</b> in GHz,
<b>width</b> (channel width around <b>frequency</b>) in GHz, <b>n</b> (number of frequency points for averaging within <b>width</b>),
and <b>numberdensity</b> in molecules of $NO_2$ m$^{-3}$.)doc");

  // ----- SpectralGrid
  cls_SpectralGrid.def(py::init<const SpectralGrid &>(), py::arg("other"), "Copy constructor");
  cls_SpectralGrid.def("__copy__", [](SpectralGrid const &self) { return SpectralGrid(self); });
  cls_SpectralGrid.def("__deepcopy__", [](SpectralGrid const &self, py::dict) { return SpectralGrid(self); }, py::arg("memo"));
  cls_SpectralGrid.def(py::init<const Frequency &>(), py::arg("oneFreq"), "");
  cls_SpectralGrid.def(py::init<unsigned int, unsigned int, const Frequency &, const Frequency &>(), py::arg("numChan"), py::arg("refChan"), py::arg("refFreq"), py::arg("chanSep"), R"doc(A full constructor to be used in cases the channel separation is uniform. The
 position of the reference frequency is set at the center of the specified
 reference channel. This reference channel does not need to be necessarily
 in the range [1,numChan].
@pre no spectral window has yet been defined
@param numChan Number of channels for the spectral window
@param refChan Reference channel for the spectral window
@param refFreq Frequency for this reference channel
@param chanSep Frequency increment between two adjacent channels
@post  the spectral window has been defined; it is taken as a spectral window
       with no sideband. Its spectral window identifier spwId is 0.)doc");
  cls_SpectralGrid.def(py::init<const std::vector<double> &, Frequency::Units>(), py::arg("chanFreq"), py::arg("freqUnits"), "");
  cls_SpectralGrid.def(py::init<const std::vector<Frequency> &>(), py::arg("chanFreq"), "");
  cls_SpectralGrid.def(py::init<unsigned int, unsigned int, const Frequency &, const Frequency &, const Frequency &, const SidebandSide &, const SidebandType &>(), py::arg("numChan"), py::arg("refChan"), py::arg("refFreq"), py::arg("chanSep"), py::arg("intermediateFreq"), py::arg("sbSide"), py::arg("sbType"), R"doc(A full constructor to be used in cases of two sibands (separated or not)
 The reference frequency, may not coincide with the center
 of a channel, is the frequency used to track on.
 The frequency units (freqUnits) is common for the reference
 frequency (refFReq) and for the numChan frequencies in the list chanFreq.
 Known units are GHz, MHz, kHz and Hz.
@pre no spectral window has yet been defined
@param numChan Number of channels for the spectral window
@param refFreq Frequency of the reference channel
@param chanSep Frequency interval between two adajacent channels
@param intermediateFreq Intermediate Frequency
@param SidebandSide code (see #SidebandSide for details)
@param SidebandType code (see #SidebandType for details)
@post  <b>Two</b> spectral windows have been defined, one for each sideband
       Their spectral window identifiers are 0 and 1. The identifier is 0 and 1 for the lower
       and upper sidebands if the input netSideband is 0, 1, 3 or 5 else it is 1 and 0 respectively.)doc");
  cls_SpectralGrid.def(py::init([](unsigned int numChan, unsigned int refChan, std::vector<double> chanFreq, Frequency::Units freqUnits) { return new SpectralGrid(numChan, refChan, chanFreq.data(), freqUnits); }), py::arg("numChan"), py::arg("refChan"), py::arg("chanFreq"), py::arg("freqUnits"), R"doc(A full constructor to be used in cases the channel separation is not uniform.
 In this case the reference frequency coincides with the center of a channel,
 the one at the refChan position in the numChan elements of the list of
 frequencies chanFreq. Hence refChan must be in the range [1,numChan]. The
 frequency units (freqUnits) is common for the reference
 frequency (refFReq) and for the numChan frequencies in the list chanFreq.
 Known units are GHz, MHz, kHz and Hz.
@pre no spectral window has yet been defined
@param numChan Number of channels for the spectral window
@param refChan Reference channel for the spectral window
@param chanFreq The frequencies of the individual channels
@param freqUnits The frequency units used to define refFreq and chanFreq
@post  the spectral window has been defined; it is taken as a spectral window
       with no sideband. Its spectral window identifier spwId is 0.)doc");
  cls_SpectralGrid.def(py::init<>(), "");
  cls_SpectralGrid.def("add", static_cast<unsigned int (SpectralGrid::*)(unsigned int, unsigned int, const Frequency &, const Frequency &)>(&SpectralGrid::add), py::arg("numChan"), py::arg("refChan"), py::arg("refFreq"), py::arg("chanSep"), R"doc(Add a new spectral window, uniformly sampled, this spectral window having no sideband.
@pre   at least one spectral window has already been defined
@param numChan Number of channels for the spectral window
@param refChan Reference channel for the spectral window
@param refFreq Frequency for this reference channel
@param chanSep Frequency increment between two adjacent channels
@return the identifier for this spectral window
@post  the spectral window has been defined and appended to the set of spectral windows;
       this new spectral window is taken as one with no sideband.)doc");
  cls_SpectralGrid.def("add", [](SpectralGrid &self, unsigned int numChan, unsigned int refChan, std::vector<double> chanFreq, Frequency::Units freqUnits) { return self.add(numChan, refChan, chanFreq.data(), freqUnits); }, py::arg("numChan"), py::arg("refChan"), py::arg("chanFreq"), py::arg("freqUnits"), R"doc(Add a new spectral window, this spectral window having no sideband.
@pre   at least one spectral window has already been defined
@param numChan Number of channels for the spectral window
@param refChan Reference channel for the spectral window
@param chanFreq The frequency for every channel
@param freqUnits The frequency units (GHz, MHz or kHz, else assumed in Hz) used for chanFreq
@return the identifier for this spectral window
@post  the spectral window has been defined and appended to the set of spectral windows;
       this new spectral window is taken as one with no sideband.)doc");
  cls_SpectralGrid.def("add", static_cast<unsigned int (SpectralGrid::*)(const std::vector<Frequency> &)>(&SpectralGrid::add), py::arg("chanFreq"), "");
  cls_SpectralGrid.def("add", static_cast<void (SpectralGrid::*)(unsigned int, unsigned int, const Frequency &, const Frequency &, const Frequency &, const SidebandSide &, const SidebandType &)>(&SpectralGrid::add), py::arg("numChan"), py::arg("refChan"), py::arg("refFreq"), py::arg("chanSep"), py::arg("intermediateFreq"), py::arg("sbSide"), py::arg("sbType"), R"doc(Add two new spectral windows, one spectral window per sideband.
@pre   at least one spectral window has already been defined
@param numChan Number of channels for the spectral window in one sideband
@param refFreq The frequency at the reference channel for that spectral window
@param chanSep The channel separation (unsigned)
@param intermediateFreq the Intermediate Frequency
@return the netSideband for this first spectral window (the second spectral will have the corresponding
        netSideband for the other sideband.
@post  the spectral window has been defined and appended to the set of spectral windows;
       this new spectral window is taken as one with no sideband.
\note For SSB receivers the first sideband is the signal sideband and in this case refFreq is usually
      the frequency for the middle of that sideband. For DSB refFreq may be in between the two sideband.)doc");
  cls_SpectralGrid.def("getNumSpectralWindow", static_cast<unsigned int (SpectralGrid::*)() const>(&SpectralGrid::getNumSpectralWindow), R"doc(Accessor to the number of spectral wondows
@return number of spectral windows)doc");
  cls_SpectralGrid.def("getNumChan", static_cast<unsigned int (SpectralGrid::*)() const>(&SpectralGrid::getNumChan), R"doc(Accessor to the number of frequency points for the first spectral window
@return number of frequency channels)doc");
  cls_SpectralGrid.def("getNumChan", static_cast<unsigned int (SpectralGrid::*)(unsigned int) const>(&SpectralGrid::getNumChan), py::arg("spwId"), R"doc(Accessor to the number of frequency points for a given spectral window
@param spwId spectral window identifier (0-based)
@return number of frequency channels)doc");
  cls_SpectralGrid.def("getRefChan", static_cast<unsigned int (SpectralGrid::*)() const>(&SpectralGrid::getRefChan), R"doc(Accessor to the reference channel of the first spectral window
@return the reference channel
\note with the constructor SpectralGrid( int numChan, double refFreq, double* chanFreq, std::string freqUnits)
      there is no way to determine the reference channel if the grid is not regularily sampled! would that be
      the case, the returned value is 0.)doc");
  cls_SpectralGrid.def("getRefChan", static_cast<unsigned int (SpectralGrid::*)(unsigned int) const>(&SpectralGrid::getRefChan), py::arg("spwId"), R"doc(Accessor to the reference channel for a given spectral window
@param spwId spectral window identifier (0-based)
@return the reference channel)doc");
  cls_SpectralGrid.def("getRefFreq", static_cast<Frequency (SpectralGrid::*)() const>(&SpectralGrid::getRefFreq), R"doc(Accessor to the reference frequency (Hz) for the first spectral window
@return the frequency at the reference channel position)doc");
  cls_SpectralGrid.def("getRefFreq", static_cast<Frequency (SpectralGrid::*)(unsigned int) const>(&SpectralGrid::getRefFreq), py::arg("spwId"), R"doc(Accessor to the reference frequency (Hz) for a given spectral window
@param spwId spectral window identifier (0-based)
@return the frequency at the reference channel position)doc");
  cls_SpectralGrid.def("getChanSep", static_cast<Frequency (SpectralGrid::*)() const>(&SpectralGrid::getChanSep), R"doc(Accessor to the channel separation for regularily spaced grids (for the first spectral window)
@return the channel separation (Hz))doc");
  cls_SpectralGrid.def("getChanSep", static_cast<Frequency (SpectralGrid::*)(unsigned int) const>(&SpectralGrid::getChanSep), py::arg("spwId"), R"doc(Accessor to the channel separation for regularily spaced grids (for a given spectral window)
@param spwId spectral window identifier (0-based)
@return the channel separation (Hz))doc");
  cls_SpectralGrid.def("getChanFreq", static_cast<Frequency (SpectralGrid::*)(unsigned int) const>(&SpectralGrid::getChanFreq), py::arg("chanNum"), R"doc(Accessor to the frequency (Hz) for a given grid point (for the first spectral window)
@param chanNum    the channel number (grid units)
@ return the frequency (Hz) corresponding to the center of the channel)doc");
  cls_SpectralGrid.def("getChanWidth", static_cast<Frequency (SpectralGrid::*)(unsigned int) const>(&SpectralGrid::getChanWidth), py::arg("chanNum"), "");
  cls_SpectralGrid.def("getChanFreq", static_cast<Frequency (SpectralGrid::*)(unsigned int, unsigned int) const>(&SpectralGrid::getChanFreq), py::arg("spwId"), py::arg("chanNum"), R"doc(Accessor to the frequency (Hz) for a given grid point for the specified spectral window
@param spwId     spectral window identifier (0-based)
@param chanNum   the channel number (grid units)
@ return the frequency (Hz) corresponding to the center of the channel)doc");
  cls_SpectralGrid.def("getChanWidth", static_cast<Frequency (SpectralGrid::*)(unsigned int, unsigned int) const>(&SpectralGrid::getChanWidth), py::arg("spwId"), py::arg("chanNum"), "");
  cls_SpectralGrid.def("getSbChanFreq", static_cast<std::vector<double> (SpectralGrid::*)(unsigned int, unsigned int, const std::string &) const>(&SpectralGrid::getSbChanFreq), py::arg("spwId"), py::arg("chanNum"), py::arg("freqUnits"), R"doc(Accessor to the frequencies in the specified units for a given channel index (0-based) for the
the specified spectral window its corresponding other sideband.
@param spwId     spectral window identifier (0-based)
@param chanNum   the channel number (grid units)
@param freqUnits the requested units
@return  the frequencies corresponding to the center of the channel in the specified units for
         the input spectral window and for the corresponding channel in the other sideband)doc");
  cls_SpectralGrid.def("getSpectralWindow", static_cast<std::vector<double> (SpectralGrid::*)(unsigned int) const>(&SpectralGrid::getSpectralWindow), py::arg("spwId"), R"doc(Accessor to retrieve the spectral grid of a spectral window
@param spwId     spectral window identifier (0-based)
@return a std::vector of numChan frequencies (Hz))doc");
  cls_SpectralGrid.def("getBandwidth", static_cast<Frequency (SpectralGrid::*)() const>(&SpectralGrid::getBandwidth), R"doc(Method to get the frequency range encompassing the list of frequency grid points (for the first spectral window)
\note In case of irregular sampling the return value is the difference between the frequencies of the channels
      with the highest one and the channel with the lowedt one else it the product of the number of channels
      times the channel separation
@return the frequency bandwidth (Hz))doc");
  cls_SpectralGrid.def("getBandwidth", static_cast<Frequency (SpectralGrid::*)(unsigned int) const>(&SpectralGrid::getBandwidth), py::arg("spwId"), R"doc(Method to get the frequency range encompassing the list of frequency grid points for the specified spectral window
\note In case of irregular sampling the return value is the difference between the frequencies of the channels
      with the highest one and the channel with the lowedt one else it the product of the number of channels
      times the channel separation
@param spwId spectral window identifier (0-based)
@return the frequency bandwidth (Hz))doc");
  cls_SpectralGrid.def("getMinFreq", static_cast<Frequency (SpectralGrid::*)() const>(&SpectralGrid::getMinFreq), R"doc(Method to get the frequency (Hz) for the point at the lowest frequency (for the first spectral window)
@return the frequency of the channel at the lowest frequency)doc");
  cls_SpectralGrid.def("getMinFreq", static_cast<Frequency (SpectralGrid::*)(unsigned int) const>(&SpectralGrid::getMinFreq), py::arg("spwId"), R"doc(Method to get the frequency in the specified units for the channel at the lowest frequency for the
specified spectral window
@param spwId spectral window identifier (0-based)
@return the frequency (Hz) of the channel at the lowest frequency)doc");
  cls_SpectralGrid.def("getMaxFreq", static_cast<Frequency (SpectralGrid::*)() const>(&SpectralGrid::getMaxFreq), R"doc(Method to get the frequency (Hz) for the point at the largest frequency (for the first spectral window)
@return the frequency (Hz) of the channel at the highest frequency)doc");
  cls_SpectralGrid.def("getMaxFreq", static_cast<Frequency (SpectralGrid::*)(unsigned int) const>(&SpectralGrid::getMaxFreq), py::arg("spwId"), R"doc(Method to get the frequency in the specified units for the point at the largest frequency (for the first
spectral window)
@param  units the requested units
@return the frequency (Hz) of the channel at the highest frequency)doc");
  cls_SpectralGrid.def("isRegular", static_cast<bool (SpectralGrid::*)() const>(&SpectralGrid::isRegular), R"doc(Method to know if the spectral grid is regular or not (the first spectral window)
@return true if uniformly sampled, else false)doc");
  cls_SpectralGrid.def("isRegular", static_cast<bool (SpectralGrid::*)(unsigned int) const>(&SpectralGrid::isRegular), py::arg("spwId"), R"doc(Method to know if the spectral grid is regular or not for the specified spectral window
@param spwId spectral window identifier (0-based)
@return true if uniformly sampled, else false)doc");
  cls_SpectralGrid.def("getSidebandSide", static_cast<std::string (SpectralGrid::*)(unsigned int) const>(&SpectralGrid::getSidebandSide), py::arg("spwId"), R"doc(Accessor for the side of the sideband
@param spwId spectral window identifier (0-based)
@return the side of the sideband
\note Possible result is no sideband (NoSB) or lower sideband (LSB) or upper sideband (USB))doc");
  cls_SpectralGrid.def("getAssocNature", static_cast<std::vector<std::string> (SpectralGrid::*)(unsigned int) const>(&SpectralGrid::getAssocNature), py::arg("spwId"), R"doc(Accessor to the nature(s) of the associated spectral window(s)
@pre the spectral window must have an associated sideband. Would that not be the
     case the returned std::vector has a size of 0.
@param spwId spectral window identifier (0-based)
@return the associated nature(s) of the associated spectral windows)doc");
  cls_SpectralGrid.def("getAssocSpwId", static_cast<std::vector<unsigned int> (SpectralGrid::*)(unsigned int) const>(&SpectralGrid::getAssocSpwId), py::arg("spwId"), R"doc(Accessor to the identifier of the associated spectral window(s)
@pre the spectral window must have an associated spectral window. Would that not be the
     case the returned std::vector has a size of 0.
@param spwId spectral window identifier (0-based)
@return the identifiers of the its associated spectral windows)doc");
  cls_SpectralGrid.def("getAssocSpwIds", static_cast<std::vector<unsigned int> (SpectralGrid::*)(const std::vector<unsigned int> &) const>(&SpectralGrid::getAssocSpwIds), py::arg("spwIds"), "");
  cls_SpectralGrid.def("getSidebandType", static_cast<std::string (SpectralGrid::*)(unsigned int) const>(&SpectralGrid::getSidebandType), py::arg("spwId"), R"doc(Accessor for the type of  sideband
@pre the spectral window must have an associated spectral window. Would that not be the
     case the returned std::vector has a size of 0.
@param spwId spectral window identifier (0-based)
@return the type of the sideband
\note Possible result is double sideband (DSB) or single sideband (SSB) or two sidebands (2SB).
2SB implies sideband separation which is possible only in the interferometric case)doc");
  cls_SpectralGrid.def("getSideband", static_cast<std::string (SpectralGrid::*)(unsigned int) const>(&SpectralGrid::getSideband), py::arg("spwId"), R"doc(Accessor for the side of the sideband and its type
@pre the spectral window must have a sideband side and a sideband type. Would that not be the
     case the returned std::string has a size of 0.
@param spwId spectral window identifier (0-based)
@return the side and the type of the sideband)doc");
  cls_SpectralGrid.def("getLoFrequency", static_cast<double (SpectralGrid::*)() const>(&SpectralGrid::getLoFrequency), "");
  cls_SpectralGrid.def("getLoFrequency", static_cast<double (SpectralGrid::*)(unsigned int) const>(&SpectralGrid::getLoFrequency), py::arg("spwId"), "");
  cls_SpectralGrid.def("__eq__", [](SpectralGrid a, const SpectralGrid & b) { return a == b; }, py::is_operator());
  cls_SpectralGrid.def(py::init([](unsigned int numChan, double refFreq, std::vector<double> chanFreq, Frequency::Units freqUnits) { return new SpectralGrid(numChan, refFreq, chanFreq.data(), freqUnits); }), py::arg("numChan"), py::arg("refFreq"), py::arg("chanFreq"), py::arg("freqUnits"), R"doc(A full constructor to be used in cases the channel separation is not uniform.
 In this case the reference frequency may not coincide with the center
 of a channel. The frequency units (freqUnits) is common for the reference
 frequency (refFReq) and for the numChan frequencies in the list chanFreq.
 Known units are GHz, MHz, kHz and Hz.
@pre no spectral window has yet been defined
@param numChan Number of channels for the spectral window
@param refFreq The frequency of the reference channel
@param chanFreq The frequencies of the individual channels
@param freqUnits The frequency units used to define refFreq and chanFreq
@post  the spectral window has been defined; it is taken as a spectral window
       with no sideband. Its spectral window identifier spwId is 0.)doc");
  cls_SpectralGrid.def(py::init<double, const std::vector<double> &, Frequency::Units>(), py::arg("refFreq"), py::arg("chanFreq"), py::arg("freqUnits"), "");
  cls_SpectralGrid.def("add", [](SpectralGrid &self, unsigned int numChan, double refFreq, std::vector<double> chanFreq, Frequency::Units freqUnits) { return self.add(numChan, refFreq, chanFreq.data(), freqUnits); }, py::arg("numChan"), py::arg("refFreq"), py::arg("chanFreq"), py::arg("freqUnits"), R"doc(Add a new spectral window, this spectral window having no sideband.
@pre   at least one spectral window has already been defined
@param numChan Number of channels for the spectral window
@param refFreq The frequency at the reference channel for the spectral window
@param chanFreq The frequency for every channel
@param freqUnits The frequency units (GHz, MHz or kHz, else assumed in Hz) used for refFreq and chanFreq
@return the identifier for this spectral window
@post  the spectral window has been defined and appended to the set of spectral windows;
       this new spectral window is taken as one with no sideband.)doc");
  cls_SpectralGrid.def("add", static_cast<unsigned int (SpectralGrid::*)(unsigned int, double, const std::vector<double> &, Frequency::Units)>(&SpectralGrid::add), py::arg("numChan"), py::arg("refFreq"), py::arg("chanFreq"), py::arg("freqUnits"), "");
  cls_SpectralGrid.def("getChanNum", static_cast<double (SpectralGrid::*)(double) const>(&SpectralGrid::getChanNum), py::arg("freq"), R"doc(Method to get the grid position for a given frequency specified in Hz (the first spectral window)
@return the grid position)doc");
  cls_SpectralGrid.def("getChanNum", static_cast<double (SpectralGrid::*)(unsigned int, double) const>(&SpectralGrid::getChanNum), py::arg("spwId"), py::arg("freq"), R"doc(Method to get the grid position for a given frequency specified in Hz for the specified spectral window
@param freq the frequency (Hz) for the grid position
@param spwId spectral window identifier (0-based)
@return the grid position)doc");
  cls_SpectralGrid.attr("__hash__") = py::none();

  // ----- RefractiveIndexProfile
  cls_RefractiveIndexProfile.def(py::init<const RefractiveIndexProfile &>(), py::arg("other"), "Copy constructor");
  cls_RefractiveIndexProfile.def("__copy__", [](RefractiveIndexProfile const &self) { return RefractiveIndexProfile(self); });
  cls_RefractiveIndexProfile.def("__deepcopy__", [](RefractiveIndexProfile const &self, py::dict) { return RefractiveIndexProfile(self); }, py::arg("memo"));
  cls_RefractiveIndexProfile.def(py::init<const Frequency &, const AtmProfile &>(), py::arg("frequency"), py::arg("atmProfile"), R"doc(A full constructor for the case of a profile of absorption coefficients
 at a single frequency)doc");
  cls_RefractiveIndexProfile.def(py::init<const SpectralGrid &, const AtmProfile &>(), py::arg("spectralGrid"), py::arg("atmProfile"), R"doc(A full constructor for the case of a profile of absorption coefficients
 for a set of frequency points.)doc");
  cls_RefractiveIndexProfile.def(py::init<>(), "");
  cls_RefractiveIndexProfile.def("addNewSpectralWindow", static_cast<void (RefractiveIndexProfile::*)(unsigned int, unsigned int, const Frequency &, const Frequency &)>(&RefractiveIndexProfile::addNewSpectralWindow), py::arg("numChan"), py::arg("refChan"), py::arg("refFreq"), py::arg("chanSep"), R"doc(Setter of new spectral windows (adds frequencies to the SpectralGrid and calculates the corresponding absorption coefficients))doc");
  cls_RefractiveIndexProfile.def("addNewSpectralWindow", [](RefractiveIndexProfile &self, unsigned int numChan, unsigned int refChan, std::vector<double> chanFreq, Frequency::Units freqUnits) { return self.addNewSpectralWindow(numChan, refChan, chanFreq.data(), freqUnits); }, py::arg("numChan"), py::arg("refChan"), py::arg("chanFreq"), py::arg("freqUnits"), R"doc(Setter of new spectral windows (adds frequencies to the SpectralGrid and calculates the corresponding absorption coefficients))doc");
  cls_RefractiveIndexProfile.def("addNewSpectralWindow", static_cast<void (RefractiveIndexProfile::*)(unsigned int, unsigned int, const Frequency &, const Frequency &, const Frequency &, const SidebandSide &, const SidebandType &)>(&RefractiveIndexProfile::addNewSpectralWindow), py::arg("numChan"), py::arg("refChan"), py::arg("refFreq"), py::arg("chanSep"), py::arg("intermediateFreq"), py::arg("sbSide"), py::arg("sbType"), R"doc(Setter of new spectral windows (adds frequencies to the SpectralGrid and calculates the corresponding absorption coefficients))doc");
  cls_RefractiveIndexProfile.def("addNewSpectralWindow", static_cast<void (RefractiveIndexProfile::*)(const std::vector<Frequency> &)>(&RefractiveIndexProfile::addNewSpectralWindow), py::arg("chanFreq"), "");
  cls_RefractiveIndexProfile.def("getNumIndividualFrequencies", static_cast<unsigned int (RefractiveIndexProfile::*)() const>(&RefractiveIndexProfile::getNumIndividualFrequencies), R"doc(Accessor to total number of Frequency points in the SpectralGrid object)doc");
  cls_RefractiveIndexProfile.def("getFrequency", static_cast<double (RefractiveIndexProfile::*)() const>(&RefractiveIndexProfile::getFrequency), R"doc(Accessor to the single frequency (or the frequency of the first grid point
 in case of a spectrum) in Hz (SI default unit))doc");
  cls_RefractiveIndexProfile.def("getFrequency", static_cast<double (RefractiveIndexProfile::*)(Frequency::Units) const>(&RefractiveIndexProfile::getFrequency), py::arg("freqUnits"), R"doc(Accessor to the single frequency (or the frequency of the first grid point
 in case of a spectrum) in specified unit)doc");
  cls_RefractiveIndexProfile.def("getAbsH2OLines", static_cast<InverseLength (RefractiveIndexProfile::*)(unsigned int) const>(&RefractiveIndexProfile::getAbsH2OLines), py::arg("nl"), R"doc(Accessor to get H2O lines Absorption Coefficient at layer nl, for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("getAbsH2OLines", static_cast<InverseLength (RefractiveIndexProfile::*)(unsigned int, unsigned int) const>(&RefractiveIndexProfile::getAbsH2OLines), py::arg("nf"), py::arg("nl"), R"doc(Accessor to get H2O lines Absorption Coefficient at layer nl and frequency channel nf, for RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("getAbsH2OLines", static_cast<InverseLength (RefractiveIndexProfile::*)(unsigned int, unsigned int, unsigned int) const>(&RefractiveIndexProfile::getAbsH2OLines), py::arg("spwid"), py::arg("nf"), py::arg("nl"), R"doc(Accessor to get H2O Continuum Absorption Coefficient at layer nl, spectral window spwid and channel nf)doc");
  cls_RefractiveIndexProfile.def("getAbsH2OCont", static_cast<InverseLength (RefractiveIndexProfile::*)(unsigned int) const>(&RefractiveIndexProfile::getAbsH2OCont), py::arg("nl"), R"doc(Accessor to get H2O Continuum Absorption Coefficient at layer nl, for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("getAbsH2OCont", static_cast<InverseLength (RefractiveIndexProfile::*)(unsigned int, unsigned int) const>(&RefractiveIndexProfile::getAbsH2OCont), py::arg("nf"), py::arg("nl"), R"doc(Accessor to get H2O Continuum Absorption Coefficient at layer nl and frequency channel nf, for RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("getAbsH2OCont", static_cast<InverseLength (RefractiveIndexProfile::*)(unsigned int, unsigned int, unsigned int) const>(&RefractiveIndexProfile::getAbsH2OCont), py::arg("spwid"), py::arg("nf"), py::arg("nl"), R"doc(Accessor to get H2O Continuum Absorption Coefficient at layer nl, spectral window spwid and channel nf)doc");
  cls_RefractiveIndexProfile.def("getAbsO2Lines", static_cast<InverseLength (RefractiveIndexProfile::*)(unsigned int) const>(&RefractiveIndexProfile::getAbsO2Lines), py::arg("nl"), R"doc(Function to retrieve O2 lines Absorption Coefficient at layer nl, for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("getAbsO2Lines", static_cast<InverseLength (RefractiveIndexProfile::*)(unsigned int, unsigned int) const>(&RefractiveIndexProfile::getAbsO2Lines), py::arg("nf"), py::arg("nl"), R"doc(Function to retrieve O2 lines Absorption Coefficient at layer nl and frequency channel nf, for RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("getAbsO2Lines", static_cast<InverseLength (RefractiveIndexProfile::*)(unsigned int, unsigned int, unsigned int) const>(&RefractiveIndexProfile::getAbsO2Lines), py::arg("spwid"), py::arg("nf"), py::arg("nl"), R"doc(Function to retrieve O2 lines Absorption Coefficient at layer nl, spectral window spwid and channel nf)doc");
  cls_RefractiveIndexProfile.def("getAbsDryCont", static_cast<InverseLength (RefractiveIndexProfile::*)(unsigned int) const>(&RefractiveIndexProfile::getAbsDryCont), py::arg("nl"), R"doc(Function to retrieve Dry continuum Absorption Coefficient at layer nl, for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("getAbsDryCont", static_cast<InverseLength (RefractiveIndexProfile::*)(unsigned int, unsigned int) const>(&RefractiveIndexProfile::getAbsDryCont), py::arg("nf"), py::arg("nl"), R"doc(Function to retrieve Dry continuum Absorption Coefficient at layer nl and frequency channel nf, for RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("getAbsDryCont", static_cast<InverseLength (RefractiveIndexProfile::*)(unsigned int, unsigned int, unsigned int) const>(&RefractiveIndexProfile::getAbsDryCont), py::arg("spwid"), py::arg("nf"), py::arg("nl"), R"doc(Function to retrieve Dry continuum Absorption Coefficient at layer nl, spectral window spwid and channel nf)doc");
  cls_RefractiveIndexProfile.def("getAbsO3Lines", static_cast<InverseLength (RefractiveIndexProfile::*)(unsigned int) const>(&RefractiveIndexProfile::getAbsO3Lines), py::arg("nl"), R"doc(Function to retrieve O3 lines Absorption Coefficient at layer nl, for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("getAbsO3Lines", static_cast<InverseLength (RefractiveIndexProfile::*)(unsigned int, unsigned int) const>(&RefractiveIndexProfile::getAbsO3Lines), py::arg("nf"), py::arg("nl"), R"doc(Function to retrieve O3 lines Absorption Coefficient at layer nl and frequency channel nf, for RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("getAbsO3Lines", static_cast<InverseLength (RefractiveIndexProfile::*)(unsigned int, unsigned int, unsigned int) const>(&RefractiveIndexProfile::getAbsO3Lines), py::arg("spwid"), py::arg("nf"), py::arg("nl"), R"doc(Function to retrieve O3 lines Absorption Coefficient at layer nl, spectral window spwid and channel nf)doc");
  cls_RefractiveIndexProfile.def("getAbsCOLines", static_cast<InverseLength (RefractiveIndexProfile::*)(unsigned int) const>(&RefractiveIndexProfile::getAbsCOLines), py::arg("nl"), R"doc(Function to retrieve CO lines Absorption Coefficient at layer nl, for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("getAbsCOLines", static_cast<InverseLength (RefractiveIndexProfile::*)(unsigned int, unsigned int) const>(&RefractiveIndexProfile::getAbsCOLines), py::arg("nf"), py::arg("nl"), R"doc(Function to retrieve CO lines Absorption Coefficient at layer nl and frequency channel nf, for RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("getAbsCOLines", static_cast<InverseLength (RefractiveIndexProfile::*)(unsigned int, unsigned int, unsigned int) const>(&RefractiveIndexProfile::getAbsCOLines), py::arg("spwid"), py::arg("nf"), py::arg("nl"), R"doc(Function to retrieve CO lines Absorption Coefficient at layer nl, spectral window spwid and channel nf)doc");
  cls_RefractiveIndexProfile.def("getAbsN2OLines", static_cast<InverseLength (RefractiveIndexProfile::*)(unsigned int) const>(&RefractiveIndexProfile::getAbsN2OLines), py::arg("nl"), R"doc(Function to retrieve N2O lines Absorption Coefficient at layer nl, for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("getAbsN2OLines", static_cast<InverseLength (RefractiveIndexProfile::*)(unsigned int, unsigned int) const>(&RefractiveIndexProfile::getAbsN2OLines), py::arg("nf"), py::arg("nl"), R"doc(Function to retrieve N2O lines Absorption Coefficient at layer nl and frequency channel nf, for RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("getAbsN2OLines", static_cast<InverseLength (RefractiveIndexProfile::*)(unsigned int, unsigned int, unsigned int) const>(&RefractiveIndexProfile::getAbsN2OLines), py::arg("spwid"), py::arg("nf"), py::arg("nl"), R"doc(Function to retrieve N2O lines Absorption Coefficient at layer nl, spectral window spwid and channel nf)doc");
  cls_RefractiveIndexProfile.def("getAbsNO2Lines", static_cast<InverseLength (RefractiveIndexProfile::*)(unsigned int) const>(&RefractiveIndexProfile::getAbsNO2Lines), py::arg("nl"), R"doc(Function to retrieve NO2 lines Absorption Coefficient at layer nl, for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("getAbsNO2Lines", static_cast<InverseLength (RefractiveIndexProfile::*)(unsigned int, unsigned int) const>(&RefractiveIndexProfile::getAbsNO2Lines), py::arg("nf"), py::arg("nl"), R"doc(Function to retrieve NO2 lines Absorption Coefficient at layer nl and frequency channel nf, for RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("getAbsNO2Lines", static_cast<InverseLength (RefractiveIndexProfile::*)(unsigned int, unsigned int, unsigned int) const>(&RefractiveIndexProfile::getAbsNO2Lines), py::arg("spwid"), py::arg("nf"), py::arg("nl"), R"doc(Function to retrieve NO2 lines Absorption Coefficient at layer nl, spectral window spwid and channel nf)doc");
  cls_RefractiveIndexProfile.def("getAbsSO2Lines", static_cast<InverseLength (RefractiveIndexProfile::*)(unsigned int) const>(&RefractiveIndexProfile::getAbsSO2Lines), py::arg("nl"), R"doc(Function to retrieve SO2 lines Absorption Coefficient at layer nl, for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("getAbsSO2Lines", static_cast<InverseLength (RefractiveIndexProfile::*)(unsigned int, unsigned int) const>(&RefractiveIndexProfile::getAbsSO2Lines), py::arg("nf"), py::arg("nl"), R"doc(Function to retrieve SO2 lines Absorption Coefficient at layer nl and frequency channel nf, for RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("getAbsSO2Lines", static_cast<InverseLength (RefractiveIndexProfile::*)(unsigned int, unsigned int, unsigned int) const>(&RefractiveIndexProfile::getAbsSO2Lines), py::arg("spwid"), py::arg("nf"), py::arg("nl"), R"doc(Function to retrieve SO2 lines Absorption Coefficient at layer nl, spectral window spwid and channel nf)doc");
  cls_RefractiveIndexProfile.def("getAbsHClLines", static_cast<InverseLength (RefractiveIndexProfile::*)(unsigned int) const>(&RefractiveIndexProfile::getAbsHClLines), py::arg("nl"), R"doc(Function to retrieve HCl lines Absorption Coefficient at layer nl, for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("getAbsHClLines", static_cast<InverseLength (RefractiveIndexProfile::*)(unsigned int, unsigned int) const>(&RefractiveIndexProfile::getAbsHClLines), py::arg("nf"), py::arg("nl"), R"doc(Function to retrieve HCl lines Absorption Coefficient at layer nl and frequency channel nf, for RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("getAbsHClLines", static_cast<InverseLength (RefractiveIndexProfile::*)(unsigned int, unsigned int, unsigned int) const>(&RefractiveIndexProfile::getAbsHClLines), py::arg("spwid"), py::arg("nf"), py::arg("nl"), R"doc(Function to retrieve HCl lines Absorption Coefficient at layer nl, spectral window spwid and channel nf)doc");
  cls_RefractiveIndexProfile.def("getAbsHCNLines", static_cast<InverseLength (RefractiveIndexProfile::*)(unsigned int) const>(&RefractiveIndexProfile::getAbsHCNLines), py::arg("nl"), R"doc(Function to retrieve HCN lines Absorption Coefficient at layer nl, for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("getAbsHCNLines", static_cast<InverseLength (RefractiveIndexProfile::*)(unsigned int, unsigned int) const>(&RefractiveIndexProfile::getAbsHCNLines), py::arg("nf"), py::arg("nl"), R"doc(Function to retrieve HCN lines Absorption Coefficient at layer nl and frequency channel nf, for RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("getAbsHCNLines", static_cast<InverseLength (RefractiveIndexProfile::*)(unsigned int, unsigned int, unsigned int) const>(&RefractiveIndexProfile::getAbsHCNLines), py::arg("spwid"), py::arg("nf"), py::arg("nl"), R"doc(Function to retrieve HCN lines Absorption Coefficient at layer nl, spectral window spwid and channel nf)doc");
  cls_RefractiveIndexProfile.def("getAbsTotalDry", static_cast<InverseLength (RefractiveIndexProfile::*)(unsigned int) const>(&RefractiveIndexProfile::getAbsTotalDry), py::arg("nl"), R"doc(Function to retrieve total Dry Absorption Coefficient at layer nl, for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("getAbsTotalDry", static_cast<InverseLength (RefractiveIndexProfile::*)(unsigned int, unsigned int) const>(&RefractiveIndexProfile::getAbsTotalDry), py::arg("nf"), py::arg("nl"), R"doc(Function to retrieve total Dry Absorption Coefficient at layer nl and frequency channel nf, for RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("getAbsTotalDry", static_cast<InverseLength (RefractiveIndexProfile::*)(unsigned int, unsigned int, unsigned int) const>(&RefractiveIndexProfile::getAbsTotalDry), py::arg("spwid"), py::arg("nf"), py::arg("nl"), R"doc(Function to retrieve total Dry Absorption Coefficient at layer nl, spectral window spwid and channel nf)doc");
  cls_RefractiveIndexProfile.def("getAbsTotalWet", static_cast<InverseLength (RefractiveIndexProfile::*)(unsigned int) const>(&RefractiveIndexProfile::getAbsTotalWet), py::arg("nl"), R"doc(Function to retrieve total Wet Absorption Coefficient at layer nl, for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("getAbsTotalWet", static_cast<InverseLength (RefractiveIndexProfile::*)(unsigned int, unsigned int) const>(&RefractiveIndexProfile::getAbsTotalWet), py::arg("nf"), py::arg("nl"), R"doc(Function to retrieve total Wet Absorption Coefficient at layer nl and frequency channel nf, for RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("getAbsTotalWet", static_cast<InverseLength (RefractiveIndexProfile::*)(unsigned int, unsigned int, unsigned int) const>(&RefractiveIndexProfile::getAbsTotalWet), py::arg("spwid"), py::arg("nf"), py::arg("nl"), R"doc(Function to retrieve total Wet Absorption Coefficient at layer nl, spectral window spwid and channel nf)doc");
  cls_RefractiveIndexProfile.def("getAverageO2LinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getAverageO2LinesOpacity), py::arg("spwid"), "");
  cls_RefractiveIndexProfile.def("getAverageO3LinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getAverageO3LinesOpacity), py::arg("spwid"), "");
  cls_RefractiveIndexProfile.def("getAverageN2OLinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getAverageN2OLinesOpacity), py::arg("spwid"), "");
  cls_RefractiveIndexProfile.def("getAverageNO2LinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getAverageNO2LinesOpacity), py::arg("spwid"), "");
  cls_RefractiveIndexProfile.def("getAverageSO2LinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getAverageSO2LinesOpacity), py::arg("spwid"), "");
  cls_RefractiveIndexProfile.def("getAverageHClLinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getAverageHClLinesOpacity), py::arg("spwid"), "");
  cls_RefractiveIndexProfile.def("getAverageHCNLinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getAverageHCNLinesOpacity), py::arg("spwid"), "");
  cls_RefractiveIndexProfile.def("getAverageCOLinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getAverageCOLinesOpacity), py::arg("spwid"), "");
  cls_RefractiveIndexProfile.def("getAverageDryContOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getAverageDryContOpacity), py::arg("spwid"), "");
  cls_RefractiveIndexProfile.def("getDryOpacity", static_cast<Opacity (RefractiveIndexProfile::*)()>(&RefractiveIndexProfile::getDryOpacity), R"doc(Function to retrieve the integrated Dry Opacity along the atmospheric path for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("getDryOpacityUpTo", static_cast<Opacity (RefractiveIndexProfile::*)(Length)>(&RefractiveIndexProfile::getDryOpacityUpTo), py::arg("refalti"), "");
  cls_RefractiveIndexProfile.def("getDryOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getDryOpacity), py::arg("nc"), R"doc(Function to retrieve the integrated Dry Opacity along the atmospheric path for channel nc in an RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("getDryOpacityUpTo", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int, Length)>(&RefractiveIndexProfile::getDryOpacityUpTo), py::arg("nc"), py::arg("refalti"), "");
  cls_RefractiveIndexProfile.def("getDryOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int, unsigned int)>(&RefractiveIndexProfile::getDryOpacity), py::arg("spwid"), py::arg("nc"), "");
  cls_RefractiveIndexProfile.def("getDryOpacityUpTo", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int, unsigned int, Length)>(&RefractiveIndexProfile::getDryOpacityUpTo), py::arg("spwid"), py::arg("nc"), py::arg("refalti"), "");
  cls_RefractiveIndexProfile.def("getAverageDryOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getAverageDryOpacity), py::arg("spwid"), "");
  cls_RefractiveIndexProfile.def("getDryContOpacity", static_cast<Opacity (RefractiveIndexProfile::*)()>(&RefractiveIndexProfile::getDryContOpacity), R"doc(Function to retrieve the integrated Dry Continuum Opacity along the atmospheric path for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("getDryContOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getDryContOpacity), py::arg("nc"), R"doc(Function to retrieve the integrated Dry Continuum Opacity along the atmospheric path for channel nc in an RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("getDryContOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int, unsigned int)>(&RefractiveIndexProfile::getDryContOpacity), py::arg("spwid"), py::arg("nc"), "");
  cls_RefractiveIndexProfile.def("getO2LinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)()>(&RefractiveIndexProfile::getO2LinesOpacity), R"doc(Function to get the integrated O2 (all isotopic and vib. species) line opacity along the atmospheric path for a single frequency in a RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("getO2LinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getO2LinesOpacity), py::arg("nc"), R"doc(Function to get the integrated O2 (all isotopic and vib. species) line opacity along the atmospheric path for channel nc in a RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("getO2LinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int, unsigned int)>(&RefractiveIndexProfile::getO2LinesOpacity), py::arg("spwid"), py::arg("nc"), "");
  cls_RefractiveIndexProfile.def("get16O16OLinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)()>(&RefractiveIndexProfile::get16O16OLinesOpacity), R"doc(Function to get the integrated 16O16O Lines Opacity along the atmospheric path for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("get16O16OLinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::get16O16OLinesOpacity), py::arg("nc"), R"doc(Function to get the integrated 16O16O Lines Opacity along the atmospheric path for channel nc in an RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("get16O16OLinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int, unsigned int)>(&RefractiveIndexProfile::get16O16OLinesOpacity), py::arg("spwid"), py::arg("nc"), "");
  cls_RefractiveIndexProfile.def("get16O16OVIBLinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)()>(&RefractiveIndexProfile::get16O16OVIBLinesOpacity), R"doc(Function to get the integrated 16O16OVIB Lines Opacity along the atmospheric path for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("get16O16OVIBLinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::get16O16OVIBLinesOpacity), py::arg("nc"), R"doc(Function to get the integrated 16O16OVIB Lines Opacity along the atmospheric path for channel nc in an RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("get16O16OVIBLinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int, unsigned int)>(&RefractiveIndexProfile::get16O16OVIBLinesOpacity), py::arg("spwid"), py::arg("nc"), "");
  cls_RefractiveIndexProfile.def("get16O18OLinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)()>(&RefractiveIndexProfile::get16O18OLinesOpacity), R"doc(Function to get the integrated 16O18O Lines Opacity along the atmospheric path for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("get16O18OLinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::get16O18OLinesOpacity), py::arg("nc"), R"doc(Function to get the integrated 16O18O Lines Opacity along the atmospheric path for channel nc in an RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("get16O18OLinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int, unsigned int)>(&RefractiveIndexProfile::get16O18OLinesOpacity), py::arg("spwid"), py::arg("nc"), "");
  cls_RefractiveIndexProfile.def("get16O17OLinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)()>(&RefractiveIndexProfile::get16O17OLinesOpacity), R"doc(Function to get the integrated 16O17O Lines Opacity along the atmospheric path for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("get16O17OLinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::get16O17OLinesOpacity), py::arg("nc"), R"doc(Function to get the integrated 16O17O Lines Opacity along the atmospheric path for channel nc in an RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("get16O17OLinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int, unsigned int)>(&RefractiveIndexProfile::get16O17OLinesOpacity), py::arg("spwid"), py::arg("nc"), "");
  cls_RefractiveIndexProfile.def("getO3LinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)()>(&RefractiveIndexProfile::getO3LinesOpacity), R"doc(Function to retrieve the integrated O3 Lines Opacity along the atmospheric path for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("getO3LinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getO3LinesOpacity), py::arg("nc"), R"doc(Function to retrieve the integrated O3 Lines Opacity along the atmospheric path for channel nc in an RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("getO3LinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int, unsigned int)>(&RefractiveIndexProfile::getO3LinesOpacity), py::arg("spwid"), py::arg("nc"), "");
  cls_RefractiveIndexProfile.def("get16O16O16OLinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)()>(&RefractiveIndexProfile::get16O16O16OLinesOpacity), "");
  cls_RefractiveIndexProfile.def("get16O16O16OLinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::get16O16O16OLinesOpacity), py::arg("nc"), R"doc(Function to retrieve the integrated 16O16O16O Lines Opacity along the atmospheric path for channel nc in an RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("get16O16O16OLinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int, unsigned int)>(&RefractiveIndexProfile::get16O16O16OLinesOpacity), py::arg("spwid"), py::arg("nc"), "");
  cls_RefractiveIndexProfile.def("get16O16O16OV1LinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)()>(&RefractiveIndexProfile::get16O16O16OV1LinesOpacity), "");
  cls_RefractiveIndexProfile.def("get16O16O16OV1LinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::get16O16O16OV1LinesOpacity), py::arg("nc"), R"doc(Function to retrieve the integrated 16O16O16O V1=1 Lines Opacity along the atmospheric path for channel nc in an RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("get16O16O16OV1LinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int, unsigned int)>(&RefractiveIndexProfile::get16O16O16OV1LinesOpacity), py::arg("spwid"), py::arg("nc"), "");
  cls_RefractiveIndexProfile.def("get16O16O16OV2LinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)()>(&RefractiveIndexProfile::get16O16O16OV2LinesOpacity), "");
  cls_RefractiveIndexProfile.def("get16O16O16OV2LinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::get16O16O16OV2LinesOpacity), py::arg("nc"), R"doc(Function to retrieve the integrated 16O16O16O V2=1 Lines Opacity along the atmospheric path for channel nc in an RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("get16O16O16OV2LinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int, unsigned int)>(&RefractiveIndexProfile::get16O16O16OV2LinesOpacity), py::arg("spwid"), py::arg("nc"), "");
  cls_RefractiveIndexProfile.def("get16O16O16OV3LinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)()>(&RefractiveIndexProfile::get16O16O16OV3LinesOpacity), "");
  cls_RefractiveIndexProfile.def("get16O16O16OV3LinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::get16O16O16OV3LinesOpacity), py::arg("nc"), R"doc(Function to retrieve the integrated 16O16O16O V3=1 Lines Opacity along the atmospheric path for channel nc in an RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("get16O16O16OV3LinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int, unsigned int)>(&RefractiveIndexProfile::get16O16O16OV3LinesOpacity), py::arg("spwid"), py::arg("nc"), "");
  cls_RefractiveIndexProfile.def("get16O16O17OLinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)()>(&RefractiveIndexProfile::get16O16O17OLinesOpacity), "");
  cls_RefractiveIndexProfile.def("get16O16O17OLinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::get16O16O17OLinesOpacity), py::arg("nc"), R"doc(Function to retrieve the integrated 16O16O17O Lines Opacity along the atmospheric path for channel nc in an RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("get16O16O17OLinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int, unsigned int)>(&RefractiveIndexProfile::get16O16O17OLinesOpacity), py::arg("spwid"), py::arg("nc"), "");
  cls_RefractiveIndexProfile.def("get16O16O18OLinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)()>(&RefractiveIndexProfile::get16O16O18OLinesOpacity), "");
  cls_RefractiveIndexProfile.def("get16O16O18OLinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::get16O16O18OLinesOpacity), py::arg("nc"), R"doc(Function to retrieve the integrated 16O16O18O Lines Opacity along the atmospheric path for channel nc in an RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("get16O16O18OLinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int, unsigned int)>(&RefractiveIndexProfile::get16O16O18OLinesOpacity), py::arg("spwid"), py::arg("nc"), "");
  cls_RefractiveIndexProfile.def("get16O17O16OLinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)()>(&RefractiveIndexProfile::get16O17O16OLinesOpacity), "");
  cls_RefractiveIndexProfile.def("get16O17O16OLinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::get16O17O16OLinesOpacity), py::arg("nc"), R"doc(Function to retrieve the integrated 16O17O16O Lines Opacity along the atmospheric path for channel nc in an RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("get16O17O16OLinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int, unsigned int)>(&RefractiveIndexProfile::get16O17O16OLinesOpacity), py::arg("spwid"), py::arg("nc"), "");
  cls_RefractiveIndexProfile.def("get16O18O16OLinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)()>(&RefractiveIndexProfile::get16O18O16OLinesOpacity), "");
  cls_RefractiveIndexProfile.def("get16O18O16OLinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::get16O18O16OLinesOpacity), py::arg("nc"), R"doc(Function to retrieve the integrated 16O18O16O Lines Opacity along the atmospheric path for channel nc in an RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("get16O18O16OLinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int, unsigned int)>(&RefractiveIndexProfile::get16O18O16OLinesOpacity), py::arg("spwid"), py::arg("nc"), "");
  cls_RefractiveIndexProfile.def("getCOLinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)()>(&RefractiveIndexProfile::getCOLinesOpacity), R"doc(Function to retrieve the integrated CO Lines Opacity along the atmospheric path for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("getCOLinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getCOLinesOpacity), py::arg("nc"), R"doc(Function to retrieve the integrated CO Lines Opacity along the atmospheric path for channel nc in an RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("getCOLinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int, unsigned int)>(&RefractiveIndexProfile::getCOLinesOpacity), py::arg("spwid"), py::arg("nc"), "");
  cls_RefractiveIndexProfile.def("getN2OLinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)()>(&RefractiveIndexProfile::getN2OLinesOpacity), R"doc(Function to retrieve the integrated N2O Lines Opacity along the atmospheric path for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("getN2OLinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getN2OLinesOpacity), py::arg("nc"), R"doc(Function to retrieve the integrated N2O Lines Opacity along the atmospheric path for channel nc in an RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("getN2OLinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int, unsigned int)>(&RefractiveIndexProfile::getN2OLinesOpacity), py::arg("spwid"), py::arg("nc"), "");
  cls_RefractiveIndexProfile.def("getNO2LinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)()>(&RefractiveIndexProfile::getNO2LinesOpacity), R"doc(Function to retrieve the integrated NO2 Lines Opacity along the atmospheric path for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("getNO2LinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getNO2LinesOpacity), py::arg("nc"), R"doc(Function to retrieve the integrated NO2 Lines Opacity along the atmospheric path for channel nc in an RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("getNO2LinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int, unsigned int)>(&RefractiveIndexProfile::getNO2LinesOpacity), py::arg("spwid"), py::arg("nc"), "");
  cls_RefractiveIndexProfile.def("getSO2LinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)()>(&RefractiveIndexProfile::getSO2LinesOpacity), R"doc(Function to retrieve the integrated SO2 Lines Opacity along the atmospheric path for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("getSO2LinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getSO2LinesOpacity), py::arg("nc"), R"doc(Function to retrieve the integrated SO2 Lines Opacity along the atmospheric path for channel nc in an RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("getSO2LinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int, unsigned int)>(&RefractiveIndexProfile::getSO2LinesOpacity), py::arg("spwid"), py::arg("nc"), "");
  cls_RefractiveIndexProfile.def("getHClLinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)()>(&RefractiveIndexProfile::getHClLinesOpacity), R"doc(Function to retrieve the integrated HCl Lines Opacity along the atmospheric path for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("getHClLinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getHClLinesOpacity), py::arg("nc"), R"doc(Function to retrieve the integrated HCl Lines Opacity along the atmospheric path for channel nc in an RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("getHClLinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int, unsigned int)>(&RefractiveIndexProfile::getHClLinesOpacity), py::arg("spwid"), py::arg("nc"), "");
  cls_RefractiveIndexProfile.def("getHCNLinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)()>(&RefractiveIndexProfile::getHCNLinesOpacity), R"doc(Function to retrieve the integrated HCN Lines Opacity along the atmospheric path for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("getHCNLinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getHCNLinesOpacity), py::arg("nc"), R"doc(Function to retrieve the integrated HCN Lines Opacity along the atmospheric path for channel nc in an RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("getHCNLinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(unsigned int, unsigned int)>(&RefractiveIndexProfile::getHCNLinesOpacity), py::arg("spwid"), py::arg("nc"), "");
  cls_RefractiveIndexProfile.def("getWetOpacity", static_cast<Opacity (RefractiveIndexProfile::*)()>(&RefractiveIndexProfile::getWetOpacity), R"doc(Function to retrieve the integrated Wet Opacity along the atmospheric path
corresponding to the 1st guess water column (from AtmProfile object) or the
for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("getWetOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(const Length &)>(&RefractiveIndexProfile::getWetOpacity), py::arg("integratedwatercolumn"), R"doc(Function to retrieve the integrated Wet Opacity along the atmospheric path
for a given integratedwatercolumn)doc");
  cls_RefractiveIndexProfile.def("getWetOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(const Length &, unsigned int)>(&RefractiveIndexProfile::getWetOpacity), py::arg("integratedwatercolumn"), py::arg("nc"), R"doc(Function to retrieve the integrated Wet Opacity along the atmospheric path
corresponding to a given water vapor column
for channel nc in an RefractiveIndexProfile
object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("getWetOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(const Length &, unsigned int, unsigned int)>(&RefractiveIndexProfile::getWetOpacity), py::arg("integratedwatercolumn"), py::arg("spwid"), py::arg("nc"), R"doc(Function to retrieve the integrated Wet Opacity along the atmospheric path
corresponding to a given water vapor column
for channel nc in an RefractiveIndexProfile
object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("getH2OLinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)()>(&RefractiveIndexProfile::getH2OLinesOpacity), R"doc(Function to retrieve the integrated H2O Lines Opacity along the atmospheric path
corresponding to the 1st guess water column (from AtmProfile object))doc");
  cls_RefractiveIndexProfile.def("getH2OLinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(const Length &)>(&RefractiveIndexProfile::getH2OLinesOpacity), py::arg("integratedwatercolumn"), R"doc(Function to retrieve the integrated H2O Lines Opacity along the atmospheric path
corresponding to a given water vapor column)doc");
  cls_RefractiveIndexProfile.def("getH2OLinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(const Length &, unsigned int)>(&RefractiveIndexProfile::getH2OLinesOpacity), py::arg("integratedwatercolumn"), py::arg("nc"), R"doc(Function to retrieve the integrated H2O Lines Opacity along the atmospheric path
corresponding to a given water vapor column
for channel nc in an RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("getH2OLinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(const Length &, unsigned int, unsigned int)>(&RefractiveIndexProfile::getH2OLinesOpacity), py::arg("integratedwatercolumn"), py::arg("spwid"), py::arg("nc"), R"doc(Function to retrieve the integrated H2O Lines Opacity along the atmospheric path
corresponding to a given water vapor column
for channel nc in an RefractiveIndexProfile object of a spectral window)doc");
  cls_RefractiveIndexProfile.def("getHH16OLinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)()>(&RefractiveIndexProfile::getHH16OLinesOpacity), R"doc(Function to retrieve the integrated HH16O Lines Opacity along the atmospheric path
corresponding to the 1st guess water column (from AtmProfile object))doc");
  cls_RefractiveIndexProfile.def("getHH16OLinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(const Length &)>(&RefractiveIndexProfile::getHH16OLinesOpacity), py::arg("integratedwatercolumn"), R"doc(Function to retrieve the integrated HH16O Lines Opacity along the atmospheric path
corresponding to a given water vapor column)doc");
  cls_RefractiveIndexProfile.def("getHH16OLinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(const Length &, unsigned int)>(&RefractiveIndexProfile::getHH16OLinesOpacity), py::arg("integratedwatercolumn"), py::arg("nc"), R"doc(Function to retrieve the integrated HH16O Lines Opacity along the atmospheric path
corresponding to a given water vapor column
for channel nc in an RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("getHH16OLinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(const Length &, unsigned int, unsigned int)>(&RefractiveIndexProfile::getHH16OLinesOpacity), py::arg("integratedwatercolumn"), py::arg("spwid"), py::arg("nc"), R"doc(Function to retrieve the integrated HH16O Lines Opacity along the atmospheric path
corresponding to a given water vapor column
for channel nc in an RefractiveIndexProfile object of a spectral window)doc");
  cls_RefractiveIndexProfile.def("getH2OContOpacity", static_cast<Opacity (RefractiveIndexProfile::*)()>(&RefractiveIndexProfile::getH2OContOpacity), R"doc(Function to retrieve the integrated HH16O Continuum Opacity along the atmospheric path
corresponding to the 1st guess water column (from AtmProfile object))doc");
  cls_RefractiveIndexProfile.def("getH2OContOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(const Length &)>(&RefractiveIndexProfile::getH2OContOpacity), py::arg("integratedwatercolumn"), R"doc(Function to retrieve the integrated H2O Continuum Opacity along the atmospheric path
corresponding to a given water vapor column)doc");
  cls_RefractiveIndexProfile.def("getH2OContOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(const Length &, unsigned int)>(&RefractiveIndexProfile::getH2OContOpacity), py::arg("integratedwatercolumn"), py::arg("nc"), R"doc(Function to retrieve the integrated H2O Continuum Opacity along the atmospheric path
corresponding to a given water vapor column
for channel nc in an RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("getH2OContOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(const Length &, unsigned int, unsigned int)>(&RefractiveIndexProfile::getH2OContOpacity), py::arg("integratedwatercolumn"), py::arg("spwid"), py::arg("nc"), R"doc(Function to retrieve the integrated H2O Continuum Opacity along the atmospheric path
corresponding to a given water vapor column
for channel nc in an RefractiveIndexProfile object of a spectral window)doc");
  cls_RefractiveIndexProfile.def("getAverageWetOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(const Length &, unsigned int)>(&RefractiveIndexProfile::getAverageWetOpacity), py::arg("integratedwatercolumn"), py::arg("spwid"), "");
  cls_RefractiveIndexProfile.def("getAverageH2OLinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(const Length &, unsigned int)>(&RefractiveIndexProfile::getAverageH2OLinesOpacity), py::arg("integratedwatercolumn"), py::arg("spwid"), "");
  cls_RefractiveIndexProfile.def("getAverageHH16OLinesOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(const Length &, unsigned int)>(&RefractiveIndexProfile::getAverageHH16OLinesOpacity), py::arg("integratedwatercolumn"), py::arg("spwid"), "");
  cls_RefractiveIndexProfile.def("getAverageH2OContOpacity", static_cast<Opacity (RefractiveIndexProfile::*)(const Length &, unsigned int)>(&RefractiveIndexProfile::getAverageH2OContOpacity), py::arg("integratedwatercolumn"), py::arg("spwid"), "");
  cls_RefractiveIndexProfile.def("getNonDispersiveDryPhaseDelay", static_cast<Angle (RefractiveIndexProfile::*)()>(&RefractiveIndexProfile::getNonDispersiveDryPhaseDelay), R"doc(Function to retrieve the integrated Atmospheric Phase Delay (Dry part) along the atmospheric path
corresponding to a given water vapor column
for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("getNonDispersiveDryPathLength", static_cast<Length (RefractiveIndexProfile::*)()>(&RefractiveIndexProfile::getNonDispersiveDryPathLength), R"doc(Function to retrieve the integrated Atmospheric Path length (Dry part) along the atmospheric path
corresponding to a given water vapor column
for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("getNonDispersiveDryPhaseDelay", static_cast<Angle (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getNonDispersiveDryPhaseDelay), py::arg("nc"), R"doc(Function to retrieve the integrated Atmospheric Phase Delay (Dry part) along the atmospheric path
corresponding to a given water vapor column
for channel nc in an RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("getNonDispersiveDryPathLength", static_cast<Length (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getNonDispersiveDryPathLength), py::arg("nc"), R"doc(Function to retrieve the integrated Atmospheric Path length (Dry part) along the atmospheric path
corresponding to a given water vapor column
for channel nc in an RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("getNonDispersiveDryPhaseDelay", static_cast<Angle (RefractiveIndexProfile::*)(unsigned int, unsigned int)>(&RefractiveIndexProfile::getNonDispersiveDryPhaseDelay), py::arg("spwid"), py::arg("nc"), R"doc(Function to retrieve the integrated Atmospheric Phase Delay (Dry part) along the atmospheric path
corresponding to a given water vapor column
for single frequency RefractiveIndexProfile object with several Spectral Grids)doc");
  cls_RefractiveIndexProfile.def("getNonDispersiveDryPathLength", static_cast<Length (RefractiveIndexProfile::*)(unsigned int, unsigned int)>(&RefractiveIndexProfile::getNonDispersiveDryPathLength), py::arg("spwid"), py::arg("nc"), R"doc(Function to retrieve the integrated Atmospheric Path length (Dry part) along the atmospheric path
corresponding to a given water vapor column
for channel nc in an RefractiveIndexProfile object with everal Spectral Grids)doc");
  cls_RefractiveIndexProfile.def("getDispersiveDryPhaseDelay", static_cast<Angle (RefractiveIndexProfile::*)()>(&RefractiveIndexProfile::getDispersiveDryPhaseDelay), R"doc(Function to retrieve the integrated Atmospheric Phase Delay (Dry part) along the atmospheric path
corresponding to a given water vapor column
for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("getDispersiveDryPathLength", static_cast<Length (RefractiveIndexProfile::*)()>(&RefractiveIndexProfile::getDispersiveDryPathLength), R"doc(Function to retrieve the integrated Atmospheric Path length (Dry part) along the atmospheric path
corresponding to a given water vapor column
for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("getDispersiveDryPhaseDelay", static_cast<Angle (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getDispersiveDryPhaseDelay), py::arg("nc"), R"doc(Function to retrieve the integrated Atmospheric Phase Delay (Dry part) along the atmospheric path
corresponding to a given water vapor column
for channel nc in an RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("getDispersiveDryPathLength", static_cast<Length (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getDispersiveDryPathLength), py::arg("nc"), R"doc(Function to retrieve the integrated Atmospheric Path length (Dry part) along the atmospheric path
corresponding to a given water vapor column
for channel nc in an RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("getDispersiveDryPhaseDelay", static_cast<Angle (RefractiveIndexProfile::*)(unsigned int, unsigned int)>(&RefractiveIndexProfile::getDispersiveDryPhaseDelay), py::arg("spwid"), py::arg("nc"), R"doc(Function to retrieve the integrated Atmospheric Phase Delay (Dry part) along the atmospheric path
corresponding to a given water vapor column
for single frequency RefractiveIndexProfile object with several Spectral Grids)doc");
  cls_RefractiveIndexProfile.def("getDispersiveDryPathLength", static_cast<Length (RefractiveIndexProfile::*)(unsigned int, unsigned int)>(&RefractiveIndexProfile::getDispersiveDryPathLength), py::arg("spwid"), py::arg("nc"), R"doc(Function to retrieve the integrated Atmospheric Path length (Dry part) along the atmospheric path
corresponding to a given water vapor column
for channel nc in an RefractiveIndexProfile object with everal Spectral Grids)doc");
  cls_RefractiveIndexProfile.def("getAverageNonDispersiveDryPathLength", static_cast<Length (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getAverageNonDispersiveDryPathLength), py::arg("spwid"), R"doc(Function to retrieve the average integrated Atmospheric Path Length (Dry part) in spectral Window spwid)doc");
  cls_RefractiveIndexProfile.def("getAverageDispersiveDryPathLength", static_cast<Length (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getAverageDispersiveDryPathLength), py::arg("spwid"), R"doc(Function to retrieve the average integrated Atmospheric Path Length (Dry part) in spectral Window spwid)doc");
  cls_RefractiveIndexProfile.def("getAverageNonDispersiveDryPhaseDelay", static_cast<Angle (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getAverageNonDispersiveDryPhaseDelay), py::arg("spwid"), R"doc(Function to retrieve the average integrated Atmospheric Phase Delay (Dry part) in spectral Window spwid)doc");
  cls_RefractiveIndexProfile.def("getAverageDispersiveDryPhaseDelay", static_cast<Angle (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getAverageDispersiveDryPhaseDelay), py::arg("spwid"), R"doc(Function to retrieve the average integrated Atmospheric Phase Delay (Dry part) in spectral Window spwid)doc");
  cls_RefractiveIndexProfile.def("getO2LinesPhaseDelay", static_cast<Angle (RefractiveIndexProfile::*)()>(&RefractiveIndexProfile::getO2LinesPhaseDelay), R"doc(Function to retrieve the integrated Atmospheric Phase Delay (due to O2 lines) along the atmospheric path
corresponding to a given water vapor column
for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("getO2LinesPathLength", static_cast<Length (RefractiveIndexProfile::*)()>(&RefractiveIndexProfile::getO2LinesPathLength), R"doc(Function to retrieve the integrated Atmospheric Path length (due to O2 Lines) along the atmospheric path
corresponding to a given water vapor column
for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("getO2LinesPhaseDelay", static_cast<Angle (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getO2LinesPhaseDelay), py::arg("nc"), R"doc(Function to retrieve the integrated Atmospheric Phase Delay (due to O2 Lines) along the atmospheric path
corresponding to a given water vapor column
for channel nc in an RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("getO2LinesPathLength", static_cast<Length (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getO2LinesPathLength), py::arg("nc"), R"doc(Function to retrieve the integrated Atmospheric Path length (due to O2 Lines) along the atmospheric path
corresponding to a given water vapor column
for channel nc in an RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("getO2LinesPhaseDelay", static_cast<Angle (RefractiveIndexProfile::*)(unsigned int, unsigned int)>(&RefractiveIndexProfile::getO2LinesPhaseDelay), py::arg("spwid"), py::arg("nc"), R"doc(Function to retrieve the integrated Atmospheric Phase Delay (due to O2 Lines) along the atmospheric path
corresponding to a given water vapor column
for single frequency RefractiveIndexProfile object with several Spectral Grids)doc");
  cls_RefractiveIndexProfile.def("getAverageO2LinesPhaseDelay", static_cast<Angle (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getAverageO2LinesPhaseDelay), py::arg("spwid"), R"doc(Function to retrieve the average integrated Atmospheric Phase Delay (due to O2 Lines) in spectral Window spwid)doc");
  cls_RefractiveIndexProfile.def("getO2LinesPathLength", static_cast<Length (RefractiveIndexProfile::*)(unsigned int, unsigned int)>(&RefractiveIndexProfile::getO2LinesPathLength), py::arg("spwid"), py::arg("nc"), R"doc(Function to retrieve the integrated Atmospheric Path length (due to O2 Lines) along the atmospheric path
corresponding to a given water vapor column
for channel nc in an RefractiveIndexProfile object with everal Spectral Grids)doc");
  cls_RefractiveIndexProfile.def("getAverageO2LinesPathLength", static_cast<Length (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getAverageO2LinesPathLength), py::arg("spwid"), R"doc(Function to retrieve the average integrated Atmospheric Path Length (due to O2 Lines) in spectral Window spwid)doc");
  cls_RefractiveIndexProfile.def("getO3LinesPhaseDelay", static_cast<Angle (RefractiveIndexProfile::*)()>(&RefractiveIndexProfile::getO3LinesPhaseDelay), R"doc(Function to retrieve the integrated Atmospheric Phase Delay (due to O3 lines) along the atmospheric path
corresponding to a given water vapor column
for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("getO3LinesPathLength", static_cast<Length (RefractiveIndexProfile::*)()>(&RefractiveIndexProfile::getO3LinesPathLength), R"doc(Function to retrieve the integrated Atmospheric Path length (due to O3 Lines) along the atmospheric path
corresponding to a given water vapor column
for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("getO3LinesPhaseDelay", static_cast<Angle (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getO3LinesPhaseDelay), py::arg("nc"), R"doc(Function to retrieve the integrated Atmospheric Phase Delay (due to O3 Lines) along the atmospheric path
corresponding to a given water vapor column
for channel nc in an RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("getO3LinesPathLength", static_cast<Length (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getO3LinesPathLength), py::arg("nc"), R"doc(Function to retrieve the integrated Atmospheric Path length (due to O3 Lines) along the atmospheric path
corresponding to a given water vapor column
for channel nc in an RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("getO3LinesPhaseDelay", static_cast<Angle (RefractiveIndexProfile::*)(unsigned int, unsigned int)>(&RefractiveIndexProfile::getO3LinesPhaseDelay), py::arg("spwid"), py::arg("nc"), R"doc(Function to retrieve the integrated Atmospheric Phase Delay (due to O3 Lines) along the atmospheric path
corresponding to a given water vapor column
for single frequency RefractiveIndexProfile object with several Spectral Grids)doc");
  cls_RefractiveIndexProfile.def("getAverageO3LinesPhaseDelay", static_cast<Angle (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getAverageO3LinesPhaseDelay), py::arg("spwid"), R"doc(Function to retrieve the average integrated Atmospheric Phase Delay (due to O3 Lines) in spectral Window spwid)doc");
  cls_RefractiveIndexProfile.def("getO3LinesPathLength", static_cast<Length (RefractiveIndexProfile::*)(unsigned int, unsigned int)>(&RefractiveIndexProfile::getO3LinesPathLength), py::arg("spwid"), py::arg("nc"), R"doc(Function to retrieve the integrated Atmospheric Path length (due to O3 Lines) along the atmospheric path
corresponding to a given water vapor column
for channel nc in an RefractiveIndexProfile object with everal Spectral Grids)doc");
  cls_RefractiveIndexProfile.def("getAverageO3LinesPathLength", static_cast<Length (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getAverageO3LinesPathLength), py::arg("spwid"), R"doc(Function to retrieve the average integrated Atmospheric Path Length (due to O3 Lines) in spectral Window spwid)doc");
  cls_RefractiveIndexProfile.def("getCOLinesPhaseDelay", static_cast<Angle (RefractiveIndexProfile::*)()>(&RefractiveIndexProfile::getCOLinesPhaseDelay), R"doc(Function to retrieve the integrated Atmospheric Phase Delay (due to CO lines) along the atmospheric path
corresponding to a given water vapor column
for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("getCOLinesPathLength", static_cast<Length (RefractiveIndexProfile::*)()>(&RefractiveIndexProfile::getCOLinesPathLength), R"doc(Function to retrieve the integrated Atmospheric Path length (due to CO Lines) along the atmospheric path
corresponding to a given water vapor column
for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("getCOLinesPhaseDelay", static_cast<Angle (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getCOLinesPhaseDelay), py::arg("nc"), R"doc(Function to retrieve the integrated Atmospheric Phase Delay (due to CO Lines) along the atmospheric path
corresponding to a given water vapor column
for channel nc in an RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("getCOLinesPathLength", static_cast<Length (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getCOLinesPathLength), py::arg("nc"), R"doc(Function to retrieve the integrated Atmospheric Path length (due to CO Lines) along the atmospheric path
corresponding to a given water vapor column
for channel nc in an RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("getCOLinesPhaseDelay", static_cast<Angle (RefractiveIndexProfile::*)(unsigned int, unsigned int)>(&RefractiveIndexProfile::getCOLinesPhaseDelay), py::arg("spwid"), py::arg("nc"), R"doc(Function to retrieve the integrated Atmospheric Phase Delay (due to CO Lines) along the atmospheric path
corresponding to a given water vapor column
for single frequency RefractiveIndexProfile object with several Spectral Grids)doc");
  cls_RefractiveIndexProfile.def("getAverageCOLinesPhaseDelay", static_cast<Angle (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getAverageCOLinesPhaseDelay), py::arg("spwid"), R"doc(Function to retrieve the average integrated Atmospheric Phase Delay (due to CO Lines) in spectral Window spwid)doc");
  cls_RefractiveIndexProfile.def("getCOLinesPathLength", static_cast<Length (RefractiveIndexProfile::*)(unsigned int, unsigned int)>(&RefractiveIndexProfile::getCOLinesPathLength), py::arg("spwid"), py::arg("nc"), R"doc(Function to retrieve the integrated Atmospheric Path length (due to CO Lines) along the atmospheric path
corresponding to a given water vapor column
for channel nc in an RefractiveIndexProfile object with everal Spectral Grids)doc");
  cls_RefractiveIndexProfile.def("getAverageCOLinesPathLength", static_cast<Length (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getAverageCOLinesPathLength), py::arg("spwid"), R"doc(Function to retrieve the average integrated Atmospheric Path Length (due to CO Lines) in spectral Window spwid)doc");
  cls_RefractiveIndexProfile.def("getN2OLinesPhaseDelay", static_cast<Angle (RefractiveIndexProfile::*)()>(&RefractiveIndexProfile::getN2OLinesPhaseDelay), R"doc(Function to retrieve the integrated Atmospheric Phase Delay (due to N2O lines) along the atmospheric path
corresponding to a given water vapor column
for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("getN2OLinesPathLength", static_cast<Length (RefractiveIndexProfile::*)()>(&RefractiveIndexProfile::getN2OLinesPathLength), R"doc(Function to retrieve the integrated Atmospheric Path length (due to N2O Lines) along the atmospheric path
corresponding to a given water vapor column
for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("getN2OLinesPhaseDelay", static_cast<Angle (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getN2OLinesPhaseDelay), py::arg("nc"), R"doc(Function to retrieve the integrated Atmospheric Phase Delay (due to N2O Lines) along the atmospheric path
corresponding to a given water vapor column
for channel nc in an RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("getN2OLinesPathLength", static_cast<Length (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getN2OLinesPathLength), py::arg("nc"), R"doc(Function to retrieve the integrated Atmospheric Path length (due to N2O Lines) along the atmospheric path
corresponding to a given water vapor column
for channel nc in an RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("getN2OLinesPhaseDelay", static_cast<Angle (RefractiveIndexProfile::*)(unsigned int, unsigned int)>(&RefractiveIndexProfile::getN2OLinesPhaseDelay), py::arg("spwid"), py::arg("nc"), R"doc(Function to retrieve the integrated Atmospheric Phase Delay (due to N2O Lines) along the atmospheric path
corresponding to a given water vapor column
for single frequency RefractiveIndexProfile object with several Spectral Grids)doc");
  cls_RefractiveIndexProfile.def("getAverageN2OLinesPhaseDelay", static_cast<Angle (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getAverageN2OLinesPhaseDelay), py::arg("spwid"), R"doc(Function to retrieve the average integrated Atmospheric Phase Delay (due to N2O Lines) in spectral Window spwid)doc");
  cls_RefractiveIndexProfile.def("getN2OLinesPathLength", static_cast<Length (RefractiveIndexProfile::*)(unsigned int, unsigned int)>(&RefractiveIndexProfile::getN2OLinesPathLength), py::arg("spwid"), py::arg("nc"), R"doc(Function to retrieve the integrated Atmospheric Path length (due to N2O Lines) along the atmospheric path
corresponding to a given water vapor column
for channel nc in an RefractiveIndexProfile object with everal Spectral Grids)doc");
  cls_RefractiveIndexProfile.def("getAverageN2OLinesPathLength", static_cast<Length (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getAverageN2OLinesPathLength), py::arg("spwid"), R"doc(Function to retrieve the average integrated Atmospheric Path Length (due to N2O Lines) in spectral Window spwid)doc");
  cls_RefractiveIndexProfile.def("getNO2LinesPhaseDelay", static_cast<Angle (RefractiveIndexProfile::*)()>(&RefractiveIndexProfile::getNO2LinesPhaseDelay), R"doc(Function to retrieve the integrated Atmospheric Phase Delay (due to NO2 lines) along the atmospheric path
corresponding to a given water vapor column
for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("getNO2LinesPathLength", static_cast<Length (RefractiveIndexProfile::*)()>(&RefractiveIndexProfile::getNO2LinesPathLength), R"doc(Function to retrieve the integrated Atmospheric Path length (due to NO2 Lines) along the atmospheric path
corresponding to a given water vapor column
for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("getNO2LinesPhaseDelay", static_cast<Angle (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getNO2LinesPhaseDelay), py::arg("nc"), R"doc(Function to retrieve the integrated Atmospheric Phase Delay (due to NO2 Lines) along the atmospheric path
corresponding to a given water vapor column
for channel nc in an RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("getNO2LinesPathLength", static_cast<Length (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getNO2LinesPathLength), py::arg("nc"), R"doc(Function to retrieve the integrated Atmospheric Path length (due to NO2 Lines) along the atmospheric path
corresponding to a given water vapor column
for channel nc in an RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("getNO2LinesPhaseDelay", static_cast<Angle (RefractiveIndexProfile::*)(unsigned int, unsigned int)>(&RefractiveIndexProfile::getNO2LinesPhaseDelay), py::arg("spwid"), py::arg("nc"), R"doc(Function to retrieve the integrated Atmospheric Phase Delay (due to NO2 Lines) along the atmospheric path
corresponding to a given water vapor column
for single frequency RefractiveIndexProfile object with several Spectral Grids)doc");
  cls_RefractiveIndexProfile.def("getAverageNO2LinesPhaseDelay", static_cast<Angle (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getAverageNO2LinesPhaseDelay), py::arg("spwid"), R"doc(Function to retrieve the average integrated Atmospheric Phase Delay (due to NO2 Lines) in spectral Window spwid)doc");
  cls_RefractiveIndexProfile.def("getNO2LinesPathLength", static_cast<Length (RefractiveIndexProfile::*)(unsigned int, unsigned int)>(&RefractiveIndexProfile::getNO2LinesPathLength), py::arg("spwid"), py::arg("nc"), R"doc(Function to retrieve the integrated Atmospheric Path length (due to NO2 Lines) along the atmospheric path
corresponding to a given water vapor column
for channel nc in an RefractiveIndexProfile object with everal Spectral Grids)doc");
  cls_RefractiveIndexProfile.def("getAverageNO2LinesPathLength", static_cast<Length (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getAverageNO2LinesPathLength), py::arg("spwid"), R"doc(Function to retrieve the average integrated Atmospheric Path Length (due to NO2 Lines) in spectral Window spwid)doc");
  cls_RefractiveIndexProfile.def("getSO2LinesPhaseDelay", static_cast<Angle (RefractiveIndexProfile::*)()>(&RefractiveIndexProfile::getSO2LinesPhaseDelay), R"doc(Function to retrieve the integrated Atmospheric Phase Delay (due to SO2 lines) along the atmospheric path
corresponding to a given water vapor column
for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("getSO2LinesPathLength", static_cast<Length (RefractiveIndexProfile::*)()>(&RefractiveIndexProfile::getSO2LinesPathLength), R"doc(Function to retrieve the integrated Atmospheric Path length (due to SO2 Lines) along the atmospheric path
corresponding to a given water vapor column
for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("getSO2LinesPhaseDelay", static_cast<Angle (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getSO2LinesPhaseDelay), py::arg("nc"), R"doc(Function to retrieve the integrated Atmospheric Phase Delay (due to SO2 Lines) along the atmospheric path
corresponding to a given water vapor column
for channel nc in an RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("getSO2LinesPathLength", static_cast<Length (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getSO2LinesPathLength), py::arg("nc"), R"doc(Function to retrieve the integrated Atmospheric Path length (due to SO2 Lines) along the atmospheric path
corresponding to a given water vapor column
for channel nc in an RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("getSO2LinesPhaseDelay", static_cast<Angle (RefractiveIndexProfile::*)(unsigned int, unsigned int)>(&RefractiveIndexProfile::getSO2LinesPhaseDelay), py::arg("spwid"), py::arg("nc"), R"doc(Function to retrieve the integrated Atmospheric Phase Delay (due to SO2 Lines) along the atmospheric path
corresponding to a given water vapor column
for single frequency RefractiveIndexProfile object with several Spectral Grids)doc");
  cls_RefractiveIndexProfile.def("getAverageSO2LinesPhaseDelay", static_cast<Angle (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getAverageSO2LinesPhaseDelay), py::arg("spwid"), R"doc(Function to retrieve the average integrated Atmospheric Phase Delay (due to SO2 Lines) in spectral Window spwid)doc");
  cls_RefractiveIndexProfile.def("getSO2LinesPathLength", static_cast<Length (RefractiveIndexProfile::*)(unsigned int, unsigned int)>(&RefractiveIndexProfile::getSO2LinesPathLength), py::arg("spwid"), py::arg("nc"), R"doc(Function to retrieve the integrated Atmospheric Path length (due to SO2 Lines) along the atmospheric path
corresponding to a given water vapor column
for channel nc in an RefractiveIndexProfile object with everal Spectral Grids)doc");
  cls_RefractiveIndexProfile.def("getAverageSO2LinesPathLength", static_cast<Length (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getAverageSO2LinesPathLength), py::arg("spwid"), R"doc(Function to retrieve the average integrated Atmospheric Path Length (due to SO2 Lines) in spectral Window spwid)doc");
  cls_RefractiveIndexProfile.def("getHClLinesPhaseDelay", static_cast<Angle (RefractiveIndexProfile::*)()>(&RefractiveIndexProfile::getHClLinesPhaseDelay), R"doc(Function to retrieve the integrated Atmospheric Phase Delay (due to HCl lines) along the atmospheric path
corresponding to a given water vapor column
for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("getHClLinesPathLength", static_cast<Length (RefractiveIndexProfile::*)()>(&RefractiveIndexProfile::getHClLinesPathLength), R"doc(Function to retrieve the integrated Atmospheric Path length (due to HCl Lines) along the atmospheric path
corresponding to a given water vapor column
for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("getHClLinesPhaseDelay", static_cast<Angle (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getHClLinesPhaseDelay), py::arg("nc"), R"doc(Function to retrieve the integrated Atmospheric Phase Delay (due to HCl Lines) along the atmospheric path
corresponding to a given water vapor column
for channel nc in an RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("getHClLinesPathLength", static_cast<Length (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getHClLinesPathLength), py::arg("nc"), R"doc(Function to retrieve the integrated Atmospheric Path length (due to HCl Lines) along the atmospheric path
corresponding to a given water vapor column
for channel nc in an RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("getHClLinesPhaseDelay", static_cast<Angle (RefractiveIndexProfile::*)(unsigned int, unsigned int)>(&RefractiveIndexProfile::getHClLinesPhaseDelay), py::arg("spwid"), py::arg("nc"), R"doc(Function to retrieve the integrated Atmospheric Phase Delay (due to HCl Lines) along the atmospheric path
corresponding to a given water vapor column
for single frequency RefractiveIndexProfile object with several Spectral Grids)doc");
  cls_RefractiveIndexProfile.def("getAverageHClLinesPhaseDelay", static_cast<Angle (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getAverageHClLinesPhaseDelay), py::arg("spwid"), R"doc(Function to retrieve the average integrated Atmospheric Phase Delay (due to HCl Lines) in spectral Window spwid)doc");
  cls_RefractiveIndexProfile.def("getHClLinesPathLength", static_cast<Length (RefractiveIndexProfile::*)(unsigned int, unsigned int)>(&RefractiveIndexProfile::getHClLinesPathLength), py::arg("spwid"), py::arg("nc"), R"doc(Function to retrieve the integrated Atmospheric Path length (due to HCl Lines) along the atmospheric path
corresponding to a given water vapor column
for channel nc in an RefractiveIndexProfile object with everal Spectral Grids)doc");
  cls_RefractiveIndexProfile.def("getAverageHClLinesPathLength", static_cast<Length (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getAverageHClLinesPathLength), py::arg("spwid"), R"doc(Function to retrieve the average integrated Atmospheric Path Length (due to HCl Lines) in spectral Window spwid)doc");
  cls_RefractiveIndexProfile.def("getHCNLinesPhaseDelay", static_cast<Angle (RefractiveIndexProfile::*)()>(&RefractiveIndexProfile::getHCNLinesPhaseDelay), R"doc(Function to retrieve the integrated Atmospheric Phase Delay (due to HCN lines) along the atmospheric path
corresponding to a given water vapor column
for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("getHCNLinesPathLength", static_cast<Length (RefractiveIndexProfile::*)()>(&RefractiveIndexProfile::getHCNLinesPathLength), R"doc(Function to retrieve the integrated Atmospheric Path length (due to HCN Lines) along the atmospheric path
corresponding to a given water vapor column
for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("getHCNLinesPhaseDelay", static_cast<Angle (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getHCNLinesPhaseDelay), py::arg("nc"), R"doc(Function to retrieve the integrated Atmospheric Phase Delay (due to HCN Lines) along the atmospheric path
corresponding to a given water vapor column
for channel nc in an RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("getHCNLinesPathLength", static_cast<Length (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getHCNLinesPathLength), py::arg("nc"), R"doc(Function to retrieve the integrated Atmospheric Path length (due to HCN Lines) along the atmospheric path
corresponding to a given water vapor column
for channel nc in an RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("getHCNLinesPhaseDelay", static_cast<Angle (RefractiveIndexProfile::*)(unsigned int, unsigned int)>(&RefractiveIndexProfile::getHCNLinesPhaseDelay), py::arg("spwid"), py::arg("nc"), R"doc(Function to retrieve the integrated Atmospheric Phase Delay (due to HCN Lines) along the atmospheric path
corresponding to a given water vapor column
for single frequency RefractiveIndexProfile object with several Spectral Grids)doc");
  cls_RefractiveIndexProfile.def("getAverageHCNLinesPhaseDelay", static_cast<Angle (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getAverageHCNLinesPhaseDelay), py::arg("spwid"), R"doc(Function to retrieve the average integrated Atmospheric Phase Delay (due to HCN Lines) in spectral Window spwid)doc");
  cls_RefractiveIndexProfile.def("getHCNLinesPathLength", static_cast<Length (RefractiveIndexProfile::*)(unsigned int, unsigned int)>(&RefractiveIndexProfile::getHCNLinesPathLength), py::arg("spwid"), py::arg("nc"), R"doc(Function to retrieve the integrated Atmospheric Path length (due to HCN Lines) along the atmospheric path
corresponding to a given water vapor column
for channel nc in an RefractiveIndexProfile object with everal Spectral Grids)doc");
  cls_RefractiveIndexProfile.def("getAverageHCNLinesPathLength", static_cast<Length (RefractiveIndexProfile::*)(unsigned int)>(&RefractiveIndexProfile::getAverageHCNLinesPathLength), py::arg("spwid"), R"doc(Function to retrieve the average integrated Atmospheric Path Length (due to HCN Lines) in spectral Window spwid)doc");
  cls_RefractiveIndexProfile.def("getDispersiveH2OPhaseDelay", static_cast<Angle (RefractiveIndexProfile::*)()>(&RefractiveIndexProfile::getDispersiveH2OPhaseDelay), R"doc(Function to retrieve the integrated Atmospheric Phase Delay (Dispersive part) along the atmospheric path
corresponding to the 1st guess water column (from AtmProfile object)
for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("getDispersiveH2OPhaseDelay", static_cast<Angle (RefractiveIndexProfile::*)(const Length &)>(&RefractiveIndexProfile::getDispersiveH2OPhaseDelay), py::arg("integratedwatercolumn"), R"doc(Function to retrieve the integrated Atmospheric Phase Delay (Dispersive part) along the atmospheric path
corresponding to a given water vapor column
for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("getDispersiveH2OPathLength", static_cast<Length (RefractiveIndexProfile::*)()>(&RefractiveIndexProfile::getDispersiveH2OPathLength), R"doc(Function to retrieve the integrated Atmospheric Path length (Dispersive part) along the atmospheric path
corresponding to the 1st guess water column (from AtmProfile object)
for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("getDispersiveH2OPathLength", static_cast<Length (RefractiveIndexProfile::*)(const Length &)>(&RefractiveIndexProfile::getDispersiveH2OPathLength), py::arg("integratedwatercolumn"), R"doc(Function to retrieve the integrated Atmospheric Path length (Dispersive part) along the atmospheric path
corresponding to a given water vapor column
for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("getDispersiveH2OPhaseDelay", static_cast<Angle (RefractiveIndexProfile::*)(const Length &, unsigned int)>(&RefractiveIndexProfile::getDispersiveH2OPhaseDelay), py::arg("integratedwatercolumn"), py::arg("nc"), R"doc(Function to retrieve the integrated Atmospheric Phase Delay (Dispersive part) along the atmospheric path
corresponding to a given water vapor column
for channel nc in an RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("getDispersiveH2OPathLength", static_cast<Length (RefractiveIndexProfile::*)(const Length &, unsigned int)>(&RefractiveIndexProfile::getDispersiveH2OPathLength), py::arg("integratedwatercolumn"), py::arg("nc"), R"doc(Function to retrieve the integrated Atmospheric Path length (Dispersive part) along the atmospheric path
corresponding to a given water vapor column
for channel nc in an RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("getDispersiveH2OPhaseDelay", static_cast<Angle (RefractiveIndexProfile::*)(const Length &, unsigned int, unsigned int)>(&RefractiveIndexProfile::getDispersiveH2OPhaseDelay), py::arg("integratedwatercolumn"), py::arg("spwid"), py::arg("nc"), R"doc(Function to retrieve the integrated Atmospheric Phase Delay (Dispersive part) along the atmospheric path
corresponding to a given water vapor column
for single frequency RefractiveIndexProfile object with several Spectral Grids)doc");
  cls_RefractiveIndexProfile.def("getAverageDispersiveH2OPhaseDelay", static_cast<Angle (RefractiveIndexProfile::*)(const Length &, unsigned int)>(&RefractiveIndexProfile::getAverageDispersiveH2OPhaseDelay), py::arg("integratedwatercolumn"), py::arg("spwid"), R"doc(Function to retrieve the average integrated Atmospheric Phase Delay (Dispersive part) in spectral Window spwid)doc");
  cls_RefractiveIndexProfile.def("getDispersiveH2OPathLength", static_cast<Length (RefractiveIndexProfile::*)(const Length &, unsigned int, unsigned int)>(&RefractiveIndexProfile::getDispersiveH2OPathLength), py::arg("integratedwatercolumn"), py::arg("spwid"), py::arg("nc"), R"doc(Function to retrieve the integrated Atmospheric Path length (Dispersive part) along the atmospheric path
corresponding to a given water vapor column
for channel nc in an RefractiveIndexProfile object with everal Spectral Grids)doc");
  cls_RefractiveIndexProfile.def("getAverageDispersiveH2OPathLength", static_cast<Length (RefractiveIndexProfile::*)(const Length &, unsigned int)>(&RefractiveIndexProfile::getAverageDispersiveH2OPathLength), py::arg("integratedwatercolumn"), py::arg("spwid"), R"doc(Function to retrieve the average integrated Atmospheric Path Length (Dispersive part) in spectral Window spwid)doc");
  cls_RefractiveIndexProfile.def("getNonDispersiveH2OPhaseDelay", static_cast<Angle (RefractiveIndexProfile::*)()>(&RefractiveIndexProfile::getNonDispersiveH2OPhaseDelay), R"doc(Function to retrieve the integrated Atmospheric Phase Delay (Non-Dispersive part) along the atmospheric path
corresponding to the 1st guess water column (from AtmProfile object)
for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("getNonDispersiveH2OPhaseDelay", static_cast<Angle (RefractiveIndexProfile::*)(const Length &)>(&RefractiveIndexProfile::getNonDispersiveH2OPhaseDelay), py::arg("integratedwatercolumn"), R"doc(Function to retrieve the integrated Atmospheric Phase Delay (Non-Dispersive part) along the atmospheric path
corresponding to a given water vapor column
for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("getNonDispersiveH2OPathLength", static_cast<Length (RefractiveIndexProfile::*)()>(&RefractiveIndexProfile::getNonDispersiveH2OPathLength), R"doc(Function to retrieve the integrated Atmospheric Path Length (Non-Dispersive part) along the atmospheric path
corresponding to the 1st guess water column (from AtmProfile object)
for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("getNonDispersiveH2OPathLength", static_cast<Length (RefractiveIndexProfile::*)(const Length &)>(&RefractiveIndexProfile::getNonDispersiveH2OPathLength), py::arg("integratedwatercolumn"), R"doc(Function to retrieve the integrated Atmospheric Path Length (Non-Dispersive part) along the atmospheric path
corresponding to a given water vapor column
for single frequency RefractiveIndexProfile object)doc");
  cls_RefractiveIndexProfile.def("getNonDispersiveH2OPhaseDelay", static_cast<Angle (RefractiveIndexProfile::*)(const Length &, unsigned int)>(&RefractiveIndexProfile::getNonDispersiveH2OPhaseDelay), py::arg("integratedwatercolumn"), py::arg("nc"), R"doc(Function to retrieve the integrated Atmospheric Phase Delay (Non-Dispersive part) along the atmospheric path
corresponding to a given water vapor column
for channel nc in an RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("getNonDispersiveH2OPathLength", static_cast<Length (RefractiveIndexProfile::*)(const Length &, unsigned int)>(&RefractiveIndexProfile::getNonDispersiveH2OPathLength), py::arg("integratedwatercolumn"), py::arg("nc"), R"doc(Function to retrieve the integrated Atmospheric Path Length (Non-Dispersive part) along the atmospheric path
corresponding to a given water vapor column
for channel nc in an RefractiveIndexProfile object with a spectral grid)doc");
  cls_RefractiveIndexProfile.def("getNonDispersiveH2OPhaseDelay", static_cast<Angle (RefractiveIndexProfile::*)(const Length &, unsigned int, unsigned int)>(&RefractiveIndexProfile::getNonDispersiveH2OPhaseDelay), py::arg("integratedwatercolumn"), py::arg("spwid"), py::arg("nc"), R"doc(Function to retrieve the integrated Atmospheric Phase Delay (Non-Dispersive part) along the atmospheric path
corresponding to a given water vapor column
for channel nc in an RefractiveIndexProfile object with several spectral grids)doc");
  cls_RefractiveIndexProfile.def("getAverageNonDispersiveH2OPathLength", static_cast<Length (RefractiveIndexProfile::*)(const Length &, unsigned int)>(&RefractiveIndexProfile::getAverageNonDispersiveH2OPathLength), py::arg("integratedwatercolumn"), py::arg("spwid"), R"doc(Function to retrieve the average integrated Atmospheric Path Length (Non-Dispersive part) in spectral Window spwid)doc");
  cls_RefractiveIndexProfile.def("getAverageNonDispersiveH2OPhaseDelay", static_cast<Angle (RefractiveIndexProfile::*)(const Length &, unsigned int)>(&RefractiveIndexProfile::getAverageNonDispersiveH2OPhaseDelay), py::arg("integratedwatercolumn"), py::arg("spwid"), R"doc(Function to retrieve the average integrated Atmospheric Phase Delay (Non-Dispersive part) in spectral Window spwid)doc");
  cls_RefractiveIndexProfile.def("getNonDispersiveH2OPathLength", static_cast<Length (RefractiveIndexProfile::*)(const Length &, unsigned int, unsigned int)>(&RefractiveIndexProfile::getNonDispersiveH2OPathLength), py::arg("integratedwatercolumn"), py::arg("spwid"), py::arg("nc"), R"doc(Function to retrieve the integrated Atmospheric Path Length (Non-Dispersive part) along the atmospheric path
corresponding to a given water vapor column
for channel nc in an RefractiveIndexProfile object with several spectral grids)doc");
  cls_RefractiveIndexProfile.def("updateNewSpectralWindows", static_cast<void (RefractiveIndexProfile::*)()>(&RefractiveIndexProfile::updateNewSpectralWindows), "");
  cls_RefractiveIndexProfile.def("setBasicAtmosphericParameters", static_cast<bool (RefractiveIndexProfile::*)(const Length &, const Pressure &, const Temperature &, double, const Humidity &, const Length &)>(&RefractiveIndexProfile::setBasicAtmosphericParameters), py::arg("altitude"), py::arg("groundPressure"), py::arg("groundTemperature"), py::arg("tropoLapseRate"), py::arg("relativeHumidity"), py::arg("wvScaleHeight"), R"doc(Setter to update the AtmProfile and RefractiveIndexProfile if some basic atmospheric parameter has changed.
@pre   an RefractiveIndexProfile already exists
@param altitude          the new altitude, a Length
@param groundPressure    the Pressure at the ground level
@param groundTemperature the Temperature at the ground level
@param tropoLapseRate    the tropospheric lapse rate
@param relativeHumidity  the relative Humidity
@param wvScaleHeight     the scale height of the water vapor, a Length
@return true if the atmospheric profile has been updated, else false because the basic parameters have not changed
@post   the atmospheric profile, and accordingly the absorption phase profile, have been updated, unless none
        of all the input basic parameters correspond to new values.

\note  there is an overriding on this method in the sub-class in WaterVaporRadiance sub-class. Hence this method
       must not be overloaded in this RefractiveIndexProfile class.)doc");
  cls_RefractiveIndexProfile.def("addNewSpectralWindow", [](RefractiveIndexProfile &self, unsigned int numChan, double refFreq, std::vector<double> chanFreq, Frequency::Units freqUnits) { return self.addNewSpectralWindow(numChan, refFreq, chanFreq.data(), freqUnits); }, py::arg("numChan"), py::arg("refFreq"), py::arg("chanFreq"), py::arg("freqUnits"), R"doc(Setter of new spectral windows (adds frequencies to the SpectralGrid and calculates the corresponding absorption coefficients))doc");
  cls_RefractiveIndexProfile.def("addNewSpectralWindow", static_cast<void (RefractiveIndexProfile::*)(unsigned int, double, const std::vector<double> &, Frequency::Units)>(&RefractiveIndexProfile::addNewSpectralWindow), py::arg("numChan"), py::arg("refFreq"), py::arg("chanFreq"), py::arg("freqUnits"), R"doc(Setter of new spectral windows (adds frequencies to the SpectralGrid and calculates the corresponding absorption coefficients))doc");

  // ----- WaterVaporRadiometer
  cls_WaterVaporRadiometer.def(py::init<const WaterVaporRadiometer &>(), py::arg("other"), "Copy constructor");
  cls_WaterVaporRadiometer.def("__copy__", [](WaterVaporRadiometer const &self) { return WaterVaporRadiometer(self); });
  cls_WaterVaporRadiometer.def("__deepcopy__", [](WaterVaporRadiometer const &self, py::dict) { return WaterVaporRadiometer(self); }, py::arg("memo"));
  cls_WaterVaporRadiometer.def(py::init<>(), "");
  cls_WaterVaporRadiometer.def(py::init<const std::vector<unsigned int> &>(), py::arg("IdChannels"), R"doc(Class constructor with identifiers of radiometric channels. Sky Coupling = 1.0, Sideband Gain: 50% (no spilloverTemperature given))doc");
  cls_WaterVaporRadiometer.def(py::init<const std::vector<unsigned int> &, const std::vector<double> &>(), py::arg("IdChannels"), py::arg("skyCoupling"), R"doc(Class constructor with identifiers of radiometric channels. Sideband Gain: 50% (no spilloverTemperature given))doc");
  cls_WaterVaporRadiometer.def(py::init<const std::vector<unsigned int> &, const std::vector<Percent> &>(), py::arg("IdChannels"), py::arg("signalGain"), R"doc(Class constructor with identifiers of radiometric channels. Sky Coupling = 1.0 (no spilloverTemperature given))doc");
  cls_WaterVaporRadiometer.def(py::init<const std::vector<unsigned int> &, const std::vector<double> &, const std::vector<Percent> &>(), py::arg("IdChannels"), py::arg("skyCoupling"), py::arg("signalGain"), R"doc(Full class constructor (no spilloverTemperature given))doc");
  cls_WaterVaporRadiometer.def(py::init<const std::vector<unsigned int> &, const Temperature &>(), py::arg("IdChannels"), py::arg("spilloverTemperature"), R"doc(Class constructor with identifiers of radiometric channels. Sky Coupling = 1.0, Sideband Gain: 50% (spilloverTemperature given))doc");
  cls_WaterVaporRadiometer.def(py::init<const std::vector<unsigned int> &, const std::vector<double> &, const Temperature &>(), py::arg("IdChannels"), py::arg("skyCoupling"), py::arg("spilloverTemperature"), R"doc(Class constructor with identifiers of radiometric channels. Sideband Gain: 50% (spilloverTemperature given))doc");
  cls_WaterVaporRadiometer.def(py::init<const std::vector<unsigned int> &, const std::vector<Percent> &, const Temperature &>(), py::arg("IdChannels"), py::arg("signalGain"), py::arg("spilloverTemperature"), R"doc(Class constructor with identifiers of radiometric channels. Sky Coupling = 1.0 (spilloverTemperature given))doc");
  cls_WaterVaporRadiometer.def(py::init<const std::vector<unsigned int> &, const std::vector<double> &, const std::vector<Percent> &, const Temperature &>(), py::arg("IdChannels"), py::arg("skyCoupling"), py::arg("signalGain"), py::arg("spilloverTemperature"), R"doc(Full class constructor (spilloverTemperature given))doc");
  cls_WaterVaporRadiometer.def("getIdChannels", static_cast<std::vector<unsigned int> (WaterVaporRadiometer::*)() const>(&WaterVaporRadiometer::getIdChannels), R"doc(Accessor to identifiers of radiometric channels (vector of int))doc");
  cls_WaterVaporRadiometer.def("getSkyCoupling", static_cast<std::vector<double> (WaterVaporRadiometer::*)() const>(&WaterVaporRadiometer::getSkyCoupling), R"doc(Accessor to Sky coupling of the different radiometric channels (vector of double))doc");
  cls_WaterVaporRadiometer.def("getsignalGain", static_cast<std::vector<Percent> (WaterVaporRadiometer::*)() const>(&WaterVaporRadiometer::getsignalGain), R"doc(Accessor to signalGain of the different radiometric channels (vector of percent))doc");
  cls_WaterVaporRadiometer.def("getSpilloverTemperature", static_cast<Temperature (WaterVaporRadiometer::*)() const>(&WaterVaporRadiometer::getSpilloverTemperature), R"doc(Accessor to SpilloverTemperature)doc");
  cls_WaterVaporRadiometer.def("setSpilloverTemperature", static_cast<void (WaterVaporRadiometer::*)(Temperature)>(&WaterVaporRadiometer::setSpilloverTemperature), py::arg("spilloverTemperature"), R"doc(Setter of SpilloverTemperature)doc");
  cls_WaterVaporRadiometer.def(py::init<const std::vector<unsigned int> &, double>(), py::arg("IdChannels"), py::arg("skyCoupling"), "");
  cls_WaterVaporRadiometer.def("multiplySkyCoupling", static_cast<void (WaterVaporRadiometer::*)(double)>(&WaterVaporRadiometer::multiplySkyCoupling), py::arg("factor"), R"doc(Multiplier of the Sky coupling vector)doc");
  cls_WaterVaporRadiometer.def("multiplySkyCouplingChannel", static_cast<void (WaterVaporRadiometer::*)(unsigned int, double)>(&WaterVaporRadiometer::multiplySkyCouplingChannel), py::arg("ichan"), py::arg("factor"), R"doc(Multiplier of one  Sky coupling channel)doc");
  cls_WaterVaporRadiometer.def("setSkyCoupling", static_cast<void (WaterVaporRadiometer::*)(double)>(&WaterVaporRadiometer::setSkyCoupling), py::arg("factor"), R"doc(Setter of the Sky coupling vector to a single Sky Coupling value)doc");
  cls_WaterVaporRadiometer.def("setSkyCoupling", static_cast<void (WaterVaporRadiometer::*)(unsigned int, double)>(&WaterVaporRadiometer::setSkyCoupling), py::arg("i"), py::arg("factor"), "");

  // ----- WVRMeasurement
  cls_WVRMeasurement.def(py::init<const WVRMeasurement &>(), py::arg("other"), "Copy constructor");
  cls_WVRMeasurement.def("__copy__", [](WVRMeasurement const &self) { return WVRMeasurement(self); });
  cls_WVRMeasurement.def("__deepcopy__", [](WVRMeasurement const &self, py::dict) { return WVRMeasurement(self); }, py::arg("memo"));
  cls_WVRMeasurement.def(py::init<>(), R"doc(Class constructor with no radiometric channels)doc");
  cls_WVRMeasurement.def(py::init<const Angle &, const std::vector<Temperature> &>(), py::arg("elevation"), py::arg("measuredSkyBrightness"), R"doc(The basic class constructor, with the elevation angle corresponding to the measurement, and the measurements themselves
in the channels of the water vapor radiometer system)doc");
  cls_WVRMeasurement.def(py::init<const Angle &, const std::vector<Temperature> &, const std::vector<Temperature> &, const Length &, const Temperature &>(), py::arg("elevation"), py::arg("measuredSkyBrightness"), py::arg("fittedSkyBrightness"), py::arg("retrievedWaterVaporColumn"), py::arg("sigma_fittedSkyBrightness"), R"doc(A more general class constructor, with the elevation angle corresponding to the measurement, the measurements themselves
in the channels of the water vapor radiometer system, the fitted values in those channels and the sigma of the fit. This
constructor is not intended to be used by the user, but by water vapor retrieval procedures inside the SkyStatus class)doc");
  cls_WVRMeasurement.def("getElevation", static_cast<Angle (WVRMeasurement::*)() const>(&WVRMeasurement::getElevation), R"doc(Accessor to elevation)doc");
  cls_WVRMeasurement.def("getAirMass", static_cast<double (WVRMeasurement::*)() const>(&WVRMeasurement::getAirMass), R"doc(Accessor to air mass)doc");
  cls_WVRMeasurement.def("getmeasuredSkyBrightness", static_cast<std::vector<Temperature> (WVRMeasurement::*)() const>(&WVRMeasurement::getmeasuredSkyBrightness), R"doc(Accessor to measured sky brightness temperature)doc");
  cls_WVRMeasurement.def("getfittedSkyBrightness", static_cast<std::vector<Temperature> (WVRMeasurement::*)() const>(&WVRMeasurement::getfittedSkyBrightness), R"doc(Accessor to fitted sky brightness temperatures)doc");
  cls_WVRMeasurement.def("setfittedSkyBrightness", static_cast<void (WVRMeasurement::*)(const std::vector<Temperature> &)>(&WVRMeasurement::setfittedSkyBrightness), py::arg("a"), R"doc(Setter of fitted sky brightness temperatures)doc");
  cls_WVRMeasurement.def("getretrievedWaterVaporColumn", static_cast<Length (WVRMeasurement::*)() const>(&WVRMeasurement::getretrievedWaterVaporColumn), R"doc(Accessor to retrieved water vapor column)doc");
  cls_WVRMeasurement.def("setretrievedWaterVaporColumn", static_cast<void (WVRMeasurement::*)(const Length &)>(&WVRMeasurement::setretrievedWaterVaporColumn), py::arg("a"), R"doc(Setter of retrieved water vapor column)doc");
  cls_WVRMeasurement.def("getSigmaFit", static_cast<Temperature (WVRMeasurement::*)() const>(&WVRMeasurement::getSigmaFit), R"doc(Accessor to sigma of the fit (in K))doc");
  cls_WVRMeasurement.def("setSigmaFit", static_cast<void (WVRMeasurement::*)(const Temperature &)>(&WVRMeasurement::setSigmaFit), py::arg("a"), R"doc(Setter of sigma of the fit (in K))doc");

  // ----- SkyStatus
  cls_SkyStatus.def(py::init<const SkyStatus &>(), py::arg("other"), "Copy constructor");
  cls_SkyStatus.def("__copy__", [](SkyStatus const &self) { return SkyStatus(self); });
  cls_SkyStatus.def("__deepcopy__", [](SkyStatus const &self, py::dict) { return SkyStatus(self); }, py::arg("memo"));
  cls_SkyStatus.def(py::init<const RefractiveIndexProfile &>(), py::arg("refractiveIndexProfile"), R"doc(The basic constructor. It will allow to perform forward radiative transfer enquires in
 the spectral bands of refractiveIndexProfile, and to use some of these bands for water vapor retrievals.
 The basic constructor needs at least an  RefractiveIndexProfile object (it brings the spectral information via the
 SpectralGrid object inherited by it). Additional inputs can be the
 Air mass (default 1.0), sky background temperature (default 2.73 K), and user water vapor column (default 1 mm).
 Methods inside the class allow to retrieve the water vapor column and eventually update the user value to the retrieved one.
 In order to perform such retrievals, the numerical methods will need as inputs the measured T_EBBs towards the sky in
 some spectral bands that will be designed as water vapor radiometry channels. The sideband gains and coupling to the sky
 of these vapor radiometry channels should also be inputs of the retrieval methods, otherwise they will be set to default
 values. See documentation ef particular methods for more information.)doc");
  cls_SkyStatus.def(py::init<const RefractiveIndexProfile &, const Temperature &>(), py::arg("refractiveIndexProfile"), py::arg("temperatureBackground"), R"doc(Class constructor with additional inputs)doc");
  cls_SkyStatus.def(py::init<const RefractiveIndexProfile &, const Length &>(), py::arg("refractiveIndexProfile"), py::arg("wh2o"), R"doc(Class constructor with additional inputs)doc");
  cls_SkyStatus.def(py::init<const RefractiveIndexProfile &, const Length &, const Temperature &>(), py::arg("refractiveIndexProfile"), py::arg("wh2o"), py::arg("temperatureBackground"), R"doc(Class constructor with additional inputs)doc");
  cls_SkyStatus.def(py::init<const RefractiveIndexProfile &, const Temperature &, const Length &>(), py::arg("refractiveIndexProfile"), py::arg("temperatureBackground"), py::arg("wh2o"), R"doc(Class constructor with additional inputs)doc");
  cls_SkyStatus.def("getUserWH2O", static_cast<Length (SkyStatus::*)() const>(&SkyStatus::getUserWH2O), R"doc(Accessor to get the user water vapor column. This is the water vapor column used for forward
radiative transfer calculations. It can be equal to wh2o_retrieved_ when this one is avalilable
and the proper setter or update accessor (retrieveandupdateWaterVapor) has been used.)doc");
  cls_SkyStatus.def("setUserWH2O", static_cast<void (SkyStatus::*)(const Length &)>(&SkyStatus::setUserWH2O), py::arg("wh2o"), R"doc(Setter for user zenith water vapor column for forward radiative transfer calculations. The user
zenith water vapor column equals the retrieved zenith water vapor column from H2O radiometers,
every time the last one is derived with the retrieveandupdateWaterVapor accessor.)doc");
  cls_SkyStatus.def("getAirMass", static_cast<double (SkyStatus::*)() const>(&SkyStatus::getAirMass), R"doc(Accessor to get airmass)doc");
  cls_SkyStatus.def("getSkyBackgroundTemperature", static_cast<Temperature (SkyStatus::*)() const>(&SkyStatus::getSkyBackgroundTemperature), R"doc(Accessor to get sky background temperature)doc");
  cls_SkyStatus.def("setSkyBackgroundTemperature", static_cast<void (SkyStatus::*)(const Temperature &)>(&SkyStatus::setSkyBackgroundTemperature), py::arg("skyBackgroundTemperature"), R"doc(Setter for sky background temperature in SkyStatus without
performing water vapor retrieval)doc");
  cls_SkyStatus.def("getAverageTebbSky", static_cast<Temperature (SkyStatus::*)()>(&SkyStatus::getAverageTebbSky), R"doc(Accesor to the average Equivalent Blackbody Temperature in spectral window 0, for the current conditions
and a perfect sky coupling)doc");
  cls_SkyStatus.def("getAverageTebbSky", static_cast<Temperature (SkyStatus::*)(unsigned int)>(&SkyStatus::getAverageTebbSky), py::arg("spwid"), R"doc(Accesor to the average Equivalent Blackbody Temperature in spectral window spwid, for the current conditions
and a perfect sky coupling)doc");
  cls_SkyStatus.def("getAverageTebbSky", static_cast<Temperature (SkyStatus::*)(const Length &)>(&SkyStatus::getAverageTebbSky), py::arg("wh2o"), R"doc(Accesor to the average Equivalent Blackbody Temperature in spectral window 0, for the current
conditions, except water column wh2o, and a perfect sky coupling)doc");
  cls_SkyStatus.def("getAverageTebbSky", static_cast<Temperature (SkyStatus::*)(unsigned int, const Length &)>(&SkyStatus::getAverageTebbSky), py::arg("spwid"), py::arg("wh2o"), R"doc(Accesor to the average Equivalent Blackbody Temperature in spectral window spwid, for the current
conditions, except water column wh2o, and a perfect sky coupling)doc");
  cls_SkyStatus.def("getTebbSky", static_cast<Temperature (SkyStatus::*)()>(&SkyStatus::getTebbSky), R"doc(Accesor to the Equivalent Blackbody Temperature in spectral window 0 and channel 0, for the currnet
(user) Water Vapor Column, the current Air Mass, and perfect Sky Coupling to the sky)doc");
  cls_SkyStatus.def("getTebbSky", static_cast<Temperature (SkyStatus::*)(unsigned int)>(&SkyStatus::getTebbSky), py::arg("nc"), R"doc(Accesor to the Equivalent Blackbody Temperature in spectral window 0 and channel nc, for the currnet
(user) Water Vapor Column, the current Air Mass, and perfect Sky Coupling to the sky)doc");
  cls_SkyStatus.def("getTebbSky", static_cast<Temperature (SkyStatus::*)(unsigned int, unsigned int)>(&SkyStatus::getTebbSky), py::arg("spwid"), py::arg("nc"), R"doc(Accesor to the Equivalent Blackbody Temperature in spectral window spwid and channel nc, for the currnet
(user) Water Vapor Column, the current Air Mass, and perfect Sky Coupling to the sky)doc");
  cls_SkyStatus.def("getTebbSky", static_cast<Temperature (SkyStatus::*)(const Length &)>(&SkyStatus::getTebbSky), py::arg("wh2o"), R"doc(Accesor to the Equivalent Blackbody Temperature in spectral window 0 and channel 0, for Water
Vapor Column wh2o, the current Air Mass, and perfect Sky Coupling to the sky)doc");
  cls_SkyStatus.def("getTebbSky", static_cast<Temperature (SkyStatus::*)(unsigned int, const Length &)>(&SkyStatus::getTebbSky), py::arg("nc"), py::arg("wh2o"), R"doc(Accesor to the Equivalent Blackbody Temperature in spectral window 0 and channel nc, for Water
Vapor Column wh2o, the current Air Mass, and perfect Sky Coupling to the sky)doc");
  cls_SkyStatus.def("getTebbSky", static_cast<Temperature (SkyStatus::*)(unsigned int, unsigned int, const Length &)>(&SkyStatus::getTebbSky), py::arg("spwid"), py::arg("nc"), py::arg("wh2o"), R"doc(Accesor to the Equivalent Blackbody Temperature in spectral window spwid and channel nc, for Water
Vapor Column wh2o, the current Air Mass, and perfect Sky Coupling to the sky)doc");
  cls_SkyStatus.def("getAverageTrjSky", static_cast<Temperature (SkyStatus::*)()>(&SkyStatus::getAverageTrjSky), R"doc(Accesor to the average Rayleigh-Jeans Temperature in spectral window 0, for the current conditions
and a perfect sky coupling)doc");
  cls_SkyStatus.def("getAverageTrjSky", static_cast<Temperature (SkyStatus::*)(unsigned int)>(&SkyStatus::getAverageTrjSky), py::arg("spwid"), R"doc(Accesor to the average Rayleigh-Jeans Temperature in spectral window spwid, for the current conditions
and a perfect sky coupling)doc");
  cls_SkyStatus.def("getAverageTrjSky", static_cast<Temperature (SkyStatus::*)(const Length &)>(&SkyStatus::getAverageTrjSky), py::arg("wh2o"), R"doc(Accesor to the average Rayleigh-Jeans Temperature in spectral window 0, for the current
conditions, except water column wh2o, and a perfect sky coupling)doc");
  cls_SkyStatus.def("getAverageTrjSky", static_cast<Temperature (SkyStatus::*)(unsigned int, const Length &)>(&SkyStatus::getAverageTrjSky), py::arg("spwid"), py::arg("wh2o"), R"doc(Accesor to the average Rayleigh-Jeans Temperature in spectral window spwid, for the current
conditions, except water column wh2o, and a perfect sky coupling)doc");
  cls_SkyStatus.def("getTrjSky", static_cast<Temperature (SkyStatus::*)()>(&SkyStatus::getTrjSky), R"doc(Accesor to the Rayleigh-Jeans Temperature in spectral window 0 and channel 0, for the currnet
(user) Water Vapor Column, the current Air Mass, and perfect Sky Coupling to the sky)doc");
  cls_SkyStatus.def("getTrjSky", static_cast<Temperature (SkyStatus::*)(unsigned int)>(&SkyStatus::getTrjSky), py::arg("nc"), R"doc(Accesor to the Rayleigh-Jeans Temperature in spectral window 0 and channel nc, for the currnet
(user) Water Vapor Column, the current Air Mass, and perfect Sky Coupling to the sky)doc");
  cls_SkyStatus.def("getTrjSky", static_cast<Temperature (SkyStatus::*)(unsigned int, unsigned int)>(&SkyStatus::getTrjSky), py::arg("spwid"), py::arg("nc"), R"doc(Accesor to the Rayleigh-Jeans Temperature in spectral window spwid and channel nc, for the currnet
(user) Water Vapor Column, the current Air Mass, and perfect Sky Coupling to the sky)doc");
  cls_SkyStatus.def("getTrjSky", static_cast<Temperature (SkyStatus::*)(const Length &)>(&SkyStatus::getTrjSky), py::arg("wh2o"), R"doc(Accesor to the Rayleigh-Jeans Temperature in spectral window 0 and channel 0, for Water
Vapor Column wh2o, the current Air Mass, and perfect Sky Coupling to the sky)doc");
  cls_SkyStatus.def("getTrjSky", static_cast<Temperature (SkyStatus::*)(unsigned int, const Length &)>(&SkyStatus::getTrjSky), py::arg("nc"), py::arg("wh2o"), R"doc(Accesor to the Rayleigh-Jeans Temperature in spectral window 0 and channel nc, for Water
Vapor Column wh2o, the current Air Mass, and perfect Sky Coupling to the sky)doc");
  cls_SkyStatus.def("getTrjSky", static_cast<Temperature (SkyStatus::*)(unsigned int, unsigned int, const Length &)>(&SkyStatus::getTrjSky), py::arg("spwid"), py::arg("nc"), py::arg("wh2o"), R"doc(Accesor to the Rayleigh-Jeans Temperature in spectral window spwid and channel nc, for Water
Vapor Column wh2o, the current Air Mass, and perfect Sky Coupling to the sky)doc");
  cls_SkyStatus.def("getSkyTransmission", static_cast<double (SkyStatus::*)(unsigned int)>(&SkyStatus::getSkyTransmission), py::arg("nc"), "");
  cls_SkyStatus.def("getWetOpacity", static_cast<Opacity (SkyStatus::*)()>(&SkyStatus::getWetOpacity), R"doc(Accesor to get the integrated zenith Wet Opacity for the current conditions, for a single
frequency RefractiveIndexProfile object or for the point 0 of spectral window 0 of a
multi-window RefractiveIndexProfile object.
There is overloading. The same accessor exists in RefractiveIndexProfile but in that
case the returned value corresponds to the zenith water vapor column of the AtmProfile object.)doc");
  cls_SkyStatus.def("getWetOpacityUpTo", static_cast<Opacity (SkyStatus::*)(Length)>(&SkyStatus::getWetOpacityUpTo), py::arg("refalti"), "");
  cls_SkyStatus.def("getWetOpacity", static_cast<Opacity (SkyStatus::*)(unsigned int)>(&SkyStatus::getWetOpacity), py::arg("nc"), R"doc(Accesor to get the integrated zenith Wet Opacity for the current conditions,
for the point nc of spectral window 0.
There is overloading. The same accessor exists in RefractiveIndexProfile but in that
case the returned value corresponds to the zenith water vapor column of the AtmProfile object.)doc");
  cls_SkyStatus.def("getWetOpacityUpTo", static_cast<Opacity (SkyStatus::*)(unsigned int, Length)>(&SkyStatus::getWetOpacityUpTo), py::arg("nc"), py::arg("refalti"), "");
  cls_SkyStatus.def("getWetOpacity", static_cast<Opacity (SkyStatus::*)(unsigned int, unsigned int)>(&SkyStatus::getWetOpacity), py::arg("spwid"), py::arg("nc"), R"doc(Accesor to get the integrated zenith Wet Opacity for the current conditions,
for the point nc of spectral window spwid.
There is overloading. The same accessor exists in RefractiveIndexProfile but in that
case the returned value corresponds to the zenith water vapor column of the AtmProfile object.)doc");
  cls_SkyStatus.def("getWetOpacityUpTo", static_cast<Opacity (SkyStatus::*)(unsigned int, unsigned int, Length)>(&SkyStatus::getWetOpacityUpTo), py::arg("spwid"), py::arg("nc"), py::arg("refalti"), "");
  cls_SkyStatus.def("getAverageWetOpacity", static_cast<Opacity (SkyStatus::*)(unsigned int)>(&SkyStatus::getAverageWetOpacity), py::arg("spwid"), R"doc(Accesor to get the average Wet Opacity for the current conditions,
in spectral window spwid.
There is overloading. The same accessor exists in RefractiveIndexProfile but in that
case the returned value corresponds to the zenith water vapor column of the AtmProfile object.)doc");
  cls_SkyStatus.def("getAverageH2OLinesOpacity", static_cast<Opacity (SkyStatus::*)(unsigned int)>(&SkyStatus::getAverageH2OLinesOpacity), py::arg("spwid"), "");
  cls_SkyStatus.def("getAverageH2OContOpacity", static_cast<Opacity (SkyStatus::*)(unsigned int)>(&SkyStatus::getAverageH2OContOpacity), py::arg("spwid"), "");
  cls_SkyStatus.def("getDryOpacity", static_cast<Opacity (SkyStatus::*)()>(&SkyStatus::getDryOpacity), "");
  cls_SkyStatus.def("getDryOpacity", static_cast<Opacity (SkyStatus::*)(unsigned int)>(&SkyStatus::getDryOpacity), py::arg("nc"), "");
  cls_SkyStatus.def("getDryOpacity", static_cast<Opacity (SkyStatus::*)(unsigned int, unsigned int)>(&SkyStatus::getDryOpacity), py::arg("spwid"), py::arg("nc"), "");
  cls_SkyStatus.def("getAverageDryOpacity", static_cast<Opacity (SkyStatus::*)(unsigned int)>(&SkyStatus::getAverageDryOpacity), py::arg("spwid"), "");
  cls_SkyStatus.def("getAverageO2LinesOpacity", static_cast<Opacity (SkyStatus::*)(unsigned int)>(&SkyStatus::getAverageO2LinesOpacity), py::arg("spwid"), "");
  cls_SkyStatus.def("getAverageO3LinesOpacity", static_cast<Opacity (SkyStatus::*)(unsigned int)>(&SkyStatus::getAverageO3LinesOpacity), py::arg("spwid"), "");
  cls_SkyStatus.def("getAverageN2OLinesOpacity", static_cast<Opacity (SkyStatus::*)(unsigned int)>(&SkyStatus::getAverageN2OLinesOpacity), py::arg("spwid"), "");
  cls_SkyStatus.def("getAverageNO2LinesOpacity", static_cast<Opacity (SkyStatus::*)(unsigned int)>(&SkyStatus::getAverageNO2LinesOpacity), py::arg("spwid"), "");
  cls_SkyStatus.def("getAverageHClLinesOpacity", static_cast<Opacity (SkyStatus::*)(unsigned int)>(&SkyStatus::getAverageHClLinesOpacity), py::arg("spwid"), "");
  cls_SkyStatus.def("getAverageHCNLinesOpacity", static_cast<Opacity (SkyStatus::*)(unsigned int)>(&SkyStatus::getAverageHCNLinesOpacity), py::arg("spwid"), "");
  cls_SkyStatus.def("getAverageSO2LinesOpacity", static_cast<Opacity (SkyStatus::*)(unsigned int)>(&SkyStatus::getAverageSO2LinesOpacity), py::arg("spwid"), "");
  cls_SkyStatus.def("getAverageCOLinesOpacity", static_cast<Opacity (SkyStatus::*)(unsigned int)>(&SkyStatus::getAverageCOLinesOpacity), py::arg("spwid"), "");
  cls_SkyStatus.def("getAverageDryContOpacity", static_cast<Opacity (SkyStatus::*)(unsigned int)>(&SkyStatus::getAverageDryContOpacity), py::arg("spwid"), "");
  cls_SkyStatus.def("getTotalOpacity", static_cast<Opacity (SkyStatus::*)()>(&SkyStatus::getTotalOpacity), "");
  cls_SkyStatus.def("getTotalOpacity", static_cast<Opacity (SkyStatus::*)(unsigned int)>(&SkyStatus::getTotalOpacity), py::arg("nc"), "");
  cls_SkyStatus.def("getTotalOpacity", static_cast<Opacity (SkyStatus::*)(unsigned int, unsigned int)>(&SkyStatus::getTotalOpacity), py::arg("spwid"), py::arg("nc"), "");
  cls_SkyStatus.def("getAverageTotalOpacity", static_cast<Opacity (SkyStatus::*)(unsigned int)>(&SkyStatus::getAverageTotalOpacity), py::arg("spwid"), "");
  cls_SkyStatus.def("getTotalOpacityUpTo", static_cast<Opacity (SkyStatus::*)(Length)>(&SkyStatus::getTotalOpacityUpTo), py::arg("refalti"), "");
  cls_SkyStatus.def("getTotalOpacityUpTo", static_cast<Opacity (SkyStatus::*)(unsigned int, Length)>(&SkyStatus::getTotalOpacityUpTo), py::arg("nc"), py::arg("refalti"), "");
  cls_SkyStatus.def("getTotalOpacityUpTo", static_cast<Opacity (SkyStatus::*)(unsigned int, unsigned int, Length)>(&SkyStatus::getTotalOpacityUpTo), py::arg("spwid"), py::arg("nc"), py::arg("refalti"), "");
  cls_SkyStatus.def("getH2OLinesOpacity", static_cast<Opacity (SkyStatus::*)()>(&SkyStatus::getH2OLinesOpacity), R"doc(Accesor to get the integrated zenith H2O Lines Opacity for the current conditions,
for a single frequency RefractiveIndexProfile object or for the point 0 of spectral
window 0 of a multi-window RefractiveIndexProfile object.
There is overloading. The same accessor exists in RefractiveIndexProfile but in that
case the returned value corresponds to the zenith water vapor column of the AtmProfile object.)doc");
  cls_SkyStatus.def("getH2OLinesOpacityUpTo", static_cast<Opacity (SkyStatus::*)(Length)>(&SkyStatus::getH2OLinesOpacityUpTo), py::arg("refalti"), "");
  cls_SkyStatus.def("getH2OLinesOpacity", static_cast<Opacity (SkyStatus::*)(unsigned int)>(&SkyStatus::getH2OLinesOpacity), py::arg("nc"), R"doc(Accesor to get the integrated zenith H2O Lines Opacity for the current conditions,
for the point nc of spectral window 0.
There is overloading. The same accessor exists in RefractiveIndexProfile but in that
case the returned value corresponds to the zenith water vapor column of the AtmProfile object.)doc");
  cls_SkyStatus.def("getH2OLinesOpacityUpTo", static_cast<Opacity (SkyStatus::*)(unsigned int, Length)>(&SkyStatus::getH2OLinesOpacityUpTo), py::arg("nc"), py::arg("refalti"), "");
  cls_SkyStatus.def("getH2OLinesOpacity", static_cast<Opacity (SkyStatus::*)(unsigned int, unsigned int)>(&SkyStatus::getH2OLinesOpacity), py::arg("spwid"), py::arg("nc"), R"doc(Accesor to get the integrated zenith H2O Lines Opacity for the current conditions,
for the point nc of spectral window spwid.
There is overloading. The same accessor exists in RefractiveIndexProfile but in that
case the returned value corresponds to the zenith water vapor column of the AtmProfile object.)doc");
  cls_SkyStatus.def("getH2OLinesOpacityUpTo", static_cast<Opacity (SkyStatus::*)(unsigned int, unsigned int, Length)>(&SkyStatus::getH2OLinesOpacityUpTo), py::arg("spwid"), py::arg("nc"), py::arg("refalti"), "");
  cls_SkyStatus.def("getHH16OLinesOpacity", static_cast<Opacity (SkyStatus::*)()>(&SkyStatus::getHH16OLinesOpacity), R"doc(Accesor to get the integrated zenith HH16O Lines Opacity for the current conditions,
for a single frequency RefractiveIndexProfile object or for the point 0 of spectral
window 0 of a multi-window RefractiveIndexProfile object.
There is overloading. The same accessor exists in RefractiveIndexProfile but in that
case the returned value corresponds to the zenith water vapor column of the AtmProfile object.)doc");
  cls_SkyStatus.def("getHH16OLinesOpacityUpTo", static_cast<Opacity (SkyStatus::*)(Length)>(&SkyStatus::getHH16OLinesOpacityUpTo), py::arg("refalti"), "");
  cls_SkyStatus.def("getHH16OLinesOpacity", static_cast<Opacity (SkyStatus::*)(unsigned int)>(&SkyStatus::getHH16OLinesOpacity), py::arg("nc"), R"doc(Accesor to get the integrated zenith HH16O Lines Opacity for the current conditions,
for the point nc of spectral window 0.
There is overloading. The same accessor exists in RefractiveIndexProfile but in that
case the returned value corresponds to the zenith water vapor column of the AtmProfile object.)doc");
  cls_SkyStatus.def("getHH16OLinesOpacityUpTo", static_cast<Opacity (SkyStatus::*)(unsigned int, Length)>(&SkyStatus::getHH16OLinesOpacityUpTo), py::arg("nc"), py::arg("refalti"), "");
  cls_SkyStatus.def("getHH16OLinesOpacity", static_cast<Opacity (SkyStatus::*)(unsigned int, unsigned int)>(&SkyStatus::getHH16OLinesOpacity), py::arg("spwid"), py::arg("nc"), R"doc(Accesor to get the integrated zenith HH16O Lines Opacity for the current conditions,
for the point nc of spectral window spwid.
There is overloading. The same accessor exists in RefractiveIndexProfile but in that
case the returned value corresponds to the zenith water vapor column of the AtmProfile object.)doc");
  cls_SkyStatus.def("getHH16OLinesOpacityUpTo", static_cast<Opacity (SkyStatus::*)(unsigned int, unsigned int, Length)>(&SkyStatus::getHH16OLinesOpacityUpTo), py::arg("spwid"), py::arg("nc"), py::arg("refalti"), "");
  cls_SkyStatus.def("getHH16OV2LinesOpacity", static_cast<Opacity (SkyStatus::*)()>(&SkyStatus::getHH16OV2LinesOpacity), R"doc(Accesor to get the integrated zenith HH16OV2 Lines Opacity for the current conditions,
for a single frequency RefractiveIndexProfile object or for the point 0 of spectral
window 0 of a multi-window RefractiveIndexProfile object.
There is overloading. The same accessor exists in RefractiveIndexProfile but in that
case the returned value corresponds to the zenith water vapor column of the AtmProfile object.)doc");
  cls_SkyStatus.def("getHH16OV2LinesOpacityUpTo", static_cast<Opacity (SkyStatus::*)(Length)>(&SkyStatus::getHH16OV2LinesOpacityUpTo), py::arg("refalti"), "");
  cls_SkyStatus.def("getHH16OV2LinesOpacity", static_cast<Opacity (SkyStatus::*)(unsigned int)>(&SkyStatus::getHH16OV2LinesOpacity), py::arg("nc"), R"doc(Accesor to get the integrated zenith HH16OV2 Lines Opacity for the current conditions,
for the point nc of spectral window 0.
There is overloading. The same accessor exists in RefractiveIndexProfile but in that
case the returned value corresponds to the zenith water vapor column of the AtmProfile object.)doc");
  cls_SkyStatus.def("getHH16OV2LinesOpacityUpTo", static_cast<Opacity (SkyStatus::*)(unsigned int, Length)>(&SkyStatus::getHH16OV2LinesOpacityUpTo), py::arg("nc"), py::arg("refalti"), "");
  cls_SkyStatus.def("getHH16OV2LinesOpacity", static_cast<Opacity (SkyStatus::*)(unsigned int, unsigned int)>(&SkyStatus::getHH16OV2LinesOpacity), py::arg("spwid"), py::arg("nc"), R"doc(Accesor to get the integrated zenith HH16OV2 Lines Opacity for the current conditions,
for the point nc of spectral window spwid.
There is overloading. The same accessor exists in RefractiveIndexProfile but in that
case the returned value corresponds to the zenith water vapor column of the AtmProfile object.)doc");
  cls_SkyStatus.def("getHH16OV2LinesOpacityUpTo", static_cast<Opacity (SkyStatus::*)(unsigned int, unsigned int, Length)>(&SkyStatus::getHH16OV2LinesOpacityUpTo), py::arg("spwid"), py::arg("nc"), py::arg("refalti"), "");
  cls_SkyStatus.def("getHH18OLinesOpacity", static_cast<Opacity (SkyStatus::*)()>(&SkyStatus::getHH18OLinesOpacity), R"doc(Accesor to get the integrated zenith HH18O Lines Opacity for the current conditions,
for a single frequency RefractiveIndexProfile object or for the point 0 of spectral
window 0 of a multi-window RefractiveIndexProfile object.
There is overloading. The same accessor exists in RefractiveIndexProfile but in that
case the returned value corresponds to the zenith water vapor column of the AtmProfile object.)doc");
  cls_SkyStatus.def("getHH18OLinesOpacityUpTo", static_cast<Opacity (SkyStatus::*)(Length)>(&SkyStatus::getHH18OLinesOpacityUpTo), py::arg("refalti"), "");
  cls_SkyStatus.def("getHH18OLinesOpacity", static_cast<Opacity (SkyStatus::*)(unsigned int)>(&SkyStatus::getHH18OLinesOpacity), py::arg("nc"), R"doc(Accesor to get the integrated zenith HH18O Lines Opacity for the current conditions,
for the point nc of spectral window 0.
There is overloading. The same accessor exists in RefractiveIndexProfile but in that
case the returned value corresponds to the zenith water vapor column of the AtmProfile object.)doc");
  cls_SkyStatus.def("getHH18OLinesOpacityUpTo", static_cast<Opacity (SkyStatus::*)(unsigned int, Length)>(&SkyStatus::getHH18OLinesOpacityUpTo), py::arg("nc"), py::arg("refalti"), "");
  cls_SkyStatus.def("getHH18OLinesOpacity", static_cast<Opacity (SkyStatus::*)(unsigned int, unsigned int)>(&SkyStatus::getHH18OLinesOpacity), py::arg("spwid"), py::arg("nc"), R"doc(Accesor to get the integrated zenith HH18O Lines Opacity for the current conditions,
for the point nc of spectral window spwid.
There is overloading. The same accessor exists in RefractiveIndexProfile but in that
case the returned value corresponds to the zenith water vapor column of the AtmProfile object.)doc");
  cls_SkyStatus.def("getHH18OLinesOpacityUpTo", static_cast<Opacity (SkyStatus::*)(unsigned int, unsigned int, Length)>(&SkyStatus::getHH18OLinesOpacityUpTo), py::arg("spwid"), py::arg("nc"), py::arg("refalti"), "");
  cls_SkyStatus.def("getHH17OLinesOpacity", static_cast<Opacity (SkyStatus::*)()>(&SkyStatus::getHH17OLinesOpacity), R"doc(Accesor to get the integrated zenith HH17O Lines Opacity for the current conditions,
for a single frequency RefractiveIndexProfile object or for the point 0 of spectral
window 0 of a multi-window RefractiveIndexProfile object.
There is overloading. The same accessor exists in RefractiveIndexProfile but in that
case the returned value corresponds to the zenith water vapor column of the AtmProfile object.)doc");
  cls_SkyStatus.def("getHH17OLinesOpacityUpTo", static_cast<Opacity (SkyStatus::*)(Length)>(&SkyStatus::getHH17OLinesOpacityUpTo), py::arg("refalti"), "");
  cls_SkyStatus.def("getHH17OLinesOpacity", static_cast<Opacity (SkyStatus::*)(unsigned int)>(&SkyStatus::getHH17OLinesOpacity), py::arg("nc"), R"doc(Accesor to get the integrated zenith HH17O Lines Opacity for the current conditions,
for the point nc of spectral window 0.
There is overloading. The same accessor exists in RefractiveIndexProfile but in that
case the returned value corresponds to the zenith water vapor column of the AtmProfile object.)doc");
  cls_SkyStatus.def("getHH17OLinesOpacityUpTo", static_cast<Opacity (SkyStatus::*)(unsigned int, Length)>(&SkyStatus::getHH17OLinesOpacityUpTo), py::arg("nc"), py::arg("refalti"), "");
  cls_SkyStatus.def("getHH17OLinesOpacity", static_cast<Opacity (SkyStatus::*)(unsigned int, unsigned int)>(&SkyStatus::getHH17OLinesOpacity), py::arg("spwid"), py::arg("nc"), R"doc(Accesor to get the integrated zenith HH17O Lines Opacity for the current conditions,
for the point nc of spectral window spwid.
There is overloading. The same accessor exists in RefractiveIndexProfile but in that
case the returned value corresponds to the zenith water vapor column of the AtmProfile object.)doc");
  cls_SkyStatus.def("getHH17OLinesOpacityUpTo", static_cast<Opacity (SkyStatus::*)(unsigned int, unsigned int, Length)>(&SkyStatus::getHH17OLinesOpacityUpTo), py::arg("spwid"), py::arg("nc"), py::arg("refalti"), "");
  cls_SkyStatus.def("getHDOLinesOpacity", static_cast<Opacity (SkyStatus::*)()>(&SkyStatus::getHDOLinesOpacity), R"doc(Accesor to get the integrated zenith HDO Lines Opacity for the current conditions,
for a single frequency RefractiveIndexProfile object or for the point 0 of spectral
window 0 of a multi-window RefractiveIndexProfile object.
There is overloading. The same accessor exists in RefractiveIndexProfile but in that
case the returned value corresponds to the zenith water vapor column of the AtmProfile object.)doc");
  cls_SkyStatus.def("getHDOLinesOpacityUpTo", static_cast<Opacity (SkyStatus::*)(Length)>(&SkyStatus::getHDOLinesOpacityUpTo), py::arg("refalti"), "");
  cls_SkyStatus.def("getHDOLinesOpacity", static_cast<Opacity (SkyStatus::*)(unsigned int)>(&SkyStatus::getHDOLinesOpacity), py::arg("nc"), R"doc(Accesor to get the integrated zenith HDO Lines Opacity for the current conditions,
for the point nc of spectral window 0.
There is overloading. The same accessor exists in RefractiveIndexProfile but in that
case the returned value corresponds to the zenith water vapor column of the AtmProfile object.)doc");
  cls_SkyStatus.def("getHDOLinesOpacityUpTo", static_cast<Opacity (SkyStatus::*)(unsigned int, Length)>(&SkyStatus::getHDOLinesOpacityUpTo), py::arg("nc"), py::arg("refalti"), "");
  cls_SkyStatus.def("getHDOLinesOpacity", static_cast<Opacity (SkyStatus::*)(unsigned int, unsigned int)>(&SkyStatus::getHDOLinesOpacity), py::arg("spwid"), py::arg("nc"), R"doc(Accesor to get the integrated zenith HDO Lines Opacity for the current conditions,
for the point nc of spectral window spwid.
There is overloading. The same accessor exists in RefractiveIndexProfile but in that
case the returned value corresponds to the zenith water vapor column of the AtmProfile object.)doc");
  cls_SkyStatus.def("getHDOLinesOpacityUpTo", static_cast<Opacity (SkyStatus::*)(unsigned int, unsigned int, Length)>(&SkyStatus::getHDOLinesOpacityUpTo), py::arg("spwid"), py::arg("nc"), py::arg("refalti"), "");
  cls_SkyStatus.def("getH2OContOpacity", static_cast<Opacity (SkyStatus::*)()>(&SkyStatus::getH2OContOpacity), R"doc(Accesor to get the integrated zenith H2O Continuum Opacity for the current conditions,
for a single frequency RefractiveIndexProfile object or for the point 0 of spectral
window 0 of a multi-window RefractiveIndexProfile object.
There is overloading. The same accessor exists in RefractiveIndexProfile but in that
case the returned value corresponds to the zenith water vapor column of the AtmProfile object.)doc");
  cls_SkyStatus.def("getH2OContOpacityUpTo", static_cast<Opacity (SkyStatus::*)(Length)>(&SkyStatus::getH2OContOpacityUpTo), py::arg("refalti"), "");
  cls_SkyStatus.def("getH2OContOpacity", static_cast<Opacity (SkyStatus::*)(unsigned int)>(&SkyStatus::getH2OContOpacity), py::arg("nc"), R"doc(Accesor to get the integrated zenith H2O Continuum Opacity for the current conditions,
for the point nc of spectral window 0.
There is overloading. The same accessor exists in RefractiveIndexProfile but in that
case the returned value corresponds to the zenith water vapor column of the AtmProfile object.)doc");
  cls_SkyStatus.def("getH2OContOpacityUpTo", static_cast<Opacity (SkyStatus::*)(unsigned int, Length)>(&SkyStatus::getH2OContOpacityUpTo), py::arg("nc"), py::arg("refalti"), "");
  cls_SkyStatus.def("getH2OContOpacity", static_cast<Opacity (SkyStatus::*)(unsigned int, unsigned int)>(&SkyStatus::getH2OContOpacity), py::arg("spwid"), py::arg("nc"), R"doc(Accesor to get the integrated zenith H2O Continuum Opacity for the current conditions,
for the point nc of spectral window spwid.
There is overloading. The same accessor exists in RefractiveIndexProfile but in that
case the returned value corresponds to the zenith water vapor column of the AtmProfile object.)doc");
  cls_SkyStatus.def("getH2OContOpacityUpTo", static_cast<Opacity (SkyStatus::*)(unsigned int, unsigned int, Length)>(&SkyStatus::getH2OContOpacityUpTo), py::arg("spwid"), py::arg("nc"), py::arg("refalti"), "");
  cls_SkyStatus.def("getDispersiveH2OPhaseDelay", static_cast<Angle (SkyStatus::*)()>(&SkyStatus::getDispersiveH2OPhaseDelay), R"doc(Accesor to get the integrated zenith H2O Atmospheric Phase Delay (Dispersive part)
for the current conditions, for a single frequency RefractiveIndexProfile object or
for the point 0 of spectral window 0 of a multi-window RefractiveIndexProfile object.
There is overloading. The same accessor exists in RefractiveIndexProfile but in that
case the returned value corresponds to the zenith water vapor column of the AtmProfile object.)doc");
  cls_SkyStatus.def("getDispersiveH2OPhaseDelay", static_cast<Angle (SkyStatus::*)(unsigned int)>(&SkyStatus::getDispersiveH2OPhaseDelay), py::arg("nc"), R"doc(Accesor to get the integrated zenith H2O Atmospheric Phase Delay (Dispersive part)
for the current conditions, for a single frequency RefractiveIndexProfile object or
for the point nc of spectral window 0.
There is overloading. The same accessor exists in RefractiveIndexProfile but in that
case the returned value corresponds to the zenith water vapor column of the AtmProfile object.)doc");
  cls_SkyStatus.def("getDispersiveH2OPhaseDelay", static_cast<Angle (SkyStatus::*)(unsigned int, unsigned int)>(&SkyStatus::getDispersiveH2OPhaseDelay), py::arg("spwid"), py::arg("nc"), R"doc(Accesor to get the integrated zenith H2O Atmospheric Phase Delay (Dispersive part)
for the current conditions, for a single frequency RefractiveIndexProfile object or
for the point nc of spectral window spwid.
There is overloading. The same accessor exists in RefractiveIndexProfile but in that
case the returned value corresponds to the zenith water vapor column of the AtmProfile object.)doc");
  cls_SkyStatus.def("getDispersiveH2OPathLength", static_cast<Length (SkyStatus::*)()>(&SkyStatus::getDispersiveH2OPathLength), R"doc(Accesor to get the integrated zenith H2O Atmospheric Path length (Dispersive part)
for the current conditions, for a single frequency RefractiveIndexProfile object or
for the point 0 of spectral window 0 of a multi-window RefractiveIndexProfile object.
There is overloading. The same accessor exists in RefractiveIndexProfile but in that
case the returned value corresponds to the zenith water vapor column of the AtmProfile object.)doc");
  cls_SkyStatus.def("getDispersiveH2OPathLength", static_cast<Length (SkyStatus::*)(unsigned int)>(&SkyStatus::getDispersiveH2OPathLength), py::arg("nc"), R"doc(Accesor to get the integrated zenith H2O Atmospheric Path length (Dispersive part)
for the current conditions, for a single frequency RefractiveIndexProfile object or
for the point nc of spectral window 0.
There is overloading. The same accessor exists in RefractiveIndexProfile but in that
case the returned value corresponds to the zenith water vapor column of the AtmProfile object.)doc");
  cls_SkyStatus.def("getDispersiveH2OPathLength", static_cast<Length (SkyStatus::*)(unsigned int, unsigned int)>(&SkyStatus::getDispersiveH2OPathLength), py::arg("spwid"), py::arg("nc"), R"doc(Accesor to get the integrated zenith H2O Atmospheric Path length (Dispersive part)
for the current conditions, for a single frequency RefractiveIndexProfile object or
for the point nc of spectral window spwid.
There is overloading. The same accessor exists in RefractiveIndexProfile but in that
case the returned value corresponds to the zenith water vapor column of the AtmProfile object.)doc");
  cls_SkyStatus.def("getNonDispersiveH2OPhaseDelay", static_cast<Angle (SkyStatus::*)()>(&SkyStatus::getNonDispersiveH2OPhaseDelay), R"doc(Accesor to get the integrated zenith H2O Atmospheric Phase Delay (Non-Dispersive part)
for the current conditions, for a single frequency RefractiveIndexProfile object or
for the point 0 of spectral window 0 of a multi-window RefractiveIndexProfile object.
There is overloading. The same accessor exists in RefractiveIndexProfile but in that
case the returned value corresponds to the zenith water vapor column of the AtmProfile object.)doc");
  cls_SkyStatus.def("getNonDispersiveH2OPhaseDelay", static_cast<Angle (SkyStatus::*)(unsigned int)>(&SkyStatus::getNonDispersiveH2OPhaseDelay), py::arg("nc"), R"doc(Accesor to get the integrated zenith H2O Atmospheric Phase Delay (Non-Dispersive part)
for the current conditions, for a single frequency RefractiveIndexProfile object or
for the point nc of spectral window 0.
There is overloading. The same accessor exists in RefractiveIndexProfile but in that
case the returned value corresponds to the zenith water vapor column of the AtmProfile object.)doc");
  cls_SkyStatus.def("getNonDispersiveH2OPhaseDelay", static_cast<Angle (SkyStatus::*)(unsigned int, unsigned int)>(&SkyStatus::getNonDispersiveH2OPhaseDelay), py::arg("spwid"), py::arg("nc"), R"doc(Accesor to get the integrated zenith H2O Atmospheric Phase Delay (Non-Dispersive part)
for the current conditions, for a single frequency RefractiveIndexProfile object or
for the point nc of spectral window spwid.
There is overloading. The same accessor exists in RefractiveIndexProfile but in that
case the returned value corresponds to the zenith water vapor column of the AtmProfile object.)doc");
  cls_SkyStatus.def("getNonDispersiveH2OPathLength", static_cast<Length (SkyStatus::*)()>(&SkyStatus::getNonDispersiveH2OPathLength), R"doc(Accesor to get the integrated zenith H2O Atmospheric Path length (Non-Dispersive part)
for the current conditions, for a single frequency RefractiveIndexProfile object or
for the point 0 of spectral window 0 of a multi-window RefractiveIndexProfile object.
There is overloading. The same accessor exists in RefractiveIndexProfile but in that
case the returned value corresponds to the zenith water vapor column of the AtmProfile object.)doc");
  cls_SkyStatus.def("getNonDispersiveH2OPathLength", static_cast<Length (SkyStatus::*)(unsigned int)>(&SkyStatus::getNonDispersiveH2OPathLength), py::arg("nc"), R"doc(Accesor to get the integrated zenith H2O Atmospheric Path length (Non-Dispersive part)
for the current conditions, for a single frequency RefractiveIndexProfile object or
for the point nc of spectral window 0.
There is overloading. The same accessor exists in RefractiveIndexProfile but in that
case the returned value corresponds to the zenith water vapor column of the AtmProfile object.)doc");
  cls_SkyStatus.def("getNonDispersiveH2OPathLength", static_cast<Length (SkyStatus::*)(unsigned int, unsigned int)>(&SkyStatus::getNonDispersiveH2OPathLength), py::arg("spwid"), py::arg("nc"), R"doc(Accesor to get the integrated zenith H2O Atmospheric Path length (Non-Dispersive part)
for the current conditions, for a single frequency RefractiveIndexProfile object or
for the point nc of spectral window spwid.
There is overloading. The same accessor exists in RefractiveIndexProfile but in that
case the returned value corresponds to the zenith water vapor column of the AtmProfile object.)doc");
  cls_SkyStatus.def("getAverageDispersiveH2OPhaseDelay", static_cast<Angle (SkyStatus::*)(unsigned int)>(&SkyStatus::getAverageDispersiveH2OPhaseDelay), py::arg("spwid"), R"doc(Accessor to get the average integrated zenith Atmospheric Phase Delay (Dispersive part)
for the current conditions in spectral Window spwid.
There is overloading. The same accessor exists in RefractiveIndexProfile but in that
case the returned value corresponds to the zenith water vapor column of the AtmProfile object.)doc");
  cls_SkyStatus.def("getAverageDispersiveH2OPhaseDelay", static_cast<Angle (SkyStatus::*)()>(&SkyStatus::getAverageDispersiveH2OPhaseDelay), R"doc(Accessor to get the average integrated zenith Atmospheric Phase Delay (Dispersive part)
for the current conditions in spectral Window 0.
There is overloading. The same accessor exists in RefractiveIndexProfile but in that
case the returned value corresponds to the zenith water vapor column of the AtmProfile object.)doc");
  cls_SkyStatus.def("getAverageNonDispersiveH2OPhaseDelay", static_cast<Angle (SkyStatus::*)(unsigned int)>(&SkyStatus::getAverageNonDispersiveH2OPhaseDelay), py::arg("spwid"), R"doc(Accessor to get the average integrated zenith Atmospheric Phase Delay (Non-Dispersive
part) in spectral Window spwid.
There is overloading. The same accessor exists in RefractiveIndexProfile but in that
case the returned value corresponds to the zenith water vapor column of the AtmProfile object.)doc");
  cls_SkyStatus.def("getAverageNonDispersiveH2OPhaseDelay", static_cast<Angle (SkyStatus::*)()>(&SkyStatus::getAverageNonDispersiveH2OPhaseDelay), R"doc(Accessor to get the average integrated zenith Atmospheric Phase Delay (Non-Dispersive
part) in spectral Window 0.
There is overloading. The same accessor exists in RefractiveIndexProfile but in that
case the returned value corresponds to the zenith water vapor column of the AtmProfile object.)doc");
  cls_SkyStatus.def("getAverageDispersiveH2OPathLength", static_cast<Length (SkyStatus::*)(unsigned int)>(&SkyStatus::getAverageDispersiveH2OPathLength), py::arg("spwid"), R"doc(Accessor to get the average integrated zenith Atmospheric Path Length (Dispersive part)
in spectral Window spwid.
There is overloading. The same accessor exists in RefractiveIndexProfile but in that
case the returned value corresponds to the zenith water vapor column of the AtmProfile object.)doc");
  cls_SkyStatus.def("getAverageDispersiveH2OPathLength", static_cast<Length (SkyStatus::*)()>(&SkyStatus::getAverageDispersiveH2OPathLength), R"doc(Accessor to get the average integrated zenith Atmospheric Path Length (Dispersive part)
in spectral Window 0.
There is overloading. The same accessor exists in RefractiveIndexProfile but in that
case the returned value corresponds to the zenith water vapor column of the AtmProfile object.)doc");
  cls_SkyStatus.def("getAverageNonDispersiveH2OPathLength", static_cast<Length (SkyStatus::*)(unsigned int)>(&SkyStatus::getAverageNonDispersiveH2OPathLength), py::arg("spwid"), R"doc(Accessor to get the average integrated zenith Atmospheric Path Length (Non-Dispersive
part) in spectral Window spwid.
There is overloading. The same accessor exists in RefractiveIndexProfile but in that
case the returned value corresponds to the zenith water vapor column of the AtmProfile object.)doc");
  cls_SkyStatus.def("getAverageNonDispersiveH2OPathLength", static_cast<Length (SkyStatus::*)()>(&SkyStatus::getAverageNonDispersiveH2OPathLength), R"doc(Accessor to get the average integrated zenith Atmospheric Path Length (Non-Dispersive
part) in spectral Window 0.
There is overloading. The same accessor exists in RefractiveIndexProfile but in that
case the returned value corresponds to the zenith water vapor column of the AtmProfile object.)doc");
  cls_SkyStatus.def("getAverageH2OPathLength", static_cast<Length (SkyStatus::*)(unsigned int)>(&SkyStatus::getAverageH2OPathLength), py::arg("spwid"), "");
  cls_SkyStatus.def("getAverageH2OPathLength", static_cast<Length (SkyStatus::*)()>(&SkyStatus::getAverageH2OPathLength), "");
  cls_SkyStatus.def("getAverageH2OPathLengthDerivative", static_cast<double (SkyStatus::*)(unsigned int)>(&SkyStatus::getAverageH2OPathLengthDerivative), py::arg("spwid"), "");
  cls_SkyStatus.def("getAverageH2OPathLengthDerivative", static_cast<double (SkyStatus::*)()>(&SkyStatus::getAverageH2OPathLengthDerivative), "");
  cls_SkyStatus.def("getAverageH2OPhaseDelay", static_cast<Angle (SkyStatus::*)(unsigned int)>(&SkyStatus::getAverageH2OPhaseDelay), py::arg("spwid"), "");
  cls_SkyStatus.def("getAverageH2OPhaseDelay", static_cast<Angle (SkyStatus::*)()>(&SkyStatus::getAverageH2OPhaseDelay), "");
  cls_SkyStatus.def("getAverageDispersiveDryPathLength", static_cast<Length (SkyStatus::*)(unsigned int)>(&SkyStatus::getAverageDispersiveDryPathLength), py::arg("spwid"), "");
  cls_SkyStatus.def("getAverageDispersiveDryPathLength", static_cast<Length (SkyStatus::*)()>(&SkyStatus::getAverageDispersiveDryPathLength), "");
  cls_SkyStatus.def("getAverageNonDispersiveDryPathLength", static_cast<Length (SkyStatus::*)(unsigned int)>(&SkyStatus::getAverageNonDispersiveDryPathLength), py::arg("spwid"), "");
  cls_SkyStatus.def("getAverageNonDispersiveDryPathLength", static_cast<Length (SkyStatus::*)()>(&SkyStatus::getAverageNonDispersiveDryPathLength), "");
  cls_SkyStatus.def("getAverageNonDispersiveDryPathLength_GroundPressureDerivative", static_cast<double (SkyStatus::*)(unsigned int)>(&SkyStatus::getAverageNonDispersiveDryPathLength_GroundPressureDerivative), py::arg("spwid"), "");
  cls_SkyStatus.def("getAverageNonDispersiveDryPathLength_GroundTemperatureDerivative", static_cast<double (SkyStatus::*)(unsigned int)>(&SkyStatus::getAverageNonDispersiveDryPathLength_GroundTemperatureDerivative), py::arg("spwid"), "");
  cls_SkyStatus.def("getAverageDispersiveDryPathLength_GroundPressureDerivative", static_cast<double (SkyStatus::*)(unsigned int)>(&SkyStatus::getAverageDispersiveDryPathLength_GroundPressureDerivative), py::arg("spwid"), "");
  cls_SkyStatus.def("getAverageDispersiveDryPathLength_GroundTemperatureDerivative", static_cast<double (SkyStatus::*)(unsigned int)>(&SkyStatus::getAverageDispersiveDryPathLength_GroundTemperatureDerivative), py::arg("spwid"), "");
  cls_SkyStatus.def("getAverageO2LinesPathLength", static_cast<Length (SkyStatus::*)(unsigned int)>(&SkyStatus::getAverageO2LinesPathLength), py::arg("spwid"), "");
  cls_SkyStatus.def("getAverageO2LinesPathLength", static_cast<Length (SkyStatus::*)()>(&SkyStatus::getAverageO2LinesPathLength), "");
  cls_SkyStatus.def("setBasicAtmosphericParameters", static_cast<bool (SkyStatus::*)(const Length &)>(&SkyStatus::setBasicAtmosphericParameters), py::arg("altitude"), R"doc(The same setter is available for only one parameter each time (except for "Length wvScaleHeight" due to a type
conflict with "Length altitude"))doc");
  cls_SkyStatus.def("setBasicAtmosphericParameters", static_cast<bool (SkyStatus::*)(const Temperature &)>(&SkyStatus::setBasicAtmosphericParameters), py::arg("groundTemperature"), R"doc(The same setter is available for only one parameter each time (except for "Length wvScaleHeight" due to a type
conflict with "Length altitude"))doc");
  cls_SkyStatus.def("setBasicAtmosphericParameters", static_cast<bool (SkyStatus::*)(const Pressure &)>(&SkyStatus::setBasicAtmosphericParameters), py::arg("groundPressure"), R"doc(The same setter is available for only one parameter each time (except for "Length wvScaleHeight" due to a type
conflict with "Length altitude"))doc");
  cls_SkyStatus.def("setBasicAtmosphericParameters", static_cast<bool (SkyStatus::*)(const Humidity &)>(&SkyStatus::setBasicAtmosphericParameters), py::arg("humidity"), R"doc(The same setter is available for only one parameter each time (except for "Length wvScaleHeight" due to a type
conflict with "Length altitude"))doc");
  cls_SkyStatus.def("setBasicAtmosphericParameters", static_cast<bool (SkyStatus::*)(const Length &, const Temperature &)>(&SkyStatus::setBasicAtmosphericParameters), py::arg("altitude"), py::arg("groundTemperature"), R"doc(The same setter is available for couples of parameters. The order does not matter except for (Length altitude) and
(Length wvScaleHeight) because they are of the same type (Length). The convention is that if a type Length is in first
position, it represents the altitude, and if it is in second position, it represents wvScaleHeight)doc");
  cls_SkyStatus.def("setBasicAtmosphericParameters", static_cast<bool (SkyStatus::*)(const Length &, const Pressure &)>(&SkyStatus::setBasicAtmosphericParameters), py::arg("altitude"), py::arg("groundPressure"), R"doc(The same setter is available for couples of parameters. The order does not matter except for (Length altitude) and
(Length wvScaleHeight) because they are of the same type (Length). The convention is that if a type Length is in first
position, it represents the altitude, and if it is in second position, it represents wvScaleHeight)doc");
  cls_SkyStatus.def("setBasicAtmosphericParameters", static_cast<bool (SkyStatus::*)(const Length &, const Humidity &)>(&SkyStatus::setBasicAtmosphericParameters), py::arg("altitude"), py::arg("humidity"), R"doc(The same setter is available for couples of parameters. The order does not matter except for (Length altitude) and
(Length wvScaleHeight) because they are of the same type (Length). The convention is that if a type Length is in first
position, it represents the altitude, and if it is in second position, it represents wvScaleHeight)doc");
  cls_SkyStatus.def("setBasicAtmosphericParameters", static_cast<bool (SkyStatus::*)(const Length &, const Length &)>(&SkyStatus::setBasicAtmosphericParameters), py::arg("altitude"), py::arg("wvScaleHeight"), R"doc(The same setter is available for couples of parameters. The order does not matter except for (Length altitude) and
(Length wvScaleHeight) because they are of the same type (Length). The convention is that if a type Length is in first
position, it represents the altitude, and if it is in second position, it represents wvScaleHeight)doc");
  cls_SkyStatus.def("setBasicAtmosphericParameters", static_cast<bool (SkyStatus::*)(const Temperature &, const Pressure &)>(&SkyStatus::setBasicAtmosphericParameters), py::arg("groundTemperature"), py::arg("groundPressure"), R"doc(The same setter is available for couples of parameters. The order does not matter)doc");
  cls_SkyStatus.def("setBasicAtmosphericParameters", static_cast<bool (SkyStatus::*)(const Pressure &, const Temperature &)>(&SkyStatus::setBasicAtmosphericParameters), py::arg("groundPressure"), py::arg("groundTemperature"), R"doc(The same setter is available for couples of parameters. The order does not matter)doc");
  cls_SkyStatus.def("setBasicAtmosphericParameters", static_cast<bool (SkyStatus::*)(const Temperature &, const Humidity &)>(&SkyStatus::setBasicAtmosphericParameters), py::arg("groundTemperature"), py::arg("humidity"), R"doc(The same setter is available for couples of parameters. The order does not matter)doc");
  cls_SkyStatus.def("setBasicAtmosphericParameters", static_cast<bool (SkyStatus::*)(const Humidity &, const Temperature &)>(&SkyStatus::setBasicAtmosphericParameters), py::arg("humidity"), py::arg("groundTemperature"), R"doc(The same setter is available for couples of parameters. The order does not matter)doc");
  cls_SkyStatus.def("setBasicAtmosphericParameters", static_cast<bool (SkyStatus::*)(const Temperature &, const Length &)>(&SkyStatus::setBasicAtmosphericParameters), py::arg("groundTemperature"), py::arg("wvScaleHeight"), R"doc(The same setter is available for couples of parameters. The order does not matter except for (Length altitude) and
(Length wvScaleHeight) because they are of the same type (Length). The convention is that if a type Length is in first
position, it represents the altitude, and if it is in second position, it represents wvScaleHeight)doc");
  cls_SkyStatus.def("setBasicAtmosphericParameters", static_cast<bool (SkyStatus::*)(const Pressure &, const Humidity &)>(&SkyStatus::setBasicAtmosphericParameters), py::arg("groundPressure"), py::arg("humidity"), R"doc(The same setter is available for couples of parameters. The order does not matter)doc");
  cls_SkyStatus.def("setBasicAtmosphericParameters", static_cast<bool (SkyStatus::*)(const Humidity &, const Pressure &)>(&SkyStatus::setBasicAtmosphericParameters), py::arg("humidity"), py::arg("groundPressure"), R"doc(The same setter is available for couples of parameters. The order does not matter)doc");
  cls_SkyStatus.def("setBasicAtmosphericParameters", static_cast<bool (SkyStatus::*)(const Pressure &, const Length &)>(&SkyStatus::setBasicAtmosphericParameters), py::arg("groundPressure"), py::arg("wvScaleHeight"), R"doc(The same setter is available for couples of parameters. The order does not matter except for (Length altitude) and
(Length wvScaleHeight) because they are of the same type (Length). The convention is that if a type Length is in first
position, it represents the altitude, and if it is in second position, it represents wvScaleHeight)doc");
  cls_SkyStatus.def("setBasicAtmosphericParameters", static_cast<bool (SkyStatus::*)(const Humidity &, const Length &)>(&SkyStatus::setBasicAtmosphericParameters), py::arg("humidity"), py::arg("wvScaleHeight"), R"doc(The same setter is available for couples of parameters. The order does not matter except for (Length altitude) and
(Length wvScaleHeight) because they are of the same type (Length). The convention is that if a type Length is in first
position, it represents the altitude, and if it is in second position, it represents wvScaleHeight)doc");
  cls_SkyStatus.def("addNewSpectralWindow", static_cast<void (SkyStatus::*)(unsigned int, unsigned int, const Frequency &, const Frequency &)>(&SkyStatus::addNewSpectralWindow), py::arg("numChan"), py::arg("refChan"), py::arg("refFreq"), py::arg("chanSep"), R"doc(Setter of new spectral windows (adds frequencies to the SpectralGrid and calculates the corresponding absorption coefficients))doc");
  cls_SkyStatus.def("addNewSpectralWindow", [](SkyStatus &self, unsigned int numChan, unsigned int refChan, std::vector<double> chanFreq, Frequency::Units freqUnits) { return self.addNewSpectralWindow(numChan, refChan, chanFreq.data(), freqUnits); }, py::arg("numChan"), py::arg("refChan"), py::arg("chanFreq"), py::arg("freqUnits"), R"doc(Setter of new spectral windows (adds frequencies to the SpectralGrid and calculates the corresponding absorption coefficients))doc");
  cls_SkyStatus.def("addNewSpectralWindow", static_cast<void (SkyStatus::*)(unsigned int, unsigned int, const Frequency &, const Frequency &, const Frequency &, const SidebandSide &, const SidebandType &)>(&SkyStatus::addNewSpectralWindow), py::arg("numChan"), py::arg("refChan"), py::arg("refFreq"), py::arg("chanSep"), py::arg("intermediateFreq"), py::arg("sbSide"), py::arg("sbType"), R"doc(Setter of new spectral windows (adds frequencies to the SpectralGrid and calculates the corresponding absorption coefficients))doc");
  cls_SkyStatus.def("addNewSpectralWindow", static_cast<void (SkyStatus::*)(const std::vector<Frequency> &)>(&SkyStatus::addNewSpectralWindow), py::arg("chanFreq"), "");
  cls_SkyStatus.def("WaterVaporRetrieval_fromFTS", static_cast<Length (SkyStatus::*)(const std::vector<double> &)>(&SkyStatus::WaterVaporRetrieval_fromFTS), py::arg("v_transmission"), R"doc(Zenith Water Vapor column retrieval based on fitting the vector of zenith atmospheric transmission given as input.
Requirements: A) The FTS individual frequencies must be in spectral window 0, and B) the input zenith atmospheric
transmission vector should match those frequencies (i.e. both vectors should have the same size),
C) the air mass for the retrieval is the current one. If a different one is desired, it should be
changed using the setAirMass setter.)doc");
  cls_SkyStatus.def("WaterVaporRetrieval_fromFTS", static_cast<Length (SkyStatus::*)(const std::vector<double> &, const Frequency &, const Frequency &)>(&SkyStatus::WaterVaporRetrieval_fromFTS), py::arg("v_transmission"), py::arg("f1"), py::arg("f2"), R"doc(Same as above but using for the retrieval only the measurements between frequencies f1 and f2>f1)doc");
  cls_SkyStatus.def("WaterVaporRetrieval_fromFTS", static_cast<Length (SkyStatus::*)(unsigned int, const std::vector<double> &)>(&SkyStatus::WaterVaporRetrieval_fromFTS), py::arg("spwId"), py::arg("v_transmission"), R"doc(Zenith Water Vapor column retrieval based on fitting the vector of zenith atmospheric transmission given as input.
Requirements: A) The FTS individual frequencies must be in spectral window spwId, and B) the input zenith atmospheric
transmission vector should match those frequencies (i.e. both vectors should have the same size),
C) the air mass for the retrieval is the current one. If a different one is desired, it should be
changed using the setAirMass setter.)doc");
  cls_SkyStatus.def("WaterVaporRetrieval_fromFTS", static_cast<Length (SkyStatus::*)(unsigned int, const std::vector<double> &, const Frequency &, const Frequency &)>(&SkyStatus::WaterVaporRetrieval_fromFTS), py::arg("spwId"), py::arg("v_transmission"), py::arg("f1"), py::arg("f2"), R"doc(Same as above but using for the retrieval only the measurements between frequencies f1 and f2>f1)doc");
  cls_SkyStatus.def("WaterVaporRetrieval_fromTEBB", static_cast<Length (SkyStatus::*)(const std::vector<unsigned int> &, const std::vector<std::vector<Temperature>> &, const std::vector<double> &, const std::vector<Temperature> &)>(&SkyStatus::WaterVaporRetrieval_fromTEBB), py::arg("spwId"), py::arg("vv_tebb"), py::arg("skycoupling"), py::arg("tspill"), "");
  cls_SkyStatus.def("WaterVaporRetrieval_fromTEBB", static_cast<Length (SkyStatus::*)(const std::vector<unsigned int> &, const std::vector<Temperature> &, const std::vector<double> &, const std::vector<Temperature> &)>(&SkyStatus::WaterVaporRetrieval_fromTEBB), py::arg("spwId"), py::arg("v_tebb"), py::arg("skycoupling"), py::arg("tspill"), "");
  cls_SkyStatus.def("WaterVaporRetrieval_fromTEBB", static_cast<Length (SkyStatus::*)(const std::vector<unsigned int> &, const std::vector<std::vector<Temperature>> &, const std::vector<std::vector<double>> &, const std::vector<double> &, const std::vector<Temperature> &)>(&SkyStatus::WaterVaporRetrieval_fromTEBB), py::arg("spwId"), py::arg("vv_tebb"), py::arg("spwId_filters"), py::arg("skycoupling"), py::arg("tspill"), "");
  cls_SkyStatus.def("WaterVaporRetrieval_fromTEBB", static_cast<Length (SkyStatus::*)(const std::vector<unsigned int> &, const std::vector<Temperature> &, const std::vector<std::vector<double>> &, const std::vector<double> &, const std::vector<Temperature> &)>(&SkyStatus::WaterVaporRetrieval_fromTEBB), py::arg("spwId"), py::arg("v_tebb"), py::arg("spwId_filters"), py::arg("skycoupling"), py::arg("tspill"), "");
  cls_SkyStatus.def("WaterVaporRetrieval_fromTEBB", static_cast<Length (SkyStatus::*)(const std::vector<unsigned int> &, const std::vector<Percent> &, const std::vector<std::vector<Temperature>> &, const std::vector<double> &, const std::vector<Temperature> &)>(&SkyStatus::WaterVaporRetrieval_fromTEBB), py::arg("spwId"), py::arg("signalGain"), py::arg("vv_tebb"), py::arg("skycoupling"), py::arg("tspill"), "");
  cls_SkyStatus.def("WaterVaporRetrieval_fromTEBB", static_cast<Length (SkyStatus::*)(const std::vector<unsigned int> &, const std::vector<Percent> &, const std::vector<Temperature> &, const std::vector<double> &, const std::vector<Temperature> &)>(&SkyStatus::WaterVaporRetrieval_fromTEBB), py::arg("spwId"), py::arg("signalGain"), py::arg("v_tebb"), py::arg("skycoupling"), py::arg("tspill"), "");
  cls_SkyStatus.def("WaterVaporRetrieval_fromTEBB", static_cast<Length (SkyStatus::*)(const std::vector<unsigned int> &, const std::vector<Percent> &, const std::vector<std::vector<Temperature>> &, const std::vector<std::vector<double>> &, const std::vector<double> &, const std::vector<Temperature> &)>(&SkyStatus::WaterVaporRetrieval_fromTEBB), py::arg("spwId"), py::arg("signalGain"), py::arg("vv_tebb"), py::arg("spwId_filters"), py::arg("skycoupling"), py::arg("tspill"), "");
  cls_SkyStatus.def("WaterVaporRetrieval_fromTEBB", static_cast<Length (SkyStatus::*)(const std::vector<unsigned int> &, const std::vector<Percent> &, const std::vector<Temperature> &, const std::vector<std::vector<double>> &, const std::vector<double> &, const std::vector<Temperature> &)>(&SkyStatus::WaterVaporRetrieval_fromTEBB), py::arg("spwId"), py::arg("signalGain"), py::arg("v_tebb"), py::arg("spwId_filters"), py::arg("skycoupling"), py::arg("tspill"), "");
  cls_SkyStatus.def("setWaterVaporRadiometer", static_cast<void (SkyStatus::*)(const WaterVaporRadiometer &)>(&SkyStatus::setWaterVaporRadiometer), py::arg("waterVaporRadiometer"), R"doc((Re)setter of water vapor radiometer channels)doc");
  cls_SkyStatus.def("updateSkyCoupling_fromWVR", [](SkyStatus &self, py::list RadiometerData, unsigned int n, unsigned int m) { pyatm::ListRef<WVRMeasurement> RadiometerData_ref(RadiometerData); return self.updateSkyCoupling_fromWVR(RadiometerData_ref.vec, n, m); }, py::arg("RadiometerData"), py::arg("n"), py::arg("m"), R"doc(Performs a sky coupling retrieval using WVR measurement sets between n and m
(obtains the ratio between the current sky couplings of all WVR channels and the best fit that
results from WVR measurement sets between n and m, keeping the other parameters unchanged)
and uses the result to update the Skycoupling of all WVR channels)doc");
  cls_SkyStatus.def("updateSkyCouplingChannel_fromWVR", [](SkyStatus &self, py::list RadiometerData, unsigned int ichan, unsigned int n, unsigned int m) { pyatm::ListRef<WVRMeasurement> RadiometerData_ref(RadiometerData); return self.updateSkyCouplingChannel_fromWVR(RadiometerData_ref.vec, ichan, n, m); }, py::arg("RadiometerData"), py::arg("ichan"), py::arg("n"), py::arg("m"), R"doc(Performs a sky coupling retrieval using WVR measurement sets between n and m
(obtains the ratio between the current sky coupling of a single WVR channel (ichan) and the best fit that
results from WVR measurement sets between n and m, keeping the other parameters unchanged)
and uses the result to update the Skycoupling of than WVR channel)doc");
  cls_SkyStatus.def("updateSkyCoupling_fromWVR", [](SkyStatus &self, py::list RadiometerData, unsigned int n) { pyatm::ListRef<WVRMeasurement> RadiometerData_ref(RadiometerData); return self.updateSkyCoupling_fromWVR(RadiometerData_ref.vec, n); }, py::arg("RadiometerData"), py::arg("n"), "");
  cls_SkyStatus.def("updateSkyCoupling_fromWVR", [](SkyStatus &self, py::list RadiometerData, unsigned int n, unsigned int m, WaterVaporRadiometer & external_wvr) { pyatm::ListRef<WVRMeasurement> RadiometerData_ref(RadiometerData); return self.updateSkyCoupling_fromWVR(RadiometerData_ref.vec, n, m, external_wvr); }, py::arg("RadiometerData"), py::arg("n"), py::arg("m"), py::arg("external_wvr"), "");
  cls_SkyStatus.def("updateSkyCoupling_fromWVR", [](SkyStatus &self, py::list RadiometerData, unsigned int n, WaterVaporRadiometer & external_wvr) { pyatm::ListRef<WVRMeasurement> RadiometerData_ref(RadiometerData); return self.updateSkyCoupling_fromWVR(RadiometerData_ref.vec, n, external_wvr); }, py::arg("RadiometerData"), py::arg("n"), py::arg("external_wvr"), "");
  cls_SkyStatus.def("getWaterVaporRadiometerSkyCoupling", static_cast<double (SkyStatus::*)(int) const>(&SkyStatus::getWaterVaporRadiometerSkyCoupling), py::arg("n"), R"doc(Accessor to the sky coupling of channel n of the Water Vapor Radiometer)doc");
  cls_SkyStatus.def("getWaterVaporRadiometerSignalGain", static_cast<Percent (SkyStatus::*)(int) const>(&SkyStatus::getWaterVaporRadiometerSignalGain), py::arg("n"), R"doc(Accessor to the sky coupling of channel n of the Water Vapor Radiometer)doc");
  cls_SkyStatus.def("WaterVaporRetrieval_fromWVR", [](SkyStatus &self, py::list RadiometerData, unsigned int n, unsigned int m) { pyatm::ListRef<WVRMeasurement> RadiometerData_ref(RadiometerData); return self.WaterVaporRetrieval_fromWVR(RadiometerData_ref.vec, n, m); }, py::arg("RadiometerData"), py::arg("n"), py::arg("m"), R"doc(Performs water vapor retrieval for WVR measurement sets between n and m)doc");
  cls_SkyStatus.def("WaterVaporRetrieval_fromWVR", [](SkyStatus &self, py::list RadiometerData, unsigned int n) { pyatm::ListRef<WVRMeasurement> RadiometerData_ref(RadiometerData); return self.WaterVaporRetrieval_fromWVR(RadiometerData_ref.vec, n); }, py::arg("RadiometerData"), py::arg("n"), "");
  cls_SkyStatus.def("WaterVaporRetrieval_fromWVR", static_cast<void (SkyStatus::*)(WVRMeasurement &)>(&SkyStatus::WaterVaporRetrieval_fromWVR), py::arg("RadiometerData"), R"doc(Performs water vapor retrieval for one WVR measurement)doc");
  cls_SkyStatus.def("getWaterVaporRadiometer", static_cast<WaterVaporRadiometer (SkyStatus::*)() const>(&SkyStatus::getWaterVaporRadiometer), R"doc(Accessor to get or check the water vapor radiometer channels)doc");
  cls_SkyStatus.def("getWVRAverageSigmaTskyFit", static_cast<Temperature (SkyStatus::*)(const std::vector<WVRMeasurement> &, unsigned int, unsigned int)>(&SkyStatus::getWVRAverageSigmaTskyFit), py::arg("RadiometerData"), py::arg("n"), py::arg("m"), "");
  cls_SkyStatus.def("getWVRAverageSigmaTskyFit", static_cast<Temperature (SkyStatus::*)(const std::vector<WVRMeasurement> &, unsigned int)>(&SkyStatus::getWVRAverageSigmaTskyFit), py::arg("RadiometerData"), py::arg("n"), "");
  cls_SkyStatus.def("getWVRSigmaChannelTskyFit", static_cast<Temperature (SkyStatus::*)(const std::vector<WVRMeasurement> &, unsigned int, unsigned int, unsigned int)>(&SkyStatus::getWVRSigmaChannelTskyFit), py::arg("RadiometerData"), py::arg("ichan"), py::arg("n"), py::arg("m"), "");
  cls_SkyStatus.def(py::init<const RefractiveIndexProfile &, double>(), py::arg("refractiveIndexProfile"), py::arg("airMass"), R"doc(Class constructor with additional inputs)doc");
  cls_SkyStatus.def(py::init<const RefractiveIndexProfile &, const Temperature &, double>(), py::arg("refractiveIndexProfile"), py::arg("temperatureBackground"), py::arg("airMass"), R"doc(Class constructor with additional inputs)doc");
  cls_SkyStatus.def(py::init<const RefractiveIndexProfile &, double, const Temperature &>(), py::arg("refractiveIndexProfile"), py::arg("airMass"), py::arg("temperatureBackground"), R"doc(Class constructor with additional inputs)doc");
  cls_SkyStatus.def(py::init<const RefractiveIndexProfile &, const Length &, double>(), py::arg("refractiveIndexProfile"), py::arg("wh2o"), py::arg("airMass"), R"doc(Class constructor with additional inputs)doc");
  cls_SkyStatus.def(py::init<const RefractiveIndexProfile &, double, const Length &>(), py::arg("refractiveIndexProfile"), py::arg("airMass"), py::arg("wh2o"), R"doc(Class constructor with additional inputs)doc");
  cls_SkyStatus.def(py::init<const RefractiveIndexProfile &, const Temperature &, double, const Length &>(), py::arg("refractiveIndexProfile"), py::arg("temperatureBackground"), py::arg("airMass"), py::arg("wh2o"), R"doc(Class constructor with additional inputs)doc");
  cls_SkyStatus.def(py::init<const RefractiveIndexProfile &, const Temperature &, const Length &, double>(), py::arg("refractiveIndexProfile"), py::arg("temperatureBackground"), py::arg("wh2o"), py::arg("airMass"), R"doc(Class constructor with additional inputs)doc");
  cls_SkyStatus.def(py::init<const RefractiveIndexProfile &, double, const Temperature &, const Length &>(), py::arg("refractiveIndexProfile"), py::arg("airMass"), py::arg("temperatureBackground"), py::arg("wh2o"), R"doc(Class constructor with additional inputs)doc");
  cls_SkyStatus.def(py::init<const RefractiveIndexProfile &, double, const Length &, const Temperature &>(), py::arg("refractiveIndexProfile"), py::arg("airMass"), py::arg("wh2o"), py::arg("temperatureBackground"), R"doc(Class constructor with additional inputs)doc");
  cls_SkyStatus.def(py::init<const RefractiveIndexProfile &, const Length &, const Temperature &, double>(), py::arg("refractiveIndexProfile"), py::arg("wh2o"), py::arg("temperatureBackground"), py::arg("airMass"), R"doc(Class constructor with additional inputs)doc");
  cls_SkyStatus.def(py::init<const RefractiveIndexProfile &, const Length &, double, const Temperature &>(), py::arg("refractiveIndexProfile"), py::arg("wh2o"), py::arg("airMass"), py::arg("temperatureBackground"), R"doc(Class constructor with additional inputs)doc");
  cls_SkyStatus.def("setUserWH2O", static_cast<void (SkyStatus::*)(double, const std::string &)>(&SkyStatus::setUserWH2O), py::arg("dwh2o"), py::arg("units"), R"doc(Alternative form of the setter for user zenith water vapor column for forward radiative transfer calculations. The user
zenith water vapor column equals the retrieved zenith water vapor column from H2O radiometers,
every time the last one is derived with the retrieveandupdateWaterVapor accessor.)doc");
  cls_SkyStatus.def("setAirMass", static_cast<void (SkyStatus::*)(double)>(&SkyStatus::setAirMass), py::arg("airMass"), R"doc(Setter for air mass in SkyStatus without performing water vapor retrieval)doc");
  cls_SkyStatus.def("getAverageTebbSky", static_cast<Temperature (SkyStatus::*)(double)>(&SkyStatus::getAverageTebbSky), py::arg("airmass"), R"doc(Accesor to the average Equivalent Blackbody Temperature in spectral window 0, for the current
conditions, except Air Mass airmass, and a perfect sky coupling)doc");
  cls_SkyStatus.def("getAverageTebbSky", static_cast<Temperature (SkyStatus::*)(unsigned int, double)>(&SkyStatus::getAverageTebbSky), py::arg("spwid"), py::arg("airmass"), R"doc(Accesor to the average Equivalent Blackbody Temperature in spectral window spwid, for the current
conditions, except Air Mass airmass, and a perfect sky coupling)doc");
  cls_SkyStatus.def("getAverageTebbSky", static_cast<Temperature (SkyStatus::*)(const Length &, double, const Temperature &)>(&SkyStatus::getAverageTebbSky), py::arg("wh2o"), py::arg("skycoupling"), py::arg("Tspill"), R"doc(Accesor to the average Equivalent Blackbody Temperature in spectral window 0, for the current
conditions, except water column wh2o, introducing a Sky Coupling and Spill Over Temperature)doc");
  cls_SkyStatus.def("getAverageTebbSky", static_cast<Temperature (SkyStatus::*)(unsigned int, const Length &, double, const Temperature &)>(&SkyStatus::getAverageTebbSky), py::arg("spwid"), py::arg("wh2o"), py::arg("skycoupling"), py::arg("Tspill"), R"doc(Accesor to the average Equivalent Blackbody Temperature in spectral window spwid, for the current
conditions, except water column wh2o, introducing a Sky Coupling and Spill Over Temperature)doc");
  cls_SkyStatus.def("getAverageTebbSky", static_cast<Temperature (SkyStatus::*)(double, const Temperature &)>(&SkyStatus::getAverageTebbSky), py::arg("skycoupling"), py::arg("Tspill"), R"doc(Accesor to the average Equivalent Blackbody Temperature in spectral window 0 for the current
conditions, introducing a Sky Coupling and Spill Over Temperature)doc");
  cls_SkyStatus.def("getAverageTebbSky", static_cast<Temperature (SkyStatus::*)(unsigned int, double, const Temperature &)>(&SkyStatus::getAverageTebbSky), py::arg("spwid"), py::arg("skycoupling"), py::arg("Tspill"), R"doc(Accesor to the average Equivalent Blackbody Temperature in spectral window spwid for the current
conditions, introducing a Sky Coupling and Spill Over Temperature)doc");
  cls_SkyStatus.def("getTebbSky", static_cast<Temperature (SkyStatus::*)(double)>(&SkyStatus::getTebbSky), py::arg("airmass"), R"doc(Accesor to the Equivalent Blackbody Temperature in spectral window 0 and channel 0, for the currnet
(user) Water Vapor Column, Air Mass airmass, and perfect Sky Coupling to the sky)doc");
  cls_SkyStatus.def("getTebbSky", static_cast<Temperature (SkyStatus::*)(unsigned int, double)>(&SkyStatus::getTebbSky), py::arg("nc"), py::arg("airmass"), R"doc(Accesor to the Equivalent Blackbody Temperature in spectral window 0 and channel nc, for the currnet
(user) Water Vapor Column, Air Mass airmass, and perfect Sky Coupling to the sky)doc");
  cls_SkyStatus.def("getTebbSky", static_cast<Temperature (SkyStatus::*)(unsigned int, unsigned int, double)>(&SkyStatus::getTebbSky), py::arg("spwid"), py::arg("nc"), py::arg("airmass"), R"doc(Accesor to the Equivalent Blackbody Temperature in spectral window spwid and channel nc, for the currnet
(user) Water Vapor Column, Air Mass airmass, and perfect Sky Coupling to the sky)doc");
  cls_SkyStatus.def("getTebbSky", static_cast<Temperature (SkyStatus::*)(unsigned int, double, const Temperature &)>(&SkyStatus::getTebbSky), py::arg("nc"), py::arg("skycoupling"), py::arg("Tspill"), R"doc(Accesor to the Equivalent Blackbody Temperature in spectral window 0 and channel nc, for the current
(user) Water Vapor Column and Air Mass, Sky Coupling skycoupling, and Spill Over Temperature Tspill)doc");
  cls_SkyStatus.def("getTebbSky", static_cast<Temperature (SkyStatus::*)(unsigned int, unsigned int, double, const Temperature &)>(&SkyStatus::getTebbSky), py::arg("spwid"), py::arg("nc"), py::arg("skycoupling"), py::arg("Tspill"), R"doc(Accesor to the Equivalent Blackbody Temperature in spectral window spwid and channel nc, for the current
(user) Water Vapor Column and Air Mass, Sky Coupling skycoupling, and Spill Over Temperature Tspill)doc");
  cls_SkyStatus.def("getTebbSky", static_cast<Temperature (SkyStatus::*)(unsigned int, const Length &, double)>(&SkyStatus::getTebbSky), py::arg("nc"), py::arg("wh2o"), py::arg("airmass"), R"doc(Accesor to the Equivalent Blackbody Temperature in spectral window 0 and channel nc, for Water
Vapor Column wh2o, Air Mass airmass, and perfect Sky Coupling to the sky)doc");
  cls_SkyStatus.def("getTebbSky", static_cast<Temperature (SkyStatus::*)(unsigned int, unsigned int, const Length &, double)>(&SkyStatus::getTebbSky), py::arg("spwid"), py::arg("nc"), py::arg("wh2o"), py::arg("airmass"), R"doc(Accesor to the Equivalent Blackbody Temperature in spectral window spwid and channel nc, for Water
Vapor Column wh2o, Air Mass airmass, and perfect Sky Coupling to the sky)doc");
  cls_SkyStatus.def("getTebbSky", static_cast<Temperature (SkyStatus::*)(unsigned int, const Length &, double, const Temperature &)>(&SkyStatus::getTebbSky), py::arg("nc"), py::arg("wh2o"), py::arg("skycoupling"), py::arg("Tspill"), R"doc(Accesor to the Equivalent Blackbody Temperature in spectral window 0 and channel nc, for Water
Vapor Column wh2o, the current Air Mass, Sky Coupling skycoupling, and Spill Over Temperature Tspill)doc");
  cls_SkyStatus.def("getTebbSky", static_cast<Temperature (SkyStatus::*)(unsigned int, unsigned int, const Length &, double, const Temperature &)>(&SkyStatus::getTebbSky), py::arg("spwid"), py::arg("nc"), py::arg("wh2o"), py::arg("skycoupling"), py::arg("Tspill"), R"doc(Accesor to the Equivalent Blackbody Temperature in spectral window spwid and channel nc, for Water
Vapor Column wh2o, the current Air Mass, Sky Coupling skycoupling, and Spill Over Temperature Tspill)doc");
  cls_SkyStatus.def("getAverageTrjSky", static_cast<Temperature (SkyStatus::*)(double)>(&SkyStatus::getAverageTrjSky), py::arg("airmass"), R"doc(Accesor to the average Rayleigh-Jeans Temperature in spectral window 0, for the current
conditions, except Air Mass airmass, and a perfect sky coupling)doc");
  cls_SkyStatus.def("getAverageTrjSky", static_cast<Temperature (SkyStatus::*)(unsigned int, double)>(&SkyStatus::getAverageTrjSky), py::arg("spwid"), py::arg("airmass"), R"doc(Accesor to the average Rayleigh-Jeans Temperature in spectral window spwid, for the current
conditions, except Air Mass airmass, and a perfect sky coupling)doc");
  cls_SkyStatus.def("getAverageTrjSky", static_cast<Temperature (SkyStatus::*)(const Length &, double, const Temperature &)>(&SkyStatus::getAverageTrjSky), py::arg("wh2o"), py::arg("skycoupling"), py::arg("Tspill"), R"doc(Accesor to the average Rayleigh-Jeans Temperature in spectral window 0, for the current
conditions, except water column wh2o, introducing a Sky Coupling and Spill Over Temperature)doc");
  cls_SkyStatus.def("getAverageTrjSky", static_cast<Temperature (SkyStatus::*)(unsigned int, const Length &, double, const Temperature &)>(&SkyStatus::getAverageTrjSky), py::arg("spwid"), py::arg("wh2o"), py::arg("skycoupling"), py::arg("Tspill"), R"doc(Accesor to the average Rayleigh-Jeans Temperature in spectral window spwid, for the current
conditions, except water column wh2o, introducing a Sky Coupling and Spill Over Temperature)doc");
  cls_SkyStatus.def("getAverageTrjSky", static_cast<Temperature (SkyStatus::*)(double, const Temperature &)>(&SkyStatus::getAverageTrjSky), py::arg("skycoupling"), py::arg("Tspill"), R"doc(Accesor to the average Rayleigh-Jeans Temperature in spectral window 0 for the current
conditions, introducing a Sky Coupling and Spill Over Temperature)doc");
  cls_SkyStatus.def("getAverageTrjSky", static_cast<Temperature (SkyStatus::*)(unsigned int, double, const Temperature &)>(&SkyStatus::getAverageTrjSky), py::arg("spwid"), py::arg("skycoupling"), py::arg("Tspill"), R"doc(Accesor to the average Rayleigh-Jeans Temperature in spectral window spwid for the current
conditions, introducing a Sky Coupling and Spill Over Temperature)doc");
  cls_SkyStatus.def("getTrjSky", static_cast<Temperature (SkyStatus::*)(double)>(&SkyStatus::getTrjSky), py::arg("airmass"), R"doc(Accesor to the Rayleigh-Jeans Temperature in spectral window 0 and channel 0, for the currnet
(user) Water Vapor Column, Air Mass airmass, and perfect Sky Coupling to the sky)doc");
  cls_SkyStatus.def("getTrjSky", static_cast<Temperature (SkyStatus::*)(unsigned int, double)>(&SkyStatus::getTrjSky), py::arg("nc"), py::arg("airmass"), R"doc(Accesor to the Rayleigh-Jeans Temperature in spectral window 0 and channel nc, for the currnet
(user) Water Vapor Column, Air Mass airmass, and perfect Sky Coupling to the sky)doc");
  cls_SkyStatus.def("getTrjSky", static_cast<Temperature (SkyStatus::*)(unsigned int, unsigned int, double)>(&SkyStatus::getTrjSky), py::arg("spwid"), py::arg("nc"), py::arg("airmass"), R"doc(Accesor to the Rayleigh-Jeans Temperature in spectral window spwid and channel nc, for the currnet
(user) Water Vapor Column, Air Mass airmass, and perfect Sky Coupling to the sky)doc");
  cls_SkyStatus.def("getTrjSky", static_cast<Temperature (SkyStatus::*)(unsigned int, double, const Temperature &)>(&SkyStatus::getTrjSky), py::arg("nc"), py::arg("skycoupling"), py::arg("Tspill"), R"doc(Accesor to the Rayleigh-Jeans Temperature in spectral window 0 and channel nc, for the current
(user) Water Vapor Column and Air Mass, Sky Coupling skycoupling, and Spill Over Temperature Tspill)doc");
  cls_SkyStatus.def("getTrjSky", static_cast<Temperature (SkyStatus::*)(unsigned int, unsigned int, double, const Temperature &)>(&SkyStatus::getTrjSky), py::arg("spwid"), py::arg("nc"), py::arg("skycoupling"), py::arg("Tspill"), R"doc(Accesor to the Rayleigh-Jeans Temperature in spectral window spwid and channel nc, for the current
(user) Water Vapor Column and Air Mass, Sky Coupling skycoupling, and Spill Over Temperature Tspill)doc");
  cls_SkyStatus.def("getTrjSky", static_cast<Temperature (SkyStatus::*)(unsigned int, const Length &, double)>(&SkyStatus::getTrjSky), py::arg("nc"), py::arg("wh2o"), py::arg("airmass"), R"doc(Accesor to the Rayleigh-Jeans Temperature in spectral window 0 and channel nc, for Water
Vapor Column wh2o, Air Mass airmass, and perfect Sky Coupling to the sky)doc");
  cls_SkyStatus.def("getTrjSky", static_cast<Temperature (SkyStatus::*)(unsigned int, unsigned int, const Length &, double)>(&SkyStatus::getTrjSky), py::arg("spwid"), py::arg("nc"), py::arg("wh2o"), py::arg("airmass"), R"doc(Accesor to the Rayleigh-Jeans Temperature in spectral window spwid and channel nc, for Water
Vapor Column wh2o, Air Mass airmass, and perfect Sky Coupling to the sky)doc");
  cls_SkyStatus.def("getTrjSky", static_cast<Temperature (SkyStatus::*)(unsigned int, const Length &, double, const Temperature &)>(&SkyStatus::getTrjSky), py::arg("nc"), py::arg("wh2o"), py::arg("skycoupling"), py::arg("Tspill"), R"doc(Accesor to the Rayleigh-Jeans Temperature in spectral window 0 and channel nc, for Water
Vapor Column wh2o, the current Air Mass, Sky Coupling skycoupling, and Spill Over Temperature Tspill)doc");
  cls_SkyStatus.def("getTrjSky", static_cast<Temperature (SkyStatus::*)(unsigned int, unsigned int, const Length &, double, const Temperature &)>(&SkyStatus::getTrjSky), py::arg("spwid"), py::arg("nc"), py::arg("wh2o"), py::arg("skycoupling"), py::arg("Tspill"), R"doc(Accesor to the Rayleigh-Jeans Temperature in spectral window spwid and channel nc, for Water
Vapor Column wh2o, the current Air Mass, Sky Coupling skycoupling, and Spill Over Temperature Tspill)doc");
  cls_SkyStatus.def("setBasicAtmosphericParameters", static_cast<bool (SkyStatus::*)(const Length &, const Pressure &, const Temperature &, double, const Humidity &, const Length &)>(&SkyStatus::setBasicAtmosphericParameters), py::arg("altitude"), py::arg("groundPressure"), py::arg("groundTemperature"), py::arg("tropoLapseRate"), py::arg("humidity"), py::arg("wvScaleHeight"), R"doc(Setter for a new set of basic atmospheric parameters. Automatically updates the AtmProfile
(if generated from this basic atmospheric parameters), RefractiveIndexProfile, and SkyStatus
objects if the one or more value differ from the previous ones (there is overloading))doc");
  cls_SkyStatus.def("setBasicAtmosphericParameters", static_cast<bool (SkyStatus::*)(double)>(&SkyStatus::setBasicAtmosphericParameters), py::arg("tropoLapseRate"), R"doc(The same setter is available for only one parameter each time (except for "Length wvScaleHeight" due to a type
conflict with "Length altitude"))doc");
  cls_SkyStatus.def("setBasicAtmosphericParameters", static_cast<bool (SkyStatus::*)(const Length &, double)>(&SkyStatus::setBasicAtmosphericParameters), py::arg("altitude"), py::arg("tropoLapseRate"), R"doc(The same setter is available for couples of parameters. The order does not matter except for (Length altitude) and
(Length wvScaleHeight) because they are of the same type (Length). The convention is that if a type Length is in first
position, it represents the altitude, and if it is in second position, it represents wvScaleHeight)doc");
  cls_SkyStatus.def("setBasicAtmosphericParameters", static_cast<bool (SkyStatus::*)(const Temperature &, double)>(&SkyStatus::setBasicAtmosphericParameters), py::arg("groundTemperature"), py::arg("tropoLapseRate"), R"doc(The same setter is available for couples of parameters. The order does not matter)doc");
  cls_SkyStatus.def("setBasicAtmosphericParameters", static_cast<bool (SkyStatus::*)(double, const Temperature &)>(&SkyStatus::setBasicAtmosphericParameters), py::arg("tropoLapseRate"), py::arg("groundTemperature"), R"doc(The same setter is available for couples of parameters. The order does not matter)doc");
  cls_SkyStatus.def("setBasicAtmosphericParameters", static_cast<bool (SkyStatus::*)(const Pressure &, double)>(&SkyStatus::setBasicAtmosphericParameters), py::arg("groundPressure"), py::arg("tropoLapseRate"), R"doc(The same setter is available for couples of parameters. The order does not matter)doc");
  cls_SkyStatus.def("setBasicAtmosphericParameters", static_cast<bool (SkyStatus::*)(double, const Pressure &)>(&SkyStatus::setBasicAtmosphericParameters), py::arg("tropoLapseRate"), py::arg("groundPressure"), R"doc(The same setter is available for couples of parameters. The order does not matter)doc");
  cls_SkyStatus.def("setBasicAtmosphericParameters", static_cast<bool (SkyStatus::*)(const Humidity &, double)>(&SkyStatus::setBasicAtmosphericParameters), py::arg("humidity"), py::arg("tropoLapseRate"), R"doc(The same setter is available for couples of parameters. The order does not matter)doc");
  cls_SkyStatus.def("setBasicAtmosphericParameters", static_cast<bool (SkyStatus::*)(double, const Humidity &)>(&SkyStatus::setBasicAtmosphericParameters), py::arg("tropoLapseRate"), py::arg("humidity"), R"doc(The same setter is available for couples of parameters. The order does not matter)doc");
  cls_SkyStatus.def("setBasicAtmosphericParameters", static_cast<bool (SkyStatus::*)(double, const Length &)>(&SkyStatus::setBasicAtmosphericParameters), py::arg("tropoLapseRate"), py::arg("wvScaleHeight"), R"doc(The same setter is available for couples of parameters. The order does not matter except for (Length altitude) and
(Length wvScaleHeight) because they are of the same type (Length). The convention is that if a type Length is in first
position, it represents the altitude, and if it is in second position, it represents wvScaleHeight)doc");
  cls_SkyStatus.def("addNewSpectralWindow", [](SkyStatus &self, unsigned int numChan, double refFreq, std::vector<double> chanFreq, Frequency::Units freqUnits) { return self.addNewSpectralWindow(numChan, refFreq, chanFreq.data(), freqUnits); }, py::arg("numChan"), py::arg("refFreq"), py::arg("chanFreq"), py::arg("freqUnits"), R"doc(Setter of new spectral windows (adds frequencies to the SpectralGrid and calculates the corresponding absorption coefficients))doc");
  cls_SkyStatus.def("addNewSpectralWindow", static_cast<void (SkyStatus::*)(unsigned int, double, const std::vector<double> &, Frequency::Units)>(&SkyStatus::addNewSpectralWindow), py::arg("numChan"), py::arg("refFreq"), py::arg("chanFreq"), py::arg("freqUnits"), R"doc(Setter of new spectral windows (adds frequencies to the SpectralGrid and calculates the corresponding absorption coefficients))doc");
  cls_SkyStatus.def("WaterVaporRetrieval_fromTEBB", static_cast<Length (SkyStatus::*)(const std::vector<unsigned int> &, const std::vector<Percent> &, const std::vector<std::vector<Temperature>> &, const std::vector<std::vector<double>> &, double, const std::vector<double> &, const std::vector<Temperature> &)>(&SkyStatus::WaterVaporRetrieval_fromTEBB), py::arg("spwId"), py::arg("signalGain"), py::arg("vv_tebb"), py::arg("spwId_filters"), py::arg("airmass"), py::arg("skycoupling"), py::arg("tspill"), R"doc(Zenith Water Vapor column retrieval based on fitting measured brightness temperatures of the atmosphere)doc");
  cls_SkyStatus.def("WaterVaporRetrieval_fromTEBB", static_cast<Length (SkyStatus::*)(const std::vector<unsigned int> &, const std::vector<Percent> &, const std::vector<Temperature> &, const std::vector<std::vector<double>> &, double, const std::vector<double> &, const std::vector<Temperature> &)>(&SkyStatus::WaterVaporRetrieval_fromTEBB), py::arg("spwId"), py::arg("signalGain"), py::arg("v_tebb"), py::arg("spwId_filters"), py::arg("airmass"), py::arg("skycoupling"), py::arg("tspill"), "");
  cls_SkyStatus.def("WaterVaporRetrieval_fromTEBB", static_cast<Length (SkyStatus::*)(unsigned int, const std::vector<Temperature> &, double, const Temperature &)>(&SkyStatus::WaterVaporRetrieval_fromTEBB), py::arg("spwId"), py::arg("v_tebb"), py::arg("skycoupling"), py::arg("tspill"), "");
  cls_SkyStatus.def("WaterVaporRetrieval_fromTEBB", static_cast<Length (SkyStatus::*)(unsigned int, const std::vector<Temperature> &, const std::vector<double> &, double, const Temperature &)>(&SkyStatus::WaterVaporRetrieval_fromTEBB), py::arg("spwId"), py::arg("v_tebb"), py::arg("spwId_filter"), py::arg("skycoupling"), py::arg("tspill"), "");
  cls_SkyStatus.def("WaterVaporRetrieval_fromTEBB", static_cast<Length (SkyStatus::*)(const std::vector<unsigned int> &, const std::vector<std::vector<Temperature>> &, double, const std::vector<double> &, const std::vector<Temperature> &)>(&SkyStatus::WaterVaporRetrieval_fromTEBB), py::arg("spwId"), py::arg("vv_tebb"), py::arg("airmass"), py::arg("skycoupling"), py::arg("tspill"), "");
  cls_SkyStatus.def("WaterVaporRetrieval_fromTEBB", static_cast<Length (SkyStatus::*)(const std::vector<unsigned int> &, const std::vector<Temperature> &, double, const std::vector<double> &, const std::vector<Temperature> &)>(&SkyStatus::WaterVaporRetrieval_fromTEBB), py::arg("spwId"), py::arg("v_tebb"), py::arg("airmass"), py::arg("skycoupling"), py::arg("tspill"), "");
  cls_SkyStatus.def("WaterVaporRetrieval_fromTEBB", static_cast<Length (SkyStatus::*)(const std::vector<unsigned int> &, const std::vector<std::vector<Temperature>> &, const std::vector<std::vector<double>> &, double, const std::vector<double> &, const std::vector<Temperature> &)>(&SkyStatus::WaterVaporRetrieval_fromTEBB), py::arg("spwId"), py::arg("vv_tebb"), py::arg("spwId_filters"), py::arg("airmass"), py::arg("skycoupling"), py::arg("tspill"), "");
  cls_SkyStatus.def("WaterVaporRetrieval_fromTEBB", static_cast<Length (SkyStatus::*)(const std::vector<unsigned int> &, const std::vector<Temperature> &, const std::vector<std::vector<double>> &, double, const std::vector<double> &, const std::vector<Temperature> &)>(&SkyStatus::WaterVaporRetrieval_fromTEBB), py::arg("spwId"), py::arg("v_tebb"), py::arg("spwId_filters"), py::arg("airmass"), py::arg("skycoupling"), py::arg("tspill"), "");
  cls_SkyStatus.def("WaterVaporRetrieval_fromTEBB", static_cast<Length (SkyStatus::*)(unsigned int, const Percent &, const std::vector<Temperature> &, double, const Temperature &)>(&SkyStatus::WaterVaporRetrieval_fromTEBB), py::arg("spwId"), py::arg("signalGain"), py::arg("v_tebb"), py::arg("skycoupling"), py::arg("tspill"), "");
  cls_SkyStatus.def("WaterVaporRetrieval_fromTEBB", static_cast<Length (SkyStatus::*)(unsigned int, const Percent &, const std::vector<Temperature> &, const std::vector<double> &, double, const Temperature &)>(&SkyStatus::WaterVaporRetrieval_fromTEBB), py::arg("spwId"), py::arg("signalGain"), py::arg("v_tebb"), py::arg("spwId_filter"), py::arg("skycoupling"), py::arg("tspill"), "");
  cls_SkyStatus.def("WaterVaporRetrieval_fromTEBB", static_cast<Length (SkyStatus::*)(const std::vector<unsigned int> &, const std::vector<Percent> &, const std::vector<std::vector<Temperature>> &, double, const std::vector<double> &, const std::vector<Temperature> &)>(&SkyStatus::WaterVaporRetrieval_fromTEBB), py::arg("spwId"), py::arg("signalGain"), py::arg("vv_tebb"), py::arg("airmass"), py::arg("skycoupling"), py::arg("tspill"), "");
  cls_SkyStatus.def("WaterVaporRetrieval_fromTEBB", static_cast<Length (SkyStatus::*)(const std::vector<unsigned int> &, const std::vector<Percent> &, const std::vector<Temperature> &, double, const std::vector<double> &, const std::vector<Temperature> &)>(&SkyStatus::WaterVaporRetrieval_fromTEBB), py::arg("spwId"), py::arg("signalGain"), py::arg("v_tebb"), py::arg("airmass"), py::arg("skycoupling"), py::arg("tspill"), "");
  cls_SkyStatus.def("SkyCouplingRetrieval_fromTEBB", static_cast<double (SkyStatus::*)(unsigned int, const std::vector<Temperature> &, double, const Temperature &)>(&SkyStatus::SkyCouplingRetrieval_fromTEBB), py::arg("spwId"), py::arg("v_tebb"), py::arg("skycoupling"), py::arg("tspill"), "");
  cls_SkyStatus.def("SkyCouplingRetrieval_fromTEBB", static_cast<double (SkyStatus::*)(unsigned int, const std::vector<Temperature> &, const std::vector<double> &, double, const Temperature &)>(&SkyStatus::SkyCouplingRetrieval_fromTEBB), py::arg("spwId"), py::arg("v_tebb"), py::arg("spwId_filter"), py::arg("skycoupling"), py::arg("tspill"), "");
  cls_SkyStatus.def("sigmaSkyCouplingRetrieval_fromWVR", [](SkyStatus &self, double par_fit, const WaterVaporRadiometer & wvr, py::list RadiometerData, unsigned int n, unsigned int m) { pyatm::ListRef<WVRMeasurement> RadiometerData_ref(RadiometerData); return self.sigmaSkyCouplingRetrieval_fromWVR(par_fit, wvr, RadiometerData_ref.vec, n, m); }, py::arg("par_fit"), py::arg("wvr"), py::arg("RadiometerData"), py::arg("n"), py::arg("m"), "");
  cls_SkyStatus.def("sigmaSkyCouplingRetrieval_fromWVR", [](SkyStatus &self, double par_fit, const WaterVaporRadiometer & wvr, py::list RadiometerData, unsigned int n) { pyatm::ListRef<WVRMeasurement> RadiometerData_ref(RadiometerData); return self.sigmaSkyCouplingRetrieval_fromWVR(par_fit, wvr, RadiometerData_ref.vec, n); }, py::arg("par_fit"), py::arg("wvr"), py::arg("RadiometerData"), py::arg("n"), "");
  cls_SkyStatus.def("sigmaSkyCouplingChannelRetrieval_fromWVR", [](SkyStatus &self, double par_fit, const WaterVaporRadiometer & wvr, py::list RadiometerData, unsigned int ichan, unsigned int n, unsigned int m) { pyatm::ListRef<WVRMeasurement> RadiometerData_ref(RadiometerData); return self.sigmaSkyCouplingChannelRetrieval_fromWVR(par_fit, wvr, RadiometerData_ref.vec, ichan, n, m); }, py::arg("par_fit"), py::arg("wvr"), py::arg("RadiometerData"), py::arg("ichan"), py::arg("n"), py::arg("m"), "");
  cls_SkyStatus.def("getSigmaTransmissionFit", static_cast<double (SkyStatus::*)(unsigned int, const std::vector<double> &, double, const Frequency &, const Frequency &)>(&SkyStatus::getSigmaTransmissionFit), py::arg("spwId"), py::arg("v_transmission"), py::arg("airm"), py::arg("f1"), py::arg("f2"), "");
  cls_SkyStatus.def("getSigmaFit", static_cast<Temperature (SkyStatus::*)(unsigned int, const std::vector<Temperature> &, double, const Temperature &)>(&SkyStatus::getSigmaFit), py::arg("spwId"), py::arg("v_tebbspec"), py::arg("skyCoupling"), py::arg("Tspill"), "");
  cls_SkyStatus.def("getSigmaFit", static_cast<Temperature (SkyStatus::*)(unsigned int, const std::vector<Temperature> &, const Length &, double, const Temperature &)>(&SkyStatus::getSigmaFit), py::arg("spwId"), py::arg("v_tebbspec"), py::arg("wh2o"), py::arg("skyCoupling"), py::arg("Tspill"), "");
  cls_SkyStatus.def("getAverageTebbSky", static_cast<Temperature (SkyStatus::*)(double, double, const Temperature &)>(&SkyStatus::getAverageTebbSky), py::arg("airmass"), py::arg("skycoupling"), py::arg("Tspill"), R"doc(Accesor to the average Equivalent Blackbody Temperature in spectral window 0, for the current
conditions, except Air Mass airmass, introducing a Sky Coupling and Spill Over Temperature)doc");
  cls_SkyStatus.def("getAverageTebbSky", static_cast<Temperature (SkyStatus::*)(unsigned int, double, double, const Temperature &)>(&SkyStatus::getAverageTebbSky), py::arg("spwid"), py::arg("airmass"), py::arg("skycoupling"), py::arg("Tspill"), R"doc(Accesor to the average Equivalent Blackbody Temperature in spectral window spwid, for the current
conditions, except Air Mass airmass, introducing a Sky Coupling and Spill Over Temperature)doc");
  cls_SkyStatus.def("getAverageTebbSky", static_cast<Temperature (SkyStatus::*)(unsigned int, const Length &, double, double, const Temperature &)>(&SkyStatus::getAverageTebbSky), py::arg("spwid"), py::arg("wh2o"), py::arg("airmass"), py::arg("skycoupling"), py::arg("Tspill"), R"doc(Accesor to the average Equivalent Blackbody Temperature in spectral window spwid, for Water Column
wh2o, Air Mass airmass, Sky Coupling skycoupling, and Spill Over Temperature Tspill)doc");
  cls_SkyStatus.def("getTebbSky", static_cast<Temperature (SkyStatus::*)(unsigned int, double, double, const Temperature &)>(&SkyStatus::getTebbSky), py::arg("nc"), py::arg("airmass"), py::arg("skycoupling"), py::arg("Tspill"), R"doc(Accesor to the Equivalent Blackbody Temperature in spectral window 0 and channel nc, for the current
User Water Column, Air Mass airmass, Sky Coupling skycoupling, and Spill Over Temperature Tspill)doc");
  cls_SkyStatus.def("getTebbSky", static_cast<Temperature (SkyStatus::*)(unsigned int, unsigned int, double, double, const Temperature &)>(&SkyStatus::getTebbSky), py::arg("spwid"), py::arg("nc"), py::arg("airmass"), py::arg("skycoupling"), py::arg("Tspill"), R"doc(Accesor to the Equivalent Blackbody Temperature in spectral window spwid and channel nc, for the current
User Water Column, Air Mass airmass, Sky Coupling skycoupling, and Spill Over Temperature Tspill)doc");
  cls_SkyStatus.def("getTebbSky", static_cast<Temperature (SkyStatus::*)(unsigned int, const Length &, double, double, const Temperature &)>(&SkyStatus::getTebbSky), py::arg("nc"), py::arg("wh2o"), py::arg("airmass"), py::arg("skycoupling"), py::arg("Tspill"), R"doc(Accesor to the Equivalent Blackbody Temperature in spectral window 0 and channel nc, for Water Column
wh2o, Air Mass airmass, Sky Coupling skycoupling, and Spill Over Temperature Tspill)doc");
  cls_SkyStatus.def("getTebbSky", static_cast<Temperature (SkyStatus::*)(unsigned int, unsigned int, const Length &, double, double, const Temperature &)>(&SkyStatus::getTebbSky), py::arg("spwid"), py::arg("nc"), py::arg("wh2o"), py::arg("airmass"), py::arg("skycoupling"), py::arg("Tspill"), R"doc(Accesor to the Equivalent Blackbody Temperature in spectral window spwid and channel nc, for Water Column
wh2o, Air Mass airmass, Sky Coupling skycoupling, and Spill Over Temperature Tspill)doc");
  cls_SkyStatus.def("getAverageTrjSky", static_cast<Temperature (SkyStatus::*)(double, double, const Temperature &)>(&SkyStatus::getAverageTrjSky), py::arg("airmass"), py::arg("skycoupling"), py::arg("Tspill"), R"doc(Accesor to the average Rayleigh-Jeans Temperature in spectral window 0, for the current
conditions, except Air Mass airmass, introducing a Sky Coupling and Spill Over Temperature)doc");
  cls_SkyStatus.def("getAverageTrjSky", static_cast<Temperature (SkyStatus::*)(unsigned int, double, double, const Temperature &)>(&SkyStatus::getAverageTrjSky), py::arg("spwid"), py::arg("airmass"), py::arg("skycoupling"), py::arg("Tspill"), R"doc(Accesor to the average Rayleigh-Jeans Temperature in spectral window spwid, for the current
conditions, except Air Mass airmass, introducing a Sky Coupling and Spill Over Temperature)doc");
  cls_SkyStatus.def("getAverageTrjSky", static_cast<Temperature (SkyStatus::*)(unsigned int, const Length &, double, double, const Temperature &)>(&SkyStatus::getAverageTrjSky), py::arg("spwid"), py::arg("wh2o"), py::arg("airmass"), py::arg("skycoupling"), py::arg("Tspill"), R"doc(Accesor to the average Rayleigh-Jeans Temperature in spectral window spwid, for Water Column
wh2o, Air Mass airmass, Sky Coupling skycoupling, and Spill Over Temperature Tspill)doc");
  cls_SkyStatus.def("getTrjSky", static_cast<Temperature (SkyStatus::*)(unsigned int, double, double, const Temperature &)>(&SkyStatus::getTrjSky), py::arg("nc"), py::arg("airmass"), py::arg("skycoupling"), py::arg("Tspill"), R"doc(Accesor to the Rayleigh-Jeans Temperature in spectral window 0 and channel nc, for the current
User Water Column, Air Mass airmass, Sky Coupling skycoupling, and Spill Over Temperature Tspill)doc");
  cls_SkyStatus.def("getTrjSky", static_cast<Temperature (SkyStatus::*)(unsigned int, unsigned int, double, double, const Temperature &)>(&SkyStatus::getTrjSky), py::arg("spwid"), py::arg("nc"), py::arg("airmass"), py::arg("skycoupling"), py::arg("Tspill"), R"doc(Accesor to the Rayleigh-Jeans Temperature in spectral window spwid and channel nc, for the current
User Water Column, Air Mass airmass, Sky Coupling skycoupling, and Spill Over Temperature Tspill)doc");
  cls_SkyStatus.def("getTrjSky", static_cast<Temperature (SkyStatus::*)(unsigned int, const Length &, double, double, const Temperature &)>(&SkyStatus::getTrjSky), py::arg("nc"), py::arg("wh2o"), py::arg("airmass"), py::arg("skycoupling"), py::arg("Tspill"), R"doc(Accesor to the Rayleigh-Jeans Temperature in spectral window 0 and channel nc, for Water Column
wh2o, Air Mass airmass, Sky Coupling skycoupling, and Spill Over Temperature Tspill)doc");
  cls_SkyStatus.def("getTrjSky", static_cast<Temperature (SkyStatus::*)(unsigned int, unsigned int, const Length &, double, double, const Temperature &)>(&SkyStatus::getTrjSky), py::arg("spwid"), py::arg("nc"), py::arg("wh2o"), py::arg("airmass"), py::arg("skycoupling"), py::arg("Tspill"), R"doc(Accesor to the Rayleigh-Jeans Temperature in spectral window spwid and channel nc, for Water Column
wh2o, Air Mass airmass, Sky Coupling skycoupling, and Spill Over Temperature Tspill)doc");
  cls_SkyStatus.def("WaterVaporRetrieval_fromTEBB", static_cast<Length (SkyStatus::*)(unsigned int, const Percent &, const std::vector<Temperature> &, const std::vector<double> &, double, double, const Temperature &)>(&SkyStatus::WaterVaporRetrieval_fromTEBB), py::arg("spwId"), py::arg("signalGain"), py::arg("v_tebb"), py::arg("spwId_filter"), py::arg("airmass"), py::arg("skycoupling"), py::arg("tspill"), "");
  cls_SkyStatus.def("WaterVaporRetrieval_fromTEBB", static_cast<Length (SkyStatus::*)(const std::vector<unsigned int> &, const Percent &, const std::vector<Temperature> &, const std::vector<std::vector<double>> &, double, double, const Temperature &)>(&SkyStatus::WaterVaporRetrieval_fromTEBB), py::arg("spwId"), py::arg("signalGain"), py::arg("v_tebb"), py::arg("spwId_filters"), py::arg("airmass"), py::arg("skycoupling"), py::arg("tspill"), "");
  cls_SkyStatus.def("WaterVaporRetrieval_fromTEBB", static_cast<Length (SkyStatus::*)(const std::vector<unsigned int> &, const Percent &, const std::vector<Temperature> &, double, double, const Temperature &)>(&SkyStatus::WaterVaporRetrieval_fromTEBB), py::arg("spwId"), py::arg("signalGain"), py::arg("v_tebb"), py::arg("airmass"), py::arg("skycoupling"), py::arg("tspill"), "");
  cls_SkyStatus.def("WaterVaporRetrieval_fromTEBB", static_cast<Length (SkyStatus::*)(unsigned int, const std::vector<Temperature> &, double, double, const Temperature &)>(&SkyStatus::WaterVaporRetrieval_fromTEBB), py::arg("spwId"), py::arg("v_tebb"), py::arg("airmass"), py::arg("skycoupling"), py::arg("tspill"), "");
  cls_SkyStatus.def("WaterVaporRetrieval_fromTEBB", static_cast<Length (SkyStatus::*)(unsigned int, const std::vector<Temperature> &, const std::vector<double> &, double, double, const Temperature &)>(&SkyStatus::WaterVaporRetrieval_fromTEBB), py::arg("spwId"), py::arg("v_tebb"), py::arg("spwId_filter"), py::arg("airmass"), py::arg("skycoupling"), py::arg("tspill"), "");
  cls_SkyStatus.def("WaterVaporRetrieval_fromTEBB", static_cast<Length (SkyStatus::*)(unsigned int, const Percent &, const std::vector<Temperature> &, double, double, const Temperature &)>(&SkyStatus::WaterVaporRetrieval_fromTEBB), py::arg("spwId"), py::arg("signalGain"), py::arg("v_tebb"), py::arg("airmass"), py::arg("skycoupling"), py::arg("tspill"), "");
  cls_SkyStatus.def("WaterVaporRetrieval_fromTEBB", static_cast<Length (SkyStatus::*)(unsigned int, const Percent &, const Temperature &, double, double, const Temperature &)>(&SkyStatus::WaterVaporRetrieval_fromTEBB), py::arg("spwId"), py::arg("signalGain"), py::arg("tebb"), py::arg("airmass"), py::arg("skycoupling"), py::arg("tspill"), "");
  cls_SkyStatus.def("SkyCouplingRetrieval_fromTEBB", static_cast<double (SkyStatus::*)(unsigned int, const std::vector<Temperature> &, double, double, const Temperature &)>(&SkyStatus::SkyCouplingRetrieval_fromTEBB), py::arg("spwId"), py::arg("v_tebb"), py::arg("airmass"), py::arg("skycoupling"), py::arg("tspill"), "");
  cls_SkyStatus.def("SkyCouplingRetrieval_fromTEBB", static_cast<double (SkyStatus::*)(unsigned int, const std::vector<Temperature> &, const std::vector<double> &, double, double, const Temperature &)>(&SkyStatus::SkyCouplingRetrieval_fromTEBB), py::arg("spwId"), py::arg("v_tebb"), py::arg("spwId_filter"), py::arg("airmass"), py::arg("skycoupling"), py::arg("tspill"), "");
  cls_SkyStatus.def("getSigmaFit", static_cast<Temperature (SkyStatus::*)(unsigned int, const std::vector<Temperature> &, double, double, const Temperature &)>(&SkyStatus::getSigmaFit), py::arg("spwId"), py::arg("v_tebbspec"), py::arg("airmass"), py::arg("skyCoupling"), py::arg("Tspill"), "");
  cls_SkyStatus.def("getSigmaFit", static_cast<Temperature (SkyStatus::*)(unsigned int, const std::vector<Temperature> &, const Length &, double, double, const Temperature &)>(&SkyStatus::getSigmaFit), py::arg("spwId"), py::arg("v_tebbspec"), py::arg("wh2o"), py::arg("airmass"), py::arg("skyCoupling"), py::arg("Tspill"), "");
  cls_SkyStatus.def("getAverageTebbSky", static_cast<Temperature (SkyStatus::*)(unsigned int, const Length &, double, double, double, const Temperature &)>(&SkyStatus::getAverageTebbSky), py::arg("spwid"), py::arg("wh2o"), py::arg("airmass"), py::arg("skycoupling"), py::arg("signalgain"), py::arg("Tspill"), "");
  cls_SkyStatus.def("getAverageTrjSky", static_cast<Temperature (SkyStatus::*)(unsigned int, const Length &, double, double, double, const Temperature &)>(&SkyStatus::getAverageTrjSky), py::arg("spwid"), py::arg("wh2o"), py::arg("airmass"), py::arg("skycoupling"), py::arg("signalgain"), py::arg("Tspill"), "");

  m.def("getVersion", static_cast<std::string (*)()>(&getVersion), "");
  m.def("getTag", static_cast<std::string (*)()>(&getTag), "");
  m.def("getALMARelease", static_cast<std::string (*)()>(&getALMARelease), "");
}
