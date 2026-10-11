#!/usr/bin/env python3
"""Audit the live-observed 0012AEE0 callback against the retail XBE."""

import argparse
import hashlib
import re
from pathlib import Path

START = 0x0012AEE0
END = 0x0012AF02
VTABLE = 0x002375F8
EXPECTED = bytes.fromhex(
    "8b4424043dccfdca1c7505b001c204003de4e41f7e74f43d419eeeff0f94c0c20400"
)


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
    parser.add_argument("--log", type=Path)
    args = parser.parse_args()
    repo = Path(__file__).resolve().parents[1]
    workspace = Path(__file__).resolve().parents[3]
    image = xbe_sections(workspace / "default.xbe")
    source = (repo / "src/recomp/gen/recomp_live_type_callback.c").read_text(encoding="utf-8")
    manual = (repo / "src/recomp_manual.c").read_text(encoding="utf-8")
    assert read_va(image, START, END - START) == EXPECTED
    assert int.from_bytes(read_va(image, VTABLE, 4), "little") == START
    assert re.search(r"^void\s+sub_0012AEE0\s*\(void\)\s*$", source, re.MULTILINE)
    assert re.search(r"case\s+0x0012AEE0u:\s*return\s+sub_0012AEE0\s*;", manual)
    if args.log:
        log = args.log.read_text(encoding="utf-8", errors="replace")
        assert "unresolved Xbox target 0x0012AEE0" in log
    print("PASS: 0012AEE0 matches 34 retail XBE bytes")
    print("PASS: retail vtable 002375F8 points to the restored callback")
    print("PASS: callback is implemented and manually dispatchable")
    print(f"INFO: retail callback sha256={hashlib.sha256(EXPECTED).hexdigest().upper()}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
