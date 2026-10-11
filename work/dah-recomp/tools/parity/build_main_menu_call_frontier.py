#!/usr/bin/env python3
"""Build the direct native-call frontier for mapped main-menu functions."""

from __future__ import annotations

import json
import re
from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
REGISTRY = Path(__file__).with_name("main_menu_symbols.json")
OUTPUT = Path(__file__).with_name("main_menu_call_frontier.json")
FUNCTION_RE = re.compile(r"\bvoid\s+(sub_[0-9A-F]{8})\s*\(void\)\s*\{")
CALL_RE = re.compile(r"\b(sub_[0-9A-F]{8})\s*\(\s*\)\s*;")


def extract_functions(text: str) -> dict[str, str]:
    result: dict[str, str] = {}
    for match in FUNCTION_RE.finditer(text):
        depth = 1
        cursor = match.end()
        while cursor < len(text) and depth:
            char = text[cursor]
            if char == "{":
                depth += 1
            elif char == "}":
                depth -= 1
            cursor += 1
        if depth == 0:
            result[match.group(1)] = text[match.end():cursor - 1]
    return result


def main() -> int:
    registry = json.loads(REGISTRY.read_text(encoding="utf-8"))
    symbols = registry["symbols"]
    mapped = {item["generatedName"]: item for item in symbols}
    functions: dict[str, str] = {}
    for path in (ROOT / "src" / "recomp").rglob("*.c"):
        functions.update(extract_functions(path.read_text(encoding="utf-8", errors="ignore")))

    edges: list[dict[str, object]] = []
    missing_roots: list[str] = []
    frontier: dict[str, set[str]] = {}
    for source in sorted(mapped):
        body = functions.get(source)
        if body is None:
            missing_roots.append(source)
            continue
        for target in sorted(set(CALL_RE.findall(body))):
            target_entry = mapped.get(target)
            edges.append(
                {
                    "from": source,
                    "to": target,
                    "targetMapped": target_entry is not None,
                    "targetSemanticName": target_entry["semanticName"] if target_entry else None,
                }
            )
            if target_entry is None:
                frontier.setdefault(target, set()).add(source)

    document = {
        "schemaVersion": 1,
        "scope": "main-menu-direct-call-frontier",
        "generatedFrom": "main_menu_symbols.json and src/recomp/**/*.c",
        "mappedRootCount": len(mapped),
        "missingRoots": missing_roots,
        "edgeCount": len(edges),
        "mappedEdgeCount": sum(bool(edge["targetMapped"]) for edge in edges),
        "frontierCount": len(frontier),
        "edges": edges,
        "frontier": [
            {"generatedName": target, "calledBy": sorted(callers), "classification": "unclassified"}
            for target, callers in sorted(frontier.items())
        ],
    }
    OUTPUT.write_text(json.dumps(document, indent=2) + "\n", encoding="utf-8")
    print(
        f"main-menu call frontier: {len(mapped)} roots, {len(edges)} edges, "
        f"{len(frontier)} unclassified direct callees"
    )
    return 1 if missing_roots else 0


if __name__ == "__main__":
    raise SystemExit(main())
