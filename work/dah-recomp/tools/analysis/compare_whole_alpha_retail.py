#!/usr/bin/env python3
"""Build a whole-executable alpha/retail comparison database.

The output is evidence, not an automatic retail symbol rename. Every retail
function is inventoried. Named alpha functions are ranked by normalized code
shape, while class IDs and NUL-terminated strings are compared independently.
"""

from __future__ import annotations

import argparse
import csv
import difflib
import hashlib
import json
import re
from collections import Counter, defaultdict
from pathlib import Path


INSN_RE = re.compile(r"^\s*0x([0-9A-Fa-f]+)\s+[0-9A-Fa-f]+\s+([a-z][a-z0-9]*)\s*(.*?)\s*$")
LARGE_HEX_RE = re.compile(r"(?<![A-Za-z0-9_])0x[0-9A-Fa-f]{5,}(?![A-Za-z0-9_])")
SPACE_RE = re.compile(r"\s+")
RETURN_ID_RE = re.compile(r"^0x([0-9A-Fa-f]+)$")
SYSTEM_PATTERNS = {
    "renderingGraphics": re.compile(r"render|display|texture|material|shader|mesh|model|camera|shadow|light|cull|draw|d3d", re.I),
    "physicsHavok": re.compile(r"havok|physics|rigid|collision|constraint|ragdoll|phantom|shape", re.I),
    "audioMovie": re.compile(r"audio|sound|music|movie|bink|xmv|voice|stream", re.I),
    "uiHudMenu": re.compile(r"menu|hud|widget|frontend|screen|font|text|gui", re.I),
    "missionScript": re.compile(r"mission|script|objective|event|trigger|state", re.I),
    "aiTraffic": re.compile(r"\bai\b|pedestrian|traffic|pathfind|navigation|brain|behavior|steer", re.I),
    "weaponsOrdnance": re.compile(r"weapon|projectile|ammo|zap|ray|beam|grenade|bullet|missile", re.I),
    "playerCharacterShip": re.compile(r"crypto|player|character|actor|saucer|ship|furon", re.I),
}


def file_hash(path: Path) -> str:
    h = hashlib.sha256()
    with path.open("rb") as stream:
        for chunk in iter(lambda: stream.read(1024 * 1024), b""):
            h.update(chunk)
    return h.hexdigest()


def input_hash(path: Path) -> str:
    if path.is_file():
        return file_hash(path)
    h = hashlib.sha256()
    for child in sorted(path.glob("*.asm"), key=lambda item: item.name.lower()):
        h.update(child.name.encode("utf-8"))
        h.update(bytes.fromhex(file_hash(child)))
    return h.hexdigest()


def normalize_operand(text: str) -> str:
    text = text.split(";", 1)[0].strip().lower()
    text = LARGE_HEX_RE.sub("addr", text)
    return SPACE_RE.sub("", text)


def load_functions(path: Path) -> list[dict]:
    return json.loads(path.read_text(encoding="utf-8"))


def parse_instructions(path: Path, functions: list[dict]) -> dict[int, dict]:
    ordered = sorted((int(f["start"], 16), int(f["end"], 16), f) for f in functions)
    by_start = {start: {"tokens": [], "mnemonics": [], "raw": [], "meta": meta}
                for start, _, meta in ordered}
    paths = sorted(path.glob("*.asm"), key=lambda item: item.name.lower()) if path.is_dir() else [path]
    for asm_path in paths:
        index = 0
        with asm_path.open("r", encoding="utf-8", errors="replace") as stream:
            for raw_line in stream:
                match = INSN_RE.match(raw_line.rstrip("\r\n"))
                if not match:
                    continue
                address = int(match.group(1), 16)
                while index < len(ordered) and address >= ordered[index][1]:
                    index += 1
                if index >= len(ordered):
                    break
                start, end, _ = ordered[index]
                if not (start <= address < end):
                    continue
                current = by_start[start]
                mnemonic = match.group(2).lower()
                operand = normalize_operand(match.group(3))
                current["mnemonics"].append(mnemonic)
                current["tokens"].append(f"{mnemonic}:{operand}")
                current["raw"].append((address, mnemonic, match.group(3).split(";", 1)[0].strip().lower()))
    return by_start


