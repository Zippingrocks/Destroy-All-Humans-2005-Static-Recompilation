from __future__ import annotations

import importlib.util
from pathlib import Path
import sys
import tempfile
import unittest


MODULE_PATH = Path(__file__).with_name("dahrec_to_route.py")
SPEC = importlib.util.spec_from_file_location("dahrec_to_route", MODULE_PATH)
MODULE = importlib.util.module_from_spec(SPEC)
assert SPEC.loader is not None
sys.modules[SPEC.name] = MODULE
SPEC.loader.exec_module(MODULE)


class DahrecToRouteTests(unittest.TestCase):
    def make_recording(self, samples: list[tuple[int, ...]]) -> Path:
        temporary = tempfile.TemporaryDirectory()
        self.addCleanup(temporary.cleanup)
        path = Path(temporary.name) / "test.dahrec"
        payload = b"".join(MODULE.SAMPLE.pack(*sample) for sample in samples)
        checksum = MODULE._checksum(payload)
        header = MODULE.HEADER.pack(
            MODULE.MAGIC, 1, MODULE.HEADER.size, MODULE.SAMPLE.size,
            len(samples), checksum, 0, 1.25, -2.5, 3.75, 0, 0, 0, 0, 0,
        )
        path.write_bytes(header + payload)
        return path

    @staticmethod
    def sample(loop: int, *, a: int = 0, lx: int = 0) -> tuple[int, ...]:
        return (loop, loop + 10, 0, a, 0, 0, 0, 0, 0, 0, 0,
                lx, 0, 0, 0, 0)

    def test_valid_recording_is_compressed_without_losing_frame_spans(self):
        recording = MODULE.read_recording(self.make_recording([
            self.sample(100), self.sample(101, a=255), self.sample(102, a=255),
            self.sample(103), self.sample(104, lx=-1234),
        ]))
        route = MODULE.convert(recording)
        self.assertIn("samples=5", route)
        self.assertIn("recorded_start_position=1.25,-2.5,3.75", route)
        self.assertIn("@relative-frame", route)
        self.assertIn("1 2 0 255 0 0 0 0 0", route)
        self.assertIn("4 1 0 0 0 -1234 0 0 0", route)
        self.assertNotIn("\n0 1 ", route)

    def test_checksum_corruption_is_rejected(self):
        path = self.make_recording([self.sample(0, a=255)])
        data = bytearray(path.read_bytes())
        data[-1] ^= 1
        path.write_bytes(data)
        with self.assertRaisesRegex(ValueError, "checksum mismatch"):
            MODULE.read_recording(path)

    def test_duplicate_loop_is_rejected_because_route_cannot_represent_it(self):
        path = self.make_recording([self.sample(0), self.sample(0, a=255)])
        with self.assertRaisesRegex(ValueError, "not strictly increasing"):
            MODULE.read_recording(path)


if __name__ == "__main__":
    unittest.main()
