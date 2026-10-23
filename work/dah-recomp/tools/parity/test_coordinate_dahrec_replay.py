from __future__ import annotations

import importlib.util
from pathlib import Path
import struct
import sys
import unittest


MODULE_PATH = Path(__file__).with_name("coordinate_dahrec_replay.py")
SPEC = importlib.util.spec_from_file_location("coordinate_dahrec_replay", MODULE_PATH)
MODULE = importlib.util.module_from_spec(SPEC)
assert SPEC.loader is not None
sys.modules[SPEC.name] = MODULE
sys.path.insert(0, str(MODULE_PATH.parent))
SPEC.loader.exec_module(MODULE)


def float_bits(value: float) -> int:
    return struct.unpack("<I", struct.pack("<f", value))[0]


class CoordinatorReadinessTests(unittest.TestCase):
    def status(self, position=(1.0, 2.0, 3.0)) -> dict:
        identity = {
            "backendName": r"blocks\sites\farm",
            "actorPositionBits": [float_bits(value) for value in position],
        }
        return {
            "captureAligned": True,
            "presentationAligned": True,
            "divergent": False,
            "semanticDiff": {},
            "drift": {},
            "referenceIdentity": identity,
            "nativeIdentity": dict(identity),
        }

    def test_accepts_only_the_recorded_aligned_checkpoint(self):
        self.assertTrue(MODULE.ready(
            self.status(), r"blocks\sites\farm", (1.0, 2.0, 3.0), 0.01
        ))
        self.assertFalse(MODULE.ready(
            self.status((20.0, 2.0, 3.0)), r"blocks\sites\farm", (1.0, 2.0, 3.0), 0.01
        ))

    def test_rejects_visual_or_semantic_divergence(self):
        for field, value in (
            ("presentationAligned", False),
            ("divergent", True),
            ("semanticDiff", {"rngState": {}}),
        ):
            with self.subTest(field=field):
                status = self.status()
                status[field] = value
                self.assertFalse(MODULE.ready(
                    status, r"blocks\sites\farm", (1.0, 2.0, 3.0), 0.01
                ))


if __name__ == "__main__":
    unittest.main()
