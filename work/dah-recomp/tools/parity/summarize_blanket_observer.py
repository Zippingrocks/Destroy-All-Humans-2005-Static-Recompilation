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
    spawn_gate_values = collections.Counter()
    ai_states = collections.Counter()
    life_states = collections.Counter()
    anomaly_codes = collections.Counter()
    live_actors = {}
    actor_histories = {}
    last_census = None
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
                resources[event.get("resourceName") or event.get("resource")] += 1
                spawn_gate_values[event.get("stateByte140")] += 1
                live_actors[event.get("actor")] = event
            elif kind == "actor-despawn":
                live_actors.pop(event.get("actor"), None)
                if event.get("history"):
                    actor_histories[event.get("actor")] = event["history"]
            elif kind == "actor-summary":
                actor_histories[event.get("actor")] = event
            elif kind == "ai-state":
                if event.get("aiStateName"):
                    ai_states[event["aiStateName"]] += 1
                if event.get("lifeState"):
                    life_states[event["lifeState"]] += 1
                live_actors[event.get("actor")] = event
            elif kind == "anomaly":
                anomaly_codes[event.get("code", "unknown")] += 1
            elif kind == "heartbeat":
                last_census = event.get("census")
            if kind not in ("heartbeat", "run-start"):
                recent.append(event)
                recent = recent[-args.recent:]
    summary = {
        "firstHostSeconds": first.get("hostSeconds") if first else None,
        "lastHostSeconds": last.get("hostSeconds") if last else None,
        "events": dict(counts),
        "spawnStateByte140Values": dict(spawn_gate_values),
        "topResources": resources.most_common(20),
        "aiTransitionsInto": dict(ai_states),
        "lifeTransitionsInto": dict(life_states),
        "anomalies": dict(anomaly_codes),
        "lastCensus": last_census,
        "trackedAtLastEvent": len(live_actors),
        "actorHistories": sorted(actor_histories.values(),
                                 key=lambda item: (item.get("class", ""),
                                                   item.get("resourceName") or "",
                                                   item.get("actor", ""))),
        "recentSignificantEvents": recent,
    }
    print(json.dumps(summary, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
