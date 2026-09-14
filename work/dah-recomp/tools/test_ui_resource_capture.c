/* Reuses mock device code, but does not run the movie test or game. Actual
 * rejected UI rings exercise bounded dumps of two distinct memory windows. */
#define main movie_fixture_main
#include "test_movie_pushbuffer.c"
#undef main

int main(int argc, char **argv)
{
    uint8_t *reserved;
    char pattern[96];
    WIN32_FIND_DATAA info;
    HANDLE find;
    unsigned files = 0, low_files = 0, contiguous_files = 0;
    assert(argc == 7 || argc == 9); /* Four init +2UI +optional2scene rings. */
    _putenv("DAH_PB_CAPTURE=0"); _putenv("DAH_PB_INDEXED_CAPTURE=0");
    _putenv(argc == 9 ? "DAH_PB_REJECT_CAPTURE=4" : "DAH_PB_REJECT_CAPTURE=2");
    /* Reserve address separation matching the guest windows, committing only
     * the two64MiB regions. This never maps/reads another process's memory. */
    reserved = (uint8_t *)VirtualAlloc(NULL, (SIZE_T)XBOX_CONTIG_BASE + XBOX_CONTIG_SIZE,
                                      MEM_RESERVE, PAGE_NOACCESS);
    assert(reserved);
    assert(VirtualAlloc(reserved, XBOX_CONTIG_SIZE, MEM_COMMIT, PAGE_READWRITE) == reserved);
    test_ram = reserved + XBOX_CONTIG_BASE;
    assert(VirtualAlloc(test_ram, XBOX_CONTIG_SIZE, MEM_COMMIT, PAGE_READWRITE) == test_ram);
    for (unsigned i = 0; i < XBOX_CONTIG_SIZE; ++i) {
        reserved[i] = (uint8_t)(i * 17u + 31u);
        test_ram[i] = (uint8_t)(i * 23u + 47u);
    }
    test_device.lpVtbl = &test_device_vtable;
    test_device_vtable.Clear = mock_clear;
    test_device_vtable.DrawPrimitiveUP = mock_draw;
    pgraph_d3d11_init();
    for (int i = 1; i < argc; ++i) replay(argv[i]);
    assert(test_draws == 0 && g_pg.stats.draw_calls == 0);
    snprintf(pattern, sizeof(pattern), "dah_resource_%lu_*.bin", (unsigned long)GetCurrentProcessId());
    find = FindFirstFileA(pattern, &info); assert(find != INVALID_HANDLE_VALUE);
    do {
        unsigned pid, submission, address;
        char kind[24], window[12];
        size_t length = (size_t)info.nFileSizeLow;
        uint8_t *actual = (uint8_t *)malloc(length);
        FILE *file;
        assert(actual && !info.nFileSizeHigh && length && length <= 256u * 1024u);
        assert(sscanf(info.cFileName, "dah_resource_%u_%u_%23[^_]_%x_%11[^.]", &pid,
                      &submission, kind, &address, window) == 5);
        assert(pid == GetCurrentProcessId() && submission >= 5 && submission < (unsigned)argc);
        file = fopen(info.cFileName, "rb"); assert(file);
        assert(fread(actual, 1, length, file) == length); fclose(file);
        if (strcmp(window, "low") == 0) {
            assert(memcmp(actual, reserved + address, length) == 0); ++low_files;
        } else {
            assert(strcmp(window, "contig") == 0);
            assert(memcmp(actual, test_ram + address, length) == 0); ++contiguous_files;
        }
        ++files; free(actual);
    } while (FindNextFileA(find, &info));
    FindClose(find);
    assert(files == 8u * (argc - 5u) && low_files == files / 2 && contiguous_files == files / 2);
    for (unsigned submission = 5; submission < (unsigned)argc; ++submission) {
        FILE *file; uint32_t constants[192 * 4]; uint8_t valid[192 * 4]; char path[128];
        snprintf(path, sizeof(path), "dah_transform_%lu_%06u.bin", (unsigned long)GetCurrentProcessId(), submission);
        file = fopen(path, "rb"); assert(file);
        assert(fread(constants, 1, sizeof(constants), file) == sizeof(constants) && fgetc(file) == EOF); fclose(file);
        snprintf(path, sizeof(path), "dah_transform_valid_%lu_%06u.bin", (unsigned long)GetCurrentProcessId(), submission);
        file = fopen(path, "rb"); assert(file);
        assert(fread(valid, 1, sizeof(valid), file) == sizeof(valid) && fgetc(file) == EOF); fclose(file);
        for (unsigned c = 187 * 4; c < 192 * 4; ++c) assert(valid[c] == 1);
    }
    /* Constant upload autoincrement and boundary clamp cannot wrap over c0. */
    {
        uint32_t preserved = g_pg.transform_constants[0];
        pgraph_d3d11_method(0, NV097_SET_TRANSFORM_CONSTANT_LOAD, 191);
        for (unsigned i = 0; i < 8; ++i)
            pgraph_d3d11_method(0, NV097_SET_TRANSFORM_CONSTANT + 4u * i, 0xABCD0000u + i);
        for (unsigned i = 0; i < 4; ++i) {
            assert(g_pg.transform_constants[191 * 4 + i] == 0xABCD0000u + i);
            assert(g_pg.transform_constant_valid[191 * 4 + i]);
        }
        assert(g_pg.transform_constants[0] == preserved);
        pgraph_d3d11_method(0, NV097_SET_TRANSFORM_CONSTANT_LOAD, UINT32_MAX);
        pgraph_d3d11_method(0, NV097_SET_TRANSFORM_CONSTANT, 0);
        assert(g_pg.transform_constants[0] == preserved);
    }
    /* Exact resource bounds, overflow, uncommitted pages and guards reject. */
    assert(!indexed_guest_bytes_window(XBOX_CONTIG_SIZE - 4u, 8u, 1));
    assert(!indexed_guest_bytes_window(0, 0, 0));
    assert(VirtualFree(reserved + 0x200000u, 0x1000u, MEM_DECOMMIT));
    assert(!indexed_guest_bytes_window(0x200000u, 8u, 0));
    {
        DWORD old_protection;
        assert(VirtualProtect(test_ram + 0x200000u, 0x1000u, PAGE_READWRITE | PAGE_GUARD, &old_protection));
        assert(!indexed_guest_bytes_window(0x200000u, 8u, 1));
    }
    pgraph_d3d11_shutdown(); VirtualFree(reserved, 0, MEM_RELEASE);
    printf("PASS: actual ring replay captures%u exact resource files from two windows, constants+validity captured; malformedvertices neverdraw; SHORT/DXT extents, constantautoload and inaccessible/overflow/guard bounds reject\n", files);
    return 0;
}
