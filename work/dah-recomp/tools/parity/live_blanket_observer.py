#!/usr/bin/env python3
"""Low-overhead, read-only lifecycle observer for a running DAH recomp.

This observer deliberately records events instead of full RAM dumps.  It finds
retail actor-controller objects by their constructor invariants, follows their
scene transforms, and emits JSONL for lifecycle, state, motion, and anomalies.
It never writes process memory and never sends input to the game.
"""

from __future__ import annotations

import argparse
import ctypes
import hashlib
import json
import math
import struct
import time
from dataclasses import dataclass, field
from pathlib import Path


PROCESS_VM_READ = 0x0010
PROCESS_QUERY_LIMITED_INFORMATION = 0x1000
HOST_OFFSET = 0x10000
GUEST_MIN, GUEST_MAX = 0x10000, 0x08000000
# Exact post-constructor signatures reached by retail pedestrian dispatch
# 00063770.  Names remain address based unless the retail type is proven.
# The 22ECD8 class is known PropType; 226C60 is the pedestrian actor path.
PROFILES = (
    ("actor-225e88", 0x32C, 0x00225E88, 0x0022D480, 0x00225C90, 0x002264DC, 0x00225E28, 0x00226648),
    ("actor-2261a8", 0x534, 0x002261A8, 0x0022D480, 0x00225C90, 0x002264DC, 0x00225FE0, 0x00226648),
    ("actor-226338", 0x378, 0x00226338, 0x0022D480, 0x00225C90, 0x002264DC, 0x00225FE0, 0x00226648),
    ("actor-2264f0", 0x354, 0x002264F0, 0x0022D480, 0x00225C90, 0x002264DC, 0x00226480, 0x00226648),
    ("actor-2268b0", 0x3B4, 0x002268B0, 0x0022D480, 0x00225C90, 0x002264DC, 0x00226850, 0x00226648),
    ("actor-226a80", 0x35C, 0x00226A80, 0x0022D480, 0x00225C90, 0x002264DC, 0x00226A20, 0x00226648),
    ("pedestrian", 0x5C0, 0x00226C60, 0x0022D480, 0x00226C44, 0x002264DC, 0x00226BE8, 0x00226648),
    ("actor-229328", 0x130, 0x00229328, 0x00229314, 0x00225C90, 0x0022C8A0, 0x002292B8, 0x00229248),
    ("actor-22e7d0", 0x1A4, 0x0022E7D0, 0x0022D480, 0x00225C90, 0x0022C8A0, 0x0022E770, 0x00226648),
    ("prop", 0x164, 0x0022ECD8, 0x0022D480, 0x00225C90, 0x0022C8A0, 0x0022EC78, 0x00226648),
)
MAX_ENTITY_SIZE = max(profile[1] for profile in PROFILES)


kernel32 = ctypes.WinDLL("kernel32", use_last_error=True)
kernel32.OpenProcess.argtypes = [ctypes.c_uint32, ctypes.c_bool, ctypes.c_uint32]
kernel32.OpenProcess.restype = ctypes.c_void_p
kernel32.ReadProcessMemory.argtypes = [ctypes.c_void_p, ctypes.c_void_p,
                                       ctypes.c_void_p, ctypes.c_size_t,
                                       ctypes.POINTER(ctypes.c_size_t)]
kernel32.ReadProcessMemory.restype = ctypes.c_bool
kernel32.CloseHandle.argtypes = [ctypes.c_void_p]
kernel32.QueryFullProcessImageNameW.argtypes = [ctypes.c_void_p, ctypes.c_uint32,
                                                ctypes.c_wchar_p,
                                                ctypes.POINTER(ctypes.c_uint32)]
kernel32.QueryFullProcessImageNameW.restype = ctypes.c_bool


