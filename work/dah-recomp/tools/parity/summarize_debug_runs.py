#!/usr/bin/env python3
"""Build a stable cross-run issue index from DAH run evidence directories."""
from __future__ import annotations

import argparse
import json
from collections import Counter, defaultdict
from pathlib import Path


def load_json(path: Path) -> dict:
    try:
        value = json.loads(path.read_text(encoding="utf-8"))
        return value if isinstance(value, dict) else {}
    except (OSError, json.JSONDecodeError):
        return {}


def load_jsonl(path: Path):
    try:
        lines = path.read_text(encoding="utf-8", errors="replace").splitlines()
    except OSError:
        return
    for line_number, line in enumerate(lines, 1):
        try:
            value = json.loads(line)
        except json.JSONDecodeError:
            continue  # A killed process may leave one incomplete final record.
        if isinstance(value, dict):
            yield line_number, value


def build_index(root: Path) -> dict:
    fingerprints: dict[str, dict] = defaultdict(
        lambda: {"occurrences": 0, "runs": set(), "severities": Counter(),
                 "firstRun": None, "lastRun": None, "examples": []}
    )
    runs = []
    for manifest_path in sorted(root.glob("*/manifest.json")):
        manifest = load_json(manifest_path)
        run_id = str(manifest.get("runId") or manifest_path.parent.name)
        summary = load_json(manifest_path.parent / "summary.json")
        run_entry = {
            "runId": run_id,
            "status": manifest.get("status", "unknown"),
            "startedUtc": manifest.get("startedUtc"),
            "directory": manifest_path.parent.name,
            "events": summary.get("events"),
            "anomalies": summary.get("anomalies"),
            "droppedEvents": summary.get("droppedEvents"),
            "worstFrameUs": summary.get("worstFrameUs"),
        }
        runs.append(run_entry)
        for line_number, event in load_jsonl(manifest_path.parent / "anomalies.jsonl"):
            fingerprint = event.get("fingerprint")
            if not fingerprint:
                continue
            item = fingerprints[str(fingerprint)]
            item["occurrences"] += 1
            item["runs"].add(run_id)
            item["severities"][str(event.get("severity", "unknown"))] += 1
            item["firstRun"] = item["firstRun"] or run_id
            item["lastRun"] = run_id
            if len(item["examples"]) < 3:
                item["examples"].append({
                    "runId": run_id,
                    "line": line_number,
                    "worldTick": event.get("worldTick"),
                    "detail": event.get("detail", ""),
                })
    issue_rows = []
    for fingerprint, item in fingerprints.items():
        issue_rows.append({
            "fingerprint": fingerprint,
            "occurrences": item["occurrences"],
            "runCount": len(item["runs"]),
            "severities": dict(sorted(item["severities"].items())),
            "firstRun": item["firstRun"],
            "lastRun": item["lastRun"],
            "examples": item["examples"],
        })
    issue_rows.sort(key=lambda row: (-row["runCount"], -row["occurrences"],
                                     row["fingerprint"]))
    return {"schema": 1, "runCount": len(runs), "runs": runs,
            "fingerprints": issue_rows}


def write_markdown(path: Path, index: dict) -> None:
    lines = ["# DAH run evidence index", "",
             f"Runs indexed: **{index['runCount']}**", ""]
    if index["fingerprints"]:
        lines += ["| Fingerprint | Runs | Occurrences | Severity | Last run |",
                  "|---|---:|---:|---|---|"]
        for row in index["fingerprints"]:
            severity = ", ".join(f"{key}: {value}" for key, value in
                                 row["severities"].items())
            lines.append(f"| `{row['fingerprint']}` | {row['runCount']} | "
                         f"{row['occurrences']} | {severity} | `{row['lastRun']}` |")
    else:
        lines.append("No fingerprinted anomalies have been recorded.")
    lines += ["", "## Runs", "",
              "| Run | Status | Events | Anomalies | Dropped | Worst frame (us) |",
              "|---|---|---:|---:|---:|---:|"]
    for run in reversed(index["runs"]):
        values = [run.get(key) for key in
                  ("events", "anomalies", "droppedEvents", "worstFrameUs")]
        rendered = ["" if value is None else str(value) for value in values]
        lines.append(f"| `{run['runId']}` | {run['status']} | "
                     f"{rendered[0]} | {rendered[1]} | {rendered[2]} | {rendered[3]} |")
    path.write_text("\n".join(lines) + "\n", encoding="utf-8")


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("root", nargs="?", type=Path,
                        default=Path(__file__).resolve().parents[4] / "debug-runs")
    args = parser.parse_args()
    args.root.mkdir(parents=True, exist_ok=True)
    index = build_index(args.root)
    (args.root / "index.json").write_text(
        json.dumps(index, indent=2) + "\n", encoding="utf-8")
    write_markdown(args.root / "ISSUE_INDEX.md", index)
    print(f"indexed {index['runCount']} runs and "
          f"{len(index['fingerprints'])} fingerprints in {args.root}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
