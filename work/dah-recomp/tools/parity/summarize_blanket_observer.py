#!/usr/bin/env python3
"""Summarize a live_blanket_observer JSONL capture without dumping raw events."""

from __future__ import annotations

import argparse
import collections
import json
from pathlib import Path


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("capture", type=Path)
    parser.add_argument("--recent", type=int, default=20)
    args = parser.parse_args()
    counts = collections.Counter()
    resources = collections.Counter()
    active = collections.Counter()
    recent = []
    first = last = None
    with args.capture.open(encoding="utf-8") as source:
        for line in source:
            event = json.loads(line)
            first = first or event
            last = event
            kind = event.get("event", "unknown")
            counts[kind] += 1
            if kind == "actor-spawn":
                resources[event.get("resource")] += 1
                active[event.get("stateByte140")] += 1
            if kind not in ("heartbeat", "run-start"):
                recent.append(event)
                recent = recent[-args.recent:]
    summary = {
        "firstHostSeconds": first.get("hostSeconds") if first else None,
        "lastHostSeconds": last.get("hostSeconds") if last else None,
        "events": dict(counts),
        "spawnStateByte140Values": dict(active),
        "topResources": resources.most_common(20),
        "recentSignificantEvents": recent,
    }
    print(json.dumps(summary, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
