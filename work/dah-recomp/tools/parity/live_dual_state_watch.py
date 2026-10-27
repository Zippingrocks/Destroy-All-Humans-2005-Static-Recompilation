#!/usr/bin/env python3
"""Non-invasive live synchronization watcher for DAH1 recomp and retail xemu.

Both processes are sampled with ReadProcessMemory.  The xemu guest is never
paused and no input or guest memory is written.  Each sample is bracketed by
the retail main-loop counter; a changing bracket is rejected as torn rather
than compared.  Once both engines remain in the same semantic state, their
loop/world-tick offsets become the baseline.  Any later offset or semantic
change opens a bounded incident containing pre-roll and post-roll samples.
"""

from __future__ import annotations

import argparse
import collections
import ctypes
import hashlib
import json
import math
import os
import struct
import time
from pathlib import Path


PROCESS_VM_READ = 0x0010
PROCESS_QUERY_INFORMATION = 0x0400
PROCESS_QUERY_LIMITED_INFORMATION = 0x1000
MEM_COMMIT = 0x1000
STILL_ACTIVE = 259
NATIVE_GUEST_OFFSET = 0x10000
XBOX_RAM_SIZE = 0x04000000
CR3 = 0xF000


class MemoryRegion(ctypes.Structure):
    _fields_ = [
        ("BaseAddress", ctypes.c_void_p),
        ("AllocationBase", ctypes.c_void_p),
        ("AllocationProtect", ctypes.c_uint32),
        ("PartitionId", ctypes.c_uint16),
        ("Padding", ctypes.c_uint16),
        ("RegionSize", ctypes.c_size_t),
        ("State", ctypes.c_uint32),
        ("Protect", ctypes.c_uint32),
        ("Type", ctypes.c_uint32),
    ]


kernel32 = ctypes.WinDLL("kernel32", use_last_error=True)
kernel32.OpenProcess.argtypes = [ctypes.c_uint32, ctypes.c_bool, ctypes.c_uint32]
kernel32.OpenProcess.restype = ctypes.c_void_p
kernel32.ReadProcessMemory.argtypes = [ctypes.c_void_p, ctypes.c_void_p,
                                       ctypes.c_void_p, ctypes.c_size_t,
                                       ctypes.POINTER(ctypes.c_size_t)]
kernel32.ReadProcessMemory.restype = ctypes.c_bool
kernel32.VirtualQueryEx.argtypes = [ctypes.c_void_p, ctypes.c_void_p,
                                    ctypes.POINTER(MemoryRegion), ctypes.c_size_t]
kernel32.VirtualQueryEx.restype = ctypes.c_size_t
kernel32.GetExitCodeProcess.argtypes = [ctypes.c_void_p,
                                        ctypes.POINTER(ctypes.c_uint32)]
kernel32.GetExitCodeProcess.restype = ctypes.c_bool
kernel32.CloseHandle.argtypes = [ctypes.c_void_p]


def u32(data: bytes, offset: int = 0) -> int:
    return struct.unpack_from("<I", data, offset)[0]


class ProcessMemory:
    def __init__(self, pid: int):
        self.pid = pid
        self.handle = kernel32.OpenProcess(
            PROCESS_VM_READ | PROCESS_QUERY_INFORMATION |
            PROCESS_QUERY_LIMITED_INFORMATION, False, pid)
        if not self.handle:
            raise OSError(ctypes.get_last_error(), f"OpenProcess({pid})")

    def close(self) -> None:
        if self.handle:
            kernel32.CloseHandle(self.handle)
            self.handle = None

    def running(self) -> bool:
        code = ctypes.c_uint32()
        return bool(kernel32.GetExitCodeProcess(self.handle, ctypes.byref(code))) \
            and code.value == STILL_ACTIVE

    def exit_code(self) -> int | None:
        code = ctypes.c_uint32()
        if not kernel32.GetExitCodeProcess(self.handle, ctypes.byref(code)):
            return None
        return int(code.value)

    def read_host(self, address: int, size: int) -> bytes:
        if size <= 0:
            raise ValueError("invalid read size")
        buffer = (ctypes.c_ubyte * size)()
        actual = ctypes.c_size_t()
        if not kernel32.ReadProcessMemory(
                self.handle, ctypes.c_void_p(address), buffer, size,
                ctypes.byref(actual)) or actual.value != size:
            raise OSError(ctypes.get_last_error(),
                          f"ReadProcessMemory pid={self.pid} address=0x{address:x}")
        return bytes(buffer)


