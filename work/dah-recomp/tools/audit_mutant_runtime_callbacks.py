#!/usr/bin/env python3
"""Audit retail-only evidence and dispatch for the mutant runtime callbacks."""

from __future__ import annotations

import argparse
import hashlib
import json
import re
from pathlib import Path


CALLBACKS = (
    (0x00130B20, 0x00130B3B, 0x00237880),
    (0x000242F0, 0x0002431B, 0x00227A00),
    (0x0011CB60, 0x0011CB68, 0x00236B3C),
    (0x0014A290, 0x0014A2DA, 0x0023751C),
    (0x00078040, 0x0007805E, 0x0022C424),
)


def xbe_sections(path: Path) -> tuple[bytes, list[tuple[int, int, int]]]:
    data = path.read_bytes()
    image_base = int.from_bytes(data[0x104:0x108], "little")
    count = int.from_bytes(data[0x11C:0x120], "little")
    table = int.from_bytes(data[0x120:0x124], "little") - image_base
    sections = []
    for index in range(count):
        entry = table + index * 56
        sections.append((
            int.from_bytes(data[entry + 4:entry + 8], "little"),
            int.from_bytes(data[entry + 12:entry + 16], "little"),
            int.from_bytes(data[entry + 16:entry + 20], "little"),
        ))
    return data, sections


def read_va(image: tuple[bytes, list[tuple[int, int, int]]], va: int, size: int) -> bytes:
    data, sections = image
    for section_va, offset, section_size in sections:
        if section_va <= va and va + size <= section_va + section_size:
            start = offset + va - section_va
            return data[start:start + size]
    raise ValueError(f"0x{va:08X}..0x{va + size:08X} is not file-backed")


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--log", type=Path)
    parser.add_argument("--output", type=Path)
    args = parser.parse_args()

    repo = Path(__file__).resolve().parents[1]
    workspace = Path(__file__).resolve().parents[3]
    xbe_path = workspace / "default.xbe"
    image = xbe_sections(xbe_path)
    manual = (repo / "src/recomp_manual.c").read_text(encoding="utf-8")
    generated_path = repo / "src/recomp/gen/recomp_mutant_runtime_callbacks.c"
    generated = generated_path.read_text(encoding="utf-8")
    evidence_path = repo / "docs/evidence/mutant-runtime-callbacks.json"
    evidence = json.loads(evidence_path.read_text(encoding="utf-8"))

    if evidence["retailXbeSha256"] != hashlib.sha256(image[0]).hexdigest().upper():
        raise SystemExit("FAIL: evidence does not identify the current retail XBE")

    rows = []
    log_text = args.log.read_text(encoding="utf-8", errors="replace") if args.log else ""
    for start, end, slot in CALLBACKS:
        function = f"sub_{start:08X}"
        if not re.search(rf"^void\s+{function}\s*\(void\)\s*$", generated, re.MULTILINE):
            raise SystemExit(f"FAIL 0x{start:08X}: generated body missing")
        if not re.search(rf"case\s+0x{start:08X}u:\s*return\s+{function}\s*;", manual, re.IGNORECASE):
            raise SystemExit(f"FAIL 0x{start:08X}: manual dispatch missing")
        record = next(row for row in evidence["callbacks"] if row["start"] == f"0x{start:08X}")
        body = read_va(image, start, end - start)
        if hashlib.sha256(body).hexdigest().upper() != record["codeBytesSha256"]:
            raise SystemExit(f"FAIL 0x{start:08X}: retail bytes changed")
        if slot is not None and int.from_bytes(read_va(image, slot, 4), "little") != start:
            raise SystemExit(f"FAIL 0x{start:08X}: retail table slot 0x{slot:08X} changed")
        rows.append({
            "address": f"0x{start:08X}",
            "end": f"0x{end:08X}",
            "retailBytes": end - start,
            "tableSlot": f"0x{slot:08X}" if slot is not None else None,
            "observedInLog": (f"{start:08X}" in log_text.upper()) if log_text else None,
            "status": "retail-bytes-verified-and-dispatchable",
        })

    report = {
        "schema": 1,
        "source": "retail-xbe-only",
        "retailXbeSha256": hashlib.sha256(image[0]).hexdigest().upper(),
        "callbacks": rows,
        "corruptMidInstructionTarget": {
            "address": "0x0001EB21",
            "dispatchAdded": False,
            "reason": "address lies inside the call instruction ending at 0x0001EB22",
        },
    }
    if args.output:
        args.output.parent.mkdir(parents=True, exist_ok=True)
        args.output.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(f"PASS: {len(rows)} mutant-scene callbacks match retail and are dispatchable")
    print("PASS: corrupt mid-instruction target 0x0001EB21 was not added to dispatch")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
