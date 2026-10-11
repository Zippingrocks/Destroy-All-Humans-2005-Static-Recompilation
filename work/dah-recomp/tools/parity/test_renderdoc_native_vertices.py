"""Validate a real offline inspector JSONL against its captured raw IA bytes."""
import json
import math
from pathlib import Path
import struct
import sys


def validate(path):
    def reject(value):
        raise ValueError(f'Non-JSON numeric value: {value}')
    rows = [json.loads(line, parse_constant=reject) for line in Path(path).read_text().splitlines()]
    assert rows[0]['kind'] == 'native_vertex_inspection'
    assert rows[-1]['kind'] == 'native_vertex_summary' and rows[-1]['complete']
    draws = rows[1:-1]
    assert len(draws) == rows[-1]['inspectedDraws'] <= 4096
    vertex_count = quad_count = 0
    for row in draws:
        assert row['kind'] == 'native_vertices'
        assert row['readBytes'] <= 65536 and row['sampledVertices'] <= 512
        assert len(row['vertices']) <= 4 and len(row['rawVerticesHex']) <= 4
        assert len(bytes.fromhex(row['rawPrefixHex'])) <= 64
        if row['schema'] is None:
            assert row['vertices'] == [] and not row['boundsComplete']
            continue
        if row['reason'] is not None:
            continue
        stride = row['bindings'][0]['stride']
        assert stride in (28, 48, 52)
        for vertex, raw_hex in zip(row['vertices'], row['rawVerticesHex']):
            raw = bytes.fromhex(raw_hex)
            assert len(raw) == stride
            assert list(struct.unpack_from('<4I', raw)) == vertex['xyzrhwBits']
            assert list(struct.unpack_from('<2I', raw, 20)) == vertex['uvBits']
            assert list(raw[16:20]) == vertex['bgra']
            assert struct.unpack_from('<I', raw, 16)[0] == vertex['colorWord']
            for actual, value in zip(vertex['xyzrhw'] + vertex['uv'],
                                     struct.unpack_from('<4f', raw) + struct.unpack_from('<2f', raw, 20)):
                assert (actual is None) if not math.isfinite(value) else math.isclose(actual, value, rel_tol=6e-9, abs_tol=1e-35)
            vertex_count += 1
        if row['numIndices'] <= 4 and row['boundsComplete']:
            raw_vertices = [bytes.fromhex(v) for v in row['rawVerticesHex']]
            xy = [struct.unpack_from('<2f', v) for v in raw_vertices]
            expected = [min(p[0] for p in xy), min(p[1] for p in xy),
                        max(p[0] for p in xy), max(p[1] for p in xy)]
            assert all(math.isclose(a, b, rel_tol=6e-9, abs_tol=1e-35)
                       for a, b in zip(row['xyBounds'], expected))
            assert row['bgraRange'] == [[min(v[16+k] for v in raw_vertices), max(v[16+k] for v in raw_vertices)] for k in range(4)]
            quad_count += 1
    print(f'{len(draws)} draw rows, {vertex_count} raw/decoded vertices and {quad_count} complete small-draw bounds validated')


if __name__ == '__main__':
    validate(sys.argv[1])
