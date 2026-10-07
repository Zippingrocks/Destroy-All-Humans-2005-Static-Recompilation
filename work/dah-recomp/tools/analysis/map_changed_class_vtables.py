#!/usr/bin/env python3
"""Rank retail vtables for alpha PDB classes whose class IDs changed.

This is an evidence generator. It does not rename retail functions. A result
becomes an accepted mapping only after the class ID, constructor/caller, object
layout and runtime object all agree.
"""

from __future__ import annotations

import argparse
import csv
import json
import re
from collections import defaultdict
from pathlib import Path

from compare_whole_alpha_retail import (
    all_instruction_addresses,
    augment_functions_with_pdb_starts,
    callback_table_targets,
    class_ids,
    dispatch_addresses,
    load_functions,
    load_named_symbols,
    parse_instructions,
    rank_candidate,
    return_immediate_entries,
    xbe_sections,
)


VFTABLE_RE = re.compile(r"^(?P<class>.+)::`vftable'$", re.IGNORECASE)


def va_dword(data: bytes, sections: list[dict], address: int) -> int | None:
    for section in sections:
        start = section["va"]
        file_end = start + section["fileSize"]
        if start <= address <= file_end - 4:
            offset = section["offset"] + address - start
            return int.from_bytes(data[offset:offset + 4], "little")
    return None


def vftable_symbols(symbol_path: Path) -> list[dict]:
    document = json.loads(symbol_path.read_text(encoding="utf-8"))
    rows = []
    for item in document["symbols"]:
        address = int(item["address"], 16)
        for name in item.get("names", []):
            match = VFTABLE_RE.match(name)
            if match:
                rows.append({"address": address, "class": match.group("class"), "name": name})
    return sorted(rows, key=lambda row: row["address"])


def alpha_vftable_slots(
    data: bytes,
    sections: list[dict],
    starts: set[int],
    symbols: list[dict],
    index: int,
    maximum: int = 128,
) -> list[int]:
    address = symbols[index]["address"]
    next_address = symbols[index + 1]["address"] if index + 1 < len(symbols) else address + maximum * 4
    slots = []
    while len(slots) < maximum and address + len(slots) * 4 < next_address:
        target = va_dword(data, sections, address + len(slots) * 4)
        if target not in starts:
            break
        slots.append(target)
    return slots


def retail_table_starts(data: bytes, sections: list[dict], starts: set[int]) -> list[int]:
    result = []
    for section in sections:
        if section["name"] != ".rdata":
            continue
        blob = data[section["offset"]:section["offset"] + section["fileSize"]]
        pointers = [int.from_bytes(blob[offset:offset + 4], "little") for offset in range(0, len(blob) - 3, 4)]
        for index in range(len(pointers) - 2):
            if pointers[index] in starts and pointers[index + 1] in starts and pointers[index + 2] in starts:
                result.append(section["va"] + index * 4)
    return result


def retail_slots(data: bytes, sections: list[dict], starts: set[int], address: int, count: int) -> list[int]:
    result = []
    for index in range(count):
        target = va_dword(data, sections, address + index * 4)
        if target not in starts:
            break
        result.append(target)
    return result


