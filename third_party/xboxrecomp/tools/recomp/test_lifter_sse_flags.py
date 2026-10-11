"""COMISS flags must survive changes to its operands before a consumer.

Run with ``python -m unittest tools.recomp.test_lifter_sse_flags``. The native
execution regression uses RECOMP_TEST_CC (or an available cl/cc) and skips
only that test when no compiler is configured. Windows children stay hidden.
"""
import os
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest
from unittest.mock import patch

from . import config
from .disasm import BasicBlock, Disassembler, Operand
from .lifter import Lifter, _make_condition, lift_basic_block
from .translator import FunctionTranslator


# Retail DAH D4621..D4640: COMISS; five scalar SSE operations; POP ESI; JBE.
# The original input is [esp+14]. POP changes which word that address names.
RETAIL_ACOS = bytes.fromhex(
    "0f2f542414 f30f104c240c f30f5ccc f30f59c8 f30f58cb f30f114c2404 5e 7611")


def decode(raw, address=0x10000):
    return Disassembler().disassemble_function(raw, address, address + len(raw))


def lift(raw, address=0x10000, carry=False):
    lifter = Lifter()
    lifter.needs_cf = carry
    return lift_basic_block(lifter, BasicBlock(address, decode(raw, address)))


class SseFlagSnapshotTest(unittest.TestCase):
    def test_retail_acos_snapshots_before_sse_and_pop(self):
        code, state = lift(RETAIL_ACOS, 0xD4621)
        self.assertEqual(state[0], "comiss")
        self.assertIn("RECOMP_COMISS_LAHF(xmm2.f[0], MEMF(esp + 0x14))", code[0])
        self.assertTrue(any("POP32(esp, esi)" in line for line in code[1:-1]))
        self.assertIn("if ((_flags & 0x41))", code[-1])
        # A standalone block emits a cross-block call while a complete
        # function may emit a local goto. Both must retain the retail target.
        self.assertIn("000D4652", code[-1])
        self.assertNotIn("MEMF", code[-1])

    def test_all_flag_consumers_use_saved_flags_after_operand_mutation(self):
        # COMISS XMM0,[EAX]; overwrite XMM0, EAX, and memory before JE/SETBE/CMOVA.
        prefix = bytes.fromhex("0f2f00 0f57c0 8bc1 f30f1100")
        for consumer in ("7400", "0f96c2", "0f47d1"):
            with self.subTest(consumer=consumer):
                code, state = lift(prefix + bytes.fromhex(consumer))
                self.assertEqual(state[0], "comiss")
                self.assertIn("RECOMP_COMISS_LAHF(xmm0.f[0], MEMF(eax))", code[0])
                self.assertIn("_flags", code[-1])
                self.assertNotIn("MEMF", code[-1])
                self.assertNotIn("xmm", code[-1])

    def test_ucomiss_and_cross_block_consumers(self):
        lifter = Lifter()
        code, state = lift_basic_block(lifter, BasicBlock(
            0x10000, decode(bytes.fromhex("0f2ec1"))))
        self.assertIn("RECOMP_COMISS_LAHF(xmm0.f[0], xmm1.f[0])", code[0])
        code, state = lift_basic_block(lifter, BasicBlock(
            0x10003, decode(bytes.fromhex("0f57c0 5e 7600"), 0x10003)), state)
        self.assertEqual(state[0], "ucomiss")
        self.assertIn("if ((_flags & 0x41))", code[-1])

    def test_lahf_after_preserving_instructions_and_carry_use_snapshot(self):
        code, state = lift(bytes.fromhex("0f2f00 8bc1 9f 11d2"), carry=True)
        self.assertIn("RECOMP_COMISS_LAHF", code[0])
        self.assertEqual(code[1], "_cf = (int)(_flags & 1u); /* compare CF */")
        self.assertIn("SET_HI8(eax, _flags); /* lahf */", code)
        self.assertEqual(state[0], "adc")

    def test_new_flag_setter_replaces_compare_state(self):
        code, state = lift(bytes.fromhex("0f2fc1 85c0 7600"))
        self.assertEqual(state[0], "test")
        self.assertNotIn("_flags", code[-1])

    def test_translator_declares_snapshot_without_jcc(self):
        names = ("_SECTIONS", "SECTIONS", "_configured_from", "TEXT_VA_START",
                 "TEXT_VA_END", "RDATA_VA_START", "RDATA_VA_END", "DATA_VA_START",
                 "DATA_VA_END", "KERNEL_THUNK_ADDR", "ENTRY_POINT")
        for raw in ("0f2fc1c3", "0f2ec19fc3", "0f2fc111d2c3"):
            with self.subTest(raw=raw), patch.multiple(
                    config, **{name: getattr(config, name) for name in names}):
                image = bytes.fromhex(raw)
                base = 0x10000
                config._install([config.Section(".text", base, len(image), 0,
                                                len(image), True)],
                                base, base, "sse-flags-test")
                info = {"start": "0x00010000", "end": base + len(image),
                        "_addr": base, "size": len(image)}
                source = FunctionTranslator(image, {base: info}).translate_function(base, info)
                self.assertIn("int _flags = 0;", source)
                self.assertIn("_flags = RECOMP_COMISS_LAHF", source)
                self.assertLess(source.index("int _flags"), source.index("RECOMP_COMISS_LAHF"))

    def test_generated_code_execution_with_old_branch_negative_control(self):
        compiler = (os.environ.get("RECOMP_TEST_CC") or shutil.which("cl")
                    or shutil.which("cc"))
        if not compiler:
            self.skipTest("set RECOMP_TEST_CC to compile the emitted C regression")
        code, _ = lift(RETAIL_ACOS, 0xD4621)
        self.assertIn("(_flags & 0x41)", code[-1])
        # The isolated BasicBlock correctly emits an inter-block tail call.
        # The execution harness supplies that target as a local label, so
        # normalize only the transfer while preserving the emitted condition.
        body = "\n".join(code[:-1] +
                         ["if ((_flags & 0x41)) goto loc_000D4652;"])
        self.assertEqual(body.count("(_flags & 0x41)"), 1)
        old = body.replace("(_flags & 0x41)", "(xmm2.f[0] <= MEMF(esp + 0x14))")

        # Exercise every supported canonical Jcc against all four hardware
        # flag outcomes. The explicit truth table includes unordered inputs;
        # C float <= and == would incorrectly reject that case.
        expected = {
            "ja": [1, 0, 0, 0], "jae": [1, 0, 1, 0],
            "jb": [0, 1, 0, 1], "jbe": [0, 1, 1, 1],
            "je": [0, 0, 1, 1], "jne": [1, 1, 0, 0],
            "jp": [0, 0, 0, 1], "jnp": [1, 1, 1, 0],
            "js": [0, 0, 0, 0], "jns": [1, 1, 1, 1],
            "jo": [0, 0, 0, 0], "jno": [1, 1, 1, 1],
            "jl": [0, 0, 0, 0], "jge": [1, 1, 1, 1],
            "jle": [0, 0, 1, 1], "jg": [1, 1, 0, 0],
        }
        truth_checks = []
        operands = [Operand(type="reg", reg="xmm0"), Operand(type="reg", reg="xmm1")]
        for mnemonic, values in expected.items():
            condition, _ = _make_condition(mnemonic, "comiss", operands)
            truth_checks.append("{ const int expected[] = {%s}; CHECK(!!(%s) == expected[i]); }"
                                % (", ".join(map(str, values)), condition))
        source = C_HARNESS.replace("@FIXED@", body).replace("@OLD@", old).replace(
            "@TRUTH@", "\n".join(truth_checks))
        runtime = Path(__file__).resolve().parents[2] / "templates/runtime"
        with tempfile.TemporaryDirectory(prefix="recomp-sse-flags-") as directory:
            temporary = Path(directory)
            test = temporary / "test.c"
            executable = temporary / "test.exe"
            test.write_text(source)
            if Path(compiler).stem.lower() in ("cl", "clang-cl"):
                command = [compiler, "/nologo", "/std:c11", "/O2", "/fp:strict", "/W3",
                           f"/I{runtime}", str(test), f"/Fe{executable}",
                           f"/Fo{temporary / 'test.obj'}"]
            else:
                command = [compiler, "-std=c11", "-O2", "-fno-fast-math", f"-I{runtime}",
                           str(test), "-lm", "-o", str(executable)]
            for invocation in (command, [str(executable)]):
                result = subprocess.run(invocation, cwd=temporary, text=True,
                                        stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                                        creationflags=getattr(subprocess, "CREATE_NO_WINDOW", 0))
                self.assertEqual(result.returncode, 0, result.stdout)
            self.assertIn("negative control reproduced", result.stdout)


