#!/usr/bin/env python3
"""Attach the read-only blanket observer to each matching DAH process run.

The watcher never launches, focuses, controls, or terminates the game. It only
starts one hidden observer child for each exact executable path it discovers.
"""

from __future__ import annotations

import argparse
import ctypes
import subprocess
import sys
import time
from pathlib import Path


TH32CS_SNAPPROCESS = 0x00000002
PROCESS_QUERY_LIMITED_INFORMATION = 0x1000
INVALID_HANDLE_VALUE = ctypes.c_void_p(-1).value
CREATE_NO_WINDOW = 0x08000000


class ProcessEntry(ctypes.Structure):
    _fields_ = [
        ("dwSize", ctypes.c_uint32), ("cntUsage", ctypes.c_uint32),
        ("th32ProcessID", ctypes.c_uint32), ("th32DefaultHeapID", ctypes.c_size_t),
        ("th32ModuleID", ctypes.c_uint32), ("cntThreads", ctypes.c_uint32),
        ("th32ParentProcessID", ctypes.c_uint32), ("pcPriClassBase", ctypes.c_long),
        ("dwFlags", ctypes.c_uint32), ("szExeFile", ctypes.c_wchar * 260),
    ]


kernel32 = ctypes.WinDLL("kernel32", use_last_error=True)
kernel32.CreateToolhelp32Snapshot.argtypes = [ctypes.c_uint32, ctypes.c_uint32]
kernel32.CreateToolhelp32Snapshot.restype = ctypes.c_void_p
kernel32.Process32FirstW.argtypes = [ctypes.c_void_p, ctypes.POINTER(ProcessEntry)]
kernel32.Process32FirstW.restype = ctypes.c_bool
kernel32.Process32NextW.argtypes = [ctypes.c_void_p, ctypes.POINTER(ProcessEntry)]
kernel32.Process32NextW.restype = ctypes.c_bool
kernel32.OpenProcess.argtypes = [ctypes.c_uint32, ctypes.c_bool, ctypes.c_uint32]
kernel32.OpenProcess.restype = ctypes.c_void_p
kernel32.QueryFullProcessImageNameW.argtypes = [ctypes.c_void_p, ctypes.c_uint32,
                                                ctypes.c_wchar_p,
                                                ctypes.POINTER(ctypes.c_uint32)]
kernel32.QueryFullProcessImageNameW.restype = ctypes.c_bool
kernel32.CloseHandle.argtypes = [ctypes.c_void_p]


def process_ids(name: str):
    snapshot = kernel32.CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0)
    if snapshot == INVALID_HANDLE_VALUE:
        return []
    result = []
    try:
        entry = ProcessEntry()
        entry.dwSize = ctypes.sizeof(entry)
        more = kernel32.Process32FirstW(snapshot, ctypes.byref(entry))
        while more:
            if entry.szExeFile.casefold() == name.casefold():
                result.append(entry.th32ProcessID)
            more = kernel32.Process32NextW(snapshot, ctypes.byref(entry))
    finally:
        kernel32.CloseHandle(snapshot)
    return result


def image_path(pid: int) -> Path | None:
    handle = kernel32.OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, False, pid)
    if not handle:
        return None
    try:
        capacity = ctypes.c_uint32(32768)
        buffer = ctypes.create_unicode_buffer(capacity.value)
        if kernel32.QueryFullProcessImageNameW(handle, 0, buffer,
                                               ctypes.byref(capacity)):
            return Path(buffer.value)
        return None
    finally:
        kernel32.CloseHandle(handle)


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--executable", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    parser.add_argument("--poll-seconds", type=float, default=0.5)
    parser.add_argument("--hz", type=float, default=5.0)
    parser.add_argument("--scan-seconds", type=float, default=5.0)
    args = parser.parse_args()
    target = args.executable.resolve()
    args.output_dir.mkdir(parents=True, exist_ok=True)
    observer = Path(__file__).with_name("live_blanket_observer.py")
    children: dict[int, subprocess.Popen] = {}
    completed = set()
    try:
        while True:
            for pid, child in list(children.items()):
                if child.poll() is not None:
                    completed.add(pid)
                    del children[pid]
            current_pids = process_ids(target.name)
            completed.intersection_update(current_pids)
            for pid in current_pids:
                if pid in children or pid in completed:
                    continue
                candidate = image_path(pid)
                if not candidate or candidate.resolve() != target:
                    continue
                stamp = time.strftime("%Y%m%d-%H%M%S")
                output = args.output_dir / f"blanket-{stamp}-pid{pid}.jsonl"
                command = [sys.executable, str(observer), "--pid", str(pid),
                           "--output", str(output), "--hz", str(args.hz),
                           "--scan-seconds", str(args.scan_seconds)]
                children[pid] = subprocess.Popen(
                    command, creationflags=CREATE_NO_WINDOW,
                    stdin=subprocess.DEVNULL, stdout=subprocess.DEVNULL,
                    stderr=subprocess.DEVNULL)
            time.sleep(max(0.1, args.poll_seconds))
    except KeyboardInterrupt:
        return 0


if __name__ == "__main__":
    raise SystemExit(main())
