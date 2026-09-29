/* Isolated observer fixture: includes the actual production header and never
 * opens a game process. Both guest address windows have independent backing. */
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
static uintptr_t g_xbox_mem_offset;
static int dah_frame_presentation_held(void) { return 1; }
#include "../../src/dah_parity_state.h"

int main(int argc, char **argv)
{
    const SIZE_T bytes = 4u * 1024u * 1024u;
    FILE *input;
    unsigned char *memory;
    if (argc != 2 || !(input = fopen(argv[1], "rb"))) return 2;
    memory = VirtualAlloc(NULL, (SIZE_T)0x80000000u + bytes,
                         MEM_RESERVE, PAGE_READWRITE);
    if (!memory || !VirtualAlloc(memory, bytes, MEM_COMMIT, PAGE_READWRITE) ||
        !VirtualAlloc(memory + (SIZE_T)0x80000000u, bytes, MEM_COMMIT, PAGE_READWRITE)) return 3;
    if (fread(memory, 1, bytes, input) != bytes) return 4;
    fclose(input);
    memcpy(memory + (SIZE_T)0x80000000u, memory, bytes);
    g_xbox_mem_offset = (uintptr_t)memory;
    fputs("{\"fixture\":true", stdout);
    dah_parity_write_farm(stdout, dah_parity_word(0x286768u), dah_parity_word(0x250E60u));
    fputs("}\n", stdout);
    VirtualFree(memory, 0, MEM_RELEASE);
    return 0;
}
