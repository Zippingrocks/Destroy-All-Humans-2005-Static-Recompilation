#!/usr/bin/env python3
"""Regression coverage for retained callback evidence and source reconciliation."""

from __future__ import annotations

import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

from audit_crash_callbacks import (
    callback_implementations,
    missing_retained_callbacks,
    retained_callback_observations,
)


class RetainedCallbackAuditTests(unittest.TestCase):
    def test_scans_nested_run_evidence_and_streams_logs(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            evidence = {
                "furonlog.log": "blank\n[ICALL] unresolved Xbox target 0x00012340\n",
                "debug-runs/run-one/runtime.log": "[ICALL] unresolved Xbox target 0x00023450\n",
                "debug-runs/run-one/nested/events.jsonl": "{\"detail\":\"[ICALL] unresolved Xbox target 0x00034560\"}\n",
                "debug-runs/run-two/diagnostic.txt": "[ICALL] unresolved Xbox target 0x00045670\n",
                "crashlog/nested/crash.txt": "[ICALL] unresolved Xbox target 0x00012340\n",
                "work/dah-recomp/tools/parity/blanket-runs/run/log.LOG": "[ICALL] unresolved Xbox target 0x00000000\n",
                # A binary file or unrelated directory must not become callback
                # evidence just because its bytes contain an old log string.
                "debug-runs/run-one/memory.dmp": "[ICALL] unresolved Xbox target 0x00056780\n",
                "unrelated/archive.log": "[ICALL] unresolved Xbox target 0x00067890\n",
            }
            for name, text in evidence.items():
                path = root / name
                path.parent.mkdir(parents=True, exist_ok=True)
                path.write_text(text, encoding="utf-8")
            with patch.object(Path, "read_text", side_effect=AssertionError("must stream retained logs")):
                observations, null_calls = retained_callback_observations(root)
            self.assertEqual(set(observations), {0x12340, 0x23450, 0x34560, 0x45670})
            self.assertEqual(observations[0x12340], [
                "crashlog/nested/crash.txt:1", "furonlog.log:2",
            ])
            self.assertEqual(observations[0x34560], [
                "debug-runs/run-one/nested/events.jsonl:1",
            ])
            self.assertEqual(null_calls, 1)

    def test_restored_callback_need_not_be_in_historical_list(self):
        generated = "void sub_00012340(void) { g_eax = 7; g_esp += 4; }"
        dispatch = "{ 0x00012340u, (recomp_func_t)sub_00012340 },"
        implementations = callback_implementations("", generated, dispatch)
        self.assertEqual(missing_retained_callbacks({0x12340: ["run:1"]}, implementations, set()), [])

    def test_declaration_or_commented_body_does_not_hide_missing_callback(self):
        generated = """
void sub_00012340(void);
/* void sub_00012340(void) { g_esp += 4; } */
// void sub_00012340(void) { g_esp += 4; }
"""
        dispatch = "{ 0x00012340u, (recomp_func_t)sub_00012340 },"
        implementations = callback_implementations("", generated, dispatch)
        self.assertEqual(missing_retained_callbacks({0x12340: ["run:1"]}, implementations, set()), [0x12340])

    def test_body_without_dispatch_still_fails(self):
        generated = "void sub_00012340(void) { g_esp += 4; }"
        implementations = callback_implementations("", generated, "")
        self.assertEqual(missing_retained_callbacks({0x12340: ["run:1"]}, implementations, set()), [0x12340])

    def test_recovery_body_and_alias_to_recovery_still_fail(self):
        generated = "void sub_00012340(void) { g_esp += 4; }"
        dispatch = """
{ 0x00012340u, (recomp_func_t)sub_00012340 },
{ 0x00023450u, (recomp_func_t)sub_00012340 },
"""
        implementations = callback_implementations("", generated, dispatch)
        self.assertEqual(missing_retained_callbacks(
            {0x12340: ["run:1"], 0x23450: ["run:2"]}, implementations, {0x12340},
        ), [0x12340, 0x23450])

    def test_manual_dispatch_destination_overrides_generated(self):
        generated = "void sub_00012340(void) { g_eax = 7; g_esp += 4; }"
        dispatch = "{ 0x00012340u, (recomp_func_t)sub_00012340 },"
        manual = "case 0x00012340u: return missing_manual_body;"
        implementations = callback_implementations(manual, generated, dispatch)
        self.assertEqual(missing_retained_callbacks({0x12340: ["run:1"]}, implementations, set()), [0x12340])
        manual += "\nstatic void missing_manual_body(void) { g_eax = 8; g_esp += 4; }"
        implementations = callback_implementations(manual, generated, dispatch)
        self.assertEqual(implementations[0x12340], "missing_manual_body")

    def test_known_non_entry_is_excluded_but_unknown_target_fails(self):
        self.assertEqual(missing_retained_callbacks({
            0x00023899: ["crash:1"], 0x00012340: ["crash:2"],
        }, {}, set()), [0x12340])


if __name__ == "__main__":
    unittest.main()
