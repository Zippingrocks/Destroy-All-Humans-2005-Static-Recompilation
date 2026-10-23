#!/usr/bin/env python3
"""Arm one DAHREC1 replay in aligned native and xemu processes."""

from __future__ import annotations

import argparse
import ctypes
from ctypes import wintypes
import json
import math
from pathlib import Path
import socket
import struct
import subprocess
import sys
import time

from dahrec_to_route import read_recording


PROCESS_SUSPEND_RESUME = 0x0800
PROCESS_QUERY_LIMITED_INFORMATION = 0x1000


def write_status(path: Path, **values) -> None:
    value = {"schema": 1, "at": time.time(), **values}
    temporary = path.with_suffix(path.suffix + ".tmp")
    temporary.write_text(json.dumps(value, separators=(",", ":")) + "\n", encoding="utf-8")
    temporary.replace(path)


def process_gate(pid: int, suspend: bool) -> None:
    kernel32 = ctypes.WinDLL("kernel32", use_last_error=True)
    ntdll = ctypes.WinDLL("ntdll")
    kernel32.OpenProcess.argtypes = [wintypes.DWORD, wintypes.BOOL, wintypes.DWORD]
    kernel32.OpenProcess.restype = wintypes.HANDLE
    kernel32.CloseHandle.argtypes = [wintypes.HANDLE]
    kernel32.CloseHandle.restype = wintypes.BOOL
    handle = kernel32.OpenProcess(
        PROCESS_SUSPEND_RESUME | PROCESS_QUERY_LIMITED_INFORMATION, False, pid
    )
    if not handle:
        raise OSError(ctypes.get_last_error(), f"OpenProcess({pid}) failed")
    try:
        function = ntdll.NtSuspendProcess if suspend else ntdll.NtResumeProcess
        function.argtypes = [wintypes.HANDLE]
        function.restype = wintypes.LONG
        status = function(handle)
        if status != 0:
            raise OSError(f"NT process gate returned 0x{status & 0xFFFFFFFF:08X}")
    finally:
        kernel32.CloseHandle(handle)


def qmp_command(port: int, command: str) -> None:
    with socket.create_connection(("127.0.0.1", port), timeout=5) as connection:
        stream = connection.makefile("rwb", buffering=0)
        greeting = json.loads(stream.readline())
        if "QMP" not in greeting:
            raise RuntimeError("xemu QMP greeting missing")
        for execute in ("qmp_capabilities", command):
            stream.write(json.dumps({"execute": execute}).encode() + b"\r\n")
            while True:
                reply = json.loads(stream.readline())
                if "error" in reply:
                    raise RuntimeError(f"QMP {execute} failed: {reply['error']}")
                if "return" in reply:
                    break


def bits_position(identity: dict | None) -> tuple[float, float, float] | None:
    bits = (identity or {}).get("actorPositionBits")
    if not isinstance(bits, list) or len(bits) != 3:
        return None
    try:
        return tuple(struct.unpack("<f", struct.pack("<I", int(item) & 0xFFFFFFFF))[0] for item in bits)
    except (ValueError, TypeError, struct.error):
        return None


