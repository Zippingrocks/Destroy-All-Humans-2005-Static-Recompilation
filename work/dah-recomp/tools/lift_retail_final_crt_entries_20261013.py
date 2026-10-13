"""Audit the final five generated CRT recovery entries against retail bytes.

The addresses are internal control-flow labels rather than recovered symbols.
Only the retail XBE is accepted as behavior evidence.
"""
import argparse
import hashlib
import json
from pathlib import Path
import re
import sys

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT / "third_party" / "xboxrecomp"))
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from tools.recomp.config import configure_from_xbe, va_to_file_offset

RANGES = (
    (0x0013FBDC, 0x0013FC0B, "nonlocal x87 domain-result tail"),
    (0x0013F420, 0x0013F427, "shared x87 zero-result tail"),
    (0x0014237F, 0x001424C5, "descriptor scan/allocation continuation CFG"),
)
ENTRIES = (0x0013FBDC, 0x00142434, 0x00142450, 0x0014245C, 0x001424B3)
ENTRY_PREFIXES = {
    0x0013FBDC: "58d9e49bddbd60ffffff9b",
    0x00142434: "830eff8bc62b04bd207c2800996a2859f7f9",
    0x00142450: "837de4ff755d47e923ffffff",
    0x0014245C: "be0005000056e88ca7ffff598945e085c07444",
    0x001424B3: "834dfcffe8090000008b45e4",
}


def file_bytes(data: bytes, address: int, size: int) -> bytes:
    offset = va_to_file_offset(address)
    return data[offset:offset + size]


def generate() -> str:
    xbe = ROOT / "work/default.xbe"
    source_path = ROOT / "work/dah-recomp/src/recomp/gen/recomp_retail_final_crt_entries_20261013.c"
    unresolved_path = ROOT / "work/dah-recomp/src/recomp/gen/recomp_stubs_unresolved.c"
    data = xbe.read_bytes()
    source = source_path.read_text(encoding="utf-8")
    unresolved = unresolved_path.read_text(encoding="utf-8")
    configure_from_xbe(str(xbe))
    md = Cs(CS_ARCH_X86, CS_MODE_32)

    ranges = []
    for start, end, purpose in RANGES:
        raw = file_bytes(data, start, end - start)
        instructions = list(md.disasm(raw, start))
        if sum(i.size for i in instructions) != len(raw):
            raise SystemExit(f"FAIL retail disassembly gap at 0x{start:08X}")
        ranges.append({
            "start": f"0x{start:08X}",
            "endExclusive": f"0x{end:08X}",
            "bytes": len(raw),
            "instructions": len(instructions),
            "sha256": hashlib.sha256(raw).hexdigest(),
            "purpose": purpose,
        })

    for address, expected in ENTRY_PREFIXES.items():
        actual = file_bytes(data, address, len(expected) // 2).hex()
        if actual != expected:
            raise SystemExit(
                f"FAIL retail entry drift at 0x{address:08X}: {actual} != {expected}"
            )
        symbol = f"sub_{address:08X}"
        if not re.search(rf"\bvoid\s+{symbol}\s*\(", source):
            raise SystemExit(f"FAIL missing restored body: {symbol}")
        if re.search(rf"\bvoid\s+{symbol}\s*\(", unresolved):
            raise SystemExit(f"FAIL restored body remains a recovery stub: {symbol}")

    infinity = file_bytes(data, 0x00259BFC, 10)
    if infinity.hex() != "0000000000000080ff7f":
        raise SystemExit("FAIL retail x87 infinity constant drift")

    record = {
        "schema": 1,
        "source": "retail-xbe-only",
        "retailXbeSha256": hashlib.sha256(data).hexdigest(),
        "sourceSha256": hashlib.sha256(source.encode("utf-8")).hexdigest(),
        "entries": [f"0x{x:08X}" for x in ENTRIES],
        "ranges": ranges,
        "x87PositiveInfinity": {
            "address": "0x00259BFC",
            "bytes80": infinity.hex(),
        },
        "scope": (
            "Static retail-byte, control-flow, ABI, and isolated semantic validation; "
            "matched gameplay parity remains separate."
        ),
    }
    return json.dumps(record, indent=2) + "\n"


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--evidence", type=Path)
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    evidence = generate()
    if args.evidence:
        if args.check:
            if args.evidence.read_text(encoding="utf-8") != evidence:
                raise SystemExit(f"FAIL stale evidence: {args.evidence}")
        else:
            args.evidence.parent.mkdir(parents=True, exist_ok=True)
            args.evidence.write_text(evidence, encoding="utf-8", newline="\n")
    else:
        print(evidence, end="")
    print("PASS: five final CRT entries match retail bytes and restored bodies")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
