#ifndef __THINK2D_H__
#define __THINK2D_H__

typedef volatile unsigned long int u32;

// Registers
//-----------------------------------------------------------------------------------------------------------------------
typedef enum {
     //-----------------------------
     T2D_TARGET_MODE      = 0x000,
     T2D_TARGET_BLEND     = 0x004,
     T2D_TARGET_BAR       = 0x008,
     T2D_TARGET_STRIDE    = 0x00c,
     T2D_TARGET_RESOLXY   = 0x010,
     T2D_DST_COLORKEY     = 0x014,
     T2D_CLIPMIN          = 0x018,
     T2D_CLIPMAX          = 0x01c,
     T2D_DRAW_CMD         = 0x020,
     T2D_DRAW_STARTXY     = 0x024,
     T2D_DRAW_ENDXY       = 0x028,
     T2D_DRAW_COLOR       = 0x02c,
     T2D_BLIT_CMD         = 0x030,
     T2D_BLIT_SRCADDR     = 0x034,
     T2D_BLIT_SRCRESOL    = 0x038,
     T2D_BLIT_SRCSTRIDE   = 0x03c,
     T2D_BLIT_SRCCOLORKEY = 0x040,
     T2D_BLIT_FG_COLOR    = 0x044,
     T2D_BLIT_DSTADDR     = 0x048,
     T2D_BLIT_DSTYXSIZE   = 0x04c,
     T2D_BLIT_SCALE_YFN   = 0x050,
     T2D_BLIT_SCALE_XFN   = 0x054,
     //-----------------------------
     T2D_DRAW_EDGE0_S     = 0x060,
     T2D_DRAW_EDGE0_DX    = 0x064,
     T2D_DRAW_EDGE0_DY    = 0x068,
     T2D_DRAW_EDGE1_S     = 0x06c,
     T2D_DRAW_EDGE1_DX    = 0x070,
     T2D_DRAW_EDGE1_DY    = 0x074,
     T2D_DRAW_EDGE2_S     = 0x078,
     T2D_DRAW_EDGE2_DX    = 0x07c,
     T2D_DRAW_EDGE2_DY    = 0x080,
     T2D_DRAW_EDGE3_S     = 0x084,
     T2D_DRAW_EDGE3_DX    = 0x088,
     T2D_DRAW_EDGE3_DY    = 0x08c,
     //-----------------------------
     T2D_DRAW_RED_S       = 0x090,
     T2D_DRAW_RED_DX      = 0x094,
     T2D_DRAW_RED_DY      = 0x098,
     T2D_DRAW_GRN_S       = 0x09c,
     T2D_DRAW_GRN_DX      = 0x0a0,
     T2D_DRAW_GRN_DY      = 0x0a4,
     T2D_DRAW_BLU_S       = 0x0a8,
     T2D_DRAW_BLU_DX      = 0x0ac,
     T2D_DRAW_BLU_DY      = 0x0b0,
     T2D_DRAW_ALF_S       = 0x0b4,
     T2D_DRAW_ALF_DX      = 0x0b8,
     T2D_DRAW_ALF_DY      = 0x0bc,
     //-----------------------------
     T2D_MMULT_CTRL       = 0x0c0,
     T2D_MMULT_IM00       = 0x0c4,
     T2D_MMULT_IM01       = 0x0c8,
     T2D_MMULT_IM02       = 0x0cc,
     T2D_MMULT_IM10       = 0x0d0,
     T2D_MMULT_IM11       = 0x0d4,
     T2D_MMULT_IM12       = 0x0d8,
     T2D_MMULT_IM20       = 0x0dc,
     T2D_MMULT_IM21       = 0x0e0,
     T2D_MMULT_IM22       = 0x0e4,
     //-----------------------------
     T2D_CACHE_CTRL       = 0x0e8,
     //-----------------------------
     T2D_IDREG            = 0x0ec,
     T2D_CMDADDR          = 0x0f0,
     T2D_CMDSIZE          = 0x0f4,
     T2D_INTERRUPT        = 0x0f8,
     T2D_STATUS           = 0x0fc,
     //-----------------------------
     T2D_JPEG_CTRL        = 0x100,
     T2D_JPEG_ADDR        = 0x104,
     //-----------------------------
     T2D_TEX_MODE         = 0x110,
     T2D_TEX_BAR          = 0x114,
     T2D_TEX_RESYX        = 0x118,
     T2D_TEX_STRIDE       = 0x11c
     //-----------------------------
} T2D_Register;

