#!/usr/bin/env python3
"""Validate the evidence-backed DAH1 main-menu symbol registry."""

from __future__ import annotations

import json
import re
import sys
from collections import Counter
from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
REGISTRY = Path(__file__).with_name("main_menu_symbols.json")
SOURCE_ROOT = ROOT / "src" / "recomp"
ADDRESS_RE = re.compile(r"^0x[0-9A-F]{8}$")
GENERATED_RE = re.compile(r"^sub_([0-9A-F]{8})$")
VALID_CONFIDENCE = {"confirmed", "high", "medium", "low"}
VALID_STATUS = {
    "mapped",
    "needs-property-hashes",
    "needs-event-name",
    "needs-callgraph",
    "needs-runtime-evidence",
}


def fail(message: str) -> None:
    print(f"ERROR: {message}", file=sys.stderr)


def main() -> int:
    data = json.loads(REGISTRY.read_text(encoding="utf-8"))
    symbols = data.get("symbols", [])
    errors = 0

    if data.get("schemaVersion") != 1:
        fail("schemaVersion must be 1")
        errors += 1
    if data.get("scope") != "main-menu":
        fail("registry scope must be main-menu")
        errors += 1
    if not symbols:
        fail("registry contains no symbols")
        errors += 1

    sources = "\n".join(
        path.read_text(encoding="utf-8", errors="ignore")
        for path in SOURCE_ROOT.rglob("*.c")
    )
    addresses: list[str] = []
    generated_names: list[str] = []
    semantic_names: list[str] = []

    required = {
        "address",
        "generatedName",
        "semanticName",
        "subsystem",
        "role",
        "confidence",
        "nameOrigin",
        "status",
        "evidence",
    }
    for index, symbol in enumerate(symbols):
        label = symbol.get("generatedName", f"entry {index}")
        missing = sorted(required - symbol.keys())
        if missing:
            fail(f"{label}: missing fields {', '.join(missing)}")
            errors += 1
            continue
        address = symbol["address"]
        generated = symbol["generatedName"]
        semantic = symbol["semanticName"]
        match = GENERATED_RE.fullmatch(generated)
        if not ADDRESS_RE.fullmatch(address):
            fail(f"{label}: malformed address {address!r}")
            errors += 1
        if not match:
            fail(f"{label}: malformed generatedName")
            errors += 1
        elif address[2:] != match.group(1):
            fail(f"{label}: address does not match generatedName")
            errors += 1
        if symbol["confidence"] not in VALID_CONFIDENCE:
            fail(f"{label}: invalid confidence {symbol['confidence']!r}")
            errors += 1
        if symbol["status"] not in VALID_STATUS:
            fail(f"{label}: invalid status {symbol['status']!r}")
            errors += 1
        if not isinstance(symbol["evidence"], list) or not symbol["evidence"]:
            fail(f"{label}: evidence must be a nonempty list")
            errors += 1
        if f"void {generated}(void)" not in sources:
            fail(f"{label}: no function definition found under src/recomp")
            errors += 1
        addresses.append(address)
        generated_names.append(generated)
        semantic_names.append(semantic)

    for field, values in (
        ("address", addresses),
        ("generatedName", generated_names),
        ("semanticName", semantic_names),
    ):
        for value, count in Counter(values).items():
            if count > 1:
                fail(f"duplicate {field}: {value}")
                errors += 1

    if errors:
        print(f"main-menu symbol registry: FAILED ({errors} error(s))")
        return 1

    counts = Counter(symbol["confidence"] for symbol in symbols)
    unresolved = sum(symbol["status"] != "mapped" for symbol in symbols)
    print(
        "main-menu symbol registry: OK "
        f"({len(symbols)} symbols; "
        + ", ".join(f"{key}={counts[key]}" for key in ("confirmed", "high", "medium", "low") if counts[key])
        + f"; unresolved={unresolved})"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
