#!/usr/bin/env python3
"""Report every measurable frame-time deviation from a DAH event trace."""

from __future__ import annotations

import argparse
import json
import math
import statistics
from pathlib import Path


PHASES = ("logicUs", "renderUs", "presentUs")


def percentile(values: list[int], fraction: float) -> float:
    if not values:
        return 0.0
    ordered = sorted(values)
    position = fraction * (len(ordered) - 1)
    lower = math.floor(position)
    upper = math.ceil(position)
    if lower == upper:
        return float(ordered[lower])
    return ordered[lower] * (upper - position) + ordered[upper] * (position - lower)


def load_frames(path: Path) -> list[dict]:
    frames: list[dict] = []
    with path.open("r", encoding="utf-8") as stream:
        for line_number, raw in enumerate(stream, 1):
            try:
                row = json.loads(raw)
            except json.JSONDecodeError as error:
                raise SystemExit(f"{path}:{line_number}: {error}") from error
            if row.get("event") == "frame" and row.get("intervalUs", 0):
                frames.append(row)
    return frames


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("trace", type=Path)
    parser.add_argument("--top", type=int, default=40,
                        help="number of slowest frames to print (default: 40)")
    parser.add_argument("--all-over-target", action="store_true",
                        help="print every frame whose interval exceeds its target")
    args = parser.parse_args()

    frames = load_frames(args.trace)
    if not frames:
        raise SystemExit("no complete frame records found")

    intervals = [int(frame["intervalUs"]) for frame in frames]
    median = statistics.median(intervals)
    deviations = [abs(value - median) for value in intervals]
    mad = statistics.median(deviations)
    print(json.dumps({
        "frames": len(frames),
        "medianUs": median,
        "madUs": mad,
        "p95Us": round(percentile(intervals, 0.95), 3),
        "p99Us": round(percentile(intervals, 0.99), 3),
        "maximumUs": max(intervals),
        "overTarget": sum(int(f["intervalUs"]) > int(f["targetUs"]) for f in frames),
        "late": sum(bool(int(f.get("flags", 0)) & 1) for f in frames),
    }, separators=(",", ":")))

    selected = sorted(frames, key=lambda frame: int(frame["intervalUs"]), reverse=True)
    if args.all_over_target:
        selected = [frame for frame in selected
                    if int(frame["intervalUs"]) > int(frame["targetUs"])]
    else:
        selected = selected[:max(args.top, 0)]

    for frame in selected:
        dominant = max(PHASES, key=lambda phase: int(frame.get(phase, 0)))
        print(json.dumps({
            "hostFrame": frame["hostFrame"],
            "worldTick": frame["worldTick"],
            "loop": frame["loop"],
            "intervalUs": frame["intervalUs"],
            "targetUs": frame["targetUs"],
            "overTargetUs": int(frame["intervalUs"]) - int(frame["targetUs"]),
            "logicUs": frame["logicUs"],
            "renderUs": frame["renderUs"],
            "presentUs": frame["presentUs"],
            "totalUs": frame["totalUs"],
            "dominantPhase": dominant.removesuffix("Us"),
            "drawDelta": frame["drawDelta"],
            "presentResult": frame["presentResult"],
            "flags": frame["flags"],
        }, separators=(",", ":")))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
