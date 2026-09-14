#include <windows.h>
#include <stdio.h>
#include <stdint.h>

typedef void *(__stdcall *BinkOpenFn)(const char *, unsigned int);
typedef int (__stdcall *BinkDoFrameFn)(void *);
typedef void (__stdcall *BinkNextFrameFn)(void *);
typedef int (__stdcall *BinkCopyToBufferFn)(void *, void *, int, int, int, int, unsigned int);
typedef void (__stdcall *BinkCloseFn)(void *);
typedef const char *(__stdcall *BinkGetErrorFn)(void);

#pragma pack(push, 1)
typedef struct {
    uint16_t type;
    uint32_t size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t off_bits;
    uint32_t info_size;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bits;
    uint32_t compression;
    uint32_t image_size;
    int32_t xppm;
    int32_t yppm;
    uint32_t colors_used;
    uint32_t colors_important;
} BmpHeader;
#pragma pack(pop)

static void dump_words(const unsigned char *p, size_t n)
{
    size_t i;
    for (i = 0; i + 4 <= n; i += 4) {
        uint32_t v;
        memcpy(&v, p + i, sizeof(v));
        printf("%02X: %08X (%u)\n", (unsigned)i, v, v);
    }
}

int main(int argc, char **argv)
{
    HMODULE dll;
    void *bink;
    BinkOpenFn open_fn;
    BinkDoFrameFn do_frame;
    BinkNextFrameFn next_frame;
    BinkCopyToBufferFn copy_fn;
    BinkCloseFn close_fn;
    BinkGetErrorFn error_fn;
    static unsigned char pixels[4096 * 4096 * 4];
    const char *path = argc > 1 ? argv[1] : "saucer.bik";
    setvbuf(stdout, NULL, _IONBF, 0);

    dll = LoadLibraryA(argc > 2 ? argv[2] : "binkw32.dll");
    printf("dll=%p err=%lu\n", (void *)dll, GetLastError());
    if (!dll) return 2;
#define FN(name, type) ((type)GetProcAddress(dll, name))
    open_fn = FN("_BinkOpen@8", BinkOpenFn);
    do_frame = FN("_BinkDoFrame@4", BinkDoFrameFn);
    next_frame = FN("_BinkNextFrame@4", BinkNextFrameFn);
    copy_fn = FN("_BinkCopyToBuffer@28", BinkCopyToBufferFn);
    close_fn = FN("_BinkClose@4", BinkCloseFn);
    error_fn = FN("_BinkGetError@0", BinkGetErrorFn);
    if (!open_fn || !do_frame || !next_frame || !copy_fn || !close_fn) {
        printf("missing exports open=%p frame=%p next=%p copy=%p close=%p\n",
               (void *)open_fn, (void *)do_frame, (void *)next_frame,
               (void *)copy_fn, (void *)close_fn);
        return 3;
    }
    bink = open_fn(path, 0);
    printf("open=%p error=%s\n", bink, error_fn ? error_fn() : "?");
    if (!bink) return 4;
    dump_words((const unsigned char *)bink, 0x80);
    if (do_frame(bink) != 0) {
        printf("do_frame failed error=%s\n", error_fn ? error_fn() : "?");
    }
    for (int frame = 0; frame < 240; ++frame) {
        if (frame != 0) {
            next_frame(bink);
            if (do_frame(bink) != 0) break;
        }
        if (frame != 0 && frame != 30 && frame != 60 && frame != 120 && frame != 239)
            continue;
        /* Surface 3 is BINKSURFACE32; this is the standard RGBA/BGRA target. */
        if (copy_fn(bink, pixels, 4096 * 4, 4096, 0, 0, 3) != 0) {
            printf("copy failed frame=%d error=%s\n", frame, error_fn ? error_fn() : "?");
            continue;
        }
        {
            char name[64];
            BmpHeader h;
            FILE *bmp;
            sprintf(name, "bink_frame_%03d.bmp", frame);
            bmp = fopen(name, "wb");
            memset(&h, 0, sizeof(h));
            h.type = 0x4D42;
            h.off_bits = sizeof(h);
            h.info_size = 40;
            h.width = 640;
            h.height = -448;
            h.planes = 1;
            h.bits = 32;
            h.image_size = 640u * 448u * 4u;
            h.size = h.off_bits + h.image_size;
            if (bmp) {
                fwrite(&h, 1, sizeof(h), bmp);
                for (int y = 0; y < 448; ++y)
                    fwrite(pixels + y * 4096 * 4, 1, 640 * 4, bmp);
                fclose(bmp);
            }
            printf("saved frame=%d\n", frame);
        }
    }
    /* Keep the original single-frame raw dump for byte-level inspection. */
    if (copy_fn(bink, pixels, 4096 * 4, 4096, 0, 0, 3) != 0) {
        printf("copy failed error=%s\n", error_fn ? error_fn() : "?");
    } else {
        FILE *f = fopen("bink_frame.raw", "wb");
        if (f) { fwrite(pixels, 1, sizeof(pixels), f); fclose(f); }
        printf("copy succeeded\n");
    }
    next_frame(bink);
    close_fn(bink);
    return 0;
}
