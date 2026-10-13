"""Lift every missing retail callback in the Capitol cinematic table range."""
import argparse
import hashlib
import json
from pathlib import Path
import sys

workspace = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(workspace / "Repos" / "xboxrecomp-main"))

from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from tools.recomp.config import configure_from_xbe, va_to_file_offset
from tools.recomp.translator import FunctionTranslator

CALLBACKS = (
    (0x00021FB0, 0x00021FF8, "neighbor actor initialization callback"),
    (0x00033060, 0x00033202, "cinematic actor transform callback"),
    (0x0003C880, 0x0003C892, "cinematic runtime type-query callback"),
    (0x0003E190, 0x0003E1AB, "cinematic effect type-query callback"),
    (0x0003F9D0, 0x0003FA8F, "cinematic scene activation callback"),
)

def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--source", type=Path)
    parser.add_argument("--evidence", type=Path)
    args = parser.parse_args()
    xbe = workspace / "work" / "default.xbe"
    configure_from_xbe(str(xbe))
    data = xbe.read_bytes()
    funcs = {s: {"name": f"sub_{s:08X}", "end": e} for s, e, _ in CALLBACKS}
    dis = Cs(CS_ARCH_X86, CS_MODE_32)
    output = [
        "/* Generated only from the retail XBE for the Capitol cinematic callback set. */",
        '#define RECOMP_GENERATED_CODE\n#include "recomp_funcs.h"\n',
    ]
    rows = []
    for start, end, purpose in CALLBACKS:
        off = va_to_file_offset(start)
        code_bytes = data[off:off + end - start]
        insns = list(dis.disasm(code_bytes, start))
        assert insns and insns[-1].address + insns[-1].size == end
        assert sum(i.size for i in insns) == end - start
        assert data[va_to_file_offset(end)] == 0xCC
        code = FunctionTranslator(data, funcs).translate_function(start, funcs[start])
        assert code is not None
        output.append(code)
        rows.append({
            "start": f"0x{start:08X}", "end": f"0x{end:08X}",
            "bytes": end - start, "instructions": len(insns), "purpose": purpose,
            "codeBytesSha256": hashlib.sha256(code_bytes).hexdigest().upper(),
        })
    text = "\n".join(output)
    evidence = {"schema": 1, "source": "retail-xbe-only",
                "retailXbeSha256": hashlib.sha256(data).hexdigest().upper(),
                "callbacks": rows}
    if args.source:
        args.source.write_text(text, encoding="utf-8")
    if args.evidence:
        args.evidence.write_text(json.dumps(evidence, indent=2) + "\n", encoding="utf-8")
    if not args.source and not args.evidence:
        print(text)
    return 0

if __name__ == "__main__":
    raise SystemExit(main())
