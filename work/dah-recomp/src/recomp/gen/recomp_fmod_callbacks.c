/* Retail CRT fmod table (0x002597E0): six indirect-only entry points.
 * Original instructions: 0x0013B5A0..AE, 0x0013F420..427,
 * 0x0013F459..4DF. The surrounding classifier remains native game code.
 *
 * The runtime represents x87 registers as binary64, not extended80. These
 * helpers preserve binary64 values/payloads and the original ten-byte scratch
 * stores. They do not add full x87 sticky exception/trap emulation to that
 * existing runtime model. In particular, FPREM is completed with host fmod,
 * not a single partial reduction or an IEEE nearest-quotient remainder.
 */
#define RECOMP_GENERATED_CODE
#include "recomp_funcs.h"
#include <math.h>
#include <string.h>

static uint64_t dah_fmod_bits(double value)
{
    uint64_t bits;
    memcpy(&bits, &value, sizeof(bits));
    return bits;
}

static double dah_fmod_value(uint64_t bits)
{
    double value;
    memcpy(&value, &bits, sizeof(value));
    return value;
}

/* Exact extended80 encoding of a binary64 register, including signed zero,
 * normalized binary64 subnormals and an unmodified NaN quiet/payload field.
 * FSTP extended80 followed by FLD extended80 leaves the live value unchanged.
 */
static void dah_fmod_store80(uint32_t address, double value)
{
    uint64_t bits = dah_fmod_bits(value);
    uint64_t fraction = bits & UINT64_C(0x000FFFFFFFFFFFFF);
    unsigned exponent = (unsigned)((bits >> 52) & 0x7FFu);
    uint64_t significand;
    uint16_t sign_exponent = (uint16_t)((bits >> 48) & 0x8000u);
    if (exponent == 0x7FFu) {
        significand = UINT64_C(0x8000000000000000) | (fraction << 11);
        sign_exponent |= 0x7FFFu;
    } else if (exponent != 0u) {
        significand = (UINT64_C(0x0010000000000000) | fraction) << 11;
        sign_exponent |= (uint16_t)(exponent + 15360u);
    } else if (fraction != 0u) {
        int unbiased = -1022;
        while (!(fraction & UINT64_C(0x0010000000000000))) {
            fraction <<= 1;
            --unbiased;
        }
        significand = fraction << 11;
        sign_exponent |= (uint16_t)(unbiased + 16383);
    } else {
        significand = 0;
    }
    MEM32(address) = (uint32_t)significand;
    MEM32(address + 4u) = (uint32_t)(significand >> 32);
    MEM16(address + 8u) = sign_exponent;
}

/* x87 arithmetic propagates the larger NaN significand (positive wins a
 * sign-only tie), after preferring a quiet NaN over a signaling operand.
 * A binary64 sNaN is quieted here at arithmetic, not at the scratch store.
 */
static double dah_fmod_add(double left, double right)
{
    uint64_t a = dah_fmod_bits(left), b = dah_fmod_bits(right);
    uint64_t am = a & UINT64_C(0x7FFFFFFFFFFFFFFF);
    uint64_t bm = b & UINT64_C(0x7FFFFFFFFFFFFFFF);
    int an = am > UINT64_C(0x7FF0000000000000);
    int bn = bm > UINT64_C(0x7FF0000000000000);
    if (an || bn) {
        uint64_t selected;
        if (!an) selected = b;
        else if (!bn) selected = a;
        else {
            int aq = (a & UINT64_C(0x0008000000000000)) != 0;
            int bq = (b & UINT64_C(0x0008000000000000)) != 0;
            if (aq != bq) selected = aq ? a : b;
            else if (am != bm) selected = am > bm ? a : b;
            else selected = a < b ? a : b;
        }
        return dah_fmod_value(selected | UINT64_C(0x0008000000000000));
    }
    return left + right;
}

void sub_0013B5A0(void)
{
    unsigned top = (unsigned)g_fp_top;
    unsigned next = (top + 1u) & 7u;
    double divisor = g_fp_stack[top];
    double dividend = g_fp_stack[next];
    int quotient = 0;
    double nearest;
    unsigned low;
    /* FXCH; repeat FPREM until C2 clears. The table only selects this arm
     * for finite nonzero operands. remquo supplies low quotient bits without
     * overflowing x/y; correct its nearest quotient to truncation. */
    nearest = remquo(fabs(dividend), fabs(divisor), &quotient);
    low = ((unsigned)quotient - (nearest < 0.0 ? 1u : 0u)) & 7u;
    SET_LO16(eax, (top << 11) | ((low & 4u) << 6) |
                    ((low & 1u) << 9) | ((low & 2u) << 13)); /* FNSTSW AX */
    g_fp_stack[next] = fmod(dividend, divisor); /* FSTP ST(1) */
    g_fp_top = (int)next;
    esp += 4u;
}

void sub_0013F420(void)
{
    /* FSTP ST(0); FSTP ST(0); FLDZ; RET. */
    g_fp_top = (g_fp_top + 1) & 7;
    g_fp_stack[g_fp_top] = 0.0;
    esp += 4u;
}

void sub_0013F45B(void)
{
    unsigned next = ((unsigned)g_fp_top + 1u) & 7u;
    dah_fmod_store80(g_ebp - 0x9Eu, g_fp_stack[g_fp_top]);
    MEM8(g_ebp - 0x90u) = (MEM8(g_ebp - 0x97u) & 0x40u) ? 7u : 1u;
    g_fp_stack[next] = dah_fmod_add(g_fp_stack[next], g_fp_stack[g_fp_top]);
    g_fp_top = (int)next; /* FADDP ST(1) */
    esp += 4u;
}

void sub_0013F459(void)
{
    unsigned next = ((unsigned)g_fp_top + 1u) & 7u;
    double value = g_fp_stack[g_fp_top];
    g_fp_stack[g_fp_top] = g_fp_stack[next];
    g_fp_stack[next] = value; /* FXCH ST(1); fall through 13F45B */
    sub_0013F45B();
}

void sub_0013F483(void)
{
    unsigned next = ((unsigned)g_fp_top + 1u) & 7u;
    dah_fmod_store80(g_ebp - 0x9Eu, g_fp_stack[g_fp_top]);
    if (!(MEM8(g_ebp - 0x97u) & 0x40u)) {
        MEM8(g_ebp - 0x90u) = 1u;
    } else {
        double value = g_fp_stack[g_fp_top];
        g_fp_stack[g_fp_top] = g_fp_stack[next];
        g_fp_stack[next] = value;
        dah_fmod_store80(g_ebp - 0x9Eu, g_fp_stack[g_fp_top]);
        MEM8(g_ebp - 0x90u) = (MEM8(g_ebp - 0x97u) & 0x40u) ? 7u : 1u;
    }
    g_fp_stack[next] = dah_fmod_add(g_fp_stack[next], g_fp_stack[g_fp_top]);
    g_fp_top = (int)next;
    esp += 4u;
}

void sub_0013F4C2(void)
{
    /* FSTP ST(0) twice; FLD extended80 [259A50], whose original bytes are
     * 00 00 00 00 00 00 00 C0 FF FF (the x87 negative indefinite NaN). */
    g_fp_top = (g_fp_top + 1) & 7;
    g_fp_stack[g_fp_top] = dah_fmod_value(UINT64_C(0xFFF8000000000000));
    if ((int8_t)MEM8(g_ebp - 0x90u) <= 0)
        MEM8(g_ebp - 0x90u) = 1u;
    /* OR CL,CL has no register effect; RET shares 13F4D5's native epilogue. */
    esp += 4u;
}
