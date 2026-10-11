"""Reconcile the saved retail callback map with the current recomp dispatch.

The broad pointer scan includes data that merely resembles function pointers.
This audit narrows it to the retail class-vtable region and records whether a
candidate begins after INT3 padding, which is strong function-entry evidence.
It does not generate or dispatch code.
"""

import argparse
import csv
import json
import re
from pathlib import Path


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--output", type=Path)
    args = parser.parse_args()

    repo = Path(__file__).resolve().parents[1]
    workspace = Path(__file__).resolve().parents[3]
    map_path = repo / "tools/analysis/results/whole-alpha-retail/whole-callback-target-map.csv"
    dispatch_text = (
        (repo / "src/recomp_manual.c").read_text(encoding="utf-8", errors="replace")
        + "\n"
        + (repo / "src/recomp/gen/recomp_dispatch.c").read_text(
            encoding="utf-8", errors="replace"
        )
    )
    generated_text = "\n".join(
        path.read_text(encoding="utf-8", errors="replace")
        for path in (repo / "src/recomp/gen").glob("*.c")
    )
    generated_bodies = {
        int(value, 16)
        for value in re.findall(
            r"^void\s+sub_([0-9A-Fa-f]{8})\s*\(void\)\s*$",
            generated_text,
            re.MULTILINE,
        )
    }
    asm_lines = (workspace / "work/disasm-seeded/asm/text.asm").read_text(
        encoding="utf-8", errors="replace"
    ).splitlines()
    instruction_re = re.compile(
        r"^\s*0x([0-9A-Fa-f]{8})\s+[0-9A-Fa-f]+\s+([A-Za-z0-9]+)"
    )
    instructions = []
    for line in asm_lines:
        match = instruction_re.match(line)
        if match:
            instructions.append((int(match.group(1), 16), match.group(2).lower()))
    instruction_index = {address: index for index, (address, _) in enumerate(instructions)}

    functions = json.loads((workspace / "work/disasm-seeded/functions.json").read_text())
    discovered_starts = {int(row["start"], 16) for row in functions}
    candidates = []
    with map_path.open(newline="", encoding="utf-8") as source:
        for row in csv.DictReader(source):
            if row["status"] != "internal-target-candidate":
                continue
            address = int(row["target"], 16)
            token = re.compile(rf"0x{address:08X}u", re.IGNORECASE)
            if token.search(dispatch_text):
                continue
            body_present = address in generated_bodies
            locations = [
                int(value, 16)
                for value in re.findall(r"0x([0-9A-Fa-f]+)", row["tableLocations"])
            ]
            vtable_locations = [
                location for location in locations if 0x00225000 <= location < 0x0023B000
            ]
            if not vtable_locations:
                continue
            index = instruction_index.get(address)
            previous_is_padding = bool(
                index is not None and index > 0 and instructions[index - 1][1] == "int3"
            )
            end = None
            terminal = None
            if index is not None:
                cursor = index
                while cursor < len(instructions) and instructions[cursor][1] != "int3":
                    cursor += 1
                if cursor < len(instructions) and cursor > index:
                    end = instructions[cursor][0]
                    terminal = instructions[cursor - 1][1]
            candidates.append({
                "address": f"0x{address:08X}",
                "references": int(row["referenceCount"]),
                "vtableLocations": [f"0x{location:08X}" for location in vtable_locations],
                "instructionBoundary": index is not None,
                "precededByInt3": previous_is_padding,
                "alreadyDiscovered": address in discovered_starts,
                "bodyPresent": body_present,
                "inferredEnd": f"0x{end:08X}" if end is not None else None,
                "byteLength": end - address if end is not None else None,
                "terminalMnemonic": terminal,
                "safeLiftCandidate": bool(
                    previous_is_padding
                    and end is not None
                    and terminal in {"ret", "jmp"}
                    and end > address
                    and not body_present
                ),
            })

    candidates.sort(
        key=lambda row: (
            not row["precededByInt3"],
            not row["instructionBoundary"],
            int(row["address"], 16),
        )
    )
    report = {
        "schema": 1,
        "source": map_path.relative_to(workspace).as_posix(),
        "currentUndispatchedVtableCandidates": len(candidates),
        "strongBoundaryCandidates": sum(row["precededByInt3"] for row in candidates),
        "safeLiftCandidates": sum(row["safeLiftCandidate"] for row in candidates),
        "candidates": candidates,
    }
    if args.output:
        args.output.parent.mkdir(parents=True, exist_ok=True)
        args.output.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(json.dumps(report, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
