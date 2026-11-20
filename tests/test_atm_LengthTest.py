"""Python port of TelCalResults/Libraries/ATM/test/LengthTest.cpp."""
import pyatm
from pyatm import Length
from refcompare import assert_matches_ref, cformat as f


def run() -> list[str]:
    out = []
    longueur = Length(10)
    out.append(f"longueur={f(longueur.get('km'))}km")
    out.append(f"longueur={f(longueur.get())}m")

    h, dh = Length(10, "km"), Length(10, "m")
    out.append(f(h.get() + dh.get()))
    hsum = h + dh
    out.append(f(hsum.get()))
    out.append(f"{f(hsum.get('KM'))}KM")
    out.append(f"{f(hsum.get('km'))}km")
    z = Length(20)
    dz = Length(20, "mm")
    hdif = z - dz
    out.append(f"{f(hdif.get())} SI units")
    out.append(f"{f(hdif.get('mm'))}mm")

    scf = 3
    hscaled = h * scf
    out.append(f"{f(h.get('km'))}km * {scf} = {f(hscaled.get())}m")

    P = Length(10)
    out.append(f"Length P(10) ==> P={f(P.get())}")
    p = Length(P)
    out.append(f"Length p=P; ==> p={f(p.get())}")
    out.append("Test for the relational operators:")
    if p >= P:
        out.append("p>=P")
    if p <= P:
        out.append("p<=P")
    if p == P:
        out.append("p==P")
    out.append("Arithmetic operations:")
    p = P + p
    out.append(f"p=P+p ==> p={f(p.get())}")
    out.append(f"P={f(P.get())} must not change of value!")
    p = p + P
    out.append(f"p=p+P ==> p={f(p.get())}")
    out.append(f"P={f(P.get())} must not change of value!")
    out.append("Let declare p0 be of type Length using the default constructor: Length p0;")
    p0 = p + P
    out.append(f"p0 = p+P with p={f(p.get())} and P={f(P.get())} ==> p0=p+P={f(p0.get())}")
    p1 = Length()
    out.append("Let declare p0 be of type Length using the default constructor: Length p1;")
    out.append(f"With no assignement its value must be 0: p1={f(p1.get())}")
    if P < p:
        out.append("Test relational operator P>p: OK")
    if p != P:
        out.append("Test relational operator p!=P: OK")
    if p < P:
        out.append("p<P")
    out.append("Some more tests for arithmetic expressions ")
    p1 = Length(P)
    out.append(f"Assign the value of P to p1: p1=P ==> p1={f(p1.get())}")
    p1 = p1 + p + P
    out.append(f"Arithmetic sum: p1+p+P={f(p1.get())}")
    p1 = p1 - p - P
    out.append(f"Arithmetic difference: p1-p-P={f(p1.get())}")
    p1 = p1 * 2.0
    out.append(f"Product by a scalar p1=p1*2.0={f(p1.get('mm'))}mm")
    out.append(f"p0={f(p0.get())}")
    p1 = p0 * 2.0
    out.append(f"p1=p0*2.0={f(p1.get('mm'))}mm")
    out.append("-" * 74)
    out.append("| Note that the commutativity of the oprator * has not been implemented! |")
    out.append("-" * 74)
    out.append(f"p0={f(p0.get())} must have not changed of value")
    out.append(f"p1={f(p1.get())}")
    p1 = p1 / 2.0e0
    out.append(f"p1=p1/2.0={f(p1.get('mm'))}mm")
    p1 = p0 / 2.0
    out.append(f"p1=p0/2.0={f(p1.get('mm'))}mm")
    out.append("-" * 71)
    out.append("| Note that dividing by a physical quantity has not been implemented! |")
    out.append("-" * 71)
    out.append("")
    out.append("Some more tests for arithmetic expressions ")
    out.append(f"p0={f(p0.get())}  must have not changed of value")
    out.append(f"P={f(P.get())}")
    p1 = p0 * 2.0e0 + P
    out.append(f"p1=p0*2.0E0+P={f(p1.get())}")
    out.append("")
    out.append("TESTBED done ")
    return out


def test_LengthTest():
    assert_matches_ref(run(), "LengthTest")


def test_LengthTest_units():
    assert pyatm.Length(1, "km").get("m") == 1000.0
