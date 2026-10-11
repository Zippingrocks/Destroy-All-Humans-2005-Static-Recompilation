#!/usr/bin/env python3
"""Find a wildcard byte pattern in file-backed XBE sections.

Pattern tokens are hexadecimal bytes or ``??`` wildcards, for example::

    python tools/analysis/find_xbe_pattern.py default.xbe \
        "8B 44 24 04 8B 4C 24 08 8B 51 ?? 8B 40 ??"

The output uses Xbox virtual addresses so every hit can be passed directly to
``tools/parity/dump_xbe_code.py``.
"""

from __future__ import annotations

import argparse
import struct
from pathlib import Path


def parse_pattern(value: str) -> list[int | None]:
    result: list[int | None] = []
    for token in value.replace(",", " ").split():
        if token in {"?", "??"}:
            result.append(None)
        else:
            result.append(int(token, 16))
    if not result:
        raise argparse.ArgumentTypeError("pattern is empty")
    return result


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("xbe", type=Path)
    parser.add_argument("pattern", type=parse_pattern)
    args = parser.parse_args()

    data = args.xbe.read_bytes()
    word = lambda offset: struct.unpack_from("<I", data, offset)[0]
    image_base = word(0x104)
    section_table = word(0x120) - image_base
    hits = 0

    for index in range(word(0x11C)):
        record = section_table + index * 56
        virtual = word(record + 4)
        raw = word(record + 12)
        length = word(record + 16)
        section = data[raw : raw + length]
        stop = len(section) - len(args.pattern) + 1
        for offset in range(max(stop, 0)):
            if all(expected is None or section[offset + i] == expected
                   for i, expected in enumerate(args.pattern)):
                print(f"0x{virtual + offset:08X}")
                hits += 1

    if not hits:
        raise SystemExit(1)


if __name__ == "__main__":
    main()