def class_name_from_virtual(name: str) -> str:
    return name.rsplit("::VirtualClassId", 1)[0]


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--retail-functions", required=True, type=Path)
    parser.add_argument("--retail-asm", required=True, type=Path)
    parser.add_argument("--retail-xbe", required=True, type=Path)
    parser.add_argument("--alpha-functions", required=True, type=Path)
    parser.add_argument("--alpha-asm", required=True, type=Path)
    parser.add_argument("--alpha-symbols", required=True, type=Path)
    parser.add_argument("--alpha-xbe", required=True, type=Path)
    parser.add_argument("--whole-function-map", required=True, type=Path)
    parser.add_argument("--recomp-generated-dispatch", type=Path)
    parser.add_argument("--recomp-manual", type=Path)
    parser.add_argument("--output", required=True, type=Path)
    args = parser.parse_args()

    retail = parse_instructions(args.retail_asm, load_functions(args.retail_functions))
    alpha_meta, _ = augment_functions_with_pdb_starts(
        load_functions(args.alpha_functions), args.alpha_symbols, args.alpha_xbe
    )
    alpha_all = parse_instructions(args.alpha_asm, alpha_meta)
    alpha_names = load_named_symbols(args.alpha_symbols)
    alpha_id_rows = class_ids(alpha_all, alpha_names)
    retail_instruction_addresses = all_instruction_addresses(args.retail_asm)
    retail_callback_rows, _ = callback_table_targets(
        args.retail_xbe, retail_instruction_addresses
    )
    retail_id_rows = return_immediate_entries(
        args.retail_asm, {row["target"] for row in retail_callback_rows}
    )
    retail_ids = {row["id"] for row in retail_id_rows}
    changed = [row for row in alpha_id_rows if row["id"] not in retail_ids]
    changed_classes = {
        class_name_from_virtual(name): row
        for row in changed
        for name in row["names"]
    }

    mapped_pairs: dict[tuple[int, int], tuple[str, float]] = {}
    with args.whole_function_map.open(newline="", encoding="utf-8") as stream:
        for row in csv.DictReader(stream):
            if not row["alphaAddress"]:
                continue
            if row["status"] not in {"exact-structural-candidate", "high-confidence-candidate"}:
                continue
            mapped_pairs[(int(row["retailAddress"], 16), int(row["alphaAddress"], 16))] = (
                row["status"], float(row["score"])
            )

    alpha_data, alpha_sections = xbe_sections(args.alpha_xbe)
    retail_data, retail_sections = xbe_sections(args.retail_xbe)
    symbols = vftable_symbols(args.alpha_symbols)
    alpha_starts = set(alpha_all)
    retail_starts = set(retail)
    candidates = retail_table_starts(retail_data, retail_sections, retail_starts)
    retail_id_by_address = {row["address"]: row["id"] for row in retail_id_rows}
    dispatchable = set()
    if args.recomp_generated_dispatch and args.recomp_manual:
        dispatchable = dispatch_addresses(args.recomp_generated_dispatch, args.recomp_manual)

    output_rows = []
    for symbol_index, symbol in enumerate(symbols):
        class_name = symbol["class"]
        if class_name not in changed_classes:
            continue
        alpha_slots = alpha_vftable_slots(
            alpha_data, alpha_sections, alpha_starts, symbols, symbol_index
        )
        if len(alpha_slots) < 3:
            continue
        virtual_address = changed_classes[class_name]["address"]
        class_slot = alpha_slots.index(virtual_address) if virtual_address in alpha_slots else None
        coarse_rankings = []
        for retail_table in candidates:
            rslots = retail_slots(
                retail_data, retail_sections, retail_starts, retail_table, len(alpha_slots)
            )
            if len(rslots) < min(3, len(alpha_slots)):
                continue
            exact = mapped = 0
            weighted = 0.0
            compared = min(len(alpha_slots), len(rslots))
            for alpha_target, retail_target in zip(alpha_slots, rslots):
                alpha_tokens = alpha_all[alpha_target]["tokens"]
                retail_tokens = retail[retail_target]["tokens"]
                if alpha_tokens and tuple(alpha_tokens) == tuple(retail_tokens):
                    exact += 1
                    weighted += 1.0
                elif (retail_target, alpha_target) in mapped_pairs:
                    mapped += 1
                    weighted += mapped_pairs[(retail_target, alpha_target)][1]
            if exact + mapped < 2:
                continue
            score = weighted / len(alpha_slots)
            retail_class_target = rslots[class_slot] if class_slot is not None and class_slot < len(rslots) else None
            if class_slot is not None and retail_class_target not in retail_id_by_address:
                continue
            coarse_rankings.append({
                "retailVtable": retail_table,
                "coarseScore": score,
                "exactSlots": exact,
                "mappedSlots": mapped,
                "comparedSlots": compared,
                "retailSlots": len(rslots),
                "retailClassIdFunction": retail_class_target,
                "retailClassId": retail_id_by_address.get(retail_class_target),
                "allTargetsDispatchable": bool(dispatchable) and all(target in dispatchable for target in rslots),
            })
        coarse_rankings.sort(key=lambda row: (-row["coarseScore"], -row["exactSlots"], row["retailVtable"]))
        rankings = []
        alpha_specific = []
        for alpha_target in alpha_slots:
            target_names = alpha_names.get(alpha_target, [])
            alpha_specific.append(
                len(target_names) <= 4 and any(
                    name.startswith(f"{class_name}::") for name in target_names
                )
            )
        for candidate in coarse_rankings[:256]:
            rslots = retail_slots(
                retail_data, retail_sections, retail_starts,
                candidate["retailVtable"], len(alpha_slots)
            )
            weighted = float(candidate["exactSlots"])
            fuzzy = 0
            specific_weighted = 0.0
            specific_matches = 0
            specific_total = sum(alpha_specific)
            for slot_index, (alpha_target, retail_target) in enumerate(zip(alpha_slots, rslots)):
                alpha_tokens = alpha_all[alpha_target]["tokens"]
                retail_tokens = retail[retail_target]["tokens"]
                # COMDAT folding gives generic no-op/accessor bodies dozens of
                # unrelated aliases. They are useful vtable-shape evidence but
                # cannot distinguish a derived class.
                is_specific = alpha_specific[slot_index]
                slot_score = 0.0
                if alpha_tokens and tuple(alpha_tokens) == tuple(retail_tokens):
                    slot_score = 1.0
                    if is_specific:
                        specific_weighted += slot_score
                        specific_matches += 1
                    continue
                pair = mapped_pairs.get((retail_target, alpha_target))
                if pair:
                    slot_score = pair[1]
                    weighted += slot_score
                    if is_specific:
                        specific_weighted += slot_score
                        specific_matches += 1
                    continue
                if len(alpha_tokens) < 4 or len(retail_tokens) < 4:
                    continue
                slot_score = rank_candidate(retail[retail_target], alpha_all[alpha_target])["score"]
                if slot_score >= 0.65:
                    fuzzy += 1
                    weighted += slot_score
                if is_specific and slot_score >= 0.55:
                    specific_weighted += slot_score
                    specific_matches += 1
            candidate["fuzzySlots"] = fuzzy
            candidate["specificSlots"] = specific_total
            candidate["specificMatches"] = specific_matches
            candidate["specificScore"] = specific_weighted / specific_total if specific_total else 0.0
            broad_score = weighted / len(alpha_slots)
            candidate["score"] = (
                0.75 * candidate["specificScore"] + 0.25 * broad_score
                if specific_total else broad_score
            )
            rankings.append(candidate)
        rankings.sort(key=lambda row: (-row["score"], -row["exactSlots"], row["retailVtable"]))
        for rank, candidate in enumerate(rankings[:5], 1):
            runner_up = rankings[1]["score"] if rank == 1 and len(rankings) > 1 else None
            output_rows.append({
                "class": class_name,
                "alphaClassId": f"0x{changed_classes[class_name]['id']:08X}",
                "alphaVtable": f"0x{symbol['address']:08X}",
                "alphaSlots": len(alpha_slots),
                "alphaClassIdSlot": "" if class_slot is None else f"0x{class_slot * 4:X}",
                "rank": rank,
                "retailVtable": f"0x{candidate['retailVtable']:08X}",
                "score": f"{candidate['score']:.6f}",
                "leadOverRunnerUp": f"{candidate['score'] - runner_up:.6f}" if runner_up is not None else "",
                "exactSlots": candidate["exactSlots"],
                "mappedSlots": candidate["mappedSlots"],
                "fuzzySlots": candidate["fuzzySlots"],
                "specificSlots": candidate["specificSlots"],
                "specificMatches": candidate["specificMatches"],
                "specificScore": f"{candidate['specificScore']:.6f}",
                "comparedSlots": candidate["comparedSlots"],
                "retailSlots": candidate["retailSlots"],
                "retailClassIdFunction": "" if candidate["retailClassIdFunction"] is None else f"0x{candidate['retailClassIdFunction']:08X}",
                "retailClassId": "" if candidate["retailClassId"] is None else f"0x{candidate['retailClassId']:08X}",
                "allTargetsDispatchable": int(candidate["allTargetsDispatchable"]),
            })

    args.output.parent.mkdir(parents=True, exist_ok=True)
    with args.output.open("w", newline="", encoding="utf-8") as stream:
        writer = csv.DictWriter(stream, fieldnames=list(output_rows[0]) if output_rows else [])
        writer.writeheader()
        writer.writerows(output_rows)
    print(json.dumps({
        "changedClasses": len(changed_classes),
        "alphaVtablesRanked": len({(row['class'], row['alphaVtable']) for row in output_rows}),
        "rows": len(output_rows),
        "output": str(args.output),
    }, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