class NativeReader(ProcessMemory):
    def read(self, address: int, size: int) -> bytes:
        if address < 0x10000 or address + size > 0x08000000:
            raise ValueError(f"invalid native guest range 0x{address:x}+0x{size:x}")
        return self.read_host(address + NATIVE_GUEST_OFFSET, size)


class XemuReader(ProcessMemory):
    def __init__(self, pid: int, xbe: Path):
        super().__init__(pid)
        self.signature = xbe_signature(xbe, 0x000DACA0, 32)
        self.ram_base = self.find_ram()

    def physical(self, address: int) -> int:
        if 0x80000000 <= address < 0x84000000:
            return address & 0x03FFFFFF
        if not 0x10000 <= address < 0x08000000:
            raise ValueError(f"invalid xemu guest address 0x{address:x}")
        pde = u32(self.read_host(self.ram_base + (CR3 & 0xFFFFF000) +
                                      (address >> 22) * 4, 4))
        if not pde & 1:
            raise ValueError(f"unmapped PDE for 0x{address:x}")
        if pde & 0x80:
            return (pde & 0xFFC00000) + (address & 0x3FFFFF)
        table = pde & 0xFFFFF000
        pte = u32(self.read_host(self.ram_base + table +
                                      ((address >> 12) & 1023) * 4, 4))
        if not pte & 1:
            raise ValueError(f"unmapped PTE for 0x{address:x}")
        return (pte & 0xFFFFF000) + (address & 0xFFF)

    def read(self, address: int, size: int) -> bytes:
        result = bytearray()
        while size:
            physical = self.physical(address)
            count = min(size, 0x1000 - (physical & 0xFFF))
            if physical + count > XBOX_RAM_SIZE:
                raise ValueError("xemu physical read exceeds Xbox RAM")
            result.extend(self.read_host(self.ram_base + physical, count))
            address += count
            size -= count
        return bytes(result)

    def find_ram(self) -> int:
        address = 0
        maximum = 0x00007FFFFFFFFFFF
        candidates = []
        while address < maximum:
            region = MemoryRegion()
            if not kernel32.VirtualQueryEx(self.handle, ctypes.c_void_p(address),
                                           ctypes.byref(region), ctypes.sizeof(region)):
                break
            base = int(region.BaseAddress or 0)
            size = int(region.RegionSize)
            if region.State == MEM_COMMIT and size == XBOX_RAM_SIZE:
                candidates.append(base)
            next_address = base + max(size, 0x1000)
            if next_address <= address:
                break
            address = next_address
        for base in candidates:
            self.ram_base = base
            try:
                if self.read(0x000DACA0, len(self.signature)) == self.signature:
                    return base
            except (OSError, ValueError):
                pass
        raise RuntimeError("no xemu Xbox RAM allocation matched the retail XBE")


def xbe_signature(path: Path, address: int, size: int) -> bytes:
    data = path.read_bytes()
    image_base = u32(data, 0x104)
    section_count = u32(data, 0x11C)
    section_table = u32(data, 0x120) - image_base
    for index in range(section_count):
        section = section_table + index * 56
        virtual = u32(data, section + 4)
        raw_offset = u32(data, section + 12)
        raw_size = u32(data, section + 16)
        if virtual <= address and address + size <= virtual + raw_size:
            offset = raw_offset + address - virtual
            return data[offset:offset + size]
    raise ValueError("retail XBE signature address is outside raw sections")