class Reader:
    def __init__(self, pid: int, host_offset: int):
        self.host_offset = host_offset
        self.handle = kernel32.OpenProcess(
            PROCESS_VM_READ | PROCESS_QUERY_LIMITED_INFORMATION, False, pid)
        if not self.handle:
            raise OSError(ctypes.get_last_error(), "OpenProcess failed")

    def close(self) -> None:
        if self.handle:
            kernel32.CloseHandle(self.handle)
            self.handle = None

    def read(self, address: int, size: int) -> bytes | None:
        if address < GUEST_MIN or size <= 0 or address + size > GUEST_MAX:
            return None
        data = (ctypes.c_ubyte * size)()
        count = ctypes.c_size_t()
        ok = kernel32.ReadProcessMemory(
            self.handle, ctypes.c_void_p(address + self.host_offset), data, size,
            ctypes.byref(count))
        return bytes(data) if ok and count.value == size else None

    def u32(self, address: int) -> int:
        data = self.read(address, 4)
        return struct.unpack_from("<I", data)[0] if data else 0

    def image_path(self) -> Path | None:
        capacity = ctypes.c_uint32(32768)
        buffer = ctypes.create_unicode_buffer(capacity.value)
        if not kernel32.QueryFullProcessImageNameW(self.handle, 0, buffer,
                                                   ctypes.byref(capacity)):
            return None
        return Path(buffer.value)


def u32(data: bytes, offset: int) -> int:
    return struct.unpack_from("<I", data, offset)[0]


def f32(data: bytes, offset: int) -> float:
    return struct.unpack_from("<f", data, offset)[0]


def pointer(value: int) -> bool:
    # Native recomp pointers use the low 64 MiB guest view. Retail Xbox heap
    # pointers in xemu commonly use its 0x80000000 direct-map alias. Accepting
    # both keeps the shared decoder semantic; Reader.read still bounds native
    # process reads to the low view.
    return ((GUEST_MIN <= value < GUEST_MAX) or
            (0x80010000 <= value < 0x84000000)) and value % 4 == 0


def matching_profile(data: bytes, offset: int):
    for profile in PROFILES:
        _, size, vt, vt10, vt14, vt18, vtbc, vtc0 = profile
        if offset + size <= len(data) and (
                u32(data, offset) == vt and
                u32(data, offset + 0x10) == vt10 and
                u32(data, offset + 0x14) == vt14 and
                u32(data, offset + 0x18) == vt18 and
                u32(data, offset + 0xBC) == vtbc and
                u32(data, offset + 0xC0) == vtc0):
            return profile
    return None


def scan_actors(reader: Reader, start: int, end: int) -> dict[int, tuple]:
    data = reader.read(start, end - start)
    if not data:
        return {}
    found = {}
    # Retail heap allocations are 16-byte aligned.  Six exact constructor
    # invariants prevent XBE code/data from being mistaken for live actors.
    for offset in range(0, len(data) - min(profile[1] for profile in PROFILES), 0x10):
        profile = matching_profile(data, offset)
        if profile:
            found[start + offset] = profile
    return found


@dataclass
class Actor:
    address: int
    kind: str
    size: int
    vtable: int
    serial: int
    resource: int
    resource_name: str | None
    scene: int
    render: int
    gate140: int
    object_flags: int | None
    position: tuple[float, float, float] | None
    quaternion: tuple[float, float, float, float] | None
    state_words: tuple[int, ...]
    health_divisor_bits: int | None
    health_current_bits: int | None
    ai_state: int
    ai_state_id: int
    ai_state_name: str | None
    life_state: str | None
    physics_body: int
    physics_vtable: int
    ai_target_53c: int
    ai_target_540: int
    first_seen: float
    last_seen: float
    missing_scans: int = 0
    max_height: float | None = None
    motion_samples: int = 0
    state_events: int = 0
    ai_state_entered: float = 0.0
    last_moved: float = 0.0
    distance_travelled: float = 0.0
    ai_transitions: int = 0
    life_transitions: int = 0
    target_transitions: int = 0
    physics_transitions: int = 0
    render_transitions: int = 0
    anomalies: list[str] = field(default_factory=list)


# Words that are stable enough to expose AI/lifecycle transitions.  Transform
# and intrusive-list storage are reported separately to avoid per-frame floods.
VOLATILE_STATE_OFFSETS = {0x58, 0x11C, 0x120, 0x124, 0x128, 0x13C}
STATE_OFFSETS = tuple(offset for offset in (
    tuple(range(0x38, 0xBC, 4)) + tuple(range(0xC4, 0x134, 4)) +
    (0x138, 0x13C, 0x140, 0x144)) if offset not in VOLATILE_STATE_OFFSETS)


def cstring(reader: Reader, address: int, limit: int = 96) -> str | None:
    data = reader.read(address, limit) if pointer(address) else None
    if not data:
        return None
    end = data.find(b"\0")
    if end < 1 or not all(32 <= byte < 127 for byte in data[:end]):
        return None
    return data[:end].decode("ascii")


