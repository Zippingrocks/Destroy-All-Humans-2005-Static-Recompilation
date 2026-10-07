#!/usr/bin/env python3
"""Locate XBE strings and every file-backed dword reference to them.

The output is evidence, not a symbol assignment.  It records the XBE hash,
section/virtual address of each exact NUL-terminated string, and nearby dwords
for each pointer reference.  Registration tables often become visible as
hash/string/handler triples, while code xrefs can be disassembled separately.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import struct
from dataclasses import dataclass
from pathlib import Path


@dataclass(frozen=True)
class Section:
    name: str
    virtual: int
    virtual_size: int
    raw: int
    raw_size: int


def u32(data: bytes, offset: int) -> int:
    return struct.unpack_from("<I", data, offset)[0]


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest().upper()


def sections(data: bytes) -> list[Section]:
    image_base = u32(data, 0x104)
    count = u32(data, 0x11C)
    table = u32(data, 0x120) - image_base
    raw_records = []
    for index in range(count):
        record = table + index * 56
        raw_records.append((
            u32(data, record + 4), u32(data, record + 8),
            u32(data, record + 12), u32(data, record + 16),
            u32(data, record + 20),
        ))

    def va_bytes(address: int, limit: int = 32) -> bytes:
        for virtual, _virtual_size, raw, raw_size, _name in raw_records:
            if virtual <= address < virtual + raw_size:
                start = raw + address - virtual
                return data[start:min(start + limit, raw + raw_size)]
        return b""

    result = []
    for virtual, virtual_size, raw, raw_size, name_va in raw_records:
        name_raw = va_bytes(name_va)
        name = name_raw.split(b"\0", 1)[0].decode("ascii", errors="replace")
        result.append(Section(name, virtual, virtual_size, raw, raw_size))
    return result


def context_words(data: bytes, section: Section, raw_offset: int,
                  radius: int) -> list[dict]:
    relative = raw_offset - section.raw
    aligned = relative & ~3
    result = []
    for delta in range(-radius * 4, (radius + 1) * 4, 4):
        item_relative = aligned + delta
        if item_relative < 0 or item_relative + 4 > section.raw_size:
            continue
        item_raw = section.raw + item_relative
        result.append({
            "address": f"0x{section.virtual + item_relative:08X}",
            "value": f"0x{u32(data, item_raw):08X}",
            "selected": delta == 0,
        })
    return result


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("xbe", type=Path)
    parser.add_argument("strings", nargs="+")
    parser.add_argument("--context-words", type=int, default=3)
    parser.add_argument("--output", type=Path)
    args = parser.parse_args()
    if args.context_words < 0 or args.context_words > 32:
        parser.error("context words must be between 0 and 32")

    data = args.xbe.read_bytes()
    mapped = sections(data)
    records = []
    for query in args.strings:
        needle = query.encode("ascii") + b"\0"
        occurrences = []
        for owner in mapped:
            payload = data[owner.raw:owner.raw + owner.raw_size]
            start = 0
            while True:
                at = payload.find(needle, start)
                if at < 0:
                    break
                virtual = owner.virtual + at
                packed = struct.pack("<I", virtual)
                xrefs = []
                for source in mapped:
                    source_data = data[source.raw:source.raw + source.raw_size]
                    xref_at = 0
                    while True:
                        xref_at = source_data.find(packed, xref_at)
                        if xref_at < 0:
                            break
                        raw_offset = source.raw + xref_at
                        xrefs.append({
                            "section": source.name,
                            "address": f"0x{source.virtual + xref_at:08X}",
                            "aligned": xref_at % 4 == 0,
                            "context": context_words(
                                data, source, raw_offset, args.context_words),
                        })
                        xref_at += 1
                occurrences.append({
                    "section": owner.name,
                    "address": f"0x{virtual:08X}",
                    "xrefs": xrefs,
                })
                start = at + 1
        records.append({"query": query, "occurrences": occurrences})

    document = {
        "schema": 1,
        "method": "exact-nul-string-and-file-backed-dword-xrefs",
        "warning": "A pointer reference is a table/code clue, not proof of a function name.",
        "input": {"path": str(args.xbe.resolve()), "sha256": sha256(data)},
        "strings": records,
    }
    rendered = json.dumps(document, indent=2) + "\n"
    if args.output:
        args.output.parent.mkdir(parents=True, exist_ok=True)
        args.output.write_text(rendered, encoding="utf-8")
    else:
        print(rendered, end="")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
