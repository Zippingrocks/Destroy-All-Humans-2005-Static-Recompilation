#!/usr/bin/env python3
"""Resolve actor-controller resource pointers seen by blanket captures."""

from __future__ import annotations

import argparse
import json
import struct
from pathlib import Path

from live_blanket_observer import Reader, pointer


def printable_string(data: bytes, limit: int = 160) -> str | None:
    end = data.find(b"\0", 0, limit)
    if end < 3:
        return None
    value = data[:end]
    if not all(32 <= byte < 127 for byte in value):
        return None
    return value.decode("ascii")


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--pid", type=int, required=True)
    parser.add_argument("capture", type=Path)
    args = parser.parse_args()
    resources = set()
    for line in args.capture.open(encoding="utf-8"):
        event = json.loads(line)
        if event.get("event") == "actor-spawn" and event.get("resource"):
            resources.add(int(event["resource"], 16))
    reader = Reader(args.pid, 0x10000)
    result = []
    try:
        for resource in sorted(resources):
            raw = reader.read(resource, 0x240)
            if not raw:
                continue
            strings = []
            for offset in range(0, len(raw) - 4, 4):
                value = struct.unpack_from("<I", raw, offset)[0]
                if not pointer(value):
                    continue
                target = reader.read(value, 160)
                text = printable_string(target) if target else None
                if text:
                    strings.append({"offset": f"{offset:03X}",
                                    "pointer": f"{value:08X}", "text": text})
            direct = []
            for offset in range(len(raw)):
                text = printable_string(raw[offset:])
                if text and (not direct or offset >= direct[-1][0] + len(direct[-1][1])):
                    direct.append((offset, text))
            result.append({"resource": f"{resource:08X}",
                           "headerWords": [f"{value:08X}" for value in
                                           struct.unpack_from("<16I", raw)],
                           "directStrings": [{"offset": f"{offset:03X}", "text": text}
                                             for offset, text in direct],
                           "pointedStrings": strings})
    finally:
        reader.close()
    print(json.dumps(result, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
