/*
 * NV2A PGRAPH → D3D11 Translator
 *
 * Translates NV2A push buffer methods into D3D8→D3D11 rendering calls.
 * Designed for Xbox static recompilation (xboxrecomp toolkit).
 *
 * Menu rendering profile (captured from xemu):
 *   - INLINE_ARRAY with 5-dword vertices (X, Y, U, V, Color)
 *   - TRIANGLE_STRIP topology
 *   - ~448 vertices per frame (~89 quads)
 *   - Textured 2D elements in 640×480 screen space
 */

#include "nv2a_pgraph_d3d11.h"
#include "nv2a_regs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <float.h>
#include "dah_menu_vertex.h"
#include "dah_farm_vertex.h"
#include "dah_static_reflection_vertex.h"
#include "dah_farm_deform_vertex.h"
#include "dah_skin_vertex.h"
#include "dah_unlit_vertex.h"
#include "dah_color_mask.h"
#include "dah_skin55_vertex.h"
#include "dah_skin62_vertex.h"
#include "dah_skin60_vertex.h"
#include "dah_pox_skin_vertex.h"
#include "dah_pox_vertex.h"
#include "dah_bc1.h"
#include "../d3d/d3d8_swizzle.h"

/* D3D8 device — we include the full header for COM vtable access */
#include "../d3d/d3d8_xbox.h"
#include "../d3d/d3d8_internal.h"
#include "dah_draw_pixel_readback.h"
#include "dah_fog_color.h"
#include "../kernel/xbox_memory_layout.h"
#include "../kernel/kernel.h"
extern IDirect3DDevice8 *xbox_GetD3DDevice(void);
extern int dah_request_frame_capture(void);

/* Global.txd texture lookup */
/* Game-specific texture lookup - only available when GAME_HAS_FONT_ATLAS is defined */
#ifdef GAME_HAS_FONT_ATLAS
typedef struct { char name[24]; IDirect3DTexture8 *texture; uint32_t width, height, format; } TXD_Entry;
typedef struct { TXD_Entry entries[512]; int count; } TXD_Dict;
extern TXD_Dict g_global_txd;
extern int g_textures_loaded;
extern IDirect3DTexture8 *txd_find(const TXD_Dict *dict, const char *name);
#else
static int g_textures_loaded = 0;
#endif

/* Font atlas DXT5 data - game-specific, only available in burnout3 */
#ifdef GAME_HAS_FONT_ATLAS
#include "font_atlas_data.h"
#endif

/* Create a D3D8 texture from raw DXT5 data */
static IDirect3DTexture8 *create_dxt5_texture(IDirect3DDevice8 *dev,
    uint32_t width, uint32_t height, const void *dxt5_data, uint32_t data_size)
{
    IDirect3DTexture8 *tex = NULL;
    /* D3DFMT_DXT5 = 0x35545844 ('DXT5') on Xbox, mapped to DXGI_FORMAT_BC3 in our layer.
     * Our d3d8 layer uses format code 0x0F for DXT5. */
    HRESULT hr = dev->lpVtbl->CreateTexture(dev, width, height, 1,
        0 /*Usage*/, 0x0F /*DXT5*/, 0 /*D3DPOOL_DEFAULT*/, &tex);
    if (hr != 0 || !tex) {
        fprintf(stderr, "[PGRAPH-D3D11] Failed to create font atlas texture: hr=0x%08X\n", hr);
        return NULL;
    }

    /* Lock and fill with DXT5 data */
    D3DLOCKED_RECT lr = {0};
    hr = tex->lpVtbl->LockRect(tex, 0, &lr, NULL, 0);
    if (hr == 0 && lr.pBits) {
        memcpy(lr.pBits, dxt5_data, data_size);
        tex->lpVtbl->UnlockRect(tex, 0);
        fprintf(stderr, "[PGRAPH-D3D11] Created font atlas: %ux%u DXT5 (%u bytes)\n",
                width, height, data_size);
    } else {
        fprintf(stderr, "[PGRAPH-D3D11] Failed to lock font atlas: hr=0x%08X\n", hr);
    }
    return tex;
}

/* All method addresses come from nv2a_regs.h. In particular, the retail
 * clear methods are at 0x1D90..0x1D9C, not the 0x01D0 range. Keeping a
 * second set here previously shadowed the correct hardware definitions. */

/* NV2A draw modes → D3D primitive types */
static int nv2a_draw_mode_to_d3d(uint32_t mode) {
    switch (mode) {
        case 1:  return D3DPT_POINTLIST;
        case 2:  return D3DPT_LINELIST;
        case 3:  return D3DPT_LINESTRIP;  /* LINE_LOOP → LINE_STRIP */
        case 4:  return D3DPT_LINESTRIP;
        case 5:  return D3DPT_TRIANGLELIST;
        case 6:  return D3DPT_TRIANGLESTRIP;
        case 7:  return D3DPT_TRIANGLEFAN;
        case 8:  return D3DPT_TRIANGLELIST; /* QUADS → TRI_LIST (needs conversion) */
        default: return D3DPT_TRIANGLELIST;
    }
}

/* NV2A blend factors → D3D blend */
static uint32_t nv2a_blend_to_d3d(uint32_t nv) {
    switch (nv) {
        case 0x0000: return D3DBLEND_ZERO;
        case 0x0001: return D3DBLEND_ONE;
        case 0x0300: return D3DBLEND_SRCCOLOR;
        case 0x0301: return D3DBLEND_INVSRCCOLOR;
        case 0x0304: return D3DBLEND_DESTALPHA;
        case 0x0305: return D3DBLEND_INVDESTALPHA;
        case 0x0306: return D3DBLEND_DESTCOLOR;
        case 0x0307: return D3DBLEND_INVDESTCOLOR;
        case 0x0308: return D3DBLEND_SRCALPHASAT;
        case 0x0302: return D3DBLEND_SRCALPHA;
        case 0x0303: return D3DBLEND_INVSRCALPHA;
        default:     return D3DBLEND_ONE;
    }
}

/* NV097 uses GL-valued equations; D3DRS_BLENDOP uses D3DBLENDOP 1..5.
 * NV2A's signed variants are exposed by xemu as their ordinary host blend
 * operations because D3D8/D3D11 has no separate signed blend-op state. */
static uint32_t nv2a_blend_equation_to_d3d(uint32_t nv)
{
    switch (nv) {
    case NV097_SET_BLEND_EQUATION_V_FUNC_ADD:              return 1u;
    case NV097_SET_BLEND_EQUATION_V_FUNC_ADD_SIGNED:       return 1u;
    case NV097_SET_BLEND_EQUATION_V_FUNC_SUBTRACT:         return 2u;
    case NV097_SET_BLEND_EQUATION_V_FUNC_REVERSE_SUBTRACT: return 3u;
    case NV097_SET_BLEND_EQUATION_V_FUNC_REVERSE_SUBTRACT_SIGNED: return 3u;
    case NV097_SET_BLEND_EQUATION_V_MIN:                   return 4u;
    case NV097_SET_BLEND_EQUATION_V_MAX:                   return 5u;
    default: return 0u;
    }
}

static uint32_t nv2a_texture_address_to_d3d(uint32_t nv)
{
    switch (nv & 7u) {
    case 1u: return D3DTADDRESS_WRAP;
    case 2u: return D3DTADDRESS_MIRROR;
    case 3u: return D3DTADDRESS_CLAMP;
    case 4u: return D3DTADDRESS_BORDER;
    /* NV2A's CLAMP_TO_EDGE_OGL mode uses host edge clamping. */
    case 5u: return D3DTADDRESS_CLAMP;
    default: return D3DTADDRESS_WRAP;
    }
}

static uint32_t nv2a_texture_min_filter_to_d3d(uint32_t filter)
{
    uint32_t mode = (filter >> 16u) & 0xFFu;
    return mode == 1u || mode == 3u || mode == 5u
        ? D3DTEXF_POINT : D3DTEXF_LINEAR;
}

static uint32_t nv2a_texture_mag_filter_to_d3d(uint32_t filter)
{
    return ((filter >> 24u) & 0xFu) == 1u
        ? D3DTEXF_POINT : D3DTEXF_LINEAR;
}

static uint32_t nv2a_texture_mip_filter_to_d3d(uint32_t filter)
{
    uint32_t mode = (filter >> 16u) & 0xFFu;
    if (mode == 3u || mode == 4u) return D3DTEXF_POINT;
    if (mode == 5u || mode == 6u) return D3DTEXF_LINEAR;
    return D3DTEXF_NONE;
}

static float nv2a_texture_lod_bias(uint32_t filter)
{
    int32_t bias = (int32_t)(filter & 0x1FFFu);
    if (bias & 0x1000) bias |= ~0x1FFF;
    return (float)bias / 256.0f;
}

static uint32_t nv2a_texture_max_anisotropy(uint32_t control0)
{
    return 1u << ((control0 >> 4u) & 3u);
}

static uint32_t float_bits(float value)
{
    uint32_t bits;
    memcpy(&bits, &value, sizeof(bits));
    return bits;
}

/* ══════════════════════════════════════════════════════════════════════
 * Translator State
 * ══════════════════════════════════════════════════════════════════════ */

/* Inline vertex buffer - max 16K vertices per draw */
#define MAX_INLINE_VERTS 16384
#define INLINE_VERT_DWORDS 5  /* X, Y, U, V, Color */

/* First 28 bytes remain RwIm2DVertex-compatible; indexed 3D carries fog in TEXCOORD2. */
typedef struct {
    float x, y, z, rhw;
    uint32_t color;
    float u, v;
    float u1, v1, w1;
    float fog_coord, fog_pad;
} OutputVertex;

static struct {
    /* Draw state */
    int in_draw;           /* Between BEGIN and END */
    uint32_t draw_mode;    /* NV2A draw mode (0=end, 6=tristrip, etc.) */
    int d3d_prim_type;     /* Translated D3D prim type */

    /* Inline vertex accumulator */
    uint32_t inline_data[MAX_INLINE_VERTS * INLINE_VERT_DWORDS];
    uint32_t inline_count; /* Number of dwords accumulated */
    uint32_t vert_stride;  /* Dwords per vertex (auto-detected) */

    /* Preserve the retail indexed-array declaration for diagnosis before
     * implementing its host fetch path. This does not synthesize vertices. */
    uint32_t array_offset[16];
    uint32_t array_format[16];
    uint32_t indexed_diagnostic_count;
    uint32_t indexed_diagnostic_id;
    uint32_t indexed_diagnostic_packets;
    uint32_t draw_subchannel;
    uint32_t indices[MAX_INLINE_VERTS];
    uint32_t index_count;
    int index_overflow;
    uint32_t transform_program[136 * 4];
    uint8_t transform_valid[136 * 4];
    uint32_t transform_load_word;
    uint32_t transform_constants[192 * 4];
    uint8_t transform_constant_valid[192 * 4];
    uint32_t transform_constant_base;
    uint32_t transform_start;
    uint32_t transform_mode;
    uint32_t factor0[8], factor1[8];
    uint32_t color_icw[8], color_ocw[8], alpha_icw[8], alpha_ocw[8];
    uint32_t combiner_control, final_cw0, final_cw1, shader_stage_program;
    const uint32_t *active_pushbuffer;
    uint32_t active_pushbuffer_dwords, active_submission;
    uint32_t rejected_state_hash;
    int rejected_ring_captured;
    int rejected_capture_enabled;

    /* Clear state */
    uint32_t clear_color;
    uint32_t clear_zstencil;
    uint32_t clear_rect_h;  /* (width << 16) | x */
    uint32_t clear_rect_v;  /* (height << 16) | y */

    /* Render state cache */
    int depth_test;
    uint32_t depth_func;
    int depth_write;
    int blend_enable;
    uint32_t blend_sfactor;
    uint32_t blend_dfactor;
    uint32_t blend_equation;
    int cull_enable;
    int poly_offset_point;
    int poly_offset_line;
    int poly_offset_fill;
    float poly_offset_scale;
    float poly_offset_bias;
    int alpha_test;
    uint32_t alpha_func;
    uint32_t alpha_ref;
    uint32_t cull_face;
    uint32_t front_face;
    uint32_t color_mask;
    int stencil_test;
    uint32_t stencil_mask;
    uint32_t stencil_func;
    uint32_t stencil_ref;
    uint32_t stencil_func_mask;
    uint32_t stencil_op_fail;
    uint32_t stencil_op_zfail;
    uint32_t stencil_op_zpass;

    /* Viewport */
    float vp_offset[4];
    float vp_scale[4];
    uint32_t surface_clip_h;
    uint32_t surface_clip_v;
    uint32_t surface_format;
    uint32_t surface_pitch;
    uint32_t surface_color_offset;
    uint32_t surface_zeta_offset;
    float clip_min, clip_max;
    uint8_t clip_range_valid;
    int fog_enable;
    uint32_t fog_mode;
    float fog_param[3];
    uint32_t fog_color_raw;

    /* Texture state per stage (4 stages) */
    struct {
        uint32_t offset;     /* NV2A VRAM offset (method 0x1B00) */
        uint32_t format;     /* Format register (method 0x1B04) */
        uint32_t control0;   /* Control0 register (method 0x1B08) */
        uint32_t control1;   /* Linear image pitch (method 0x1B10) */
        uint32_t image_rect; /* Width/height (method 0x1B1C) */
        uint32_t address;
        uint32_t filter;
        int enabled;         /* Decoded from control0 bit 30 */
    } tex[4];

    /* Cached texture pointers */
    void *menu_texture;           /* IDirect3DTexture8* from Global.txd */
    IDirect3DTexture8 *font_atlas; /* Created from captured DXT5 data */
    int texture_lookup_done;
    IDirect3DTexture8 *linear_movie_texture;
    uint32_t linear_movie_width, linear_movie_height, linear_movie_format;

    /* Cached 3D-path DXT1 texture for the main menu */
    IDirect3DTexture8 *dah_3d_texture;
    uint32_t dah_3d_tex_offset;
    uint32_t dah_3d_tex_width;
    uint32_t dah_3d_tex_height;
    uint32_t dah_3d_tex_format;

    /* Stats */
    PgraphD3D11Stats stats;

    /* Chyron scroll */
    float chyron_scroll_offset;  /* Pixels to shift X for chyron text */

    /* Init flag */
    int initialized;
} g_pg;

static void dah_apply_polygon_offset(void)
{
    /* All currently translated solid triangles use the fill setting. Keep
     * point/line enables so topology-specific support can select them without
     * losing guest state. */
    d3d8_SetRasterDepthBias(g_pg.poly_offset_fill,
                            g_pg.poly_offset_scale,
                            g_pg.poly_offset_bias);
}

static int dah_apply_blend_state(IDirect3DDevice8 *dev, int enabled)
{
    uint32_t equation = nv2a_blend_equation_to_d3d(g_pg.blend_equation);
    if (enabled && !equation) {
        static unsigned reports;
        if (reports++ < 16u)
            fprintf(stderr, "[DAH-BLEND-REJECT] submit=%u equation=%08X source=%08X destination=%08X\n",
                    g_pg.active_submission, g_pg.blend_equation,
                    g_pg.blend_sfactor, g_pg.blend_dfactor);
        return 0;
    }
    dev->lpVtbl->SetRenderState(dev, D3DRS_ALPHABLENDENABLE, enabled);
    dev->lpVtbl->SetRenderState(dev, D3DRS_SRCBLEND,
                                nv2a_blend_to_d3d(g_pg.blend_sfactor));
    dev->lpVtbl->SetRenderState(dev, D3DRS_DESTBLEND,
                                nv2a_blend_to_d3d(g_pg.blend_dfactor));
    /* Disabled blending does not consume an unsupported equation. */
    if (equation) dev->lpVtbl->SetRenderState(dev, D3DRS_BLENDOP, equation);
    return 1;
}

static uint32_t dah_nv2a_stencil_op_to_d3d(uint32_t op)
{
    switch (op) {
    case NV097_SET_STENCIL_OP_V_ZERO:    return 2u;
    case NV097_SET_STENCIL_OP_V_REPLACE: return 3u;
    case NV097_SET_STENCIL_OP_V_INCRSAT: return 4u;
    case NV097_SET_STENCIL_OP_V_DECRSAT: return 5u;
    case NV097_SET_STENCIL_OP_V_INVERT:  return 6u;
    case NV097_SET_STENCIL_OP_V_INCR:    return 7u;
    case NV097_SET_STENCIL_OP_V_DECR:    return 8u;
    case NV097_SET_STENCIL_OP_V_KEEP:
    default: return 1u;
    }
}

static void dah_apply_stencil_state(IDirect3DDevice8 *dev)
{
    if (!dev) return;
    dev->lpVtbl->SetRenderState(dev, D3DRS_STENCILENABLE, g_pg.stencil_test);
    dev->lpVtbl->SetRenderState(dev, D3DRS_STENCILMASK, g_pg.stencil_func_mask);
    dev->lpVtbl->SetRenderState(dev, D3DRS_STENCILWRITEMASK, g_pg.stencil_mask);
    dev->lpVtbl->SetRenderState(dev, D3DRS_STENCILFUNC,
        g_pg.stencil_func >= 0x0200u && g_pg.stencil_func <= 0x0207u ?
        g_pg.stencil_func - 0x0200u + 1u : D3DCMP_ALWAYS);
    dev->lpVtbl->SetRenderState(dev, D3DRS_STENCILREF, g_pg.stencil_ref);
    dev->lpVtbl->SetRenderState(dev, D3DRS_STENCILFAIL,
        dah_nv2a_stencil_op_to_d3d(g_pg.stencil_op_fail));
    dev->lpVtbl->SetRenderState(dev, D3DRS_STENCILZFAIL,
        dah_nv2a_stencil_op_to_d3d(g_pg.stencil_op_zfail));
    dev->lpVtbl->SetRenderState(dev, D3DRS_STENCILPASS,
        dah_nv2a_stencil_op_to_d3d(g_pg.stencil_op_zpass));
}

static const uint8_t *indexed_guest_bytes_window(uint32_t address, size_t length, int contiguous);
static int dah_surface_is_backbuffer(uint32_t offset)
{
    /* Retail GetBackBuffer (001DAE50) reads the device at 001E8968 and
     * surface slots 1A14/1A18/1A1C. Swap (001DC2E0) rotates their Data
     * fields; AvSetDisplayMode (001DBC20) reads surface+4 as the scanout.
     * Discover these actual resources on each bind, independent of heap size. */
    const uint8_t *bytes=indexed_guest_bytes_window(0x001E8968u,4u,0);
    uint32_t device,count;
    if(!bytes||!offset)return 0;
    memcpy(&device,bytes,4);
    if(!device||device>UINT32_MAX-0x1A20u)return 0;
    bytes=indexed_guest_bytes_window(device+0x1A10u,16u,0);
    if(!bytes)return 0;
    uint32_t slots[4];memcpy(slots,bytes,sizeof slots);count=slots[0];
    if(count<2u||count>3u)return 0;
    for(unsigned i=0;i<count;i++){
        uint32_t surface=slots[i+1],data;
        if(!surface||surface>UINT32_MAX-8u)continue;
        bytes=indexed_guest_bytes_window(surface+4u,4u,0);
        if(!bytes)continue;
        memcpy(&data,bytes,4);
        if(data==offset)return 1;
    }
    return 0;
}

static void dah_bind_current_surface(void)
{
    uint32_t width = g_pg.surface_clip_h >> 16u;
    uint32_t height = g_pg.surface_clip_v >> 16u;
    if (!width || width > 4096u) width = 640u;
    if (!height || height > 4096u) height = 480u;
    d3d8_PgraphBindRenderTarget(g_pg.surface_color_offset,
        dah_surface_is_backbuffer(g_pg.surface_color_offset), width, height);
    d3d8_PgraphBindDepthSurface(g_pg.surface_zeta_offset, (g_pg.surface_format >> 4u) & 15u);
}

/* kind 0=initial submissions, 1=indexed draw, 2=distinct rejected draw. */
static int capture_pushbuffer(const uint32_t *data, uint32_t num_dwords,
                             uint32_t submission, int kind);

static uint32_t rejected_draw_hash(const char *reason)
{
    uint32_t hash = 2166136261u;
#define REJECT_HASH_WORD(value) (hash = (hash ^ (uint32_t)(value)) * 16777619u)
    for (const char *p = reason; *p; ++p) REJECT_HASH_WORD((unsigned char)*p);
    REJECT_HASH_WORD(g_pg.draw_mode); REJECT_HASH_WORD(g_pg.transform_mode);
    REJECT_HASH_WORD(g_pg.surface_format); REJECT_HASH_WORD(g_pg.surface_pitch);
    REJECT_HASH_WORD(g_pg.surface_color_offset); REJECT_HASH_WORD(g_pg.surface_zeta_offset);
    REJECT_HASH_WORD(g_pg.transform_start); REJECT_HASH_WORD(g_pg.shader_stage_program);
    REJECT_HASH_WORD(g_pg.combiner_control); REJECT_HASH_WORD(g_pg.final_cw0);
    REJECT_HASH_WORD(g_pg.final_cw1); REJECT_HASH_WORD(g_pg.depth_test);
    REJECT_HASH_WORD(g_pg.blend_enable); REJECT_HASH_WORD(g_pg.cull_enable);
    REJECT_HASH_WORD(g_pg.blend_equation);
    REJECT_HASH_WORD(g_pg.alpha_test); REJECT_HASH_WORD(g_pg.color_mask);
    for (unsigned i = 0; i < 16u; ++i) REJECT_HASH_WORD(g_pg.array_format[i]);
    /* Ignore changing buffer addresses, indices and frame pixels so repeated
     * copies of one unsupported draw cannot exhaust the four capture slots. */
    for (unsigned i = 0; i < 136u * 4u; ++i) {
        REJECT_HASH_WORD(g_pg.transform_valid[i]);
        if (g_pg.transform_valid[i]) REJECT_HASH_WORD(g_pg.transform_program[i]);
    }
    for (unsigned i = 0; i < 8u; ++i) {
        REJECT_HASH_WORD(g_pg.color_icw[i]); REJECT_HASH_WORD(g_pg.color_ocw[i]);
        REJECT_HASH_WORD(g_pg.alpha_icw[i]); REJECT_HASH_WORD(g_pg.alpha_ocw[i]);
    }
    for (unsigned i = 0; i < 4u; ++i) {
        REJECT_HASH_WORD(g_pg.tex[i].enabled); REJECT_HASH_WORD(g_pg.tex[i].format);
        REJECT_HASH_WORD(g_pg.tex[i].image_rect); REJECT_HASH_WORD(g_pg.tex[i].control0);
        REJECT_HASH_WORD(g_pg.tex[i].control1); REJECT_HASH_WORD(g_pg.tex[i].address);
        REJECT_HASH_WORD(g_pg.tex[i].filter);
    }
#undef REJECT_HASH_WORD
    return hash;
}

static void log_rejected_draw_state(const char *reason)
{
    fprintf(stderr, "[DAH-REJECTED-STATE] submit=%u reason=%s hash=%08X draw=%u mode=%u indices=%u shader_mode=%08X shader_start=%u stage_program=%08X combiner=%08X final=%08X,%08X depth=%d blend=%d cull=%d color_mask=%08X blend_equation=%08X\n",
            g_pg.active_submission, reason, g_pg.rejected_state_hash, g_pg.indexed_diagnostic_id,
            g_pg.draw_mode, g_pg.index_count, g_pg.transform_mode, g_pg.transform_start,
            g_pg.shader_stage_program, g_pg.combiner_control, g_pg.final_cw0, g_pg.final_cw1,
            g_pg.depth_test, g_pg.blend_enable, g_pg.cull_enable, g_pg.color_mask,
            g_pg.blend_equation);
    fprintf(stderr, "[DAH-REJECTED-VIEWPORT] surface_format=%08X pitch=%08X color=%08X zeta=%08X clip_range=%.9g,%.9g valid=%u scale=%.9g,%.9g,%.9g,%.9g offset=%.9g,%.9g,%.9g,%.9g surface_clip=%08X,%08X fog=%d\n",
            g_pg.surface_format, g_pg.surface_pitch, g_pg.surface_color_offset,
            g_pg.surface_zeta_offset, g_pg.clip_min, g_pg.clip_max, g_pg.clip_range_valid,
            g_pg.vp_scale[0], g_pg.vp_scale[1], g_pg.vp_scale[2], g_pg.vp_scale[3],
            g_pg.vp_offset[0], g_pg.vp_offset[1], g_pg.vp_offset[2], g_pg.vp_offset[3],
            g_pg.surface_clip_h, g_pg.surface_clip_v, g_pg.fog_enable);
    for (unsigned i = 0; i < 16u; ++i)
        if (g_pg.array_format[i] || g_pg.array_offset[i])
            fprintf(stderr, "[DAH-REJECTED-ARRAY] slot=%u offset=%08X format=%08X\n",
                    i, g_pg.array_offset[i], g_pg.array_format[i]);
    for (unsigned i = 0; i < 4u; ++i)
        fprintf(stderr, "[DAH-REJECTED-TEX] stage=%u enabled=%d offset=%08X format=%08X control=%08X,%08X rect=%08X address=%08X filter=%08X\n",
                i, g_pg.tex[i].enabled, g_pg.tex[i].offset, g_pg.tex[i].format,
                g_pg.tex[i].control0, g_pg.tex[i].control1, g_pg.tex[i].image_rect,
                g_pg.tex[i].address, g_pg.tex[i].filter);
    for (unsigned i = 0; i < 8u; ++i)
        fprintf(stderr, "[DAH-REJECTED-COMBINER] stage=%u color=%08X,%08X alpha=%08X,%08X\n",
                i, g_pg.color_icw[i], g_pg.color_ocw[i], g_pg.alpha_icw[i], g_pg.alpha_ocw[i]);
    for (uint32_t i = g_pg.transform_start, n = 0; i < 136u && n < 32u; ++i, ++n) {
        uint32_t p = i * 4u;
        if (!g_pg.transform_valid[p]) break;
        fprintf(stderr, "[DAH-REJECTED-SHADER] instruction=%u raw=%08X,%08X,%08X,%08X\n",
                i, g_pg.transform_program[p], g_pg.transform_program[p + 1u],
                g_pg.transform_program[p + 2u], g_pg.transform_program[p + 3u]);
        if (g_pg.transform_program[p + 3u] & 1u) break;
    }
    fflush(stderr);
}

/* ══════════════════════════════════════════════════════════════════════
 * Float/uint32 conversion
 * ══════════════════════════════════════════════════════════════════════ */
static float u2f(uint32_t u) {
    union { float f; uint32_t i; } x;
    x.i = u;
    return x.f;
}

/* Programmable vertex shaders write a fog distance to oFog.  NV2A applies
 * the selected fog equation after the program and interpolates that factor
 * into the register combiner.  Passing the raw distance made geometry and
 * screen-space post effects jump to the fog colour. */
static float dah_transform_fog(float distance)
{
    float factor, infinite_result = 0.0f, nan_result = 0.0f;
    if (!g_pg.fog_enable) return 1.0f;
    switch (g_pg.fog_mode) {
    case NV097_SET_FOG_MODE_V_LINEAR:
    case NV097_SET_FOG_MODE_V_LINEAR_ABS:
        infinite_result = nan_result = 1.0f;
        factor = g_pg.fog_param[0] + distance * g_pg.fog_param[1] - 1.0f;
        break;
    case NV097_SET_FOG_MODE_V_EXP:
        infinite_result = nan_result = 1.0f;
        factor = g_pg.fog_param[0] + exp2f(distance * g_pg.fog_param[1] * 16.0f) - 1.5f;
        break;
    case NV097_SET_FOG_MODE_V_EXP_ABS:
        factor = g_pg.fog_param[0] + exp2f(distance * g_pg.fog_param[1] * 16.0f) - 1.5f;
        break;
    case NV097_SET_FOG_MODE_V_EXP2:
    case NV097_SET_FOG_MODE_V_EXP2_ABS:
        factor = g_pg.fog_param[0] + exp2f(-distance * distance *
            g_pg.fog_param[1] * g_pg.fog_param[1] * 32.0f) - 1.5f;
        break;
    default:
        return distance;
    }
    if (isinf(distance)) return infinite_result;
    if (isnan(factor)) factor = nan_result;
    if (g_pg.fog_mode == NV097_SET_FOG_MODE_V_LINEAR_ABS ||
        g_pg.fog_mode == NV097_SET_FOG_MODE_V_EXP_ABS ||
        g_pg.fog_mode == NV097_SET_FOG_MODE_V_EXP2_ABS)
        factor = fabsf(factor);
    if (factor > FLT_MAX) return FLT_MAX;
    if (factor < -FLT_MAX) return -FLT_MAX;
    return factor;
}

/* ══════════════════════════════════════════════════════════════════════
 * Initialization
 * ══════════════════════════════════════════════════════════════════════ */


/* Real host occlusion queries. Retail report packets overlap the report-type
 * bit with expanded-memory addresses, so the LTCG bridge registers the exact
 * destination before the packet is submitted. Never synthesize visibility. */
static struct { uint32_t parameter; void *record; } dah_reports[256];
static unsigned dah_report_next;
static ID3D11Query *dah_zpass_query;
static int dah_zpass_enabled, dah_zpass_active;
static uint64_t dah_zpass_count;
void pgraph_d3d11_register_report(uint32_t parameter, void *record)
{
    for (unsigned i=0;i<256;i++) if (dah_reports[i].record && dah_reports[i].parameter==parameter) {
        dah_reports[i].record=record; return;
    }
    unsigned i=dah_report_next++ % 256;
    dah_reports[i].parameter=parameter; dah_reports[i].record=record;
}
static struct {unsigned kind; ID3D11Query *query; volatile uint32_t *record;} dah_query_events[256];
static unsigned dah_query_read,dah_query_write;
void pgraph_d3d11_poll_reports(void)
{
    ID3D11DeviceContext *ctx=d3d8_GetD3D11Context(); if(!ctx)return;
    while(dah_query_read!=dah_query_write) {
        unsigned i=dah_query_read%256;
        if(dah_query_events[i].kind==0) dah_zpass_count=0;
        else if(dah_query_events[i].kind==1) {
            uint64_t samples=0; HRESULT hr=ID3D11DeviceContext_GetData(ctx,(ID3D11Asynchronous*)dah_query_events[i].query,&samples,sizeof samples,0);
            if(hr==S_FALSE)return;
            if(FAILED(hr)){fprintf(stderr,"[DAH-REPORT] GPU query failed %08X\n",hr);return;}
            dah_zpass_count+=samples;ID3D11Query_Release(dah_query_events[i].query);
        } else {
            volatile uint32_t *out=dah_query_events[i].record;LARGE_INTEGER tick;QueryPerformanceCounter(&tick);
            out[0]=(uint32_t)tick.QuadPart;out[1]=(uint32_t)((uint64_t)tick.QuadPart>>32);out[2]=(uint32_t)dah_zpass_count;MemoryBarrier();out[3]=0;
        }
        ++dah_query_read;
    }
}
static void dah_query_event(unsigned kind,ID3D11Query *query,volatile uint32_t *record)
{
    while(dah_query_write-dah_query_read==256){pgraph_d3d11_poll_reports();SwitchToThread();}
    unsigned i=dah_query_write++%256;dah_query_events[i].kind=kind;dah_query_events[i].query=query;dah_query_events[i].record=record;
}
static int dah_zpass_finish(void)
{
    if(dah_zpass_active){ID3D11DeviceContext_End(d3d8_GetD3D11Context(),(ID3D11Asynchronous*)dah_zpass_query);dah_query_event(1,dah_zpass_query,NULL);dah_zpass_query=NULL;dah_zpass_active=0;}
    pgraph_d3d11_poll_reports();return 1;
}
static void dah_zpass_begin(void)
{
    if(!dah_zpass_enabled || dah_zpass_active) return;
    ID3D11Device *dev=d3d8_GetD3D11Device();
    ID3D11DeviceContext *ctx=d3d8_GetD3D11Context();
    if(!dev || !ctx) return;
    if(!dah_zpass_query) {
        D3D11_QUERY_DESC desc={D3D11_QUERY_OCCLUSION,0};
        HRESULT hr=ID3D11Device_CreateQuery(dev,&desc,&dah_zpass_query);
        if(FAILED(hr)) { fprintf(stderr,"[DAH-REPORT] CreateQuery failed %08X\n",hr); return; }
    }
    ID3D11DeviceContext_Begin(ctx,(ID3D11Asynchronous*)dah_zpass_query);
    dah_zpass_active=1;
}
static void dah_zpass_report(uint32_t parameter)
{
    dah_zpass_finish();
    for(unsigned i=0;i<256;i++) if(dah_reports[i].record&&dah_reports[i].parameter==parameter){dah_query_event(2,NULL,dah_reports[i].record);pgraph_d3d11_poll_reports();dah_zpass_begin();return;}
    fprintf(stderr,"[DAH-REPORT] unregistered destination %08X\n",parameter);dah_zpass_begin();
}

void pgraph_d3d11_init(void)
{
    memset(&g_pg, 0, sizeof(g_pg));
    g_pg.vert_stride = INLINE_VERT_DWORDS;  /* Default: 5 dwords per vertex */
    g_pg.clear_color = 0xFF000000;
    g_pg.clear_zstencil = 0xFFFFFF00u;
    g_pg.color_mask = 0x01010101;
    g_pg.front_face = 0x0901u; /* NV097_FRONT_FACE_CCW reset convention. */
    g_pg.stencil_mask = 0xFFu;
    g_pg.stencil_func = 0x0207u;
    g_pg.stencil_func_mask = 0xFFu;
    g_pg.stencil_op_fail = NV097_SET_STENCIL_OP_V_KEEP;
    g_pg.stencil_op_zfail = NV097_SET_STENCIL_OP_V_KEEP;
    g_pg.stencil_op_zpass = NV097_SET_STENCIL_OP_V_KEEP;
    /* Match the host D3D device's initial LESS_EQUAL depth comparison. */
    g_pg.depth_func = 0x0203u;
    g_pg.depth_write = 1;
    g_pg.blend_equation = NV097_SET_BLEND_EQUATION_V_FUNC_ADD;
    g_pg.initialized = 1;

    fprintf(stderr, "[PGRAPH-D3D11] Translator initialized\n");
}

void pgraph_d3d11_shutdown(void)
{
    dah_zpass_finish();
    if(dah_zpass_query) { ID3D11Query_Release(dah_zpass_query); dah_zpass_query=NULL; }
    if (g_pg.linear_movie_texture) {
        g_pg.linear_movie_texture->lpVtbl->Release(g_pg.linear_movie_texture);
        g_pg.linear_movie_texture = NULL;
    }
    if (g_pg.dah_3d_texture) {
        g_pg.dah_3d_texture->lpVtbl->Release(g_pg.dah_3d_texture);
        g_pg.dah_3d_texture = NULL;
    }
    g_pg.initialized = 0;
    fprintf(stderr, "[PGRAPH-D3D11] Translator shut down (draws=%u, verts=%u)\n",
            g_pg.stats.draw_calls, g_pg.stats.vertices_submitted);
}

/* ══════════════════════════════════════════════════════════════════════
 * Draw Submission
 * ══════════════════════════════════════════════════════════════════════ */

/* This gated retail path uses physical offsets from contiguous resources.
 * Native D3D resource locks OR 0x80000000 into those offsets. The runtime
 * deliberately backs that window separately from low XBE/heap RAM (see
 * xbox_memory_layout.c), so reading low RAM returns unrelated, often zero,
 * bytes. Resolve the same contiguous window that native locks write; never
 * fall back to low RAM or mask an unsupported DMA address into valid data. */
/* Valid only for one synchronous pushbuffer batch (or one direct draw). Guest execution cannot free or change
 * its memory protection between these array/texture reads. */
static struct {uintptr_t begin,end;} dah_read_regions[16];
static unsigned dah_read_region_count;
/* Debug/replay switches are fixed at process launch. Hot Farm loops can
 * execute tens of thousands of methods per frame, so never rescan the CRT
 * environment for the same switch inside method or per-draw dispatch. */
#define DAH_LAUNCH_FLAG(function_name, variable_name) \
    static int function_name(void) { \
        static int enabled = -1; \
        if (enabled < 0) enabled = getenv(variable_name) != NULL; \
        return enabled; \
    }
DAH_LAUNCH_FLAG(dah_memory_window_profile_enabled, "DAH_MEMORY_WINDOW_PROFILE")
DAH_LAUNCH_FLAG(dah_matrix_trace_enabled, "DAH_MATRIX_TRACE")
DAH_LAUNCH_FLAG(dah_method_profile_enabled, "DAH_METHOD_PROFILE")
DAH_LAUNCH_FLAG(dah_farm_fine_profile_enabled, "DAH_FARM_FINE_PROFILE")
DAH_LAUNCH_FLAG(dah_runtime_profile_enabled, "DAH_RUNTIME_PROFILE")
DAH_LAUNCH_FLAG(dah_skin_dump_enabled, "DAH_FARM_SKIN_DUMP")
DAH_LAUNCH_FLAG(dah_crypto_head_trace_enabled, "DAH_CRYPTO_HEAD_TRACE")
DAH_LAUNCH_FLAG(dah_skin_disabled, "DAH_DISABLE_SKIN")
DAH_LAUNCH_FLAG(dah_geometry_trace_enabled, "DAH_GEOMETRY_TRACE")
DAH_LAUNCH_FLAG(dah_fog_trace_enabled, "DAH_FOG_TRACE")
DAH_LAUNCH_FLAG(dah_color_mask_trace_enabled, "DAH_COLOR_MASK_TRACE")
DAH_LAUNCH_FLAG(dah_draw_pixel_trace_enabled, "DAH_DRAW_PIXEL_TRACE")
DAH_LAUNCH_FLAG(dah_ui_animation_trace_enabled, "DAH_UI_ANIMATION_TRACE")
#undef DAH_LAUNCH_FLAG

static uint32_t dah_ui_animation_trace_start(void)
{
    static uint32_t start;
    static int configured;
    if (!configured) {
        const char *value = getenv("DAH_UI_ANIMATION_TRACE_START");
        char *end = NULL;
        unsigned long parsed = value && *value ? strtoul(value, &end, 10) : 0u;
        if (value && end != value && !*end && parsed <= UINT32_MAX)
            start = (uint32_t)parsed;
        configured = 1;
    }
    return start;
}

/* Diagnostic counters only: no query, read eligibility, or cache lifetime is
 * changed. At most 40 reports, each covering 300 synchronous submissions.
 * The first eight distinct rejected regions are retained with exact outcomes. */
static struct {
    uint64_t calls,hits,queries,readable,rejected,failed,outside_queries;
    uint64_t batch_resets,direct_resets,batches,batch_zero,batch_one;
    uint64_t batch_queries,batch_query_max,reject_other;
    unsigned range_count,reports;
    struct { uintptr_t begin,end; DWORD state,protect; uint64_t count; } ranges[8];
} dah_window_profile;

