#!/usr/bin/env python3
"""Prove Normal has no reporter and Debug-Reporter emits allowlisted JSON."""

from __future__ import annotations

import argparse
import json
import os
import shutil
import subprocess
import tempfile
from pathlib import Path


ALLOWED_SESSION_FIELDS = {
    "schema",
    "privacySchema",
    "reportId",
    "kind",
    "buildFnv1a64",
    "status",
    "durationSeconds",
    "events",
    "anomalies",
    "droppedEvents",
    "frameBudgetMisses",
    "sceneVisibilityFlashes",
    "playerRenderLosses",
    "hudCinematicOverlaps",
    "worstFrameUs",
    "containsPaths",
    "containsMemory",
    "containsGameAssets",
}

FORBIDDEN_TEXT = {
    "c:\\",
    "\\users\\",
    "computername",
    "username",
    "executable",
    "save",
    "input",
    "screenshot",
    "runtime.log",
    "debug-runs",
    "crashlog",
}

REPORTER_MARKERS = (
    b"reporting-settings.json",
    b"Debug-Reporter edition",
    b"report_bug",
)


def run_without_game_data(executable: Path, directory: Path) -> None:
    directory.mkdir()
    destination = directory / "DestroyAllHumans.exe"
    shutil.copy2(executable, destination)
    environment = os.environ.copy()
    environment["DAH_INTERNAL_RUN"] = "1"
    subprocess.run(
        [str(destination)],
        cwd=directory,
        env=environment,
        timeout=30,
        check=False,
    )


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--normal", type=Path, required=True)
    parser.add_argument("--reporter", type=Path, required=True)
    args = parser.parse_args()

    normal_bytes = args.normal.read_bytes()
    reporter_bytes = args.reporter.read_bytes()
    assert not any(marker in normal_bytes for marker in REPORTER_MARKERS), (
        "Normal binary contains Debug-Reporter markers"
    )
    assert all(marker in reporter_bytes for marker in REPORTER_MARKERS), (
        "Debug-Reporter binary is missing reporter markers"
    )

    with tempfile.TemporaryDirectory(prefix="dah-report-privacy-") as temporary:
        root = Path(temporary)
        normal_directory = root / "normal"
        reporter_directory = root / "reporter"
        run_without_game_data(args.normal.resolve(), normal_directory)
        run_without_game_data(args.reporter.resolve(), reporter_directory)

        assert not (normal_directory / "reports").exists()
        assert not (normal_directory / "reporting-settings.json").exists()

        settings = json.loads(
            (reporter_directory / "reporting-settings.json").read_text()
        )
        assert settings["sendCrashReports"] is False
        assert settings["sendSessionReports"] is False

        reports = list((reporter_directory / "reports" / "local").glob("*.json"))
        assert len(reports) == 1, reports
        raw = reports[0].read_text(encoding="utf-8")
        report = json.loads(raw)
        assert set(report) == ALLOWED_SESSION_FIELDS, set(report)
        lowered = raw.lower()
        leaked = sorted(value for value in FORBIDDEN_TEXT if value in lowered)
        assert not leaked, leaked
        assert report["containsPaths"] is False
        assert report["containsMemory"] is False
        assert report["containsGameAssets"] is False

    print("PASS: Normal has no reporter; Debug-Reporter JSON is allowlisted")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
