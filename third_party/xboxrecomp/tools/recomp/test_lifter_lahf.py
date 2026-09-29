import unittest

from .disasm import BasicBlock, Instruction, Operand
from .lifter import Lifter, lift_basic_block


def reg(name):
    return Operand(type="reg", reg=name)


def pair(mnemonic="ucomiss", lhs=None, rhs=None):
    compare = Instruction(0xFA3D8, 3, mnemonic, "xmm1, xmm0", "0f2ec8")
    compare.operands = [lhs or reg("xmm1"), rhs or reg("xmm0")]
    return [compare, Instruction(0xFA3DB, 1, "lahf", "", "9f")]


class LahfLifterTest(unittest.TestCase):
    def test_both_single_precision_compare_forms_and_operand_orders(self):
        for mnemonic in ("comiss", "ucomiss"):
            for lhs, rhs in (("xmm0", "xmm1"), ("xmm1", "xmm0")):
                with self.subTest(mnemonic=mnemonic, lhs=lhs):
                    code, state = lift_basic_block(Lifter(), BasicBlock(
                        start=0xFA3D8, instructions=pair(mnemonic, reg(lhs), reg(rhs))))
                    self.assertEqual(code, [
                        f"_flags = RECOMP_COMISS_LAHF({lhs}.f[0], {rhs}.f[0]);"
                        f" /* {mnemonic} flags snapshot */",
                        "SET_HI8(eax, _flags); /* lahf */"])
                    self.assertEqual(state[0], mnemonic)

    def test_memory_operand_is_read_before_ah_write_and_carry_survives(self):
        lifter = Lifter()
        lifter.needs_cf = True
        rhs = Operand(type="mem", mem_base="eax", mem_disp=4, mem_size=4)
        code, _ = lift_basic_block(lifter, BasicBlock(
            start=0, instructions=pair(rhs=rhs)))
        self.assertIn("RECOMP_COMISS_LAHF(xmm1.f[0], MEMF(eax + 4))", code[0])
        self.assertEqual(code[1], "SET_HI8(eax, _flags); /* lahf */")
        self.assertEqual(code[2], "_cf = (int)(_flags & 1u); /* compare CF */")

    def test_retail_test_ah_and_parity_branch_are_preserved(self):
        test = Instruction(0xFA3DC, 3, "test", "ah, 0x44", "f6c444")
        test.operands = [reg("ah"), Operand(type="imm", imm=0x44)]
        for mnemonic in ("jp", "jnp"):
            jump = Instruction(0xFA3DF, 2, mnemonic, "0xFA443", "")
            jump.jump_target = 0xFA443
            code, state = lift_basic_block(Lifter(), BasicBlock(
                start=0xFA3D8, instructions=pair() + [test, jump]))
            generated = "\n".join(code)
            self.assertIn("SET_HI8(eax, _flags)", generated)
            self.assertIn("HI8(eax)", code[-1] if "HI8(eax)" in code[-1] else generated)
            self.assertIn("RECOMP_PARITY8", code[-1])
            self.assertEqual(state[0], "test")
            self.assertEqual("!RECOMP_PARITY8" in code[-1], mnemonic == "jnp")

    def test_unrelated_lahf_is_not_fused_to_stale_float_operands(self):
        instructions = pair()
        intervening = Instruction(0xFA3DB, 2, "test", "eax, eax", "85c0")
        intervening.operands = [reg("eax"), reg("eax")]
        instructions.insert(1, intervening)
        code, _ = lift_basic_block(Lifter(), BasicBlock(start=0, instructions=instructions))
        self.assertNotIn("SET_HI8(eax, _flags)", "\n".join(code))
        self.assertEqual("\n".join(code).count("RECOMP_COMISS_LAHF"), 1)


if __name__ == "__main__":
    unittest.main()