def load_named_symbols(path: Path) -> dict[int, list[str]]:
    document = json.loads(path.read_text(encoding="utf-8"))
    return {
        int(item["address"], 16): item["names"]
        for item in document["symbols"]
        if item.get("executable_section") and item.get("names")
    }


def ngrams(tokens: list[str], width: int = 3) -> set[tuple[str, ...]]:
    if len(tokens) < width:
        return set()
    return {tuple(tokens[i:i + width]) for i in range(len(tokens) - width + 1)}


def ratio(left: list[str], right: list[str]) -> float:
    return difflib.SequenceMatcher(None, left, right, autojunk=False).ratio()


def shape_ratio(left: int, right: int) -> float:
    if not left or not right:
        return 0.0
    return min(left, right) / max(left, right)


def call_count(item: dict) -> int:
    return sum(1 for mnemonic in item["mnemonics"] if mnemonic == "call")


def rank_candidate(retail: dict, alpha: dict) -> dict:
    mnemonic_score = ratio(retail["mnemonics"], alpha["mnemonics"])
    token_score = ratio(retail["tokens"], alpha["tokens"])
    instruction_shape = shape_ratio(len(retail["tokens"]), len(alpha["tokens"]))
    byte_shape = shape_ratio(int(retail["meta"]["size"]), int(alpha["meta"]["size"]))
    call_shape = shape_ratio(call_count(retail) + 1, call_count(alpha) + 1)
    score = (0.34 * mnemonic_score + 0.34 * token_score +
             0.13 * instruction_shape + 0.09 * byte_shape + 0.10 * call_shape)
    return {
        "score": score,
        "mnemonicScore": mnemonic_score,
        "tokenScore": token_score,
        "instructionShape": instruction_shape,
        "byteShape": byte_shape,
        "callShape": call_shape,
    }


def xbe_sections(path: Path) -> tuple[bytes, list[dict]]:
    data = path.read_bytes()
    base = int.from_bytes(data[0x104:0x108], "little")
    count = int.from_bytes(data[0x11C:0x120], "little")
    table = int.from_bytes(data[0x120:0x124], "little") - base
    sections = []
    for i in range(count):
        entry = table + i * 56
        name_ptr = int.from_bytes(data[entry + 20:entry + 24], "little") - base
        name = data[name_ptr:data.find(b"\0", name_ptr)].decode("ascii", errors="replace")
        sections.append({
            "name": name,
            "va": int.from_bytes(data[entry + 4:entry + 8], "little"),
            "virtualSize": int.from_bytes(data[entry + 8:entry + 12], "little"),
            "offset": int.from_bytes(data[entry + 12:entry + 16], "little"),
            "fileSize": int.from_bytes(data[entry + 16:entry + 20], "little"),
            "flags": int.from_bytes(data[entry:entry + 4], "little"),
        })
    return data, sections


def extract_strings(path: Path, minimum: int = 4) -> dict[str, list[int]]:
    data, sections = xbe_sections(path)
    found: dict[str, list[int]] = defaultdict(list)
    for section in sections:
        blob = data[section["offset"]:section["offset"] + section["fileSize"]]
        for match in re.finditer(rb"[\x20-\x7E]{%d,}\x00" % minimum, blob):
            value = match.group(0)[:-1].decode("ascii")
            found[value].append(section["va"] + match.start())
    return found


def content_inventory(root: Path) -> dict[str, dict]:
    result = {}
    for path in sorted(root.rglob("*")):
        if not path.is_file():
            continue
        relative = path.relative_to(root).as_posix()
        result[relative] = {
            "size": path.stat().st_size,
            "sha256": file_hash(path),
            "kind": "build-report" if any(tag in path.name for tag in (".builder_report.", ".linker_report.")) or path.suffix == ".txt" else "game-payload",
        }
    return result