RESOURCE_NAMES: dict[int, str | None] = {}


def read_actor(reader: Reader, address: int, profile: tuple, now: float,
               old: Actor | None = None) -> Actor | None:
    kind, size, vtable, *_ = profile
    raw = reader.read(address, size)
    if not raw or matching_profile(raw, 0) != profile:
        return None
    scene = u32(raw, 0x28)
    transform = reader.read(scene, 0x50) if pointer(scene) else None
    position = None
    quaternion = None
    object_flags = None
    if transform:
        candidate = tuple(f32(transform, 0x2C + index * 4) for index in range(3))
        quat = tuple(f32(transform, 0x38 + index * 4) for index in range(4))
        if all(math.isfinite(value) for value in candidate):
            position = candidate
        if all(math.isfinite(value) for value in quat):
            quaternion = quat
        object_flags = u32(transform, 0x4C)
    resource = u32(raw, 0x1C)
    if resource not in RESOURCE_NAMES:
        name_pointer = reader.u32(resource + 0x0C) if pointer(resource) else 0
        RESOURCE_NAMES[resource] = cstring(reader, name_pointer)
    resource_name = RESOURCE_NAMES[resource]
    health_divisor = u32(raw, 0x368) if size >= 0x374 else None
    health_current = u32(raw, 0x370) if size >= 0x374 else None
    ai_state = u32(raw, 0x34C) if kind == "pedestrian" else 0
    ai_descriptor = reader.u32(ai_state + 8) if pointer(ai_state) else 0
    ai_state_id = reader.u32(ai_descriptor) if pointer(ai_descriptor) else 0
    ai_name_pointer = reader.u32(ai_descriptor + 0x0C) if pointer(ai_descriptor) else 0
    ai_state_name = cstring(reader, ai_name_pointer)
    if ai_state_name and "dead" in ai_state_name:
        life_state = "dead"
    elif ai_state_name and ("death" in ai_state_name or "dying" in ai_state_name):
        life_state = "dying"
    elif ai_state_name:
        life_state = "alive"
    else:
        life_state = None
    physics_body = u32(raw, 0x110) if size >= 0x114 else 0
    physics_vtable = reader.u32(physics_body) if pointer(physics_body) else 0
    actor = Actor(
        address=address, kind=kind, size=size, vtable=vtable,
        serial=u32(raw, 8), resource=resource, resource_name=resource_name,
        scene=scene, render=u32(raw, 0x144) if size >= 0x148 else 0,
        gate140=raw[0x140] if size > 0x140 else 0,
        object_flags=object_flags, position=position, quaternion=quaternion,
        state_words=tuple(u32(raw, offset) for offset in STATE_OFFSETS if offset + 4 <= size),
        health_divisor_bits=health_divisor, health_current_bits=health_current,
        ai_state=ai_state, ai_state_id=ai_state_id, ai_state_name=ai_state_name,
        life_state=life_state, physics_body=physics_body,
        physics_vtable=physics_vtable,
        ai_target_53c=u32(raw, 0x53C) if kind == "pedestrian" else 0,
        ai_target_540=u32(raw, 0x540) if kind == "pedestrian" else 0,
        first_seen=old.first_seen if old else now, last_seen=now,
        max_height=old.max_height if old else None,
        motion_samples=old.motion_samples if old else 0,
        state_events=old.state_events if old else 0,
        ai_state_entered=old.ai_state_entered if old else now,
        last_moved=old.last_moved if old else now,
        distance_travelled=old.distance_travelled if old else 0.0,
        ai_transitions=old.ai_transitions if old else 0,
        life_transitions=old.life_transitions if old else 0,
        target_transitions=old.target_transitions if old else 0,
        physics_transitions=old.physics_transitions if old else 0,
        render_transitions=old.render_transitions if old else 0,
        anomalies=list(old.anomalies) if old else [])
    if position:
        actor.max_height = (position[2] if actor.max_height is None else
                            max(actor.max_height, position[2]))
    return actor