def ready(status: dict, backend: str, expected: tuple[float, float, float], tolerance: float) -> bool:
    age = time.time() - float(status.get("at", 0))
    if not 0 <= age <= 0.5:
        return False
    identities = (status.get("referenceIdentity"), status.get("nativeIdentity"))
    for identity in identities:
        if (identity or {}).get("backendName") != backend:
            return False
        actual = bits_position(identity)
        if actual is None or math.dist(actual, expected) > tolerance:
            return False
    return True


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--recording", required=True, type=Path)
    parser.add_argument("--recording-name", required=True)
    parser.add_argument("--session", required=True, type=Path)
    parser.add_argument("--request", required=True, type=Path)
    parser.add_argument("--barrier", required=True, type=Path)
    parser.add_argument("--ready-file", required=True, type=Path)
    parser.add_argument("--start-file", required=True, type=Path)
    parser.add_argument("--trace", required=True, type=Path)
    parser.add_argument("--status", required=True, type=Path)
    parser.add_argument("--gdb-port", type=int, default=1236)
    parser.add_argument("--qmp-port", type=int, default=4446)
    parser.add_argument("--backend", default=r"blocks\sites\farm")
    parser.add_argument("--position-tolerance", type=float, default=2.0)
    parser.add_argument("--wait-seconds", type=float, default=900.0)
    args = parser.parse_args()

    recording = read_recording(args.recording)
    manifest = json.loads((args.session / "manifest.json").read_text(encoding="utf-8-sig"))
    native_pid = int(manifest["nativePid"])
    state_path = Path(manifest["stateStatus"])
    for path in (args.request, args.barrier, args.ready_file, args.start_file, args.trace):
        if path.exists():
            raise FileExistsError(f"coordinator output must be new: {path}")
        path.parent.mkdir(parents=True, exist_ok=True)
    write_status(args.status, state="waiting_for_recorded_checkpoint",
                 recording=str(args.recording), samples=len(recording.samples),
                 checksum=f"{recording.checksum:08X}", backend=args.backend,
                 startPosition=recording.start_position)

    deadline = time.monotonic() + args.wait_seconds
    consecutive = 0
    accepted = None
    while time.monotonic() < deadline:
        try:
            status = json.loads(state_path.read_text(encoding="utf-8-sig"))
        except (OSError, ValueError):
            status = {}
        if ready(status, args.backend, recording.start_position, args.position_tolerance):
            consecutive += 1
            accepted = status
            if consecutive >= 3:
                break
        else:
            consecutive = 0
        time.sleep(0.02)
    if consecutive < 3 or accepted is None:
        write_status(args.status, state="failed", reason="recorded_checkpoint_timeout")
        return 2

    native_suspended = False
    xemu_stopped = False
    adapter = None
    try:
        qmp_command(args.qmp_port, "stop")
        xemu_stopped = True
        process_gate(native_pid, True)
        native_suspended = True
        write_status(args.status, state="arming", acceptedAlignmentAt=accepted.get("at"))
        replay = Path(__file__).with_name("xemu_input_replay.mjs")
        adapter = subprocess.Popen([
            "node", str(replay), "--port", str(args.gdb_port),
            "--dahrec", str(args.recording), "--out", str(args.trace),
            "--barrier", str(args.barrier), "--ready-file", str(args.ready_file),
            "--start-file", str(args.start_file), "--seconds", "1800",
        ], cwd=replay.parent, creationflags=getattr(subprocess, "CREATE_NO_WINDOW", 0))
        ready_deadline = time.monotonic() + 30
        while not args.ready_file.exists() and adapter.poll() is None and time.monotonic() < ready_deadline:
            time.sleep(0.01)
        if not args.ready_file.exists():
            raise RuntimeError(f"xemu replay adapter did not arm (exit={adapter.poll()})")
        args.request.write_text(args.recording_name + "\n", encoding="ascii")
        args.barrier.write_text(json.dumps({
            "schema": 1, "releasedAt": time.time(), "acceptedAlignmentAt": accepted.get("at"),
            "backend": args.backend, "startPosition": recording.start_position,
            "checksum": f"{recording.checksum:08X}", "samples": len(recording.samples),
        }, separators=(",", ":")) + "\n", encoding="utf-8")
        args.start_file.write_text("start\n", encoding="ascii")
        qmp_command(args.qmp_port, "cont")
        xemu_stopped = False
        process_gate(native_pid, False)
        native_suspended = False
        write_status(args.status, state="replaying", adapterPid=adapter.pid,
                     releasedAt=time.time(), acceptedAlignmentAt=accepted.get("at"),
                     startingBlockers={
                         "semanticDiff": accepted.get("semanticDiff") or {},
                         "drift": accepted.get("drift") or {},
                         "captureAligned": accepted.get("captureAligned") is True,
                         "presentationAligned": accepted.get("presentationAligned") is True,
                     })
        exit_code = adapter.wait(timeout=1800)
        if exit_code != 0:
            raise RuntimeError(f"xemu replay adapter exited with {exit_code}")
        trace = json.loads(args.trace.read_text(encoding="utf-8"))
        if not trace.get("recording", {}).get("completed"):
            raise RuntimeError("xemu replay ended without recording completion")
        write_status(args.status, state="completed", adapterPid=adapter.pid,
                     samples=trace.get("samples"), events=len(trace.get("events", [])))
        return 0
    except Exception as error:
        write_status(args.status, state="failed", reason=str(error))
        print(f"Replay coordination failed: {error}", file=sys.stderr)
        return 1
    finally:
        if xemu_stopped:
            try:
                qmp_command(args.qmp_port, "cont")
            except Exception:
                pass
        if native_suspended:
            try:
                process_gate(native_pid, False)
            except Exception:
                pass


if __name__ == "__main__":
    raise SystemExit(main())
