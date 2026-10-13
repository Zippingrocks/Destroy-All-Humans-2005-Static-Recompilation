#!/usr/bin/env python3
"""Fail closed on unclassified native patches and publish an honest ledger."""
from __future__ import annotations

import argparse
import hashlib
import json
import re
from collections import Counter
from pathlib import Path

RE_DAH_DEF = re.compile(
    r"^(?:static\s+)?(?:inline\s+)?(?:void|int|unsigned|uint32_t|uint64_t|"
    r"int32_t|float|double|bool|BOOLEAN|HRESULT|const\s+char\s*\*)\s+"
    r"(dah_[A-Za-z0-9_]+)\s*\(", re.MULTILINE
)
RE_DAH_USE = re.compile(r"\b(dah_[A-Za-z0-9_]+)\s*\(")
RE_SUB_DEF = re.compile(r"^void\s+(sub_[0-9A-Fa-f]{8})\s*\(void\)\s*$", re.MULTILINE)
RE_STUB = re.compile(
    r"void\s+sub_([0-9A-Fa-f]{8})\s*\(void\)\s*\{\s*g_esp\s*\+=\s*4",
    re.MULTILINE,
)
RE_OVERRIDE = re.compile(
    r"case\s+0x([0-9A-Fa-f]{8})u:\s*return\s+([A-Za-z_][A-Za-z0-9_]*)\s*;"
)

ALLOWED_CATEGORIES = {
    "retail-restoration", "parity-implementation", "compatibility-layer",
    "diagnostic-instrumentation", "development-tooling", "temporary-mitigation",
}
COUNTED_AS_COMPLETION = {"retail-restoration"}
KNOWN_DATA_ARTIFACT_STUBS = {
    0x001EC715, 0x001EC74C, 0x001EC762,
    0x0021769D, 0x002176B9, 0x002176C7,
}


