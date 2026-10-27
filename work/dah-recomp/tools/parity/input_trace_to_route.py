#!/usr/bin/env python3
"""Convert lossless FURON-INPUT changes into a shared frame-scheduled route."""

from __future__ import annotations

import argparse
import re
from pathlib import Path


PATTERN = re.compile(
    r"^\[FURON-INPUT\] poll=(?P<poll>\d+)(?: loop=(?P<loop>\d+))? "
    r"changed=(?P<changed>[01]) packet=\d+ buttons=(?P<buttons>[0-9A-Fa-f]{4}) "
    r"analog=A:(?P<a>\d+),B:(?P<b>\d+),X:(?P<x>\d+),Y:(?P<y>\d+),"
    r"BLACK:(?P<black>\d+),WHITE:(?P<white>\d+),LT:(?P<lt>\d+),RT:(?P<rt>\d+) "
    r"sticks=(?P<lx>-?\d+),(?P<ly>-?\d+),(?P<rx>-?\d+),(?P<ry>-?\d+) "
)


def parse(path: Path) -> list[dict]:
    changes = []
    saw_loop = None
    for line_number, line in enumerate(path.read_text(encoding="utf-8", errors="replace").splitlines(), 1):
        match = PATTERN.match(line)
        if not match or match.group("changed") != "1":
            continue
        item = {key: int(value, 16 if key == "buttons" else 10)
                for key, value in match.groupdict().items()
                if key not in ("changed", "loop") and value is not None}
        item["loop"] = int(match.group("loop")) if match.group("loop") else None
        has_loop = item["loop"] is not None
        if saw_loop is None:
            saw_loop = has_loop
        elif saw_loop != has_loop:
            raise ValueError(f"{path}:{line_number}: mixed legacy and loop-numbered input rows")
        changes.append(item)
    if not changes:
        raise ValueError(f"{path}: no changed FURON-INPUT rows")
    return changes


def neutral(item: dict) -> bool:
    return all(item[key] == 0 for key in
               ("buttons", "a", "b", "x", "y", "black", "white", "lt", "rt",
                "lx", "ly", "rx", "ry"))


def convert(changes: list[dict], tail: int) -> str:
    clock = "loop" if changes[0]["loop"] is not None else "poll"
    clock_key = "loop" if clock == "loop" else "poll"
    collapsed = []
    for item in changes:
        if collapsed and item[clock_key] == collapsed[-1][clock_key]:
            collapsed[-1] = item
        elif collapsed and item[clock_key] < collapsed[-1][clock_key]:
            raise ValueError(f"input {clock_key} moved backwards")
        else:
            collapsed.append(item)
    origin = collapsed[0][clock_key]
    lines = [
        "# Generated from final logical pad states delivered by the recomp.",
        f"# Source clock: {clock}; origin={origin}; zero/neutral spans are implicit.",
        "# start duration hex_buttons A B LX LY RX RY X Y BLACK WHITE LT RT",
    ]
    if clock == "loop":
        lines.append("@relative-frame")
    for index, item in enumerate(collapsed):
        start = item[clock_key] - origin
        finish = (collapsed[index + 1][clock_key] - origin
                  if index + 1 < len(collapsed) else start + tail)
        duration = finish - start
        if duration <= 0 or neutral(item):
            continue
        lines.append(
            f"{start} {duration} {item['buttons']:X} {item['a']} {item['b']} "
            f"{item['lx']} {item['ly']} {item['rx']} {item['ry']} "
            f"{item['x']} {item['y']} {item['black']} {item['white']} "
            f"{item['lt']} {item['rt']}"
        )
    minimum = 4 if clock == "loop" else 3
    if len(lines) == minimum:
        raise ValueError("trace contains no non-neutral input spans")
    if len(lines) - minimum > 4096:
        raise ValueError("route exceeds the native 4096-event diagnostic limit; crop the trace")
    return "\n".join(lines) + "\n"


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("log", type=Path)
    parser.add_argument("out", type=Path)
    parser.add_argument("--tail", type=int, default=1,
                        help="duration for a final non-neutral state")
    args = parser.parse_args()
    if args.tail < 1 or args.tail > 100000:
        parser.error("--tail must be in [1,100000]")
    if args.out.exists():
        parser.error("output must be new")
    payload = convert(parse(args.log), args.tail)
    args.out.parent.mkdir(parents=True, exist_ok=True)
    args.out.write_text(payload, encoding="utf-8")
    print(f"wrote {args.out} ({payload.count(chr(10))} lines)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