C_HARNESS = r'''
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "recomp_types.h"
#define CHECK(c) do { ++checks; if (!(c)) { fprintf(stderr, "line %d\n", __LINE__); exit(1); } } while (0)
ptrdiff_t g_xbox_mem_offset;
static unsigned checks;

static int fixed(float input, float neighbour) {
    int _flags = 0;
    uint32_t esp = 32, esi;
    RecompXmm xmm0 = XMM_SCALAR(1), xmm1, xmm2 = XMM_ZERO();
    RecompXmm xmm3 = XMM_ZERO(), xmm4 = XMM_ZERO();
    MEMF(esp+0x14) = input; MEMF(esp+0x18) = neighbour;
    MEMF(esp+0x0c) = 0.25f;
    @FIXED@
    return 0;
loc_000D4652:
    return 1;
}
static int old(float input, float neighbour) {
    int _flags = 0;
    uint32_t esp = 32, esi;
    RecompXmm xmm0 = XMM_SCALAR(1), xmm1, xmm2 = XMM_ZERO();
    RecompXmm xmm3 = XMM_ZERO(), xmm4 = XMM_ZERO();
    MEMF(esp+0x14) = input; MEMF(esp+0x18) = neighbour;
    MEMF(esp+0x0c) = 0.25f;
    @OLD@
    return 0;
loc_000D4652:
    return 1;
}
int main(void) {
    unsigned i, j, failures = 0;
    uint32_t memory[32] = {0};
    const float samples[] = {-1, -0.94f, -0.01f, -0.0f, 0, 0.01f, 0.94f, 1, NAN};
    const float neighbours[] = {-10, -1, -0.0f, 0, 1, 10, NAN};
    const float lhs[] = {1, -1, 0, NAN}, rhs[] = {0, 0, -0.0f, 0};
    g_xbox_mem_offset = (ptrdiff_t)memory;
    for (i = 0; i < sizeof(samples)/sizeof(*samples); ++i) {
        int expected = isnan(samples[i]) || samples[i] >= 0;
        for (j = 0; j < sizeof(neighbours)/sizeof(*neighbours); ++j) {
            CHECK(fixed(samples[i], neighbours[j]) == expected);
            failures += old(samples[i], neighbours[j]) != expected;
        }
    }
    CHECK(failures > 0);
    for (i = 0; i < 4; ++i) {
        int _flags = RECOMP_COMISS_LAHF(lhs[i], rhs[i]);
        @TRUTH@
    }
    printf("%u generated-code checks passed; negative control reproduced %u failures\n", checks, failures);
    return 0;
}
'''


if __name__ == "__main__":
    unittest.main()
