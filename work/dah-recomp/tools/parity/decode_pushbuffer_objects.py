"""Print object switches and copy-oriented NV2A packets from a raw ring capture."""

from __future__ import annotations

import argparse
import struct
from pathlib import Path


def packets(path: Path):
    data = path.read_bytes()
    words = struct.unpack(f"<{len(data) // 4}I", data)
    pos = 0
    while pos < len(words):
        header = words[pos]
        if header == 0:
            pos += 1
            continue
        masked = header & 0xE0030003
        if masked == 0:
            noninc = False
        elif masked == 0x40000000:
            noninc = True
        else:
            pos += 1
            continue
        count = (header >> 18) & 0x7FF
        method = header & 0x1FFC
        subchannel = (header >> 13) & 7
        if count == 0 or count > len(words) - pos - 1:
            pos += 1
            continue
        values = words[pos + 1 : pos + 1 + count]
        yield pos, subchannel, method, noninc, values
        pos += count + 1


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("captures", nargs="+", type=Path)
    parser.add_argument(
        "--find", action="append", type=lambda value: int(value, 16), default=[]
    )
    parser.add_argument("--start", type=lambda value: int(value, 16), default=0)
    parser.add_argument("--end", type=lambda value: int(value, 16))
    args = parser.parse_args()
    for path in args.captures:
        print(f"== {path.name} ==")
        objects = [None] * 8
        for pos, sub, method, noninc, values in packets(path):
            if pos < args.start or (args.end is not None and pos >= args.end):
                continue
            if args.start or args.end is not None:
                rendered = " ".join(f"{value:08X}" for value in values[:24])
                suffix = " ..." if len(values) > 24 else ""
                print(
                    f"{pos:06X} sub={sub} obj={objects[sub]!s:>10} "
                    f"method={method:04X} count={len(values)} "
                    f"{'noninc' if noninc else 'inc'} {rendered}{suffix}"
                )
                continue
            if args.find:
                if any(value in args.find for value in values):
                    rendered = " ".join(f"{value:08X}" for value in values[:24])
                    suffix = " ..." if len(values) > 24 else ""
                    print(
                        f"{pos:06X} sub={sub} obj={objects[sub]!s:>10} "
                        f"method={method:04X} count={len(values)} "
                        f"{'noninc' if noninc else 'inc'} {rendered}{suffix}"
                    )
                continue
            if method == 0:
                for value in values:
                    objects[sub] = value
                    print(f"{pos:06X} sub={sub} SET_OBJECT {value:08X}")
                continue
            # 2D surface/image-blit control apertures, plus low methods that
            # reveal the context object connected to an image-blit object.
            if method <= 0x310 and method not in (0x100, 0x110, 0x120, 0x124,
                                                  0x128, 0x12C, 0x130, 0x180,
                                                  0x184, 0x188, 0x190, 0x194,
                                                  0x198, 0x19C, 0x1A0, 0x1A4,
                                                  0x1A8, 0x200, 0x204, 0x208,
                                                  0x20C, 0x210, 0x214):
                rendered = " ".join(f"{value:08X}" for value in values[:16])
                suffix = " ..." if len(values) > 16 else ""
                print(
                    f"{pos:06X} sub={sub} obj={objects[sub]!s:>10} "
                    f"method={method:04X} count={len(values)} "
                    f"{'noninc' if noninc else 'inc'} {rendered}{suffix}"
                )
            elif method in (0x2FC, 0x300, 0x304, 0x308, 0x30C):
                rendered = " ".join(f"{value:08X}" for value in values[:16])
                print(
                    f"{pos:06X} sub={sub} obj={objects[sub]!s:>10} "
                    f"method={method:04X} count={len(values)} "
                    f"{'noninc' if noninc else 'inc'} {rendered}"
                )


if __name__ == "__main__":
    main()
