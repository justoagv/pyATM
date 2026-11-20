cmake_minimum_required(VERSION 3.18)

file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/cpp/ATM/ATM_VERSION" _atm_version_line LIMIT_COUNT 1)
string(REGEX MATCH "^[0-9]+\\.[0-9]+\\.[0-9]+" ATM_VERSION "${_atm_version_line}")

project(pyatm VERSION ${ATM_VERSION} LANGUAGES CXX)

# C++ namespace of the ATM library:
#   telcal -> telcal::atm (compiled with -DALMA_TELCAL, as in TelCal)
#   atm    -> atm         (as in CASA)
set(PYATM_NAMESPACE "telcal" CACHE STRING "C++ namespace of ATM: telcal (telcal::atm) or atm")
set_property(CACHE PYATM_NAMESPACE PROPERTY STRINGS telcal atm)
if(NOT PYATM_NAMESPACE MATCHES "^(telcal|atm)$")
  message(FATAL_ERROR "PYATM_NAMESPACE must be 'telcal' or 'atm' (got '${PYATM_NAMESPACE}')")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release)
endif()

# Install layout inside the Python package (wheel): pyatm/{include,lib,lib/cmake/pyatm,lib/pkgconfig}
if(SKBUILD)
  set(PYATM_INSTALL_DIR "${SKBUILD_PROJECT_NAME}")
else()
  set(PYATM_INSTALL_DIR "pyatm")
endif()
set(PYATM_INCLUDE_DIR "${PYATM_INSTALL_DIR}/include")
set(PYATM_LIB_DIR "${PYATM_INSTALL_DIR}/lib")
set(PYATM_CMAKE_DIR "${PYATM_LIB_DIR}/cmake/pyatm")

# ----------------------------------------------------------------------------- C++ library
set(ATM_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cpp/ATM")
file(GLOB ATM_SOURCES CONFIGURE_DEPENDS "${ATM_DIR}/src/*.cpp")
file(GLOB ATM_HEADERS CONFIGURE_DEPENDS "${ATM_DIR}/include/*.h")

add_library(ATM SHARED ${ATM_SOURCES})
add_library(pyatm::ATM ALIAS ATM)
target_include_directories(ATM PUBLIC
  $<BUILD_INTERFACE:${ATM_DIR}/include>
  $<INSTALL_INTERFACE:${PYATM_INCLUDE_DIR}>)
if(PYATM_NAMESPACE STREQUAL "telcal")
  target_compile_definitions(ATM PUBLIC ALMA_TELCAL)
  set(PYATM_CXX_NAMESPACE "telcal::atm")
  set(PYATM_CFLAGS_NAMESPACE "-DALMA_TELCAL")
else()
  set(PYATM_CXX_NAMESPACE "atm")
  set(PYATM_CFLAGS_NAMESPACE "")
endif()
target_compile_features(ATM PUBLIC cxx_std_17)
set_target_properties(ATM PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
  EXPORT_NAME ATM)

# ----------------------------------------------------------------------------- Python module
find_package(Python REQUIRED COMPONENTS Interpreter Development.Module)
find_package(pybind11 CONFIG REQUIRED)

pybind11_add_module(_atm
  src/bindings/atm_module.cpp
  src/bindings/atm_generated.cpp)
target_include_directories(_atm PRIVATE src/bindings)
target_link_libraries(_atm PRIVATE ATM)
# The library is shipped next to the extension module, in pyatm/lib
set_target_properties(_atm PROPERTIES INSTALL_RPATH "$ORIGIN/lib")

# ----------------------------------------------------------------------------- install
install(TARGETS ATM EXPORT pyatmTargets
  LIBRARY DESTINATION ${PYATM_LIB_DIR}
  ARCHIVE DESTINATION ${PYATM_LIB_DIR}
  RUNTIME DESTINATION ${PYATM_LIB_DIR})
install(FILES ${ATM_HEADERS} DESTINATION ${PYATM_INCLUDE_DIR})
install(TARGETS _atm LIBRARY DESTINATION ${PYATM_INSTALL_DIR})

install(EXPORT pyatmTargets NAMESPACE pyatm:: DESTINATION ${PYATM_CMAKE_DIR})
include(CMakePackageConfigHelpers)
configure_package_config_file(cmake/pyatmConfig.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/pyatmConfig.cmake"
  INSTALL_DESTINATION ${PYATM_CMAKE_DIR})
write_basic_package_version_file("${CMAKE_CURRENT_BINARY_DIR}/pyatmConfigVersion.cmake"
  COMPATIBILITY SameMajorVersion)
install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/pyatmConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/pyatmConfigVersion.cmake"
  DESTINATION ${PYATM_CMAKE_DIR})

configure_file(cmake/pyatm.pc.in "${CMAKE_CURRENT_BINARY_DIR}/pyatm.pc" @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/pyatm.pc" DESTINATION "${PYATM_LIB_DIR}/pkgconfig")

file(READ "${ATM_DIR}/TELCAL_SOURCE" PYATM_TELCAL_SOURCE)
string(STRIP "${PYATM_TELCAL_SOURCE}" PYATM_TELCAL_SOURCE)
configure_file(cmake/_build_info.py.in "${CMAKE_CURRENT_BINARY_DIR}/_build_info.py" @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/_build_info.py" DESTINATION ${PYATM_INSTALL_DIR})
