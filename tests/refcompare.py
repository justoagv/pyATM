"""Compare the output of a Python port of an ATM C++ unit test with the TelCal reference output.

The C++ tests under TelCalResults/Libraries/ATM/test are run by TAT, which prefixes each output
line with ``"<n> - "``, applies ``TestList.sed`` and drops the lines matching ``TestList.grep``.
The reference files are copied to ``tests/atm/ref`` by ``tools/sync_from_telcal.sh``.

The comparison is done on the sequence of numbers found in the output: same count, and each
value equal to the reference within ``rtol`` or within the printed precision of the reference.
"""
from __future__ import annotations

import math
import re
from pathlib import Path

ATM_DIR = Path(__file__).parent / "atm"
DATA_DIR = ATM_DIR / "data"
REF_DIR = ATM_DIR / "ref"

_PREFIX = re.compile(r"^\d+ - ")
_NUMBER = re.compile(r"(?<![\w.])[-+]?(?:\d+\.?\d*|\.\d+)(?:[eE][-+]?\d+)?(?![\d.])")
_GREP = ("ground pressure has changed", "ground temperature has changed", "tropo lapse rate has changed")
_SED = (re.compile(r"version: [0-9].[0-9].[0-9]"), "version: x.y.z")


def cformat(x: float, precision: int = 6) -> str:
    """Format a double like ``std::cout << x`` (default stream: %g with 6 significant digits)."""
    if isinstance(x, (int,)) and not isinstance(x, bool):
        return str(x)
    if math.isnan(x):
        return "-nan" if math.copysign(1.0, x) < 0 else "nan"
    if math.isinf(x):
        return "-inf" if x < 0 else "inf"
    return f"{x:.{precision}g}"


def filter_lines(lines: list[str]) -> list[str]:
    """Apply the TAT TestList.grep / TestList.sed filters."""
    out = []
    for line in lines:
        if any(g in line for g in _GREP):
            continue
        out.append(_SED[0].sub(_SED[1], line))
    return out


def load_ref(name: str) -> list[str]:
    """Reference output lines (TAT prefix removed, license header and test name line skipped)."""
    lines = (REF_DIR / f"{name}.ref").read_text(errors="replace").splitlines()
    body = []
    started = False
    for line in lines:
        if not started:
            if line.startswith("#") or not line.strip():
                continue
            started = True
            if line.strip().split()[0] in (name, name.replace("Test", "")) and not _PREFIX.match(line):
                continue
        body.append(_PREFIX.sub("", line, count=1))
    return body


def _tolerance(token: str, rtol: float) -> float:
    """Allowed difference: rtol relative, or 1 unit of the last printed digit of the reference."""
    value = float(token)
    mantissa, _, exponent = token.lower().partition("e")
    decimals = len(mantissa.split(".")[1]) if "." in mantissa else 0
    last_digit = 10.0 ** (-decimals + (int(exponent) if exponent else 0))
    return max(rtol * abs(value), 1.01 * last_digit)


def numbers(lines: list[str]) -> list[tuple[int, str]]:
    return [(i, m.group(0)) for i, line in enumerate(lines) for m in _NUMBER.finditer(line)]


def assert_matches_ref(lines: list[str], name: str, rtol: float = 1e-6) -> None:
    """Assert that the numbers in ``lines`` match those of the reference output ``name``.ref."""
    ref_lines = filter_lines(load_ref(name))
    out_lines = filter_lines([sub for line in lines for sub in line.split("\n")])
    ref_nums, out_nums = numbers(ref_lines), numbers(out_lines)
    for k, ((ri, rtok), (oi, otok)) in enumerate(zip(ref_nums, out_nums)):
        tol = _tolerance(rtok, rtol)
        if not abs(float(otok) - float(rtok)) <= tol:
            raise AssertionError(
                f"{name}: number #{k} differs: got {otok} expected {rtok} (tol {tol:g})\n"
                f"  output line {oi}: {out_lines[oi]!r}\n  ref    line {ri}: {ref_lines[ri]!r}")
    if len(ref_nums) != len(out_nums):
        n = min(len(ref_nums), len(out_nums))
        ri = ref_nums[n][0] if n < len(ref_nums) else len(ref_lines) - 1
        oi = out_nums[n][0] if n < len(out_nums) else len(out_lines) - 1
        raise AssertionError(
            f"{name}: {len(out_nums)} numbers in output, {len(ref_nums)} in reference; first extra at\n"
            f"  output line {oi}: {out_lines[oi] if out_lines else ''!r}\n"
            f"  ref    line {ri}: {ref_lines[ri] if ref_lines else ''!r}")