def read(path: Path) -> str:
    return path.read_text(encoding="utf-8", errors="replace")


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--manifest", type=Path)
    ap.add_argument("--json", type=Path)
    ap.add_argument("--markdown", type=Path)
    args = ap.parse_args()
    repo = Path(__file__).resolve().parents[1]
    root = repo.parents[1]
    manifest_path = args.manifest or repo / "tools" / "parity" / "port_integrity_manifest.json"
    manifest = json.loads(read(manifest_path))
    entries = manifest["nativeSymbols"]
    by_name = {row["symbol"]: row for row in entries}
    if len(by_name) != len(entries):
        raise SystemExit("FAIL duplicate nativeSymbols entry")
    bad_categories = sorted({row["category"] for row in entries} - ALLOWED_CATEGORIES)
    if bad_categories:
        raise SystemExit("FAIL unknown categories: " + ", ".join(bad_categories))

    source_files = sorted((repo / "src").glob("**/*.c"))
    custom_defs: dict[str, str] = {}
    for path in source_files:
        if "src/recomp/gen" in path.as_posix():
            continue
        for name in RE_DAH_DEF.findall(read(path)):
            custom_defs[name] = path.relative_to(repo).as_posix()
    unknown_defs = sorted(set(custom_defs) - set(by_name))
    stale_entries = sorted(set(by_name) - set(custom_defs))
    if unknown_defs or stale_entries:
        raise SystemExit(
            "FAIL native patch classification drift; unclassified="
            + repr(unknown_defs) + " stale=" + repr(stale_entries)
        )

    generated = repo / "src" / "recomp" / "gen"
    generated_text = "\n".join(read(p) for p in generated.glob("*.c"))
    hook_entries = manifest.get("generatedHooks", [])
    hook_by_name = {row["symbol"]: row for row in hook_entries}
    if len(hook_by_name) != len(hook_entries):
        raise SystemExit("FAIL duplicate generatedHooks entry")
    bad_hook_categories = sorted(
        {row["category"] for row in hook_entries} - ALLOWED_CATEGORIES
    )
    if bad_hook_categories:
        raise SystemExit("FAIL unknown generated-hook categories: " + ", ".join(bad_hook_categories))
    hook_uses = set(RE_DAH_USE.findall(generated_text))
    classified_hooks = set(by_name) | set(hook_by_name)
    unknown_hooks = sorted(hook_uses - classified_hooks)
    stale_hooks = sorted(set(hook_by_name) - hook_uses)
    if unknown_hooks:
        raise SystemExit("FAIL generated code calls unclassified native hooks: " + repr(unknown_hooks))
    if stale_hooks:
        raise SystemExit("FAIL stale generatedHooks entries: " + repr(stale_hooks))

    manual = read(repo / "src" / "recomp_manual.c")
    overrides = []
    for addr_s, function in RE_OVERRIDE.findall(manual):
        address = int(addr_s, 16)
        if function != f"sub_{address:08X}":
            overrides.append((address, function))
    allowed_overrides = {
        (int(row["address"], 16), row["function"])
        for row in manifest["manualDispatchOverrides"]
    }
    actual_overrides = set(overrides)
    if actual_overrides != allowed_overrides:
        raise SystemExit(
            "FAIL manual dispatch override drift; unclassified="
            + repr(sorted(actual_overrides - allowed_overrides))
            + " stale=" + repr(sorted(allowed_overrides - actual_overrides))
        )

    stubs_text = read(generated / "recomp_stubs_unresolved.c")
    all_noop_stubs = {int(x, 16) for x in RE_STUB.findall(stubs_text)}
    missing_artifact_stubs = KNOWN_DATA_ARTIFACT_STUBS - all_noop_stubs
    if missing_artifact_stubs:
        raise SystemExit("FAIL documented data-artifact stub drift: "
                         + repr([hex(x) for x in sorted(missing_artifact_stubs)]))
    data_artifact_stubs = all_noop_stubs & KNOWN_DATA_ARTIFACT_STUBS
    recovery_stubs = all_noop_stubs - data_artifact_stubs
    seeds = {int(x["start"], 16) for x in json.loads(read(repo / "icall_seeds.json"))}
    seeded_stubs = sorted(seeds & all_noop_stubs)
    if seeded_stubs:
        raise SystemExit("FAIL seeded no-op recovery stubs: " + repr([hex(x) for x in seeded_stubs]))

    special_files = []
    for path in sorted(generated.glob("recomp_*.c")):
        if re.fullmatch(r"recomp_[0-9]{4}\.c", path.name) or path.name in {
            "recomp_dispatch.c", "recomp_stubs_unresolved.c", "recomp_seeded.c"
        }:
            continue
        functions = RE_SUB_DEF.findall(read(path))
        if functions:
            special_files.append({"file": path.name, "functions": len(functions)})

    classified_entries = entries + hook_entries
    counts = Counter(row["category"] for row in classified_entries)
    provisional = [row for row in classified_entries if row["category"] == "temporary-mitigation"]
    unverified = [row for row in classified_entries if row.get("evidenceStatus") != "verified"]
    completion = [
        row for row in classified_entries
        if row["category"] in COUNTED_AS_COMPLETION
        and row.get("evidenceStatus") == "verified"
    ]
    report = {
        "schema": 1,
        "policy": {
            "completionCategories": sorted(COUNTED_AS_COMPLETION),
            "temporaryMitigationsCountTowardCompletion": False,
            "compatibilityLayersCountTowardCompletion": False,
        },
        "summary": {
            "classifiedNativeSymbols": len(classified_entries),
            "categoryCounts": dict(sorted(counts.items())),
            "verifiedNativeSymbols": len(classified_entries) - len(unverified),
            "unverifiedNativeSymbols": len(unverified),
            "provisionalMitigations": len(provisional),
            "manualDispatchOverrides": len(overrides),
            "retailRecoverySourceFiles": len(special_files),
            "recoveryNoOpStubs": len(recovery_stubs),
            "generatedDataArtifactStubs": len(data_artifact_stubs),
            "seededNoOpStubs": len(seeded_stubs),
            "completionCreditedNativeSymbols": len(completion),
        },
        "nativeSymbols": [dict(row, source=custom_defs[row["symbol"]]) for row in entries],
        "generatedHooks": hook_entries,
        "manualDispatchOverrides": manifest["manualDispatchOverrides"],
        "specialRetailRecoverySources": special_files,
        "recoveryNoOpStubAddresses": [f"0x{x:08X}" for x in sorted(recovery_stubs)],
        "generatedDataArtifactStubAddresses": [
            f"0x{x:08X}" for x in sorted(data_artifact_stubs)
        ],
    }
    encoded = json.dumps(report, indent=2) + "\n"
    if args.json:
        args.json.parent.mkdir(parents=True, exist_ok=True)
        args.json.write_text(encoded, encoding="utf-8")
    if args.markdown:
        lines = [
            "# Port integrity ledger", "",
            "Generated by `tools/audit_port_integrity.py`. Only verified retail",
            "restorations receive completion credit. Compatibility code, developer",
            "tools, diagnostics, parity implementations, and mitigations do not.", "",
            "## Current accounting", "",
            f"- Classified native symbols and generated hooks: **{len(classified_entries)}**",
            f"- Verified classifications: **{len(classified_entries) - len(unverified)}**",
            f"- Unverified or partially evidenced native symbols: **{len(unverified)}**",
            f"- Temporary mitigations: **{len(provisional)}**",
            f"- Recovery no-op stubs remaining: **{len(recovery_stubs)}**",
            f"- Proven generated data-artifact stubs: **{len(data_artifact_stubs)}**",
            f"- Seeded callbacks using no-op stubs: **{len(seeded_stubs)}**", "",
            "## Category counts", "",
            "| Category | Count | Completion credit |", "|---|---:|:---:|",
        ]
        for category in sorted(ALLOWED_CATEGORIES):
            lines.append(f"| {category} | {counts[category]} | {'yes' if category in COUNTED_AS_COMPLETION else 'no'} |")
        lines += ["", "## Open provisional work", ""]
        if provisional:
            for row in provisional:
                lines.append(f"- `{row['symbol']}` — {row['reason']} Acceptance: {row['acceptance']}")
        else:
            lines.append("None.")
        lines += ["", "## Unverified classifications", ""]
        if unverified:
            for row in unverified:
                lines.append(f"- `{row['symbol']}` ({row['category']}) — {row['reason']}")
        else:
            lines.append("None.")
        lines += ["", "## Enforcement", "",
                  "The audit fails on any new unclassified native function, stale manifest",
                  "entry, unclassified manual dispatch override, unclassified generated-code",
                  "hook, or indirect-call seed that still resolves to a recovery no-op stub.", ""]
        args.markdown.parent.mkdir(parents=True, exist_ok=True)
        args.markdown.write_text("\n".join(lines), encoding="utf-8")
    print(
        "PASS port integrity: "
        f"{len(classified_entries)} classified native symbols/hooks, {len(provisional)} provisional, "
        f"{len(recovery_stubs)} recovery stubs, {len(data_artifact_stubs)} data artifacts, "
        "0 seeded stubs"
    )
    return 0

if __name__ == "__main__":
    raise SystemExit(main())
