"""Compare observed Farm trajectories without equating host time or heap pointers.

World-tick alignment is a diagnostic hypothesis, not proof that the two observer
phases are equivalent. Preserve phase labels and report raw float bits first.
"""
import argparse
import json
import math
from pathlib import Path
import struct

FARM = "blocks\\sites\\farm"
FIELDS = ("worldElapsedBits", "worldStepBits", "worldPaused", "worldRealtime",
          "rngState", "cameraUpdate", "actorPositionBits", "moveState",
          "cameraLocalBits", "cameraQuatBits", "cameraWorldBits")


def rows(path):
    data = Path(path).read_bytes()
    result = []
    incomplete_tail = False
    for index, line in enumerate(data.splitlines()):
        if not line.strip():
            continue
        try:
            result.append(json.loads(line))
        except json.JSONDecodeError:
            if index == len(data.splitlines()) - 1 and not data.endswith(b"\n"):
                incomplete_tail = True
            else:
                raise
    return result, incomplete_tail


def active(row, name):
    return any(item.get("name") == name and item.get("active")
               for item in row.get("ui", []))


def describe(samples):
    farm = [r for r in samples if r.get("backendName") == FARM]
    def first(predicate):
        row = next((r for r in samples if predicate(r)), None)
        if row is None:
            return None
        return {k: row.get(k) for k in ("loop", "hostFrame", "worldTick", "phase")}
    held = [r for r in samples if r.get("observer", {}).get("presentationHeld")]
    return {
        "samples": len(samples), "farmSamples": len(farm),
        "phases": sorted({r.get("phase", "unknown") for r in samples}),
        "firstPendingFarm": first(lambda r: r.get("pendingBackendName") == FARM),
        "firstCommittedFarm": first(lambda r: r.get("backendName") == FARM and
                                    r.get("backendState") == 22 and not r.get("pendingBackend")),
        "firstFarmCinematicUi": first(lambda r: r.get("backendName") == FARM and active(r, "cinematic")),
        "firstFarmMainUi": first(lambda r: r.get("backendName") == FARM and active(r, "main")),
        "presentationHold": {"observedSamples": len(held),
                             "firstLoop": held[0]["loop"] if held else None,
                             "lastLoop": held[-1]["loop"] if held else None},
        "farmStepBits": sorted({r["worldStepBits"] for r in farm if r.get("worldStepBits") is not None}),
    }


def by_tick(samples):
    ticks = {}
    for row in samples:
        tick = row.get("worldTick")
        if (row.get("backendName") == FARM and row.get("backendState") == 22
                and row.get("worldPaused") == 0 and isinstance(tick, int) and tick > 0):
            ticks.setdefault(tick, row)
    return ticks


def float_difference(left, right):
    values = zip(left, right) if isinstance(left, list) and isinstance(right, list) else [(left, right)]
    maximum = 0.0
    for a, b in values:
        af = struct.unpack("<f", struct.pack("<I", a))[0]
        bf = struct.unpack("<f", struct.pack("<I", b))[0]
        if not math.isfinite(af) or not math.isfinite(bf):
            return None
        maximum = max(maximum, abs(af - bf))
    return maximum


def compare(reference, native):
    a, b = by_tick(reference), by_tick(native)
    ticks = sorted(a.keys() & b.keys())
    fields = {}
    for field in FIELDS:
        count = equal = 0
        first_mismatch = None
        maximum = 0.0
        for tick in ticks:
            av, bv = a[tick].get(field), b[tick].get(field)
            if av is None or bv is None:
                continue
            count += 1
            equal += av == bv
            if av != bv and first_mismatch is None:
                first_mismatch = {"worldTick": tick, "referenceLoop": a[tick]["loop"],
                                  "nativeLoop": b[tick]["loop"], "reference": av, "native": bv}
            if field.endswith("Bits"):
                delta = float_difference(av, bv)
                if delta is not None:
                    maximum = max(maximum, delta)
        fields[field] = {"compared": count, "bitExact": equal, "firstMismatch": first_mismatch}
        if field.endswith("Bits"):
            fields[field]["maxAbsoluteFloatDifference"] = maximum if count else None
    return {"schema": 1, "timingVerified": False, "pixelAccuracyVerified": False,
            "phaseAlignmentVerified": False,
            "alignment": "first unpaused committed Farm observation at each positive worldTick",
            "limitations": ["Different observer phases can change values within the same tick.",
                            "Debugger stops, readbacks and state logging perturb timing.",
                            "Equal state fields do not prove equal rendering or accepted input."],
            "reference": describe(reference), "native": describe(native),
            "commonWorldTicks": len(ticks),
            "worldTickRange": [ticks[0], ticks[-1]] if ticks else None, "fields": fields}


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("reference")
    parser.add_argument("native")
    parser.add_argument("--out", required=True)
    args = parser.parse_args()
    reference, reference_tail = rows(args.reference)
    native, native_tail = rows(args.native)
    report = compare(reference, native)
    report["inputs"] = {"reference": str(Path(args.reference).resolve()),
                        "native": str(Path(args.native).resolve()),
                        "incompleteReferenceTail": reference_tail, "incompleteNativeTail": native_tail}
    with open(args.out, "x", encoding="utf-8") as output:
        json.dump(report, output, indent=2)
        output.write("\n")
    print(json.dumps({"out": args.out, "commonWorldTicks": report["commonWorldTicks"],
                      "phaseAlignmentVerified": False, "timingVerified": False}))