def dispatch_addresses(generated_path: Path, manual_path: Path) -> set[int]:
    generated = generated_path.read_text(encoding="utf-8", errors="replace")
    manual = manual_path.read_text(encoding="utf-8", errors="replace")
    addresses = {
        int(value, 16)
        for value in re.findall(r"\{\s*0x([0-9A-Fa-f]{5,8})u,\s*\(recomp_func_t\)", generated)
    }
    addresses.update(
        int(value, 16)
        for value in re.findall(r"case\s+0x([0-9A-Fa-f]{5,8})u\s*:\s*return", manual, re.IGNORECASE)
    )
    addresses.update(
        int(value, 16)
        for value in re.findall(r"xbox_va\s*==\s*0x([0-9A-Fa-f]{5,8})u?", manual, re.IGNORECASE)
    )
    return addresses


def callback_table_targets(xbe_path: Path, instruction_addresses: set[int]) -> tuple[list[dict], int]:
    data, sections = xbe_sections(xbe_path)
    references: dict[int, list[tuple[str, int]]] = defaultdict(list)
    table_count = 0
    for section in sections:
        # Function-pointer arrays and C++ vtables live in the ordinary data
        # sections. Scanning executable sections mistakes switch jump tables
        # and embedded instruction words for callback registrations.
        if section["name"] not in {".rdata", ".data"}:
            continue
        blob = data[section["offset"]:section["offset"] + section["fileSize"]]
        run: list[tuple[int, int]] = []

        def flush() -> None:
            nonlocal table_count
            if len(run) < 3:
                return
            table_count += 1
            for location, target in run:
                references[target].append((section["name"], location))

        for offset in range(0, len(blob) - 3, 4):
            target = int.from_bytes(blob[offset:offset + 4], "little")
            location = section["va"] + offset
            if target in instruction_addresses:
                run.append((location, target))
            else:
                flush()
                run = []
        flush()
    rows = []
    for target, refs in sorted(references.items()):
        rows.append({
            "target": target,
            "referenceCount": len(refs),
            "tableLocations": " | ".join(f"{section}:0x{location:08X}" for section, location in refs),
        })
    return rows, table_count


def class_ids(functions: dict[int, dict], names: dict[int, list[str]] | None = None) -> list[dict]:
    rows = []
    for address, item in functions.items():
        raw = item["raw"]
        if len(raw) != 2 or raw[0][1] != "mov" or raw[1][1] != "ret":
            continue
        operands = [part.strip() for part in raw[0][2].split(",", 1)]
        if len(operands) != 2 or operands[0] != "eax":
            continue
        match = RETURN_ID_RE.match(operands[1])
        if not match:
            continue
        value = int(match.group(1), 16)
        row = {"address": address, "id": value}
        if names and address in names:
            virtual_names = [name for name in names[address] if "VirtualClassId" in name]
            if not virtual_names:
                continue
            row["names"] = virtual_names
        elif names:
            continue
        rows.append(row)
    return rows