def word(reader, address: int) -> int:
    return u32(reader.read(address, 4))


def ascii_field(reader, address: int, size: int) -> str | None:
    raw = reader.read(address, size)
    end = raw.find(b"\0")
    if end < 0 or any(value < 32 or value > 126 for value in raw[:end]):
        return None
    return raw[:end].decode("ascii")


def animation_tick(bits: int | None, hz: float = 60.0) -> int | None:
    if bits is None:
        return None
    value = struct.unpack("<f", struct.pack("<I", bits))[0]
    if not math.isfinite(value) or value < 0:
        return None
    return round(value * hz)


MENU_NAMES = {
    "tthubMain", "options", "optionsController", "optionsAudio",
    "optionsDisplay", "labUpgrade",
}


def selector_path(path: str) -> bool:
    patterns = (
        ("tthubMain/slot", "/underline", 4),
        ("options/slot", "bkgnd", 4),
        ("optionsController/slots/slot", "/bkgnd", 8),
        ("optionsAudio/slots/slot", "/bkgnd", 8),
        ("optionsDisplay/slots/slot", "/bkgnd", 8),
        ("labUpgrade/slots/slot", "/selected", 3),
    )
    for prefix, suffix, maximum in patterns:
        if not path.startswith(prefix):
            continue
        remainder = path[len(prefix):]
        if remainder and remainder[0].isdigit() and 1 <= int(remainder[0]) <= maximum \
                and remainder[1:] == suffix:
            return True
    return False


def guest_pointer(address: int, size: int) -> bool:
    return not (address & 3) and (
        0x10000 <= address <= 0x08000000 - size or
        0x80000000 <= address <= 0x84000000 - size
    )


def ui_identity(reader) -> dict:
    """Return pointer-independent active menu/selector identities.

    This duplicates the bounded, validated retail traversal used by
    dah_parity_state.h. Heap addresses are intentionally omitted because they
    are unrelated between xemu and the recomp.
    """
    root_link = word(reader, 0x00258470)
    root = word(reader, root_link) if root_link else 0
    selectors: list[str] = []
    active_menus: list[str] = []
    active_ui_roots: list[str] = []
    objects: set[int] = set()
    node_count = 0
    complete = True

    def walk(obj: int, parent: int, parent_path: str, depth: int) -> None:
        nonlocal complete, node_count
        if not complete:
            return
        if not guest_pointer(obj, 0x60):
            complete = False
            return
        header = reader.read(obj, 0x60)
        if parent and u32(header, 8) != parent:
            complete = False
            return
        if obj in objects or len(objects) >= 512:
            complete = False
            return
        objects.add(obj)
        if not (u32(header, 4) & 0xFF):
            return
        path = ""
        if depth:
            raw_name = header[0x0C:0x34]
            end = raw_name.find(b"\0")
            if end <= 0 or end >= 40:
                complete = False
                return
            name_bytes = raw_name[:end]
            if any(value < 32 or value >= 127 or value in (34, 47, 92)
                   for value in name_bytes):
                complete = False
                return
            name = name_bytes.decode("ascii")
            if depth == 1:
                active_ui_roots.append(name)
                if name not in MENU_NAMES:
                    return
                active_menus.append(name)
            path = f"{parent_path}/{name}" if parent_path else name
            if len(path) >= 256:
                complete = False
                return
            if selector_path(path):
                if len(selectors) >= 32:
                    complete = False
                    return
                selectors.append(path)
                return
        if depth == 4:
            return
        sentinel = obj + 0x44
        node = u32(header, 0x44)
        list_nodes: set[int] = set()
        while node and node != sentinel:
            if (not guest_pointer(node, 12) or
                    node in list_nodes or len(list_nodes) >= 64 or
                    node_count >= 512):
                complete = False
                return
            list_nodes.add(node)
            node_count += 1
            node_data = reader.read(node, 12)
            child = u32(node_data, 8)
            if child:
                walk(child, obj, path, depth + 1)
            else:
                complete = False
            node = u32(node_data)
        if not node:
            complete = False

    if root:
        walk(root, 0, "", 0)
    return {
        "uiRootPresent": bool(root),
        "activeUiRoots": sorted(set(active_ui_roots)),
        "activeMenus": sorted(set(active_menus)),
        "selectors": sorted(selectors),
        "selectorsComplete": complete,
    }


