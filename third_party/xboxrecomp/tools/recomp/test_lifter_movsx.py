import unittest

from .disasm import Instruction, Operand
from .lifter import Lifter


class MovsxRegisterTest(unittest.TestCase):
    def test_all_word_registers_are_sign_extended(self):
        for source, parent in (("ax", "eax"), ("bx", "ebx"), ("cx", "ecx"),
                               ("dx", "edx"), ("si", "esi"), ("di", "edi"),
                               ("bp", "ebp"), ("sp", "esp")):
            with self.subTest(source=source):
                insn = Instruction(0, 3, "movsx", f"ebx, {source}", "")
                insn.operands = [Operand(type="reg", reg="ebx"),
                                 Operand(type="reg", reg=source)]
                self.assertEqual(Lifter().lift_instruction(insn),
                                 [f"ebx = SX16(LO16({parent}));"])

    def test_retail_bink_self_extension(self):
        insn = Instruction(0x216752, 3, "movsx", "ebp, bp", "0fbfed")
        insn.operands = [Operand(type="reg", reg="ebp"),
                         Operand(type="reg", reg="bp")]
        self.assertEqual(Lifter().lift_instruction(insn),
                         ["ebp = SX16(LO16(ebp));"])

    def test_bp_and_sp_zero_extension_remains_unsigned(self):
        for source, parent in (("bp", "ebp"), ("sp", "esp")):
            with self.subTest(source=source):
                insn = Instruction(0, 3, "movzx", f"eax, {source}", "")
                insn.operands = [Operand(type="reg", reg="eax"),
                                 Operand(type="reg", reg=source)]
                self.assertEqual(Lifter().lift_instruction(insn),
                                 [f"eax = ZX16(LO16({parent}));"])


if __name__ == "__main__":
    unittest.main()
