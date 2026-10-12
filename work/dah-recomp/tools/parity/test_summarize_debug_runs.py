#!/usr/bin/env python3
from __future__ import annotations

import json
import importlib.util
import tempfile
import unittest
from pathlib import Path

MODULE_PATH = Path(__file__).with_name("summarize_debug_runs.py")
SPEC = importlib.util.spec_from_file_location("summarize_debug_runs", MODULE_PATH)
assert SPEC and SPEC.loader
MODULE = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(MODULE)
build_index = MODULE.build_index
write_markdown = MODULE.write_markdown


class RunEvidenceSummaryTests(unittest.TestCase):
    def test_groups_fingerprints_and_tolerates_truncated_tail(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            for run_id, status in (("run-a", "completed"), ("run-b", "closed")):
                run = root / run_id
                run.mkdir()
                (run / "manifest.json").write_text(json.dumps({
                    "runId": run_id, "status": status,
                    "startedUtc": "2026-10-11T00:00:00Z",
                }), encoding="utf-8")
                (run / "summary.json").write_text(json.dumps({
                    "events": 10, "anomalies": 1, "droppedEvents": 0,
                    "worstFrameUs": 40000,
                }), encoding="utf-8")
                (run / "anomalies.jsonl").write_text(
                    json.dumps({"event": "anomaly",
                                "fingerprint": "frame-budget-miss",
                                "severity": "warning", "worldTick": 5,
                                "detail": "measuredUs=40000"}) + "\n{" ,
                    encoding="utf-8")
            index = build_index(root)
            self.assertEqual(index["runCount"], 2)
            self.assertEqual(len(index["fingerprints"]), 1)
            issue = index["fingerprints"][0]
            self.assertEqual(issue["occurrences"], 2)
            self.assertEqual(issue["runCount"], 2)
            markdown = root / "ISSUE_INDEX.md"
            write_markdown(markdown, index)
            self.assertIn("frame-budget-miss", markdown.read_text(encoding="utf-8"))


if __name__ == "__main__":
    unittest.main()
