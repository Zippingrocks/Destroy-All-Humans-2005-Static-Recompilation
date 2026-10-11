#!/usr/bin/env python3
"""Audit the Ion Detonator crash repair using the retail XBE only."""

import argparse
import hashlib
import json
import re
from pathlib import Path


CALLBACKS = (
    (0x00075660, 0x00075681, 0x0022C1FC),
    (0x00075780, 0x000757A1, 0x0022C1AC),
    (0x00075800, 0x00075815, 0x0022C218),
    (0x00075A10, 0x00075C52, 0x0022C1E8),
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
    parser.add_argument("--evidence", type=Path, required=True)
    parser.add_argument("--crash", type=Path)
    args = parser.parse_args()

    repo = Path(__file__).resolve().parents[1]
    workspace = Path(__file__).resolve().parents[3]
    retail_path = workspace / "default.xbe"
    retail = xbe_sections(retail_path)
    retail_sha = hashlib.sha256(retail[0]).hexdigest().upper()
    manual = (repo / "src/recomp_manual.c").read_text(encoding="utf-8")
    generated = (repo / "src/recomp/gen/recomp_ion_detonator_retail_callbacks.c").read_text(
        encoding="utf-8")
    evidence = json.loads(args.evidence.read_text(encoding="utf-8"))

    assert evidence["source"] == "retail-xbe-only"
    assert evidence["retailXbeSha256"] == retail_sha
    rows = {int(row["start"], 16): row for row in evidence["callbacks"]}
    for start, end, slot in CALLBACKS:
        function = f"sub_{start:08X}"
        assert int.from_bytes(read_va(retail, slot, 4), "little") == start
        assert start in rows and int(rows[start]["end"], 16) == end
        code = read_va(retail, start, end - start)
        assert hashlib.sha256(code).hexdigest().upper() == rows[start]["codeBytesSha256"]
        assert re.search(rf"^void\s+{function}\s*\(void\)\s*$", generated, re.MULTILINE)
        assert re.search(
            rf"case\s+0x{start:08X}u:\s*return\s+{function}\s*;",
            manual, re.IGNORECASE)

    if args.crash:
        crash = args.crash.read_text(encoding="utf-8", errors="replace")
        for start, _, _ in CALLBACKS:
            assert f"unresolved Xbox target 0x{start:08X}" in crash

    print("PASS: retail XBE hash matches the generated evidence")
    print("PASS: four retail table slots and function byte ranges match")
    print("PASS: four generated bodies are manually dispatchable")
    if args.crash:
        print("PASS: the preserved crash observed all four retail callbacks unresolved")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
