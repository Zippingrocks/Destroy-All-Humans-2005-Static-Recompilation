#!/usr/bin/env python3
"""Rank named alpha functions as candidates for one retail DAH function.

This is deliberately an evidence generator, not an automatic renamer.  It
compares normalized instruction streams and simple function-shape metadata.
Addresses and immediates are removed so that moved globals and calls do not
destroy a match, while register names and memory-field offsets remain visible.
The JSON output records every input hash so a result can be reproduced later.
"""

from __future__ import annotations

import argparse
import difflib
import hashlib
import json
import re
from pathlib import Path


FUNCTION_RE = re.compile(r"^; Function: (\S+)$")
START_RE = re.compile(r"^; Start: (0x[0-9A-Fa-f]+)\s+End: (0x[0-9A-Fa-f]+)")
INSTRUCTION_RE = re.compile(
    r"^\s*(0x[0-9A-Fa-f]+)\s+[0-9A-Fa-f]+\s+([a-z][a-z0-9]*)\s*(.*?)\s*$"
)
HEX_RE = re.compile(r"(?<![A-Za-z0-9_])(?:0x)?[0-9A-Fa-f]{5,}(?![A-Za-z0-9_])")
SHORT_NUMBER_RE = re.compile(r"(?<![A-Za-z0-9_])(?:0x[0-9A-Fa-f]+|\d+)(?![A-Za-z0-9_])")
SPACE_RE = re.compile(r"\s+")


