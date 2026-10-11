#!/usr/bin/env python3
"""Compare aligned native and xemu blanket captures by semantic census.

This reports differences; it never claims a parity failure unless the caller
has aligned level, checkpoint, mission state, input edge and world tick.
"""

from __future__ import annotations

import argparse
import json
from collections import Counter
from pathlib import Path


def read_events(path: Path):
    with path.open(encoding="utf-8") as source:
        for line in source:
            if line.strip():
                yield json.loads(line)


def native_census(path: Path) -> dict:
    actors = {}
    heartbeat = None
    for event in read_events(path):
        kind = event.get("event")
        if kind == "actor-spawn":
            actors[event.get("actor")] = event
        elif kind in ("actor-state", "ai-state"):
            actors[event.get("actor")] = {**actors.get(event.get("actor"), {}),
                                           **event}
        elif kind == "actor-despawn":
            actors.pop(event.get("actor"), None)
        elif kind == "heartbeat" and event.get("census"):
            heartbeat = event["census"]
    if heartbeat:
        return heartbeat
    return census_from_actors(actors.values())


def xemu_census(path: Path) -> dict:
    actors = []
    final = None
    for event in read_events(path):
        if event.get("event") == "actor-snapshot":
            actors.append(event)
        elif event.get("event") == "snapshot-end":
            final = event.get("census")
    return final or census_from_actors(actors)


def census_from_actors(actors) -> dict:
    fields = {
        "byClass": Counter(), "byResource": Counter(),
        "byAiState": Counter(), "byLifeState": Counter(),
    }
    for actor in actors:
        if actor.get("class"):
            fields["byClass"][actor["class"]] += 1
        resource = actor.get("resourceName") or actor.get("resource")
        if resource:
            fields["byResource"][resource] += 1
        if actor.get("aiStateName"):
            fields["byAiState"][actor["aiStateName"]] += 1
        if actor.get("lifeState"):
            fields["byLifeState"][actor["lifeState"]] += 1
    return {key: dict(value) for key, value in fields.items()}


def differences(reference: dict, native: dict) -> dict:
    result = {}
    for category in sorted(set(reference) | set(native)):
        ref = reference.get(category, {})
        got = native.get(category, {})
        rows = []
        for name in sorted(set(ref) | set(got)):
            expected, actual = ref.get(name, 0), got.get(name, 0)
            if expected != actual:
                rows.append({"name": name, "xemu": expected, "native": actual,
                             "delta": actual - expected})
        result[category] = rows
    return result


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("xemu", type=Path)
    parser.add_argument("native", type=Path)
    parser.add_argument("--out", type=Path)
    parser.add_argument("--alignment", default="unverified")
    args = parser.parse_args()
    reference = xemu_census(args.xemu)
    native = native_census(args.native)
    delta = differences(reference, native)
    report = {
        "schema": 1,
        "alignment": args.alignment,
        "comparisonStatus": ("comparable" if args.alignment == "verified"
                             else "diagnostic-only"),
        "warning": (None if args.alignment == "verified" else
                    "Different census values are not parity failures until level, "
                    "checkpoint, mission state, input edge and world tick are aligned."),
        "xemu": reference,
        "native": native,
        "differences": delta,
        "matching": all(not rows for rows in delta.values()),
    }
    serialized = json.dumps(report, indent=2) + "\n"
    if args.out:
        args.out.write_text(serialized, encoding="utf-8")
    print(serialized, end="")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
