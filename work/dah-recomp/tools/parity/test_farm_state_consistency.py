"""Compare the actual native observer with the actual RAM decoder.

Run test_farm_state_consistency.ps1, or run from a VS x64 developer shell.
--native can select an already compiled test_farm_state_native.c executable.
This creates isolated synthetic memory; it does not inspect, launch, or change
either game process.
"""
import json
from pathlib import Path
import shutil
import struct
import subprocess
import sys
import tempfile
import unittest

from decode_xemu_ram import XboxRam

NATIVE_EXECUTABLE = None
if '--native' in sys.argv:
    argument = sys.argv.index('--native')
    NATIVE_EXECUTABLE = Path(sys.argv[argument + 1]).resolve()
    del sys.argv[argument:argument + 2]


class FarmStateConsistency(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.directory = tempfile.TemporaryDirectory(prefix='dah-farm-state-')
        cls.root = Path(cls.directory.name)
        if NATIVE_EXECUTABLE is not None:
            cls.executable = NATIVE_EXECUTABLE
            return
        cls.executable = cls.root / 'observer.exe'
        compiler = shutil.which('cl.exe')
        if not compiler:
            raise RuntimeError('Run from a VS x64 developer shell (cl.exe required)')
        result = subprocess.run([
            compiler, '/nologo', '/O2', '/std:c11', '/Gy', '/Gw',
            f'/Fo:{cls.root / "observer.obj"}', f'/Fe:{cls.executable}',
            str(Path(__file__).with_name('test_farm_state_native.c')),
            '/link', '/OPT:REF'], cwd=cls.root, capture_output=True, text=True)
        if result.returncode:
            raise RuntimeError(result.stdout + result.stderr)

    @classmethod
    def tearDownClass(cls):
        cls.directory.cleanup()

    def setUp(self):
        self.data = bytearray(64 * 1024 * 1024)
        # Two 4 MiB virtual windows share captured physical RAM.
        self.word(0x3000, 0x83)
        self.word(0x3000 + 512 * 4, 0x83)
        self.addresses = dict(world=0x300000, pending=0x310000, control=0x320000,
                              player=0x330000, actor=0x340000, movement=0x350000,
                              renderer=0x360000, node=0x370000,
                              actor_object=0x398000, actor_node=0x39A000, body=0x39C000,
                              physics_inner=0x3A0000, weapon_manager=0x3A2000,
                              holobob=0x3A3000)
        self.populate()

    def word(self, address, value):
        struct.pack_into('<I', self.data, address & 0x7fffffff, value)

    def populate(self, high=False):
        p = {name: address | (0x80000000 if high else 0)
             for name, address in self.addresses.items()}
        for address, value in [(0x286768, p['world']), (0x25FBFC, p['pending']),
                               (0x25FCEC, p['control']), (0x250E60, p['renderer']),
                               (0x278A58, 0xABCDEF01), (0x258B48, 0xABCDEF01)]:
            self.word(address, value)
        for obj, offset, value in [
            ('world', 0, 0x235780), ('world', 8, 456),
            ('world', 12, 0x42C80000), ('world', 16, 0x3D088889),
            ('world', 0x303C, 0xABCD0100), ('pending', 0x10, 22),
            ('control', 0x38, p['player']), ('player', 0, 0x223344),
            ('player', 0x30, 2), ('player', 0x34, 0),
            ('player', 0x38, p['actor']), ('actor', 0, 0x22C9F8),
            ('actor', 0x130, p['movement']),
            ('movement', 0x14, 0x3DCCCCCD),
            ('movement', 0x18, 0x40000000),
            ('movement', 0x48, 7),
            ('movement', 0x2AC, 0x40400000),
            ('movement', 0x2B0, 0x40800000),
            ('actor', 0x28, p['actor_object']), ('actor', 0x4A0, p['actor_node']),
            ('actor', 0x110, p['body']), ('actor_object', 0, p['actor_node']),
            ('body', 0x0C, p['physics_inner']), ('physics_inner', 0, 0x237968),
            ('actor_object', 0x4C, 3), ('actor_node', 0, 0x234308),
            ('actor_node', 8, 0x12345678), ('body', 0, 0x2376E8),
            ('actor', 0x370, 0x42960000), ('actor', 0x368, 0x42C80000),
            ('renderer', 0xEC, p['node']), ('node', 8, 0x12345678)]:
            self.word(p[obj] + offset, value)
        for obj, offset, count in [('actor', 0x14C, 3), ('renderer', 0x80, 3),
                                  ('renderer', 0x70, 3), ('node', 0x20, 3),
                                  ('node', 0x40, 4), ('node', 0x50, 16)]:
            for i in range(count):
                self.word(p[obj] + offset + i * 4, 0x3F800000 + i)
        self.word(0x2376E8 + 0x90, 0x12BB30)
        for obj, offset, count, base in [
                ('actor_object', 0x2C, 3, 0x40000000),
                ('actor_object', 0x38, 4, 0x3E800000),
                ('actor_node', 0x40, 4, 0x3E000000),
                ('actor_node', 0x50, 16, 0x3F000000),
                ('body', 0x84, 3, 0xBEA74000),
                ('physics_inner', 0x38, 4, 0x3D800000)]:
            for i in range(count):
                self.word(p[obj] + offset + i * 4, base + i)
        name = b'blocks\\sites\\farm "test"\0'
        start = self.addresses['pending'] + 0x50C
        self.data[start:start + len(name)] = name
        self.populate_hud(high)

    def populate_hud(self, high=False):
        window = 0x80000000 if high else 0
        self.hud_objects = [window | (0x380000 + i * 0x1000) for i in range(6)]
        self.hud_links = [window | (0x390000 + i * 0x20) for i in range(5)]
        self.hud_root_link = window | 0x388000
        self.word(0x258470, self.hud_root_link)
        self.word(self.hud_root_link, self.hud_objects[0])
        for index, (obj, name) in enumerate(zip(self.hud_objects,
                ('root', 'main', 'alien', 'healthandconcentration', 'change', 'bar'))):
            start = obj & 0x7fffffff
            self.data[start:start + 0x600] = bytes(0x600)
            self.word(obj, 0x22A8D8 if index == 5 else 0x220000)
            self.word(obj + 4, 0xABCDEF01)  # Activity is only the low byte.
            self.word(obj + 8, self.hud_objects[index - 1] if index else 0)
            encoded = name.encode('ascii') + b'\0'
            self.data[start + 12:start + 12 + len(encoded)] = encoded
            sentinel = obj + 0x44
            link = self.hud_links[index] if index < 5 else sentinel
            self.word(sentinel, link)
            self.word(sentinel + 4, link)
            if index < 5:
                self.word(link, sentinel)
                self.word(link + 4, sentinel)
                self.word(link + 8, self.hud_objects[index + 1])
        bar = self.hud_objects[-1]
        self.word(bar + 0x534, 0xABCDEF01)  # Visibility is also one byte.
        self.word(bar + 0x3F0, 0x3F400000)
        self.word(bar + 0x3F4, 0x3F800000)
        self.word(0x226E38, 0x3E000000)  # Source threshold = 0.125.
        for segment in range(60):
            bits = 0x3F000000 if segment < 20 else 0x3E000000 if segment < 40 else 0xBF000000
            self.word(bar + 0x40C + segment * 4, bits)

    def compare(self):
        capture = self.root / 'fixture.bin'
        capture.write_bytes(self.data[:4 * 1024 * 1024])
        result = subprocess.run([str(self.executable), str(capture)],
                                capture_output=True, text=True, timeout=10)
        self.assertEqual(result.returncode, 0, result.stderr)
        native = json.loads(result.stdout)
        self.assertEqual(native.pop('observer'),
                         dict(source='native-host', presentationHeld=True))
        native.pop('fixture')
        decoded = XboxRam(self.data, 0x3000).farm_state()
        differences = {key: (native.get(key), decoded.get(key))
                       for key in native.keys() | decoded.keys()
                       if native.get(key) != decoded.get(key)}
        self.assertEqual(differences, {})
        return native

    def populate_enemy_bar(self, high=False):
        window = 0x80000000 if high else 0
        main, parent, bar = self.hud_objects[1], window | 0x39E000, window | 0x39F000
        parent_link, bar_link = window | 0x39D000, window | 0x39D020
        self.word(self.hud_links[1], parent_link)
        self.word(parent_link, main + 0x44)
        self.word(parent_link + 4, self.hud_links[1])
        self.word(parent_link + 8, parent)
        for obj, name, owner, vtable in [(parent, b'enemyhealth', main, 0x2350A4),
                                         (bar, b'bar', parent, 0x23511C)]:
            self.word(obj, vtable)
            self.word(obj + 4, 1)
            self.word(obj + 8, owner)
            start = (obj & 0x7fffffff) + 12
            self.data[start:start + len(name) + 1] = name + b'\0'
        self.word(parent + 0x44, bar_link)
        self.word(bar_link, parent + 0x44)
        self.word(bar_link + 4, parent + 0x44)
        self.word(bar_link + 8, bar)
        for offset, values in [(0xB0, (431.0, 64.0, 100.0, 6.0)),
                               (0xD0, (0.7843138, 0.0, 0.0, 0.7843138)),
                               (0x150, (1.0, 1.0))]:
            for i, value in enumerate(values):
                self.word(bar + offset + i * 4, struct.unpack('<I', struct.pack('<f', value))[0])
        self.word(bar + 0x14C, 1)
        return parent, bar

    def populate_holobob(self, high=False):
        window = 0x80000000 if high else 0
        actor = window | self.addresses['actor']
        manager = window | self.addresses['weapon_manager']
        holobob = window | self.addresses['holobob']
        self.word(actor + 0x138, manager)
        for index in range(4):
            self.word(manager + 0x4C + index * 4, holobob)
        self.word(manager + 0x58, holobob)
        self.word(holobob, 0x22FD50)
        self.word(holobob + 0x34, 1)
        self.word(holobob + 0x44, 3)
        self.word(holobob + 0x178, 0x81234560)
        self.word(holobob + 0x17C, 0x89ABCDEF)
        return manager, holobob

    def test_holobob_lifecycle_fields_in_both_windows(self):
        for high in (False, True):
            self.populate(high)
            manager, holobob = self.populate_holobob(high)
            capture = self.root / f'holobob-{int(high)}.bin'
            capture.write_bytes(self.data[:4 * 1024 * 1024])
            process = subprocess.run([str(self.executable), str(capture)],
                                     capture_output=True, text=True, timeout=10)
            self.assertEqual(process.returncode, 0, process.stderr)
            native = json.loads(process.stdout)
            decoded = XboxRam(self.data, 0x3000).farm_state()
            expected = dict(weaponManager=manager, holobobMain=holobob,
                            holobobActive=1, holobobState=3,
                            holobobTarget=0x81234560,
                            holobobToken=0x89ABCDEF)
            for field, value in expected.items():
                self.assertEqual(native[field], value)
                self.assertEqual(decoded[field], value)

    def test_enemy_bar_fields_and_activity_in_both_windows(self):
        for high in (False, True):
            self.populate(high)
            parent, bar = self.populate_enemy_bar(high)
            result = self.compare()
            self.assertEqual(result['hudEnemyBar'], bar)
            self.assertTrue(result['hudEnemyBarComplete'])
            self.assertTrue(result['hudEnemyBarActive'])
            self.assertEqual(result['hudEnemyBarRectBits'], [0x43D78000, 0x42800000, 0x42C80000, 0x40C00000])
            self.assertEqual(result['hudEnemyBarColorBits'], [0x3F48C8CA, 0, 0, 0x3F48C8CA])
            self.assertEqual(result['hudEnemyBarFillBits'], [0x3F800000, 0x3F800000])
            self.assertEqual(result['hudEnemyBarDirection'], 1)
            self.word(parent + 4, 0)
            result = self.compare()
            self.assertTrue(result['hudEnemyBarOwnActive'])
            self.assertFalse(result['hudEnemyBarAncestorsActive'])
            self.assertFalse(result['hudEnemyBarActive'])
            self.word(parent + 4, 1)
            self.word(bar + 4, 0)
            result = self.compare()
            self.assertFalse(result['hudEnemyBarOwnActive'])
            self.assertTrue(result['hudEnemyBarAncestorsActive'])
            self.assertFalse(result['hudEnemyBarActive'])

    def test_enemy_bar_absent_or_wrong_class_stays_unknown(self):
        result = self.compare()
        self.assertIsNone(result['hudEnemyBar'])
        self.assertTrue(result['hudEnemyBarTraversalComplete'])
        self.assertIsNone(result['hudEnemyBarRectBits'])
        self.assertIsNone(result['hudEnemyBarActive'])
        _, bar = self.populate_enemy_bar()
        self.word(bar, 0x123456)
        result = self.compare()
        self.assertEqual(result['hudEnemyBarVtable'], 0x123456)
        self.assertFalse(result['hudEnemyBarComplete'])
        self.assertIsNone(result['hudEnemyBarFillBits'])

    def test_complete_low_and_high_windows(self):
        for high in (False, True):
            with self.subTest(high=high):
                self.populate(high)
                result = self.compare()
                self.assertTrue(all(result[k] for k in ('worldComplete', 'playerComplete',
                                                       'actorComplete', 'cameraComplete')))
                self.assertEqual(result['cameraUpdate'], 1)
                self.assertEqual(result['worldPaused'], 0)
                self.assertEqual(result['worldRealtime'], 1)
                self.assertEqual(result['hudShield'], self.hud_objects[-1])
                self.assertTrue(result['hudShieldTraversalComplete'])
                self.assertTrue(result['hudShieldComplete'])
                self.assertTrue(result['hudShieldActive'])
                self.assertTrue(result['hudShieldVisible'])
                self.assertEqual(result['hudShieldFillBits'], [0x3F400000, 0x3F800000])
                self.assertEqual(result['hudShieldPositiveSegments'], 20)
                self.assertTrue(result['hudActorHealthComplete'])
                self.assertEqual(result['hudActorCurrentBits'], 0x42960000)
                self.assertEqual(result['hudActorDivisorBits'], 0x42C80000)
                for prefix in ('actorObject', 'actorSceneNode', 'physicsBody'):
                    self.assertTrue(result[prefix + 'Complete'])
                self.assertEqual(result['actorObjectQuatBits'], [0x3E800000 + i for i in range(4)])
                self.assertEqual(result['actorObjectPositionBits'], [0x40000000 + i for i in range(3)])
                self.assertEqual(result['actorObjectFlags'], 3)
                self.assertEqual(result['actorSceneNodeVtable'], 0x234308)
                self.assertEqual(result['actorSceneQuatBits'], [0x3E000000 + i for i in range(4)])
                self.assertEqual(result['actorSceneWorldBits'], [0x3F000000 + i for i in range(16)])
                self.assertEqual(result['physicsBodyVtable'], 0x2376E8)
                self.assertEqual(result['physicsVelocitySetter'], 0x12BB30)
                self.assertEqual(result['physicsVelocityBits'], [0xBEA74000 + i for i in range(3)])
                self.assertEqual(result['physicsInner'],
                                 self.addresses['physics_inner'] | (0x80000000 if high else 0))
                self.assertEqual(result['physicsInnerVtable'], 0x237968)
                self.assertEqual(result['physicsInnerQuatBits'], [0x3D800000 + i for i in range(4)])
                self.assertTrue(result['physicsInnerComplete'])
                self.assertTrue(result['movementMotionComplete'])
                self.assertEqual(result['movementAngularVelocityBits'], 0x3DCCCCCD)
                self.assertEqual(result['movementHeadingBits'], 0x40000000)
                self.assertEqual(result['movementSteeringBits'], [0x40400000, 0x40800000])

    def test_motion_pointer_failures_do_not_invent_zero_transforms(self):
        for bad in (0, 3, 0x500000, 0xFD000000):
            for offset, pointer, complete, value in (
                    (0x28, 'actorObject', 'actorObjectComplete', 'actorObjectQuatBits'),
                    (0x4A0, 'actorSceneNode', 'actorSceneNodeComplete', 'actorSceneWorldBits'),
                    (0x110, 'physicsBody', 'physicsBodyComplete', 'physicsVelocityBits')):
                with self.subTest(address=hex(bad), field=pointer):
                    self.populate()
                    self.word(self.addresses['actor'] + offset, bad)
                    result = self.compare()
                    self.assertEqual(result[pointer], bad)
                    self.assertFalse(result[complete])
                    self.assertIsNone(result[value])

    def test_motion_wrong_classes_or_velocity_setter_preserve_raw_identity(self):
        self.word(self.addresses['actor_node'], 0x123456)
        self.word(self.addresses['body'], 0x123456)
        result = self.compare()
        self.assertEqual(result['actorSceneNodeVtable'], 0x123456)
        self.assertEqual(result['physicsBodyVtable'], 0x123456)
        self.assertFalse(result['actorSceneNodeComplete'])
        self.assertFalse(result['physicsBodyComplete'])
        self.assertIsNone(result['actorSceneQuatBits'])
        self.assertIsNone(result['physicsVelocityBits'])
        self.assertIsNone(result['physicsVelocitySetter'])
        self.populate()
        self.word(0x2376E8 + 0x90, 0x123456)
        result = self.compare()
        self.assertEqual(result['physicsVelocitySetter'], 0x123456)
        self.assertFalse(result['physicsBodyComplete'])
        self.assertIsNone(result['physicsVelocityBits'])

    def test_motion_fields_preserve_raw_float_bits(self):
        self.word(self.addresses['actor_object'] + 0x38, 0x80000000)
        self.word(self.addresses['actor_node'] + 0x40, 0x7FC00001)
        self.word(self.addresses['body'] + 0x84, 0xFF800000)
        self.word(self.addresses['physics_inner'] + 0x38, 0x80000000)
        result = self.compare()
        self.assertEqual(result['actorObjectQuatBits'][0], 0x80000000)
        self.assertEqual(result['actorSceneQuatBits'][0], 0x7FC00001)
        self.assertEqual(result['physicsVelocityBits'][0], 0xFF800000)
        self.assertEqual(result['physicsInnerQuatBits'][0], 0x80000000)

    def test_movement_pointer_failure_keeps_motion_fields_unknown(self):
        self.word(self.addresses['actor'] + 0x130, 0)
        result = self.compare()
        self.assertFalse(result['moveStateComplete'])
        self.assertFalse(result['movementMotionComplete'])
        self.assertIsNone(result['moveState'])
        self.assertIsNone(result['movementAngularVelocityBits'])
        self.assertIsNone(result['movementHeadingBits'])
        self.assertIsNone(result['movementSteeringBits'])

    def test_null_unaligned_unmapped_out_of_range_roots(self):
        for bad in (0, 3, 0x500000, 0xFD000000):
            with self.subTest(address=hex(bad)):
                for address in (0x286768, 0x25FBFC, 0x25FCEC, 0x250E60):
                    self.word(address, bad)
                result = self.compare()
                self.assertFalse(result['worldComplete'])
                self.assertIsNone(result['worldTick'])
                self.assertIsNone(result['actorPositionBits'])

    def test_wrong_classes(self):
        self.word(self.addresses['world'], 0xDEADBEEF)
        self.word(self.addresses['actor'], 0xDEADBEEF)
        result = self.compare()
        self.assertEqual(result['worldVtable'], 0xDEADBEEF)
        self.assertIsNone(result['worldTick'])
        self.assertIsNone(result['moveState'])
        self.assertFalse(result['hudActorHealthComplete'])
        self.assertIsNone(result['hudActorCurrentBits'])

    def test_pending_invalid_names(self):
        start = self.addresses['pending'] + 0x50C
        for name in (b'X' * 128, b'bad\x01\0', b''):
            with self.subTest(name=name[:12]):
                self.data[start:start + 128] = bytes(128)
                self.data[start:start + len(name)] = name
                result = self.compare()
                self.assertEqual(result['pendingBackendComplete'], name == b'')

    def test_partial_world_header_preserves_vtable(self):
        # Header mapped, flags unavailable: compare each observer's null rules.
        world = 0x3FFF00
        self.word(0x286768, world)
        self.word(world, 0x235780)
        self.compare()

    def test_partial_pending_header_preserves_state(self):
        pending = 0x3FFF00
        self.word(0x25FBFC, pending)
        self.word(pending + 0x10, 22)
        self.compare()

    def test_hud_absent_and_missing_leaf_are_complete_traversals(self):
        for missing in ('root-link', 'root-object', 'leaf'):
            with self.subTest(missing=missing):
                self.populate_hud()
                if missing == 'root-link':
                    self.word(0x258470, 0)
                elif missing == 'root-object':
                    self.word(self.hud_root_link, 0)
                else:
                    sentinel = self.hud_objects[-2] + 0x44
                    self.word(sentinel, sentinel)
                    self.word(sentinel + 4, sentinel)
                result = self.compare()
                self.assertEqual(result['hudShield'], 0)
                self.assertTrue(result['hudShieldTraversalComplete'])
                self.assertFalse(result['hudShieldComplete'])
                self.assertIsNone(result['hudShieldActive'])

    def test_hud_malformed_lists_are_unknown(self):
        for malformed in ('cycle', 'null-next', 'wrong-parent', 'duplicate', 'bad-root-link'):
            with self.subTest(malformed=malformed):
                self.populate_hud()
                if malformed == 'cycle':
                    self.word(self.hud_links[2], self.hud_links[2])
                elif malformed == 'null-next':
                    self.word(self.hud_links[2], 0)
                elif malformed == 'wrong-parent':
                    self.word(self.hud_objects[3] + 8, self.hud_objects[0])
                elif malformed == 'duplicate':
                    extra = 0x391000
                    self.word(self.hud_links[2], extra)
                    self.word(extra, self.hud_objects[2] + 0x44)
                    self.word(extra + 4, self.hud_links[2])
                    self.word(extra + 8, self.hud_objects[3])
                else:
                    self.word(0x258470, 0x500000)
                result = self.compare()
                self.assertIsNone(result['hudShield'])
                self.assertFalse(result['hudShieldTraversalComplete'])
                self.assertFalse(result['hudShieldComplete'])

    def test_hud_inactive_ancestor_and_hidden_leaf(self):
        for ancestor in range(6):
            with self.subTest(ancestor=ancestor):
                self.populate_hud()
                self.word(self.hud_objects[ancestor] + 4, 0xABCDE000)
                self.word(self.hud_objects[-1] + 0x534, 0xABCDEF00)
                result = self.compare()
                self.assertTrue(result['hudShieldComplete'])
                self.assertFalse(result['hudShieldActive'])
                self.assertFalse(result['hudShieldVisible'])

    def test_hud_wrong_leaf_class(self):
        self.word(self.hud_objects[-1], 0xDEADBEEF)
        result = self.compare()
        self.assertTrue(result['hudShieldTraversalComplete'])
        self.assertFalse(result['hudShieldComplete'])
        self.assertIsNone(result['hudShieldFillBits'])
        self.assertIsNone(result['hudShieldPositiveSegments'])

    def test_hud_nonfinite_segments_preserve_other_known_fields(self):
        for value in (0x7FC00001, 0x7F800000, 0xFF800000):
            with self.subTest(bits=hex(value)):
                self.populate_hud()
                self.word(self.hud_objects[-1] + 0x40C + 59 * 4, value)
                result = self.compare()
                self.assertTrue(result['hudShieldTraversalComplete'])
                self.assertFalse(result['hudShieldComplete'])
                self.assertIsNone(result['hudShieldPositiveSegments'])
                self.assertEqual(result['hudShieldFillBits'], [0x3F400000, 0x3F800000])


if __name__ == '__main__':
    unittest.main(verbosity=2)
