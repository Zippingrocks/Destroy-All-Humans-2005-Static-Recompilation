#!/usr/bin/env python3
"""Validate and summarize the bounded main-menu route coverage ledger."""

from __future__ import annotations

import json
import sys
from collections import Counter
from pathlib import Path


PATH = Path(__file__).with_name("main_menu_coverage.json")
DIMENSIONS = ("static", "runtime", "xemuParity")


def main() -> int:
    data = json.loads(PATH.read_text(encoding="utf-8"))
    allowed = set(data.get("statusValues", []))
    routes = data.get("routes", [])
    errors: list[str] = []
    ids: set[str] = set()
    for index, route in enumerate(routes):
        route_id = route.get("id", f"entry-{index}")
        if route_id in ids:
            errors.append(f"duplicate route id: {route_id}")
        ids.add(route_id)
        for field in ("id", "area", "description", "evidence", *DIMENSIONS):
            if field not in route:
                errors.append(f"{route_id}: missing {field}")
        for dimension in DIMENSIONS:
            if route.get(dimension) not in allowed:
                errors.append(f"{route_id}: invalid {dimension}={route.get(dimension)!r}")
        if route.get("runtime") == "verified" and not route.get("evidence"):
            errors.append(f"{route_id}: verified runtime has no evidence")
        if route.get("xemuParity") == "verified" and not route.get("evidence"):
            errors.append(f"{route_id}: verified xemu parity has no evidence")
    if data.get("schemaVersion") != 1 or data.get("scope") != "main-menu":
        errors.append("invalid schemaVersion or scope")
    if errors:
        for error in errors:
            print(f"ERROR: {error}", file=sys.stderr)
        return 1
    summaries = []
    for dimension in DIMENSIONS:
        counts = Counter(route[dimension] for route in routes)
        summaries.append(
            f"{dimension}:" + ",".join(f"{status}={counts[status]}" for status in data["statusValues"] if counts[status])
        )
    print(f"main-menu coverage: OK ({len(routes)} routes; {'; '.join(summaries)})")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