static void dah_memory_window_rejected(uintptr_t begin,uintptr_t end,DWORD state,DWORD protect)
{
    unsigned i;
    for(i=0;i<dah_window_profile.range_count;i++) {
        if(dah_window_profile.ranges[i].begin==begin && dah_window_profile.ranges[i].end==end &&
           dah_window_profile.ranges[i].state==state && dah_window_profile.ranges[i].protect==protect) {
            ++dah_window_profile.ranges[i].count;return;
        }
    }
    if(i==8u) {++dah_window_profile.reject_other;return;}
    ++dah_window_profile.range_count;
    dah_window_profile.ranges[i].begin=begin;dah_window_profile.ranges[i].end=end;
    dah_window_profile.ranges[i].state=state;dah_window_profile.ranges[i].protect=protect;
    dah_window_profile.ranges[i].count=1;
}

static void dah_memory_window_batch_end(uint32_t submission)
{
    if(!dah_memory_window_profile_enabled() || dah_window_profile.reports>=40u)return;
    ++dah_window_profile.batches;
    if(!dah_window_profile.batch_queries)++dah_window_profile.batch_zero;
    if(dah_window_profile.batch_queries==1u)++dah_window_profile.batch_one;
    if(dah_window_profile.batch_queries>dah_window_profile.batch_query_max)
        dah_window_profile.batch_query_max=dah_window_profile.batch_queries;
    if(dah_window_profile.batches<300u)return;
    fprintf(stderr,"[DAH-MEM-WINDOW] submit=%u calls=%llu hits=%llu queries=%llu readable=%llu rejected=%llu failed=%llu outside-queries=%llu batch-resets=%llu direct-resets=%llu batches=%llu zero-query-batches=%llu one-query-batches=%llu max-batch-queries=%llu cache-count=%u\n",
        submission,(unsigned long long)dah_window_profile.calls,(unsigned long long)dah_window_profile.hits,
        (unsigned long long)dah_window_profile.queries,(unsigned long long)dah_window_profile.readable,
        (unsigned long long)dah_window_profile.rejected,(unsigned long long)dah_window_profile.failed,
        (unsigned long long)dah_window_profile.outside_queries,(unsigned long long)dah_window_profile.batch_resets,
        (unsigned long long)dah_window_profile.direct_resets,(unsigned long long)dah_window_profile.batches,
        (unsigned long long)dah_window_profile.batch_zero,(unsigned long long)dah_window_profile.batch_one,
        (unsigned long long)dah_window_profile.batch_query_max,dah_read_region_count);
    for(unsigned i=0;i<dah_window_profile.range_count;i++)
        fprintf(stderr,"[DAH-MEM-REJECT] submit=%u native=%p..%p state=%08lX protect=%08lX queries=%llu\n",
            submission,(void*)dah_window_profile.ranges[i].begin,(void*)dah_window_profile.ranges[i].end,
            dah_window_profile.ranges[i].state,dah_window_profile.ranges[i].protect,
            (unsigned long long)dah_window_profile.ranges[i].count);
    if(dah_window_profile.reject_other)fprintf(stderr,"[DAH-MEM-REJECT] submit=%u other-range-queries=%llu\n",
        submission,(unsigned long long)dah_window_profile.reject_other);
    unsigned reports=dah_window_profile.reports+1u;
    memset(&dah_window_profile,0,sizeof(dah_window_profile));
    dah_window_profile.reports=reports;
}

/* Method timing is opt-in and sampled at three pushbuffers by default.
 * The launch-time variables move that bounded sample into heavy Farm. */
static int dah_method_profile_sample(uint32_t submission)
{
    static int configured;
    static uint32_t first = 2700u, last = 3300u, step = 300u;
    if (!dah_method_profile_enabled()) return 0;
    if (!configured) {
        const char *value; char *end; unsigned long parsed;
        value = getenv("DAH_METHOD_PROFILE_FIRST");
        if (value && *value) {
            parsed = strtoul(value, &end, 10);
            if (end != value && !*end && parsed <= UINT32_MAX - 600u) {
                first = (uint32_t)parsed; last = first + 600u;
            }
        }
        value = getenv("DAH_METHOD_PROFILE_LAST");
        if (value && *value) {
            parsed = strtoul(value, &end, 10);
            if (end != value && !*end && parsed <= UINT32_MAX) last = (uint32_t)parsed;
        }
        value = getenv("DAH_METHOD_PROFILE_STEP");
        if (value && *value) {
            parsed = strtoul(value, &end, 10);
            if (end != value && !*end && parsed >= 1u && parsed <= 10000u) step = (uint32_t)parsed;
        }
        fprintf(stderr, "[DAH-METHOD-WINDOW] first=%u last=%u step=%u\n", first, last, step);
        configured = 1;
    }
    return submission >= first && submission <= last &&
        ((submission - first) % step) == 0u;
}
static int dah_method_timing_active;
static double dah_method_draw_ms;
static unsigned dah_method_draw_count;
/* Active for only one sampled draw; all renderer work is synchronous. */
static int dah_fine_texture_active;
static double dah_fine_texture_lookup_ms, dah_fine_texture_upload_ms;
static uint64_t dah_fine_texture_hash_bytes;
static unsigned dah_fine_texture_uploads;
static double dah_profile_ms(void);
static const uint8_t *indexed_guest_bytes_window(uint32_t address, size_t length, int contiguous)
{
    const uint8_t *pointer;
    uintptr_t end, cursor;
    const int profile=dah_memory_window_profile_enabled() && dah_window_profile.reports<40u;
    if(profile)++dah_window_profile.calls;
    if (!length || (uint64_t)address + length > XBOX_CONTIG_SIZE ||
        !xbox_GetMemoryBase()) return NULL;
    pointer = (const uint8_t *)((contiguous ? (uintptr_t)XBOX_CONTIG_BASE : 0u) + address + xbox_GetMemoryOffset());
    cursor = (uintptr_t)pointer;
    end = cursor + length;
    while (cursor < end) {
        MEMORY_BASIC_INFORMATION info;
        uintptr_t region_end;
        unsigned r;
        for(r=0;r<dah_read_region_count;r++)if(cursor>=dah_read_regions[r].begin && cursor<dah_read_regions[r].end)break;
        if(r<dah_read_region_count){if(profile)++dah_window_profile.hits;cursor=dah_read_regions[r].end<end?dah_read_regions[r].end:end;continue;}
        if(profile) {
            ++dah_window_profile.queries;
            if(g_pg.active_pushbuffer)++dah_window_profile.batch_queries;
            else ++dah_window_profile.outside_queries;
        }
        if (!VirtualQuery((const void *)cursor, &info, sizeof(info))) {
            if(profile)++dah_window_profile.failed;
            return NULL;
        }
        if(info.State != MEM_COMMIT || (info.Protect & (PAGE_NOACCESS | PAGE_GUARD))) {
            if(profile) {
                ++dah_window_profile.rejected;
                dah_memory_window_rejected((uintptr_t)info.BaseAddress,(uintptr_t)info.BaseAddress+info.RegionSize,info.State,info.Protect);
            }
            return NULL;
        }
        if(profile)++dah_window_profile.readable;
        region_end = (uintptr_t)info.BaseAddress + info.RegionSize;
        if (region_end <= cursor) return NULL;
        if(dah_read_region_count<16){dah_read_regions[dah_read_region_count].begin=(uintptr_t)info.BaseAddress;dah_read_regions[dah_read_region_count++].end=region_end;}
        cursor = region_end < end ? region_end : end;
    }
    return pointer;
}

static const uint8_t *indexed_guest_bytes(uint32_t address, size_t length)
{
    return indexed_guest_bytes_window(address, length, 1);
}

/* Diagnostic only: save both candidate backing windows without selecting a
 * different renderer mapping. Called only for an already-bounded opt-in
 * rejected-ring capture (at most four states), max2MiB per resource/window.
 * The .bin files contain original bytes, not rendered or manufactured pixels. */
static void capture_indexed_resource(const char *kind, uint32_t address, size_t length)
{
    if (!length || length > 2u * 1024u * 1024u) return;
    for (int contiguous = 0; contiguous < 2; ++contiguous) {
        const uint8_t *bytes = indexed_guest_bytes_window(address, length, contiguous);
        const char *window = contiguous ? "contig" : "low";
        char path[160];
        FILE *file;
        uint32_t hash = 2166136261u;
        size_t nonzero = 0;
        if (!bytes) {
            fprintf(stderr, "[DAH-RESOURCE-CAPTURE] submit=%u kind=%s address=%08X window=%s bytes=%zu unavailable\n",
                    g_pg.active_submission, kind, address, window, length);
            continue;
        }
        snprintf(path, sizeof(path), "dah_resource_%lu_%06u_%s_%08X_%s.bin",
                 (unsigned long)GetCurrentProcessId(), g_pg.active_submission, kind, address, window);
        file = fopen(path, "wb");
        if (!file) continue;
        if (fwrite(bytes, 1, length, file) != length) { fclose(file); continue; }
        fclose(file);
        for (size_t i = 0; i < length; ++i) { hash = (hash ^ bytes[i]) * 16777619u; nonzero += bytes[i] != 0; }
        fprintf(stderr, "[DAH-RESOURCE-CAPTURE] submit=%u kind=%s address=%08X window=%s bytes=%zu nonzero=%zu fnv1a=%08X path=%s\n",
                g_pg.active_submission, kind, address, window, length, nonzero, hash, path);
    }
}

static void capture_rejected_resources(void)
{
    uint32_t first = UINT32_MAX, last = 0;
    uint32_t texture_format = (g_pg.tex[0].format >> 8u) & 0xFFu;
    uint64_t texture_bytes = (uint64_t)(g_pg.tex[0].control1 >> 16u) * (g_pg.tex[0].image_rect & 0xFFFFu);
    /* Compressed resources use power-of-two dimensions from FORMAT, not the
     * stale linear IMAGE_RECT/PITCH left behind by an earlier Bink texture. */
    if (texture_format == 0x0Cu || texture_format == 0x0Eu || texture_format == 0x0Fu) {
        uint32_t width = 1u << ((g_pg.tex[0].format >> 20u) & 15u);
        uint32_t height = 1u << ((g_pg.tex[0].format >> 24u) & 15u);
        uint32_t levels = (g_pg.tex[0].format >> 16u) & 15u;
        uint32_t block_bytes = texture_format == 0x0Cu ? 8u : 16u;
        texture_bytes = 0;
        if (((g_pg.tex[0].format >> 4u) & 15u) == 2u && !(g_pg.tex[0].format & 4u))
            for (uint32_t level = 0; level < levels; ++level) {
                texture_bytes += (uint64_t)((width + 3u) / 4u) * ((height + 3u) / 4u) * block_bytes;
                if (width > 1u) width >>= 1u;
                if (height > 1u) height >>= 1u;
            }
    }
    if (g_pg.tex[0].enabled && texture_bytes && texture_bytes <= 2u * 1024u * 1024u)
        capture_indexed_resource("texture0", g_pg.tex[0].offset, (size_t)texture_bytes);
    if (!g_pg.index_count || g_pg.index_overflow) return;
    for (uint32_t i = 0; i < g_pg.index_count; ++i) {
        if (g_pg.indices[i] < first) first = g_pg.indices[i];
        if (g_pg.indices[i] > last) last = g_pg.indices[i];
    }
    for (unsigned slot = 0; slot < 3u; ++slot) {
        uint32_t components = (g_pg.array_format[slot] >> 4u) & 15u;
        uint32_t type = g_pg.array_format[slot] & 15u;
        uint32_t stride = g_pg.array_format[slot] >> 8u;
        uint32_t element_bytes = components * (type == 0u ? 1u : type == 1u ? 2u : type == 2u ? 4u : 0u);
        uint64_t address = (uint64_t)g_pg.array_offset[slot] + (uint64_t)first * stride;
        uint64_t length = (uint64_t)(last - first) * stride + element_bytes;
        char kind[24];
        if (!element_bytes || stride < element_bytes || address > UINT32_MAX || length > 256u * 1024u) continue;
        snprintf(kind, sizeof(kind), "vertex%u", slot);
        capture_indexed_resource(kind, (uint32_t)address, (size_t)length);
    }
    {
        char path[128]; FILE *file;
        snprintf(path, sizeof(path), "dah_transform_%lu_%06u.bin", (unsigned long)GetCurrentProcessId(), g_pg.active_submission);
        file = fopen(path, "wb");
        if (file) { fwrite(g_pg.transform_constants, 1, sizeof(g_pg.transform_constants), file); fclose(file); }
        snprintf(path, sizeof(path), "dah_transform_valid_%lu_%06u.bin", (unsigned long)GetCurrentProcessId(), g_pg.active_submission);
        file = fopen(path, "wb");
        if (file) { fwrite(g_pg.transform_constant_valid, 1, sizeof(g_pg.transform_constant_valid), file); fclose(file); }
        fprintf(stderr, "[DAH-TRANSFORM-CAPTURE] submit=%u constants=192 raw-bytes=%zu valid-bytes=%zu\n",
                g_pg.active_submission, sizeof(g_pg.transform_constants), sizeof(g_pg.transform_constant_valid));
    }
}


/* ── Fetch one NV2A vertex attribute into a float4 ── */
static void fetch_attr_float4(const uint8_t *base, uint32_t stride,
                               uint32_t rel_idx, uint32_t type,
                               uint32_t count, float out[4])
{
    const uint8_t *ptr = base + (size_t)rel_idx * stride;
    out[0] = out[1] = out[2] = 0.0f; out[3] = 0.0f;
    if (type == 2u) {           /* float32 */
        for (uint32_t j = 0; j < count && j < 4u; ++j) {
            float f; memcpy(&f, ptr + j * 4u, 4u); out[j] = f;
        }
    } else if (type == 1u) {    /* S1: signed 16-bit, normalised to [-1, 1] */
        for (uint32_t j = 0; j < count && j < 4u; ++j) {
            int16_t s; memcpy(&s, ptr + j * 2u, 2u);
            out[j] = fmaxf(-1.0f, s / 32767.0f);
        }
    } else if (type == 4u) { /* UB_OGL: normalized RGB(A) bytes. */
        for (uint32_t j = 0; j < count && j < 4u; ++j)
            out[j] = ptr[j] / 255.0f;
    } else if (type == 0u) {    /* UB_D3D: normalized BGRA bytes, exposed as RGBA. */
        for (uint32_t j = 0; j < count && j < 4u; ++j)
            out[j] = ptr[j < 3u ? 2u-j : 3u] / 255.0f;
    }
}

static void dah_complete_static_texcoord(uint32_t count, float value[4])
{
    if (count < 4u) value[3] = 1.0f;
}

/* ── Pack float RGBA [0..1] to D3D ARGB uint32 ── */
static uint32_t pack_argb(const float d[4])
{
#define CLAMP01(x) ((x) < 0.0f ? 0.0f : (x) > 1.0f ? 1.0f : (x))
    uint32_t a = (uint32_t)(CLAMP01(d[3]) * 255.0f + 0.5f);
    uint32_t r = (uint32_t)(CLAMP01(d[0]) * 255.0f + 0.5f);
    uint32_t g = (uint32_t)(CLAMP01(d[1]) * 255.0f + 0.5f);
    uint32_t b = (uint32_t)(CLAMP01(d[2]) * 255.0f + 0.5f);
#undef CLAMP01
    return (a << 24) | (r << 16) | (g << 8) | b;
}

/* ── Indexed 3D draw path: handles the DAH main-menu 17-instruction VSH ──
 * Returns 1 on success, 0 when this draw should fall through to the
 * movie-gated path.  Never touches the existing reject counter or logs. */

extern void d3d8_combiners_set_nv2a(uint32_t,uint32_t,const uint32_t*,const uint32_t*,const uint32_t*,const uint32_t*,const uint32_t*,const uint32_t*,uint32_t,uint32_t);
extern void d3d8_combiners_set_texture_alpha_one_mask(uint32_t);
extern void dah_renderdoc_begin_effect(const char *label);

static uint32_t dah_texture_alpha_one_mask(void)
{
    uint32_t mask = 0;
    for (unsigned stage = 0; stage < 4u; ++stage) {
        uint32_t format = (g_pg.tex[stage].format >> 8u) & 255u;
        /* SZ_X8R8G8B8 and LU_IMAGE_X8R8G8B8. xemu's texture tables
         * use RGB8 / alpha-ONE swizzles for these exact formats. */
        if (g_pg.tex[stage].enabled && (format == 0x07u || format == 0x1eu))
            mask |= 1u << stage;
    }
    return mask;
}
extern void d3d8_combiners_set_vertex_fog(int);
extern void d3d8_combiners_set_vertex_fog_constant(float);
static struct DahMeshTexture { uint32_t offset,key,width,height,format,hash; IDirect3DTexture8 *texture; uint32_t last_successful_submission; const uint8_t *last_source; size_t last_source_bytes; uint8_t *snapshot; size_t snapshot_bytes; uint32_t content_valid; } dah_mesh_textures[256];
static unsigned dah_mesh_texture_next;
/* Up to 64 MiB total across 256 entries, and no more than 1 MiB per asset.
 * A failed allocation simply falls back to the existing content hash. */
#define DAH_MESH_SNAPSHOT_BUDGET ((size_t)64u * 1024u * 1024u)
#define DAH_MESH_SNAPSHOT_MAX_ASSET ((size_t)1u * 1024u * 1024u)
static size_t dah_mesh_snapshot_total_bytes;
static void dah_mesh_texture_snapshot_drop(struct DahMeshTexture *cache)
{
    if (!cache->snapshot) return;
    dah_mesh_snapshot_total_bytes -= cache->snapshot_bytes;
    free(cache->snapshot);
    cache->snapshot = NULL;
    cache->snapshot_bytes = 0;
}
static int dah_mesh_texture_snapshot_matches(const struct DahMeshTexture *cache,
                                             const uint8_t *source, size_t bytes)
{
    return cache->content_valid && cache->snapshot &&
           cache->snapshot_bytes == bytes && !memcmp(cache->snapshot, source, bytes);
}
static void dah_mesh_texture_snapshot_update(struct DahMeshTexture *cache,
                                             const uint8_t *source, size_t bytes)
{
    if (!bytes || bytes > DAH_MESH_SNAPSHOT_MAX_ASSET) {
        dah_mesh_texture_snapshot_drop(cache);
        return;
    }
    if (cache->snapshot_bytes != bytes) {
        dah_mesh_texture_snapshot_drop(cache);
        if (bytes > DAH_MESH_SNAPSHOT_BUDGET - dah_mesh_snapshot_total_bytes) return;
        cache->snapshot = (uint8_t *)malloc(bytes);
        if (!cache->snapshot) return;
        cache->snapshot_bytes = bytes;
        dah_mesh_snapshot_total_bytes += bytes;
    }
    memcpy(cache->snapshot, source, bytes);
}

/* Success is scoped to one synchronous pushbuffer. Later submissions
 * compare a bounded byte-exact snapshot; textures without a snapshot retain
 * the existing hash path. Dynamic content at the same address is detected. */
static void dah_mesh_texture_mark_success(struct DahMeshTexture *cache,
                                          const uint8_t *source, size_t bytes)
{
    cache->last_successful_submission = g_pg.active_pushbuffer ? g_pg.active_submission : 0u;
    cache->last_source = source;
    cache->last_source_bytes = bytes;
}
static IDirect3DTexture8 *dah_mesh_texture_window(unsigned stage,IDirect3DDevice8 *dev,int contiguous)
{
    IDirect3DTexture8 *tex_obj=NULL; HRESULT hr;
    struct DahMeshTexture *cache=NULL;
    if (!g_pg.tex[stage].enabled) return NULL;
    double dah_lookup_start = dah_fine_texture_active ? dah_profile_ms() : 0.0;
    for(unsigned i=0;i<256;i++) if(dah_mesh_textures[i].texture && dah_mesh_textures[i].offset==g_pg.tex[stage].offset && dah_mesh_textures[i].key==g_pg.tex[stage].format) {cache=&dah_mesh_textures[i];break;}
    if(!cache) {cache=&dah_mesh_textures[dah_mesh_texture_next++%256]; if(cache->texture) cache->texture->lpVtbl->Release(cache->texture); dah_mesh_texture_snapshot_drop(cache); memset(cache,0,sizeof(*cache)); cache->offset=g_pg.tex[stage].offset;cache->key=g_pg.tex[stage].format;}
    if (dah_fine_texture_active) dah_fine_texture_lookup_ms += dah_profile_ms() - dah_lookup_start;
    if (g_pg.tex[stage].enabled) {
        uint32_t w, h;
        size_t bytes;
        const uint8_t *source;
        D3DLOCKED_RECT lr = {0};
        uint32_t format = (g_pg.tex[stage].format >> 8u) & 255u;
        int compressed_alpha = format == 14u || format == 15u;
        int swizzled_abgr = format == 0x3au;
        int swizzled_argb = format == 6u || swizzled_abgr;
        int linear_argb = format == D3DFMT_LIN_A8R8G8B8;
        uint32_t source_pitch = 0u;
        /* Exact retail reflection pass: stage 1 is a DXT1 cubemap.
         * Xbox lays six faces in +X,-X,+Y,-Y,+Z,-Z order, each with all
         * mip levels and each face start aligned to 128 bytes. */
        if ((g_pg.tex[stage].format & 4u) != 0u) {
            uint32_t cube_format=g_pg.tex[stage].format;
            uint32_t cube_shape=cube_format & ~4u;
            unsigned levels=(cube_format>>16u)&15u;
            size_t face_bytes=0,face_stride,total;
            if(stage!=1u||format!=12u||!levels||levels>13u||
               !dah_bc1_shape(cube_shape,&w,&h,&bytes)||w!=h)return NULL;
            for(unsigned level=0,size=w;level<levels;level++,size=size>1u?size/2u:1u){
                size_t blocks=(size+3u)/4u;
                face_bytes+=blocks*blocks*8u;
            }
            face_stride=(face_bytes+127u)&~(size_t)127u;
            if(face_stride>SIZE_MAX/6u)return NULL;
            total=face_stride*6u;
            source=indexed_guest_bytes_window(g_pg.tex[stage].offset,total,contiguous);
            if(!source)return NULL;
            if(g_pg.active_pushbuffer && cache->texture && cache->content_valid &&
               cache->last_successful_submission==g_pg.active_submission &&
               cache->last_source==source && cache->last_source_bytes==total &&
               cache->width==w && cache->height==h && cache->format==12u)
                return cache->texture;
            int dah_snapshot_comparable=cache->texture && cache->content_valid &&
                cache->width==w && cache->height==h && cache->format==12u &&
                cache->snapshot && cache->snapshot_bytes==total;
            if(dah_snapshot_comparable && dah_mesh_texture_snapshot_matches(cache,source,total)){
                dah_mesh_texture_mark_success(cache,source,total);return cache->texture;
            }
            uint32_t hash=2166136261u;
            for(size_t j=0;j<total;j++)hash=(hash^source[j])*16777619u;
            if (dah_fine_texture_active) dah_fine_texture_hash_bytes += total;
            if(cache->texture&&!dah_snapshot_comparable&&cache->content_valid&&cache->hash==hash&&cache->width==w&&cache->height==h&&cache->format==12u){dah_mesh_texture_mark_success(cache,source,total);return cache->texture;}
            if(!cache->texture||cache->width!=w||cache->height!=h||cache->format!=12u){
                IDirect3DTexture8 *created=NULL;
                hr=d3d8_CreateCubeTextureImpl(w,levels,D3DFMT_DXT1,&created);
                if(FAILED(hr)||!created)return NULL;
                if(cache->texture)cache->texture->lpVtbl->Release(cache->texture);
                cache->texture=created;cache->width=w;cache->height=h;cache->format=12u;cache->last_successful_submission=0u;cache->last_source=NULL;cache->last_source_bytes=0u;cache->content_valid=0u;dah_mesh_texture_snapshot_drop(cache);
            }
            double dah_upload_start = dah_fine_texture_active ? dah_profile_ms() : 0.0;
            hr=d3d8_UploadCubeTextureImpl(cache->texture,source,face_stride);
            if(FAILED(hr)){cache->content_valid=0u;dah_mesh_texture_snapshot_drop(cache);return NULL;}
            if (dah_fine_texture_active) {
                dah_fine_texture_upload_ms += dah_profile_ms() - dah_upload_start;
                ++dah_fine_texture_uploads;
            }
            cache->hash=hash;cache->content_valid=1u;
            dah_mesh_texture_snapshot_update(cache,source,total);
            dah_mesh_texture_mark_success(cache,source,total);
            return cache->texture;
        }
        uint32_t shape_format = (g_pg.tex[stage].format & ~0xFF00u) | 0x0C00u;
        D3DFORMAT host_format = compressed_alpha ? (D3DFORMAT)format : D3DFMT_LIN_A8R8G8B8;
        if (linear_argb) {
            w = g_pg.tex[stage].image_rect >> 16u;
            h = g_pg.tex[stage].image_rect & 0xFFFFu;
            source_pitch = g_pg.tex[stage].control1 >> 16u;
            if (!w || !h || w > 4096u || h > 4096u ||
                source_pitch < w * 4u || (size_t)source_pitch > SIZE_MAX / h)
                return NULL;
            bytes = (size_t)source_pitch * h;
        } else {
            if ((format != 12u && !compressed_alpha && !swizzled_argb) ||
                !dah_bc1_shape(shape_format, &w, &h, &bytes)) return NULL;
            if (compressed_alpha) bytes *= 2u;
            if (swizzled_argb) bytes=(size_t)w*h*4u;
        }
        /* D3D11 BC2/BC3 uploads use block rows. Small BC1 assets retain the
         * existing CPU decode; do not invent padding for small alpha assets. */
        if ((compressed_alpha && (w < 4u || h < 4u)) ||
            !(source = indexed_guest_bytes_window(g_pg.tex[stage].offset, bytes, contiguous))) {
            return NULL;
        }
        {
            static int dah_effect_texture_dumped;
            const char *dump_path = getenv("DAH_EFFECT_TEXTURE_DUMP");
            const char *dump_offset = getenv("DAH_EFFECT_TEXTURE_OFFSET");
            if (!dah_effect_texture_dumped && dump_path && *dump_path &&
                dump_offset && *dump_offset &&
                g_pg.tex[stage].offset == (uint32_t)strtoul(dump_offset, NULL, 0)) {
                FILE *dump = fopen(dump_path, "wb");
                if (dump) {
                    fwrite(source, 1u, bytes, dump);
                    fclose(dump);
                    fprintf(stderr,
                        "[DAH-EFFECT-TEXTURE-DUMP] stage=%u offset=%08X format=%u size=%ux%u bytes=%zu path=%s\n",
                        stage, g_pg.tex[stage].offset, format, w, h, bytes, dump_path);
                    dah_effect_texture_dumped = 1;
                }
            }
        }
        if(g_pg.active_pushbuffer && cache->texture && cache->content_valid &&
           cache->last_successful_submission==g_pg.active_submission &&
           cache->last_source==source && cache->last_source_bytes==bytes &&
           cache->width==w && cache->height==h && cache->format==(uint32_t)host_format)
            return cache->texture;
        int dah_snapshot_comparable=cache->texture && cache->content_valid &&
            cache->width==w && cache->height==h && cache->format==(uint32_t)host_format &&
            cache->snapshot && cache->snapshot_bytes==bytes;
        if(dah_snapshot_comparable && dah_mesh_texture_snapshot_matches(cache,source,bytes)){
            dah_mesh_texture_mark_success(cache,source,bytes);return cache->texture;
        }
        uint32_t hash=2166136261u; for(size_t j=0;j<bytes;j++) hash=(hash^source[j])*16777619u;
        if (dah_fine_texture_active) dah_fine_texture_hash_bytes += bytes;
        if(cache->texture && !dah_snapshot_comparable && cache->content_valid && cache->hash==hash && cache->width==w && cache->height==h && cache->format==(uint32_t)host_format) {dah_mesh_texture_mark_success(cache,source,bytes);return cache->texture;}
        if (!cache->texture || cache->width != w ||
            cache->height != h || cache->format != (uint32_t)host_format) {
            IDirect3DTexture8 *created = NULL;
            hr = dev->lpVtbl->CreateTexture(dev, w, h, 1u, 0,
                                            host_format, 0, &created);
            if (FAILED(hr) || !created) { return NULL; }
            if (cache->texture)
                cache->texture->lpVtbl->Release(cache->texture);
            cache->texture = created;
            cache->width = w; cache->height = h;
            cache->format = (uint32_t)host_format;
            cache->last_successful_submission=0u;cache->last_source=NULL;cache->last_source_bytes=0u;
            cache->content_valid=0u;dah_mesh_texture_snapshot_drop(cache);
        }
        /* Resources can change in place; do not cache content by address. */
        tex_obj = cache->texture;
        double dah_upload_start = dah_fine_texture_active ? dah_profile_ms() : 0.0;
        hr = tex_obj->lpVtbl->LockRect(tex_obj, 0u, &lr, NULL, 0);
        if (FAILED(hr)) { cache->content_valid=0u;dah_mesh_texture_snapshot_drop(cache);return NULL; }
        int decoded = 0;
        if (linear_argb) {
            decoded=lr.pBits&&lr.Pitch>=(INT)(w*4u);
            if(decoded)for(uint32_t y=0;y<h;y++)
                memcpy((uint8_t*)lr.pBits+(size_t)y*lr.Pitch,
                       source+(size_t)y*source_pitch,(size_t)w*4u);
        } else if (swizzled_argb) {
            decoded=lr.pBits&&lr.Pitch>=(INT)(w*4u);
            if(decoded&&lr.Pitch==(INT)(w*4u))xbox_unswizzle_rect(lr.pBits,source,w,h,4u);
            else if(decoded){uint8_t *linear=(uint8_t*)malloc(bytes);if(!linear)decoded=0;else{xbox_unswizzle_rect(linear,source,w,h,4u);for(uint32_t y=0;y<h;y++)memcpy((uint8_t*)lr.pBits+(size_t)y*lr.Pitch,linear+(size_t)y*w*4u,w*4u);free(linear);}}
            /* SZ_A8B8G8R8 is RGBA in little-endian guest memory. The
             * LIN_A8R8G8B8 host upload expects BGRA, including table textures. */
            if(decoded && swizzled_abgr)for(uint32_t y=0;y<h;y++){
                uint8_t *row=(uint8_t*)lr.pBits+(size_t)y*lr.Pitch;
                for(uint32_t x=0;x<w;x++){uint8_t red=row[4u*x];row[4u*x]=row[4u*x+2u];row[4u*x+2u]=red;}
            }
        } else if (compressed_alpha) {
            size_t row_bytes = ((w + 3u) / 4u) * 16u;
            decoded = lr.pBits && lr.Pitch >= (INT)row_bytes;
            if (decoded) for (uint32_t row = 0; row < (h + 3u) / 4u; ++row)
                memcpy((uint8_t *)lr.pBits + (size_t)row * lr.Pitch,
                       source + (size_t)row * row_bytes, row_bytes);
        } else decoded = lr.Pitch > 0 && dah_bc1_decode(source, bytes, w, h,
                                                     lr.pBits, (size_t)lr.Pitch);
        hr = tex_obj->lpVtbl->UnlockRect(tex_obj, 0u);
        if (!decoded || FAILED(hr)) { cache->content_valid=0u;dah_mesh_texture_snapshot_drop(cache);return NULL; }
        if (dah_fine_texture_active) {
            dah_fine_texture_upload_ms += dah_profile_ms() - dah_upload_start;
            ++dah_fine_texture_uploads;
        }
        cache->hash=hash;cache->content_valid=1u;
        dah_mesh_texture_snapshot_update(cache,source,bytes);
        dah_mesh_texture_mark_success(cache,source,bytes);
        if (0)
            fprintf(stderr, "[DAH-3D-BC1] size=%ux%u bytes=%zu offset=%08X window=low raw=%02X%02X%02X%02X%02X%02X%02X%02X\n",
                    w, h, bytes, g_pg.tex[stage].offset,
                    source[0], source[1], source[2], source[3],
                    source[4], source[5], source[6], source[7]);
    }


    return tex_obj;
}

static IDirect3DTexture8 *dah_mesh_texture(unsigned stage,IDirect3DDevice8 *dev)
{
    return dah_mesh_texture_window(stage,dev,0);
}

/* Independent of the early Farm material budget. Capture only the exact
 * retail unlit program in [start,start+32), at most 64 draw outcomes. This
 * observes already-built CPU vertices and state; it performs no GPU readback. */
static void dah_hud_draw_trace(const char *reason,unsigned kind,
    const OutputVertex *out,uint32_t count,uint32_t fail_index,HRESULT hr)
{
    static int initialized,enabled;
    static uint32_t start;
    static unsigned reports;
    if(kind!=14u)return;
    if(!initialized){
        const char *value=getenv("DAH_HUD_DRAW_TRACE_START");
        initialized=1;
        if(value&&*value){
            char *end;unsigned long parsed=strtoul(value,&end,0);
            if(!*end&&parsed<=UINT32_MAX-32u){start=(uint32_t)parsed;enabled=1;}
        }
    }
    if(!enabled||g_pg.active_submission<start||
       g_pg.active_submission-start>=32u||reports>=64u)return;
    ++reports;
    uint32_t indices=g_pg.index_count<MAX_INLINE_VERTS?g_pg.index_count:MAX_INLINE_VERTS;
    uint32_t first=UINT32_MAX,last=0;
    float minimum[6]={FLT_MAX,FLT_MAX,FLT_MAX,FLT_MAX,FLT_MAX,FLT_MAX};
    float maximum[6]={-FLT_MAX,-FLT_MAX,-FLT_MAX,-FLT_MAX,-FLT_MAX,-FLT_MAX};
    unsigned rgba_min[4]={255,255,255,255},rgba_max[4]={0,0,0,0};
    unsigned finite=0,front=0;
    for(uint32_t i=0;i<indices;++i){
        if(g_pg.indices[i]<first)first=g_pg.indices[i];
        if(g_pg.indices[i]>last)last=g_pg.indices[i];
    }
    if(!out)count=0;
    if(count>indices)count=indices;
    for(uint32_t i=0;i<count;++i){
        float values[6]={out[i].x,out[i].y,out[i].z,out[i].rhw,out[i].u,out[i].v};
        unsigned channels[4]={(out[i].color>>16u)&255u,(out[i].color>>8u)&255u,
            out[i].color&255u,out[i].color>>24u};
        int all_finite=1;
        for(unsigned j=0;j<6u;++j){
            if(!isfinite(values[j]))all_finite=0;
            else{if(values[j]<minimum[j])minimum[j]=values[j];
                 if(values[j]>maximum[j])maximum[j]=values[j];}
        }
        finite+=all_finite;front+=out[i].rhw>0.0f;
        for(unsigned j=0;j<4u;++j){
            if(channels[j]<rgba_min[j])rgba_min[j]=channels[j];
            if(channels[j]>rgba_max[j])rgba_max[j]=channels[j];
        }
    }
    fprintf(stderr,"[DAH-HUD-DRAW] submit=%u draw=%u result=%s kind=14 mode=%u "
        "indices=%u range=%u..%u overflow=%d inline=%u built=%u fail_i=%u finite=%u front=%u "
        "target=%08X surface=%08X pitch=%08X zeta=%08X clip=%08X,%08X mask=%08X "
        "depth=%d,%d,%04X cull=%d,%04X,%04X alpha=%d,%04X,%u "
        "blend=%d,%04X,%04X,%04X combiner=%08X final=%08X,%08X stages=%08X hr=%08lX\n",
        g_pg.active_submission,g_pg.indexed_diagnostic_id,reason,g_pg.draw_mode,
        g_pg.index_count,first,last,g_pg.index_overflow,g_pg.inline_count,count,fail_index,finite,front,
        g_pg.surface_color_offset,g_pg.surface_format,g_pg.surface_pitch,g_pg.surface_zeta_offset,
        g_pg.surface_clip_h,g_pg.surface_clip_v,g_pg.color_mask,
        g_pg.depth_test,g_pg.depth_write,g_pg.depth_func,g_pg.cull_enable,g_pg.front_face,g_pg.cull_face,
        g_pg.alpha_test,g_pg.alpha_func,g_pg.alpha_ref,g_pg.blend_enable,g_pg.blend_sfactor,
        g_pg.blend_dfactor,g_pg.blend_equation,g_pg.combiner_control,g_pg.final_cw0,g_pg.final_cw1,
        g_pg.shader_stage_program,(unsigned long)hr);
    if(count){
        fprintf(stderr,"[DAH-HUD-BOUNDS] submit=%u draw=%u xy=%.9g,%.9g..%.9g,%.9g "
            "z=%.9g..%.9g rhw=%.9g..%.9g uv=%.9g,%.9g..%.9g,%.9g "
            "rgba=%u,%u,%u,%u..%u,%u,%u,%u\n",
            g_pg.active_submission,g_pg.indexed_diagnostic_id,minimum[0],minimum[1],maximum[0],maximum[1],
            minimum[2],maximum[2],minimum[3],maximum[3],minimum[4],minimum[5],maximum[4],maximum[5],
            rgba_min[0],rgba_min[1],rgba_min[2],rgba_min[3],rgba_max[0],rgba_max[1],rgba_max[2],rgba_max[3]);
        for(unsigned i=0;i<count&&i<4u;++i)
            fprintf(stderr,"[DAH-HUD-VERTEX] submit=%u draw=%u i=%u index=%u "
                "xyz=%.9g,%.9g,%.9g rhw=%.9g uv=%.9g,%.9g rgba=%u,%u,%u,%u\n",
                g_pg.active_submission,g_pg.indexed_diagnostic_id,i,g_pg.indices[i],
                out[i].x,out[i].y,out[i].z,out[i].rhw,out[i].u,out[i].v,
                (out[i].color>>16u)&255u,(out[i].color>>8u)&255u,out[i].color&255u,out[i].color>>24u);
    }
    fprintf(stderr,"[DAH-HUD-ARRAYS] submit=%u draw=%u",g_pg.active_submission,g_pg.indexed_diagnostic_id);
    for(unsigned slot=0;slot<16u;++slot)if(g_pg.array_format[slot])
        fprintf(stderr," %u:%08X:%08X",slot,g_pg.array_offset[slot],g_pg.array_format[slot]);
    fputc('\n',stderr);
    static const unsigned constants[]={1,2,36,37,38,39,187};
    for(unsigned ci=0;ci<sizeof(constants)/sizeof(constants[0]);++ci){
        unsigned at=constants[ci]*4u;
        fprintf(stderr,"[DAH-HUD-CONSTANT] submit=%u draw=%u c=%u bits=%08X,%08X,%08X,%08X valid=%u%u%u%u\n",
            g_pg.active_submission,g_pg.indexed_diagnostic_id,constants[ci],
            g_pg.transform_constants[at],g_pg.transform_constants[at+1u],
            g_pg.transform_constants[at+2u],g_pg.transform_constants[at+3u],
            g_pg.transform_constant_valid[at],g_pg.transform_constant_valid[at+1u],
            g_pg.transform_constant_valid[at+2u],g_pg.transform_constant_valid[at+3u]);
    }
    for(unsigned stage=0;stage<4u;++stage)
        fprintf(stderr,"[DAH-HUD-TEXTURE] submit=%u draw=%u stage=%u enabled=%d "
            "offset=%08X format=%08X control=%08X,%08X rect=%08X address=%08X filter=%08X\n",
            g_pg.active_submission,g_pg.indexed_diagnostic_id,stage,g_pg.tex[stage].enabled,
            g_pg.tex[stage].offset,g_pg.tex[stage].format,g_pg.tex[stage].control0,g_pg.tex[stage].control1,
            g_pg.tex[stage].image_rect,g_pg.tex[stage].address,g_pg.tex[stage].filter);
    unsigned stages=g_pg.combiner_control&15u;if(stages>8u)stages=8u;
    for(unsigned stage=0;stage<stages;++stage)
        fprintf(stderr,"[DAH-HUD-COMBINER] submit=%u draw=%u stage=%u color=%08X,%08X alpha=%08X,%08X factor=%08X,%08X\n",
            g_pg.active_submission,g_pg.indexed_diagnostic_id,stage,g_pg.color_icw[stage],g_pg.color_ocw[stage],
            g_pg.alpha_icw[stage],g_pg.alpha_ocw[stage],g_pg.factor0[stage],g_pg.factor1[stage]);
    fflush(stderr);
}