def sample_once(reader) -> dict:
    loop_before = word(reader, 0x0025B1DC)
    driver_vtable = word(reader, 0x0025B1D0)
    backend = pending = 0
    if driver_vtable == 0x0022B510:
        backend = word(reader, 0x0025FBF8)
        pending = word(reader, 0x0025FBFC)
    renderer = word(reader, 0x00250E60)
    world = word(reader, 0x00286768)
    control = word(reader, 0x0025FCEC)
    player = word(reader, control + 0x38) if control else 0
    actor = word(reader, player + 0x38) if player else 0
    movement = word(reader, actor + 0x130) if actor else 0
    movie = word(reader, 0x0028681C)
    movie_header = ([word(reader, movie + offset)
                     for offset in range(0, 24, 4)] if movie else None)
    ui = ui_identity(reader)
    world_elapsed_bits = word(reader, world + 0x0C) if world else None
    values = {
        "loop": loop_before,
        "backend": backend,
        "backendName": ascii_field(reader, backend + 0x50C, 128) if backend else None,
        "backendState": word(reader, backend + 0x10) if backend else None,
        "pendingBackend": pending,
        "pendingBackendName": ascii_field(reader, pending + 0x50C, 128) if pending else None,
        "refresh": (60 if word(reader, renderer + 0x238) else 50) if renderer else None,
        "divisor": word(reader, renderer + 0x27C) if renderer else None,
        "interval": word(reader, renderer + 0x2C8) if renderer else None,
        "savedBackBufferEnabled": reader.read(renderer + 0x488, 1)[0] if renderer else None,
        "world": world,
        "worldTick": word(reader, world + 8) if world else None,
        "worldElapsedBits": world_elapsed_bits,
        "worldAnimationTick": animation_tick(world_elapsed_bits),
        "worldStepBits": word(reader, world + 0x10) if world else None,
        "worldPaused": reader.read(world + 0x303C, 1)[0] if world else None,
        "worldRealtime": reader.read(world + 0x303D, 1)[0] if world else None,
        "rngState": word(reader, 0x00278A58),
        "movie": movie,
        "movieActive": bool(movie),
        "movieHeader": movie_header,
        "movieWidth": movie_header[0] if movie_header else None,
        "movieHeight": movie_header[1] if movie_header else None,
        "movieFrames": movie_header[2] if movie_header else None,
        "movieFrame": movie_header[3] if movie_header else None,
        "movieLastFrame": movie_header[4] if movie_header else None,
        "movieRate": movie_header[5] if movie_header else None,
        "movieFlags": reader.read(0x002867F4, 1)[0],
        "movieMode": word(reader, 0x002867F8),
        "movieLifecycle": word(reader, 0x00286804),
        "cameraUpdate": reader.read(0x00258B48, 1)[0],
        "playerFocus": word(reader, player + 0x30) if player else None,
        "playerShip": word(reader, player + 0x34) if player else None,
        "playerCrypto": actor if player else None,
        "actorPositionBits": list(struct.unpack("<III", reader.read(actor + 0x14C, 12))) if actor else None,
        "moveState": word(reader, movement + 0x48) if movement else None,
        **ui,
    }
    loop_after = word(reader, 0x0025B1DC)
    if loop_before != loop_after:
        raise RuntimeError("torn-sample")
    return values


def stable_sample(reader, retries: int = 4) -> tuple[dict | None, int]:
    for attempt in range(retries):
        try:
            return sample_once(reader), attempt
        except (OSError, ValueError):
            continue
        except RuntimeError as error:
            if str(error) != "torn-sample":
                raise
    return None, retries


