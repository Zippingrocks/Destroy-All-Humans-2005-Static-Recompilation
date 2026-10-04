#!/usr/bin/env python3
"""Build the GitHub Pages function-coverage dataset from repository evidence."""

import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[4]
FUNCTIONS = ROOT / "work" / "disasm-seeded" / "functions.json"
GEN = ROOT / "work" / "dah-recomp" / "src" / "recomp" / "gen"
SEEDS = ROOT / "work" / "dah-recomp" / "icall_seeds.json"
PARITY = ROOT / "work" / "dah-recomp" / "tools" / "parity"
OUTPUT = ROOT / "docs" / "coverage" / "data.js"

ADDRESS = re.compile(r"(?:sub_|0x)([0-9A-Fa-f]{8})")
DEFINITION = re.compile(r"\bvoid\s+sub_([0-9A-Fa-f]{8})\s*\(")
DISPATCH = re.compile(r"\{\s*0x([0-9A-Fa-f]{8})u,")


def addresses(text, pattern=ADDRESS):
    return {int(m.group(1), 16) for m in pattern.finditer(text)}


def source_addresses(path, pattern=DEFINITION):
    return addresses(path.read_text(encoding="utf-8", errors="replace"), pattern)


def main():
    functions = json.loads(FUNCTIONS.read_text(encoding="utf-8"))
    seeds = {
        int(item["start"], 16)
        for item in json.loads(SEEDS.read_text(encoding="utf-8"))
    }
    dispatch = source_addresses(GEN / "recomp_dispatch.c", DISPATCH)
    stubs = source_addresses(GEN / "recomp_stubs_unresolved.c")

    numbered = {p.resolve() for p in GEN.glob("recomp_[0-9][0-9][0-9][0-9].c")}
    special_sources = [
        p for p in GEN.glob("recomp_*.c")
        if p.resolve() not in numbered
        and p.name not in {"recomp_dispatch.c", "recomp_stubs_unresolved.c"}
    ]
    recovered = set()
    recovery_source = {}
    for path in special_sources:
        found = source_addresses(path)
        recovered.update(found)
        for address in found:
            recovery_source[address] = path.name

    evidence = set()
    for path in PARITY.glob("*.md"):
        evidence.update(addresses(path.read_text(encoding="utf-8", errors="replace")))

    rows = []
    known = set()
    for fn in functions:
        address = int(fn["start"], 16)
        known.add(address)
        if address in stubs:
            status = "stubbed"
        elif address in recovered:
            status = "recovered"
        elif address in seeds:
            status = "seeded"
        elif address in dispatch:
            status = "translated"
        else:
            status = "missing"
        rows.append([
            address,
            max(1, int(fn.get("size", 1))),
            fn.get("name") or f"sub_{address:08X}",
            status,
            round(float(fn.get("confidence", 0)), 3),
            int(fn.get("num_instructions", 0)),
            len(fn.get("calls_to", [])),
            len(fn.get("called_by", [])),
            1 if address in evidence else 0,
            recovery_source.get(address, ""),
        ])

    # Mid-function callbacks can be absent from the disassembler inventory.
    # Keep them visible without pretending their unknown byte extent is known.
    for address in sorted((seeds | stubs | recovered) - known):
        status = "stubbed" if address in stubs else "recovered" if address in recovered else "seeded"
        rows.append([
            address, 16, f"sub_{address:08X}", status, 0, 0, 0, 0,
            1 if address in evidence else 0,
            recovery_source.get(address, ""),
        ])

    rows.sort(key=lambda row: row[0])
    meta = {
        "generated": "repository build",
        "functionCount": len(rows),
        "inventoryCount": len(functions),
        "dispatchCount": len(dispatch),
        "seedCount": len(seeds),
        "recoveredCount": sum(row[3] == "recovered" for row in rows),
        "stubCount": sum(row[3] == "stubbed" for row in rows),
        "evidenceCount": sum(bool(row[8]) for row in rows),
        "totalBytes": sum(row[1] for row in rows),
    }
    OUTPUT.parent.mkdir(parents=True, exist_ok=True)
    payload = "window.DAH_COVERAGE=" + json.dumps(
        {"meta": meta, "functions": rows}, separators=(",", ":")
    ) + ";\n"
    OUTPUT.write_text(payload, encoding="utf-8")
    print(f"wrote {OUTPUT.relative_to(ROOT)}: {len(rows)} entries, {len(payload):,} bytes")


if __name__ == "__main__":
    main()
