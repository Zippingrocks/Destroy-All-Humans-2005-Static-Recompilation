/* Retail-only callback restoration; regenerate with tools/lift_retail_type_callbacks_20261013.py. */
#define RECOMP_GENERATED_CODE
#include "recomp_funcs.h"

/* 0x00012700: mov eax, 0x68F1100B; ret. Retail table 0x00225EA8. */
void sub_00012700(void)
{
    g_eax = 0x68F1100Bu;
    g_esp += 4u;
}

/* 0x00012A40: mov eax, 0x1975BCED; ret. Retail table 0x00226060. */
void sub_00012A40(void)
{
    g_eax = 0x1975BCEDu;
    g_esp += 4u;
}

/* 0x00015AE0: mov eax, 0x177F1145; ret. Retail table 0x00226510. */
void sub_00015AE0(void)
{
    g_eax = 0x177F1145u;
    g_esp += 4u;
}

/* 0x000161C0: mov eax, 0xF90E4ACE; ret. Retail table 0x00226738. */
void sub_000161C0(void)
{
    g_eax = 0xF90E4ACEu;
    g_esp += 4u;
}

/* 0x0005FA20: mov eax, 0xF2D43FBF; ret. Retail table 0x0022A8DC. */
void sub_0005FA20(void)
{
    g_eax = 0xF2D43FBFu;
    g_esp += 4u;
}

/* 0x0009A260: mov eax, 0x71C8DF8F; ret. Retail table 0x0022F498. */
void sub_0009A260(void)
{
    g_eax = 0x71C8DF8Fu;
    g_esp += 4u;
}

/* 0x0009C2D0: mov eax, 0x8BFCF9A0; ret. Retail table 0x0022F620. */
void sub_0009C2D0(void)
{
    g_eax = 0x8BFCF9A0u;
    g_esp += 4u;
}

/* 0x000A1270: mov eax, 0x6460CAB8; ret. Retail table 0x0022FA00. */
void sub_000A1270(void)
{
    g_eax = 0x6460CAB8u;
    g_esp += 4u;
}

/* 0x000A1DB0: mov eax, 0x68195EBC; ret. Retail table 0x0022FAC0. */
void sub_000A1DB0(void)
{
    g_eax = 0x68195EBCu;
    g_esp += 4u;
}

/* 0x000A4980: mov eax, 0x9BCE23F0; ret. Retail table 0x0022FE20. */
void sub_000A4980(void)
{
    g_eax = 0x9BCE23F0u;
    g_esp += 4u;
}

/* Retail 0x00012A10..0x00012A40. MOV AL/SETE AL preserve the upper EAX bytes. */
void sub_00012A10(void)
{
    g_eax = MEM32(g_esp + 4u);
    if (g_eax == 0x1975BCEDu) goto accepted;
    if (g_eax == 0xB405C7B6u) goto accepted;
    if (g_eax == 0x883240FCu) goto accepted;
    if (g_eax == 0x38082939u) goto accepted;
    SET_LO8(g_eax, g_eax == 0xA75FFAEBu);
    g_esp += 8u; /* ret 4 */
    return;
accepted:
    SET_LO8(g_eax, 1u);
    g_esp += 8u; /* ret 4 */
}

/* 0x000127D0: jmp 0x000117D0. Preserve the caller's return address. */
void sub_000127D0(void)
{
    sub_000117D0();
}