CORE_SEMANTIC_FIELDS = (
    "backendName", "backendState", "pendingBackendName", "refresh", "divisor",
    "interval", "savedBackBufferEnabled", "worldPaused", "worldRealtime",
    "movieActive", "movieWidth", "movieHeight", "movieFrames", "movieRate",
    "movieFlags", "movieMode", "movieLifecycle", "cameraUpdate",
    "playerFocus", "moveState",
)

UI_SEMANTIC_FIELDS = (
    "uiRootPresent", "activeUiRoots", "activeMenus", "selectors",
    "selectorsComplete", "rngState",
)


def semantic_diff(reference: dict, native: dict) -> dict:
    # A full-screen Bink movie owns presentation. Its dormant UI tree may be in
    # a transient or stale list state and cannot invalidate movie alignment.
    fields = CORE_SEMANTIC_FIELDS
    if not reference.get("movieActive") and not native.get("movieActive"):
        fields += UI_SEMANTIC_FIELDS
    differences = {
        field: {"reference": reference.get(field), "native": native.get(field)}
        for field in fields if reference.get(field) != native.get(field)
    }
    if not reference.get("movieActive") and not native.get("movieActive"):
        reference_tick = reference.get("worldAnimationTick")
        native_tick = native.get("worldAnimationTick")
        if (reference_tick is None) != (native_tick is None) or (
                reference_tick is not None and native_tick is not None and
                abs(native_tick - reference_tick) > 1):
            differences["worldAnimationTick"] = {
                "reference": reference_tick, "native": native_tick,
                "allowedSequentialDelta": 1,
            }
    return differences


def append_json(path: Path, row: dict) -> None:
    with path.open("a", encoding="utf-8", buffering=1) as stream:
        stream.write(json.dumps(row, separators=(",", ":")) + "\n")


def optional_rate(current: object, previous: object, elapsed: float) -> float | None:
    """Calculate a counter rate only while both samples expose the counter."""
    if isinstance(current, bool) or isinstance(previous, bool):
        return None
    if not isinstance(current, (int, float)) or not isinstance(previous, (int, float)):
        return None
    if elapsed <= 0:
        return None
    return round((current - previous) / elapsed, 6)


