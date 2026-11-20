"""Python port of TelCalResults/Libraries/ATM/test/SpectralGridTest.cpp."""
import os
import sys
import tempfile

import pyatm
from pyatm import Frequency, SpectralGrid
from refcompare import assert_matches_ref, cformat as f


def cpp_stdout(out, fn, *args):
    """Call ``fn(*args)`` capturing what the C++ library writes to std::cout (fd 1) into ``out``."""
    sys.stdout.flush()
    saved = os.dup(1)
    with tempfile.TemporaryFile(mode="w+b") as tmp:
        os.dup2(tmp.fileno(), 1)
        try:
            result = fn(*args)
        finally:
            os.dup2(saved, 1)
            os.close(saved)
        tmp.seek(0)
        out.extend(tmp.read().decode(errors="replace").splitlines())
    return result


def run() -> list[str]:
    out = []
    T = " SpectralGridTest:"
    numChan = 64
    refChan = 32

    myRefFreq = Frequency(90.0, "GHz")
    myChanSep = Frequency(0.01, "GHz")

    out.append(f"{T} Test 1:")
    out.append(f"{T} Create a pointer with first element construted with SpectralGrid(usigned int numChan, "
               "unsigned int refChan, Frequency refFreq, Frequency chanSep):")
    sgPtr1 = SpectralGrid(numChan, refChan, myRefFreq, myChanSep)
    out.append(f"{T} Number of channels retrieved:  {sgPtr1.getNumChan()} (Value entered to constructor:{numChan})")
    out.append(f"{T} Reference frequency retrieved: {f(sgPtr1.getRefFreq().get())} Hz; "
               f"{T}  Input:{f(myRefFreq.get('GHz'))} GHz")
    out.append(f"{T} Reference frequency retrieved: {f(sgPtr1.getRefFreq().get('GHz'))}GHz "
               f"{T} Input:{f(myRefFreq.get('GHz'))} GHz")
    out.append(f"{T} Reference channel retrieved:   {sgPtr1.getRefChan()} (Value entered to constructor:{refChan})")
    out.append(f"{T} Channel separation retrieved:  {f(sgPtr1.getChanSep().get())} Hz; "
               f"{T} Input:{f(myChanSep.get('GHz'))} GHz")
    out.append(f"{T} Channel separation retrieved:  {f(sgPtr1.getChanSep().get('kHz'))} kHz "
               f"{T} Input:{f(myChanSep.get('GHz'))} GHz")
    out.append(f"{T} Number of spectral windows: {sgPtr1.getNumSpectralWindow()}")
    out.append(f"{T} Number of channels for spectral window identifier 0: {sgPtr1.getNumChan(0)}")
    res = cpp_stdout(out, sgPtr1.getNumChan, 1)
    out.append(f"{T} Number of channels for spectral window identifier 1: {res}")
    if sgPtr1.isRegular(0):
        out.append(f"{T} the first spectral window is regularily sampled")
    else:
        out.append(f"{T} the first spectral window is not regularily sampled")
    if len(sgPtr1.getAssocSpwId(0)) == 0:
        out.append(f"{T} First spectral window has no associated spectral windows")
    else:
        out.append(f"{T} First spectral window has associated spectral windows ")
    out.append(f"{T} End of Test 1")
    out.append("    ")

    out.append(f"{T} Test 2")
    out.append(f"{T} New spectral window using add(unsigned int numChan, unsigned int refChan, "
               "Frequency refFreq, Frequency chanSep):")
    numChan1 = 128
    refChan1 = 32
    myNewRefFreq = Frequency(215.0, "GHz")
    myNewChanSep = Frequency(0.02, "GHz")
    spwId = sgPtr1.add(numChan1, refChan1, myNewRefFreq, myNewChanSep)
    out.append(f"{T} A new spectral window has been appended and got the identifier number:{spwId}")
    out.append(f"{T} Number of spectral windows: {sgPtr1.getNumSpectralWindow()}")

    for spwId in (0, 1):
        out.append(f"{T} Number of channels retrieved for spwId {spwId}: {sgPtr1.getNumChan(spwId)}")
        out.append(f"{T} Reference frequency retrieved: {f(sgPtr1.getRefFreq(spwId).get('GHz'))} GHz")
        out.append(f"{T} Channel separation retrieved:  {f(sgPtr1.getChanSep(spwId).get('GHz'))} GHz GHz")
    spwId = 1

    if sgPtr1.isRegular(spwId):
        out.append(f"{T} the spectral window with id {spwId} is regularily sampled")
    else:
        out.append(f"{T} the spectral window with id {spwId} is not regularily sampled")

    out.append(f"{T} Number of spectral windows: {sgPtr1.getNumSpectralWindow()}")

    if len(sgPtr1.getSideband(spwId)) == 0:
        out.append(f"{T} As expected this spectral window with spwid={spwId} has no sideband specification")
    id_ = 10
    if len(cpp_stdout(out, sgPtr1.getSideband, id_)) == 0:
        out.append(f"{T} Spectral window with id={id_} does not exist!")
    out.append(f"{T} End of Test 2")

    out.append(f"{T} Channel frequency and number for the first spectral window: ")
    chanFreq = []
    for i in range(sgPtr1.getNumChan()):
        chanFreq.append(sgPtr1.getChanFreq(i).get())
        out.append(f"SpectralGridTest: {i} channel: {i - refChan + 1} freq: {f(chanFreq[i])}")
    chFreq = list(chanFreq)
    out.append("")

    del sgPtr1

    refFreq = 90.0e9

    out.append(f"{T} Test 2:")
    out.append(f"{T} Build using SpectralGrid( unsigned int numChan, unsigned int refChan, double* chFreq, "
               "string units):")
    sgPtr2 = SpectralGrid(numChan, refChan, chFreq, Frequency.UnitHertz)
    out.append(f"{T} Number of channels retrieved: {sgPtr2.getNumChan()}    Input:  {numChan}")
    out.append(f"{T} Reference frequency retrieved:{f(sgPtr2.getRefFreq().get())}Hz  Initial: none")
    out.append(f"{T} Reference frequency retrieved:{f(sgPtr2.getRefFreq().get('MHz'))}MHz Initial: none")
    out.append(f"{T} Reference channel retrieved:  {sgPtr2.getRefChan()}    Input:  {refChan}")
    out.append(f"{T} Channel separation retrieved: {f(sgPtr2.getChanSep().get())}Hz  Initial: none")
    out.append(f"{T} Channel separation retrieved: {f(sgPtr2.getChanSep().get('MHz'))}MHz Initial: none")
    if sgPtr2.isRegular():
        out.append(f"{T} the first spectral window with id 0 is regularily sampled")
    else:
        out.append(f"{T} the first spectral window with id 0 is not regularily sampled")
    chFreq[sgPtr2.getNumChan() // 4] = chFreq[sgPtr2.getNumChan() // 4] + 1.0
    out.append(f"{T} Add a second irregular spectral window using add( unsigned int numChan, "
               "unsigned int refChan, double* chFreq, string units):")
    sgPtr2.add(numChan, refChan, chFreq, Frequency.UnitHertz)
    if sgPtr2.isRegular():
        out.append(f"{T} the first spectral window with id 0 is regularily sampled as expected")
    else:
        out.append(f"{T} the first spectral window with id 0 is not regularily sampled ==> ERROR in the code")
    if sgPtr2.isRegular(spwId):
        out.append(f"{T} the spectral window with id {spwId} is regularily sampled ==> ERROR in the code")
    else:
        out.append(f"{T} the spectral window with id {spwId} is not regularily sampled as expected")
    del sgPtr2

    out.append("")
    out.append("")

    out.append(f"{T} Test 3:")
    out.append(f"{T} Build using SpectralGrid( unsigned int numChan, double refFreq, double* chFreq, "
               "string freqUnits):")
    sgPtr3 = SpectralGrid(numChan, refFreq, chFreq, Frequency.UnitHertz)
    out.append(f"{T} Number of channels retrieved: {sgPtr3.getNumChan()} Input: {numChan}")
    out.append(f"{T} Reference frequency retrieved:{f(sgPtr3.getRefFreq().get())}Hz  Initial:{f(refFreq)}Hz")
    out.append(f"{T} Reference frequency retrieved:{f(sgPtr3.getRefFreq().get('MHz'))}MHz Initial:{f(refFreq)}Hz")
    out.append(f"{T} Reference channel retrieved:  {sgPtr3.getRefChan()} Initial: {refChan}")
    out.append(f"{T} Channel separation retrieved: {f(sgPtr3.getChanSep().get())} Initial: none")

    chan = 16.123456
    out.append(f"{T} Position (GU) retrieved: "
               f"{f(sgPtr3.getChanNum(refFreq + sgPtr3.getChanSep().get() * chan))}"
               f"{T}  Exact: {f(chan)}")
    out.append(f"{T} Total bandwidth retrieved: {f(sgPtr3.getBandwidth().get())}"
               f"{T} Initial: {f(sgPtr3.getChanSep().get() * (numChan - 1))}")
    out.append(f"{T} Frequency range: from {f(sgPtr3.getMinFreq().get())} to {f(sgPtr3.getMaxFreq().get())}Hz")
    out.append(f"{T} Frequency range: from {f(sgPtr3.getMinFreq().get('GHz'))} to "
               f"{f(sgPtr3.getMaxFreq().get('GHz'))}GHz")
    del sgPtr3

    out.append("")
    out.append("")

    numChan = 128
    refChan = 64
    refFreq2 = Frequency(215.0, "GHz")
    chanSep2 = Frequency(0.02, "GHz")
    intermediateFreq = Frequency(2.0, "GHz")
    bandWidth = Frequency(1.0, "GHz")  # noqa: F841  (unused, as in the C++ test)

    sgPtr1 = SpectralGrid(numChan, refChan, refFreq2, chanSep2, intermediateFreq, pyatm.LSB, pyatm.SSB)

    out.append(f"{T} Number of spectral windows:            {sgPtr1.getNumSpectralWindow()} Expected: 2")

    for spwId in range(sgPtr1.getNumSpectralWindow()):
        out.append(f"{T} Sideband:                              {sgPtr1.getSideband(spwId)}")
        out.append(f"{T} LO frequency:                          {f(sgPtr1.getLoFrequency(spwId))}Hz ")
        out.append(f"{T} Number of channels retrieved:          {sgPtr1.getNumChan(spwId)} for spwId {spwId}: "
                   f" Input:{numChan}")
        out.append(f"{T} Reference frequency retrieved:         {f(sgPtr1.getRefFreq(spwId).get())}"
                   f"  Input:{f(refFreq2.get('GHz'))}GHz")
        out.append(f"{T} Reference frequency retrieved:         {f(sgPtr1.getRefFreq(spwId).get('GHz'))}GHz "
                   f" Input:{f(refFreq2.get('GHz'))}GHz")
        out.append(f"{T} Reference channel retrieved:           {sgPtr1.getRefChan()} Input:{refChan}")
        out.append(f"{T} Channel separation retrieved:          {f(sgPtr1.getChanSep(spwId).get())}Hz "
                   f" Input: |{f(chanSep2.get('GHz'))}| GHz")
        out.append(f"{T} Channel separation retrieved:          {f(sgPtr1.getChanSep(spwId).get('kHz'))}kHz "
                   f" Input: |{f(chanSep2.get('GHz'))}| GHz")
        out.append(f"{T} minFreq:                               {f(sgPtr1.getMinFreq(spwId).get('GHz'))} GHz")
        out.append(f"{T} maxFreq:                               {f(sgPtr1.getMaxFreq(spwId).get('GHz'))} GHz")
        out.append(f"{T} Channel (grid units) for the min:      "
                   f"{f(sgPtr1.getChanNum(spwId, sgPtr1.getMinFreq(spwId).get()))}")
        out.append(f"{T} Channel (grid units) for the max:      "
                   f"{f(sgPtr1.getChanNum(spwId, sgPtr1.getMaxFreq(spwId).get()))}")

        if sgPtr1.isRegular(spwId):
            out.append(f"{T} the spectral window with id {spwId} is regularily sampled")
        else:
            out.append(f"{T} the spectral window with id {spwId} is not regularily sampled")

        if len(sgPtr1.getAssocSpwId(spwId)) == 0:
            out.append(f"{T} the spectral window with id {spwId} has no associated spectral window")
        else:
            for n in range(len(sgPtr1.getAssocSpwId(spwId))):
                assocSpwId = sgPtr1.getAssocSpwId(spwId)[n]
                out.append(f"{T} the spectral window with id {spwId} has the associated spec. win. with id "
                           f"{assocSpwId} ({sgPtr1.getAssocNature(spwId)[n]})")
                for i in range(sgPtr1.getNumChan(spwId)):
                    out.append(f"{T} chan index:{i} {sgPtr1.getSideband(spwId)} "
                               f"{f(sgPtr1.getChanFreq(spwId, i).get('GHz'))}GHz  "
                               f"{sgPtr1.getAssocNature(spwId)[n]} "
                               f"{f(sgPtr1.getChanFreq(assocSpwId, i).get('GHz'))}GHz")
        out.append("")

    out.append(f"{T} TESTBED done")
    return out


def test_SpectralGridTest():
    assert_matches_ref(run(), "SpectralGridTest")
