#!/usr/bin/env python3
"""Audit the observed Sonic Boom callback using retail evidence only."""

import argparse
import hashlib
import json
import re
from pathlib import Path


START = 0x000A6AF0
END = 0x000A6B59
TABLE_SLOT = 0x00230124


def xbe_sections(path: Path):
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


def read_va(image, va: int, size: int) -> bytes:
    data, sections = image
    for section_va, offset, section_size in sections:
        if section_va <= va and va + size <= section_va + section_size:
            start = offset + va - section_va
            return data[start:start + size]
    raise ValueError(f"0x{va:08X} is not file-backed")


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--evidence", type=Path, required=True)
    parser.add_argument("--log", type=Path)
    args = parser.parse_args()

    repo = Path(__file__).resolve().parents[1]
    workspace = Path(__file__).resolve().parents[3]
    image = xbe_sections(workspace / "default.xbe")
    evidence = json.loads(args.evidence.read_text(encoding="utf-8"))
    callback = evidence["callback"]
    retail_sha = hashlib.sha256(image[0]).hexdigest().upper()
    generated = (repo / "src/recomp/gen/recomp_sonic_boom_retail_callback.c").read_text(
        encoding="utf-8")
    manual = (repo / "src/recomp_manual.c").read_text(encoding="utf-8")

    assert evidence["source"] == "retail-xbe-only"
    assert evidence["retailXbeSha256"] == retail_sha
    assert int(callback["start"], 16) == START
    assert int(callback["end"], 16) == END
    assert int.from_bytes(read_va(image, TABLE_SLOT, 4), "little") == START
    code_bytes = read_va(image, START, END - START)
    assert hashlib.sha256(code_bytes).hexdigest().upper() == callback["codeBytesSha256"]
    assert re.search(r"^void\s+sub_000A6AF0\s*\(void\)\s*$", generated, re.MULTILINE)
    assert re.search(
        r"case\s+0x000A6AF0u:\s*return\s+sub_000A6AF0\s*;",
        manual, re.IGNORECASE)
    if args.log:
        log = args.log.read_text(encoding="utf-8", errors="replace")
        assert log.count("unresolved Xbox target 0x000A6AF0") >= 1

    print("PASS: Sonic Boom retail callback bytes and table slot match")
    print("PASS: generated callback is manually dispatchable")
    if args.log:
        print("PASS: preserved long-play log observed the callback unresolved")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