// Register Index
//-----------------------------------------------------------------------------------------------------------------------
typedef volatile struct __THINK2D {
    u32 regs[64];
} THINK2D;

// Drawing Engine Primitives
//-----------------------------------------------------------------------------------------------------------------------
typedef enum {
    DRAW_LINE     = 0x01,
    DRAW_BOX      = 0x02,
    DRAW_PIXEL    = 0x03,
    DRAW_TRIANGLE = 0x04,
    DRAW_QUAD     = 0x05,
    DRAW_MATMULT  = 0x10
} T2D_Draw_Primitives;

// JPEG Commands
//-----------------------------------------------------------------------------------------------------------------------
typedef enum {
    JPEG_SLEEP    = 0x20000,
    JPEG_RESET    = 0x10002,
    JPEG_GO       = 0x04
} T2D_JPEG_Primitives;

// Hardware Colour Formats Display Modes
//-----------------------------------------------------------------------------------------------------------------------
typedef enum {
        T2D_RGBX8888   =  0x00,
        T2D_RGBA8888   =  0x01,
        T2D_XRGB8888   =  0x02,
        T2D_ARGB8888   =  0x03,

        T2D_RGBA5650   =  0x04,
        T2D_RGBA5551   =  0x05,
        T2D_RGBA4444   =  0x06,

        T2D_RGBA0800   =  0x07,
        T2D_RGBA0008   =  0x08,
        T2D_L8         =  0x09,
        T2D_RGBA3320   =  0x0A,
        T2D_LUT8       =  0x0B,
        T2D_BW1        =  0x0C,
        T2D_UYVY       =  0x0D,
        T2D_JPEG       =  0x0E,

		T2D_BGRA       =  0x10,
		T2D_BGRX       =  0x11
} T2D_VideoMode;
//-----------------------------------------------------------------------------------------------------------------------

// Scaling Direction
//-----------------------------------------------------------------------------------------------------------------------
typedef enum {
        T2D_NOSCALE   =  0x0,
        T2D_UPSCALE   =  0x1,
        T2D_DNSCALE   =  0x2
} T2D_ScaleMode;


// Blending Factor Selector
//-----------------------------------------------------------------------------------------------------------------------
typedef enum {
  DSBF_UNKNOWN             = 0x0,
  DSBF_ZERO                = 0x1,
  DSBF_ONE                 = 0x2,
  DSBF_SRCCOLOR            = 0x3,
  DSBF_INVSRCCOLOR         = 0x4,
  DSBF_SRCALPHA            = 0x5,
  DSBF_INVSRCALPHA         = 0x6,
  DSBF_DESTALPHA           = 0x7,
  DSBF_INVDESTALPHA        = 0x8,
  DSBF_DESTCOLOR           = 0x9,
  DSBF_INVDESTCOLOR        = 0xa,
  DSBF_SRCALPHASAT         = 0xb,

  DST_COLORKEY             = 0x80000000,
  SRC_COLORKEY             = (1<<27),
  SRC_MODULATE_A           = (1<<29),
  SRC_FORCE_A              = (1<<28),
  SRC_COLORIZE             = (1<<30),
  DST_DITHER               = 0x40000000
} T2D_BlendMode;
//-----------------------------------------------------------------------------------------------------------------------
const T2D_BlendMode T2D_SRCCOPY     = (T2D_BlendMode) ((DSBF_ZERO        <<16) | DSBF_ONE );
const T2D_BlendMode T2D_SRCALPHA    = (T2D_BlendMode) ((DSBF_INVSRCALPHA <<16) | DSBF_SRCALPHA);
const T2D_BlendMode T2D_STENCIL     = (T2D_BlendMode) (SRC_COLORIZE | (DSBF_INVSRCCOLOR <<16) | DSBF_SRCCOLOR );
//-----------------------------------------------------------------------------------------------------------------------