def write_status(path: Path | None, row: dict) -> None:
    if path is None:
        return
    temporary = path.with_suffix(path.suffix + ".tmp")
    payload = json.dumps(row, separators=(",", ":"))
    for attempt in range(4):
        try:
            temporary.write_text(payload, encoding="utf-8")
            os.replace(temporary, path)
            return
        except PermissionError:
            # A concurrent Windows reader can briefly deny replacement. The
            # visual watcher rejects stale status, so retaining the previous
            # complete record is safer than crashing or publishing partial JSON.
            if attempt != 3:
                time.sleep(0.001)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--xemu-pid", type=int, required=True)
    parser.add_argument("--native-pid", type=int, required=True)
    parser.add_argument("--xbe", type=Path, required=True)
    parser.add_argument("--out", type=Path, required=True)
    parser.add_argument("--status-out", type=Path,
                        help="atomically replaced current alignment record")
    parser.add_argument("--hz", type=float, default=20.0)
    parser.add_argument("--pre-seconds", type=float, default=5.0)
    parser.add_argument("--post-seconds", type=float, default=5.0)
    parser.add_argument("--baseline-samples", type=int, default=10)
    parser.add_argument("--baseline-timeout", type=float, default=2.0)
    parser.add_argument("--seconds", type=float, default=0.0,
                        help="zero watches until either process exits")
    args = parser.parse_args()
    if not 1 <= args.hz <= 120:
        parser.error("--hz must be in [1,120]")
    if args.out.exists():
        parser.error("--out must name a new file")
    args.out.parent.mkdir(parents=True, exist_ok=True)
    if args.status_out:
        args.status_out.parent.mkdir(parents=True, exist_ok=True)

    native = NativeReader(args.native_pid)
    xemu = XemuReader(args.xemu_pid, args.xbe)
    period = 1.0 / args.hz
    ring = collections.deque(maxlen=max(1, round(args.pre_seconds * args.hz)))
    started = time.perf_counter()
    next_sample = started
    baseline = None
    baseline_window = collections.deque(
        maxlen=max(args.baseline_samples, round(args.baseline_timeout * args.hz)))
    same_phase_started = None
    incident_until = 0.0
    incident = 0
    last_heartbeat = 0.0
    last_rate_sample = None
    baseline_failure_reported = False
    incident_fingerprints = set()
    append_json(args.out, {
        "event": "run-start", "schema": 1, "source": "dual-live-external",
        "xemuPid": args.xemu_pid, "nativePid": args.native_pid,
        "xemuRamBase": f"0x{xemu.ram_base:x}",
        "xbeSha256": hashlib.sha256(args.xbe.read_bytes()).hexdigest().upper(),
        "hz": args.hz, "consistency": "loop-bracketed-read-only",
        "limitation": "host reads are not a shared presentation latch",
    })
    try:
        while native.running() and xemu.running():
            now = time.perf_counter()
            if args.seconds and now - started >= args.seconds:
                break
            if now < next_sample:
                time.sleep(min(next_sample - now, period))
                continue
            next_sample += period
            pair_started = time.perf_counter_ns()
            reference, reference_retries = stable_sample(xemu)
            split = time.perf_counter_ns()
            native_state, native_retries = stable_sample(native)
            pair_finished = time.perf_counter_ns()
            if reference is None or native_state is None:
                row = {"event": "sample-rejected", "at": time.time(),
                       "referenceRetries": reference_retries,
                       "nativeRetries": native_retries}
                ring.append(row)
                continue
            offsets = {
                "loop": native_state["loop"] - reference["loop"],
                "worldTick": (native_state["worldTick"] - reference["worldTick"]
                              if native_state["worldTick"] is not None and
                              reference["worldTick"] is not None else None),
                "movieFrame": (native_state["movieFrame"] - reference["movieFrame"]
                               if native_state["movieFrame"] is not None and
                               reference["movieFrame"] is not None and
                               native_state["movieFrames"] == reference["movieFrames"]
                               else None),
            }
            differences = semantic_diff(reference, native_state)
            movie_synchronized = (offsets["movieFrame"] is None or
                                  abs(offsets["movieFrame"]) <= 1)
            same_phase = (not differences and movie_synchronized and
                          reference["backendName"] is not None)
            if baseline is None and same_phase:
                if same_phase_started is None:
                    same_phase_started = now
                baseline_window.append(offsets)
                loop_values = [item["loop"] for item in baseline_window]
                tick_values = [item["worldTick"] for item in baseline_window
                               if item["worldTick"] is not None]
                movie_values = [item["movieFrame"] for item in baseline_window
                                if item["movieFrame"] is not None]
                stable_loop = (len(loop_values) >= args.baseline_samples and
                               max(loop_values) - min(loop_values) <= 1)
                stable_tick = (not tick_values or
                               (len(tick_values) >= args.baseline_samples and
                                max(tick_values) - min(tick_values) <= 1))
                stable_movie = (not movie_values or
                                (len(movie_values) >= args.baseline_samples and
                                 max(movie_values) - min(movie_values) <= 1))
                if stable_loop and stable_tick and stable_movie:
                    loop_values.sort()
                    tick_values.sort()
                    movie_values.sort()
                    baseline = {"loopOffset": loop_values[len(loop_values) // 2],
                                "worldTickOffset": (tick_values[len(tick_values) // 2]
                                                    if tick_values else None),
                                "movieFrameOffset": (movie_values[len(movie_values) // 2]
                                                     if movie_values else None),
                                "backendName": reference["backendName"]}
                    append_json(args.out, {"event": "baseline", "at": time.time(), **baseline})
                elif (not baseline_failure_reported and
                      now - same_phase_started >= args.baseline_timeout):
                    baseline_failure_reported = True
                    incident += 1
                    incident_until = now + args.post_seconds
                    detail = {
                        "loopOffsetRange": [min(loop_values), max(loop_values)],
                        "worldTickOffsetRange": ([min(tick_values), max(tick_values)]
                                                 if tick_values else None),
                        "movieFrameOffsetRange": ([min(movie_values), max(movie_values)]
                                                   if movie_values else None),
                        "seconds": round(now - same_phase_started, 6),
                    }
                    append_json(args.out, {
                        "event": "incident-start", "incident": incident,
                        "kind": "baseline-unstable", "at": time.time(),
                        "preSamples": len(ring), "detail": detail,
                        "fingerprint": hashlib.sha256(json.dumps(
                            detail, sort_keys=True).encode()).hexdigest()[:16],
                    })
                    for buffered in ring:
                        append_json(args.out, {**buffered, "incident": incident,
                                               "preRoll": True})
            elif baseline is None:
                same_phase_started = None
                baseline_window.clear()
                baseline_failure_reported = False
            drift = {}
            uncertain = {}
            if offsets["movieFrame"] is not None and abs(offsets["movieFrame"]) > 1:
                drift["movieFrameAbsolute"] = {
                    "required": "same frame (+/-1 for sequential sampling)",
                    "current": offsets["movieFrame"]}
            if baseline is not None:
                for field, offset_key, baseline_key in (
                        ("loopOffset", "loop", "loopOffset"),
                        ("worldTickOffset", "worldTick", "worldTickOffset")):
                    current = offsets[offset_key]
                    expected = baseline[baseline_key]
                    if current is None or expected is None or current == expected:
                        continue
                    delta = current - expected
                    if abs(delta) > 1:
                        drift[field] = {"baseline": expected, "current": current}
                    else:
                        # The two stable snapshots are necessarily sequential.
                        # At an edge, a genuinely locked pair can therefore
                        # alternate between adjacent offsets.  The independent
                        # high-rate phase watcher detects a persistent one-frame
                        # loss without turning this read-order ambiguity into a
                        # false state divergence.
                        uncertain[field] = {"baseline": expected, "current": current,
                                            "sequentialReadDelta": delta}
            row = {
                "event": "sample", "at": time.time(),
                "pairReadUs": round((pair_finished - pair_started) / 1000, 3),
                "splitReadUs": round((pair_finished - split) / 1000, 3),
                "offsets": offsets, "drift": drift, "uncertain": uncertain,
                "semanticDiff": differences,
                "reference": reference, "native": native_state,
            }
            ring.append(row)
            divergent = bool(drift or differences)
            capture_aligned = bool(baseline and not divergent)
            phase_clock_aligned = (
                abs(offsets["movieFrame"]) <= 1
                if offsets["movieFrame"] is not None else
                True
            )
            presentation_aligned = bool(capture_aligned and phase_clock_aligned)
            write_status(args.status_out, {
                "event": "alignment", "at": time.time(), "baseline": baseline,
                "offsets": offsets, "divergent": divergent,
                "captureAligned": capture_aligned, "drift": drift,
                "presentationAligned": presentation_aligned,
                "uncertain": uncertain,
                "semanticDiff": differences,
                "referenceIdentity": {
                    "backendName": reference["backendName"],
                    "activeUiRoots": reference["activeUiRoots"],
                    "activeMenus": reference["activeMenus"],
                    "selectors": reference["selectors"],
                    "selectorsComplete": reference["selectorsComplete"],
                    "worldAnimationTick": reference["worldAnimationTick"],
                    "rngState": reference["rngState"],
                    "actorPositionBits": reference["actorPositionBits"],
                },
                "nativeIdentity": {
                    "backendName": native_state["backendName"],
                    "activeUiRoots": native_state["activeUiRoots"],
                    "activeMenus": native_state["activeMenus"],
                    "selectors": native_state["selectors"],
                    "selectorsComplete": native_state["selectorsComplete"],
                    "worldAnimationTick": native_state["worldAnimationTick"],
                    "rngState": native_state["rngState"],
                    "actorPositionBits": native_state["actorPositionBits"],
                },
            })
            divergence_fingerprint = hashlib.sha256(json.dumps({
                "driftFields": sorted(drift),
                "semanticFields": sorted(differences),
            }, sort_keys=True).encode()).hexdigest()[:16]
            if (divergent and time.perf_counter() >= incident_until and
                    divergence_fingerprint not in incident_fingerprints):
                incident_fingerprints.add(divergence_fingerprint)
                incident += 1
                incident_until = time.perf_counter() + args.post_seconds
                append_json(args.out, {"event": "incident-start", "incident": incident,
                                       "at": time.time(), "preSamples": len(ring),
                                       "fingerprint": divergence_fingerprint})
                for buffered in ring:
                    append_json(args.out, {**buffered, "incident": incident, "preRoll": True})
            elif (divergent and baseline is not None and
                  time.perf_counter() >= incident_until):
                # Keep repeat occurrences countable without duplicating the
                # full pre-roll payload for an already-known failure shape.
                incident += 1
                incident_until = time.perf_counter() + args.post_seconds
                append_json(args.out, {
                    "event": "incident-repeat", "incident": incident,
                    "at": time.time(), "fingerprint": divergence_fingerprint,
                    "offsets": offsets, "drift": drift,
                    "semanticDiff": differences,
                })
            elif time.perf_counter() < incident_until:
                append_json(args.out, {**row, "incident": incident, "preRoll": False})
            if now - last_heartbeat >= 1.0:
                rates = None
                if last_rate_sample is not None:
                    elapsed = now - last_rate_sample[0]
                    previous_reference, previous_native = last_rate_sample[1:]
                    if elapsed > 0:
                        rates = {
                            "referenceLoopHz": optional_rate(reference.get("loop"), previous_reference.get("loop"), elapsed),
                            "nativeLoopHz": optional_rate(native_state.get("loop"), previous_native.get("loop"), elapsed),
                            "referenceWorldTickHz": optional_rate(reference.get("worldTick"), previous_reference.get("worldTick"), elapsed),
                            "nativeWorldTickHz": optional_rate(native_state.get("worldTick"), previous_native.get("worldTick"), elapsed),
                        }
                last_rate_sample = (now, reference, native_state)
                append_json(args.out, {"event": "heartbeat", "at": time.time(),
                                       "baseline": baseline, "offsets": offsets,
                                       "divergent": divergent,
                                       "captureAligned": capture_aligned,
                                       "presentationAligned": presentation_aligned,
                                       "uncertain": uncertain,
                                       "rates": rates,
                                       "pairReadUs": row["pairReadUs"]})
                last_heartbeat = now
            if divergent and baseline is not None:
                # Preserve the failed epoch above, then permit a fresh baseline
                # only after the two engines return to the same semantic state.
                append_json(args.out, {
                    "event": "baseline-reset", "at": time.time(),
                    "reason": "state-or-offset-divergence",
                    "previousBaseline": baseline,
                    "offsets": offsets,
                    "drift": drift,
                    "semanticDiff": differences,
                })
                baseline = None
                baseline_window.clear()
                same_phase_started = None
                baseline_failure_reported = False
                last_rate_sample = None
    finally:
        reference_running = xemu.running()
        native_running = native.running()
        reference_exit_code = xemu.exit_code()
        native_exit_code = native.exit_code()
        native.close()
        xemu.close()
    append_json(args.out, {"event": "run-end", "at": time.time(),
                           "incidents": incident, "baseline": baseline,
                           "referenceRunning": reference_running,
                           "nativeRunning": native_running,
                           "referenceExitCode": reference_exit_code,
                           "nativeExitCode": native_exit_code})
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