def ident(actor: Actor) -> dict:
    return {"actor": f"{actor.address:08X}", "class": actor.kind,
            "vtable": f"{actor.vtable:08X}", "serial": actor.serial,
            "resource": f"{actor.resource:08X}",
            "resourceName": actor.resource_name,
            "render": f"{actor.render:08X}", "stateByte140": actor.gate140,
            "aiState": f"{actor.ai_state:08X}" if actor.ai_state else None,
            "aiStateId": f"{actor.ai_state_id:08X}" if actor.ai_state_id else None,
            "aiStateName": actor.ai_state_name, "lifeState": actor.life_state,
            "physicsBody": f"{actor.physics_body:08X}" if actor.physics_body else None,
            "physicsVtable": f"{actor.physics_vtable:08X}" if actor.physics_vtable else None,
            "aiTarget53C": f"{actor.ai_target_53c:08X}" if actor.ai_target_53c else None,
            "aiTarget540": f"{actor.ai_target_540:08X}" if actor.ai_target_540 else None}


def rounded(values: tuple[float, ...] | None) -> list[float] | None:
    return [round(value, 5) for value in values] if values else None


def emit(output, kind: str, now: float, tick: int, **fields) -> None:
    output.write(json.dumps({"event": kind, "hostSeconds": now,
                             "worldTick": tick, **fields},
                            separators=(",", ":")) + "\n")


def actor_summary(actor: Actor, now: float) -> dict:
    return {
        **ident(actor),
        "lifetimeSeconds": round(now - actor.first_seen, 3),
        "stateSeconds": round(now - actor.ai_state_entered, 3),
        "secondsSinceMovement": round(now - actor.last_moved, 3),
        "distanceTravelled": round(actor.distance_travelled, 3),
        "motionSamples": actor.motion_samples,
        "stateEvents": actor.state_events,
        "aiTransitions": actor.ai_transitions,
        "lifeTransitions": actor.life_transitions,
        "targetTransitions": actor.target_transitions,
        "physicsTransitions": actor.physics_transitions,
        "renderTransitions": actor.render_transitions,
        "lastPosition": rounded(actor.position),
        "maxHeight": actor.max_height,
        "anomalies": actor.anomalies,
    }


def census(tracked: dict[int, Actor]) -> dict:
    by_class: dict[str, int] = {}
    by_resource: dict[str, int] = {}
    by_ai_state: dict[str, int] = {}
    by_life: dict[str, int] = {}
    for actor in tracked.values():
        by_class[actor.kind] = by_class.get(actor.kind, 0) + 1
        resource = actor.resource_name or f"{actor.resource:08X}"
        by_resource[resource] = by_resource.get(resource, 0) + 1
        if actor.ai_state_name:
            by_ai_state[actor.ai_state_name] = by_ai_state.get(actor.ai_state_name, 0) + 1
        if actor.life_state:
            by_life[actor.life_state] = by_life.get(actor.life_state, 0) + 1
    return {
        "byClass": dict(sorted(by_class.items())),
        "byResource": dict(sorted(by_resource.items())),
        "byAiState": dict(sorted(by_ai_state.items())),
        "byLifeState": dict(sorted(by_life.items())),
    }