// Direct FB (Porter Duff)
const T2D_BlendMode DSPD_NONE       = (T2D_BlendMode) (DSBF_SRCALPHA     | (DSBF_INVSRCALPHA  <<16));
const T2D_BlendMode DSPD_CLEAR      = (T2D_BlendMode) (DSBF_ZERO         | (DSBF_ZERO         <<16));
const T2D_BlendMode DSPD_SRC        = (T2D_BlendMode) (DSBF_ONE          | (DSBF_ZERO         <<16));
const T2D_BlendMode DSPD_SRC_OVER   = (T2D_BlendMode) (DSBF_ONE          | (DSBF_INVSRCALPHA  <<16));
const T2D_BlendMode DSPD_DST_OVER   = (T2D_BlendMode) (DSBF_INVDESTALPHA | (DSBF_ONE          <<16));
const T2D_BlendMode DSPD_SRC_IN     = (T2D_BlendMode) (DSBF_DESTALPHA    | (DSBF_ZERO         <<16));
const T2D_BlendMode DSPD_DST_IN     = (T2D_BlendMode) (DSBF_ZERO         | (DSBF_SRCALPHA     <<16));
const T2D_BlendMode DSPD_SRC_OUT    = (T2D_BlendMode) (DSBF_INVDESTALPHA | (DSBF_ZERO         <<16));
const T2D_BlendMode DSPD_DST_OUT    = (T2D_BlendMode) (DSBF_ZERO         | (DSBF_INVSRCALPHA  <<16));
const T2D_BlendMode DSPD_SRC_ATOP   = (T2D_BlendMode) (DSBF_DESTALPHA    | (DSBF_INVSRCALPHA  <<16));
const T2D_BlendMode DSPD_DST_ATOP   = (T2D_BlendMode) (DSBF_INVDESTALPHA | (DSBF_SRCALPHA     <<16));
const T2D_BlendMode DSPD_ADD        = (T2D_BlendMode) (DSBF_ONE          | (DSBF_ONE          <<16));
const T2D_BlendMode DSPD_XOR        = (T2D_BlendMode) (DSBF_INVDESTALPHA | (DSBF_INVSRCALPHA  <<16));
static T2D_BlendMode T2D_TargetBlend_PorterDuff[13];

// Porter Duff Indexes
//-----------------------------------------------------------------------------------------------------------------------
void init_T2D_TargetBlend_PorterDuff(void) {
    T2D_TargetBlend_PorterDuff[0]  = DSPD_NONE;
    T2D_TargetBlend_PorterDuff[1]  = DSPD_CLEAR;
    T2D_TargetBlend_PorterDuff[2]  = DSPD_SRC;
    T2D_TargetBlend_PorterDuff[3]  = DSPD_SRC_OVER;
    T2D_TargetBlend_PorterDuff[4]  = DSPD_DST_OVER;
    T2D_TargetBlend_PorterDuff[5]  = DSPD_SRC_IN;
    T2D_TargetBlend_PorterDuff[6]  = DSPD_DST_IN;
    T2D_TargetBlend_PorterDuff[7]  = DSPD_SRC_OUT;
    T2D_TargetBlend_PorterDuff[8]  = DSPD_DST_OUT;
    T2D_TargetBlend_PorterDuff[9]  = DSPD_SRC_ATOP;
    T2D_TargetBlend_PorterDuff[10] = DSPD_DST_ATOP;
    T2D_TargetBlend_PorterDuff[11] = DSPD_ADD;
    T2D_TargetBlend_PorterDuff[12] = DSPD_XOR;
}
//-----------------------------------------------------------------------------------------------------------------------

// Rotation Modes
//-----------------------------------------------------------------------------------------------------------------------
typedef enum {
  T2D_DEG000                    = 0x0,
  T2D_DEG090                    = 0x1,
  T2D_DEG180                    = 0x2,
  T2D_DEG270                    = 0x3,
  T2D_MIR_X                     = 0x4,
  T2D_MIR_Y                     = 0x5
} T2D_Rotation;

// Vertex
//-----------------------------------------------------------------------------------------------------------------------
typedef struct __T25D_Vertex {
    float x,y;
    unsigned char r,g,b,a;
} Vertex;

// FON File format
//-----------------------------------------------------------------------------------------------------------------------
struct glyphs {
    int width_x;        // width character's points
    int width_y;        // The image characters in a block of data
    int offset_x;
    int offset_y;
    char data[32];
 };

//-----------------------------------------------------------------------------------------------------------------------
typedef struct Font {
    struct glyphs glyph[256];
} Font;

#endif // __THINK2D_H__
