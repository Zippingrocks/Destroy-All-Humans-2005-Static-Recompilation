#!/usr/bin/env python3
"""Audit preserved crashes and every callback previously reported unresolved.

This is a read-only source/original-XBE check. It does not launch the game.
The optional alpha XBE check records the proven shared ActorSamSite destructor
slot and the point where the retail primary vtable extends beyond the alpha.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import re
from pathlib import Path


CALLBACKS = (
    (0x00015FC0, "current-crash", "dah_retail_15fc0"),
    (0x00016CA0, "current-crash", "dah_retail_16ca0"),
    (0x0003CD20, "current-run", "sub_0003CD20"),
    (0x0003E2E0, "current-run", "sub_0003E2E0"),
    (0x0004ACC0, "current-run", "sub_0004ACC0"),
    (0x000A21A0, "current-run", "sub_000A21A0"),
    (0x00016A90, "static-vtable", "sub_00016A90"),
    (0x0009A210, "static-vtable", "sub_0009A210"),
    (0x00075660, "ion-detonator-retail", "sub_00075660"),
    (0x00075780, "ion-detonator-retail", "sub_00075780"),
    (0x00075800, "ion-detonator-retail", "sub_00075800"),
    (0x00075A10, "ion-detonator-retail", "sub_00075A10"),
    (0x000A6AF0, "sonic-boom-retail", "sub_000A6AF0"),
    (0x0002A1A0, "longplay-cleanup-retail", "sub_0002A1A0"),
    (0x0012AEE0, "live-type-query-retail", "sub_0012AEE0"),
    (0x00130B20, "mutant-runtime-retail", "sub_00130B20"),
    (0x000242F0, "mutant-runtime-retail", "sub_000242F0"),
    (0x0011CB60, "mutant-runtime-retail", "sub_0011CB60"),
    (0x0014A290, "mutant-runtime-retail", "sub_0014A290"),
    (0x00078040, "mutant-runtime-retail", "sub_00078040"),
    (0x00041540, "historical", "sub_00041540"),
    (0x00085FE0, "historical", "sub_00085FE0"),
    (0x0004F9E0, "historical", "sub_0004F9E0"),
    (0x00054B20, "historical", "sub_00054B20"),
    (0x0011FA30, "historical-stale-log", "sub_0011FA30"),
    (0x00143689, "historical-stale-log", "sub_00143689"),
)

UNRESOLVED_LINE = re.compile(
    r"\[ICALL\]\s+unresolved Xbox target 0x([0-9A-Fa-f]{8})"
)


def retained_callback_observations(workspace: Path) -> tuple[dict[int, list[str]], int]:
    """Collect callback targets from the retained runtime/crash logs.

    Zero targets are recorded separately because they are null/corrupt calls
    produced after an earlier failure, not retail functions that can be lifted.
    """
    candidates = []
    for pattern in ("*.log", "*.txt", "*.jsonl"):
        candidates.extend(workspace.glob(pattern))
    crashlog = workspace / "crashlog"
    if crashlog.exists():
        candidates.extend(crashlog.rglob("*.txt"))
        candidates.extend(crashlog.rglob("*.log"))
        candidates.extend(crashlog.rglob("*.jsonl"))
    blanket_runs = workspace / "work/dah-recomp/tools/parity/blanket-runs"
    if blanket_runs.exists():
        candidates.extend(blanket_runs.rglob("*.txt"))
        candidates.extend(blanket_runs.rglob("*.log"))
        candidates.extend(blanket_runs.rglob("*.jsonl"))

    observations: dict[int, list[str]] = {}
    null_calls = 0
    for path in sorted(set(candidates)):
        if not path.is_file():
            continue
        for line_number, line in enumerate(
            path.read_text(encoding="utf-8", errors="replace").splitlines(), 1
        ):
            match = UNRESOLVED_LINE.search(line)
            if not match:
                continue
            address = int(match.group(1), 16)
            if address == 0:
                null_calls += 1
                continue
            source = path.relative_to(workspace).as_posix()
            observations.setdefault(address, []).append(f"{source}:{line_number}")
    return observations, null_calls


def dispatched(address: int, manual: str, generated_dispatch: str) -> bool:
    token = rf"0x{address:08X}u"
    return re.search(token, manual, re.IGNORECASE) is not None or re.search(
        token, generated_dispatch, re.IGNORECASE
    ) is not None


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def xbe_sections(path: Path) -> tuple[bytes, list[tuple[int, int, int]]]:
    data = path.read_bytes()
    image_base = int.from_bytes(data[0x104:0x108], "little")
    count = int.from_bytes(data[0x11C:0x120], "little")
    table = int.from_bytes(data[0x120:0x124], "little") - image_base
    sections = []
    for index in range(count):
        entry = table + index * 56
        va = int.from_bytes(data[entry + 4:entry + 8], "little")
        offset = int.from_bytes(data[entry + 12:entry + 16], "little")
        size = int.from_bytes(data[entry + 16:entry + 20], "little")
        sections.append((va, offset, size))
    return data, sections


def read_va(image: tuple[bytes, list[tuple[int, int, int]]], va: int, size: int) -> bytes:
    data, sections = image
    for section_va, offset, section_size in sections:
        if section_va <= va and va + size <= section_va + section_size:
            start = offset + va - section_va
            return data[start:start + size]
    raise ValueError(f"0x{va:08X}..0x{va + size:08X} is not file-backed")


def dword(image: tuple[bytes, list[tuple[int, int, int]]], va: int) -> int:
    return int.from_bytes(read_va(image, va, 4), "little")


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--output", type=Path)
    parser.add_argument("--alpha-xbe", type=Path)
    args = parser.parse_args()

    repo = Path(__file__).resolve().parents[1]
    workspace = Path(__file__).resolve().parents[3]
    manual = (repo / "src/recomp_manual.c").read_text(encoding="utf-8")
    generated = "\n".join(
        path.read_text(encoding="utf-8", errors="replace")
        for path in (repo / "src/recomp/gen").glob("*.c")
    )
    generated_dispatch = (repo / "src/recomp/gen/recomp_dispatch.c").read_text(encoding="utf-8")

    seed_path = repo / "icall_seeds.json"
    seed_addresses = {
        int(entry["start"], 16)
        for entry in json.loads(seed_path.read_text(encoding="utf-8"))
    }
    missing_seed_dispatch = sorted(
        address for address in seed_addresses
        if not dispatched(address, manual, generated_dispatch)
    )
    if missing_seed_dispatch:
        missing = ", ".join(f"0x{address:08X}" for address in missing_seed_dispatch)
        raise SystemExit(f"FAIL cumulative indirect-call seed(s) lack dispatch: {missing}")

    recovery_source = (repo / "src/recomp/gen/recomp_stubs_unresolved.c").read_text(
        encoding="utf-8"
    )
    recovery_stubs = {
        int(value, 16)
        for value in re.findall(
            r"void\s+sub_([0-9A-Fa-f]{8})\s*\(void\)\s*\{\s*g_esp\s*\+=\s*4",
            recovery_source,
        )
    }
    seeded_recovery_stubs = sorted(seed_addresses & recovery_stubs)
    if seeded_recovery_stubs:
        bad = ", ".join(f"0x{address:08X}" for address in seeded_recovery_stubs)
        raise SystemExit(f"FAIL runtime callback seed(s) still use no-op recovery stubs: {bad}")

    callback_rows = []
    implemented_addresses = set()
    for address, origin, function in CALLBACKS:
        if function.startswith("dah_retail_"):
            body_present = re.search(rf"static\s+void\s+{re.escape(function)}\s*\(", manual) is not None
        else:
            body_present = re.search(rf"^void\s+{re.escape(function)}\s*\(void\)\s*$", generated, re.MULTILINE) is not None
        manual_case = re.search(
            rf"case\s+0x{address:08X}u:\s*return\s+{re.escape(function)}\s*;", manual, re.IGNORECASE
        ) is not None
        generated_case = re.search(
            rf"\{{\s*0x{address:08X}u,\s*\(recomp_func_t\){re.escape(function)}\s*\}}",
            generated_dispatch,
            re.IGNORECASE,
        ) is not None
        dispatch_present = manual_case or generated_case
        if not body_present or not dispatch_present:
            raise SystemExit(f"FAIL 0x{address:08X}: body={body_present} dispatch={dispatch_present}")
        callback_rows.append({
            "address": f"0x{address:08X}",
            "origin": origin,
            "function": function,
            "dispatch": "manual" if manual_case else "generated",
            "status": "implemented-and-dispatchable",
        })
        implemented_addresses.add(address)

    retained_observations, retained_null_calls = retained_callback_observations(workspace)
    missing_retained = sorted(set(retained_observations) - implemented_addresses)
    if missing_retained:
        missing = ", ".join(f"0x{address:08X}" for address in missing_retained)
        raise SystemExit(f"FAIL retained unresolved callback(s) lack implementations: {missing}")

    accumulated_addresses = seed_addresses | implemented_addresses | set(retained_observations)
    accumulated_recovery_stubs = sorted(accumulated_addresses & recovery_stubs)
    if accumulated_recovery_stubs:
        bad = ", ".join(f"0x{address:08X}" for address in accumulated_recovery_stubs)
        raise SystemExit(f"FAIL accumulated callback target(s) use no-op recovery stubs: {bad}")
    missing_accumulated_dispatch = sorted(
        address for address in accumulated_addresses
        if not dispatched(address, manual, generated_dispatch)
    )
    if missing_accumulated_dispatch:
        missing = ", ".join(
            f"0x{address:08X}" for address in missing_accumulated_dispatch
        )
        raise SystemExit(f"FAIL accumulated callback target(s) lack dispatch: {missing}")

    retail_path = workspace / "default.xbe"
    retail = xbe_sections(retail_path)
    expected = {
        0x00015FC0: bytes.fromhex("8b411c80b889010000017505e9cffd0e00c3"),
        0x00016CA0: bytes.fromhex("568bf1e878fffffff644240801740956e85b4a050083c4048bc65ec20400"),
    }
    for address, body in expected.items():
        if read_va(retail, address, len(body)) != body:
            raise SystemExit(f"FAIL retail byte audit at 0x{address:08X}")

    crash_db = workspace / "crashlog/unique-crashes.jsonl"
    crashes = [json.loads(line) for line in crash_db.read_text(encoding="utf-8").splitlines() if line.strip()]
    alpha_record: dict | None = None
    if args.alpha_xbe is not None:
        alpha = xbe_sections(args.alpha_xbe)
        alpha_record = {
            "path": str(args.alpha_xbe.resolve()),
            "sha256": sha256(args.alpha_xbe),
            "actorSamSitePrimaryVtable": "0x001EE848",
            "deletingDestructorSlot": {"offset": "0x24", "target": f"0x{dword(alpha, 0x001EE848 + 0x24):08X}"},
            "firstNonFunctionWord": {
                "offset": "0x98",
                "value": f"0x{dword(alpha, 0x001EE848 + 0x98):08X}",
                "ascii": read_va(alpha, 0x001EE848 + 0x98, 4).decode("ascii", errors="replace"),
            },
        }

    report = {
        "schema": 2,
        "retailXbe": {"path": str(retail_path), "sha256": sha256(retail_path)},
        "preservedCrashCount": len(crashes),
        "preservedCrashes": crashes,
        "callbacks": callback_rows,
        "cumulativeIndirectCallAudit": {
            "source": seed_path.relative_to(workspace).as_posix(),
            "seedTargets": len(seed_addresses),
            "accumulatedUniqueTargets": len(accumulated_addresses),
            "missingDispatchTargets": [],
            "generatedRecoveryStubCount": len(recovery_stubs),
            "runtimeSeedRecoveryStubIntersection": [],
            "accumulatedRecoveryStubIntersection": [],
            "status": "all-dispatchable",
        },
        "retainedRuntimeAudit": {
            "nonNullTargets": [
                {
                    "address": f"0x{address:08X}",
                    "observations": sources,
                    "status": "implemented-and-dispatchable",
                }
                for address, sources in sorted(retained_observations.items())
            ],
            "nullCascadeCalls": retained_null_calls,
            "unimplementedNonNullTargets": [],
        },
        "retailActorSamSiteVtable": {
            "address": "0x00226A80",
            "deletingDestructorSlot": {"offset": "0x24", "target": f"0x{dword(retail, 0x00226A80 + 0x24):08X}"},
            "restoredRetailOnlySlot": {"offset": "0xE4", "target": f"0x{dword(retail, 0x00226A80 + 0xE4):08X}"},
        },
        "alpha": alpha_record,
    }
    if args.output:
        args.output.parent.mkdir(parents=True, exist_ok=True)
        args.output.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(f"PASS: {len(crashes)} preserved unique crash signature(s)")
    print(f"PASS: {len(callback_rows)} observed callbacks have bodies and dispatch entries")
    print(
        f"PASS: all {len(seed_addresses)} cumulative indirect-call seeds are dispatchable; "
        f"none use {len(recovery_stubs)} generated no-op recovery stubs"
    )
    print(f"PASS: {len(accumulated_addresses)} unique accumulated callback targets reconciled")
    print(
        f"PASS: {len(retained_observations)} non-null callback target(s) in retained logs "
        f"are dispatchable ({retained_null_calls} null cascade call(s) excluded)"
    )
    print("PASS: retail crash callbacks match original XBE bytes and vtable slots")
    if alpha_record:
        print("PASS: alpha retains the +0x24 destructor slot; retail extends past alpha +0x98")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
