#!/usr/bin/env python3
"""Read-only UI and cinematic transition observer for a running DAH recomp.

The observer follows the retail UI tree rooted at ``[[0x258470]]`` and emits a
JSONL row only when a named UI object's effective visibility changes.  It also
records the verified in-engine cinematic list at every such transition.  This
makes early HUD/objective release measurable without patching the game, sending
input, or continuously dumping guest RAM.
"""

from __future__ import annotations

import argparse
import json
import struct
import time
from pathlib import Path

from cinematic_state import read_cinematic_state
from live_blanket_observer import HOST_OFFSET, Reader, pointer


WATCH_ROOTS = {
    "main", "mission", "messages", "tutorial", "cinematic", "fade", "burn",
    "reticle", "objectives", "objective", "subtitles", "subtitle",
}
MAX_DEPTH = 10
MAX_OBJECTS = 512
MAX_LINKS = 128


def text_name(raw: bytes) -> str:
    value = raw.split(b"\0", 1)[0]
    return value.decode("latin1", errors="replace") if value else "<unnamed>"


def read_ui_tree(reader: Reader) -> tuple[int, dict[str, dict]]:
    """Return relevant named UI objects and their inherited active state."""
    root_link = reader.u32(0x00258470)
    root = reader.u32(root_link) if pointer(root_link) else 0
    if not pointer(root):
        return root, {}

    result: dict[str, dict] = {}
    seen: set[int] = set()

    def walk(obj: int, parent: int, parent_path: str, inherited: bool,
             depth: int, retain: bool) -> None:
        if (not pointer(obj) or obj in seen or len(seen) >= MAX_OBJECTS or
                depth > MAX_DEPTH):
            return
        header = reader.read(obj, 0x60)
        if not header:
            return
        if parent and struct.unpack_from("<I", header, 8)[0] != parent:
            return
        seen.add(obj)
        own_active = bool(header[4])
        effective = inherited and own_active
        name = text_name(header[0x0C:0x34])
        path = f"{parent_path}/{name}" if parent_path else name
        lowered = name.lower()
        branch_keep = retain or lowered in WATCH_ROOTS
        keep = branch_keep or depth == 0
        if keep:
            result[path] = {
                "address": f"{obj:08X}",
                "ownActive": own_active,
                "effectiveActive": effective,
            }

        sentinel = obj + 0x44
        node = struct.unpack_from("<I", header, 0x44)[0]
        links: set[int] = set()
        while (pointer(node) and node != sentinel and node not in links and
               len(links) < MAX_LINKS and len(seen) < MAX_OBJECTS):
            links.add(node)
            link = reader.read(node, 12)
            if not link:
                break
            child = struct.unpack_from("<I", link, 8)[0]
            # At the root, inspect every direct child so watched branches can
            # become active later. Below it, retain the complete watched branch.
            if depth == 0 or branch_keep:
                walk(child, obj, path, effective, depth + 1, branch_keep)
            node = struct.unpack_from("<I", link)[0]

    walk(root, 0, "", True, 0, False)
    return root, result


def sample_activity(reader: Reader, layout: dict[str, dict]) -> dict[str, dict]:
    """Refresh active bytes with one contiguous read for the level UI heap."""
    addresses = [int(node["address"], 16) for path, node in layout.items()
                 if "/" in path]
    low = min(addresses) if addresses else 0
    high = max(addresses) + 5 if addresses else 0
    slab = reader.read(low, high - low) if low and high - low <= 0x200000 else None
    sampled: dict[str, dict] = {}
    for path in sorted(layout, key=lambda value: (value.count("/"), value)):
        address = int(layout[path]["address"], 16)
        if slab is not None and low <= address and address + 5 <= high:
            own_active = bool(slab[address + 4 - low])
        else:
            value = reader.read(address + 4, 1)
            own_active = bool(value and value[0])
        parent = path.rsplit("/", 1)[0] if "/" in path else None
        inherited = (sampled[parent]["effectiveActive"]
                     if parent in sampled else True)
        sampled[path] = {
            "address": f"{address:08X}",
            "ownActive": own_active,
            "effectiveActive": inherited and own_active,
        }
    return sampled