/* Opt-in Farm material probe. State is logged only for the first 256
 * accepted meshes and four instances of each distinct rejected shader/material.
 * No hot-path work is done unless DAH_FARM_MATERIAL_TRACE is set. */
static int dah_farm_material_trace_enabled(void)
{
    static int enabled = -1;
    static unsigned first_submission = 2750u;
    if (enabled < 0) {
        const char *first;
        enabled = getenv("DAH_FARM_MATERIAL_TRACE") != NULL;
        first = getenv("DAH_FARM_MATERIAL_TRACE_START");
        if (first && *first) first_submission = (unsigned)strtoul(first,NULL,0);
    }
    return enabled && g_pg.active_submission >= first_submission &&
           (g_pg.transform_mode & 3u) == 2u && g_pg.index_count >= 3u;
}

static void dah_farm_material_trace(const char *reason, unsigned kind,
                                    const OutputVertex *out, uint32_t count,
                                    uint32_t vertex_index, HRESULT hr)
{
    dah_hud_draw_trace(reason,kind,out,count,vertex_index,hr);
    static unsigned accepted, accepted_other, rejected;
    static int farm_armed;
    static struct { uint32_t hash; unsigned n; } seen[128];
    static unsigned seen_count;
    uint32_t base, p1, p5, hash = 2166136261u;
    float xmin = 1e30f, ymin = 1e30f, xmax = -1e30f, ymax = -1e30f;
    float zmin = 1e30f, zmax = -1e30f;
    uint32_t color_or = 0, color_and = 0xFFFFFFFFu;
    unsigned visible = 0;
    int ok = strcmp(reason, "accepted") == 0;

    if ((kind == 13u || kind == 15u) && strcmp(reason,"accepted") != 0 &&
        dah_crypto_head_trace_enabled() && g_pg.active_submission >= 6000u &&
        g_pg.active_submission <= 7000u && g_pg.active_submission % 100u == 0u) {
        static unsigned traced_rejects;
        if (traced_rejects++ < 32u)
            fprintf(stderr,
                "[DAH-CRYPTO-REJECT] sub=%u draw=%u reason=%s n=%u built=%u "
                "at=%u tex0=%08X,%08X tex1=%08X,%08X array0=%08X "
                "target=%08X\n",
                g_pg.active_submission,g_pg.indexed_diagnostic_id,reason,
                g_pg.index_count,count,vertex_index,g_pg.tex[0].offset,
                g_pg.tex[0].format,g_pg.tex[1].offset,g_pg.tex[1].format,
                g_pg.array_offset[0],g_pg.surface_color_offset);
    }

    if (!dah_farm_material_trace_enabled()) return;
    if (ok) {
        if (kind >= 10u) farm_armed = 1;
        if (!farm_armed) return;
        if (kind < 10u) {
            if (accepted_other++ >= 128u) return;
        } else if (accepted++ >= 256u) return;
    } else {
        if (rejected >= 128u) return;
        base = g_pg.transform_start <= 134u ? g_pg.transform_start * 4u : 0u;
        p1 = g_pg.transform_program[base + 1u];
        p5 = g_pg.transform_program[base + 5u];
        for (const char *s = reason; *s; ++s) hash = (hash ^ (uint8_t)*s) * 16777619u;
        hash = (hash ^ kind) * 16777619u;
        hash = (hash ^ p1) * 16777619u;
        hash = (hash ^ p5) * 16777619u;
        hash = (hash ^ g_pg.tex[0].format) * 16777619u;
        hash = (hash ^ g_pg.tex[1].format) * 16777619u;
        for (unsigned j = 0; j < seen_count; ++j) if (seen[j].hash == hash) {
            if (seen[j].n++ >= 4u) return;
            goto unique_checked;
        }
        if (seen_count >= 128u) return;
        seen[seen_count].hash = hash;
        seen[seen_count++].n = 1u;
unique_checked:
        ++rejected;
    }
    base = g_pg.transform_start <= 134u ? g_pg.transform_start * 4u : 0u;
    p1 = g_pg.transform_program[base + 1u];
    p5 = g_pg.transform_program[base + 5u];
    for (uint32_t i = 0; i < count && out; ++i) {
        if (out[i].x < xmin) xmin = out[i].x;
        if (out[i].x > xmax) xmax = out[i].x;
        if (out[i].y < ymin) ymin = out[i].y;
        if (out[i].y > ymax) ymax = out[i].y;
        if (out[i].z < zmin) zmin = out[i].z;
        if (out[i].z > zmax) zmax = out[i].z;
        color_or |= out[i].color;
        color_and &= out[i].color;
        if (out[i].rhw > 0.0f) ++visible;
    }
    fprintf(stderr,
        "[DAH-FARM-MATERIAL] submit=%u draw=%u result=%s kind=%u n=%u built=%u fail_i=%u "
        "prog=%08X,%08X target=%08X tex0=%u,%08X,%08X tex1=%u,%08X,%08X "
        "xy=%.2f,%.2f..%.2f,%.2f z=%.5g..%.5g at_y400=%u front=%u "
        "argb0=%08X argb_or=%08X argb_and=%08X "
        "sampler0=%08X,%08X bias=%.3f aniso=%u "
        "combiner=%08X final=%08X,%08X stage=%08X "
        "blend=%u,%04X,%04X depth=%d,%d,%04X alpha=%d,%04X,%u hr=%08lX\n",
        g_pg.active_submission, g_pg.indexed_diagnostic_id, reason, kind,
        g_pg.index_count, count, vertex_index, p1, p5,
        g_pg.surface_color_offset,
        g_pg.tex[0].enabled, g_pg.tex[0].offset, g_pg.tex[0].format,
        g_pg.tex[1].enabled, g_pg.tex[1].offset, g_pg.tex[1].format,
        xmin, ymin, xmax, ymax, zmin, zmax,
        count && ymin <= 400.0f && ymax >= 400.0f, visible,
        count ? out[0].color : 0u, color_or, color_and,
        g_pg.tex[0].filter, g_pg.tex[0].control0,
        nv2a_texture_lod_bias(g_pg.tex[0].filter),
        nv2a_texture_max_anisotropy(g_pg.tex[0].control0),
        g_pg.combiner_control, g_pg.final_cw0, g_pg.final_cw1,
        g_pg.shader_stage_program,
        g_pg.blend_enable, g_pg.blend_sfactor, g_pg.blend_dfactor,
        g_pg.depth_test, g_pg.depth_write, g_pg.depth_func,
        g_pg.alpha_test, g_pg.alpha_func, g_pg.alpha_ref,
        (unsigned long)hr);
}

/* One offscreen and one main-target sample of each missing Farm program.
 * This is intentionally opt-in and bounded to four complete snapshots. */
static void dah_farm_unknown_program_dump(void)
{
    static uint32_t seen_target[3][2];
    static unsigned seen_count[3];
    unsigned slot, base, min_index = UINT32_MAX, max_index = 0u;
    uint32_t fingerprint, target;
    if (!(dah_farm_material_trace_enabled() || dah_crypto_head_trace_enabled()) ||
        g_pg.active_submission < (dah_crypto_head_trace_enabled() ? 7000u : 2900u) ||
        g_pg.index_count < (dah_crypto_head_trace_enabled() ? 30u : 100u) ||
        g_pg.transform_start > 100u) return;
    base = g_pg.transform_start * 4u;
    fingerprint = g_pg.transform_program[base + 1u];
    if (fingerprint == 0x0057E61Bu) slot = 0u;
    else if (fingerprint == 0x00C4801Bu) slot = 1u;
    /* Rockwell vehicle body/reflection program.  The wheels and trim use
     * existing Farm paths, but this body pass was previously rejected before
     * any vertices were transformed.  Capture it once per target so its exact
     * retail instruction stream can be translated and verified. */
    else if (fingerprint == 0x0048421Bu) slot = 2u;
    else return;
    target = g_pg.surface_color_offset;
    for (unsigned j = 0; j < seen_count[slot]; ++j)
        if (seen_target[slot][j] == target) return;
    if (seen_count[slot] >= 2u) return;
    seen_target[slot][seen_count[slot]++] = target;
    for (uint32_t i = 0; i < g_pg.index_count; ++i) {
        if (g_pg.indices[i] < min_index) min_index = g_pg.indices[i];
        if (g_pg.indices[i] > max_index) max_index = g_pg.indices[i];
    }
    fprintf(stderr, "[DAH-FARM-PROGRAM] begin submit=%u draw=%u sig=%08X target=%08X start=%u indices=%u range=%u..%u\n",
            g_pg.active_submission, g_pg.indexed_diagnostic_id, fingerprint,
            target, g_pg.transform_start, g_pg.index_count, min_index, max_index);
    for (unsigned ins = 0; ins < 128u && ins + g_pg.transform_start < 136u; ++ins) {
        unsigned at = base + ins * 4u;
        fprintf(stderr, "[DAH-FARM-PROGRAM] ins=%02u word=%08X,%08X,%08X,%08X valid=%u%u%u%u\n",
                ins, g_pg.transform_program[at], g_pg.transform_program[at + 1u],
                g_pg.transform_program[at + 2u], g_pg.transform_program[at + 3u],
                g_pg.transform_valid[at], g_pg.transform_valid[at + 1u],
                g_pg.transform_valid[at + 2u], g_pg.transform_valid[at + 3u]);
        if (g_pg.transform_valid[at + 3u] && (g_pg.transform_program[at + 3u] & 1u)) break;
    }
    for (unsigned s = 0; s < 16u; ++s) {
        uint32_t fmt = g_pg.array_format[s], off = g_pg.array_offset[s];
        if (!fmt && !off) continue;
        fprintf(stderr, "[DAH-FARM-PROGRAM] array=%u base=%08X format=%08X type=%u count=%u stride=%u\n",
                s, off, fmt, fmt & 15u, (fmt >> 4u) & 15u, fmt >> 8u);
        if (s < 4u && min_index != UINT32_MAX && (fmt >> 8u) < 0x10000u) {
            uint64_t addr = (uint64_t)off + (uint64_t)min_index * (fmt >> 8u);
            if (addr <= UINT32_MAX) {
                const uint8_t *raw = indexed_guest_bytes_window((uint32_t)addr, 16u, 0);
                if (raw) {
                    uint32_t words[4];
                    memcpy(words, raw, sizeof(words));
                    fprintf(stderr, "[DAH-FARM-PROGRAM] sample=%u addr=%08X raw=%08X,%08X,%08X,%08X\n",
                            s, (uint32_t)addr, words[0], words[1], words[2], words[3]);
                }
            }
        }
    }
    if (fingerprint == 0x0057E61Bu && dah_skin_dump_enabled()) {
        unsigned samples = 0u;
        uint32_t sampled[8];
        fprintf(stderr, "[DAH-FARM-SKIN-ORACLE] begin submit=%u draw=%u target=%08X constants=192 vertex_stride=%u\n",
                g_pg.active_submission, g_pg.indexed_diagnostic_id, target,
                g_pg.array_format[0] >> 8u);
        for (unsigned c = 0; c < 192u; ++c) {
            unsigned at = c * 4u;
            fprintf(stderr, "[DAH-FARM-SKIN-ORACLE] c=%03u bits=%08X,%08X,%08X,%08X valid=%u%u%u%u\n",
                    c, g_pg.transform_constants[at], g_pg.transform_constants[at + 1u],
                    g_pg.transform_constants[at + 2u], g_pg.transform_constants[at + 3u],
                    g_pg.transform_constant_valid[at], g_pg.transform_constant_valid[at + 1u],
                    g_pg.transform_constant_valid[at + 2u], g_pg.transform_constant_valid[at + 3u]);
        }
        fprintf(stderr, "[DAH-FARM-SKIN-ORACLE] first_indices=");
        for (uint32_t i = 0; i < g_pg.index_count && i < 32u; ++i)
            fprintf(stderr, "%s%u", i ? "," : "", g_pg.indices[i]);
        fputc('\n', stderr);
        for (uint32_t i = 0; i < g_pg.index_count && samples < 8u; ++i) {
            uint32_t index = g_pg.indices[i];
            unsigned j;
            for (j = 0; j < samples; ++j) if (sampled[j] == index) break;
            if (j != samples) continue;
            sampled[samples++] = index;
            uint32_t stride = g_pg.array_format[0] >> 8u;
            uint64_t addr = (uint64_t)g_pg.array_offset[0] + (uint64_t)index * stride;
            if (stride != 40u || addr > UINT32_MAX) continue;
            const uint8_t *raw = indexed_guest_bytes_window((uint32_t)addr, 40u, 0);
            const char *window = "low";
            if (!raw) {raw = indexed_guest_bytes_window((uint32_t)addr, 40u, 1); window = "contiguous";}
            if (!raw) continue;
            uint32_t words[10];
            memcpy(words, raw, sizeof(words));
            fprintf(stderr, "[DAH-FARM-SKIN-ORACLE] vertex=%u addr=%08X window=%s raw=",
                    index, (uint32_t)addr, window);
            for (unsigned k = 0; k < 10u; ++k) fprintf(stderr, "%s%08X", k ? "," : "", words[k]);
            fputc('\n', stderr);
        }
        fprintf(stderr, "[DAH-FARM-SKIN-ORACLE] end submit=%u draw=%u target=%08X samples=%u\n",
                g_pg.active_submission, g_pg.indexed_diagnostic_id, target, samples);
    }
    if (dah_crypto_head_trace_enabled())
        for (unsigned stage = 0; stage < 2u; ++stage)
            fprintf(stderr, "[DAH-HEAD-TEX] stage=%u enabled=%d offset=%08X format=%08X rect=%08X\n",
                    stage, g_pg.tex[stage].enabled, g_pg.tex[stage].offset,
                    g_pg.tex[stage].format, g_pg.tex[stage].image_rect);
    fprintf(stderr, "[DAH-FARM-PROGRAM] end sig=%08X target=%08X\n", fingerprint, target);
}


/* Opt-in attribution only: at most two consecutive submissions (default
 * 6300/6301, overridden by DAH_COLOR_MASK_TRACE_FIRST), plus the first32
 * masked 3D draws elsewhere. This is outside normal FPS acceptance runs. */

/* Observed raw guest state only. "seen" distinguishes an unobserved field
 * from a written zero. These methods keep their existing dispatch behavior. */
static uint32_t dah_trace_stencil_raw[8],dah_trace_stencil_seen;
static void dah_trace_stencil_observe(uint32_t method,uint32_t param)
{
    unsigned index;
    if(method==NV097_SET_STENCIL_TEST_ENABLE)index=0u;
    else if(method>=NV097_SET_STENCIL_MASK && method<=NV097_SET_STENCIL_OP_ZPASS && !(method&3u))
        index=1u+(method-NV097_SET_STENCIL_MASK)/4u;
    else return;
    if(!dah_color_mask_trace_enabled())return;
    dah_trace_stencil_raw[index]=param;
    dah_trace_stencil_seen|=1u<<index;
}

/* Candidate coverage only, before GPU cull/depth/stencil/texture evaluation.
 * Each matching triangle includes the actual transformed vertices, so a
 * nonzero hit is evidence to investigate, not proof of a visible fragment. */
static void dah_trace_draw_probes(unsigned kind,const OutputVertex *out)
{
    static const float points[4][2]={{20.5f,20.5f},{20.5f,175.5f},{400.5f,180.5f},{438.5f,330.5f}};
    static unsigned details;
    unsigned hits[4]={0,0,0,0},first[4]={0,0,0,0};
    for(unsigned p=0;p<4u;++p){
        float x=points[p][0],y=points[p][1];
        for(uint32_t i=2u;i<g_pg.index_count;++i){
            const OutputVertex *a=&out[i-2u],*b=&out[i-1u],*c=&out[i];
            float area=(b->x-a->x)*(c->y-a->y)-(b->y-a->y)*(c->x-a->x);
            float e0=(b->x-a->x)*(y-a->y)-(b->y-a->y)*(x-a->x);
            float e1=(c->x-b->x)*(y-b->y)-(c->y-b->y)*(x-b->x);
            float e2=(a->x-c->x)*(y-c->y)-(a->y-c->y)*(x-c->x);
            if(!(a->rhw>0.f && b->rhw>0.f && c->rhw>0.f) || !isfinite(area) || fabsf(area)<1e-8f)continue;
            if((e0>=0.f && e1>=0.f && e2>=0.f)||(e0<=0.f && e1<=0.f && e2<=0.f)){
                if(!hits[p])first[p]=i;
                ++hits[p];
            }
        }
    }
    fprintf(stderr,"[DAH-DRAW-STATE] sub=%u draw=%u kind=%u zeta=%08X surface=%08X cull=%u,%X,%X "
        "stencil_seen=%02X stencil=%X,%X,%X,%X,%X,%X,%X,%X probes=%u,%u,%u,%u\n",
        g_pg.active_submission,g_pg.indexed_diagnostic_id,kind,g_pg.surface_zeta_offset,g_pg.surface_format,
        g_pg.cull_enable,g_pg.front_face,g_pg.cull_face,dah_trace_stencil_seen,
        dah_trace_stencil_raw[0],dah_trace_stencil_raw[1],dah_trace_stencil_raw[2],dah_trace_stencil_raw[3],
        dah_trace_stencil_raw[4],dah_trace_stencil_raw[5],dah_trace_stencil_raw[6],dah_trace_stencil_raw[7],
        hits[0],hits[1],hits[2],hits[3]);
    for(unsigned p=0;p<4u;++p){
        if(!hits[p] || details>=1024u)continue;
        ++details;
        uint32_t i=first[p];
        fprintf(stderr,"[DAH-DRAW-TRIANGLE] sub=%u draw=%u probe=%u xy=%.1f,%.1f strip_i=%u vertices=",
            g_pg.active_submission,g_pg.indexed_diagnostic_id,p,points[p][0],points[p][1],i);
        for(uint32_t j=i-2u;j<=i;++j){
            const OutputVertex *v=&out[j];
            fprintf(stderr," [%.9g,%.9g,%.9g,%.9g,%08X,%.9g,%.9g]",v->x,v->y,v->z,v->rhw,v->color,v->u,v->v);
        }
        fputc('\n',stderr);
    }
}


/* Pure diagnostics: one specified submission, only the observed presented
 * target 03C20000, at most 64 candidate draws / 128 three-pixel maps. */
static unsigned dah_pixel_xy[3][2]={{20u,20u},{50u,200u},{450u,180u}};
static struct {
    unsigned active,kind,mask;uint32_t before[3];
    float fog_min,fog_max,fog_probe_first[3];
} dah_pixel_pending;
static void dah_pixel_trace_begin(unsigned kind,const OutputVertex *out)
{
    static unsigned configured,first=7001u,pairs,auto_triangles,any_target;
    dah_pixel_pending.active=0u;
    if(!dah_draw_pixel_trace_enabled())return;
    if(!configured){
        const char *s=getenv("DAH_DRAW_PIXEL_TRACE_FIRST");
        if(s && *s){char *end;unsigned long n=strtoul(s,&end,10);if(!*end && n<0xFFFFFFFFu)first=(unsigned)n;}
        s=getenv("DAH_DRAW_PIXEL_TRACE_XY");
        if(s && *s){
            unsigned x0,y0,x1,y1,x2,y2;char tail;
            if(sscanf(s,"%u,%u;%u,%u;%u,%u%c",&x0,&y0,&x1,&y1,&x2,&y2,&tail)==6 &&
               x0<4096u && y0<4096u && x1<4096u && y1<4096u && x2<4096u && y2<4096u){
                dah_pixel_xy[0][0]=x0;dah_pixel_xy[0][1]=y0;
                dah_pixel_xy[1][0]=x1;dah_pixel_xy[1][1]=y1;
                dah_pixel_xy[2][0]=x2;dah_pixel_xy[2][1]=y2;
            }
        }
        s=getenv("DAH_DRAW_PIXEL_TRACE_AUTO");
        auto_triangles=s && *s && strcmp(s,"0");
        s=getenv("DAH_DRAW_PIXEL_TRACE_ANY_TARGET");
        any_target=s && *s && strcmp(s,"0");
        configured=1u;
    }
    if(g_pg.active_submission!=first || pairs>=64u || (!any_target && g_pg.surface_color_offset!=0x03C20000u) ||
       !dah_nv2a_color_write_mask(g_pg.color_mask))return;
    if(auto_triangles){
        unsigned found=0u;
        for(uint32_t i=2u;i<g_pg.index_count && found<3u;++i){
            const OutputVertex *a=&out[i-2u],*b=&out[i-1u],*c=&out[i];
            float area=(b->x-a->x)*(c->y-a->y)-(b->y-a->y)*(c->x-a->x);
            float x=(a->x+b->x+c->x)/3.f,y=(a->y+b->y+c->y)/3.f;
            if(a->rhw>0.f && b->rhw>0.f && c->rhw>0.f && isfinite(area) && fabsf(area)>.01f &&
               isfinite(x) && isfinite(y) && x>=0.f && y>=0.f && x<640.f && y<480.f){
                dah_pixel_xy[found][0]=(unsigned)x;dah_pixel_xy[found][1]=(unsigned)y;++found;
            }
        }
        if(!found)return;
        while(found<3u){dah_pixel_xy[found][0]=dah_pixel_xy[0][0];dah_pixel_xy[found][1]=dah_pixel_xy[0][1];++found;}
    }
    unsigned mask=0u;
    dah_pixel_pending.fog_min=1e30f;dah_pixel_pending.fog_max=-1e30f;
    for(unsigned p=0;p<3u;++p)dah_pixel_pending.fog_probe_first[p]=NAN;
    float xmin=1e30f,ymin=1e30f,xmax=-1e30f,ymax=-1e30f;
    int mixed=0;
    for(uint32_t i=0;i<g_pg.index_count;++i){
        if(out[i].x<xmin)xmin=out[i].x;if(out[i].x>xmax)xmax=out[i].x;
        if(out[i].y<ymin)ymin=out[i].y;if(out[i].y>ymax)ymax=out[i].y;
        if(!(out[i].rhw>0.f))mixed=1;
        float fog=kind==12u?out[i].fog_coord:out[i].w1;
        if(fog<dah_pixel_pending.fog_min)dah_pixel_pending.fog_min=fog;
        if(fog>dah_pixel_pending.fog_max)dah_pixel_pending.fog_max=fog;
    }
    for(unsigned p=0;p<3u;++p){
        float x=(float)dah_pixel_xy[p][0]+.5f,y=(float)dah_pixel_xy[p][1]+.5f;
        if(x<xmin || x>xmax || y<ymin || y>ymax)continue;
        /* Conservatively retain mixed-W candidates; they need GPU clipping
         * before screen coverage can be decided. No geometry is changed. */
        if(mixed){mask|=1u<<p;continue;}
        for(uint32_t i=2u;i<g_pg.index_count;++i){
            const OutputVertex *a=&out[i-2u],*b=&out[i-1u],*c=&out[i];
            float area=(b->x-a->x)*(c->y-a->y)-(b->y-a->y)*(c->x-a->x);
            float e0=(b->x-a->x)*(y-a->y)-(b->y-a->y)*(x-a->x);
            float e1=(c->x-b->x)*(y-b->y)-(c->y-b->y)*(x-b->x);
            float e2=(a->x-c->x)*(y-c->y)-(a->y-c->y)*(x-c->x);
            if(!isfinite(area) || fabsf(area)<1e-8f)continue;
            if((e0>=0.f && e1>=0.f && e2>=0.f)||(e0<=0.f && e1<=0.f && e2<=0.f)){
                float wa=(e1/area)*a->rhw,wb=(e2/area)*b->rhw,wc=(e0/area)*c->rhw;
                float denom=wa+wb+wc;
                float fa=kind==12u?a->fog_coord:a->w1;
                float fb=kind==12u?b->fog_coord:b->w1;
                float fc=kind==12u?c->fog_coord:c->w1;
                if(isfinite(denom)&&fabsf(denom)>1e-20f)
                    dah_pixel_pending.fog_probe_first[p]=(wa*fa+wb*fb+wc*fc)/denom;
                mask|=1u<<p;break;
            }
        }
    }
    if(!mask)return;
    if(!pairs){
        int queued=dah_request_frame_capture();
        fprintf(stderr,"[DAH-PIXEL-CAPTURE] sub=%u queued=%d maps_max=128 pairs_max=64; diagnostic timing excluded\n",g_pg.active_submission,queued);
    }
    ++pairs;
    HRESULT hr=dah_read_active_rt_pixels(d3d8_GetD3D11Context(),dah_pixel_xy,3,dah_pixel_pending.before);
    if(FAILED(hr)){fprintf(stderr,"[DAH-PIXEL-READ-FAIL] sub=%u draw=%u kind=%u phase=before xy=%u,%u;%u,%u;%u,%u hr=%08lX\n",g_pg.active_submission,g_pg.indexed_diagnostic_id,kind,dah_pixel_xy[0][0],dah_pixel_xy[0][1],dah_pixel_xy[1][0],dah_pixel_xy[1][1],dah_pixel_xy[2][0],dah_pixel_xy[2][1],(unsigned long)hr);return;}
    dah_pixel_pending.active=1u;dah_pixel_pending.kind=kind;dah_pixel_pending.mask=mask;
}
static void dah_pixel_trace_end(HRESULT draw_hr)
{
    static unsigned material_dumped;
    uint32_t after[3];unsigned darkened=0u;
    if(!dah_pixel_pending.active)return;
    dah_pixel_pending.active=0u;
    HRESULT hr=dah_read_active_rt_pixels(d3d8_GetD3D11Context(),dah_pixel_xy,3,after);
    if(FAILED(hr)){fprintf(stderr,"[DAH-PIXEL-READ-FAIL] sub=%u draw=%u phase=after hr=%08lX\n",g_pg.active_submission,g_pg.indexed_diagnostic_id,(unsigned long)hr);return;}
    for(unsigned p=0;p<3u;++p){
        uint32_t a=dah_pixel_pending.before[p],b=after[p];
        int old_dark=(a>>24)<=2u && ((a>>16)&255u)<=2u && ((a>>8)&255u)<=2u;
        int new_dark=(b>>24)<=2u && ((b>>16)&255u)<=2u && ((b>>8)&255u)<=2u;
        if(!old_dark && new_dark)darkened|=1u<<p;
    }
    fprintf(stderr,"[DAH-PIXEL-DRAW] sub=%u draw=%u kind=%u target=%08X candidate=%X darkened=%X hr=%08lX "
        "p0=%u,%u:%08X>%08X p1=%u,%u:%08X>%08X p2=%u,%u:%08X>%08X "
        "nv=%08X depth=%u,%u,%X blend=%u,%X,%X tex0=%08X,%08X tex1=%08X,%08X final=%08X,%08X\n",
        g_pg.active_submission,g_pg.indexed_diagnostic_id,dah_pixel_pending.kind,g_pg.surface_color_offset,
        dah_pixel_pending.mask,darkened,(unsigned long)draw_hr,
        dah_pixel_xy[0][0],dah_pixel_xy[0][1],dah_pixel_pending.before[0],after[0],
        dah_pixel_xy[1][0],dah_pixel_xy[1][1],dah_pixel_pending.before[1],after[1],
        dah_pixel_xy[2][0],dah_pixel_xy[2][1],dah_pixel_pending.before[2],after[2],
        g_pg.color_mask,g_pg.depth_test,g_pg.depth_write,g_pg.depth_func,g_pg.blend_enable,g_pg.blend_sfactor,g_pg.blend_dfactor,
        g_pg.tex[0].offset,g_pg.tex[0].format,g_pg.tex[1].offset,g_pg.tex[1].format,g_pg.final_cw0,g_pg.final_cw1);
    /* First covering triangle interpolation is observational; depth/cull
     * may select another triangle. NaN denotes absent/ambiguous coverage. */
    fprintf(stderr,"[DAH-PIXEL-FOG] sub=%u draw=%u kind=%u enabled=%d raw=%08X host=%08X range=%.9g,%.9g first_tri_probe=%.9g,%.9g,%.9g\n",
        g_pg.active_submission,g_pg.indexed_diagnostic_id,dah_pixel_pending.kind,
        g_pg.fog_enable,g_pg.fog_color_raw,d3d8_GetRenderStates()[D3DRS_FOGCOLOR],
        dah_pixel_pending.fog_min,dah_pixel_pending.fog_max,
        dah_pixel_pending.fog_probe_first[0],dah_pixel_pending.fog_probe_first[1],dah_pixel_pending.fog_probe_first[2]);
    if(darkened && !material_dumped){
        material_dumped=1u;
        fprintf(stderr,"[DAH-PIXEL-PROGRAM] sub=%u draw=%u start=%u mode=%08X words=",
            g_pg.active_submission,g_pg.indexed_diagnostic_id,g_pg.transform_start,g_pg.transform_mode);
        for(unsigned i=g_pg.transform_start*4u;i<136u*4u;++i)
            if(g_pg.transform_valid[i])fprintf(stderr," %u:%08X",i,g_pg.transform_program[i]);
        fputc('\n',stderr);
        fprintf(stderr,"[DAH-PIXEL-CONSTANTS] sub=%u draw=%u words=",g_pg.active_submission,g_pg.indexed_diagnostic_id);
        for(unsigned i=0;i<192u*4u;++i)
            if(g_pg.transform_constant_valid[i])fprintf(stderr," %u:%08X",i,g_pg.transform_constants[i]);
        fputc('\n',stderr);
        fprintf(stderr,"[DAH-PIXEL-MATERIAL] sub=%u draw=%u shader=%08X control=%08X final=%08X,%08X arrays=",
            g_pg.active_submission,g_pg.indexed_diagnostic_id,g_pg.shader_stage_program,g_pg.combiner_control,g_pg.final_cw0,g_pg.final_cw1);
        for(unsigned i=0;i<16u;++i)fprintf(stderr," %u:%08X,%08X",i,g_pg.array_offset[i],g_pg.array_format[i]);
        fprintf(stderr," combiners=");
        for(unsigned i=0;i<8u;++i)fprintf(stderr," %u:%08X,%08X,%08X,%08X,%08X,%08X",i,
            g_pg.color_icw[i],g_pg.color_ocw[i],g_pg.alpha_icw[i],g_pg.alpha_ocw[i],g_pg.factor0[i],g_pg.factor1[i]);
        fprintf(stderr," textures=");
        for(unsigned i=0;i<4u;++i)fprintf(stderr," %u:%08X,%08X,%08X,%08X,%08X,%08X",i,
            g_pg.tex[i].offset,g_pg.tex[i].format,g_pg.tex[i].control0,g_pg.tex[i].control1,g_pg.tex[i].address,g_pg.tex[i].filter);
        fputc('\n',stderr);
    }
}

static void dah_trace_color_mask_draw(unsigned kind,const OutputVertex *out,HRESULT hr)
{
    static unsigned first=6300u,configured,frame_records,masked_records,capture_requested;
    unsigned in_window;
    if(!dah_color_mask_trace_enabled() || FAILED(hr))return;
    if(!configured){
        const char *value=getenv("DAH_COLOR_MASK_TRACE_FIRST");
        if(value && *value){char *end;unsigned long n=strtoul(value,&end,10);if(!*end && n<0xFFFFFFFFu)first=(unsigned)n;}
        configured=1u;
    }
    in_window=g_pg.active_submission==first || g_pg.active_submission==first+1u;
    if(in_window && !capture_requested){
        capture_requested=1u;
        int queued=dah_request_frame_capture();
        fprintf(stderr,"[DAH-TRACE-CAPTURE] sub=%u draw=%u queued=%d next_present_frames=2\n",
            g_pg.active_submission,g_pg.indexed_diagnostic_id,queued);
    }
    if(in_window){if(frame_records++>=1024u)return;}
    else if(dah_nv2a_color_write_mask(g_pg.color_mask)!=15u){if(masked_records++>=32u)return;}
    else return;
    {
        float xmin=1e30f,ymin=1e30f,xmax=-1e30f,ymax=-1e30f;
        unsigned front=0,black=0;
        for(uint32_t i=0;i<g_pg.index_count;++i){
            const OutputVertex *v=&out[i];
            if(v->x<xmin)xmin=v->x;if(v->x>xmax)xmax=v->x;
            if(v->y<ymin)ymin=v->y;if(v->y>ymax)ymax=v->y;
            if(v->rhw>0)++front;
            if(!(v->color&0x00FFFFFFu))++black;
        }
        fprintf(stderr,"[DAH-COLOR-MASK] sub=%u draw=%u kind=%u n=%u nv=%08X host=%X "
            "target=%08X xy=%.1f,%.1f..%.1f,%.1f front=%u black=%u color0=%08X "
            "depth=%d,%d,%X blend=%d,%X,%X atest=%d,%X,%u "
            "tex0=%08X,%08X tex1=%08X,%08X combiner=%08X final=%08X,%08X\n",
            g_pg.active_submission,g_pg.indexed_diagnostic_id,kind,g_pg.index_count,
            g_pg.color_mask,dah_nv2a_color_write_mask(g_pg.color_mask),g_pg.surface_color_offset,
            xmin,ymin,xmax,ymax,front,black,out[0].color,g_pg.depth_test,g_pg.depth_write,g_pg.depth_func,
            g_pg.blend_enable,g_pg.blend_sfactor,g_pg.blend_dfactor,g_pg.alpha_test,g_pg.alpha_func,g_pg.alpha_ref,
            g_pg.tex[0].offset,g_pg.tex[0].format,g_pg.tex[1].offset,g_pg.tex[1].format,
            g_pg.combiner_control,g_pg.final_cw0,g_pg.final_cw1);
        if(in_window)dah_trace_draw_probes(kind,out);
    }
}

