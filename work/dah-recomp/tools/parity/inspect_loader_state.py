#!/usr/bin/env python3
"""Read-only snapshot of the retail package loader state in a native run."""

from __future__ import annotations

import argparse
import ctypes
import struct


PROCESS_VM_READ = 0x0010
PROCESS_QUERY_LIMITED_INFORMATION = 0x1000
HOST_OFFSET = 0x10000

kernel32 = ctypes.WinDLL("kernel32", use_last_error=True)
kernel32.OpenProcess.argtypes = [ctypes.c_uint32, ctypes.c_bool, ctypes.c_uint32]
kernel32.OpenProcess.restype = ctypes.c_void_p
kernel32.ReadProcessMemory.argtypes = [ctypes.c_void_p, ctypes.c_void_p,
                                       ctypes.c_void_p, ctypes.c_size_t,
                                       ctypes.POINTER(ctypes.c_size_t)]
kernel32.ReadProcessMemory.restype = ctypes.c_bool


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--pid", type=int, required=True)
    args = parser.parse_args()
    handle = kernel32.OpenProcess(
        PROCESS_VM_READ | PROCESS_QUERY_LIMITED_INFORMATION, False, args.pid)
    if not handle:
        raise OSError(ctypes.get_last_error(), "OpenProcess failed")

    def read(address: int, size: int) -> bytes:
        data = (ctypes.c_ubyte * size)()
        count = ctypes.c_size_t()
        ok = kernel32.ReadProcessMemory(
            handle, ctypes.c_void_p(address + HOST_OFFSET), data, size,
            ctypes.byref(count))
        if not ok or count.value != size:
            raise OSError(ctypes.get_last_error(), f"read {address:08X} failed")
        return bytes(data)

    def u32(address: int) -> int:
        return struct.unpack("<I", read(address, 4))[0]

    manager = 0x0025B1D0
    backend = u32(manager + 0x4A28)
    selected = u32(manager + 0x4A2C)
    vtable = u32(manager)
    print(f"manager={manager:08X} vtable={vtable:08X} update={u32(manager + 0x1C):08X}")
    print(f"flags={u32(manager + 0x4A30):08X} backend={backend:08X} selected={selected:08X}")
    print(f"completion={u32(manager + 0x18):08X} callback={u32(manager + 0x20):08X}")
    print(f"ready_fn={u32(vtable + 0x60):08X} current={u32(0x0025FBF8):08X} pending={u32(0x0025FBFC):08X}")
    singleton = u32(0x0024B87C)
    if 0x10000 <= singleton < 0x08000000:
        gate854 = struct.unpack('<H', read(singleton + 0x854, 2))[0]
        gate8d8 = struct.unpack('<H', read(singleton + 0x8D8, 2))[0]
        print(f"singleton={singleton:08X} gate854={gate854:04X} gate8D8={gate8d8:04X}")
        objects = [u32(singleton + 0x858 + i * 4) for i in range(gate8d8)]
        print("gate8D8_objects=" + ",".join(f"{value:08X}" for value in objects))
        for obj in sorted(set(objects)):
            if 0x10000 <= obj < 0x08000000:
                print(f"  object={obj:08X} vtable={u32(obj):08X} owner={u32(obj + 0x3C):08X} "
                      f"type={u32(obj + 0x40):08X} flags={struct.unpack('<H', read(obj + 0x44, 2))[0]:04X}")
    for label, address in (("backend", backend), ("selected", selected),
                           ("block", 0x0025EFF8), ("stream", 0x0025EFFC)):
        if not 0x10000 <= address < 0x08000000:
            print(f"{label}={address:08X} invalid")
            continue
        words = [u32(address + i * 4) for i in range(28)]
        print(f"{label}={address:08X}: " + " ".join(
            f"+{i * 4:02X}={value:08X}" for i, value in enumerate(words)))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