def section_coverage(functions: dict[int, dict]) -> dict[str, dict[str, int]]:
    sections: dict[str, list[dict]] = defaultdict(list)
    for item in functions.values():
        sections[item["meta"]["section"]].append(item)
    return {
        section: {
            "discovered": len(items),
            "parsed": sum(bool(item["tokens"]) for item in items),
        }
        for section, items in sorted(sections.items())
    }


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--retail-functions", required=True, type=Path)
    parser.add_argument("--retail-asm", required=True, type=Path)
    parser.add_argument("--retail-xbe", required=True, type=Path)
    parser.add_argument("--alpha-functions", required=True, type=Path)
    parser.add_argument("--alpha-asm", required=True, type=Path)
    parser.add_argument("--alpha-symbols", required=True, type=Path)
    parser.add_argument("--alpha-xbe", required=True, type=Path)
    parser.add_argument("--retail-content-root", type=Path)
    parser.add_argument("--alpha-content-root", type=Path)
    parser.add_argument("--recomp-generated-dispatch", type=Path)
    parser.add_argument("--recomp-manual", type=Path)
    parser.add_argument("--output-directory", required=True, type=Path)
    args = parser.parse_args()

    retail_meta = load_functions(args.retail_functions)
    alpha_meta = load_functions(args.alpha_functions)
    retail = parse_instructions(args.retail_asm, retail_meta)
    alpha_all = parse_instructions(args.alpha_asm, alpha_meta)
    alpha_names = load_named_symbols(args.alpha_symbols)
    alpha = {address: item for address, item in alpha_all.items() if address in alpha_names}

    exact_index: dict[tuple[str, ...], list[int]] = defaultdict(list)
    grams_by_alpha: dict[int, set[tuple[str, ...]]] = {}
    gram_frequency: Counter = Counter()
    for address, item in alpha.items():
        exact_index[tuple(item["tokens"])].append(address)
        grams = ngrams(item["tokens"])
        grams_by_alpha[address] = grams
        gram_frequency.update(grams)
    inverted: dict[tuple[str, ...], list[int]] = defaultdict(list)
    for address, grams in grams_by_alpha.items():
        for gram in grams:
            if gram_frequency[gram] <= 48:
                inverted[gram].append(address)

    rows = []
    status_counts = Counter()
    for retail_address, item in sorted(retail.items()):
        tokens = item["tokens"]
        exact = exact_index.get(tuple(tokens), []) if tokens else []
        candidate_addresses: list[int]
        method = "none"
        if exact:
            candidate_addresses = exact
            method = "exact-normalized"
        elif len(tokens) >= 3:
            votes: Counter = Counter()
            for gram in ngrams(tokens):
                for address in inverted.get(gram, ()):
                    votes[address] += 1
            candidate_addresses = [
                address for address, _ in sorted(votes.items(), key=lambda pair: (-pair[1], pair[0]))[:32]
            ]
            method = "rare-ngram-fuzzy" if candidate_addresses else "none"
        else:
            candidate_addresses = []

        ranked = []
        for alpha_address in candidate_addresses:
            scores = rank_candidate(item, alpha[alpha_address])
            ranked.append((scores["score"], alpha_address, scores))
        ranked.sort(reverse=True)
        if ranked:
            score, alpha_address, scores = ranked[0]
            names = alpha_names[alpha_address]
            ambiguous = sum(1 for value, _, _ in ranked if score - value <= 0.015) > 1
            if method == "exact-normalized" and len(tokens) >= 4 and not ambiguous:
                status = "exact-structural-candidate"
            elif score >= 0.88 and len(tokens) >= 6 and not ambiguous:
                status = "high-confidence-candidate"
            elif score >= 0.70 and len(tokens) >= 5:
                status = "medium-candidate"
            else:
                status = "weak-or-ambiguous"
            row = {
                "retailAddress": f"0x{retail_address:08X}",
                "retailSection": item["meta"]["section"],
                "retailSize": item["meta"]["size"],
                "retailInstructions": len(tokens),
                "status": status,
                "method": method,
                "alphaAddress": f"0x{alpha_address:08X}",
                "alphaSection": alpha[alpha_address]["meta"]["section"],
                "alphaNames": " | ".join(names),
                **{key: f"{value:.6f}" for key, value in scores.items()},
                "ambiguous": int(ambiguous),
            }
        else:
            status = "no-named-alpha-candidate"
            row = {
                "retailAddress": f"0x{retail_address:08X}",
                "retailSection": item["meta"]["section"],
                "retailSize": item["meta"]["size"],
                "retailInstructions": len(tokens),
                "status": status,
                "method": method,
                "alphaAddress": "",
                "alphaSection": "",
                "alphaNames": "",
                "score": "",
                "mnemonicScore": "",
                "tokenScore": "",
                "instructionShape": "",
                "byteShape": "",
                "callShape": "",
                "ambiguous": 0,
            }
        rows.append(row)
        status_counts[status] += 1

    alpha_id_rows = class_ids(alpha_all, alpha_names)
    retail_id_rows = class_ids(retail)
    alpha_ids: dict[int, list[dict]] = defaultdict(list)
    retail_ids: dict[int, list[dict]] = defaultdict(list)
    for row in alpha_id_rows:
        alpha_ids[row["id"]].append(row)
    for row in retail_id_rows:
        retail_ids[row["id"]].append(row)
    class_rows = []
    for value in sorted(set(alpha_ids) | set(retail_ids)):
        arows, rrows = alpha_ids.get(value, []), retail_ids.get(value, [])
        class_rows.append({
            "classId": f"0x{value:08X}",
            "status": "shared" if arows and rrows else ("alpha-only" if arows else "retail-only"),
            "alphaNames": " | ".join(sorted({name for row in arows for name in row.get("names", [])})),
            "alphaAddresses": " | ".join(f"0x{row['address']:08X}" for row in arows),
            "retailAddresses": " | ".join(f"0x{row['address']:08X}" for row in rrows),
        })

    retail_strings = extract_strings(args.retail_xbe)
    alpha_strings = extract_strings(args.alpha_xbe)
    string_rows = []
    string_counts = Counter()
    for value in sorted(set(alpha_strings) | set(retail_strings), key=lambda text: (text.lower(), text)):
        in_alpha, in_retail = value in alpha_strings, value in retail_strings
        status = "shared" if in_alpha and in_retail else ("alpha-only" if in_alpha else "retail-only")
        string_counts[status] += 1
        string_rows.append({
            "status": status,
            "value": value,
            "alphaAddresses": " | ".join(f"0x{x:08X}" for x in alpha_strings.get(value, [])),
            "retailAddresses": " | ".join(f"0x{x:08X}" for x in retail_strings.get(value, [])),
        })

    content_rows = []
    content_counts = Counter()
    retail_content = alpha_content = None
    if args.retail_content_root and args.alpha_content_root:
        retail_content = content_inventory(args.retail_content_root)
        alpha_content = content_inventory(args.alpha_content_root)
        for relative in sorted(set(alpha_content) | set(retail_content), key=str.lower):
            alpha_item, retail_item = alpha_content.get(relative), retail_content.get(relative)
            if alpha_item and retail_item:
                status = "identical" if alpha_item["sha256"] == retail_item["sha256"] else "changed"
            else:
                status = "alpha-only" if alpha_item else "retail-only"
            content_counts[status] += 1
            content_rows.append({
                "path": relative,
                "status": status,
                "kind": (retail_item or alpha_item)["kind"],
                "alphaSize": alpha_item["size"] if alpha_item else "",
                "retailSize": retail_item["size"] if retail_item else "",
                "alphaSha256": alpha_item["sha256"] if alpha_item else "",
                "retailSha256": retail_item["sha256"] if retail_item else "",
            })

    callback_rows = []
    callback_table_count = 0
    if args.recomp_generated_dispatch and args.recomp_manual:
        instruction_addresses = {
            address for item in retail.values() for address, _, _ in item["raw"]
        }
        function_starts = set(retail)
        dispatchable = dispatch_addresses(args.recomp_generated_dispatch, args.recomp_manual)
        callback_rows, callback_table_count = callback_table_targets(args.retail_xbe, instruction_addresses)
        for row in callback_rows:
            target = row["target"]
            row["target"] = f"0x{target:08X}"
            is_function_start = target in function_starts
            is_dispatchable = target in dispatchable
            row["functionStart"] = int(is_function_start)
            row["dispatchable"] = int(is_dispatchable)
            if is_function_start:
                row["status"] = "covered-function-start" if is_dispatchable else "missing-function-start"
            else:
                row["status"] = "internal-target-covered" if is_dispatchable else "internal-target-candidate"

    args.output_directory.mkdir(parents=True, exist_ok=True)
    function_path = args.output_directory / "whole-function-map.csv"
    class_path = args.output_directory / "whole-class-id-map.csv"
    string_path = args.output_directory / "whole-string-map.csv"
    content_path = args.output_directory / "whole-content-map.csv"
    callback_path = args.output_directory / "whole-callback-target-map.csv"
    outputs = [(function_path, rows), (class_path, class_rows), (string_path, string_rows)]
    if content_rows:
        outputs.append((content_path, content_rows))
    if callback_rows:
        outputs.append((callback_path, callback_rows))
    for path, data in outputs:
        with path.open("w", newline="", encoding="utf-8") as stream:
            writer = csv.DictWriter(stream, fieldnames=list(data[0].keys()) if data else [])
            writer.writeheader()
            writer.writerows(data)

    summary = {
        "schema": 1,
        "warning": "Function matches are candidates until class/caller/vtable/runtime evidence accepts them.",
        "inputs": {
            name: {"path": path.name, "sha256": input_hash(path)}
            for name, path in {
                "retailFunctions": args.retail_functions,
                "retailAsm": args.retail_asm,
                "retailXbe": args.retail_xbe,
                "alphaFunctions": args.alpha_functions,
                "alphaAsm": args.alpha_asm,
                "alphaSymbols": args.alpha_symbols,
                "alphaXbe": args.alpha_xbe,
            }.items()
        },
        "functions": {
            "retailDiscovered": len(retail),
            "alphaDiscovered": len(alpha_all),
            "alphaNamedFunctionStarts": len(alpha),
            "retailUnparsed": sum(not item["tokens"] for item in retail.values()),
            "alphaUnparsed": sum(not item["tokens"] for item in alpha_all.values()),
            "retailBySection": section_coverage(retail),
            "alphaBySection": section_coverage(alpha_all),
            "statusCounts": dict(status_counts),
            "strongCandidateSystems": {
                category: sum(
                    row["status"] in {"exact-structural-candidate", "high-confidence-candidate"}
                    and bool(pattern.search(row["alphaNames"]))
                    for row in rows
                )
                for category, pattern in SYSTEM_PATTERNS.items()
            },
            "database": function_path.name,
        },
        "classIds": {
            "alphaNamed": len(alpha_id_rows),
            "retailReturnImmediateCandidates": len(retail_id_rows),
            "statusCounts": dict(Counter(row["status"] for row in class_rows)),
            "database": class_path.name,
        },
        "strings": {
            "alphaUnique": len(alpha_strings),
            "retailUnique": len(retail_strings),
            "statusCounts": dict(string_counts),
            "database": string_path.name,
        },
    }
    if content_rows:
        summary["content"] = {
            "alphaFiles": len(alpha_content),
            "retailFiles": len(retail_content),
            "alphaBytes": sum(item["size"] for item in alpha_content.values()),
            "retailBytes": sum(item["size"] for item in retail_content.values()),
            "statusCounts": dict(content_counts),
            "gamePayloadStatusCounts": dict(Counter(
                row["status"] for row in content_rows if row["kind"] == "game-payload"
            )),
            "buildReportStatusCounts": dict(Counter(
                row["status"] for row in content_rows if row["kind"] == "build-report"
            )),
            "database": content_path.name,
        }
    if callback_rows:
        callback_statuses = Counter(row["status"] for row in callback_rows)
        summary["callbackTables"] = {
            "scannedSections": [".rdata", ".data"],
            "candidateTables": callback_table_count,
            "uniqueTargets": len(callback_rows),
            "functionStartTargets": sum(row["functionStart"] for row in callback_rows),
            "coveredFunctionStarts": callback_statuses["covered-function-start"],
            "missingFunctionStarts": callback_statuses["missing-function-start"],
            "internalTargets": sum(not row["functionStart"] for row in callback_rows),
            "coveredInternalTargets": callback_statuses["internal-target-covered"],
            "internalTargetCandidates": callback_statuses["internal-target-candidate"],
            "statusCounts": dict(callback_statuses),
            "database": callback_path.name,
        }
    summary_path = args.output_directory / "whole-comparison-summary.json"
    summary_path.write_text(json.dumps(summary, indent=2) + "\n", encoding="utf-8")
    print(json.dumps(summary, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