static double dah_profile_ms(void);
static int submit_indexed_3d(void)
{
    IDirect3DDevice8 *dev;
    const float (*c)[4];
    uint32_t first = UINT32_MAX, last = 0;
    const uint8_t *arr[9];
    static const uint32_t attribute_slots[9]={0,1,2,3,4,10,11,12,13};
    unsigned program_kind, attribute_count;
    uint32_t slot_type[9], slot_count[9], slot_stride[9];
    OutputVertex *out;
    IDirect3DTexture8 *tex_obj = NULL;
    IDirect3DTexture8 *pox_textures[4] = {NULL,NULL,NULL,NULL};
    int pox_render_targets[4] = {0,0,0,0};
    HRESULT hr;
    static unsigned log_count;

    /* Must be vertex-program mode and match the captured DAH menu shader. */
    if ((g_pg.transform_mode & 3u) != 2u || g_pg.transform_start > 136u - 36u) return 0;
    program_kind = dah_menu_program_kind(
            g_pg.transform_program + g_pg.transform_start * 4u,
            g_pg.transform_valid  + g_pg.transform_start * 4u);
    if (!program_kind) program_kind = dah_farm_program_kind(g_pg.transform_program + g_pg.transform_start * 4u, g_pg.transform_valid + g_pg.transform_start * 4u);
    if (!program_kind && g_pg.transform_start <= 136u - 38u &&
        dah_rockwell_vehicle_reflection_program_matches(
            g_pg.transform_program + g_pg.transform_start * 4u,
            g_pg.transform_valid + g_pg.transform_start * 4u)) program_kind = 27u;
    if (!program_kind && g_pg.transform_start <= 136u - 15u &&
        dah_rockwell_static_lit_program_matches(
            g_pg.transform_program + g_pg.transform_start * 4u,
            g_pg.transform_valid + g_pg.transform_start * 4u)) program_kind = 28u;
    if (!program_kind && g_pg.transform_start <= 136u - 32u)
        program_kind = dah_static_reflection_program_kind(
            g_pg.transform_program + g_pg.transform_start * 4u,
            g_pg.transform_valid + g_pg.transform_start * 4u);
    if (!program_kind && !dah_skin_disabled() && g_pg.transform_start <= 136u - 57u)
        program_kind = dah_skin_program_kind(g_pg.transform_program + g_pg.transform_start * 4u,
                                             g_pg.transform_valid + g_pg.transform_start * 4u);
    if (!program_kind && !dah_skin_disabled() && g_pg.transform_start <= 136u - 55u)
        program_kind = dah_skin55_program_kind(
            g_pg.transform_program + g_pg.transform_start * 4u,
            g_pg.transform_valid + g_pg.transform_start * 4u);
    if (!program_kind && !dah_skin_disabled() && g_pg.transform_start <= 136u - 62u)
        program_kind = dah_skin62_program_kind(
            g_pg.transform_program + g_pg.transform_start * 4u,
            g_pg.transform_valid + g_pg.transform_start * 4u);
    if (!program_kind && !dah_skin_disabled() && g_pg.transform_start <= 136u - 62u)
        program_kind = dah_pox_skin_program_kind(
            g_pg.transform_program + g_pg.transform_start * 4u,
            g_pg.transform_valid + g_pg.transform_start * 4u);
    if (!program_kind && !dah_skin_disabled() && g_pg.transform_start <= 136u - 62u)
        program_kind = dah_pox_morph_program_kind(
            g_pg.transform_program + g_pg.transform_start * 4u,
            g_pg.transform_valid + g_pg.transform_start * 4u);
    if (!program_kind && !dah_skin_disabled() && g_pg.transform_start <= 136u - 60u)
        program_kind = dah_skin60_program_kind(
            g_pg.transform_program + g_pg.transform_start * 4u,
            g_pg.transform_valid + g_pg.transform_start * 4u);
    if (!program_kind && g_pg.transform_start <= 136u - 24u)
        program_kind = dah_pox_static_program_kind(
            g_pg.transform_program + g_pg.transform_start * 4u,
            g_pg.transform_valid + g_pg.transform_start * 4u);
    if (!program_kind && g_pg.transform_start <= 136u - 9u) program_kind = dah_unlit9_program_kind(
            g_pg.transform_program + g_pg.transform_start * 4u,
            g_pg.transform_valid + g_pg.transform_start * 4u);
    if (!program_kind && g_pg.transform_start <= 136u - 21u) program_kind = dah_pox_program_kind(
            g_pg.transform_program + g_pg.transform_start * 4u,
            g_pg.transform_valid + g_pg.transform_start * 4u);
    if (!program_kind && g_pg.transform_start <= 136u - 16u) program_kind = dah_pox_ui_program_kind(
            g_pg.transform_program + g_pg.transform_start * 4u,
            g_pg.transform_valid + g_pg.transform_start * 4u);
    if (!program_kind) program_kind = dah_farm_deform_program_kind(
            g_pg.transform_program + g_pg.transform_start * 4u,
            g_pg.transform_valid + g_pg.transform_start * 4u);
    if (dah_ui_animation_trace_enabled() &&
        g_pg.active_submission >= dah_ui_animation_trace_start() &&
        g_pg.index_count == 5u && g_pg.transform_start <= 126u &&
        g_pg.array_format[0] == 0x1832u &&
        g_pg.array_format[1] == 0x1822u &&
        g_pg.array_format[2] == 0x1840u &&
        g_pg.tex[0].enabled && g_pg.tex[0].format == 0x07710F29u &&
        g_pg.tex[0].image_rect == 0x028001E0u &&
        g_pg.transform_valid[g_pg.transform_start * 4u + 1u] &&
        g_pg.transform_program[g_pg.transform_start * 4u + 1u] == 0x00C4801Bu) {
        static unsigned projector_kind_reports;
        if (projector_kind_reports++ < 8u) {
            uint32_t base = g_pg.transform_start * 4u;
            fprintf(stderr,"[DAH-PROJECTOR-KIND] sub=%u draw=%u kind=%u program=",
                g_pg.active_submission,g_pg.indexed_diagnostic_id,program_kind);
            for (unsigned i=0;i<40u;++i)
                fprintf(stderr,"%s%08X",i?",":"",g_pg.transform_program[base+i]);
            fputc('\n',stderr);fflush(stderr);
        }
    }
    /* The malformed Farm projector/bloom draw is a five-index strip using
     * the exact static Farm program.  Keep this probe independent of
     * submission numbering: tracing changes host pacing enough to move the
     * draw between pushbuffer submissions. */
    if (dah_ui_animation_trace_enabled() && g_pg.index_count == 5u &&
        !g_pg.tex[0].enabled && g_pg.active_submission >= 5000u) {
        static unsigned bloom_clear_reports;
        if (bloom_clear_reports++ < 64u) {
            uint32_t base = g_pg.transform_start * 4u;
            fprintf(stderr,
                "[DAH-BLOOM-CLEAR-CANDIDATE] sub=%u draw=%u kind=%u target=%08X "
                "clip=%08X,%08X idx=%u,%u,%u,%u,%u arrays=%08X,%08X,%08X "
                "off=%08X,%08X,%08X tex=%u:%08X:%08X,%u:%08X:%08X "
                "mask=%08X stage=%08X combiner=%08X program=",
                g_pg.active_submission,g_pg.indexed_diagnostic_id,program_kind,
                g_pg.surface_color_offset,g_pg.surface_clip_h,g_pg.surface_clip_v,
                g_pg.indices[0],g_pg.indices[1],g_pg.indices[2],g_pg.indices[3],g_pg.indices[4],
                g_pg.array_format[0],g_pg.array_format[1],g_pg.array_format[2],
                g_pg.array_offset[0],g_pg.array_offset[1],g_pg.array_offset[2],
                g_pg.tex[0].enabled,g_pg.tex[0].format,g_pg.tex[0].image_rect,
                g_pg.tex[1].enabled,g_pg.tex[1].format,g_pg.tex[1].image_rect,
                g_pg.color_mask,g_pg.shader_stage_program,g_pg.combiner_control);
            for (unsigned i=0;i<40u;++i)
                fprintf(stderr,"%s%08X",i?",":"",g_pg.transform_program[base+i]);
            fputc('\n',stderr);fflush(stderr);
        }
    }
    attribute_count = (program_kind == 16u || program_kind == 20u || program_kind == 25u) ? 9u :
        (program_kind == 13u || program_kind == 15u || program_kind == 19u) ? 5u :
        (program_kind == 12u || program_kind == 22u || program_kind == 29u || program_kind == 2u || program_kind == 3u) ? 4u :
        (program_kind == 11u || program_kind == 23u || program_kind == 24u) ? 2u : 3u;
    if (!program_kind) {
        if (dah_ui_animation_trace_enabled() &&
            g_pg.active_submission >= dah_ui_animation_trace_start()) {
            static uint32_t seen_hashes[64];
            static unsigned seen_count;
            uint32_t hash = 2166136261u, words = 0u;
            uint32_t base_word = g_pg.transform_start * 4u;
            for (unsigned instruction = 0; instruction < 62u && base_word + words + 3u < 136u * 4u; ++instruction) {
                int complete = 1;
                for (unsigned part = 0; part < 4u; ++part) {
                    uint32_t at = base_word + words + part;
                    uint32_t value = g_pg.transform_valid[at] ? g_pg.transform_program[at] : 0xDEADBEEFu;
                    hash = (hash ^ value) * 16777619u;
                    if (!g_pg.transform_valid[at]) complete = 0;
                }
                words += 4u;
                if (!complete || (g_pg.transform_program[base_word + words - 1u] & 1u)) break;
            }
            int seen = 0;
            for (unsigned i = 0; i < seen_count; ++i) if (seen_hashes[i] == hash) { seen = 1; break; }
            if (!seen && seen_count < 64u) {
                seen_hashes[seen_count++] = hash;
                fprintf(stderr, "[DAH-UI-PROGRAM] submit=%u hash=%08X words=%u texture=%08X format=%08X indices=%u arrays=",
                        g_pg.active_submission, hash, words, g_pg.tex[0].offset, g_pg.tex[0].format, g_pg.index_count);
                for (unsigned slot = 0; slot < 16u; ++slot)
                    if ((g_pg.array_format[slot] >> 4u) & 15u)
                        fprintf(stderr, "%u:%08X:%08X,", slot, g_pg.array_offset[slot], g_pg.array_format[slot]);
                fprintf(stderr, "\n[DAH-UI-PROGRAM-WORDS] hash=%08X", hash);
                for (unsigned i = 0; i < words; ++i) fprintf(stderr, " %08X", g_pg.transform_program[base_word + i]);
                fprintf(stderr, "\n"); fflush(stderr);
            }
        }
        /* Log unique other vertex programs so we know what we're missing. */
        static uint32_t last_prog0 = 0, other_count = 0;
        uint32_t base = g_pg.transform_start * 4u;
        uint32_t w0 = g_pg.transform_program[base + 1];
        if (w0 != last_prog0 && other_count++ < 64u) {
            last_prog0 = w0;
            fprintf(stderr,
                "[DAH-3D-OTHER] draw=%u mode=%u prog_start=%u"
                " words[1]=%08X words[5]=%08X vcount=%u surface=%08X\n",
                g_pg.indexed_diagnostic_id, g_pg.transform_mode,
                g_pg.transform_start,
                g_pg.transform_program[base + 1],
                g_pg.transform_program[base + 5],
                g_pg.index_count, g_pg.surface_color_offset);
            /* Full program dump when first word matches our fingerprint — helps
             * identify which instruction words differ from dah_menu_program. */
            if (w0 == 0x00A5C21Au) {
                uint32_t first_bad = UINT32_MAX;
                for (unsigned k = 0; k < 68u; ++k) {
                    uint32_t exp = dah_menu_program[k / 4u][k % 4u];
                    int valid = g_pg.transform_valid[base + k];
                    uint32_t got = valid ? g_pg.transform_program[base + k] : 0xDEADBEEFu;
                    if (first_bad == UINT32_MAX && (!valid || got != exp))
                        first_bad = k;
                    fprintf(stderr, "[DAH-3D-PROG] k=%02u got=%08X exp=%08X valid=%d%s\n",
                            k, got, exp, valid, got != exp || !valid ? " DIFF" : "");
                }
                fprintf(stderr, "[DAH-3D-PROG-SUMMARY] first_bad=%u draw=%u\n",
                        first_bad, g_pg.indexed_diagnostic_id);
                fflush(stderr);
            }
        }

        if(dah_crypto_head_trace_enabled() &&
           (g_pg.active_submission==6300u || g_pg.active_submission==6500u)){
            static unsigned crypto_unknown_count;
            if(crypto_unknown_count++<512u)
                fprintf(stderr,
                    "[DAH-CRYPTO-OTHER] sub=%u draw=%u n=%u start=%u "
                    "sig=%08X,%08X array0=%08X,%08X array1=%08X,%08X "
                    "tex0=%08X,%08X target=%08X cull=%d,%X,%X\n",
                    g_pg.active_submission,g_pg.indexed_diagnostic_id,
                    g_pg.index_count,g_pg.transform_start,w0,
                    g_pg.transform_program[base+5u],
                    g_pg.array_offset[0],g_pg.array_format[0],
                    g_pg.array_offset[1],g_pg.array_format[1],
                    g_pg.tex[0].offset,g_pg.tex[0].format,
                    g_pg.surface_color_offset,
                    g_pg.cull_enable,g_pg.front_face,g_pg.cull_face);
        }

        dah_farm_unknown_program_dump();
        dah_farm_material_trace("shader", 0u, NULL, 0u, UINT32_MAX, 0);
        return 0;
    }

    dev = xbox_GetD3DDevice();
    /* Retail Farm deformation uses both TRIANGLES and TRIANGLE_STRIP. The
     * expanded vertex buffer is already in guest index order, so either
     * topology can be submitted directly without rebuilding indices. */
    if (!dev || (g_pg.draw_mode != 5u && g_pg.draw_mode != 6u) ||
        (g_pg.draw_mode == 5u && (g_pg.index_count % 3u) != 0u) || g_pg.index_count < 3u ||
        g_pg.index_overflow || g_pg.inline_count) {
        dah_farm_material_trace("draw-state", program_kind, NULL, 0u, UINT32_MAX, 0);
        return 0;
    }

    /* Verify the critical transform constants are loaded (MVP + viewport + UV).
     * Lighting constants c[46..48] may legitimately be zero when the game uses
     * a flat-ambient model; we accept them as zero rather than requiring valid. */
    c = (const float (*)[4])g_pg.transform_constants;
    {
        static const uint8_t critical[] = {1, 2, 36, 37, 38, 39, 78, 79};
        static const uint8_t reflection[] = {1,2,16,17,28,29,30,32,33,34,36,37,38,39,48,56,76,77,78,79,187};
        static const uint8_t skin[] = {1,2,19,20,24,25,36,37,38,39,46,47,48,56,76,77,78,79,187,190,191};
        static const uint8_t skin55[] = {1,2,19,20,36,37,38,39,46,47,48,56,76,77,78,79,187,191};
        static const uint8_t morph62[] = {1,2,19,20,24,25,36,37,38,39,46,47,48,56,76,77,78,79,85,187,190,191};
        static const uint8_t pox_skin[] = {1,2,19,20,24,25,36,37,38,39,47,48,49,50,51,56,64,65,66,76,77,78,79,187,189,190,191};
        static const uint8_t pox_morph[] = {1,2,19,20,24,25,36,37,38,39,47,48,49,50,51,56,64,65,66,76,77,78,79,85,187,189,190,191};
        static const uint8_t pox_static[] = {1,2,19,20,36,37,38,39,47,48,49,50,51,56,64,65,66,76,77,78,79,187,189};
        static const uint8_t rockwell_vehicle[] = {1,2,19,20,24,25,36,37,38,39,47,48,49,50,51,56,64,65,66,76,77,78,79,187,189,190};
        static const uint8_t rockwell_vehicle_reflection[] = {1,2,19,20,28,29,30,32,33,34,36,37,38,39,47,48,49,50,51,56,64,65,66,76,77,78,79,187,189};
        static const uint8_t rockwell_static_lit[] = {1,2,3,4,32,33,34,36,37,38,39,56,77,190};
        static const uint8_t static_reflection[] = {1,2,19,20,28,29,30,32,33,34,36,37,38,39,46,47,48,56,76,77,78,79,187};
        static const uint8_t unlit9[] = {1,2,36,37,38,39};
        static const uint8_t pox[] = {1,2,36,37,38,39,126,127,187,190};
        static const uint8_t pox_ui[] = {1,2,36,37,38,39,56,78,79};
        static const uint8_t farm_deform[] = {1,2,36,37,38,39,46,187,189,191};
        static const uint8_t farm_push[] = {1,2,36,37,38,39,46,187,189};
        static const uint8_t farm_constant[] = {1,2,36,37,38,39,187};
        const uint8_t *required = (program_kind == 29u || program_kind == 30u) ? static_reflection :
            program_kind == 14u ? unlit9 :
            program_kind == 28u ? rockwell_static_lit :
            program_kind == 27u ? rockwell_vehicle_reflection :
            program_kind == 26u ? rockwell_vehicle :
            program_kind == 17u ? pox :
            program_kind == 18u ? pox_ui :
            program_kind == 21u ? pox_static :
            program_kind == 20u ? pox_morph : program_kind == 19u ? pox_skin :
            program_kind == 22u ? farm_deform : program_kind == 23u ? farm_push :
            program_kind == 24u ? farm_constant :
            program_kind == 25u ? morph62 :
            program_kind == 16u ? morph62 : program_kind == 15u ? skin55 :
            program_kind == 13u ? skin : program_kind == 12u ? reflection : critical;
        unsigned required_count = (program_kind == 29u || program_kind == 30u) ? sizeof(static_reflection) :
            program_kind == 14u ? sizeof(unlit9) :
            program_kind == 28u ? sizeof(rockwell_static_lit) :
            program_kind == 27u ? sizeof(rockwell_vehicle_reflection) :
            program_kind == 26u ? sizeof(rockwell_vehicle) :
            program_kind == 17u ? sizeof(pox) :
            program_kind == 18u ? sizeof(pox_ui) :
            program_kind == 21u ? sizeof(pox_static) :
            program_kind == 20u ? sizeof(pox_morph) : program_kind == 19u ? sizeof(pox_skin) :
            program_kind == 22u ? sizeof(farm_deform) : program_kind == 23u ? sizeof(farm_push) :
            program_kind == 24u ? sizeof(farm_constant) :
            program_kind == 25u ? sizeof(morph62) :
            program_kind == 16u ? sizeof(morph62) : program_kind == 15u ? sizeof(skin55) :
            program_kind == 13u ? sizeof(skin) :
            program_kind == 12u ? sizeof(reflection) : (program_kind == 11u ? 6u : 8u);
        int ok = 1;
        for (unsigned i = 0; ok && i < required_count; ++i)
            for (unsigned j = 0; j < 4u; ++j)
                if (!g_pg.transform_constant_valid[required[i] * 4u + j] ||
                    !isfinite(c[required[i]][j])) { ok = 0; break; }
        if (program_kind == 14u &&
            (!g_pg.transform_constant_valid[187u * 4u] || !isfinite(c[187][0]))) ok = 0;
        if (!ok) {
            if (log_count++ < 4u)
                fprintf(stderr, "[DAH-3D-SKIP] critical constants not ready draw=%u\n",
                        g_pg.indexed_diagnostic_id);
            dah_farm_material_trace("constants", program_kind, NULL, 0u, UINT32_MAX, 0);
            return 0;
        }
    }

    /* Use the uploaded retail constants unchanged, including intentional zero
     * translations for camera-centered passes. */

    if(program_kind==17u && dah_ui_animation_trace_enabled()){
        static uint32_t last_pox_hash;
        static unsigned pox_reports;
        uint32_t hash=2166136261u;
        for(unsigned ci=96u;ci<=127u;++ci)for(unsigned component=0;component<4u;++component){
            uint32_t bits;memcpy(&bits,&c[ci][component],sizeof bits);hash=(hash^bits)*16777619u;
        }
        if(pox_reports<64u && (!pox_reports || hash!=last_pox_hash)){
            fprintf(stderr,"[DAH-POX-STATE] submit=%u hash=%08X c126=%g,%g c127=%g,%g stages=",
                g_pg.active_submission,hash,c[126][0],c[126][1],c[127][0],c[127][1]);
            for(unsigned stage=0;stage<4u;++stage)fprintf(stderr,"%s%u:%d:%08X:%08X:%08X",
                stage?",":"",stage,g_pg.tex[stage].enabled,g_pg.tex[stage].offset,
                g_pg.tex[stage].format,g_pg.tex[stage].image_rect);
            fprintf(stderr," shader=%08X combiner=%08X final=%08X,%08X\n",
                g_pg.shader_stage_program,g_pg.combiner_control,g_pg.final_cw0,g_pg.final_cw1);
            fflush(stderr);++pox_reports;last_pox_hash=hash;
        }
    }

    /* Log the first MVP and then unique c[39] values to track camera passes. */
    if (log_count < 16u) {
        static float last_c39[4] = {0,0,0,0};
        static int logged_first_mvp;
        if (!logged_first_mvp || c[39][0] != last_c39[0] ||
            c[39][2] != last_c39[2] || c[39][3] != last_c39[3]) {
            logged_first_mvp = 1;
            memcpy(last_c39, c[39], sizeof(last_c39));
            fprintf(stderr,
                "[DAH-3D-MVP] draw=%u c36=(%.4f,%.4f,%.4f,%.4f)"
                " c37=(%.4f,%.4f,%.4f,%.4f) c38=(%.4f,%.4f,%.4f,%.4f)"
                " c39=(%.4f,%.4f,%.4f,%.4f) c1=(%.3g,%.3g,%.3g,%.3g)"
                " c2=(%.3g,%.3g,%.3g,%.3g)\n",
                g_pg.indexed_diagnostic_id,
                c[36][0],c[36][1],c[36][2],c[36][3],
                c[37][0],c[37][1],c[37][2],c[37][3],
                c[38][0],c[38][1],c[38][2],c[38][3],
                c[39][0],c[39][1],c[39][2],c[39][3],
                c[1][0],c[1][1],c[1][2],c[1][3],
                c[2][0],c[2][1],c[2][2],c[2][3]);
        }
    }
    if (log_count == 0u && program_kind < 10u) {
        fprintf(stderr, "[DAH-3D-STATE] subchannel=%u stage_program=%08X combiner=%08X final=%08X,%08X surface=%08X pitch=%08X color=%08X zeta=%08X\n",
                g_pg.draw_subchannel,
                g_pg.shader_stage_program, g_pg.combiner_control,
                g_pg.final_cw0, g_pg.final_cw1, g_pg.surface_format,
                g_pg.surface_pitch, g_pg.surface_color_offset,
                g_pg.surface_zeta_offset);
        for (unsigned stage = 0; stage < 4u; ++stage)
            fprintf(stderr, "[DAH-3D-TEX] stage=%u enabled=%d offset=%08X format=%08X control=%08X,%08X rect=%08X address=%08X filter=%08X\n",
                    stage, g_pg.tex[stage].enabled, g_pg.tex[stage].offset,
                    g_pg.tex[stage].format, g_pg.tex[stage].control0,
                    g_pg.tex[stage].control1, g_pg.tex[stage].image_rect,
                    g_pg.tex[stage].address, g_pg.tex[stage].filter);
        for (unsigned stage = 0; stage < 4u; ++stage)
            fprintf(stderr, "[DAH-3D-COMBINER] stage=%u color=%08X,%08X alpha=%08X,%08X\n",
                    stage, g_pg.color_icw[stage], g_pg.color_ocw[stage],
                    g_pg.alpha_icw[stage], g_pg.alpha_ocw[stage]);
    }


    if(program_kind==16u && dah_crypto_head_trace_enabled() &&
       (g_pg.active_submission==6300u || g_pg.active_submission==6500u)){
        static unsigned morph_trace_count;
        if(morph_trace_count++<16u){
            fprintf(stderr,"[DAH-CRYPTO-MORPH] sub=%u draw=%u n=%u exact=248 c85=%.6g,%.6g,%.6g,%.6g\n",
                g_pg.active_submission,g_pg.indexed_diagnostic_id,g_pg.index_count,
                c[85][0],c[85][1],c[85][2],c[85][3]);
            for(unsigned ai=0;ai<9u;++ai){
                unsigned s=attribute_slots[ai];
                fprintf(stderr,"[DAH-CRYPTO-MORPH-ARRAY] sub=%u draw=%u slot=%u offset=%08X format=%08X\n",
                    g_pg.active_submission,g_pg.indexed_diagnostic_id,s,
                    g_pg.array_offset[s],g_pg.array_format[s]);
            }
        }
    }
    /* Decode the arrays used by this exact vertex program. */
    for (unsigned s = 0; s < attribute_count; ++s) {
        slot_type[s]   = g_pg.array_format[attribute_slots[s]] & 0xFu;
        slot_count[s]  = (g_pg.array_format[attribute_slots[s]] >> 4u) & 0xFu;
        slot_stride[s] = g_pg.array_format[attribute_slots[s]] >> 8u;
    }
    if (program_kind < 10u) {
    /* Slot 0: position – need ≥3 float components. */
    if (slot_type[0] != 2u || slot_count[0] < 3u || slot_stride[0] < 12u) { dah_farm_material_trace("slot0", program_kind, NULL, 0u, UINT32_MAX, 0); return 0; }
    /* Slot 1: normal – need ≥3 components (S1 or float). */
    if (slot_count[1] < 3u || slot_stride[1] == 0u) { dah_farm_material_trace("slot1", program_kind, NULL, 0u, UINT32_MAX, 0); return 0; }
    /* Slot 2: texcoord – need ≥2 float components. */
    if (slot_type[2] != 2u || slot_count[2] < 2u || slot_stride[2] < 8u) { dah_farm_material_trace("slot2", program_kind, NULL, 0u, UINT32_MAX, 0); return 0; }

    if ((program_kind == 2u || program_kind == 3u) && (slot_count[3] < 3u || slot_count[3] > 4u ||
        slot_stride[3] == 0u || (slot_type[3] > 2u && slot_type[3] != 4u) ||
        (slot_type[3] == 0u && slot_count[3] != 4u))) { dah_farm_material_trace("slot3", program_kind, NULL, 0u, UINT32_MAX, 0); return 0; }

    } else {
        for (unsigned slot=0;slot<attribute_count;slot++) {
            unsigned type=slot_type[slot],count=slot_count[slot];
            unsigned bytes=type==2u?4u:type==1u?2u:1u;
            if(type!=0u&&type!=1u&&type!=2u&&type!=4u){dah_farm_material_trace("slot-type",program_kind,NULL,0u,slot,0);return 0;}
            if(!count||count>4u||slot_stride[slot]<count*bytes||(type==0u&&count!=4u)){dah_farm_material_trace("slot-size",program_kind,NULL,0u,slot,0);return 0;}
        }
        if(slot_type[0]!=2u||slot_count[0]<3u||slot_count[1]<(program_kind==11u?3u:2u)){dah_farm_material_trace("slot-farm",program_kind,NULL,0u,UINT32_MAX,0);return 0;}
        if((program_kind==26u||program_kind==27u||program_kind==28u)&&(slot_type[1]!=1u||slot_count[1]!=3u||slot_type[2]!=2u||slot_count[2]!=2u)){
            dah_farm_material_trace("slot-rockwell-vehicle",program_kind,NULL,0u,UINT32_MAX,0);return 0;
        }
        if(program_kind==22u&&(slot_type[1]!=2u||slot_count[1]<3u||slot_type[2]!=2u||slot_count[2]<3u||slot_count[3]<3u)){
            dah_farm_material_trace("slot-deform",program_kind,NULL,0u,UINT32_MAX,0);return 0;
        }
        if(program_kind==12u&&(slot_count[2]!=4u||slot_count[3]<3u)){dah_farm_material_trace("slot-reflect",program_kind,NULL,0u,UINT32_MAX,0);return 0;}
        if(program_kind==29u&&(slot_type[1]!=1u||slot_count[1]!=3u||slot_type[2]!=2u||slot_count[2]!=2u||slot_count[3]<3u)){
            dah_farm_material_trace("slot-static-reflect",program_kind,NULL,0u,UINT32_MAX,0);return 0;
        }
        if(program_kind==30u&&(slot_type[1]!=1u||slot_count[1]!=3u||slot_type[2]!=2u||slot_count[2]!=2u)){
            dah_farm_material_trace("slot-saucer-reflect",program_kind,NULL,0u,UINT32_MAX,0);return 0;
        }
        if(program_kind==14u){
            static const uint32_t unlit_formats[3]={0x1832u,0x1822u,0x1840u};
            static const uint32_t unlit_offsets[3]={0u,12u,20u};
            uint32_t base=g_pg.array_offset[0];
            if(base>UINT32_MAX-20u){dah_farm_material_trace("unlit-layout",program_kind,NULL,0u,UINT32_MAX,0);return 0;}
            for(unsigned s=0;s<3u;s++)if(g_pg.array_format[s]!=unlit_formats[s]||
                g_pg.array_offset[s]!=base+unlit_offsets[s]){
                dah_farm_material_trace("unlit-layout",program_kind,NULL,0u,s,0);return 0;
            }
        }
        if(program_kind==13u||program_kind==15u||program_kind==16u||program_kind==19u||program_kind==20u||program_kind==25u){
            static const uint32_t skin_formats[5]={0x2832u,0x2832u,0x2840u,0x2840u,0x2822u};
            static const uint32_t skin_offsets[5]={0u,12u,24u,28u,32u};
            uint32_t base=g_pg.array_offset[0];
            if(base>UINT32_MAX-32u){dah_farm_material_trace("skin-layout",program_kind,NULL,0u,UINT32_MAX,0);return 0;}
            for(unsigned s=0;s<5u;s++)if(g_pg.array_format[s]!=skin_formats[s]||
                g_pg.array_offset[s]!=base+skin_offsets[s]){
                dah_farm_material_trace("skin-layout",program_kind,NULL,0u,s,0);return 0;
            }
        }
    }
    if(program_kind==16u||program_kind==20u||program_kind==25u)
        for(unsigned ai=5u;ai<9u;++ai)
            if(slot_count[ai]<3u){dah_farm_material_trace("morph-layout",program_kind,NULL,0u,attribute_slots[ai],0);return 0;}
    static unsigned dah_fine_draw_logs;
    int dah_fine_draw = dah_farm_fine_profile_enabled() &&
        dah_method_profile_sample(g_pg.active_submission) &&
        (g_pg.indexed_diagnostic_id % 17u) == 0u && dah_fine_draw_logs < 512u;
    int dah_runtime_profile = dah_runtime_profile_enabled();
    int dah_draw_timing = dah_runtime_profile || dah_fine_draw;
    double setup_start = dah_draw_timing ? dah_profile_ms() : 0.0;
    unsigned dah_fine_vertex_cache_hits = 0u;
    /* Index range. */
    for (uint32_t i = 0; i < g_pg.index_count; ++i) {
        if (g_pg.indices[i] < first) first = g_pg.indices[i];
        if (g_pg.indices[i] > last)  last  = g_pg.indices[i];
    }

    /* Fetch vertex arrays – 3D static mesh data lives in low XBE/heap RAM,
     * not in the contiguous D3D-locked window. Try contiguous first; fall
     * back to low window. Log once per log_count budget for diagnostics. */
    {
        for (unsigned s = 0; s < attribute_count; ++s) {
            uint32_t bpc = slot_type[s] == 1u ? 2u :
                           (slot_type[s] == 0u || slot_type[s] == 4u) ? 1u : 4u;
            uint64_t begin  = (uint64_t)g_pg.array_offset[attribute_slots[s]]
                            + (uint64_t)first * slot_stride[s];
            uint64_t length = (uint64_t)(last - first) * slot_stride[s]
                            + (uint64_t)slot_count[s] * bpc;
            if (begin > UINT32_MAX || length > XBOX_CONTIG_SIZE) { dah_farm_material_trace("array-range", program_kind, NULL, 0u, s, 0); return 0; }

            /* Static 3D meshes live in low XBE/heap RAM. The exact unlit
             * program uses E9250's locked 24-byte vertex buffer: E8FF0 calls
             * 1DD6C0, which returns Data | 0x80000000. Its shader signature
             * and declaration were checked above. Like the Pox CRT buffers,
             * this data belongs to the separate contiguous graphics window. */
            /* The reflection program is also used by Farm's generated
             * landscape grid.  ECD20 fills that vertex buffer through the
             * D3D locked/contiguous window; the same guest offset in low RAM
             * is an all-zero mirror and collapses the whole grid to one
             * off-screen point after entering the saucer. */
            int contiguous = program_kind == 12u || program_kind == 14u ||
                             program_kind == 17u || program_kind == 18u;
            arr[s] = indexed_guest_bytes_window((uint32_t)begin, (size_t)length, contiguous);
            if (!arr[s]) { dah_farm_material_trace("array-read", program_kind, NULL, 0u, s, 0); return 0; }

            if (log_count < 8u) {
                /* Inspect first 12 bytes in each window to diagnose zero-data. */
                const uint8_t *c0 = indexed_guest_bytes_window((uint32_t)begin, length < 12u ? (size_t)length : 12u, 0);
                const uint8_t *c1 = indexed_guest_bytes_window((uint32_t)begin, length < 12u ? (size_t)length : 12u, 1);
                uint32_t r0[3] = {0,0,0}, r1[3] = {0,0,0};
                if (c0 && length >= 12u) { memcpy(&r0[0],c0,4); memcpy(&r0[1],c0+4,4); memcpy(&r0[2],c0+8,4); }
                if (c1 && length >= 12u) { memcpy(&r1[0],c1,4); memcpy(&r1[1],c1+4,4); memcpy(&r1[2],c1+8,4); }
                fprintf(stderr,
                    "[DAH-3D-ARRAYS] draw=%u slot=%u off=%08X stride=%u cnt=%u"
                    " first=%u last=%u begin=%08X len=%u\n"
                    "  low =%s %08X %08X %08X\n"
                    "  cont=%s %08X %08X %08X\n",
                    g_pg.indexed_diagnostic_id, s, g_pg.array_offset[s],
                    slot_stride[s], slot_count[s], first, last,
                    (uint32_t)begin, (uint32_t)length,
                    c0 ? "ok" : "NG", r0[0], r0[1], r0[2],
                    c1 ? "ok" : "NG", r1[0], r1[1], r1[2]);
            }
        }
    }

    /* Preserve the full expanded strip but transform repeated source
     * indices once per draw. No array or constant can change while this
     * synchronous submit_indexed_3d call is expanding its own strip. */
    uint64_t vertex_span = (uint64_t)last - first + 1u;
    uint32_t cache_span = log_count >= 4u && g_pg.index_count >= 64u &&
        vertex_span <= 4096u && g_pg.index_count > vertex_span + 16u ?
        (uint32_t)vertex_span : 0u;
    size_t output_bytes = (size_t)g_pg.index_count * sizeof(*out);
    size_t cache_bytes = (size_t)cache_span * (sizeof(*out) + 1u);
    out = (OutputVertex *)malloc(output_bytes + cache_bytes);
    if (!out) { dah_farm_material_trace("alloc", program_kind, NULL, 0u, UINT32_MAX, 0); return 0; }
    OutputVertex *vertex_cache = cache_span ? out + g_pg.index_count : NULL;
    uint8_t *vertex_seen = cache_span ? (uint8_t *)(vertex_cache + cache_span) : NULL;
    if (vertex_seen) memset(vertex_seen, 0, cache_span);

    /* Scan all unique vertices once to find range of clip.w and screen.y.
     * Logged only for the first qualifying draw, budget 1 report. */
    if (log_count == 0u && program_kind < 10u) {
        uint32_t n_front = 0, n_onscreen = 0;
        float min_clipw = 1e38f, max_clipw = -1e38f;
        for (uint32_t v = 0; v <= last - first; ++v) {
            float p[4]={0,0,0,1}, n2[4]={0,0,1,0}, t[4]={0};
            DahMenuVertex rv;
            fetch_attr_float4(arr[0], slot_stride[0], v, slot_type[0], slot_count[0], p);
            if (slot_count[0] < 4u) p[3] = 1.0f;
            fetch_attr_float4(arr[1], slot_stride[1], v, slot_type[1], slot_count[1], n2);
            fetch_attr_float4(arr[2], slot_stride[2], v, slot_type[2], slot_count[2], t);
            if (!dah_menu_vertex(p, n2, t, c, &rv)) continue;
            float cw = rv.screen[3];
            if (cw < min_clipw) min_clipw = cw;
            if (cw > max_clipw) max_clipw = cw;
            if (cw > 0.0f) n_front++;
            if (rv.screen[1] >= 0.f && rv.screen[1] <= 480.f &&
                rv.screen[0] >= 0.f && rv.screen[0] <= 640.f) n_onscreen++;
        }
        fprintf(stderr,
            "[DAH-3D-SCAN] draw=%u verts=%u front=%u onscreen=%u"
            " clipw=[%.2e,%.2e]\n",
            g_pg.indexed_diagnostic_id, last-first+1, n_front, n_onscreen,
            min_clipw, max_clipw);
        /* Also log first 6 unique vertex positions and their clip.w. */
        for (uint32_t v = 0; v < 6u && v <= last-first; ++v) {
            float p[4]={0,0,0,1}, n2[4]={0,0,1,0}, t[4]={0};
            DahMenuVertex rv;
            fetch_attr_float4(arr[0], slot_stride[0], v, slot_type[0], slot_count[0], p);
            if (slot_count[0] < 4u) p[3] = 1.0f;
            fetch_attr_float4(arr[1], slot_stride[1], v, slot_type[1], slot_count[1], n2);
            fetch_attr_float4(arr[2], slot_stride[2], v, slot_type[2], slot_count[2], t);
            if (dah_menu_vertex(p, n2, t, c, &rv))
                fprintf(stderr,
                    "[DAH-3D-SCAN-V%u] pos=(%.3f,%.3f,%.3f) clipw=%.3e"
                    " sx=%.1f sy=%.1f\n",
                    v, p[0], p[1], p[2], rv.screen[3],
                    rv.screen[0], rv.screen[1]);
        }
    }

    double vertices_start=dah_draw_timing ? dah_profile_ms() : 0.0;
    double dah_vertex_attr_ms=0.0, dah_vertex_shader_ms=0.0;
    double dah_vertex_pack_ms=0.0, dah_vertex_hit_ms=0.0;
    /* Transform each indexed vertex through the captured shader function. */
    for (uint32_t i = 0; i < g_pg.index_count; ++i) {
        double dah_vertex_stage_start=dah_fine_draw ? dah_profile_ms() : 0.0;
        uint32_t rel = g_pg.indices[i] - first;
        if (vertex_seen && vertex_seen[rel]) {
            if (dah_fine_draw) ++dah_fine_vertex_cache_hits;
            out[i] = vertex_cache[rel];
            if(dah_fine_draw)dah_vertex_hit_ms+=dah_profile_ms()-dah_vertex_stage_start;
            continue;
        }
        float pos[4]    = {0, 0, 0, 1.0f};
        float normal[4] = {0, 0, 1.0f, 0};
        float tex[4]    = {0, 0, 0, 0};
        DahMenuVertex result;

        fetch_attr_float4(arr[0], slot_stride[0], rel, slot_type[0], slot_count[0], pos);
        if (slot_count[0] < 4u) pos[3] = 1.0f;

        fetch_attr_float4(arr[1], slot_stride[1], rel, slot_type[1], slot_count[1], normal);

        if (attribute_count > 2u) fetch_attr_float4(arr[2], slot_stride[2], rel, slot_type[2], slot_count[2], tex);

        float extra[4] = {0};
        if (program_kind == 2u || program_kind == 3u || program_kind == 12u || program_kind == 22u || program_kind == 29u ||
            program_kind == 13u || program_kind == 15u || program_kind == 16u ||
            program_kind == 19u || program_kind == 20u || program_kind == 25u)
            fetch_attr_float4(arr[3], slot_stride[3], rel, slot_type[3], slot_count[3], extra);
        int vertex_ok;
        float reflection_uv[4]={0};
        if(dah_fine_draw){double t=dah_profile_ms();dah_vertex_attr_ms+=t-dah_vertex_stage_start;dah_vertex_stage_start=t;}
        if(program_kind==13u||program_kind==15u||program_kind==16u||program_kind==19u||program_kind==20u||program_kind==25u){
            float uv4[4]={0,0,0,1}, inputs[9][4];
            fetch_attr_float4(arr[4], slot_stride[4], rel, slot_type[4], slot_count[4], uv4);
            if(dah_fine_draw){double t=dah_profile_ms();dah_vertex_attr_ms+=t-dah_vertex_stage_start;dah_vertex_stage_start=t;}
            uv4[3]=1.0f; /* NV2A fills absent fourth attribute component. */
            memcpy(inputs[0],pos,sizeof pos);memcpy(inputs[1],normal,sizeof normal);
            memcpy(inputs[2],tex,sizeof tex);memcpy(inputs[3],extra,sizeof extra);
            memcpy(inputs[4],uv4,sizeof uv4);
            if(program_kind==16u||program_kind==20u||program_kind==25u)
                for(unsigned ai=5;ai<9u;++ai)
                    fetch_attr_float4(arr[ai],slot_stride[ai],rel,slot_type[ai],slot_count[ai],inputs[ai]);
            vertex_ok=(program_kind==19u||program_kind==20u) ?
                dah_pox_skin_vertex(inputs,c,g_pg.transform_constant_valid,program_kind==20u,&result,reflection_uv) :
                (program_kind==16u||program_kind==25u) ?
                dah_skin62_vertex(inputs,c,g_pg.transform_constant_valid,&result,reflection_uv,NULL,NULL) :
                program_kind==15u ?
                dah_skin55_vertex(inputs,c,g_pg.transform_constant_valid,&result) :
                dah_skin_vertex(inputs,c,g_pg.transform_constant_valid,&result,reflection_uv,NULL,NULL);
        }else if(program_kind==26u||program_kind==27u){
            float inputs[3][4];
            if(slot_count[1]<4u)normal[3]=1.0f;
            if(slot_count[2]<4u)tex[3]=1.0f;
            memcpy(inputs[0],pos,sizeof pos);memcpy(inputs[1],normal,sizeof normal);
            memcpy(inputs[2],tex,sizeof tex);
            vertex_ok=program_kind==27u ?
                dah_rockwell_vehicle_reflection_vertex(inputs,c,&result,reflection_uv) :
                dah_rockwell_vehicle_vertex(inputs,c,&result,reflection_uv);
        }else if(program_kind==29u||program_kind==30u){
            float inputs[4][4];
            if(slot_count[1]<4u)normal[3]=1.0f;
            if(slot_count[2]<4u)tex[3]=1.0f;
            if(program_kind==30u)extra[3]=1.0f;
            else if(slot_count[3]<4u)extra[3]=1.0f;
            memcpy(inputs[0],pos,sizeof pos);memcpy(inputs[1],normal,sizeof normal);
            memcpy(inputs[2],tex,sizeof tex);memcpy(inputs[3],extra,sizeof extra);
            vertex_ok=dah_static_reflection_vertex(inputs,c,&result,reflection_uv);
        }else if(program_kind==28u){
            float inputs[3][4];
            if(slot_count[1]<4u)normal[3]=1.0f;
            memcpy(inputs[0],pos,sizeof pos);memcpy(inputs[1],normal,sizeof normal);
            memcpy(inputs[2],tex,sizeof tex);
            vertex_ok=dah_rockwell_static_lit_vertex(inputs,c,&result);
        }else if(program_kind==24u){
            vertex_ok=dah_farm_constant_vertex(pos,c,&result);
        }else if(program_kind==23u){
            vertex_ok=dah_farm_push_vertex(pos,normal,c,&result);
        }else if(program_kind==22u){
            float inputs[4][4];
            if(slot_count[1]<4u)normal[3]=1.0f;
            if(slot_count[2]<4u)tex[3]=1.0f;
            if(slot_count[3]<4u)extra[3]=1.0f;
            memcpy(inputs[0],pos,sizeof pos);memcpy(inputs[1],normal,sizeof normal);
            memcpy(inputs[2],tex,sizeof tex);memcpy(inputs[3],extra,sizeof extra);
            vertex_ok=dah_farm_deform_vertex(inputs,c,g_pg.transform_constant_valid,&result);
        }else if(program_kind==21u){
            vertex_ok=dah_pox_static_vertex(pos,normal,tex,c,g_pg.transform_constant_valid,&result);
        }else if(program_kind==18u){
            vertex_ok=dah_pox_ui_vertex(pos,normal,tex,c,&result);
        }else if(program_kind==17u){
            vertex_ok=dah_pox_vertex(pos,normal,c,g_pg.transform_constant_valid,&result);
        }else if(program_kind==14u){
            vertex_ok=dah_unlit9_vertex(pos,normal,tex,c,&result);
        }else if(program_kind==12u){
            /* NV2A fills absent fourth attribute components with 1. */
            if(slot_count[1]<4u)normal[3]=1.0f;
            float inputs[4][4];
            memcpy(inputs[0],pos,sizeof pos);memcpy(inputs[1],normal,sizeof normal);
            memcpy(inputs[2],tex,sizeof tex);memcpy(inputs[3],extra,sizeof extra);
            vertex_ok=dah_farm_reflection_vertex(inputs,c,&result,reflection_uv);
        }else if(program_kind>=10u){
            float inputs[3][4];
            if(slot_count[1]<4u)normal[3]=1.0f;
            if(attribute_count>2u&&slot_count[2]<4u)tex[3]=1.0f;
            memcpy(inputs[0],pos,sizeof pos);memcpy(inputs[1],normal,sizeof normal);memcpy(inputs[2],tex,sizeof tex);
            vertex_ok=dah_farm_vertex(program_kind,inputs,c,&result);
        }else {
            /* The static/menu program uses DP4 for its texture transform.
             * Xemu's captured input pads the Farm sky's float2 v2 as
             * (x,y,0,1), so preserve c78.w/c79.w instead of dropping the
             * animated U translation. Keep this scoped away from packed
             * skin/morph streams whose missing lanes have separate rules. */
            if (attribute_count > 2u)
                dah_complete_static_texcoord(slot_count[2], tex);
            vertex_ok=dah_menu_vertex_impl(pos, normal, tex, c,
                (program_kind == 2u || program_kind == 3u) ? extra : NULL, &result);
        }
        if (!vertex_ok) {

            if((program_kind==13u||program_kind==15u||program_kind==16u) && dah_crypto_head_trace_enabled()) {
                static unsigned traced_skin_vertices;
                if(traced_skin_vertices++<16u) {
                    float weights[4]={0},bones[4]={0},uv[4]={0};
                    float morph[4][4]={{0}};
                    fetch_attr_float4(arr[2],slot_stride[2],rel,slot_type[2],slot_count[2],weights);
                    fetch_attr_float4(arr[3],slot_stride[3],rel,slot_type[3],slot_count[3],bones);
                    fetch_attr_float4(arr[4],slot_stride[4],rel,slot_type[4],slot_count[4],uv);
                    if(program_kind==16u)
                        for(unsigned j=0;j<4u;++j)
                            fetch_attr_float4(arr[5u+j],slot_stride[5u+j],rel,
                                slot_type[5u+j],slot_count[5u+j],morph[j]);
                    fprintf(stderr,
                        "[DAH-CRYPTO-VERTEX-FAIL] sub=%u draw=%u i=%u idx=%u "
                        "weights=%g,%g,%g,%g bones=%g,%g,%g,%g c191=%g,%g,%g,%g "
                        "uv=%g,%g c85=%g,%g,%g,%g morph=" ,
                        g_pg.active_submission,g_pg.indexed_diagnostic_id,i,
                        g_pg.indices[i],weights[0],weights[1],weights[2],weights[3],
                        bones[0],bones[1],bones[2],bones[3],
                        c[191][0],c[191][1],c[191][2],c[191][3],uv[0],uv[1],
                        c[85][0],c[85][1],c[85][2],c[85][3]);
                    for(unsigned j=0;j<4u;++j)
                        fprintf(stderr,"%s[%g,%g,%g]",j?",":"",
                            morph[j][0],morph[j][1],morph[j][2]);
                    fprintf(stderr," valid-bases=");
                    for(unsigned j=0;j<4u;++j) {
                        int base=86+(int)floorf(bones[j]*c[191][j]+0.001f);
                        fprintf(stderr,"%s%d:%u%u%u",j?",":"",base,
                            base>=0&&base<192?g_pg.transform_constant_valid[base*4u]:0,
                            base>=0&&base+1<192?g_pg.transform_constant_valid[(base+1)*4u]:0,
                            base>=0&&base+2<192?g_pg.transform_constant_valid[(base+2)*4u]:0);
                    }
                    fputc('\n',stderr);
                }
            }

            /* Reject the whole strip: moving one vertex off-screen creates
             * large connecting triangles, not a degenerate primitive. */
            dah_farm_material_trace(program_kind == 11u &&
                (!isfinite(normal[2]) || normal[2] < -86.0f || normal[2] >= 103.0f)
                ? "vertex-palette" : "vertex", program_kind, out, i, i, 0);
            static unsigned vertex_fail_log_count;
            if (dah_farm_material_trace_enabled() && vertex_fail_log_count++ < 32u)
                fprintf(stderr, "[DAH-FARM-VERTEX-FAIL] draw=%u kind=%u i=%u pos=%g,%g,%g,%g slot1=%g,%g,%g,%g slot2=%g,%g,%g,%g\n",
                    g_pg.indexed_diagnostic_id, program_kind, i, pos[0], pos[1], pos[2], pos[3],
                    normal[0], normal[1], normal[2], normal[3],
                    tex[0], tex[1], tex[2], tex[3]);
            free(out); return 0;
        }

        if(dah_fine_draw){double t=dah_profile_ms();dah_vertex_shader_ms+=t-dah_vertex_stage_start;dah_vertex_stage_start=t;}
        out[i].x   = result.screen[0];
        out[i].y   = result.screen[1];
        /* Integer NV2A depth uses the surface precision (16 or 24 bits). */
        out[i].z   = result.screen[2] / (((g_pg.surface_format >> 4u) & 15u) == 1u ? 65535.0f : 16777215.0f);
        if (out[i].z < 0.0f) out[i].z = 0.0f;
        if (out[i].z > 1.0f) out[i].z = 1.0f;
        /* Preserve the original W sign for homogeneous clipping. */
        out[i].rhw = dah_menu_rcc(result.screen[3]);
        out[i].color = pack_argb(result.diffuse);
        if(program_kind==17u){
            uint32_t width=g_pg.tex[0].image_rect>>16u;
            uint32_t height=g_pg.tex[0].image_rect&0xFFFFu;
            if(!width||!height){width=640u;height=480u;}
            out[i].u=result.uv[0]/(float)width;
            out[i].v=result.uv[1]/(float)height;
        }else{
            out[i].u=result.uv[0];out[i].v=result.uv[1];
        }
        out[i].u1 = dah_menu_dot3(normal,c[24])*c[190][0]+c[190][0];
        out[i].v1 = dah_menu_dot3(normal,c[25])*c[190][1]+c[190][1];
        /* TEXCOORD2.x carries the retail vertex shader fog output to the
         * NV2A final combiner. Reflection keeps all three cube coordinates. */
        /* NV2A forces oFog to one when fog is disabled, even when a
         * programmable vertex shader wrote a different fog coordinate. */
        float vertex_fog = dah_transform_fog(result.fog);
        out[i].w1=vertex_fog;
        out[i].fog_coord=1.0f;
        out[i].fog_pad=0.0f;
        if(program_kind==12u||program_kind==27u||program_kind==29u||program_kind==30u){out[i].u1=reflection_uv[0];out[i].v1=reflection_uv[1];out[i].w1=reflection_uv[2];out[i].fog_coord=vertex_fog;out[i].fog_pad=1.0f;}
        else if(program_kind==26u){out[i].u1=reflection_uv[0];out[i].v1=reflection_uv[1];}
        else if(program_kind==13u||program_kind==16u||program_kind==19u||program_kind==20u){out[i].u1=reflection_uv[0];out[i].v1=reflection_uv[1];}
        else if(program_kind==17u)out[i].u1=out[i].v1=0.0f;
        else if(program_kind>=10u)out[i].u1=out[i].v1=0;

        if (vertex_seen) {
            vertex_cache[rel] = out[i];
            vertex_seen[rel] = 1u;
        }
        if(dah_fine_draw)dah_vertex_pack_ms+=dah_profile_ms()-dah_vertex_stage_start;
        if (log_count < 4u && i < 3u)
            fprintf(stderr,
                "[DAH-3D-VERT] draw=%u i=%u screen=(%.2f,%.2f,%.4f) rhw=%g"
                " clipw=%.2f color=%08X uv=(%.4f,%.4f)\n",
                g_pg.indexed_diagnostic_id, i,
                out[i].x, out[i].y, out[i].z, out[i].rhw,
                result.screen[3],
                out[i].color, out[i].u, out[i].v);
    }

    /* The Farm projector mask is a five-index strip using the exact static
     * program.  Keep this bounded trace beside the transform so a capture can
     * distinguish bad guest inputs/constants from host packing or topology. */
    if (program_kind == 10u && g_pg.index_count == 5u &&
        g_pg.active_submission >= 8000u && dah_ui_animation_trace_enabled()) {
        static int effect_capture_requested;
        const char *effect_submission = getenv("DAH_RENDERDOC_EFFECT_SUBMISSION");
        float effect_xmin=FLT_MAX,effect_ymin=FLT_MAX;
        float effect_xmax=-FLT_MAX,effect_ymax=-FLT_MAX;
        for (uint32_t effect_i=0;effect_i<g_pg.index_count;++effect_i) {
            if(out[effect_i].x<effect_xmin)effect_xmin=out[effect_i].x;
            if(out[effect_i].x>effect_xmax)effect_xmax=out[effect_i].x;
            if(out[effect_i].y<effect_ymin)effect_ymin=out[effect_i].y;
            if(out[effect_i].y>effect_ymax)effect_ymax=out[effect_i].y;
        }
        if (!effect_capture_requested && effect_submission && *effect_submission &&
            g_pg.active_submission >= (uint32_t)strtoul(effect_submission, NULL, 0) &&
            g_pg.tex[0].offset == 0x02493800u && effect_xmax>=0.0f &&
            effect_xmin<=640.0f && effect_ymax>=0.0f && effect_ymin<=480.0f) {
            dah_renderdoc_begin_effect("DAH1 Farm alpha billboard effect");
            effect_capture_requested = 1;
        }
        static unsigned projector_reports;
        if (projector_reports++ < 64u) {
            fprintf(stderr,
                "[DAH-PROJECTOR-STRIP] sub=%u draw=%u idx=%u,%u,%u,%u,%u "
                "array=%08X,%08X,%08X off=%08X,%08X,%08X "
                "tex0=%08X,%08X,%08X,%08X,%08X,%08X "
                "blend=%d,%08X,%08X,%08X alpha=%d,%08X,%u combiner=%08X "
                "c1=%g,%g,%g,%g c2=%g,%g,%g,%g c56=%g,%g,%g,%g\n",
                g_pg.active_submission,g_pg.indexed_diagnostic_id,
                g_pg.indices[0],g_pg.indices[1],g_pg.indices[2],g_pg.indices[3],g_pg.indices[4],
                g_pg.array_format[0],g_pg.array_format[1],g_pg.array_format[2],
                g_pg.array_offset[0],g_pg.array_offset[1],g_pg.array_offset[2],
                g_pg.tex[0].offset,g_pg.tex[0].format,g_pg.tex[0].control0,
                g_pg.tex[0].image_rect,g_pg.tex[0].address,g_pg.tex[0].filter,
                g_pg.blend_enable,g_pg.blend_sfactor,g_pg.blend_dfactor,g_pg.blend_equation,
                g_pg.alpha_test,g_pg.alpha_func,g_pg.alpha_ref,g_pg.combiner_control,
                c[1][0],c[1][1],c[1][2],c[1][3],
                c[2][0],c[2][1],c[2][2],c[2][3],
                c[56][0],c[56][1],c[56][2],c[56][3]);
            for (uint32_t k = 0; k < g_pg.index_count; ++k) {
                uint32_t rel = g_pg.indices[k] - first;
                float p[4]={0,0,0,1}, uv[4]={0}, col[4]={0};
                fetch_attr_float4(arr[0],slot_stride[0],rel,slot_type[0],slot_count[0],p);
                fetch_attr_float4(arr[1],slot_stride[1],rel,slot_type[1],slot_count[1],uv);
                fetch_attr_float4(arr[2],slot_stride[2],rel,slot_type[2],slot_count[2],col);
                fprintf(stderr,
                    "[DAH-PROJECTOR-VERTEX] k=%u idx=%u p=%g,%g,%g,%g "
                    "uv=%g,%g col=%g,%g,%g,%g out=%g,%g,%g,%g,%08X,%g,%g,%g\n",
                    k,g_pg.indices[k],p[0],p[1],p[2],p[3],uv[0],uv[1],
                    col[0],col[1],col[2],col[3],out[k].x,out[k].y,out[k].z,
                    out[k].rhw,out[k].color,out[k].u,out[k].v,out[k].w1);
            }
            fflush(stderr);
        }
    }

    if(program_kind==17u && dah_ui_animation_trace_enabled()){
        static uint32_t last_vertex_hash;
        static unsigned vertex_reports;
        uint32_t hash=2166136261u;float umin=1e30f,vmin=1e30f,umax=-1e30f,vmax=-1e30f;
        for(uint32_t i=0;i<g_pg.index_count;++i){
            uint32_t bits[2];memcpy(bits,&out[i].u,2u*sizeof(uint32_t));
            for(unsigned j=0;j<2u;++j)hash=(hash^bits[j])*16777619u;
            if(out[i].u<umin)umin=out[i].u;if(out[i].u>umax)umax=out[i].u;
            if(out[i].v<vmin)vmin=out[i].v;if(out[i].v>vmax)vmax=out[i].v;
        }
        if(vertex_reports<64u&&(!vertex_reports||hash!=last_vertex_hash)){
            float packed[4]={0};uint32_t rel=g_pg.indices[0]-first;
            fetch_attr_float4(arr[1],slot_stride[1],rel,slot_type[1],slot_count[1],packed);
            fprintf(stderr,"[DAH-POX-VERTICES] submit=%u hash=%08X uv=%g,%g..%g,%g first=%g,%g packed=%g,%g,%g,%g\n",
                g_pg.active_submission,hash,umin,vmin,umax,vmax,out[0].u,out[0].v,
                packed[0],packed[1],packed[2],packed[3]);
            fflush(stderr);++vertex_reports;last_vertex_hash=hash;
        }
        if(g_pg.index_count>=130u && g_pg.index_count<=150u){
            static unsigned lookup_reports;
            if(lookup_reports++<32u){
                float packed[4]={0};uint32_t rel=g_pg.indices[0]-first;
                fetch_attr_float4(arr[1],slot_stride[1],rel,slot_type[1],slot_count[1],packed);
                float fx=out[0].x*c[126][0],fy=out[0].y*c[126][1];fx-=floorf(fx);fy-=floorf(fy);
                int address=96+(int)floorf(fx*c[127][0]+fy*c[127][1]*c[127][1]+0.001f);
                fprintf(stderr,"[DAH-POX-LOOKUP] submit=%u draw=%u n=%u idx=%u screen=%g,%g "
                    "frac=%g,%g address=%d lookup=%g,%g packedw=%g uv=%g,%g fog=%d c187=%g\n",
                    g_pg.active_submission,g_pg.indexed_diagnostic_id,g_pg.index_count,g_pg.indices[0],
                    out[0].x,out[0].y,fx,fy,address,
                    address>=0&&address<192?c[address][0]:NAN,address>=0&&address<192?c[address][1]:NAN,
                    packed[3],out[0].u,out[0].v,g_pg.fog_enable,c[187][0]);
                fflush(stderr);
            }
        }
    }



    if((program_kind==10u||program_kind==11u) && dah_crypto_head_trace_enabled() &&
       (g_pg.active_submission==6300u || g_pg.active_submission==6500u)){
        static unsigned traced_basic;
        if(traced_basic<256u){
            float xmin=1e30f,ymin=1e30f,xmax=-1e30f,ymax=-1e30f;
            float zmin=1e30f,zmax=-1e30f;
            unsigned front=0,screen=0,amin=255u,amax=0u;
            for(uint32_t k=0;k<g_pg.index_count;++k){
                const OutputVertex *q=&out[k];
                unsigned alpha=q->color>>24u;
                if(q->x<xmin)xmin=q->x;if(q->x>xmax)xmax=q->x;
                if(q->y<ymin)ymin=q->y;if(q->y>ymax)ymax=q->y;
                if(q->z<zmin)zmin=q->z;if(q->z>zmax)zmax=q->z;
                if(q->rhw>0.0f)++front;
                if(q->rhw>0.0f&&q->x>=0.0f&&q->x<640.0f&&q->y>=0.0f&&q->y<480.0f)++screen;
                if(alpha<amin)amin=alpha;if(alpha>amax)amax=alpha;
            }
            if(xmax>=250.0f&&xmin<=365.0f&&ymax>=150.0f&&ymin<=385.0f&&
               xmax-xmin<250.0f&&ymax-ymin<250.0f){
                ++traced_basic;
                fprintf(stderr,
                    "[DAH-CRYPTO-BASIC] sub=%u draw=%u kind=%u n=%u "
                    "xy=%.1f,%.1f..%.1f,%.1f z=%.5f..%.5f "
                    "front=%u screen=%u alpha=%u..%u tex=%08X,%08X "
                    "target=%08X depth=%d,%d,%X cull=%d,%X,%X "
                    "atest=%d,%X,%u blend=%d,%X,%X\n",
                    g_pg.active_submission,g_pg.indexed_diagnostic_id,
                    program_kind,g_pg.index_count,xmin,ymin,xmax,ymax,zmin,zmax,
                    front,screen,amin,amax,g_pg.tex[0].offset,g_pg.tex[0].format,
                    g_pg.surface_color_offset,g_pg.depth_test,g_pg.depth_write,
                    g_pg.depth_func,g_pg.cull_enable,g_pg.front_face,g_pg.cull_face,
                    g_pg.alpha_test,g_pg.alpha_func,g_pg.alpha_ref,
                    g_pg.blend_enable,g_pg.blend_sfactor,g_pg.blend_dfactor);
            }
        }
    }


    if (program_kind == 13u && g_pg.index_count == 3231u &&
        dah_crypto_head_trace_enabled() &&
        (g_pg.active_submission == 6300u || g_pg.active_submission == 6500u)) {
        fprintf(stderr,
            "[DAH-CRYPTO-MATERIAL] sub=%u draw=%u final=%08X,%08X "
            "combiner=%08X shader=%08X color0=%08X,%08X alpha0=%08X,%08X "
            "tex0=%08X,%08X,%08X,%08X,%08X\n",
            g_pg.active_submission,g_pg.indexed_diagnostic_id,
            g_pg.final_cw0,g_pg.final_cw1,g_pg.combiner_control,
            g_pg.shader_stage_program,g_pg.color_icw[0],g_pg.color_ocw[0],
            g_pg.alpha_icw[0],g_pg.alpha_ocw[0],
            g_pg.tex[0].offset,g_pg.tex[0].format,g_pg.tex[0].address,
            g_pg.tex[0].filter,g_pg.tex[0].control0);
        uint32_t span = last - first + 1u;
        uint8_t *seen_bones = (uint8_t *)calloc(span, 1u);
        unsigned count[64] = {0};
        float ymin[64], ymax[64], xmin[64], xmax[64];
        unsigned outlier_count = 0u;
        for (unsigned j = 0; j < 64u; ++j) {
            ymin[j] = xmin[j] = 1e30f;
            ymax[j] = xmax[j] = -1e30f;
        }
        if (seen_bones) {
            for (uint32_t k = 0; k < g_pg.index_count; ++k) {
                uint32_t rel = g_pg.indices[k] - first;
                if (seen_bones[rel]) continue;
                seen_bones[rel] = 1u;
                float weights[4], bones[4], pos[4];
                fetch_attr_float4(arr[0], slot_stride[0], rel, slot_type[0], slot_count[0], pos);
                fetch_attr_float4(arr[2], slot_stride[2], rel, slot_type[2], slot_count[2], weights);
                fetch_attr_float4(arr[3], slot_stride[3], rel, slot_type[3], slot_count[3], bones);
                unsigned dominant = 0u;
                for (unsigned j = 1u; j < 4u; ++j)
                    if (weights[j] > weights[dominant]) dominant = j;
                int bone = (int)floorf(bones[dominant] * c[191][dominant] + 0.001f) / 3;
                if (weights[dominant] > 0.0f && bone >= 0 && bone < 35) {
                    unsigned b = (unsigned)bone;
                    ++count[b];
                    if (out[k].x < xmin[b]) xmin[b] = out[k].x;
                    if (out[k].x > xmax[b]) xmax[b] = out[k].x;
                    if (out[k].y < ymin[b]) ymin[b] = out[k].y;
                    if (out[k].y > ymax[b]) ymax[b] = out[k].y;
                }
                if ((out[k].y < 230.0f || out[k].y > 470.0f) && outlier_count++ < 24u)
                    fprintf(stderr,
                        "[DAH-CRYPTO-BONE-OUT] sub=%u idx=%u screen=%.1f,%.1f,%.5f "
                        "raw=%.3f,%.3f,%.3f weights=%.3f,%.3f,%.3f,%.3f "
                        "bones=%.3f,%.3f,%.3f,%.3f dominant=%d\n",
                        g_pg.active_submission,g_pg.indices[k],out[k].x,out[k].y,out[k].z,
                        pos[0],pos[1],pos[2],weights[0],weights[1],weights[2],weights[3],
                        bones[0],bones[1],bones[2],bones[3],bone);
            }
            for (unsigned j = 0; j < 64u; ++j)
                if (count[j]) fprintf(stderr,
                    "[DAH-CRYPTO-BONE] sub=%u bone=%u count=%u xy=%.1f,%.1f..%.1f,%.1f "
                    "m0=%.3f,%.3f,%.3f,%.3f\n",
                    g_pg.active_submission,j,count[j],xmin[j],ymin[j],xmax[j],ymax[j],
                    c[86u + 3u*j][0],c[86u + 3u*j][1],
                    c[86u + 3u*j][2],c[86u + 3u*j][3]);
            free(seen_bones);
        }
    }

    if ((program_kind == 13u || program_kind == 15u || program_kind == 16u) &&
        dah_crypto_head_trace_enabled() &&
        g_pg.active_submission >= 6000u && g_pg.active_submission <= 7000u &&
        g_pg.active_submission % 100u == 0u) {
        static unsigned traced;
        if (traced++ < 256u) {
            float xmin=1e30f,ymin=1e30f,xmax=-1e30f,ymax=-1e30f;
            float zmin=1e30f,zmax=-1e30f;
            unsigned front=0,screen=0,alpha_zero=0;
            unsigned alpha_min=255u,alpha_max=0u;
            unsigned tri_cw=0,tri_ccw=0,tri_flat=0;
            for (uint32_t k=0;k<g_pg.index_count;++k) {
                const OutputVertex *q=&out[k];
                unsigned a=q->color >> 24u;
                if(q->x<xmin)xmin=q->x;if(q->x>xmax)xmax=q->x;
                if(q->y<ymin)ymin=q->y;if(q->y>ymax)ymax=q->y;
                if(q->z<zmin)zmin=q->z;if(q->z>zmax)zmax=q->z;
                if(q->rhw>0.0f)++front;
                if(q->rhw>0.0f && q->x>=0.0f && q->x<640.0f &&
                   q->y>=0.0f && q->y<480.0f)++screen;
                if(!a)++alpha_zero;
                if(a<alpha_min)alpha_min=a;if(a>alpha_max)alpha_max=a;
            }
            for(uint32_t k=0;k+2u<g_pg.index_count;++k){
                const OutputVertex *a=&out[k],*b=&out[k+1u],*d=&out[k+2u];
                if(a->rhw<=0.0f||b->rhw<=0.0f||d->rhw<=0.0f)continue;
                double signed_area=((double)b->x-a->x)*((double)d->y-a->y)-
                    ((double)b->y-a->y)*((double)d->x-a->x);
                if(k&1u)signed_area=-signed_area;
                if(signed_area>0.0001)++tri_cw;
                else if(signed_area< -0.0001)++tri_ccw;
                else ++tri_flat;
            }
            fprintf(stderr,
                "[DAH-CRYPTO-SKIN] sub=%u draw=%u kind=%u n=%u idx=%u..%u tex0=%08X,%08X "
                "xy=%.1f,%.1f..%.1f,%.1f z=%.5f..%.5f front=%u screen=%u "
                "alpha=%u..%u zero=%u tris=%u,%u,%u depth=%d,%d,%X "
                "cull=%d,%X,%X alpha-test=%d,%X,%u blend=%d,%X,%X "
                "c187w=%g c191=%g,%g,%g,%g sample=%g,%g,%g,%08X\n",
                g_pg.active_submission,g_pg.indexed_diagnostic_id,program_kind,g_pg.index_count,
                first,last,g_pg.tex[0].offset,g_pg.tex[0].format,
                xmin,ymin,xmax,ymax,zmin,zmax,front,screen,alpha_min,alpha_max,
                alpha_zero,tri_cw,tri_ccw,tri_flat,
                g_pg.depth_test,g_pg.depth_write,g_pg.depth_func,
                g_pg.cull_enable,g_pg.front_face,g_pg.cull_face,
                g_pg.alpha_test,g_pg.alpha_func,g_pg.alpha_ref,
                g_pg.blend_enable,g_pg.blend_sfactor,g_pg.blend_dfactor,
                c[187][3],c[191][0],c[191][1],c[191][2],c[191][3],
                out[0].x,out[0].y,out[0].z,out[0].color);
        }
    }

    if (dah_geometry_trace_enabled() && g_pg.active_submission == 800u) {
        float xmin=1e30f,ymin=1e30f,xmax=-1e30f,ymax=-1e30f,zmin=1e30f,zmax=-1e30f;
        unsigned front=0; uint32_t colors=0;
        for(unsigned i=0;i<g_pg.index_count;++i) {
            if(out[i].rhw > 0) ++front;
            xmin=fminf(xmin,out[i].x); xmax=fmaxf(xmax,out[i].x);
            ymin=fminf(ymin,out[i].y); ymax=fmaxf(ymax,out[i].y);
            zmin=fminf(zmin,out[i].z); zmax=fmaxf(zmax,out[i].z);
            colors |= out[i].color;
        }
        fprintf(stderr,"[DAH-GEOMETRY] draw=%u n=%u front=%u xy=%g,%g..%g,%g z=%g..%g color=%08X tex=%08X fmt=%08X depth=%u,%u,%X cull=%u,%X,%X alpha=%u,%X,%u blend=%u,%X,%X\n",
            g_pg.indexed_diagnostic_id,g_pg.index_count,front,xmin,ymin,xmax,ymax,zmin,zmax,colors,
            g_pg.tex[0].offset,g_pg.tex[0].format,g_pg.depth_test,g_pg.depth_write,g_pg.depth_func,
            g_pg.cull_enable,g_pg.front_face,g_pg.cull_face,g_pg.alpha_test,g_pg.alpha_func,g_pg.alpha_ref,
            g_pg.blend_enable,g_pg.blend_sfactor,g_pg.blend_dfactor);
    }
    double texture_start=dah_draw_timing ? dah_profile_ms() : 0.0;
    if (dah_fine_draw) {
        dah_fine_texture_lookup_ms = dah_fine_texture_upload_ms = 0.0;
        dah_fine_texture_hash_bytes = 0u;
        dah_fine_texture_uploads = 0u;
    }
    dah_fine_texture_active = dah_fine_draw;
    if(program_kind==17u){
        for(unsigned stage=0;stage<4u;++stage){
            if(!g_pg.tex[stage].enabled)continue;
            /* A stale/feedback RT record is not enough provenance: Farm's
             * Pox projector and saucer particles use ordinary linear ARGB
             * textures at offsets that may also have served as old targets.
             * Only classify a texture as an RT when its live SRV can be bound. */
            pox_render_targets[stage]=d3d8_PgraphTryBindRenderTargetTexture(
                stage,g_pg.tex[stage].offset)!=FALSE;
            if(!pox_render_targets[stage])pox_textures[stage]=dah_mesh_texture(stage,dev);
        }
        tex_obj=pox_textures[0];
    }else tex_obj=dah_mesh_texture(0,dev);
    dah_fine_texture_active = 0;
    double dah_fine_texture0_end = dah_fine_draw ? dah_profile_ms() : 0.0;
    if(program_kind==17u){
        for(unsigned stage=0;stage<4u;++stage)if(g_pg.tex[stage].enabled &&
            !pox_render_targets[stage] && !pox_textures[stage]){
            dah_farm_material_trace("texture-pox",program_kind,out,g_pg.index_count,stage,0);free(out);return 0;
        }
    }else if(g_pg.tex[0].enabled && !tex_obj) {dah_farm_material_trace("texture0",program_kind,out,g_pg.index_count,UINT32_MAX,0);free(out);return 0;}
    dah_fine_texture_active = dah_fine_draw;
    IDirect3DTexture8 *tex1_obj=program_kind==17u ? pox_textures[1] : program_kind>=3u ? dah_mesh_texture(1,dev) : NULL;
    dah_fine_texture_active = 0;
    double texture_end=dah_draw_timing ? dah_profile_ms() : 0.0;
    if(program_kind!=17u && program_kind>=3u && g_pg.tex[1].enabled && !tex1_obj) {dah_farm_material_trace("texture1",program_kind,out,g_pg.index_count,UINT32_MAX,0);free(out);return 0;}

    if (dah_fog_trace_enabled() && program_kind >= 10u &&
        (!dah_ui_animation_trace_enabled() ||
         g_pg.active_submission >= dah_ui_animation_trace_start())) {
        static unsigned fog_trace_count;
        if (fog_trace_count++ < 16u) {
            float fog_min = 1e30f, fog_max = -1e30f;
            for (uint32_t i = 0; i < g_pg.index_count; ++i) {
                float f = (program_kind == 12u || program_kind == 27u || program_kind == 29u || program_kind == 30u) ? out[i].fog_coord : out[i].w1;
                if (f < fog_min) fog_min = f;
                if (f > fog_max) fog_max = f;
            }
            const DWORD *rs = d3d8_GetRenderStates();
            fprintf(stderr, "[DAH-FARM-FOG] submit=%u draw=%u kind=%u n=%u c56=%g,%g,%g,%g vertex=%g..%g fogcolor=%08X fog_enable=%u final=%08X,%08X\n",
                g_pg.active_submission, g_pg.indexed_diagnostic_id, program_kind, g_pg.index_count,
                c[56][0], c[56][1], c[56][2], c[56][3], fog_min, fog_max,
                rs ? rs[D3DRS_FOGCOLOR] : 0u, rs ? (unsigned)rs[D3DRS_FOGENABLE] : 0u,
                g_pg.final_cw0, g_pg.final_cw1);
        }
    }
    /* ── D3D render state (same combiner intent as movie shader) ── */
    dev->lpVtbl->SetPixelShader(dev, 0);
    /* Every captured programmable path writes a fog coordinate consumed by
     * the NV2A final combiner. TEXCOORD2.x carries it for the host combiner;
     * the reflection path widens TEXCOORD1 to preserve its cube vector. */
    dev->lpVtbl->SetVertexShader(dev, D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX3 |
        ((program_kind==12u||program_kind==27u||program_kind==29u||program_kind==30u) ? D3DFVF_TEXCOORDSIZE3(1) : 0u));
    dev->lpVtbl->SetRenderState(dev, D3DRS_ZENABLE,          g_pg.depth_test);
    dev->lpVtbl->SetRenderState(dev, D3DRS_ZWRITEENABLE,     g_pg.depth_write);
    dev->lpVtbl->SetRenderState(dev, D3DRS_LIGHTING,         FALSE);
    dev->lpVtbl->SetRenderState(dev, D3DRS_COLORWRITEENABLE,
                                dah_nv2a_color_write_mask(g_pg.color_mask));
    dev->lpVtbl->SetRenderState(dev, D3DRS_ZFUNC, g_pg.depth_func - 0x0200u + 1u);
    dev->lpVtbl->SetRenderState(dev, D3DRS_CULLMODE, g_pg.cull_enable ?
        ((g_pg.front_face == 0x0901u) == (g_pg.cull_face == 0x0405u) ? D3DCULL_CCW : D3DCULL_CW) : D3DCULL_NONE);
    if (!dah_apply_blend_state(dev, g_pg.blend_enable)) {
        dah_hud_draw_trace("blend-equation",program_kind,out,g_pg.index_count,UINT32_MAX,0);
        free(out); return 0;
    }
    dev->lpVtbl->SetRenderState(dev, D3DRS_ALPHATESTENABLE, g_pg.alpha_test);
    dev->lpVtbl->SetRenderState(dev, D3DRS_ALPHAFUNC, g_pg.alpha_func - 0x0200u + 1u);
    dev->lpVtbl->SetRenderState(dev, D3DRS_ALPHAREF, g_pg.alpha_ref);

    if (tex_obj) {
        dev->lpVtbl->SetTexture(dev, 0, (IDirect3DBaseTexture8 *)tex_obj);
        dev->lpVtbl->SetTextureStageState(dev, 0, D3DTSS_COLOROP,   D3DTOP_MODULATE2X);
        dev->lpVtbl->SetTextureStageState(dev, 0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
        dev->lpVtbl->SetTextureStageState(dev, 0, D3DTSS_COLORARG2, D3DTA_TEXTURE);
        dev->lpVtbl->SetTextureStageState(dev, 0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE);
        dev->lpVtbl->SetTextureStageState(dev, 0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
        dev->lpVtbl->SetTextureStageState(dev, 0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
        dev->lpVtbl->SetTextureStageState(dev, 0, D3DTSS_ADDRESSU,
            nv2a_texture_address_to_d3d(g_pg.tex[0].address));
        dev->lpVtbl->SetTextureStageState(dev, 0, D3DTSS_ADDRESSV,
            nv2a_texture_address_to_d3d(g_pg.tex[0].address >> 8u));
        dev->lpVtbl->SetTextureStageState(dev, 0, D3DTSS_MINFILTER,
            nv2a_texture_min_filter_to_d3d(g_pg.tex[0].filter));
        dev->lpVtbl->SetTextureStageState(dev, 0, D3DTSS_MAGFILTER,
            nv2a_texture_mag_filter_to_d3d(g_pg.tex[0].filter));
        dev->lpVtbl->SetTextureStageState(dev, 0, D3DTSS_MIPFILTER,
            nv2a_texture_mip_filter_to_d3d(g_pg.tex[0].filter));
        dev->lpVtbl->SetTextureStageState(dev, 0, D3DTSS_MIPMAPLODBIAS,
            float_bits(nv2a_texture_lod_bias(g_pg.tex[0].filter)));
        dev->lpVtbl->SetTextureStageState(dev, 0, D3DTSS_MAXANISOTROPY,
            nv2a_texture_max_anisotropy(g_pg.tex[0].control0));
    } else {
        dev->lpVtbl->SetTexture(dev, 0, NULL);
        dev->lpVtbl->SetTextureStageState(dev, 0, D3DTSS_COLOROP,   D3DTOP_SELECTARG1);
        dev->lpVtbl->SetTextureStageState(dev, 0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
        dev->lpVtbl->SetTextureStageState(dev, 0, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG1);
        dev->lpVtbl->SetTextureStageState(dev, 0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
    }
    for (unsigned stage = 1u; stage < 4u; ++stage) {
        dev->lpVtbl->SetTexture(dev, stage, NULL);
        dev->lpVtbl->SetTextureStageState(dev, stage, D3DTSS_COLOROP, D3DTOP_DISABLE);
    }

    if(program_kind>=3u) {
        dev->lpVtbl->SetTexture(dev,1,(IDirect3DBaseTexture8*)tex1_obj);
        dev->lpVtbl->SetTextureStageState(dev,1,D3DTSS_ADDRESSU,D3DTADDRESS_CLAMP);
        dev->lpVtbl->SetTextureStageState(dev,1,D3DTSS_ADDRESSV,D3DTADDRESS_CLAMP);
        dev->lpVtbl->SetTextureStageState(dev,1,D3DTSS_MINFILTER,
            nv2a_texture_min_filter_to_d3d(g_pg.tex[1].filter));
        dev->lpVtbl->SetTextureStageState(dev,1,D3DTSS_MAGFILTER,
            nv2a_texture_mag_filter_to_d3d(g_pg.tex[1].filter));
        dev->lpVtbl->SetTextureStageState(dev,1,D3DTSS_MIPFILTER,
            nv2a_texture_mip_filter_to_d3d(g_pg.tex[1].filter));
        dev->lpVtbl->SetTextureStageState(dev,1,D3DTSS_MIPMAPLODBIAS,
            float_bits(nv2a_texture_lod_bias(g_pg.tex[1].filter)));
        dev->lpVtbl->SetTextureStageState(dev,1,D3DTSS_MAXANISOTROPY,
            nv2a_texture_max_anisotropy(g_pg.tex[1].control0));
    }
    /* The common kind 1/2 Farm meshes use the same register combiner and fog
     * equation as the advanced mesh paths. The former fixed-function
     * MODULATE2X approximation omitted the final fog mix, producing the dark
     * and abruptly saturated scene changes visible against xemu. */
    d3d8_combiners_set_nv2a(g_pg.combiner_control,g_pg.shader_stage_program,
        g_pg.color_icw,g_pg.color_ocw,g_pg.alpha_icw,g_pg.alpha_ocw,
        g_pg.factor0,g_pg.factor1,g_pg.final_cw0,g_pg.final_cw1);
    d3d8_combiners_set_texture_alpha_one_mask(dah_texture_alpha_one_mask());
    d3d8_combiners_set_vertex_fog(1);
    if(program_kind==17u){
        for(unsigned stage=0;stage<4u;++stage){
            dev->lpVtbl->SetTexture(dev,stage,(IDirect3DBaseTexture8*)pox_textures[stage]);
            dev->lpVtbl->SetTextureStageState(dev,stage,D3DTSS_ADDRESSU,D3DTADDRESS_CLAMP);
            dev->lpVtbl->SetTextureStageState(dev,stage,D3DTSS_ADDRESSV,D3DTADDRESS_CLAMP);
            dev->lpVtbl->SetTextureStageState(dev,stage,D3DTSS_MINFILTER,
                nv2a_texture_min_filter_to_d3d(g_pg.tex[stage].filter));
            dev->lpVtbl->SetTextureStageState(dev,stage,D3DTSS_MAGFILTER,
                nv2a_texture_mag_filter_to_d3d(g_pg.tex[stage].filter));
            dev->lpVtbl->SetTextureStageState(dev,stage,D3DTSS_MIPFILTER,
                nv2a_texture_mip_filter_to_d3d(g_pg.tex[stage].filter));
            dev->lpVtbl->SetTextureStageState(dev,stage,D3DTSS_MIPMAPLODBIAS,
                float_bits(nv2a_texture_lod_bias(g_pg.tex[stage].filter)));
            dev->lpVtbl->SetTextureStageState(dev,stage,D3DTSS_MAXANISOTROPY,
                nv2a_texture_max_anisotropy(g_pg.tex[stage].control0));
            if(pox_render_targets[stage] && FAILED(d3d8_PgraphBindRenderTargetTexture(stage,g_pg.tex[stage].offset))){
                dah_farm_material_trace("texture-pox-rt",program_kind,out,g_pg.index_count,stage,E_FAIL);
                free(out);return 0;
            }
        }
    }
    dev->lpVtbl->BeginScene(dev);
    double draw_start=dah_draw_timing ? dah_profile_ms() : 0.0;
    dah_pixel_trace_begin(program_kind,out);
    hr = dev->lpVtbl->DrawPrimitiveUP(dev,
                                       g_pg.draw_mode == 5u ? D3DPT_TRIANGLELIST : D3DPT_TRIANGLESTRIP,
                                       g_pg.draw_mode == 5u ? g_pg.index_count / 3u : g_pg.index_count - 2u,
                                       out, sizeof(*out));
    dah_pixel_trace_end(hr);
    double dah_fine_draw_end = dah_draw_timing ? dah_profile_ms() : 0.0;
    dah_trace_color_mask_draw(program_kind,out,hr);
    if (dah_runtime_profile) {static double texture_total,state_total,draw_total,setup_total,vertex_total;static unsigned n;
     setup_total+=vertices_start-setup_start;vertex_total+=texture_start-vertices_start;texture_total+=texture_end-texture_start;state_total+=draw_start-texture_end;draw_total+=dah_fine_draw_end-draw_start;
     if(++n==1000){fprintf(stderr,"[DAH-MESH-PROFILE] n=%u setup=%.3f vertex=%.3f texture=%.3f state=%.3f draw=%.3f ms\n",n,setup_total,vertex_total,texture_total,state_total,draw_total);n=0;setup_total=vertex_total=texture_total=state_total=draw_total=0;}}
    if (dah_fine_draw) {
        fprintf(stderr, "[DAH-FARM-FINE] submit=%u draw=%u kind=%u n=%u transforms=%u span=%u setup=%.3f vertex=%.3f tex0=%.3f tex1=%.3f tex-lookup=%.3f tex-upload=%.3f hash-bytes=%llu uploads=%u state=%.3f d3d-draw=%.3f ms\n",
            g_pg.active_submission, g_pg.indexed_diagnostic_id, program_kind, g_pg.index_count,
            g_pg.index_count - dah_fine_vertex_cache_hits, (unsigned)vertex_span,
            vertices_start - setup_start, texture_start - vertices_start,
            dah_fine_texture0_end - texture_start, texture_end - dah_fine_texture0_end,
            dah_fine_texture_lookup_ms, dah_fine_texture_upload_ms,
            (unsigned long long)dah_fine_texture_hash_bytes, dah_fine_texture_uploads,
            draw_start - texture_end, dah_fine_draw_end - draw_start);
        fprintf(stderr,"[DAH-FARM-VERTEX-PHASE] submit=%u draw=%u kind=%u indices=%u transforms=%u attr=%.3f shader=%.3f pack=%.3f hit=%.3f ms\n",
            g_pg.active_submission,g_pg.indexed_diagnostic_id,program_kind,g_pg.index_count,
            g_pg.index_count-dah_fine_vertex_cache_hits,dah_vertex_attr_ms,
            dah_vertex_shader_ms,dah_vertex_pack_ms,dah_vertex_hit_ms);
        ++dah_fine_draw_logs;
    }
    dah_farm_material_trace(FAILED(hr) ? "draw-failed" : "accepted",
                            program_kind, out, g_pg.index_count, UINT32_MAX, hr);
    free(out);

    if (FAILED(hr)) {
        fprintf(stderr, "[DAH-3D-DRAW] DrawPrimitiveUP failed hr=%08lX\n",
                (unsigned long)hr);
        return 0;
    }

    if(program_kind>=10u){static unsigned seen;unsigned bit=1u<<(program_kind-10u);if(!(seen&bit)){seen|=bit;fprintf(stderr,"[DAH-FARM-DRAW] kind=%u submit=%u indices=%u target=%08X hr=%08lX\n",program_kind,g_pg.active_submission,g_pg.index_count,g_pg.surface_color_offset,(unsigned long)hr);}}
    ++g_pg.stats.draw_calls;
    g_pg.stats.vertices_submitted += g_pg.index_count;
    if (log_count++ < 16u)
        fprintf(stderr, "[DAH-3D-DRAW] draw=%u verts=%u tex=%s hr=%08lX\n",
                g_pg.indexed_diagnostic_id, g_pg.index_count,
                tex_obj ? "compressed" : "none", (unsigned long)hr);
    return 1;
}

static int movie_shader_matches(void)
{
    /* Original four MOV instructions captured in retail Bink and UI draws.
     * NV2A word1 has opcode/input, word3 output index/mask:
     *   MOV oPos,v0; MOV oT0,v1; MOV oD0,v2; MOV oFog,c187.x (END).
     * The final shader position is screen space on NV2A. This exact program
     * gate prevents treating an arbitrary float4 input as a screen position.
     * The retail combiner computes RGB=2*v2.rgb*T0.rgb, A=v2.a*T0.a.
     */
    static const uint32_t program[16] = {
        0, 0x0020001B, 0x0836106C, 0x2070F800,
        0, 0x0020021B, 0x0836106C, 0x2070F848,
        0, 0x0020041B, 0x0836106C, 0x2070F818,
        0, 0x00376000, 0x0C36106C, 0x2070F829
    };
    uint32_t first;
    if ((g_pg.transform_mode & 3u) != 2u || g_pg.transform_start > 136u - 4u) return 0;
    first = g_pg.transform_start * 4u;
    for (unsigned i = 0; i < 16u; ++i)
        if (!g_pg.transform_valid[first + i] || g_pg.transform_program[first + i] != program[i])
            return 0;
    return g_pg.color_icw[0] == 0xC4C80000u && g_pg.color_ocw[0] == 0x000100C0u &&
           g_pg.alpha_icw[0] == 0xD4D81010u && g_pg.alpha_ocw[0] == 0x000000C0u &&
           g_pg.combiner_control == 0x00011101u &&
           g_pg.final_cw0 == 0x0000000Eu && g_pg.final_cw1 == 0x00001C80u &&
           g_pg.shader_stage_program == 1u;
}

static int submit_indexed_movie(void)
{
    IDirect3DDevice8 *dev = xbox_GetD3DDevice();
    OutputVertex *out = NULL;
    const uint8_t *arrays[3];
    uint32_t first_index = UINT32_MAX, last_index = 0;
    const uint8_t *texture_data;
    D3DLOCKED_RECT locked;
    uint32_t width = g_pg.tex[0].image_rect >> 16u;
    uint32_t height = g_pg.tex[0].image_rect & 0xFFFFu;
    uint32_t pitch = g_pg.tex[0].control1 >> 16u;
    uint32_t format = (g_pg.tex[0].format >> 8u) & 0xFFu;
    uint32_t texture_offset = g_pg.tex[0].offset;
    /* Linear A8R8G8B8 is also used for CPU-produced dynamic images (Bink and
     * animated frontend/lab screens). Treat it as a GPU render texture only
     * when that exact video-memory offset was previously registered as a
     * render target; the pixel format alone cannot establish provenance. */
    /* Guest allocations are reused between shell and site loads.  A font
     * atlas can therefore inherit an address that was previously registered
     * as a render target.  Probe the actual live SRV once: if it is gone (or
     * is the current output), this is ordinary guest texture data and must
     * take the upload path instead of being rejected at draw time. */
    int render_texture = format == D3DFMT_LIN_A8R8G8B8 && dev &&
                         d3d8_PgraphTryBindRenderTargetTexture(0, texture_offset);
    uint32_t bytes_per_pixel = format == D3DFMT_LIN_A4R4G4B4 ? 2u : 4u;
    uint32_t min_filter = (g_pg.tex[0].filter >> 16u) & 0xFFu;
    uint32_t mag_filter = (g_pg.tex[0].filter >> 24u) & 0xFu;
    uint32_t address_u = g_pg.tex[0].address & 7u;
    uint32_t address_v = (g_pg.tex[0].address >> 8u) & 7u;
    const char *failure = NULL;
    HRESULT result;
    static unsigned rejected;
    uint32_t pixel_hash = 2166136261u;
    uint32_t vertex_hash = 2166136261u;
    float quad_min_x = FLT_MAX, quad_min_y = FLT_MAX;
    float quad_max_x = -FLT_MAX, quad_max_y = -FLT_MAX;
    int full_screen_bink = 0;
    int animation_trace = dah_ui_animation_trace_enabled() &&
                          g_pg.active_submission >= dah_ui_animation_trace_start() &&
                          !render_texture &&
                          (format == D3DFMT_LIN_A8R8G8B8 ||
                           format == D3DFMT_LIN_A4R4G4B4);
    if (!dev || g_pg.draw_mode != 6u || g_pg.index_count < 3u || g_pg.index_overflow || g_pg.inline_count)
        failure = "primitive-or-count";
    else if (!movie_shader_matches()) failure = "shader-or-combiner";
    else if ((g_pg.array_format[0] & 0xFFu) != 0x42u ||
             (g_pg.array_format[1] & 0xFFu) != 0x22u ||
             (g_pg.array_format[2] & 0xFFu) != 0x40u)
        failure = "array-layout";
    /* The observed UI uses linear A4R4G4B4 with the same vertex/combiner
     * program as Bink's X8R8G8B8. Keep the original packed16 texels and alpha;
     * the existing D3D resource layer maps them to B4G4R4A4_UNORM. */
    else if (!g_pg.tex[0].enabled ||
             (format != D3DFMT_LIN_X8R8G8B8 && format != D3DFMT_LIN_A8R8G8B8 &&
              format != D3DFMT_LIN_A4R4G4B4) ||
             ((g_pg.tex[0].format >> 16u) & 15u) != 1u ||
             ((g_pg.tex[0].format >> 4u) & 15u) != 2u ||
             !width || !height || width > 4096u || height > 4096u || pitch < width * bytes_per_pixel)
        failure = "linear-texture-layout";
    else if (address_u != 3u || address_v != 3u || min_filter != 2u || mag_filter != 2u ||
             (g_pg.tex[0].filter >> 28u))
        failure = "sampler-layout";
    else if (g_pg.color_mask != 0x01010101u || (g_pg.depth_test && (g_pg.depth_func < 0x0200u || g_pg.depth_func > 0x0207u)) ||
             (g_pg.cull_enable && g_pg.cull_face != 0x0405u) ||
             g_pg.front_face != 0x0901u || (g_pg.alpha_test && g_pg.alpha_func != 0x0204u))
        failure = "depth-cull-alpha-state";
    for (unsigned slot = 3; !failure && slot < 16u; ++slot)
        if ((g_pg.array_format[slot] >> 4u) & 15u) failure = "extra-array";
    for (unsigned stage = 1; !failure && stage < 4u; ++stage)
        if (g_pg.tex[stage].enabled) failure = "extra-texture";
    if (failure) goto reject;

    /* Retail Bink X8 frames come from the contiguous locked-video window.
     * Linear A4 and A8 UI/effect atlases are ordinary low-RAM assets.  Captures
     * of the Farm saucer particle atlas (128x128 A8 at 03591200) contain 42376
     * nonzero bytes in low RAM and an all-zero contiguous alias; choosing the
     * alias rendered its transparent cards as opaque blue-grey squares.  Live
     * A8 render targets were already handled by the provenance probe above. */
    texture_data = render_texture ? NULL : indexed_guest_bytes_window(
        texture_offset, (size_t)pitch * height,
        format == D3DFMT_LIN_X8R8G8B8);
    if (!render_texture && !texture_data) { failure = "texture-address"; goto reject; }
    /* Validate each complete referenced array span once per batch. Repeating
     * VirtualQuery for every glyph vertex adds thousands of OS queries with
     * no additional protection. Keep the same guest-window/commit guards and
     * use 64-bit arithmetic before narrowing either address or length. */
    for (uint32_t i = 0; i < g_pg.index_count; ++i) {
        if (g_pg.indices[i] < first_index) first_index = g_pg.indices[i];
        if (g_pg.indices[i] > last_index) last_index = g_pg.indices[i];
    }
    for (unsigned slot = 0; slot < 3u; ++slot) {
        uint32_t stride = g_pg.array_format[slot] >> 8u;
        size_t bytes = slot == 0 ? 16u : slot == 1 ? 8u : 4u;
        uint64_t begin = (uint64_t)g_pg.array_offset[slot] + (uint64_t)first_index * stride;
        uint64_t length = (uint64_t)(last_index - first_index) * stride + bytes;
        if (stride < bytes || begin > UINT32_MAX || length > XBOX_CONTIG_SIZE ||
            !(arrays[slot] = indexed_guest_bytes((uint32_t)begin, (size_t)length))) {
            failure = "vertex-address";
            goto reject;
        }
    }
    out = (OutputVertex *)malloc((size_t)g_pg.index_count * sizeof(*out));
    if (!out) { failure = "vertex-allocation"; goto reject; }
    /* The movie/UI FVF consumes the first 28 bytes.  Clear the extended 3D
     * fields as well so diagnostics do not mistake allocator residue for
     * changing frontend geometry. */
    memset(out, 0, (size_t)g_pg.index_count * sizeof(*out));
    for (uint32_t i = 0; i < g_pg.index_count; ++i) {
        float position[4], uv[2];
        uint32_t color;
        const uint8_t *values[3];
        for (unsigned slot = 0; slot < 3u; ++slot) {
            uint32_t stride = g_pg.array_format[slot] >> 8u;
            values[slot] = arrays[slot] + (size_t)(g_pg.indices[i] - first_index) * stride;
        }
        memcpy(position, values[0], sizeof(position));
        memcpy(uv, values[1], sizeof(uv));
        memcpy(&color, values[2], sizeof(color));
        if (g_pg.indexed_diagnostic_id <= 4u && i < 8u)
            fprintf(stderr, "[DAH-INDEXED-VERTEX] draw=%u sequence=%u index=%u pos=%.9g,%.9g,%.9g,%.9g uv=%.9g,%.9g color=%08X\n",
                    g_pg.indexed_diagnostic_id, i, g_pg.indices[i],
                    position[0], position[1], position[2], position[3], uv[0], uv[1], color);
        /* This verified movie/UI path only accepts its observed W=1 layout;
         * the host shader's wider RHW support does not widen this gate. */
        if (!isfinite(position[0]) || !isfinite(position[1]) ||
            !isfinite(position[2]) || position[2] < 0.0f || position[2] > (((g_pg.surface_format >> 4u) & 15u) == 1u ? 65535.0f : 16777215.0f) ||
            position[3] != 1.0f || !isfinite(uv[0]) || !isfinite(uv[1])) {
            failure = "position-or-perspective";
            goto reject;
        }
        out[i].x = position[0]; out[i].y = position[1];
        if (position[0] < quad_min_x) quad_min_x = position[0];
        if (position[0] > quad_max_x) quad_max_x = position[0];
        if (position[1] < quad_min_y) quad_min_y = position[1];
        if (position[1] > quad_max_y) quad_max_y = position[1];
        out[i].z = position[2] / (((g_pg.surface_format >> 4u) & 15u) == 1u ? 65535.0f : 16777215.0f); out[i].rhw = position[3];
        out[i].color = color;
        /* NV2A linear-image coordinates are texels; D3D11 uses normalized UV. */
        out[i].u = uv[0] / (float)width;
        out[i].v = uv[1] / (float)height;
    }

    /* Retail Bink frames are three rotating 640x448 X8 buffers.  They are
     * submitted as one screen-covering four-vertex strip, inset 16 pixels to
     * preserve the movie's letterbox.  X8 has no source alpha; the NV2A blend
     * state left behind by the mothership must not make those pixels reveal
     * the previous scene.  Keep animated UI/lab textures on their original
     * path by requiring the complete Bink allocation and screen geometry. */
    full_screen_bink = !render_texture && format == D3DFMT_LIN_X8R8G8B8 &&
                       width == 640u && height == 448u && pitch == 2560u &&
                       g_pg.index_count == 4u &&
                       quad_min_x <= 1.0f && quad_max_x >= 639.0f &&
                       quad_min_y <= 17.0f && quad_max_y >= 463.0f;
    if (d3d8_IsFullScreenMovieFrame() && !full_screen_bink) {
        static unsigned suppressed_indexed_reports;
        if (suppressed_indexed_reports++ < 12u)
            fprintf(stderr, "[DAH-MOVIE-SUPPRESS] submit=%u kind=indexed texture=%08X size=%ux%u vertices=%u\n",
                    g_pg.active_submission, texture_offset, width, height,
                    g_pg.index_count);
        free(out);
        return 1;
    }

    if (render_texture) goto texture_ready;
    if (!g_pg.linear_movie_texture || g_pg.linear_movie_width != width ||
        g_pg.linear_movie_height != height || g_pg.linear_movie_format != format) {
        IDirect3DTexture8 *created = NULL;
        result = dev->lpVtbl->CreateTexture(dev, width, height, 1u, 0,
                                            (D3DFORMAT)format, 0, &created);
        if (FAILED(result) || !created) { failure = "texture-create"; goto reject; }
        if (g_pg.linear_movie_texture)
            g_pg.linear_movie_texture->lpVtbl->Release(g_pg.linear_movie_texture);
        g_pg.linear_movie_texture = created;
        g_pg.linear_movie_width = width;
        g_pg.linear_movie_height = height;
        g_pg.linear_movie_format = format;
    }
    memset(&locked, 0, sizeof(locked));
    result = g_pg.linear_movie_texture->lpVtbl->LockRect(g_pg.linear_movie_texture,
                                                        0u, &locked, NULL, 0);
    if (FAILED(result)) { failure = "texture-lock"; goto reject; }
    if (!locked.pBits || locked.Pitch < (INT)(width * bytes_per_pixel)) {
        g_pg.linear_movie_texture->lpVtbl->UnlockRect(g_pg.linear_movie_texture, 0u);
        failure = "texture-lock-layout";
        goto reject;
    }
    for (uint32_t row = 0; row < height; ++row) {
        const uint8_t *source = texture_data + (size_t)row * pitch;
        memcpy((uint8_t *)locked.pBits + (size_t)row * locked.Pitch, source, width * bytes_per_pixel);
        if (g_pg.indexed_diagnostic_id <= 4u || animation_trace)
            for (uint32_t byte = 0; byte < width * bytes_per_pixel; ++byte)
                pixel_hash = (pixel_hash ^ source[byte]) * 16777619u;
    }
    result = g_pg.linear_movie_texture->lpVtbl->UnlockRect(g_pg.linear_movie_texture, 0u);
    if (FAILED(result)) { failure = "texture-upload"; goto reject; }
    if (animation_trace) {
        const uint8_t *vertex_bytes = (const uint8_t *)out;
        size_t vertex_bytes_count = (size_t)g_pg.index_count * sizeof(*out);
        typedef struct DahUiAnimationHistory { uint32_t offset, format, count, pixels, vertices; int valid; } DahUiAnimationHistory;
        static DahUiAnimationHistory history[64];
        static unsigned history_next, reports;
        DahUiAnimationHistory *entry = NULL;
        for (size_t byte = 0; byte < vertex_bytes_count; ++byte)
            vertex_hash = (vertex_hash ^ vertex_bytes[byte]) * 16777619u;
        for (unsigned i = 0; i < 64u; ++i)
            if (history[i].valid && history[i].offset == texture_offset &&
                history[i].format == format && history[i].count == g_pg.index_count) {
                entry = &history[i]; break;
            }
        if (!entry) { entry = &history[history_next++ % 64u]; memset(entry, 0, sizeof(*entry)); entry->offset = texture_offset; entry->format = format; entry->count = g_pg.index_count; }
        if (reports < 1024u && (!entry->valid || entry->pixels != pixel_hash || entry->vertices != vertex_hash)) {
            fprintf(stderr, "[DAH-UI-ANIMATION] submit=%u texture=%08X format=%u size=%ux%u pitch=%u count=%u pixels=%08X vertices=%08X changed=%s%s first=%.3f,%.3f uv=%.3f,%.3f\n",
                    g_pg.active_submission, texture_offset, format, width, height, pitch,
                    g_pg.index_count,
                    pixel_hash, vertex_hash, entry->valid && entry->pixels != pixel_hash ? "pixels" : "",
                    entry->valid && entry->vertices != vertex_hash ? "+vertices" : "",
                    out[0].x, out[0].y, out[0].u * width, out[0].v * height);
            fflush(stderr); ++reports;
        }
        entry->pixels = pixel_hash; entry->vertices = vertex_hash; entry->valid = 1;
    }

texture_ready: ;
    dev->lpVtbl->SetPixelShader(dev, 0);
    dev->lpVtbl->SetVertexShader(dev, D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
    dev->lpVtbl->SetRenderState(dev, D3DRS_ZENABLE, g_pg.depth_test);
    dev->lpVtbl->SetRenderState(dev, D3DRS_ZWRITEENABLE, g_pg.depth_write);
    dev->lpVtbl->SetRenderState(dev, D3DRS_ZFUNC, g_pg.depth_func - 0x0200u + 1u);
    dev->lpVtbl->SetRenderState(dev, D3DRS_LIGHTING, FALSE);
    dev->lpVtbl->SetRenderState(dev, D3DRS_COLORWRITEENABLE, 15u);
    dev->lpVtbl->SetRenderState(dev, D3DRS_CULLMODE, g_pg.cull_enable ? D3DCULL_CCW : D3DCULL_NONE);
    if (!dah_apply_blend_state(dev, full_screen_bink ? FALSE : g_pg.blend_enable)) {
        failure = "unsupported-blend-equation"; goto reject;
    }
    dev->lpVtbl->SetRenderState(dev, D3DRS_ALPHATESTENABLE, g_pg.alpha_test);
    dev->lpVtbl->SetRenderState(dev, D3DRS_ALPHAFUNC, D3DCMP_GREATER);
    dev->lpVtbl->SetRenderState(dev, D3DRS_ALPHAREF, g_pg.alpha_ref);
    if (!render_texture)
        dev->lpVtbl->SetTexture(dev, 0, (IDirect3DBaseTexture8 *)g_pg.linear_movie_texture);
    dev->lpVtbl->SetTextureStageState(dev, 0, D3DTSS_COLOROP, D3DTOP_MODULATE2X);
    dev->lpVtbl->SetTextureStageState(dev, 0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
    dev->lpVtbl->SetTextureStageState(dev, 0, D3DTSS_COLORARG2, D3DTA_TEXTURE);
    dev->lpVtbl->SetTextureStageState(dev, 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
    dev->lpVtbl->SetTextureStageState(dev, 0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
    dev->lpVtbl->SetTextureStageState(dev, 0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
    dev->lpVtbl->SetTextureStageState(dev, 0, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
    dev->lpVtbl->SetTextureStageState(dev, 0, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);
    dev->lpVtbl->SetTextureStageState(dev, 0, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
    dev->lpVtbl->SetTextureStageState(dev, 0, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
    dev->lpVtbl->SetTextureStageState(dev, 0, D3DTSS_MIPFILTER, D3DTEXF_NONE);
    for (unsigned stage = 1; stage < 4u; ++stage) {
        dev->lpVtbl->SetTexture(dev, stage, NULL);
        dev->lpVtbl->SetTextureStageState(dev, stage, D3DTSS_COLOROP, D3DTOP_DISABLE);
    }
    /* A live render-target SRV was already bound by the provenance probe.
     * Ordinary guest textures were uploaded and bound immediately above. */
    dev->lpVtbl->BeginScene(dev);
    result = dev->lpVtbl->DrawPrimitiveUP(dev, D3DPT_TRIANGLESTRIP,
                                          g_pg.index_count - 2u, out, sizeof(*out));
    if (FAILED(result)) { failure = "host-draw"; goto reject; }
    ++g_pg.stats.draw_calls;
    g_pg.stats.vertices_submitted += g_pg.index_count;
    if (full_screen_bink) {
        static unsigned bink_reports;
        d3d8_MarkFullScreenMovieFrameReady();
        if (bink_reports++ < 12u)
            fprintf(stderr, "[DAH-BINK-OPAQUE] submit=%u texture=%08X bounds=%.1f,%.1f..%.1f,%.1f guest-blend=%d,%X,%X\n",
                    g_pg.active_submission, texture_offset, quad_min_x, quad_min_y,
                    quad_max_x, quad_max_y, g_pg.blend_enable,
                    g_pg.blend_sfactor, g_pg.blend_dfactor);
    }
    if (g_pg.indexed_diagnostic_id <= 4u)
        fprintf(stderr, "[DAH-INDEXED-LINEAR] draw=%u vertices=%u texture=%08X size=%ux%u pitch=%u format=%02X pixel_fnv1a=%08X hr=%08lX\n",
                g_pg.indexed_diagnostic_id, g_pg.index_count, texture_offset,
                width, height, pitch, format, pixel_hash, (unsigned long)result);
    free(out);
    return 1;

reject:
    if (g_pg.active_pushbuffer && g_pg.rejected_capture_enabled) {
        g_pg.rejected_state_hash = rejected_draw_hash(failure);
        if (capture_pushbuffer(g_pg.active_pushbuffer, g_pg.active_pushbuffer_dwords,
                              g_pg.active_submission, 2)) {
            g_pg.rejected_ring_captured = 1;
            log_rejected_draw_state(failure);
            capture_rejected_resources();
        }
    }
    if (dah_ui_animation_trace_enabled()) {
        static struct { const char *reason; uint32_t offset, format; } seen[64];
        static unsigned seen_count;
        int known = 0;
        for (unsigned i = 0; i < seen_count; ++i)
            if (seen[i].reason == failure && seen[i].offset == g_pg.tex[0].offset && seen[i].format == g_pg.tex[0].format) { known = 1; break; }
        if (!known && seen_count < 64u) {
            seen[seen_count].reason = failure; seen[seen_count].offset = g_pg.tex[0].offset; seen[seen_count].format = g_pg.tex[0].format; ++seen_count;
            fprintf(stderr, "[DAH-UI-ANIMATION-REJECT] submit=%u reason=%s texture=%08X format=%08X indices=%u\n",
                    g_pg.active_submission, failure, g_pg.tex[0].offset, g_pg.tex[0].format, g_pg.index_count);
            fflush(stderr);
        }
    }
    if (rejected++ < 8u) {
        fprintf(stderr, "[DAH-INDEXED-REJECT] reason=%s draw=%u indices=%u mode=%u shader_mode=%08X shader_start=%u\n",
                failure, g_pg.indexed_diagnostic_id, g_pg.index_count, g_pg.draw_mode,
                g_pg.transform_mode, g_pg.transform_start);
        fflush(stderr);
    }
    free(out);
    return 0;
}



/* Original eight-instruction visibility probe. D3D11 point primitives have
 * fixed size, so expand the shader's oPts into an equivalent screen square. */
static int submit_visibility_points(void)
{
    static const uint32_t program[32]={0,0x00c4801b,0x0836186c,0x28b00ff8,0,0x00c4a01b,0x0836186c,0x24b00ff8,0,0x00c4c01b,0x0836186c,0x22b00ff8,0,0x00c4e01b,0x0836186c,0x21b01800,0,0x00200200,0x0836106c,0x20708830,0,0x0640401b,0xb4361bfe,0xd018e800,0,0x0037601b,0x0c36106c,0x2070f818,0,0x0080201b,0xc400286c,0x3070e801};
    if(g_pg.draw_mode!=1 || g_pg.inline_count!=4 || g_pg.color_mask || g_pg.depth_write || (g_pg.transform_mode&3)!=2 || g_pg.transform_start>128)return 0;
    unsigned start=g_pg.transform_start*4;
    for(unsigned k=0;k<32;k++)if(!g_pg.transform_valid[start+k] || g_pg.transform_program[start+k]!=program[k])return 0;
    const float (*c)[4]=(const float(*)[4])g_pg.transform_constants;
    float p[3],clip[4];memcpy(p,g_pg.inline_data,12);float size=u2f(g_pg.inline_data[3]);
    if(!isfinite(size)||size<=0 || size>64)return 0;
    for(unsigned j=0;j<4;j++){for(unsigned k=0;k<4;k++)if(!g_pg.transform_constant_valid[(36+j)*4+k])return 0;clip[j]=dah_menu_dot3(p,c[36+j])+c[36+j][3];}
    if(!isfinite(clip[3]) || clip[3]<=0)return 0;
    float r=dah_menu_rcc(clip[3]),x=clip[0]*c[2][0]*r+c[1][0],y=clip[1]*c[2][1]*r+c[1][1];
    float z=(clip[2]*c[2][2]*r+c[1][2])/(((g_pg.surface_format>>4)&15)==1?65535.f:16777215.f);
    if(!isfinite(x)||!isfinite(y)||!isfinite(z)||z<0||z>1)return 0;
    OutputVertex v[4]={0};for(unsigned i=0;i<4;i++){v[i].x=x+((i&1)?size*.5f:-size*.5f);v[i].y=y+((i&2)?size*.5f:-size*.5f);v[i].z=z;v[i].rhw=r;v[i].color=0xffffffff;}
    IDirect3DDevice8 *dev=xbox_GetD3DDevice();if(!dev)return 0;
    dev->lpVtbl->SetPixelShader(dev,0);dev->lpVtbl->SetVertexShader(dev,D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1);
    dev->lpVtbl->SetRenderState(dev,D3DRS_ZENABLE,g_pg.depth_test);dev->lpVtbl->SetRenderState(dev,D3DRS_ZWRITEENABLE,FALSE);dev->lpVtbl->SetRenderState(dev,D3DRS_ZFUNC,g_pg.depth_func-0x200+1);
    dev->lpVtbl->SetRenderState(dev,D3DRS_COLORWRITEENABLE,0);dev->lpVtbl->SetRenderState(dev,D3DRS_CULLMODE,D3DCULL_NONE);dev->lpVtbl->SetRenderState(dev,D3DRS_ALPHATESTENABLE,FALSE);dev->lpVtbl->SetRenderState(dev,D3DRS_ALPHABLENDENABLE,FALSE);dev->lpVtbl->SetRenderState(dev,D3DRS_LIGHTING,FALSE);
    for(unsigned t=0;t<4;t++){dev->lpVtbl->SetTexture(dev,t,NULL);dev->lpVtbl->SetTextureStageState(dev,t,D3DTSS_COLOROP,t?D3DTOP_DISABLE:D3DTOP_SELECTARG1);}dev->lpVtbl->SetTextureStageState(dev,0,D3DTSS_COLORARG1,D3DTA_DIFFUSE);
    dev->lpVtbl->BeginScene(dev);HRESULT hr=dev->lpVtbl->DrawPrimitiveUP(dev,D3DPT_TRIANGLESTRIP,2,v,sizeof(*v));
    if(FAILED(hr))return 0;++g_pg.stats.draw_calls;g_pg.stats.vertices_submitted+=4;
    static unsigned n;if(n++<6)fprintf(stderr,"[DAH-VISIBILITY] center=%.4f,%.4f depth=%.7f size=%.3f\n",x,y,z,size);return 1;
}

/* Retail screen-space MOV and four-tap ADD programs. Textures are actual
 * rendered surfaces; no image substitution or guessed guest-memory contents. */
static uint32_t dah_pass_trace_submission(void);
static int submit_postprocess(void)
{
    static const uint32_t mov[16]={0,0x0020001b,0x0836106c,0x2070f800,0,0x0020021b,0x0836106c,0x2070f848,0,0x0020041b,0x0836106c,0x2070f818,0,0x00376000,0x0c36106c,0x2070f829};
    static const uint32_t blur[28]={0,0x0020001b,0x0836106c,0x2070f800,0,0x006ac21b,0x0836106c,0x3070f848,0,0x006ae21b,0x0836106c,0x3070f850,0,0x006b021b,0x0836106c,0x3070f858,0,0x006b221b,0x0836106c,0x3070f860,0,0x0020041b,0x0836106c,0x2070f818,0,0x00376000,0x0c36106c,0x2070f829};
    IDirect3DDevice8 *dev=xbox_GetD3DDevice();
    if(!dev || g_pg.draw_mode!=6 || g_pg.index_count<3 || g_pg.index_overflow || (g_pg.transform_mode&3)!=2 || g_pg.transform_start>129) return 0;
    uint32_t first=g_pg.transform_start*4;int isblur=!memcmp(g_pg.transform_program+first,blur,sizeof(blur));
    if(!isblur && memcmp(g_pg.transform_program+first,mov,sizeof(mov)))return 0;
    for(unsigned i=0;i<(unsigned)(isblur?28u:16u);i++)if(!g_pg.transform_valid[first+i])return 0;
    if((g_pg.array_format[0]&255)!=0x42 || (g_pg.array_format[1]&255)!=0x22 || (g_pg.array_format[2]&255)!=0x40)return 0;
    for(unsigned i=3;i<16;i++)if((g_pg.array_format[i]>>4)&15)return 0;
    if(g_pg.color_mask!=0x01010101u)return 0;
    /* Retail greyscale/menu pass: linear scene in T0, swizzled color
     * table in T1, addressed by T0.ar (NV2A DPNDNT_AR). */
    int dependent_ar=!isblur && g_pg.shader_stage_program==0x1e1u &&
        g_pg.tex[0].enabled && g_pg.tex[1].enabled &&
        !g_pg.tex[2].enabled && !g_pg.tex[3].enabled &&
        g_pg.tex[1].format==0x08013a29u;
    unsigned active=0;
    for(unsigned t=0;t<4;t++)if(g_pg.tex[t].enabled){
        unsigned fmt=(g_pg.tex[t].format>>8)&255;
        if(dependent_ar && t==1u){
            if((g_pg.tex[t].format&4u)!=0u)return 0;
        }else{
            if(fmt!=0x12 && fmt!=0x1e)return 0;
            if(!g_pg.tex[t].image_rect || !(g_pg.tex[t].image_rect>>16))return 0;
        }
        if((g_pg.tex[t].address&7)!=3 || ((g_pg.tex[t].address>>8)&7)!=3)return 0;
        active++;
    }
    if(!isblur && !dependent_ar && active>1)return 0;
    if(isblur)for(unsigned k=86*4;k<90*4;k++)if(!g_pg.transform_constant_valid[k])return 0;
    uint32_t lo=UINT32_MAX,hi=0;for(unsigned i=0;i<g_pg.index_count;i++){if(g_pg.indices[i]<lo)lo=g_pg.indices[i];if(g_pg.indices[i]>hi)hi=g_pg.indices[i];}
    const uint8_t *arr[3];
    for(unsigned a=0;a<3;a++){
        unsigned stride=g_pg.array_format[a]>>8,bytes=a==0?16:a==1?8:4;
        uint64_t begin=(uint64_t)g_pg.array_offset[a]+(uint64_t)lo*stride,length=(uint64_t)(hi-lo)*stride+bytes;
        if(stride<bytes || begin>UINT32_MAX || length>XBOX_CONTIG_SIZE || !(arr[a]=indexed_guest_bytes((uint32_t)begin,(size_t)length)))return 0;
    }
    typedef struct {float x,y,z,w;uint32_t color;float uv[4][2];} PostVertex;
    PostVertex *v=malloc(g_pg.index_count*sizeof(*v));if(!v)return 0;
    const float (*c)[4]=(const float(*)[4])g_pg.transform_constants;
    float zmax=((g_pg.surface_format>>4)&15)==1?65535.f:16777215.f;
    for(unsigned i=0;i<g_pg.index_count;i++){
        unsigned n=g_pg.indices[i]-lo;float pos[4],uv[2];
        memcpy(pos,arr[0]+n*(g_pg.array_format[0]>>8),16);memcpy(uv,arr[1]+n*(g_pg.array_format[1]>>8),8);
        if(!isfinite(pos[0])||!isfinite(pos[1])||!isfinite(pos[2])||pos[3]!=1 || !isfinite(uv[0])||!isfinite(uv[1])){free(v);return 0;}
        v[i].x=pos[0];v[i].y=pos[1];v[i].z=pos[2]/zmax;v[i].w=1;
        memcpy(&v[i].color,arr[2]+n*(g_pg.array_format[2]>>8),4);
        for(unsigned t=0;t<4;t++){float w=g_pg.tex[t].image_rect>>16,h=g_pg.tex[t].image_rect&65535;
            v[i].uv[t][0]=(uv[0]+(isblur?c[86+t][0]:0))/(w?w:1);
            v[i].uv[t][1]=(uv[1]+(isblur?c[86+t][1]:0))/(h?h:1);
        }
    }
    dev->lpVtbl->SetVertexShader(dev,D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX4);
    dev->lpVtbl->SetRenderState(dev,D3DRS_ZENABLE,g_pg.depth_test);
    dev->lpVtbl->SetRenderState(dev,D3DRS_ZWRITEENABLE,g_pg.depth_write);
    dev->lpVtbl->SetRenderState(dev,D3DRS_ZFUNC,g_pg.depth_func-0x200+1);
    dev->lpVtbl->SetRenderState(dev,D3DRS_LIGHTING,FALSE);
    dev->lpVtbl->SetRenderState(dev,D3DRS_COLORWRITEENABLE,15);
    dev->lpVtbl->SetRenderState(dev,D3DRS_CULLMODE,g_pg.cull_enable?D3DCULL_CCW:D3DCULL_NONE);
    if(!dah_apply_blend_state(dev,g_pg.blend_enable)){free(v);return 0;}
    dev->lpVtbl->SetRenderState(dev,D3DRS_ALPHATESTENABLE,g_pg.alpha_test);
    dev->lpVtbl->SetRenderState(dev,D3DRS_ALPHAFUNC,g_pg.alpha_func-0x200+1);
    dev->lpVtbl->SetRenderState(dev,D3DRS_ALPHAREF,g_pg.alpha_ref);
    for(unsigned t=0;t<4;t++){
        dev->lpVtbl->SetTexture(dev,t,NULL);
        dev->lpVtbl->SetTextureStageState(dev,t,D3DTSS_ADDRESSU,D3DTADDRESS_CLAMP);
        dev->lpVtbl->SetTextureStageState(dev,t,D3DTSS_ADDRESSV,D3DTADDRESS_CLAMP);
        dev->lpVtbl->SetTextureStageState(dev,t,D3DTSS_MINFILTER,D3DTEXF_LINEAR);
        dev->lpVtbl->SetTextureStageState(dev,t,D3DTSS_MAGFILTER,D3DTEXF_LINEAR);
        if(g_pg.tex[t].enabled){
            HRESULT bind_result;
            if(dependent_ar && t==1u){
                /* 001A2E60 creates this 1x256 table; 001A30E0 updates it
                 * through LockRect -> 001E07C0, which ORs Data with
                 * 80000000. This generated resource has contiguous backing. */
                IDirect3DTexture8 *table=dah_mesh_texture_window(t,dev,1);
                bind_result=table?dev->lpVtbl->SetTexture(dev,t,(IDirect3DBaseTexture8*)table):E_FAIL;
            }else if(d3d8_PgraphTryBindRenderTargetTextureSized(t,
                     g_pg.tex[t].offset, g_pg.tex[t].image_rect >> 16u,
                     g_pg.tex[t].image_rect & 0xFFFFu)){
                bind_result=S_OK;
            }else{
                /* Effect and HUD quads can share this screen-space vertex
                 * shape while sampling an ordinary Xbox texture.  Treating
                 * every such draw as render-target feedback discarded the
                 * abducto ground marker, transition overlays, and
                 * hologram/projector layers. */
                IDirect3DTexture8 *texture=dah_mesh_texture(t,dev);
                bind_result=texture ? dev->lpVtbl->SetTexture(dev,t,
                    (IDirect3DBaseTexture8*)texture) : E_FAIL;
            }
            if(FAILED(bind_result)){
                if(dah_ui_animation_trace_enabled() &&
                   g_pg.active_submission>=dah_ui_animation_trace_start()){
                    static unsigned reports;
                    if(reports++<32u)fprintf(stderr,
                        "[DAH-POSTPROCESS-REJECT] submit=%u blur=%d target=%08X stage=%u texture=%08X hr=%08lX active=%u\n",
                        g_pg.active_submission,isblur,g_pg.surface_color_offset,t,
                        g_pg.tex[t].offset,(unsigned long)bind_result,active);
                }
                free(v);return 0;
            }
        }
    }
    if(!active && g_pg.active_submission%150==0)fprintf(stderr,"[DAH-COMPOSITE] frame=%u xy=%.1f,%.1f..%.1f,%.1f color=%08X factor0=%08X blend=%u,%X,%X stages=%08X\n",g_pg.active_submission,v[0].x,v[0].y,v[3].x,v[3].y,v[0].color,g_pg.factor0[0],g_pg.blend_enable,g_pg.blend_sfactor,g_pg.blend_dfactor,g_pg.combiner_control);
    if(!active && dah_ui_animation_trace_enabled() &&
       g_pg.active_submission>=dah_ui_animation_trace_start()){
        static unsigned reports;
        if(reports++<512u)fprintf(stderr,
            "[DAH-COMPOSITE-TRACE] submit=%u target=%08X xy=%.1f,%.1f..%.1f,%.1f "
            "colors=%08X,%08X,%08X,%08X factor0=%08X blend=%u,%X,%X,%X "
            "depth=%u,%X,%u combiner=%08X final=%08X,%08X\n",
            g_pg.active_submission,g_pg.surface_color_offset,
            v[0].x,v[0].y,v[3].x,v[3].y,
            v[0].color,v[1].color,v[2].color,v[3].color,g_pg.factor0[0],
            g_pg.blend_enable,g_pg.blend_sfactor,g_pg.blend_dfactor,g_pg.blend_equation,
            g_pg.depth_test,g_pg.depth_func,g_pg.depth_write,g_pg.combiner_control,
            g_pg.final_cw0,g_pg.final_cw1);
    }
    d3d8_combiners_set_nv2a(g_pg.combiner_control,g_pg.shader_stage_program,g_pg.color_icw,g_pg.color_ocw,g_pg.alpha_icw,g_pg.alpha_ocw,g_pg.factor0,g_pg.factor1,g_pg.final_cw0,g_pg.final_cw1);
    d3d8_combiners_set_texture_alpha_one_mask(dah_texture_alpha_one_mask());
    d3d8_combiners_set_vertex_fog_constant(dah_transform_fog(c[187][0]));
    if(dependent_ar && dah_ui_animation_trace_enabled()){
        static unsigned reports;
        if(reports++<4u){
            if(reports==1u)capture_indexed_resource("lut",g_pg.tex[1].offset,1024u);
            uint32_t lut[4]={0};
            const uint8_t *source=indexed_guest_bytes_window(g_pg.tex[1].offset,1024u,1);
            if(source){memcpy(&lut[0],source,4);memcpy(&lut[1],source+256u,4);memcpy(&lut[2],source+512u,4);memcpy(&lut[3],source+1020u,4);}
            fprintf(stderr,"[DAH-POSTPROCESS-LUT] submit=%u target=%08X scene=%08X table=%08X format=%08X rect=%08X,%08X filter=%08X,%08X samples=%08X,%08X,%08X,%08X depth=%u,%X,%u cull=%u xy=%.1f,%.1f z=%g color=%08X combiner=%08X rgb=%08X/%08X alpha=%08X/%08X factor=%08X/%08X final=%08X,%08X\n",
                g_pg.active_submission,g_pg.surface_color_offset,g_pg.tex[0].offset,g_pg.tex[1].offset,g_pg.tex[1].format,
                g_pg.tex[0].image_rect,g_pg.tex[1].image_rect,g_pg.tex[0].filter,g_pg.tex[1].filter,
                lut[0],lut[1],lut[2],lut[3],g_pg.depth_test,g_pg.depth_func,g_pg.depth_write,g_pg.cull_enable,
                v[0].x,v[0].y,v[0].z,v[0].color,g_pg.combiner_control,
                g_pg.color_icw[0],g_pg.color_ocw[0],g_pg.alpha_icw[0],g_pg.alpha_ocw[0],
                g_pg.factor0[0],g_pg.factor1[0],g_pg.final_cw0,g_pg.final_cw1);
        }
    }
    if(dah_pass_trace_submission() && g_pg.active_submission==dah_pass_trace_submission()){
        static unsigned reports;
        if(reports++<512u)fprintf(stderr,
            "[DAH-PASS-POSTPROCESS] sub=%u target=%08X blur=%d color=%08X uv=%.9g,%.9g factor0=%08X alpha_one_mask=%X\n",
            g_pg.active_submission,g_pg.surface_color_offset,isblur,v[0].color,
            v[0].uv[0][0],v[0].uv[0][1],g_pg.factor0[0],dah_texture_alpha_one_mask());
    }
    dev->lpVtbl->BeginScene(dev);
    HRESULT hr=dev->lpVtbl->DrawPrimitiveUP(dev,D3DPT_TRIANGLESTRIP,g_pg.index_count-2,v,sizeof(*v));free(v);
    if(FAILED(hr))return 0;
    ++g_pg.stats.draw_calls;g_pg.stats.vertices_submitted+=g_pg.index_count;
    static unsigned logged;if(logged++<12)fprintf(stderr,"[DAH-POSTPROCESS] blur=%d textures=%u target=%08X\n",isblur,active,g_pg.surface_color_offset);
    return 1;
}

static double dah_profile_ms(void) { LARGE_INTEGER t,f; QueryPerformanceCounter(&t);QueryPerformanceFrequency(&f);return (double)t.QuadPart*1000.0/(double)f.QuadPart; }

/* Retail fullscreen colour/grade passes also arrive through INLINE_ARRAY.
 * Their declaration is float4 position, float2 UV, packed colour: seven
 * dwords per vertex.  The old menu fallback forced every inline packet to a
 * five-dword XY/UV/colour layout, truncated 28 dwords to five fake vertices,
 * and promoted packed colours such as FF7F7F7F into screen coordinates. */
static int submit_inline_screen_mov(void)
{
    static const uint32_t mov[16]={
        0,0x0020001b,0x0836106c,0x2070f800,
        0,0x0020021b,0x0836106c,0x2070f848,
        0,0x0020041b,0x0836106c,0x2070f818,
        0,0x00376000,0x0c36106c,0x2070f829
    };
    if (g_pg.draw_mode != 6u || g_pg.inline_count != 28u ||
        (g_pg.transform_mode & 3u) != 2u || g_pg.transform_start > 132u ||
        g_pg.array_format[0] != 0x42u ||
        g_pg.array_format[1] != 0x22u ||
        g_pg.array_format[2] != 0x40u)
        return 0;
    uint32_t first = g_pg.transform_start * 4u;
    for (unsigned i = 0; i < 16u; ++i)
        if (!g_pg.transform_valid[first+i] ||
            g_pg.transform_program[first+i] != mov[i])
            return 0;
    for (unsigned i = 3u; i < 16u; ++i)
        if ((g_pg.array_format[i] >> 4u) & 15u)
            return 0;
    for (unsigned i = 1u; i < 4u; ++i)
        if (g_pg.tex[i].enabled)
            return 0;
    float texture_width = 1.0f, texture_height = 1.0f;
    if (g_pg.tex[0].enabled) {
        uint32_t width = g_pg.tex[0].image_rect >> 16u;
        uint32_t height = g_pg.tex[0].image_rect & 0xFFFFu;
        if (!width || !height) return 0;
        texture_width = (float)width;
        texture_height = (float)height;
    }

    OutputVertex v[4] = {0};
    for (unsigned i = 0; i < 4u; ++i) {
        const uint32_t *source = g_pg.inline_data + i * 7u;
        v[i].x = u2f(source[0]); v[i].y = u2f(source[1]);
        v[i].z = u2f(source[2]); v[i].rhw = u2f(source[3]);
        v[i].u = u2f(source[4]) / texture_width;
        v[i].v = u2f(source[5]) / texture_height;
        v[i].color = source[6]; v[i].fog_coord = 1.0f;
        if (!isfinite(v[i].x) || !isfinite(v[i].y) ||
            !isfinite(v[i].z) || !isfinite(v[i].rhw) ||
            !isfinite(v[i].u) || !isfinite(v[i].v) ||
            v[i].z < 0.0f || v[i].z > 1.0f || v[i].rhw <= 0.0f)
            return 0;
    }

    IDirect3DDevice8 *dev = xbox_GetD3DDevice();
    if (!dev) return 0;
    dev->lpVtbl->SetPixelShader(dev,0);
    dev->lpVtbl->SetVertexShader(dev,D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1);
    dev->lpVtbl->SetRenderState(dev,D3DRS_ZENABLE,g_pg.depth_test);
    dev->lpVtbl->SetRenderState(dev,D3DRS_ZWRITEENABLE,g_pg.depth_write);
    dev->lpVtbl->SetRenderState(dev,D3DRS_ZFUNC,
        g_pg.depth_func>=0x0200u && g_pg.depth_func<=0x0207u ?
        g_pg.depth_func-0x0200u+1u : D3DCMP_LESSEQUAL);
    dev->lpVtbl->SetRenderState(dev,D3DRS_LIGHTING,FALSE);
    dev->lpVtbl->SetRenderState(dev,D3DRS_COLORWRITEENABLE,
        dah_nv2a_color_write_mask(g_pg.color_mask));
    dev->lpVtbl->SetRenderState(dev,D3DRS_CULLMODE,g_pg.cull_enable ?
        ((g_pg.front_face==0x0901u)==(g_pg.cull_face==0x0405u) ?
         D3DCULL_CCW : D3DCULL_CW) : D3DCULL_NONE);
    if (!dah_apply_blend_state(dev,g_pg.blend_enable)) return 0;
    dev->lpVtbl->SetRenderState(dev,D3DRS_ALPHATESTENABLE,g_pg.alpha_test);
    dev->lpVtbl->SetRenderState(dev,D3DRS_ALPHAFUNC,
        g_pg.alpha_func>=0x0200u && g_pg.alpha_func<=0x0207u ?
        g_pg.alpha_func-0x0200u+1u : D3DCMP_ALWAYS);
    dev->lpVtbl->SetRenderState(dev,D3DRS_ALPHAREF,g_pg.alpha_ref);
    for (unsigned stage=0;stage<4u;++stage) {
        dev->lpVtbl->SetTexture(dev,stage,NULL);
        dev->lpVtbl->SetTextureStageState(dev,stage,D3DTSS_COLOROP,
            stage ? D3DTOP_DISABLE : D3DTOP_SELECTARG1);
        if (!stage) {
            dev->lpVtbl->SetTextureStageState(dev,stage,D3DTSS_COLORARG1,D3DTA_DIFFUSE);
            dev->lpVtbl->SetTextureStageState(dev,stage,D3DTSS_ALPHAOP,D3DTOP_SELECTARG1);
            dev->lpVtbl->SetTextureStageState(dev,stage,D3DTSS_ALPHAARG1,D3DTA_DIFFUSE);
        }
    }
    if (g_pg.tex[0].enabled) {
        if (!d3d8_PgraphTryBindRenderTargetTextureSized(0,
                g_pg.tex[0].offset, g_pg.tex[0].image_rect >> 16u,
                g_pg.tex[0].image_rect & 0xFFFFu)) {
            IDirect3DTexture8 *texture=dah_mesh_texture(0,dev);
            if (!texture || FAILED(dev->lpVtbl->SetTexture(dev,0,
                    (IDirect3DBaseTexture8*)texture)))
                return 0;
        }
        dev->lpVtbl->SetTextureStageState(dev,0,D3DTSS_ADDRESSU,D3DTADDRESS_CLAMP);
        dev->lpVtbl->SetTextureStageState(dev,0,D3DTSS_ADDRESSV,D3DTADDRESS_CLAMP);
        dev->lpVtbl->SetTextureStageState(dev,0,D3DTSS_MINFILTER,D3DTEXF_LINEAR);
        dev->lpVtbl->SetTextureStageState(dev,0,D3DTSS_MAGFILTER,D3DTEXF_LINEAR);
        dev->lpVtbl->SetTextureStageState(dev,0,D3DTSS_MIPFILTER,D3DTEXF_NONE);
    }
    d3d8_combiners_set_nv2a(g_pg.combiner_control,g_pg.shader_stage_program,
        g_pg.color_icw,g_pg.color_ocw,g_pg.alpha_icw,g_pg.alpha_ocw,
        g_pg.factor0,g_pg.factor1,g_pg.final_cw0,g_pg.final_cw1);
    d3d8_combiners_set_texture_alpha_one_mask(dah_texture_alpha_one_mask());
    d3d8_combiners_set_vertex_fog_constant(dah_transform_fog(
        g_pg.transform_constant_valid[187u*4u] ?
        u2f(g_pg.transform_constants[187u*4u]) : 1.0f));
    dev->lpVtbl->BeginScene(dev);
    HRESULT hr=dev->lpVtbl->DrawPrimitiveUP(dev,D3DPT_TRIANGLESTRIP,2u,v,sizeof(*v));
    if (FAILED(hr)) return 0;
    ++g_pg.stats.draw_calls;g_pg.stats.vertices_submitted+=4u;
    static unsigned reports;
    if (reports++ < 8u)
        fprintf(stderr,"[DAH-INLINE-SCREEN-MOV] sub=%u target=%08X texture=%u:%08X color=%08X z=%g rhw=%g\n",
            g_pg.active_submission,g_pg.surface_color_offset,g_pg.tex[0].enabled,
            g_pg.tex[0].offset,v[0].color,v[0].z,v[0].rhw);
    return 1;
}

static void submit_draw_inner(void)
{
    if(!g_pg.active_pushbuffer) {
        dah_read_region_count=0;
        if(dah_memory_window_profile_enabled() && dah_window_profile.reports<40u)++dah_window_profile.direct_resets;
    }
    int dah_runtime_profile = dah_runtime_profile_enabled();
    double t0=dah_runtime_profile ? dah_profile_ms() : 0.0;
    dah_bind_current_surface();
    dah_apply_stencil_state(xbox_GetD3DDevice());
    if (d3d8_IsFullScreenMovieFrame()) {
        if (g_pg.index_count || g_pg.index_overflow)
            (void)submit_indexed_movie();
        else {
            static unsigned suppressed_inline_reports;
            if (suppressed_inline_reports++ < 12u)
                fprintf(stderr, "[DAH-MOVIE-SUPPRESS] submit=%u kind=inline vertices=%u\n",
                        g_pg.active_submission, g_pg.inline_count);
        }
        return;
    }
    if(submit_visibility_points())return;
    if (g_pg.index_count || g_pg.index_overflow) {
        double t1=dah_runtime_profile ? dah_profile_ms() : 0.0,t2,t3;
        /* Preserve the retail/stable classification order. Ordinary menu
         * sprites share the MOV program used by the fullscreen compositor;
         * the indexed renderer must get first refusal so those sprites do not
         * overwrite render targets with stale full-frame content. */
        int ok=submit_indexed_3d();t2=dah_runtime_profile ? dah_profile_ms() : 0.0;
        if (!ok) ok=submit_postprocess();
        if (!ok) submit_indexed_movie();t3=dah_runtime_profile ? dah_profile_ms() : 0.0;
        if (dah_runtime_profile) {static double bind_ms,mesh_ms,movie_ms;static unsigned count;
            bind_ms+=t1-t0;mesh_ms+=t2-t1;movie_ms+=t3-t2;
            if(++count==2000) {fprintf(stderr,"[DAH-DRAW-PROFILE] count=%u bind=%.3f mesh=%.3f ui=%.3f ms\n",count,bind_ms,mesh_ms,movie_ms);count=0;bind_ms=mesh_ms=movie_ms=0;}}
        return;
    }
    if (g_pg.inline_count == 0 || g_pg.vert_stride == 0)
        return;
    /* This exact 28-dword MOV packet is four float4/float2/colour vertices.
     * Letting the five-dword fallback consume it creates a fifth garbage
     * vertex and black tiles around projected effects. */
    if (submit_inline_screen_mov()) return;

    uint32_t num_verts = g_pg.inline_count / g_pg.vert_stride;
    if (num_verts < 3)
        return;

    const uint32_t *src = g_pg.inline_data;
    int actual_prim_type = g_pg.d3d_prim_type;
    uint32_t out_vert_count = num_verts;

    /* Handle QUADS (mode 8): convert to triangle list (6 verts per quad) */
    int is_quads = (g_pg.draw_mode == 8);
    uint32_t num_quads = is_quads ? (num_verts / 4) : 0;
    if (is_quads) {
        out_vert_count = num_quads * 6;  /* 2 triangles per quad */
        actual_prim_type = D3DPT_TRIANGLELIST;
    }

    /* Calculate primitive count */
    uint32_t prim_count = 0;
    switch (actual_prim_type) {
        case D3DPT_TRIANGLELIST:  prim_count = out_vert_count / 3; break;
        case D3DPT_TRIANGLESTRIP: prim_count = out_vert_count - 2; break;
        case D3DPT_TRIANGLEFAN:   prim_count = out_vert_count - 2; break;
        case D3DPT_LINELIST:      prim_count = out_vert_count / 2; break;
        case D3DPT_LINESTRIP:     prim_count = out_vert_count - 1; break;
        default: prim_count = out_vert_count / 3; break;
    }
    if (prim_count == 0)
        return;

    /* Convert inline vertices to OutputVertex (28 bytes) */
    OutputVertex *out = (OutputVertex *)_alloca(out_vert_count * sizeof(OutputVertex));

    /* Helper to convert one inline vertex */
    #define CONVERT_VERT(dst_idx, src_idx) do { \
        uint32_t _b = (src_idx) * g_pg.vert_stride; \
        out[dst_idx].x     = u2f(src[_b + 0]); \
        out[dst_idx].y     = u2f(src[_b + 1]); \
        out[dst_idx].z     = 0.0f; \
        out[dst_idx].rhw   = 1.0f; \
        out[dst_idx].u     = u2f(src[_b + 2]); \
        out[dst_idx].v     = u2f(src[_b + 3]); \
        out[dst_idx].color = src[_b + 4]; \
    } while(0)

    if (is_quads) {
        /* Convert quads (v0,v1,v2,v3) → two triangles (v0,v1,v2), (v0,v2,v3) */
        uint32_t out_idx = 0;
        for (uint32_t q = 0; q < num_quads; q++) {
            uint32_t qi = q * 4;
            CONVERT_VERT(out_idx + 0, qi + 0);  /* tri 1: v0 */
            CONVERT_VERT(out_idx + 1, qi + 1);  /* tri 1: v1 */
            CONVERT_VERT(out_idx + 2, qi + 2);  /* tri 1: v2 */
            CONVERT_VERT(out_idx + 3, qi + 0);  /* tri 2: v0 */
            CONVERT_VERT(out_idx + 4, qi + 2);  /* tri 2: v2 */
            CONVERT_VERT(out_idx + 5, qi + 3);  /* tri 2: v3 */
            out_idx += 6;
        }
    } else {
        for (uint32_t i = 0; i < num_verts; i++) {
            CONVERT_VERT(i, i);
        }
    }
    #undef CONVERT_VERT

    /* Diagnostic for the malformed five-vertex Farm strip seen in the GPU
     * capture.  INLINE_ARRAY can carry programmable-vertex inputs; the old
     * fallback always interpreting it as five pre-transformed 2D dwords is
     * therefore suspect.  Record both the active program and the exact guest
     * words without changing submission. */
    int malformed_inline_five = 0;
    if (num_verts == 5u) {
        for (uint32_t i = 0; i < num_verts; ++i) {
            if (!isfinite(out[i].x) || !isfinite(out[i].y) ||
                !isfinite(out[i].u) || !isfinite(out[i].v) ||
                fabsf(out[i].x) > 1000000.0f ||
                fabsf(out[i].y) > 1000000.0f ||
                fabsf(out[i].u) > 1000000.0f ||
                fabsf(out[i].v) > 1000000.0f) {
                malformed_inline_five = 1;
                break;
            }
        }
    }
    if (dah_ui_animation_trace_enabled() && malformed_inline_five) {
        static unsigned reports, gray_reports;
        int gray = g_pg.inline_count >= 7u &&
                   g_pg.inline_data[6] == 0xFF7F7F7Fu;
        if ((gray && gray_reports++ < 16u) || (!gray && reports++ < 64u)) {
            uint32_t first = g_pg.transform_start <= 129u ?
                g_pg.transform_start * 4u : 0u;
            fprintf(stderr,
                "[DAH-INLINE-FIVE] sub=%u mode=%u prim=%d dwords=%u stride=%u "
                "transform=%u,%u target=%08X tex0=%u:%08X:%08X tex1=%u:%08X:%08X "
                "arrays=%08X,%08X,%08X,%08X combiner=%08X stage=%08X program=",
                g_pg.active_submission, g_pg.draw_mode, actual_prim_type,
                g_pg.inline_count, g_pg.vert_stride, g_pg.transform_mode,
                g_pg.transform_start, g_pg.surface_color_offset,
                g_pg.tex[0].enabled, g_pg.tex[0].format,
                g_pg.tex[0].image_rect, g_pg.tex[1].enabled,
                g_pg.tex[1].format, g_pg.tex[1].image_rect,
                g_pg.array_format[0], g_pg.array_format[1],
                g_pg.array_format[2], g_pg.array_format[3],
                g_pg.combiner_control,g_pg.shader_stage_program);
            for (unsigned i = 0; i < 36u; ++i)
                fprintf(stderr, "%s%08X", i ? "," : "",
                        g_pg.transform_program[first + i]);
            fprintf(stderr, " raw=");
            for (uint32_t i = 0; i < g_pg.inline_count; ++i)
                fprintf(stderr, "%s%08X", i ? "," : "", src[i]);
            fprintf(stderr, " out=");
            for (uint32_t i = 0; i < num_verts; ++i)
                fprintf(stderr,
                    "%s[%.9g,%.9g,%.9g,%.9g,%08X,%.9g,%.9g]",
                    i ? "," : "", out[i].x, out[i].y, out[i].z,
                    out[i].rhw, out[i].color, out[i].u, out[i].v);
            fputc('\n', stderr);
            fflush(stderr);
        }
    }

    /* Chyron scroll: shift X for vertices in the chyron Y band (366-382).
     * Simple continuous scroll — no per-vertex wrapping to avoid artifacts
     * from split triangle-strip quads spanning the screen. */
    if (g_pg.chyron_scroll_offset != 0.0f && out_vert_count >= 6) {
        /* Check if this draw is in the chyron band */
        int is_chyron = 1;
        for (uint32_t i = 0; i < (out_vert_count < 8 ? out_vert_count : 8); i++) {
            if (out[i].y < 360.0f || out[i].y > 390.0f) {
                is_chyron = 0;
                break;
            }
        }
        if (is_chyron) {
            /* Find the total text width */
            float min_x = 9999.0f, max_x = -9999.0f;
            for (uint32_t i = 0; i < out_vert_count; i++) {
                if (out[i].x < min_x) min_x = out[i].x;
                if (out[i].x > max_x) max_x = out[i].x;
            }
            float text_width = max_x - min_x;

            /* Scroll loops: text slides left, then resets to start position.
             * Total cycle = text scrolls fully off-left + re-enters from right. */
            float cycle = text_width + 640.0f;
            float scroll = fmodf(g_pg.chyron_scroll_offset, cycle);

            /* Apply uniform shift to ALL vertices (no per-vertex wrap) */
            for (uint32_t i = 0; i < out_vert_count; i++) {
                out[i].x -= scroll;
            }
        }
    }

    /* Log first few draws' vertex positions (once) */
    if (g_pg.stats.draw_calls < 3 && num_verts >= 3) {
        fprintf(stderr, "[PGRAPH-D3D11] Draw verts (mode=%u, %u in → %u out):\n",
                g_pg.draw_mode, num_verts, out_vert_count);
        uint32_t show = num_verts < 8 ? num_verts : 8;
        for (uint32_t i = 0; i < show; i++) {
            uint32_t b = i * g_pg.vert_stride;
            fprintf(stderr, "  [%u] pos=(%.1f, %.1f) uv=(%.3f, %.3f) color=0x%08X\n",
                    i, u2f(src[b+0]), u2f(src[b+1]), u2f(src[b+2]), u2f(src[b+3]), src[b+4]);
        }
    }

    /* Get D3D8 device */
    IDirect3DDevice8 *dev = xbox_GetD3DDevice();
    if (!dev) return;

    /* Restore this draw's channel enables after any masked 3D pass. */
    dev->lpVtbl->SetRenderState(dev, D3DRS_COLORWRITEENABLE,
                                dah_nv2a_color_write_mask(g_pg.color_mask));
    /* Set up 2D render state — always enable alpha for menu transparency */
    dev->lpVtbl->SetRenderState(dev, D3DRS_ZENABLE, FALSE);
    dev->lpVtbl->SetRenderState(dev, D3DRS_LIGHTING, FALSE);
    dev->lpVtbl->SetRenderState(dev, D3DRS_CULLMODE, D3DCULL_NONE);
    dev->lpVtbl->SetRenderState(dev, D3DRS_ALPHABLENDENABLE, TRUE);
    dev->lpVtbl->SetRenderState(dev, D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    dev->lpVtbl->SetRenderState(dev, D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    dev->lpVtbl->SetRenderState(dev, D3DRS_BLENDOP, 1u);

    /* Set FVF for pre-transformed 2D with texture */
    dev->lpVtbl->SetVertexShader(dev, D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

    /* Bind texture based on NV2A VRAM offset.
     * Game-specific texture mapping is handled via GAME_HAS_FONT_ATLAS
     * compile flag. Generic path uses vertex color only. */
#ifdef GAME_HAS_FONT_ATLAS
    if (g_textures_loaded) {
        if (!g_pg.texture_lookup_done) {
            g_pg.texture_lookup_done = 1;
            fprintf(stderr, "[PGRAPH-D3D11] Texture lookup init (global_txd has %d textures)\n",
                    g_global_txd.count);
            for (int ti = 0; ti < g_global_txd.count; ti++) {
                fprintf(stderr, "    [%3d] %-24s %3ux%-3u fmt=0x%X\n",
                        ti, g_global_txd.entries[ti].name,
                        g_global_txd.entries[ti].width,
                        g_global_txd.entries[ti].height,
                        g_global_txd.entries[ti].format);
            }
        }

        IDirect3DTexture8 *tex = NULL;
        uint32_t vram_off = g_pg.tex[0].offset;
        switch (vram_off) {
            case 0x03C1ED00: tex = txd_find(&g_global_txd, "B3Logo"); break;
            case 0x03C24700: tex = txd_find(&g_global_txd, "bg"); break;
            case 0x03C24B80: tex = txd_find(&g_global_txd, "big_curve"); break;
            case 0x03C7BE00: tex = txd_find(&g_global_txd, "Buttons"); break;
            case 0x03C95700: tex = txd_find(&g_global_txd, "dpad"); break;
            case 0x03C95980: tex = txd_find(&g_global_txd, "FE"); break;
            case 0x03CA1A80: tex = txd_find(&g_global_txd, "small_curve"); break;
            case 0x03D57000: tex = txd_find(&g_global_txd, "box_curve"); break;
            case 0x03CB9200: tex = txd_find(&g_global_txd, "grid"); break;
            case 0x02EC0400:
                dev->lpVtbl->EndScene(dev);
                g_pg.inline_count = 0;
                return;
            case 0x021C4100:
                if (!g_pg.font_atlas) {
                    g_pg.font_atlas = create_dxt5_texture(dev,
                        FONT_ATLAS_WIDTH, FONT_ATLAS_HEIGHT,
                        font_atlas_dxt5, FONT_ATLAS_SIZE);
                }
                tex = g_pg.font_atlas;
                break;
            case 0: tex = NULL; break;
            default: tex = NULL; break;
        }

        if (tex) {
            dev->lpVtbl->SetTexture(dev, 0, (IDirect3DBaseTexture8 *)tex);
            dev->lpVtbl->SetTextureStageState(dev, 0, 1 /*COLOROP*/, 4 /*MODULATE*/);
            dev->lpVtbl->SetTextureStageState(dev, 0, 2 /*COLORARG1*/, 2 /*TEXTURE*/);
            dev->lpVtbl->SetTextureStageState(dev, 0, 3 /*COLORARG2*/, 0 /*DIFFUSE*/);
            dev->lpVtbl->SetTextureStageState(dev, 0, 4 /*ALPHAOP*/, 4 /*MODULATE*/);
            dev->lpVtbl->SetTextureStageState(dev, 0, 5 /*ALPHAARG1*/, 2 /*TEXTURE*/);
            dev->lpVtbl->SetTextureStageState(dev, 0, 6 /*ALPHAARG2*/, 0 /*DIFFUSE*/);
            dev->lpVtbl->SetTextureStageState(dev, 0, 13 /*ADDRESSU*/, 3 /*CLAMP*/);
            dev->lpVtbl->SetTextureStageState(dev, 0, 14 /*ADDRESSV*/, 3 /*CLAMP*/);
        } else {
            /* No texture — use vertex color only */
            dev->lpVtbl->SetTexture(dev, 0, NULL);
            dev->lpVtbl->SetTextureStageState(dev, 0, 1 /*COLOROP*/, 2 /*SELECTARG1*/);
            dev->lpVtbl->SetTextureStageState(dev, 0, 2 /*COLORARG1*/, 0 /*DIFFUSE*/);
            dev->lpVtbl->SetTextureStageState(dev, 0, 4 /*ALPHAOP*/, 2 /*SELECTARG1*/);
            dev->lpVtbl->SetTextureStageState(dev, 0, 5 /*ALPHAARG1*/, 0 /*DIFFUSE*/);
        }
    } else {
        dev->lpVtbl->SetTexture(dev, 0, NULL);
    }
#else
    /* Generic path: no game-specific texture lookup, use vertex color only */
    {
        dev->lpVtbl->SetTexture(dev, 0, NULL);
        dev->lpVtbl->SetTextureStageState(dev, 0, 1, 2 /*SELECTARG1*/);
        dev->lpVtbl->SetTextureStageState(dev, 0, 2, 0 /*DIFFUSE*/);
        dev->lpVtbl->SetTextureStageState(dev, 0, 4, 2 /*SELECTARG1*/);
        dev->lpVtbl->SetTextureStageState(dev, 0, 5, 0 /*DIFFUSE*/);
    }
#endif

    /* DAH submits projected particle and beam cards through INLINE_ARRAY with
     * x/y/rhw already produced by the retail vertex program.  The old generic
     * fallback discarded the active texture and drew only vertex colour,
     * turning the saucer's hover particles into large opaque blue-grey cards.
     * Upload the real guest asset through the same bounded texture path used
     * by indexed meshes and preserve the captured alpha/depth/blend state. */
    {
        IDirect3DTexture8 *inline_tex = g_pg.tex[0].enabled ?
            dah_mesh_texture(0u, dev) : NULL;
        dev->lpVtbl->SetRenderState(dev, D3DRS_ZENABLE, g_pg.depth_test);
        dev->lpVtbl->SetRenderState(dev, D3DRS_ZWRITEENABLE, g_pg.depth_write);
        dev->lpVtbl->SetRenderState(dev, D3DRS_ZFUNC,
            g_pg.depth_func >= 0x0200u && g_pg.depth_func <= 0x0207u ?
            g_pg.depth_func - 0x0200u + 1u : D3DCMP_LESSEQUAL);
        if (!dah_apply_blend_state(dev, g_pg.blend_enable)) return;
        dev->lpVtbl->SetRenderState(dev, D3DRS_ALPHATESTENABLE,
            g_pg.alpha_test);
        dev->lpVtbl->SetRenderState(dev, D3DRS_ALPHAFUNC,
            g_pg.alpha_func >= 0x0200u && g_pg.alpha_func <= 0x0207u ?
            g_pg.alpha_func - 0x0200u + 1u : D3DCMP_ALWAYS);
        dev->lpVtbl->SetRenderState(dev, D3DRS_ALPHAREF, g_pg.alpha_ref);
        if (inline_tex) {
            dev->lpVtbl->SetTexture(dev, 0,
                (IDirect3DBaseTexture8 *)inline_tex);
            dev->lpVtbl->SetTextureStageState(dev, 0, D3DTSS_COLOROP,
                D3DTOP_MODULATE2X);
            dev->lpVtbl->SetTextureStageState(dev, 0, D3DTSS_COLORARG1,
                D3DTA_DIFFUSE);
            dev->lpVtbl->SetTextureStageState(dev, 0, D3DTSS_COLORARG2,
                D3DTA_TEXTURE);
            dev->lpVtbl->SetTextureStageState(dev, 0, D3DTSS_ALPHAOP,
                D3DTOP_MODULATE);
            dev->lpVtbl->SetTextureStageState(dev, 0, D3DTSS_ALPHAARG1,
                D3DTA_DIFFUSE);
            dev->lpVtbl->SetTextureStageState(dev, 0, D3DTSS_ALPHAARG2,
                D3DTA_TEXTURE);
            dev->lpVtbl->SetTextureStageState(dev, 0, D3DTSS_ADDRESSU,
                D3DTADDRESS_WRAP);
            dev->lpVtbl->SetTextureStageState(dev, 0, D3DTSS_ADDRESSV,
                D3DTADDRESS_WRAP);
            dev->lpVtbl->SetTextureStageState(dev, 0, D3DTSS_MINFILTER,
                D3DTEXF_LINEAR);
            dev->lpVtbl->SetTextureStageState(dev, 0, D3DTSS_MAGFILTER,
                D3DTEXF_LINEAR);
            dev->lpVtbl->SetTextureStageState(dev, 0, D3DTSS_MIPFILTER,
                D3DTEXF_NONE);
        }
    }

    /* Begin scene if needed */
    dev->lpVtbl->BeginScene(dev);

    /* Draw */
    dev->lpVtbl->DrawPrimitiveUP(dev, (D3DPRIMITIVETYPE)g_pg.d3d_prim_type,
                                  prim_count, out, sizeof(OutputVertex));

    g_pg.stats.draw_calls++;
    g_pg.stats.vertices_submitted += num_verts;

    if (g_pg.stats.draw_calls <= 5 || (g_pg.stats.draw_calls % 1000) == 0) {
        fprintf(stderr, "[PGRAPH-D3D11] Draw #%u: %u verts, prim=%d, prims=%u\n",
                g_pg.stats.draw_calls, num_verts, g_pg.d3d_prim_type, prim_count);
    }
}

/* One explicitly selected ring, all draw paths. This diagnostic reads the
 * game's bound RTV only; it never captures desktop pixels. GPU maps perturb
 * this frame's timing, so the result is rendering evidence, not pacing data. */
static uint32_t dah_pass_trace_submission(void)
{
    static int configured;
    static uint32_t submission;
    if(!configured){
        const char *s=getenv("DAH_PASS_PIXEL_SUBMISSION");char *end=NULL;
        unsigned long value=s&&*s?strtoul(s,&end,10):0;
        if(s&&end!=s&&!*end&&value<=UINT32_MAX)submission=(uint32_t)value;
        configured=1;
    }
    return submission;
}

static void submit_draw(void)
{
    static unsigned reports;
    uint32_t requested=dah_pass_trace_submission();
    if(!requested || g_pg.active_submission!=requested || reports>=512u){
        submit_draw_inner();return;
    }
    static const unsigned xy[3][2]={{20,20},{50,50},{100,100}};
    uint32_t before[3]={0},after[3]={0};
    dah_bind_current_surface();
    HRESULT before_hr=dah_read_active_rt_pixels(d3d8_GetD3D11Context(),xy,3,before);
    uint32_t draws=g_pg.stats.draw_calls;
    submit_draw_inner();
    HRESULT after_hr=dah_read_active_rt_pixels(d3d8_GetD3D11Context(),xy,3,after);
    fprintf(stderr,"[DAH-PASS-PIXELS] sub=%u pass=%u target=%08X surface=%08X mask=%08X blend=%u,%X,%X,%X alpha=%u,%X,%u texture=%08X format=%08X rect=%08X shader=%08X final=%08X,%08X draw=%u hr=%08lX,%08lX before=%08X,%08X,%08X after=%08X,%08X,%08X\n",
        requested,++reports,g_pg.surface_color_offset,g_pg.surface_format,g_pg.color_mask,
        g_pg.blend_enable,g_pg.blend_sfactor,g_pg.blend_dfactor,g_pg.blend_equation,
        g_pg.alpha_test,g_pg.alpha_func,g_pg.alpha_ref,
        g_pg.tex[0].offset,g_pg.tex[0].format,g_pg.tex[0].image_rect,g_pg.shader_stage_program,g_pg.final_cw0,g_pg.final_cw1,
        g_pg.stats.draw_calls-draws,(unsigned long)before_hr,(unsigned long)after_hr,
        before[0],before[1],before[2],after[0],after[1],after[2]);
    fflush(stderr);
}

/* ══════════════════════════════════════════════════════════════════════
 * Method Handler
 * ══════════════════════════════════════════════════════════════════════ */

int pgraph_d3d11_method(int subchannel, uint32_t method, uint32_t param)
{
    if (!g_pg.initialized)
        return 0;

    g_pg.stats.methods_handled++;
    dah_trace_stencil_observe(method,param);

    if (method >= NV097_SET_VERTEX_DATA_ARRAY_OFFSET &&
        method < NV097_SET_VERTEX_DATA_ARRAY_OFFSET + 16u * 4u && !(method & 3u)) {
        g_pg.array_offset[(method - NV097_SET_VERTEX_DATA_ARRAY_OFFSET) / 4u] = param;
        return 1;
    }
    if (method >= NV097_SET_VERTEX_DATA_ARRAY_FORMAT &&
        method < NV097_SET_VERTEX_DATA_ARRAY_FORMAT + 16u * 4u && !(method & 3u)) {
        g_pg.array_format[(method - NV097_SET_VERTEX_DATA_ARRAY_FORMAT) / 4u] = param;
        return 1;
    }
    if (method >= NV097_SET_TRANSFORM_PROGRAM && method < NV097_SET_TRANSFORM_PROGRAM + 0x80u) {
        if (g_pg.transform_load_word < 136u * 4u) {
            g_pg.transform_program[g_pg.transform_load_word] = param;
            g_pg.transform_valid[g_pg.transform_load_word++] = 1;
        }
        return 1;
    }
    /* Constant data aperture: base is set by SET_TRANSFORM_CONSTANT_LOAD and
     * the slot for each word is base + (method - NV097_SET_TRANSFORM_CONSTANT)/4.
     * Range is extended to 0xC00 to cover c[0..191] in a single burst (LOAD=0
     * followed by 768 method words at 0x0B80..0x177C).  Stray methods such as
     * 0x1710 map to high-numbered, unused slots rather than corrupting c[2]. */
    if (method >= NV097_SET_TRANSFORM_CONSTANT && method < NV097_SET_TRANSFORM_CONSTANT + 0xC00u) {
        uint32_t offset = (method - NV097_SET_TRANSFORM_CONSTANT) / 4u;
        uint32_t slot = g_pg.transform_constant_base + offset;
        if (slot < 192u * 4u) {
            if (dah_matrix_trace_enabled() && (slot < 12u || (slot >= 144u && slot < 164u))) {
                static unsigned dah_constant_methods;
                if (dah_constant_methods++ < 256u)
                    fprintf(stderr, "[DAH-CONSTANT-METHOD] slot=%u c%u.%u method=%04X value=%08X float=%.6g\n",
                            slot, slot/4u, slot%4u, method, param, *(const float*)&param);
            }
            g_pg.transform_constants[slot] = param;
            g_pg.transform_constant_valid[slot] = 1;
        }
        return 1;
    }
    if(method>=NV097_SET_COMBINER_FACTOR0 && method<NV097_SET_COMBINER_FACTOR0+32) {g_pg.factor0[(method-NV097_SET_COMBINER_FACTOR0)/4]=param;return 1;}
    if(method>=NV097_SET_COMBINER_FACTOR1 && method<NV097_SET_COMBINER_FACTOR1+32) {g_pg.factor1[(method-NV097_SET_COMBINER_FACTOR1)/4]=param;return 1;}
    if (method >= NV097_SET_COMBINER_COLOR_ICW && method < NV097_SET_COMBINER_COLOR_ICW + 32u) {
        g_pg.color_icw[(method - NV097_SET_COMBINER_COLOR_ICW) / 4u] = param;
        return 1;
    }
    if (method >= NV097_SET_COMBINER_COLOR_OCW && method < NV097_SET_COMBINER_COLOR_OCW + 32u) {
        g_pg.color_ocw[(method - NV097_SET_COMBINER_COLOR_OCW) / 4u] = param;
        return 1;
    }
    if (method >= NV097_SET_COMBINER_ALPHA_ICW && method < NV097_SET_COMBINER_ALPHA_ICW + 32u) {
        g_pg.alpha_icw[(method - NV097_SET_COMBINER_ALPHA_ICW) / 4u] = param;
        return 1;
    }
    if (method >= NV097_SET_COMBINER_ALPHA_OCW && method < NV097_SET_COMBINER_ALPHA_OCW + 32u) {
        g_pg.alpha_ocw[(method - NV097_SET_COMBINER_ALPHA_OCW) / 4u] = param;
        return 1;
    }
    if (method >= NV097_SET_FOG_PARAMS && method < NV097_SET_FOG_PARAMS + 12u && !(method & 3u)) {
        g_pg.fog_param[(method - NV097_SET_FOG_PARAMS) / 4u] = u2f(param);
        return 1;
    }

    switch (method) {
    case NV097_CLEAR_REPORT_VALUE:
        dah_zpass_finish(); dah_query_event(0,NULL,NULL); dah_zpass_begin(); return 1;
    case NV097_SET_ZPASS_PIXEL_COUNT_ENABLE:
        dah_zpass_finish(); dah_zpass_enabled=param!=0; dah_zpass_begin(); return 1;
    case NV097_GET_REPORT:
        dah_zpass_report(param); return 1;
    case NV097_SET_SURFACE_FORMAT:
        g_pg.surface_format = param;
        if (dah_matrix_trace_enabled() && g_pg.active_submission >= 770u) {
            static unsigned dah_surface_format_logs;
            if (dah_surface_format_logs++ < 48u)
                fprintf(stderr, "[DAH-SURFACE] submit=%u sub=%d format=%08X pitch=%08X color=%08X\n",
                        g_pg.active_submission, subchannel, param, g_pg.surface_pitch, g_pg.surface_color_offset);
        }
        return 1;
    case NV097_SET_SURFACE_PITCH:
        g_pg.surface_pitch = param;
        return 1;
    case NV097_SET_SURFACE_COLOR_OFFSET:
        g_pg.surface_color_offset = param;
        /* Backbuffers have fixed dimensions and may be selected solely for
         * presentation. Offscreen allocation waits for complete draw/clear state. */
        if (dah_surface_is_backbuffer(param)) dah_bind_current_surface();
        if (dah_matrix_trace_enabled() && g_pg.active_submission >= 770u) {
            static unsigned dah_surface_color_logs;
            if (dah_surface_color_logs++ < 96u)
                fprintf(stderr, "[DAH-SURFACE] submit=%u sub=%d color=%08X format=%08X pitch=%08X\n",
                        g_pg.active_submission, subchannel, param, g_pg.surface_format, g_pg.surface_pitch);
        }
        return 1;
    case NV097_SET_SURFACE_ZETA_OFFSET:
        g_pg.surface_zeta_offset = param;
        return 1;
    case NV097_SET_CLIP_MIN: g_pg.clip_min = u2f(param); g_pg.clip_range_valid |= 1u; return 1;
    case NV097_SET_CLIP_MAX: g_pg.clip_max = u2f(param); g_pg.clip_range_valid |= 2u; return 1;
    case NV097_SET_FOG_MODE: g_pg.fog_mode = param; return 1;
    case NV097_SET_FOG_ENABLE: g_pg.fog_enable = param != 0; return 1;
    case NV097_SET_FOG_COLOR: {
        IDirect3DDevice8 *dev = xbox_GetD3DDevice();
        g_pg.fog_color_raw = param;
        if (dev) dev->lpVtbl->SetRenderState(dev, D3DRS_FOGCOLOR,
                                            dah_nv2a_fog_color_argb(param));
        return 1;
    }
    case NV097_SET_STENCIL_TEST_ENABLE: g_pg.stencil_test = param != 0; return 1;
    case NV097_SET_STENCIL_MASK: g_pg.stencil_mask = param; return 1;
    case NV097_SET_STENCIL_FUNC: g_pg.stencil_func = param; return 1;
    case NV097_SET_STENCIL_FUNC_REF: g_pg.stencil_ref = param; return 1;
    case NV097_SET_STENCIL_FUNC_MASK: g_pg.stencil_func_mask = param; return 1;
    case NV097_SET_STENCIL_OP_FAIL: g_pg.stencil_op_fail = param; return 1;
    case NV097_SET_STENCIL_OP_ZFAIL: g_pg.stencil_op_zfail = param; return 1;
    case NV097_SET_STENCIL_OP_ZPASS: g_pg.stencil_op_zpass = param; return 1;
    case NV097_SET_TRANSFORM_CONSTANT_LOAD:
        g_pg.transform_constant_base = param < 192u ? param * 4u : 192u * 4u;
        if (dah_matrix_trace_enabled() && param < 48u)
            fprintf(stderr, "[DAH-CONSTANT-LOAD] c=%u base=%u\n", param,
                    g_pg.transform_constant_base);
        return 1;
    case NV097_SET_TRANSFORM_PROGRAM_LOAD:
        g_pg.transform_load_word = param < 136u ? param * 4u : 136u * 4u;
        return 1;
    case NV097_SET_TRANSFORM_PROGRAM_START: g_pg.transform_start = param; return 1;
    case NV097_SET_TRANSFORM_EXECUTION_MODE: g_pg.transform_mode = param; return 1;
    case NV097_SET_COMBINER_CONTROL: g_pg.combiner_control = param; return 1;
    case NV097_SET_COMBINER_SPECULAR_FOG_CW0: g_pg.final_cw0 = param; return 1;
    case NV097_SET_COMBINER_SPECULAR_FOG_CW1: g_pg.final_cw1 = param; return 1;
    case NV097_SET_SHADER_STAGE_PROGRAM: g_pg.shader_stage_program = param; return 1;

    /* ── Draw Begin/End ── */
    case NV097_SET_BEGIN_END:
        g_pg.draw_subchannel = subchannel;
        if (param == 0) {
            /* END: submit accumulated vertices */
            if (g_pg.in_draw) {
                if (dah_method_timing_active) {
                    double t = dah_profile_ms();
                    submit_draw();
                    dah_method_draw_ms += dah_profile_ms() - t;
                    ++dah_method_draw_count;
                } else submit_draw();
                g_pg.in_draw = 0;
            }
        } else {
            /* BEGIN: start new draw */
            g_pg.in_draw = 1;
            g_pg.draw_mode = param;
            g_pg.d3d_prim_type = nv2a_draw_mode_to_d3d(param);
            g_pg.inline_count = 0;
            g_pg.indexed_diagnostic_id = 0;
            g_pg.indexed_diagnostic_packets = 0;
            g_pg.index_count = 0;
            g_pg.index_overflow = 0;
        }
        return 1;

    case NV097_ARRAY_ELEMENT16:
    case NV097_ARRAY_ELEMENT32:
    case NV097_DRAW_ARRAYS:
        /* Preserve index order. Host submission below accepts only the
         * verified retail movie shader/format, reporting all other layouts. */
        if (!g_pg.indexed_diagnostic_id) {
            g_pg.indexed_diagnostic_id = ++g_pg.indexed_diagnostic_count;
            if (g_pg.indexed_diagnostic_id <= 4u) {
                fprintf(stderr, "[DAH-INDEXED-STATE] draw=%u mode=%u subchannel=%d in_draw=%d host_support=movie-gated depth=%d blend=%d cull=%d color_mask=%08X\n",
                        g_pg.indexed_diagnostic_id, g_pg.draw_mode, subchannel,
                        g_pg.in_draw, g_pg.depth_test, g_pg.blend_enable,
                        g_pg.cull_enable, g_pg.color_mask);
                for (unsigned slot = 0; slot < 16u; ++slot) {
                    uint32_t format = g_pg.array_format[slot];
                    fprintf(stderr, "[DAH-INDEXED-ARRAY] draw=%u slot=%u offset=%08X format=%08X type=%u components=%u stride=%u\n",
                            g_pg.indexed_diagnostic_id, slot, g_pg.array_offset[slot],
                            format, format & 15u, (format >> 4u) & 15u, format >> 8u);
                }
                for (unsigned stage = 0; stage < 4u; ++stage) {
                    fprintf(stderr, "[DAH-INDEXED-TEX] draw=%u stage=%u enabled=%d offset=%08X format=%08X control0=%08X control1=%08X image_rect=%08X pitch=%u rect=%ux%u\n",
                            g_pg.indexed_diagnostic_id, stage, g_pg.tex[stage].enabled,
                            g_pg.tex[stage].offset, g_pg.tex[stage].format,
                            g_pg.tex[stage].control0, g_pg.tex[stage].control1,
                            g_pg.tex[stage].image_rect, g_pg.tex[stage].control1 >> 16u,
                            g_pg.tex[stage].image_rect >> 16u,
                            g_pg.tex[stage].image_rect & 0xFFFFu);
                }
                fprintf(stderr, "[DAH-INDEXED-VIEWPORT] draw=%u scale=%.9g,%.9g,%.9g,%.9g offset=%.9g,%.9g,%.9g,%.9g clip=%08X,%08X\n",
                        g_pg.indexed_diagnostic_id,
                        g_pg.vp_scale[0], g_pg.vp_scale[1], g_pg.vp_scale[2], g_pg.vp_scale[3],
                        g_pg.vp_offset[0], g_pg.vp_offset[1], g_pg.vp_offset[2], g_pg.vp_offset[3],
                        g_pg.surface_clip_h, g_pg.surface_clip_v);
            }
        }
        if (g_pg.indexed_diagnostic_id <= 4u && g_pg.indexed_diagnostic_packets++ < 8u) {
            fprintf(stderr, "[DAH-INDEXED-DATA] draw=%u method=%04X value=%08X lo16=%u hi16=%u\n",
                    g_pg.indexed_diagnostic_id, method, param,
                    param & 0xFFFFu, param >> 16u);
            fflush(stderr);
        }
        if (g_pg.in_draw) {
            uint32_t count = method == NV097_ARRAY_ELEMENT16 ? 2u :
                             method == NV097_DRAW_ARRAYS ? (param >> 24u) + 1u : 1u;
            if (count > MAX_INLINE_VERTS - g_pg.index_count) {
                g_pg.index_overflow = 1;
            } else {
                for (uint32_t i = 0; i < count; ++i)
                    g_pg.indices[g_pg.index_count++] = method == NV097_ARRAY_ELEMENT16 ?
                        ((param >> (i * 16u)) & 0xFFFFu) :
                        method == NV097_DRAW_ARRAYS ? (param & 0xFFFFFFu) + i : param;
            }
        }
        return 1;

    /* ── Inline Vertex Data ── */
    case NV097_INLINE_ARRAY:
        if (g_pg.in_draw && g_pg.inline_count < MAX_INLINE_VERTS * INLINE_VERT_DWORDS) {
            g_pg.inline_data[g_pg.inline_count++] = param;
        }
        return 1;

    /* ── Clear ── */
    case NV097_SET_ZSTENCIL_CLEAR_VALUE:
        g_pg.clear_zstencil = param;
        return 1;

    case NV097_SET_COLOR_CLEAR_VALUE:
        g_pg.clear_color = param;
        return 1;

    case NV097_SET_CLEAR_RECT_HORIZONTAL:
        g_pg.clear_rect_h = param;
        return 1;

    case NV097_SET_CLEAR_RECT_VERTICAL:
        g_pg.clear_rect_v = param;
        return 1;

    case NV097_CLEAR_SURFACE:
    {
        dah_bind_current_surface();
        if (param & 0xF0) (void)d3d8_PgraphPreserveCurrentRenderTarget();
        IDirect3DDevice8 *dev = xbox_GetD3DDevice();
        if (dev) {
            uint32_t flags = 0;
            if (param & 0xF0) flags |= 1;  /* D3DCLEAR_TARGET */
            if (param & 0x01) flags |= 2;  /* D3DCLEAR_ZBUFFER */
            if (param & 0x02) flags |= 4;  /* D3DCLEAR_STENCIL */
            /* Z24S8 packs stencil in the low byte and the 24-bit depth value
             * above it. This is the same register interpretation used by
             * NV2A/xemu; in particular, stencil-only clears must preserve the
             * game's requested value instead of silently clearing to zero. */
            float clear_depth = (float)(g_pg.clear_zstencil >> 8) / 16777215.0f;
            uint32_t clear_stencil = g_pg.clear_zstencil & 0xFFu;
            dev->lpVtbl->Clear(dev, 0, NULL, flags, g_pg.clear_color,
                               clear_depth, clear_stencil);
        }
        g_pg.stats.clears++;
        return 1;
    }

    /* ── Render State ── */
    case NV097_SET_DEPTH_TEST_ENABLE:
        g_pg.depth_test = param ? 1 : 0;
        return 1;

    case NV097_SET_DEPTH_FUNC: g_pg.depth_func = param; return 1;
    case NV097_SET_DEPTH_MASK: g_pg.depth_write = param != 0; return 1;
    case NV097_SET_POLY_OFFSET_POINT_ENABLE:
        g_pg.poly_offset_point = param != 0;
        return 1;
    case NV097_SET_POLY_OFFSET_LINE_ENABLE:
        g_pg.poly_offset_line = param != 0;
        return 1;
    case NV097_SET_POLY_OFFSET_FILL_ENABLE:
        g_pg.poly_offset_fill = param != 0;
        dah_apply_polygon_offset();
        return 1;
    case NV097_SET_POLYGON_OFFSET_SCALE_FACTOR:
        g_pg.poly_offset_scale = u2f(param);
        dah_apply_polygon_offset();
        return 1;
    case NV097_SET_POLYGON_OFFSET_BIAS:
        g_pg.poly_offset_bias = u2f(param);
        dah_apply_polygon_offset();
        return 1;

    case NV097_SET_BLEND_ENABLE:
        g_pg.blend_enable = param ? 1 : 0;
        return 1;

    case NV097_SET_BLEND_FUNC_SFACTOR:
        g_pg.blend_sfactor = param;
        return 1;

    case NV097_SET_BLEND_FUNC_DFACTOR:
        g_pg.blend_dfactor = param;
        return 1;

    case NV097_SET_BLEND_EQUATION:
        g_pg.blend_equation = param;
        return 1;

    case NV097_SET_CULL_FACE_ENABLE:
        g_pg.cull_enable = param ? 1 : 0;
        return 1;

    case NV097_SET_ALPHA_TEST_ENABLE:
        g_pg.alpha_test = param ? 1 : 0;
        return 1;
    case NV097_SET_ALPHA_FUNC: g_pg.alpha_func = param; return 1;
    case NV097_SET_ALPHA_REF: g_pg.alpha_ref = param; return 1;
    case NV097_SET_CULL_FACE: g_pg.cull_face = param; return 1;
    case NV097_SET_FRONT_FACE: g_pg.front_face = param; return 1;

    case NV097_SET_COLOR_MASK:
        g_pg.color_mask = param;
        return 1;

    case NV097_SET_SHADE_MODE:
        /* 1=flat, 2=gouraud — we always use gouraud */
        return 1;

    /* ── Viewport ── */
    case NV097_SET_VIEWPORT_OFFSET:
    case NV097_SET_VIEWPORT_OFFSET + 4:
    case NV097_SET_VIEWPORT_OFFSET + 8:
    case NV097_SET_VIEWPORT_OFFSET + 12:
    {
        int idx = (method - NV097_SET_VIEWPORT_OFFSET) / 4;
        g_pg.vp_offset[idx] = u2f(param);
        return 1;
    }

    case NV097_SET_VIEWPORT_SCALE:
    case NV097_SET_VIEWPORT_SCALE + 4:
    case NV097_SET_VIEWPORT_SCALE + 8:
    case NV097_SET_VIEWPORT_SCALE + 12:
    {
        int idx = (method - NV097_SET_VIEWPORT_SCALE) / 4;
        g_pg.vp_scale[idx] = u2f(param);
        return 1;
    }

    case NV097_SET_SURFACE_CLIP_HORIZONTAL:
        g_pg.surface_clip_h = param;
        return 1;

    case NV097_SET_SURFACE_CLIP_VERTICAL:
        g_pg.surface_clip_v = param;
        return 1;

    /* ── Texture state tracking (4 stages, 0x40 stride) ── */
    case NV097_SET_TEXTURE_OFFSET:
    case NV097_SET_TEXTURE_OFFSET + 0x40:
    case NV097_SET_TEXTURE_OFFSET + 0x80:
    case NV097_SET_TEXTURE_OFFSET + 0xC0:
    {
        int stage = (method - NV097_SET_TEXTURE_OFFSET) / 0x40;
        g_pg.tex[stage].offset = param;
        return 1;
    }
    case NV097_SET_TEXTURE_FORMAT:
    case NV097_SET_TEXTURE_FORMAT + 0x40:
    case NV097_SET_TEXTURE_FORMAT + 0x80:
    case NV097_SET_TEXTURE_FORMAT + 0xC0:
    {
        int stage = (method - NV097_SET_TEXTURE_FORMAT) / 0x40;
        g_pg.tex[stage].format = param;
        return 1;
    }
    case NV097_SET_TEXTURE_CONTROL0:
    case NV097_SET_TEXTURE_CONTROL0 + 0x40:
    case NV097_SET_TEXTURE_CONTROL0 + 0x80:
    case NV097_SET_TEXTURE_CONTROL0 + 0xC0:
    {
        int stage = (method - NV097_SET_TEXTURE_CONTROL0) / 0x40;
        g_pg.tex[stage].control0 = param;
        g_pg.tex[stage].enabled = (param >> 30) & 1;
        return 1;
    }
    case NV097_SET_TEXTURE_CONTROL1:
    case NV097_SET_TEXTURE_CONTROL1 + 0x40:
    case NV097_SET_TEXTURE_CONTROL1 + 0x80:
    case NV097_SET_TEXTURE_CONTROL1 + 0xC0:
        g_pg.tex[(method - NV097_SET_TEXTURE_CONTROL1) / 0x40].control1 = param;
        return 1;
    case NV097_SET_TEXTURE_IMAGE_RECT:
    case NV097_SET_TEXTURE_IMAGE_RECT + 0x40:
    case NV097_SET_TEXTURE_IMAGE_RECT + 0x80:
    case NV097_SET_TEXTURE_IMAGE_RECT + 0xC0:
        g_pg.tex[(method - NV097_SET_TEXTURE_IMAGE_RECT) / 0x40].image_rect = param;
        return 1;
    case NV097_SET_TEXTURE_ADDRESS:
    case NV097_SET_TEXTURE_ADDRESS + 0x40:
    case NV097_SET_TEXTURE_ADDRESS + 0x80:
    case NV097_SET_TEXTURE_ADDRESS + 0xC0:
        g_pg.tex[(method - NV097_SET_TEXTURE_ADDRESS) / 0x40].address = param;
        return 1;
    case NV097_SET_TEXTURE_FILTER:
    case NV097_SET_TEXTURE_FILTER + 0x40:
    case NV097_SET_TEXTURE_FILTER + 0x80:
    case NV097_SET_TEXTURE_FILTER + 0xC0:
        g_pg.tex[(method - NV097_SET_TEXTURE_FILTER) / 0x40].filter = param;
        return 1;

    default:
        /* Check if it's in a known range we can safely ignore */
        if ((method >= 0x0B80 && method < 0x0C00) ||  /* Transform program */
            (method >= 0x0E00 && method < 0x1000) ||  /* Transform constants */
            (method >= 0x1680 && method < 0x1780) ||  /* Vertex array format/offset */
            (method >= 0x1B00 && method < 0x1C00) ||  /* Texture registers */
            (method >= 0x1D60 && method < 0x1EA0) ||  /* Combiners */
            method == 0x0100 ||                        /* NOP */
            method == 0x0180 ||                        /* SET_OBJECT */
            method == 0x0394 ||                        /* TRANSFORM_EXECUTION_MODE */
            method == 0x0398 ||                        /* TRANSFORM_PROGRAM_CXT_WRITE_EN */
            method == 0x039C ||                        /* TRANSFORM_PROGRAM_LOAD */
            method == 0x01E0 ||                        /* SHADER_STAGE_PROGRAM */
            method == 0x0108 || method == 0x010C ||    /* FLIP_READ/WRITE */
            method == 0x0110 || method == 0x0114 ||    /* FLIP_MODULO/INCREMENT */
            method == 0x0118)                          /* FLIP_STALL */
        {
            return 1;  /* Silently handled (ignored but acknowledged) */
        }

        g_pg.stats.methods_ignored++;
        return 0;  /* Truly unhandled */
    }
}

void pgraph_d3d11_flush(void)
{
    if (g_pg.in_draw) {
        submit_draw();
        g_pg.in_draw = 0;
    }
    g_pg.stats.frames++;
}

/* Opt-in evidence capture of the actual retail ring, before parsing. Files
 * contain little-endian raw dwords with no header so external decoders can
 * examine skipped control packets too. Bound both count and per-file size
 * to avoid turning a long bring-up run into an unbounded disk writer. */
static int capture_pushbuffer(const uint32_t *data, uint32_t num_dwords,
                             uint32_t submission, int kind)
{
    static int configured;
    static unsigned long capture_limit, capture_start = 1u, captures;
    static unsigned long indexed_limit;
    static unsigned long indexed_captures;
    static unsigned long rejected_limit, rejected_captures, rejected_start;
    static uint32_t rejected_hashes[32], last_rejected_submission;
    const uint32_t max_capture_dwords = 512u * 1024u / sizeof(uint32_t);
    uint32_t capture_dwords;
    char path[96];
    FILE *file;
    size_t written;
    int close_result;

    if (!configured) {
        const char *value = getenv("DAH_PB_CAPTURE");
        configured = 1;
        if (value && value[0] >= '0' && value[0] <= '9') {
            char *end;
            unsigned long requested = strtoul(value, &end, 10);
            if (*end == '\0')
                capture_limit = requested > 64u ? 64u : requested;
        }
        indexed_limit = capture_limit > 8u ? 8u : capture_limit;
        rejected_limit = capture_limit > 4u ? 4u : capture_limit;
        value = getenv("DAH_PB_CAPTURE_START");
        if (value && value[0] >= '0' && value[0] <= '9') {
            char *end;
            unsigned long requested = strtoul(value, &end, 10);
            if (*end == '\0') capture_start = requested;
        }
        value = getenv("DAH_PB_INDEXED_CAPTURE");
        if (value && value[0] >= '0' && value[0] <= '9') {
            char *end;
            unsigned long requested = strtoul(value, &end, 10);
            if (*end == '\0') indexed_limit = requested > 8u ? 8u : requested;
        }
        value = getenv("DAH_PB_REJECT_START");
        if (value && value[0] >= '0' && value[0] <= '9') {
            char *end; unsigned long requested = strtoul(value, &end, 10);
            if (*end == '\0') rejected_start = requested;
        }
        value = getenv("DAH_PB_REJECT_CAPTURE");
        if (value && value[0] >= '0' && value[0] <= '9') {
            char *end;
            unsigned long requested = strtoul(value, &end, 10);
            if (*end == '\0') rejected_limit = requested > 32u ? 32u : requested;
        }
    }
    g_pg.rejected_capture_enabled = submission >= rejected_start && rejected_limit && rejected_captures < rejected_limit;
    if (kind == 2) {
        if (submission < rejected_start || !rejected_limit || rejected_captures >= rejected_limit ||
            last_rejected_submission == submission) return 0;
        for (unsigned long i = 0; i < rejected_captures; ++i)
            if (rejected_hashes[i] == g_pg.rejected_state_hash) return 0;
        rejected_hashes[rejected_captures++] = g_pg.rejected_state_hash;
        last_rejected_submission = submission;
    } else if (kind == 1) {
        if (!indexed_limit || indexed_captures >= indexed_limit) return 0;
        ++indexed_captures;
    } else {
        if (!capture_limit || submission < capture_start || captures >= capture_limit) return 0;
        ++captures;
    }

    capture_dwords = num_dwords < max_capture_dwords ?
                         num_dwords : max_capture_dwords;
    snprintf(path, sizeof(path), kind == 2 ? "dah_pb_rejected_%lu_%06u.bin" :
             kind == 1 ? "dah_pb_indexed_%lu_%06u.bin" : "dah_pb_%lu_%06u.bin",
             (unsigned long)GetCurrentProcessId(), submission);
    file = fopen(path, "wb");
    if (!file) {
        fprintf(stderr, "[DAH-PB-CAPTURE] submit=%u open-failed path=%s\n",
                submission, path);
        fflush(stderr);
        return 1;
    }
    written = fwrite(data, sizeof(*data), capture_dwords, file);
    close_result = fclose(file);
    fprintf(stderr,
            "[DAH-PB-CAPTURE] submit=%u path=%s source-dwords=%u written-dwords=%zu truncated=%u write-ok=%u indexed-trigger=%u rejected-trigger=%u\n",
            submission, path, num_dwords, written,
            (unsigned)(capture_dwords != num_dwords),
            (unsigned)(written == capture_dwords && close_result == 0),
            (unsigned)(kind == 1), (unsigned)(kind == 2));
    fflush(stderr);
    return 1;
}

void pgraph_d3d11_submit_pushbuffer(const uint32_t *data, uint32_t num_dwords)
{
    /* Xbox method packet encoding.  The D3D8LTCG ring is consumed
     * synchronously on the host, so only the linear packet range written
     * since the previous flush is presented here. */
    const uint32_t inc_mask = 0xE0030003u;
    const uint32_t noninc_mask = 0xE0030003u;
    uint32_t pos = 0;
    uint32_t methods = 0;
    uint32_t begin_packets = 0;
    uint32_t inline_packets = 0;
    uint32_t skipped_control_words = 0;
    uint32_t invalid_count_words = 0;
    uint32_t method_histogram[0x800] = {0};
    int captured;
    static uint32_t submissions = 0;

    if (!g_pg.initialized || !data || num_dwords == 0)
        return;

    /* Per-process A/B controls for validating the optimized packet paths. */
    static int disable_index_fastpath = -1;
    static int disable_constant_fastpath = -1;
    if (disable_index_fastpath < 0)
        disable_index_fastpath = getenv("DAH_DISABLE_INDEX_FASTPATH") != NULL;
    if (disable_constant_fastpath < 0)
        disable_constant_fastpath = getenv("DAH_DISABLE_CONSTANT_FASTPATH") != NULL;

    captured = capture_pushbuffer(data, num_dwords, submissions + 1u, 0);
    dah_read_region_count=0;
    if(dah_memory_window_profile_enabled() && dah_window_profile.reports<40u) {
        ++dah_window_profile.batch_resets;
        dah_window_profile.batch_queries=0;
    }
    g_pg.active_pushbuffer = data;
    g_pg.active_pushbuffer_dwords = num_dwords;
    g_pg.active_submission = submissions + 1u;
    g_pg.rejected_ring_captured = 0;

    if (submissions == 0) {
        uint32_t dump_count = num_dwords < 96u ? num_dwords : 96u;
        fprintf(stderr, "[DAH-PB-RAW] dwords=%u", num_dwords);
        for (uint32_t i = 0; i < dump_count; ++i) {
            if ((i & 7u) == 0u)
                fprintf(stderr, "\n  %04X:", i);
            fprintf(stderr, " %08X", data[i]);
        }
        fputc('\n', stderr);
        fflush(stderr);
    }

    dah_method_timing_active = dah_method_profile_sample(submissions + 1u);
    dah_method_draw_ms = 0.0;
    dah_method_draw_count = 0u;
    double dah_method_total_start = dah_method_timing_active ? dah_profile_ms() : 0.0;
    while (pos < num_dwords) {
        uint32_t header = data[pos];
        uint32_t count;
        uint32_t method;
        uint32_t subchannel;
        int noninc;

        if (header == 0) {
            ++pos;
            continue;
        }

        if ((header & inc_mask) == 0) {
            noninc = 0;
        } else if ((header & noninc_mask) == 0x40000000u) {
            noninc = 1;
        } else {
            /* Jump/call/return and padding tokens are not part of the linear
             * host range.  Skip unrecognized control words safely. */
            ++skipped_control_words;
            ++pos;
            continue;
        }

        count = (header >> 18) & 0x7FFu;
        method = header & 0x1FFCu;
        subchannel = (header >> 13) & 7u;
        if (count == 0 || count > num_dwords - pos - 1) {
            ++invalid_count_words;
            ++pos;
            continue;
        }

        /* Most retail Farm packets repeat ARRAY_ELEMENT16 many times. Once
         * the first four diagnostic draws have passed, append that packet in
         * place. This preserves every 16-bit index, the original per-word
         * overflow rule, counters and the capture histogram while avoiding
         * a full method dispatch for each index pair. */
        if (!disable_index_fastpath && noninc && method == NV097_ARRAY_ELEMENT16 && g_pg.in_draw &&
            (g_pg.indexed_diagnostic_id > 4u ||
             (!g_pg.indexed_diagnostic_id && g_pg.indexed_diagnostic_count >= 4u))) {
            uint32_t out_count = g_pg.index_count;
            int overflow = g_pg.index_overflow;
            if (!g_pg.indexed_diagnostic_id)
                g_pg.indexed_diagnostic_id = ++g_pg.indexed_diagnostic_count;
            for (uint32_t i = 0; i < count; ++i) {
                uint32_t value = data[pos + 1u + i];
                if (2u > MAX_INLINE_VERTS - out_count) {
                    overflow = 1;
                } else {
                    g_pg.indices[out_count++] = value & 0xFFFFu;
                    g_pg.indices[out_count++] = value >> 16u;
                }
            }
            g_pg.index_count = out_count;
            g_pg.index_overflow = overflow;
            g_pg.stats.methods_handled += count;
            method_histogram[NV097_ARRAY_ELEMENT16 >> 2] += count;
            methods += count;
            pos += 1u + count;
            continue;
        }

        /* Bulk-copy only the true constant range. The original handler
         * checks vertex-array offsets at 0x1720 and formats at 0x1760 before
         * its broad constant aperture; a packet touching either must pass
         * through the ordinary dispatcher in original method order. */
        if (!disable_constant_fastpath && !noninc && method >= NV097_SET_TRANSFORM_CONSTANT &&
            (uint64_t)method + (uint64_t)(count - 1u) * 4u <
                NV097_SET_VERTEX_DATA_ARRAY_OFFSET &&
            !dah_matrix_trace_enabled()) {
            uint32_t slot = g_pg.transform_constant_base +
                (method - NV097_SET_TRANSFORM_CONSTANT) / 4u;
            if (slot < 192u * 4u) {
                uint32_t copied = count;
                if (copied > 192u * 4u - slot)
                    copied = 192u * 4u - slot;
                memcpy(g_pg.transform_constants + slot,
                       data + pos + 1u, (size_t)copied * sizeof(uint32_t));
                memset(g_pg.transform_constant_valid + slot, 1, copied);
            }
            for (uint32_t i = 0; i < count; ++i)
                ++method_histogram[(method + i * 4u) >> 2];
            g_pg.stats.methods_handled += count;
            methods += count;
            pos += 1u + count;
            continue;
        }

        for (uint32_t i = 0; i < count; ++i) {
            uint32_t dispatched_method = method + (noninc ? 0u : i * 4u);
            if (dispatched_method == NV097_SET_BEGIN_END)
                ++begin_packets;
            if (dispatched_method == NV097_INLINE_ARRAY)
                ++inline_packets;
            if (dispatched_method < 0x2000u)
                ++method_histogram[dispatched_method >> 2];
            pgraph_d3d11_method((int)subchannel,
                                dispatched_method,
                                data[pos + 1 + i]);
            ++methods;
        }
        pos += 1 + count;
    }
    if (dah_method_timing_active) {
        double total_ms = dah_profile_ms() - dah_method_total_start;
        fprintf(stderr, "[DAH-METHOD-TIME] submit=%u methods=%u draws=%u total-ms=%.3f draw-ms=%.3f other-ms=%.3f\n",
                submissions + 1u, methods, dah_method_draw_count,
                total_ms, dah_method_draw_ms, total_ms - dah_method_draw_ms);
        fflush(stderr);
    }
    dah_method_timing_active = 0;
    dah_memory_window_batch_end(submissions+1u);
    dah_read_region_count=0;
    g_pg.active_pushbuffer = NULL;
    g_pg.active_pushbuffer_dwords = 0;
    captured |= g_pg.rejected_ring_captured;

    /* A ring-capacity submission may occur in the middle of a title frame.
     * The caller must flush/present at the actual end-frame boundary. */
    ++submissions;
    if (method_histogram[NV097_ARRAY_ELEMENT16 >> 2] ||
        method_histogram[NV097_ARRAY_ELEMENT32 >> 2] ||
        method_histogram[NV097_DRAW_ARRAYS >> 2]) {
        captured |= capture_pushbuffer(data, num_dwords, submissions, 1);
    }
    if (captured) {
        fprintf(stderr,
                "[DAH-PB-PARSE] submit=%u methods=%u skipped-control-words=%u invalid-count-words=%u begin=%u elem16=%u elem32=%u arrays=%u inline=%u\n",
                submissions, methods, skipped_control_words, invalid_count_words,
                begin_packets, method_histogram[NV097_ARRAY_ELEMENT16 >> 2],
                method_histogram[NV097_ARRAY_ELEMENT32 >> 2],
                method_histogram[NV097_DRAW_ARRAYS >> 2], inline_packets);
        fflush(stderr);
    }
    /* Opt-in, bounded pushbuffer method histogram for Farm performance work. */
    if (dah_method_profile_sample(submissions)) {
        fprintf(stderr, "[DAH-METHOD-PROFILE] submit=%u dwords=%u methods=%u\n",
                submissions, num_dwords, methods);
        for (uint32_t rank = 0; rank < 12u; ++rank) {
            uint32_t best_index = 0, best_count = 0;
            for (uint32_t j = 0; j < 0x800u; ++j)
                if (method_histogram[j] > best_count) {
                    best_count = method_histogram[j]; best_index = j;
                }
            if (!best_count) break;
            fprintf(stderr, "[DAH-METHOD-TOP] submit=%u rank=%u method=%04X count=%u\n",
                    submissions, rank + 1u, best_index << 2, best_count);
            method_histogram[best_index] = 0;
        }
        fflush(stderr);
    }
    if (submissions <= 8 || (submissions % 300u) == 0) {
        fprintf(stderr, "[DAH-PB] submit=%u dwords=%u methods=%u begin=%u inline=%u draws=%u verts=%u\n",
                submissions, num_dwords, methods,
                begin_packets, inline_packets,
                g_pg.stats.draw_calls, g_pg.stats.vertices_submitted);
        fflush(stderr);
    }
    if (submissions <= 2) {
        fprintf(stderr,
                "[DAH-PB-DRAW-METHODS] submit=%u begin=%u elem16=%u elem32=%u arrays=%u inline=%u\n",
                submissions,
                method_histogram[NV097_SET_BEGIN_END >> 2],
                method_histogram[NV097_ARRAY_ELEMENT16 >> 2],
                method_histogram[NV097_ARRAY_ELEMENT32 >> 2],
                method_histogram[NV097_DRAW_ARRAYS >> 2],
                method_histogram[NV097_INLINE_ARRAY >> 2]);
        for (uint32_t rank = 0; rank < 12; ++rank) {
            uint32_t best_index = 0;
            uint32_t best_count = 0;
            for (uint32_t i = 0; i < 0x800; ++i) {
                if (method_histogram[i] > best_count) {
                    best_count = method_histogram[i];
                    best_index = i;
                }
            }
            if (!best_count) break;
            fprintf(stderr, "  [DAH-PB-TOP] rank=%u method=%04X count=%u\n",
                    rank + 1, best_index << 2, best_count);
            method_histogram[best_index] = 0;
        }
        fflush(stderr);
    }
}

void pgraph_d3d11_set_chyron_scroll(uint32_t pixels)
{
    g_pg.chyron_scroll_offset = (float)pixels;
}

void pgraph_d3d11_get_stats(PgraphD3D11Stats *out)
{
    if (out) *out = g_pg.stats;
}