def file_sha256(path: Path | None) -> str | None:
    if not path or not path.is_file():
        return None
    digest = hashlib.sha256()
    with path.open("rb") as source:
        for chunk in iter(lambda: source.read(1024 * 1024), b""):
            digest.update(chunk)
    return digest.hexdigest()


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--pid", type=int, required=True)
    parser.add_argument("--output", type=Path, required=True)
    parser.add_argument("--seconds", type=float, default=600.0)
    parser.add_argument("--hz", type=float, default=10.0)
    parser.add_argument("--scan-seconds", type=float, default=2.0)
    parser.add_argument("--scan-start", type=lambda value: int(value, 0), default=0x02800000)
    parser.add_argument("--scan-end", type=lambda value: int(value, 0), default=0x04000000)
    parser.add_argument("--host-offset", type=lambda value: int(value, 0), default=HOST_OFFSET)
    args = parser.parse_args()
    if args.scan_start >= args.scan_end:
        parser.error("scan start must precede scan end")

    reader = Reader(args.pid, args.host_offset)
    args.output.parent.mkdir(parents=True, exist_ok=True)
    tracked: dict[int, Actor] = {}
    counts: dict[str, int] = {}
    start_time = time.time()
    deadline = time.perf_counter() + args.seconds
    next_sample = time.perf_counter()
    next_scan = next_sample
    next_heartbeat = next_sample
    last_heartbeat_time = start_time
    last_heartbeat_tick = 0
    stalled_heartbeats = 0
    observed_life_state = False
    observed_ai_state_name = False
    image_path = reader.image_path()

    def count(kind: str) -> None:
        counts[kind] = counts.get(kind, 0) + 1

    try:
        with args.output.open("x", encoding="utf-8", buffering=1) as output:
            emit(output, "run-start", start_time, 0, pid=args.pid,
                 observer="blanket-v2", sampleHz=args.hz,
                 executable=str(image_path) if image_path else None,
                 executableSha256=file_sha256(image_path),
                 scanSeconds=args.scan_seconds,
                 scanRange=[f"{args.scan_start:08X}", f"{args.scan_end:08X}"],
                 coverage=["actor-lifecycle", "actor-state", "actor-transform",
                           "visibility-flags", "unexpected-despawn",
                           "teleport", "nonfinite-transform"])
            while time.perf_counter() < deadline:
                perf_now = time.perf_counter()
                now = time.time()
                world = reader.u32(0x00286768)
                tick = reader.u32(world + 8) if pointer(world) else 0

                if perf_now >= next_scan:
                    found = scan_actors(reader, args.scan_start, args.scan_end)
                    for address, profile in found.items():
                        if address not in tracked:
                            actor = read_actor(reader, address, profile, now)
                            if actor:
                                tracked[address] = actor
                                observed_life_state |= actor.life_state is not None
                                observed_ai_state_name |= actor.ai_state_name is not None
                                emit(output, "actor-spawn", now, tick, **ident(actor),
                                     scene=f"{actor.scene:08X}",
                                     position=rounded(actor.position))
                                count("actor-spawn")
                        else:
                            tracked[address].missing_scans = 0
                    for address, actor in list(tracked.items()):
                        if address in found:
                            continue
                        actor.missing_scans += 1
                        if actor.missing_scans < 2:
                            continue
                        emit(output, "actor-despawn", now, tick, **ident(actor),
                             history=actor_summary(actor, now),
                             classification="semantics-unresolved")
                        count("actor-despawn")
                        if actor.kind == "pedestrian" and actor.life_state == "alive":
                            emit(output, "anomaly", now, tick, **ident(actor),
                                 code="living-pedestrian-vanished",
                                 detail="No dying/dead AI state was observed before removal")
                            count("anomaly")
                        del tracked[address]
                    next_scan = perf_now + args.scan_seconds

                for address, old in list(tracked.items()):
                    profile = found.get(address)
                    if profile is None:
                        profile = next((item for item in PROFILES if item[2] == old.vtable), None)
                    current = read_actor(reader, address, profile, now, old) if profile else None
                    if not current:
                        continue
                    observed_life_state |= current.life_state is not None
                    observed_ai_state_name |= current.ai_state_name is not None
                    if current.serial != old.serial:
                        emit(output, "anomaly", now, tick, **ident(current),
                             code="actor-address-reused", previousSerial=old.serial)
                        count("anomaly")
                    changes = []
                    for index, (before, after) in enumerate(zip(old.state_words,
                                                                current.state_words)):
                        if before != after:
                            changes.append({"offset": f"{STATE_OFFSETS[index]:03X}",
                                            "before": f"{before:08X}",
                                            "after": f"{after:08X}"})
                    if changes or current.gate140 != old.gate140 or current.render != old.render:
                        current.state_events += 1
                        if current.render != old.render:
                            current.render_transitions += 1
                        emit(output, "actor-state", now, tick, **ident(current),
                             previousStateByte140=old.gate140,
                             previousRender=f"{old.render:08X}", changes=changes)
                        count("actor-state")
                    if (current.ai_state != old.ai_state or
                            current.ai_state_id != old.ai_state_id or
                            current.ai_state_name != old.ai_state_name or
                            current.life_state != old.life_state or
                            current.physics_vtable != old.physics_vtable or
                            current.ai_target_53c != old.ai_target_53c or
                            current.ai_target_540 != old.ai_target_540):
                        ai_changed = (current.ai_state != old.ai_state or
                                      current.ai_state_id != old.ai_state_id or
                                      current.ai_state_name != old.ai_state_name)
                        life_changed = current.life_state != old.life_state
                        target_changed = (current.ai_target_53c != old.ai_target_53c or
                                          current.ai_target_540 != old.ai_target_540)
                        physics_changed = current.physics_vtable != old.physics_vtable
                        previous_state_seconds = now - old.ai_state_entered
                        if ai_changed:
                            current.ai_transitions += 1
                            current.ai_state_entered = now
                        if life_changed:
                            current.life_transitions += 1
                        if target_changed:
                            current.target_transitions += 1
                        if physics_changed:
                            current.physics_transitions += 1
                        emit(output, "ai-state", now, tick, **ident(current),
                             previousStateSeconds=round(previous_state_seconds, 3),
                             previousState=f"{old.ai_state:08X}" if old.ai_state else None,
                             previousStateId=(f"{old.ai_state_id:08X}"
                                              if old.ai_state_id else None),
                             previousStateName=old.ai_state_name,
                             previousLifeState=old.life_state,
                             previousPhysicsVtable=(f"{old.physics_vtable:08X}"
                                                    if old.physics_vtable else None),
                             previousTarget53C=(f"{old.ai_target_53c:08X}"
                                                if old.ai_target_53c else None),
                             previousTarget540=(f"{old.ai_target_540:08X}"
                                                if old.ai_target_540 else None))
                        count("ai-state")
                        if old.life_state == "dead" and current.life_state == "alive":
                            current.anomalies.append("dead-pedestrian-became-alive")
                            emit(output, "anomaly", now, tick, **ident(current),
                                 code="dead-pedestrian-became-alive",
                                 previousStateName=old.ai_state_name)
                            count("anomaly")
                    if current.position and old.position:
                        distance = math.dist(current.position, old.position)
                        current.motion_samples += 1
                        current.distance_travelled += distance
                        if distance > 0.02:
                            current.last_moved = now
                        if distance > 250.0:
                            emit(output, "anomaly", now, tick, **ident(current),
                                 code="large-transform-jump", distance=round(distance, 3),
                                 before=rounded(old.position), after=rounded(current.position))
                            count("anomaly")
                    if current.position is None and old.position is not None:
                        emit(output, "anomaly", now, tick, **ident(current),
                             code="invalid-transform", scene=f"{current.scene:08X}")
                        count("anomaly")
                    tracked[address] = current

                if perf_now >= next_heartbeat:
                    heartbeat_seconds = max(now - last_heartbeat_time, 1e-9)
                    tick_delta = ((tick - last_heartbeat_tick) & 0xFFFFFFFF
                                  if last_heartbeat_tick else 0)
                    tick_rate = tick_delta / heartbeat_seconds if last_heartbeat_tick else None
                    stalled_heartbeats = (stalled_heartbeats + 1
                                          if last_heartbeat_tick and tick_delta == 0 else 0)
                    emit(output, "heartbeat", now, tick, actors=len(tracked),
                         counts=counts, census=census(tracked),
                         tickDelta=tick_delta,
                         observedTickRate=(round(tick_rate, 3)
                                           if tick_rate is not None else None),
                         stalledHeartbeats=stalled_heartbeats)
                    last_heartbeat_time = now
                    last_heartbeat_tick = tick
                    next_heartbeat = perf_now + 1.0
                next_sample += 1.0 / max(1.0, args.hz)
                delay = next_sample - time.perf_counter()
                if delay > 0:
                    time.sleep(delay)
                else:
                    next_sample = time.perf_counter()

            end_time = time.time()
            for actor in tracked.values():
                emit(output, "actor-summary", end_time, 0,
                     **actor_summary(actor, end_time))
                count("actor-summary")
            emit(output, "run-end", end_time, 0,
                 durationSeconds=round(end_time - start_time, 3),
                 actorsRemaining=len(tracked), counts=counts,
                 coverage={
                     "actorLifecycle": counts.get("actor-spawn", 0) > 0,
                     "stateTransitions": counts.get("actor-state", 0) > 0,
                     "aiTransitions": counts.get("ai-state", 0) > 0,
                     "despawns": counts.get("actor-despawn", 0) > 0,
                     "anomalies": counts.get("anomaly", 0) > 0,
                     "damageCause": False,
                     "aliveDeadMeaning": observed_life_state,
                     "effectOwnership": False,
                     "aiTaskNames": observed_ai_state_name,
                 })
    finally:
        reader.close()
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
