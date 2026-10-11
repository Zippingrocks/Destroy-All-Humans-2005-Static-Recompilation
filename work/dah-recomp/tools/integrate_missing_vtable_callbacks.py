"""Integrate the retail vtable lifts into manual dispatch and seed discovery."""

import json
from pathlib import Path


repo = Path(__file__).resolve().parents[1]
evidence_path = repo / "tools/analysis/results/missing-vtable-callback-evidence.json"
evidence = json.loads(evidence_path.read_text(encoding="utf-8"))
addresses = [int(row["start"], 16) for row in evidence["callbacks"]]


def replace_block(path: Path, begin: str, end: str, body: str, anchor: str) -> None:
    text = path.read_text(encoding="utf-8")
    block = begin + "\n" + body.rstrip() + "\n" + end
    if begin in text:
        left, rest = text.split(begin, 1)
        _, right = rest.split(end, 1)
        text = left + block + right
    else:
        assert anchor in text, (path, anchor)
        text = text.replace(anchor, block + "\n" + anchor, 1)
    path.write_text(text, encoding="utf-8")


manual = repo / "src/recomp_manual.c"
externs = "\n".join(f"extern void sub_{address:08X}(void);" for address in addresses)
replace_block(
    manual,
    "/* BEGIN RETAIL VTABLE GAP EXTERNS */",
    "/* END RETAIL VTABLE GAP EXTERNS */",
    externs,
    "static int dah_input_is_internal(void);",
)

cases = "\n".join(
    f"    case 0x{address:08X}u: return sub_{address:08X};" for address in addresses
)
replace_block(
    manual,
    "    /* BEGIN RETAIL VTABLE GAP DISPATCH */",
    "    /* END RETAIL VTABLE GAP DISPATCH */",
    cases,
    "    case 0x00012140u: return dah_retail_12140;",
)

header = repo / "src/recomp/gen/recomp_funcs.h"
prototypes = "\n".join(f"void sub_{address:08X}(void);" for address in addresses)
replace_block(
    header,
    "/* BEGIN RETAIL VTABLE GAP PROTOTYPES */",
    "/* END RETAIL VTABLE GAP PROTOTYPES */",
    prototypes,
    "#endif /* RECOMP_FUNCS_H */",
)

seed_path = repo / "icall_seeds.json"
seed_text = seed_path.read_text(encoding="utf-8")
seeds = json.loads(seed_text)
present = {int(item["start"], 16) for item in seeds}
missing = [address for address in addresses if address not in present]
if missing:
    compact_rows = "\n".join(
        f'  {{"start":"0x{address:08X}"}}' + ("," if index + 1 < len(missing) else "")
        for index, address in enumerate(missing)
    )
    stripped = seed_text.rstrip()
    assert stripped.endswith("]")
    prefix = stripped[:-1].rstrip()
    seed_path.write_text(prefix + ",\n" + compact_rows + "\n]\n", encoding="utf-8")

print(f"integrated {len(addresses)} retail vtable callbacks")