def sha256(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        for chunk in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(chunk)
    return digest.hexdigest()


def normalize_operand(operand: str) -> str:
    operand = operand.split(";", 1)[0].strip().lower()
    operand = HEX_RE.sub("addr", operand)
    operand = SHORT_NUMBER_RE.sub("n", operand)
    return SPACE_RE.sub("", operand)


def parse_asm(path: Path) -> dict[int, dict]:
    functions: dict[int, dict] = {}
    pending_name: str | None = None
    current: dict | None = None
    with path.open("r", encoding="utf-8", errors="replace") as stream:
        for raw in stream:
            line = raw.rstrip("\r\n")
            match = FUNCTION_RE.match(line)
            if match:
                pending_name = match.group(1)
                current = None
                continue
            match = START_RE.match(line)
            if match and pending_name:
                start = int(match.group(1), 16)
                current = {
                    "start": start,
                    "end": int(match.group(2), 16),
                    "name": pending_name,
                    "tokens": [],
                    "mnemonics": [],
                }
                functions[start] = current
                continue
            match = INSTRUCTION_RE.match(line)
            if match and current is not None:
                mnemonic = match.group(2).lower()
                operand = normalize_operand(match.group(3))
                current["mnemonics"].append(mnemonic)
                current["tokens"].append(f"{mnemonic}:{operand}")
    return functions


def parse_asm_range(path: Path, start: int, end: int) -> dict:
    """Parse an exact instruction range even when function discovery missed it."""
    tokens: list[str] = []
    mnemonics: list[str] = []
    with path.open("r", encoding="utf-8", errors="replace") as stream:
        for raw in stream:
            match = INSTRUCTION_RE.match(raw.rstrip("\r\n"))
            if not match:
                continue
            address = int(match.group(1), 16)
            if address < start:
                continue
            if address >= end:
                break
            mnemonic = match.group(2).lower()
            operand = normalize_operand(match.group(3))
            mnemonics.append(mnemonic)
            tokens.append(f"{mnemonic}:{operand}")
    if not tokens:
        raise SystemExit(
            f"retail range 0x{start:08X}..0x{end:08X} has no parsed instructions"
        )
    return {
        "start": start,
        "end": end,
        "name": f"sub_{start:08X}",
        "tokens": tokens,
        "mnemonics": mnemonics,
    }


def load_function_metadata(path: Path) -> dict[int, dict]:
    return {int(item["start"], 16): item for item in json.loads(path.read_text(encoding="utf-8"))}


def load_symbols(path: Path) -> dict[int, list[str]]:
    document = json.loads(path.read_text(encoding="utf-8"))
    return {
        int(item["address"], 16): item["names"]
        for item in document["symbols"]
        if item.get("executable_section")
    }


def ratio(left: list[str], right: list[str]) -> float:
    return difflib.SequenceMatcher(None, left, right, autojunk=False).ratio()


def shape_ratio(left: int, right: int) -> float:
    if not left or not right:
        return 0.0
    return min(left, right) / max(left, right)


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--retail-address", required=True, type=lambda value: int(value, 0))
    parser.add_argument(
        "--retail-end",
        type=lambda value: int(value, 0),
        help=("exclusive end of a byte-audited retail function that automatic "
              "function discovery omitted"),
    )
    parser.add_argument("--retail-functions", required=True, type=Path)
    parser.add_argument("--retail-asm", required=True, type=Path)
    parser.add_argument("--alpha-functions", required=True, type=Path)
    parser.add_argument("--alpha-asm", required=True, type=Path)
    parser.add_argument("--alpha-symbols", required=True, type=Path)
    parser.add_argument("--top", type=int, default=20)
    parser.add_argument("--output", type=Path)
    args = parser.parse_args()

    retail_meta = load_function_metadata(args.retail_functions)
    alpha_meta = load_function_metadata(args.alpha_functions)
    retail_asm = parse_asm(args.retail_asm)
    alpha_asm = parse_asm(args.alpha_asm)
    alpha_symbols = load_symbols(args.alpha_symbols)

    explicit_range = args.retail_end is not None
    if explicit_range:
        retail_start = args.retail_address
        if args.retail_end <= retail_start:
            raise SystemExit("--retail-end must be greater than --retail-address")
        target_asm = parse_asm_range(args.retail_asm, retail_start, args.retail_end)
        target_meta = {
            "start": f"0x{retail_start:08X}",
            "end": f"0x{args.retail_end:08X}",
            "size": args.retail_end - retail_start,
            "name": target_asm["name"],
            "calls_to": [None for mnemonic in target_asm["mnemonics"] if mnemonic == "call"],
        }
    else:
        retail_start = next(
            (start for start, item in retail_meta.items()
             if start <= args.retail_address < int(item["end"], 16)),
            None,
        )
        if retail_start is None or retail_start not in retail_asm:
            raise SystemExit(
                f"retail address 0x{args.retail_address:08X} is not in a parsed "
                "function; provide its verified exclusive end with --retail-end"
            )
        target_meta = retail_meta[retail_start]
        target_asm = retail_asm[retail_start]
    target_count = len(target_asm["tokens"])
    candidates = []
    for start, candidate_asm in alpha_asm.items():
        names = alpha_symbols.get(start)
        candidate_meta = alpha_meta.get(start)
        if not names or not candidate_meta:
            continue
        candidate_count = len(candidate_asm["tokens"])
        count_shape = shape_ratio(target_count, candidate_count)
        size_shape = shape_ratio(target_meta["size"], candidate_meta["size"])
        if count_shape < 0.45 or size_shape < 0.40:
            continue
        mnemonic_score = ratio(target_asm["mnemonics"], candidate_asm["mnemonics"])
        token_score = ratio(target_asm["tokens"], candidate_asm["tokens"])
        call_shape = shape_ratio(len(target_meta.get("calls_to", [])) + 1,
                                 len(candidate_meta.get("calls_to", [])) + 1)
        score = (
            0.42 * mnemonic_score
            + 0.28 * token_score
            + 0.12 * count_shape
            + 0.10 * size_shape
            + 0.08 * call_shape
        )
        candidates.append({
            "score": round(score, 6),
            "alphaStart": f"0x{start:08X}",
            "alphaEnd": candidate_meta["end"],
            "names": names,
            "mnemonicScore": round(mnemonic_score, 6),
            "tokenScore": round(token_score, 6),
            "instructionShape": round(count_shape, 6),
            "byteShape": round(size_shape, 6),
            "callShape": round(call_shape, 6),
            "alphaInstructionCount": candidate_count,
            "alphaSize": candidate_meta["size"],
        })
    candidates.sort(key=lambda item: item["score"], reverse=True)

    paths = {
        "retailFunctions": args.retail_functions,
        "retailAsm": args.retail_asm,
        "alphaFunctions": args.alpha_functions,
        "alphaAsm": args.alpha_asm,
        "alphaSymbols": args.alpha_symbols,
    }
    output = {
        "schema": 1,
        "method": "normalized-instruction-and-function-shape-ranking",
        "warning": "Candidates require manual control-flow, call-graph, constant, vtable, and runtime validation before naming retail code.",
        "inputs": {name: {"path": str(path.resolve()), "sha256": sha256(path)} for name, path in paths.items()},
        "retail": {
            "queriedAddress": f"0x{args.retail_address:08X}",
            "explicitRange": explicit_range,
            "functionStart": f"0x{retail_start:08X}",
            "functionEnd": target_meta["end"],
            "currentName": target_meta["name"],
            "instructionCount": target_count,
            "size": target_meta["size"],
        },
        "candidates": candidates[: max(args.top, 1)],
    }
    rendered = json.dumps(output, indent=2) + "\n"
    if args.output:
        args.output.parent.mkdir(parents=True, exist_ok=True)
        args.output.write_text(rendered, encoding="utf-8")
    else:
        print(rendered, end="")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
