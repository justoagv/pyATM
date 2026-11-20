"""The wheel ships the ATM C++ headers and library: compile C++ code against them."""
import os
import shlex
import shutil
import subprocess
import sys
from pathlib import Path

import pytest

import pyatm
from pyatm import config

CXX = shutil.which(os.environ.get("CXX", "c++"))
NS = "telcal::atm" if pyatm.CXX_NAMESPACE == "telcal::atm" else "atm"

SOURCE = f"""
#include <iostream>
#include "ATMSkyStatus.h"
#include "ATMVersion.h"
using namespace {NS};
int main()
{{
  AtmProfile profile(Length(5000, "m"), Pressure(560, "mb"), Temperature(270, "K"), -5.6,
                     Humidity(20, "%"), Length(2, "km"), 1);
  SpectralGrid grid(Frequency(230, "GHz"));
  RefractiveIndexProfile rip(grid, profile);
  SkyStatus sky(rip);
  std::cout.precision(15);
  std::cout << getVersion() << " " << profile.getNumLayer() << " " << sky.getTebbSky().get("K") << std::endl;
  return 0;
}}
"""


def python_result():
    profile = pyatm.AtmProfile(pyatm.Length(5000, "m"), pyatm.Pressure(560, "mb"), pyatm.Temperature(270, "K"),
                               -5.6, pyatm.Humidity(20, "%"), pyatm.Length(2, "km"), 1)
    sky = pyatm.SkyStatus(pyatm.RefractiveIndexProfile(pyatm.SpectralGrid(pyatm.Frequency(230, "GHz")), profile))
    return pyatm.getVersion(), profile.getNumLayer(), sky.getTebbSky().get("K")


def check_output(exe: Path):
    version, nlayers, tebb = subprocess.run([str(exe)], check=True, capture_output=True, text=True).stdout.split()
    py_version, py_nlayers, py_tebb = python_result()
    assert version == py_version
    assert int(nlayers) == py_nlayers
    assert float(tebb) == pytest.approx(py_tebb, rel=1e-12)


def test_compile_with_pyatm_config(tmp_path):
    src = tmp_path / "main.cpp"
    src.write_text(SOURCE)
    exe = tmp_path / "main"
    cmd = [CXX, "-std=c++17", str(src), "-o", str(exe), *shlex.split(config.get_cflags()),
           *shlex.split(config.get_libs())]
    subprocess.run(cmd, check=True)
    check_output(exe)


def test_pyatm_config_cli():
    exe = Path(sys.executable).with_name("pyatm-config")
    out = subprocess.run([str(exe), "--cflags", "--libs"], check=True, capture_output=True, text=True).stdout
    assert f"-I{config.get_include()}" in out and "-lATM" in out
    assert ("-DALMA_TELCAL" in out) == (pyatm.CXX_NAMESPACE == "telcal::atm")
    assert (Path(config.get_include()) / "ATMSkyStatus.h").is_file()
    assert (Path(config.get_cmake_dir()) / "pyatmConfig.cmake").is_file()
    assert (Path(config.get_pkgconfig_dir()) / "pyatm.pc").is_file()


def test_compile_with_cmake(tmp_path):
    cmake = shutil.which("cmake", path=f"{Path(sys.executable).parent}{os.pathsep}{os.environ.get('PATH', '')}")
    (tmp_path / "main.cpp").write_text(SOURCE)
    (tmp_path / "CMakeLists.txt").write_text(
        "cmake_minimum_required(VERSION 3.15)\nproject(atmtest CXX)\nset(CMAKE_CXX_STANDARD 17)\n"
        "find_package(pyatm REQUIRED CONFIG)\nadd_executable(main main.cpp)\n"
        "target_link_libraries(main PRIVATE pyatm::ATM)\n")
    build = tmp_path / "build"
    subprocess.run([cmake, "-S", str(tmp_path), "-B", str(build), f"-Dpyatm_DIR={config.get_cmake_dir()}",
                    f"-DCMAKE_CXX_COMPILER={CXX}"], check=True)
    subprocess.run([cmake, "--build", str(build)], check=True)
    check_output(build / "main")
