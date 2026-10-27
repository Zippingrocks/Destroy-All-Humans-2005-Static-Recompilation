#!/usr/bin/env python3
"""Release a shared input-route barrier only after live presentation alignment."""

from __future__ import annotations

import argparse
import json
import os
import struct
import time
from pathlib import Path


def read_status(path: Path, event: str) -> dict | None:
    try:
        value = json.loads(path.read_text(encoding="utf-8-sig"))
    except (OSError, ValueError):
        return None
    if value.get("event") != event:
        return None
    return value


def aligned(value: dict, maximum_age: float) -> bool:
    age = time.time() - float(value.get("at", 0))
    return (0 <= age <= maximum_age and
            value.get("captureAligned") is True and
            value.get("presentationAligned") is True and
            not value.get("divergent") and
            not value.get("semanticDiff"))


def position(identity: dict | None) -> tuple[float, float, float] | None:
    bits = (identity or {}).get("actorPositionBits")
    if not isinstance(bits, list) or len(bits) != 3 or not all(isinstance(item, int) for item in bits):
        return None
    return tuple(struct.unpack("<f", struct.pack("<I", item & 0xFFFFFFFF))[0] for item in bits)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--state-status", required=True, type=Path)
    parser.add_argument("--phase-status", required=True, type=Path)
    parser.add_argument("--barrier", required=True, type=Path)
    parser.add_argument("--seconds", type=float, default=60.0)
    parser.add_argument("--consecutive", type=int, default=3)
    parser.add_argument("--maximum-age-ms", type=float, default=250.0)
    parser.add_argument("--backend", default="",
                        help="optional backend required before release")
    parser.add_argument("--start-position", nargs=3, type=float, metavar=("X", "Y", "Z"))
    parser.add_argument("--position-tolerance", type=float, default=2.0)
    args = parser.parse_args()
    if not 1 <= args.consecutive <= 100:
        parser.error("--consecutive must be in [1,100]")
    if not 1 <= args.seconds <= 600:
        parser.error("--seconds must be in [1,600]")
    if not 10 <= args.maximum_age_ms <= 2000:
        parser.error("--maximum-age-ms must be in [10,2000]")
    if not 0 < args.position_tolerance <= 1000:
        parser.error("--position-tolerance must be in (0,1000]")
    if args.barrier.exists():
        raise FileExistsError(f"barrier already exists: {args.barrier}")
    args.barrier.parent.mkdir(parents=True, exist_ok=True)
    deadline = time.perf_counter() + args.seconds
    consecutive = 0
    last_at = None
    accepted = None
    while time.perf_counter() < deadline:
        value = read_status(args.state_status, "alignment")
        phase = read_status(args.phase_status, "phase")
        if value and value.get("at") != last_at:
            last_at = value.get("at")
            phase_age = time.time() - float((phase or {}).get("at", 0))
            phase_ok = bool(phase and phase.get("phaseAligned") is True and
                            0 <= phase_age <= 1.5)
            identities = (value.get("referenceIdentity"), value.get("nativeIdentity"))
            backend_ok = not args.backend or all(
                (identity or {}).get("backendName") == args.backend for identity in identities)
            position_ok = True
            if args.start_position:
                expected = tuple(args.start_position)
                positions = tuple(position(identity) for identity in identities)
                position_ok = all(
                    actual is not None and
                    sum((actual[index] - expected[index]) ** 2 for index in range(3)) ** 0.5
                    <= args.position_tolerance
                    for actual in positions
                )
            if (aligned(value, args.maximum_age_ms / 1000.0) and phase_ok and
                    backend_ok and position_ok):
                consecutive += 1
                accepted = {"state": value, "phase": phase}
            else:
                consecutive = 0
                accepted = None
            if consecutive >= args.consecutive:
                break
        time.sleep(0.005)
    if consecutive < args.consecutive or accepted is None:
        print(json.dumps({"released": False, "reason": "alignment-timeout",
                          "consecutive": consecutive,
                          "lastStatusAt": last_at}, separators=(",", ":")))
        return 1
    payload = {
        "schema": 1,
        "releasedAt": time.time(),
        "alignmentAt": accepted["state"].get("at"),
        "phaseAt": accepted["phase"].get("at"),
        "baseline": accepted["state"].get("baseline"),
        "offsets": accepted["state"].get("offsets"),
        "phase": {
            "currentOffset": accepted["phase"].get("currentOffset"),
            "currentPhaseMedianMs": accepted["phase"].get("currentPhaseMedianMs"),
            "currentPhaseP95DeviationMs": accepted["phase"].get("currentPhaseP95DeviationMs"),
        },
        "consecutive": consecutive,
    }
    descriptor = os.open(args.barrier, os.O_WRONLY | os.O_CREAT | os.O_EXCL, 0o600)
    with os.fdopen(descriptor, "w", encoding="utf-8") as stream:
        json.dump(payload, stream, separators=(",", ":"))
        stream.write("\n")
    print(json.dumps({"released": True, "barrier": str(args.barrier),
                      **payload}, separators=(",", ":")))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
