#!/usr/bin/env python3
"""Print a compact one-shot snapshot of live retail pedestrian actors."""

from __future__ import annotations

import argparse
import json
import struct
import time

from live_blanket_observer import Reader, cstring, read_actor, scan_actors


def as_float(bits: int | None) -> float | None:
    return struct.unpack("<f", struct.pack("<I", bits))[0] if bits is not None else None


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--pid", type=int, required=True)
    args = parser.parse_args()
    reader = Reader(args.pid, 0x10000)
    rows = []
    try:
        for address, profile in scan_actors(reader, 0x02900000, 0x03400000).items():
            if profile[0] != "pedestrian":
                continue
            actor = read_actor(reader, address, profile, time.time())
            if not actor:
                continue
            body = reader.u32(address + 0x110)
            inner = reader.u32(body + 0x0C) if body else 0
            ai_state = reader.u32(address + 0x34C)
            ai_descriptor = reader.u32(ai_state + 8) if ai_state else 0
            ai_name_pointer = reader.u32(ai_descriptor + 0x0C) if ai_descriptor else 0
            rows.append({
                "actor": f"{address:08X}", "serial": actor.serial,
                "resourceName": actor.resource_name,
                "position": actor.position,
                "healthDivisorBits": (f"{actor.health_divisor_bits:08X}"
                                      if actor.health_divisor_bits is not None else None),
                "healthDivisorFloat": as_float(actor.health_divisor_bits),
                "healthCurrentBits": (f"{actor.health_current_bits:08X}"
                                      if actor.health_current_bits is not None else None),
                "healthCurrentFloat": as_float(actor.health_current_bits),
                "physicsBody": f"{body:08X}",
                "physicsBodyVtable": f"{reader.u32(body):08X}" if body else None,
                "physicsInner": f"{inner:08X}",
                "physicsInnerVtable": f"{reader.u32(inner):08X}" if inner else None,
                "pedFlags3D0": f"{reader.u32(address + 0x3D0):08X}",
                "pedState3CC": reader.u32(address + 0x3CC),
                "pedState3D8": f"{reader.u32(address + 0x3D8):08X}",
                "aiState": f"{ai_state:08X}",
                "aiStateVtable": f"{reader.u32(ai_state):08X}" if ai_state else None,
                "aiDescriptor": f"{ai_descriptor:08X}",
                "aiStateId": (f"{reader.u32(ai_descriptor):08X}"
                              if ai_descriptor else None),
                "aiStateName": cstring(reader, ai_name_pointer),
                "pedTarget53C": f"{reader.u32(address + 0x53C):08X}",
                "pedTarget540": f"{reader.u32(address + 0x540):08X}",
                "pedFlags558": f"{reader.u32(address + 0x558):08X}",
                "pedFlags598": f"{reader.u32(address + 0x598):08X}",
            })
    finally:
        reader.close()
    print(json.dumps(rows, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
