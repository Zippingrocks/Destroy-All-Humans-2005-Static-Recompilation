#!/usr/bin/env python3
"""Decode DAH entity and AI state from a 64 MiB xemu RAM capture.

The output uses the same actor identity, resource, AI, life, physics and census
fields as live_blanket_observer.py.  It is an offline decoder: capture atomicity
is declared by the caller and never inferred from a quiet or plausible result.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import time
from pathlib import Path

from decode_xemu_ram import XboxRam
from live_blanket_observer import (MAX_ENTITY_SIZE, RESOURCE_NAMES, census,
                                   ident, matching_profile, read_actor, rounded)


class XboxReader:
    def __init__(self, ram: XboxRam):
        self.ram = ram

    def read(self, address: int, size: int) -> bytes | None:
        try:
            return self.ram.read(address, size)
        except (ValueError, IndexError):
            return None

    def u32(self, address: int) -> int:
        try:
            return self.ram.word(address)
        except (ValueError, IndexError):
            return 0


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def write_event(output, event: str, **fields) -> None:
    output.write(json.dumps({"event": event, **fields},
                            separators=(",", ":")) + "\n")


def scan_mapped_actors(reader: XboxReader, start: int, end: int) -> dict[int, tuple]:
    """Scan mapped heap pages without treating one unmapped page as no heap."""
    found = {}
    page = start & ~0xFFF
    while page < end:
        data = reader.read(page, min(0x1000 + MAX_ENTITY_SIZE, end - page))
        if data:
            for offset in range(max(0, start - page), min(0x1000, end - page), 0x10):
                profile = matching_profile(data, offset)
                if profile:
                    found[page + offset] = profile
        page += 0x1000
    return found


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("ram", type=Path)
    parser.add_argument("--out", type=Path, required=True)
    parser.add_argument("--cr3", type=lambda value: int(value, 0), default=0xF000)
    parser.add_argument("--scan-start", type=lambda value: int(value, 0),
                        default=0x82000000)
    parser.add_argument("--scan-end", type=lambda value: int(value, 0),
                        default=0x84000000)
    parser.add_argument("--atomic", action="store_true",
                        help="Declare that xemu was paused for this capture")
    args = parser.parse_args()
    if args.scan_start >= args.scan_end:
        parser.error("scan start must precede scan end")

    raw = args.ram.read_bytes()
    reader = XboxReader(XboxRam(raw, args.cr3))
    RESOURCE_NAMES.clear()
    captured_at = time.time()
    found = scan_mapped_actors(reader, args.scan_start, args.scan_end)
    actors = {}
    for address, profile in found.items():
        actor = read_actor(reader, address, profile, captured_at)
        if actor:
            actors[address] = actor

    args.out.parent.mkdir(parents=True, exist_ok=True)
    with args.out.open("x", encoding="utf-8", buffering=1) as output:
        write_event(output, "snapshot-start", hostSeconds=captured_at,
                    source="xemu-physical-ram", ram=str(args.ram),
                    ramSha256=sha256(raw), cr3=f"{args.cr3:08X}",
                    atomic=args.atomic,
                    consistency=("paused-atomic" if args.atomic else
                                 "live-non-atomic"),
                    scanRange=[f"{args.scan_start:08X}",
                               f"{args.scan_end:08X}"])
        for actor in sorted(actors.values(), key=lambda item: item.address):
            write_event(output, "actor-snapshot", hostSeconds=captured_at,
                        **ident(actor), scene=f"{actor.scene:08X}",
                        objectFlags=(f"{actor.object_flags:08X}"
                                     if actor.object_flags is not None else None),
                        position=rounded(actor.position),
                        quaternion=rounded(actor.quaternion))
        write_event(output, "snapshot-end", hostSeconds=captured_at,
                    actors=len(actors), census=census(actors),
                    coverage={
                        "actorIdentity": bool(actors),
                        "resourceNames": any(a.resource_name for a in actors.values()),
                        "namedAiState": any(a.ai_state_name for a in actors.values()),
                        "lifeState": any(a.life_state for a in actors.values()),
                        "atomic": args.atomic,
                        "spawnDespawn": False,
                        "damageCause": False,
                        "effectOwnership": False,
                    })
    print(json.dumps({"output": str(args.out), "actors": len(actors),
                      "atomic": args.atomic, "census": census(actors)}, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