def cinematic_summary(reader: Reader) -> dict:
    state = read_cinematic_state(reader)
    return {
        "manager": (f"{state['cinematicManager']:08X}"
                    if state.get("cinematicManager") else None),
        "declaredCount": state.get("cinematicDeclaredCount"),
        "complete": state.get("cinematicComplete"),
        "reason": state.get("cinematicReason"),
        "movies": [{
            "object": f"{movie['object']:08X}",
            "nameHash": (f"{movie['nameHash']:08X}"
                         if movie.get("nameHash") is not None else None),
            "durationBits": (f"{movie['durationBits']:08X}"
                             if movie.get("durationBits") is not None else None),
            "elapsedBits": (f"{movie['elapsedBits']:08X}"
                            if movie.get("elapsedBits") is not None else None),
            "flags": movie.get("flags"),
            "state": movie.get("state"),
        } for movie in (state.get("cinematics") or [])],
    }


def emit(stream, kind: str, reader: Reader, **fields) -> None:
    world = reader.u32(0x00286768)
    tick = reader.u32(world + 8) if pointer(world) else 0
    elapsed_bits = reader.u32(world + 0x0C) if pointer(world) else 0
    renderer = reader.u32(0x00250E60)
    movie = reader.u32(0x0028681C)
    row = {
        "type": kind,
        "time": round(time.time(), 6),
        "loop": reader.u32(0x0025B1DC),
        "world": f"{world:08X}" if world else None,
        "worldTick": tick,
        "worldElapsedBits": f"{elapsed_bits:08X}",
        "worldPaused": (reader.read(world + 0x303C, 1) or b"\0")[0]
                       if pointer(world) else None,
        "worldRealtime": (reader.read(world + 0x303D, 1) or b"\0")[0]
                         if pointer(world) else None,
        "savedBackbuffer": (f"{reader.u32(renderer + 0x484):08X}"
                            if pointer(renderer) else None),
        "savedBackbufferEnabled": ((reader.read(renderer + 0x488, 1) or b"\0")[0]
                                   if pointer(renderer) else None),
        "binkMovie": f"{movie:08X}" if movie else None,
        "binkMode": reader.u32(0x002867F8),
        "binkFlags": (reader.read(0x002867F4, 1) or b"\0")[0],
        "binkLifecycle": reader.u32(0x00286804),
        **fields,
    }
    stream.write(json.dumps(row, separators=(",", ":")) + "\n")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--pid", type=int, required=True)
    parser.add_argument("--output", type=Path, required=True)
    parser.add_argument("--seconds", type=float, default=0.0,
                        help="capture duration; zero follows process until exit")
    parser.add_argument("--hz", type=float, default=30.0)
    parser.add_argument("--host-offset", type=lambda value: int(value, 0),
                        default=HOST_OFFSET)
    args = parser.parse_args()

    reader = Reader(args.pid, args.host_offset)
    args.output.parent.mkdir(parents=True, exist_ok=True)
    deadline = (time.perf_counter() + args.seconds
                if args.seconds > 0 else float("inf"))
    previous: dict[str, dict] | None = None
    previous_root = 0
    next_sample = time.perf_counter()
    try:
        with args.output.open("x", encoding="utf-8", buffering=1) as stream:
            emit(stream, "run-start", reader, pid=args.pid, sampleHz=args.hz,
                 observer="ui-transition-v1")
            while time.perf_counter() < deadline and reader.is_running():
                root_link = reader.u32(0x00258470)
                root = reader.u32(root_link) if pointer(root_link) else 0
                if previous is None or root != previous_root:
                    root, layout = read_ui_tree(reader)
                    current = sample_activity(reader, layout)
                    emit(stream, "ui-root", reader,
                         root=f"{root:08X}" if root else None,
                         nodes=current, cinematic=cinematic_summary(reader))
                else:
                    current = sample_activity(reader, previous)
                    changed = {}
                    for path in sorted(set(previous) | set(current)):
                        before, after = previous.get(path), current.get(path)
                        if before != after:
                            changed[path] = {"before": before, "after": after}
                    if changed:
                        emit(stream, "ui-transition", reader, changes=changed,
                             cinematic=cinematic_summary(reader))
                previous, previous_root = current, root
                next_sample += 1.0 / max(1.0, args.hz)
                delay = next_sample - time.perf_counter()
                if delay > 0:
                    time.sleep(delay)
                else:
                    next_sample = time.perf_counter()
            emit(stream, "run-end", reader,
                 reason=("process-exited" if not reader.is_running()
                         else "duration-complete"))
    finally:
        reader.close()
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
