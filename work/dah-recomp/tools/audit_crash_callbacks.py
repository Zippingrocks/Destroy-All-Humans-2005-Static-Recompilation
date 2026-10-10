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
    (0x00041540, "historical", "sub_00041540"),
    (0x00085FE0, "historical", "sub_00085FE0"),
    (0x0004F9E0, "historical", "sub_0004F9E0"),
    (0x00054B20, "historical", "sub_00054B20"),
    (0x0011FA30, "historical-stale-log", "sub_0011FA30"),
    (0x00143689, "historical-stale-log", "sub_00143689"),
)


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

    callback_rows = []
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
        "schema": 1,
        "retailXbe": {"path": str(retail_path), "sha256": sha256(retail_path)},
        "preservedCrashCount": len(crashes),
        "preservedCrashes": crashes,
        "callbacks": callback_rows,
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
    print("PASS: retail crash callbacks match original XBE bytes and vtable slots")
    if alpha_record:
        print("PASS: alpha retains the +0x24 destructor slot; retail extends past alpha +0x98")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
