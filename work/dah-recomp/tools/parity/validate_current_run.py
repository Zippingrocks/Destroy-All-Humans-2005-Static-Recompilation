#!/usr/bin/env python3
"""Reject mixed or stale DAH diagnostics before reporting a playtest bug."""

import argparse
import ctypes
import json
import os
import re
from pathlib import Path


RUN_LINE = re.compile(r"^\[DAH-RUN\].*\bid=([^ ]+).*$")


def process_is_running(pid: int) -> bool:
    if os.name != "nt":
        try:
            os.kill(pid, 0)
            return True
        except OSError:
            return False
    process_query_limited_information = 0x1000
    still_active = 259
    kernel32 = ctypes.WinDLL("kernel32", use_last_error=True)
    kernel32.OpenProcess.argtypes = [ctypes.c_uint32, ctypes.c_bool, ctypes.c_uint32]
    kernel32.OpenProcess.restype = ctypes.c_void_p
    kernel32.GetExitCodeProcess.argtypes = [ctypes.c_void_p,
                                             ctypes.POINTER(ctypes.c_uint32)]
    kernel32.GetExitCodeProcess.restype = ctypes.c_bool
    kernel32.CloseHandle.argtypes = [ctypes.c_void_p]
    handle = kernel32.OpenProcess(process_query_limited_information, False, pid)
    if not handle:
        return False
    try:
        exit_code = ctypes.c_uint32()
        return bool(kernel32.GetExitCodeProcess(handle, ctypes.byref(exit_code))) and \
            exit_code.value == still_active
    finally:
        kernel32.CloseHandle(handle)


def first_nonempty(path: Path) -> str:
    with path.open("r", encoding="utf-8", errors="replace") as source:
        for line in source:
            if line.strip():
                return line.rstrip("\r\n")
    raise ValueError(f"{path}: empty file")


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--root", type=Path, default=Path.cwd())
    args = parser.parse_args()
    root = args.root.resolve()
    manifest_path = root / "dah_current_run.json"
    manifest = json.loads(manifest_path.read_text(encoding="utf-8"))
    run_id = manifest["runId"]
    if manifest.get("status") == "running" and not process_is_running(int(manifest["pid"])):
        raise SystemExit(
            f"STALE RUN: {run_id} says running but pid {manifest['pid']} has exited"
        )

    log_path = Path(manifest["logPath"])
    if not log_path.is_absolute():
        log_path = root / log_path
    log_id = None
    with log_path.open("r", encoding="utf-8", errors="replace") as source:
        for line in source:
            match = RUN_LINE.match(line.rstrip("\r\n"))
            if match:
                log_id = match.group(1)
                break
    if log_id != run_id:
        raise SystemExit(f"MIXED RUN: manifest={run_id} furonlog={log_id}")

    event_name = manifest["eventTracePath"]
    if event_name != "0":
        event_path = Path(event_name)
        if not event_path.is_absolute():
            event_path = root / event_path
        event = json.loads(first_nonempty(event_path))
        if event.get("event") != "run-start" or event.get("runId") != run_id:
            raise SystemExit(
                f"MIXED RUN: manifest={run_id} event-trace={event.get('runId')}"
            )
        if event.get("executableFnv1a64") != manifest.get("executableFnv1a64"):
            raise SystemExit("MIXED BUILD: executable identity differs across diagnostics")

    print(
        f"current run OK: id={run_id} status={manifest['status']} "
        f"build={manifest['executableFnv1a64']}"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
