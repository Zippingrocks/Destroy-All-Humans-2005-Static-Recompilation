#!/usr/bin/env python3
"""Lay out xemu and the recomp with exact, equal client dimensions.

The operation never activates either window. Exact client dimensions are a
precondition for unresampled pixel comparison and keep an enlarged xemu window
from turning host rendering load into apparent game-timing drift.
"""

from __future__ import annotations

import argparse
import ctypes
import json
import time


SW_SHOWNOACTIVATE = 4
SWP_NOZORDER = 0x0004
SWP_NOACTIVATE = 0x0010
SWP_NOOWNERZORDER = 0x0200
SPI_GETWORKAREA = 0x0030


class Rect(ctypes.Structure):
    _fields_ = [("left", ctypes.c_long), ("top", ctypes.c_long),
                ("right", ctypes.c_long), ("bottom", ctypes.c_long)]


user32 = ctypes.WinDLL("user32", use_last_error=True)
EnumProc = ctypes.WINFUNCTYPE(ctypes.c_bool, ctypes.c_void_p, ctypes.c_void_p)
user32.EnumWindows.argtypes = [EnumProc, ctypes.c_void_p]
user32.GetWindowThreadProcessId.argtypes = [ctypes.c_void_p,
                                             ctypes.POINTER(ctypes.c_uint32)]
user32.GetWindowRect.argtypes = [ctypes.c_void_p, ctypes.POINTER(Rect)]
user32.GetClientRect.argtypes = [ctypes.c_void_p, ctypes.POINTER(Rect)]
user32.IsWindowVisible.argtypes = [ctypes.c_void_p]
user32.IsZoomed.argtypes = [ctypes.c_void_p]
user32.IsIconic.argtypes = [ctypes.c_void_p]
user32.ShowWindowAsync.argtypes = [ctypes.c_void_p, ctypes.c_int]
user32.SetWindowPos.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_int,
                                ctypes.c_int, ctypes.c_int, ctypes.c_int,
                                ctypes.c_uint]
user32.SystemParametersInfoW.argtypes = [ctypes.c_uint, ctypes.c_uint,
                                         ctypes.c_void_p, ctypes.c_uint]


def process_window(pid: int) -> int:
    candidates: list[tuple[int, int, int]] = []

    @EnumProc
    def visit(hwnd, _):
        owner = ctypes.c_uint32()
        user32.GetWindowThreadProcessId(hwnd, ctypes.byref(owner))
        if owner.value == pid:
            rect = Rect()
            if user32.GetWindowRect(hwnd, ctypes.byref(rect)):
                area = max(0, rect.right - rect.left) * max(0, rect.bottom - rect.top)
                candidates.append((int(bool(user32.IsWindowVisible(hwnd))), area,
                                   int(hwnd)))
        return True

    if not user32.EnumWindows(visit, None) or not candidates:
        raise RuntimeError(f"process {pid} has no top-level window")
    return max(candidates)[2]


def dimensions(hwnd: int) -> dict:
    outer, client = Rect(), Rect()
    if not user32.GetWindowRect(hwnd, ctypes.byref(outer)):
        raise OSError(ctypes.get_last_error(), "GetWindowRect")
    if not user32.GetClientRect(hwnd, ctypes.byref(client)):
        raise OSError(ctypes.get_last_error(), "GetClientRect")
    return {
        "outer": [outer.left, outer.top, outer.right - outer.left,
                  outer.bottom - outer.top],
        "client": [client.right - client.left, client.bottom - client.top],
    }


def resize_client(hwnd: int, x: int, y: int, width: int, height: int) -> dict:
    if user32.IsZoomed(hwnd) or user32.IsIconic(hwnd):
        if not user32.ShowWindowAsync(hwnd, SW_SHOWNOACTIVATE):
            raise OSError(ctypes.get_last_error(), "ShowWindowAsync")
    if dimensions(hwnd)["client"] == [0, 0]:
        # A process intentionally launched minimized has a 0x0 client until
        # Windows handles the asynchronous show request.  SW_SHOWNOACTIVATE
        # restores its last placement without taking keyboard focus.
        user32.ShowWindowAsync(hwnd, SW_SHOWNOACTIVATE)
        deadline = time.monotonic() + 3.0
        while dimensions(hwnd)["client"] == [0, 0] and time.monotonic() < deadline:
            time.sleep(0.05)
    for _ in range(2):
        current = dimensions(hwnd)
        outer_width = width + current["outer"][2] - current["client"][0]
        outer_height = height + current["outer"][3] - current["client"][1]
        if not user32.SetWindowPos(hwnd, None, x, y, outer_width, outer_height,
                                   SWP_NOZORDER | SWP_NOACTIVATE |
                                   SWP_NOOWNERZORDER):
            raise OSError(ctypes.get_last_error(), "SetWindowPos")
        time.sleep(0.1)
        if dimensions(hwnd)["client"] == [width, height]:
            break
    result = dimensions(hwnd)
    if result["client"] != [width, height]:
        raise RuntimeError(f"client resize failed: expected {width}x{height}, "
                           f"got {result['client'][0]}x{result['client'][1]}")
    return result


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--reference-pid", type=int, required=True)
    parser.add_argument("--native-pid", type=int, required=True)
    parser.add_argument("--client-width", type=int, default=640)
    parser.add_argument("--client-height", type=int, default=480)
    parser.add_argument("--gap", type=int, default=12)
    args = parser.parse_args()
    reference = process_window(args.reference_pid)
    native = process_window(args.native_pid)
    work = Rect()
    if not user32.SystemParametersInfoW(SPI_GETWORKAREA, 0,
                                         ctypes.byref(work), 0):
        raise OSError(ctypes.get_last_error(), "SystemParametersInfoW")
    outer_guess = args.client_width + 32
    if work.right - work.left >= outer_guess * 2 + args.gap:
        reference_xy = (work.left + args.gap, work.top + args.gap)
        native_xy = (work.left + outer_guess + args.gap * 2,
                     work.top + args.gap)
    else:
        reference_xy = (work.left + args.gap, work.top + args.gap)
        native_xy = (work.left + args.gap,
                     work.top + args.client_height + 64 + args.gap * 2)
    report = {
        "schema": 1,
        "captureContract": "equal client dimensions; no resampling",
        "focusChanged": False,
        "reference": resize_client(reference, *reference_xy,
                                   args.client_width, args.client_height),
        "native": resize_client(native, *native_xy,
                                args.client_width, args.client_height),
    }
    print(json.dumps(report, separators=(",", ":")))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
