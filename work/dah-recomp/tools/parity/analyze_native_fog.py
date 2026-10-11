#!/usr/bin/env python3
"""Summarize fog constants and sampled fog coordinates from vertex inspection."""

import argparse
import collections
import json
import struct


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("inspection_jsonl")
    args = parser.parse_args()
    groups = collections.defaultdict(lambda: {
        "draws": 0, "events": [], "minimum": float("inf"),
        "maximum": -float("inf")})
    with open(args.inspection_jsonl, encoding="utf-8-sig") as source:
        for line in source:
            item = json.loads(line)
            if item.get("kind") != "native_vertices":
                continue
            constants = next((binding for binding in
                              item.get("descriptorBindings", [])
                              if binding.get("stage") == 4 and
                              binding.get("index") == 0 and
                              binding.get("rawDataHex")), None)
            if constants is None:
                continue
            raw = bytes.fromhex(constants["rawDataHex"])
            if len(raw) < 332:
                continue
            fog_color = struct.unpack_from("<4f", raw, 288)
            alpha_ref = struct.unpack_from("<f", raw, 304)[0]
            alpha_func, alpha_test, fog_enable, vertex_valid = \
                struct.unpack_from("<4I", raw, 308)
            vertex_constant = struct.unpack_from("<f", raw, 324)[0]
            stride = item.get("bindings", [{}])[0].get("stride", 0)
            fogs = []
            for vertex_hex in item.get("rawVerticesHex", []):
                vertex = bytes.fromhex(vertex_hex)
                offset = 40 if stride == 52 else 36
                if len(vertex) >= offset + 4:
                    fogs.append(struct.unpack_from("<f", vertex, offset)[0])
            key = (tuple(round(value, 8) for value in fog_color),
                   round(alpha_ref, 8), alpha_func,
                   alpha_test, fog_enable, vertex_valid,
                   round(vertex_constant, 8), stride)
            group = groups[key]
            group["draws"] += 1
            if len(group["events"]) < 8:
                group["events"].append(item["event"])
            if fogs:
                group["minimum"] = min(group["minimum"], *fogs)
                group["maximum"] = max(group["maximum"], *fogs)
    for key, group in sorted(groups.items(), key=lambda pair: -pair[1]["draws"]):
        color, alpha_ref, alpha_func, alpha_test, enabled, valid, constant, stride = key
        fog_range = ("unavailable" if group["minimum"] == float("inf") else
                     f"{group['minimum']:.8g}..{group['maximum']:.8g}")
        print(f"draws={group['draws']} events={group['events']} stride={stride} "
              f"fogColor={color} fogEnable={enabled} vertexValid={valid} "
              f"vertexConstant={constant} sampledFog={fog_range} "
              f"alphaTest={alpha_test} alphaFunc={alpha_func} "
              f"alphaRef={alpha_ref:.8g}")


if __name__ == "__main__":
    main()
