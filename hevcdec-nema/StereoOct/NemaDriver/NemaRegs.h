//----------------------------------------------
// Generated Hardware Registers
//----------------------------------------------

#ifndef NEMA_HW_REGS
#define NEMA_HW_REGS 1


// Number of Threads per core
#define NEMA_CORES	0x000

// Number of Threads per core
#define NEMA_THREADS	0x004

// Interrupt raised from this core
#define NEMA_INTERRUPT	0x008

// Host Fork Coordinates
#define NEMA_HF_COORDS	0x00c

// Host Fork CodePointer
#define NEMA_HF_CODEPTR	0x010

// Host Fork DataPointer
#define NEMA_HF_DATAPTR	0x014

// Host Fork BasePointer
#define NEMA_BASEPTR	0x018

// Governor Control
#define NEMA_GOV_CONTROL	0x01c

// Cache Base
#define NEMA_CACHEBASE	0x020

// Cache Base
#define NEMA_CACHECTRL	0x024

// DCache Flush
#define NEMA_CACHEFLUSH	0x028

// ICache Flush
#define NEMA_ICACHEFLUSH	0x02c

// Barrier Counter 0
#define NEMA_BARRIERCNT0	0x030

// Barrier Counter 1
#define NEMA_BARRIERCNT1	0x034

// Command List Address
#define NEMA_CMDLIST_A	0x038

// Command List Size
#define NEMA_CMDLIST_S	0x03c

// Vertex 0 XYZW
#define NEMA_VERTEX0  	0x04c
#define NEMA_VERTEX0_0	0x04c
#define NEMA_VERTEX0_W	0x04c
#define NEMA_VERTEX0_A	0x04c
#define NEMA_VERTEX0_Q	0x04c
#define NEMA_VERTEX0_1	0x048
#define NEMA_VERTEX0_Z	0x048
#define NEMA_VERTEX0_B	0x048
#define NEMA_VERTEX0_P	0x048
#define NEMA_VERTEX0_2	0x044
#define NEMA_VERTEX0_Y	0x044
#define NEMA_VERTEX0_G	0x044
#define NEMA_VERTEX0_T	0x044
#define NEMA_VERTEX0_3	0x040
#define NEMA_VERTEX0_X	0x040
#define NEMA_VERTEX0_R	0x040
#define NEMA_VERTEX0_S	0x040

// Vertex 1 XYZW
#define NEMA_VERTEX1  	0x05c
#define NEMA_VERTEX1_0	0x05c
#define NEMA_VERTEX1_W	0x05c
#define NEMA_VERTEX1_A	0x05c
#define NEMA_VERTEX1_Q	0x05c
#define NEMA_VERTEX1_1	0x058
#define NEMA_VERTEX1_Z	0x058
#define NEMA_VERTEX1_B	0x058
#define NEMA_VERTEX1_P	0x058
#define NEMA_VERTEX1_2	0x054
#define NEMA_VERTEX1_Y	0x054
#define NEMA_VERTEX1_G	0x054
#define NEMA_VERTEX1_T	0x054
#define NEMA_VERTEX1_3	0x050
#define NEMA_VERTEX1_X	0x050
#define NEMA_VERTEX1_R	0x050
#define NEMA_VERTEX1_S	0x050

// Vertex 2 XYZW
#define NEMA_VERTEX2  	0x06c
#define NEMA_VERTEX2_0	0x06c
#define NEMA_VERTEX2_W	0x06c
#define NEMA_VERTEX2_A	0x06c
#define NEMA_VERTEX2_Q	0x06c
#define NEMA_VERTEX2_1	0x068
#define NEMA_VERTEX2_Z	0x068
#define NEMA_VERTEX2_B	0x068
#define NEMA_VERTEX2_P	0x068
#define NEMA_VERTEX2_2	0x064
#define NEMA_VERTEX2_Y	0x064
#define NEMA_VERTEX2_G	0x064
#define NEMA_VERTEX2_T	0x064
#define NEMA_VERTEX2_3	0x060
#define NEMA_VERTEX2_X	0x060
#define NEMA_VERTEX2_R	0x060
#define NEMA_VERTEX2_S	0x060

// Rasterizer Command
#define NEMA_RAST_CMD	0x070

// Fragment Code Pointer
#define NEMA_FRAG_PTR	0x074

// Vertex Code Pointer
#define NEMA_VERT_PTR	0x078

// Interpolators Control
#define NEMA_INTERP_CTRL	0x09c

// Target Mode
#define NEMA_TARGET_MODE	0x0a0

// Target Blend
#define NEMA_TARGET_BLEND	0x0a4

// Target Base Addr
#define NEMA_TARGET_BAR	0x0a8

// Target Stride
#define NEMA_TARGET_STRIDE	0x0ac

// Target Resolution
#define NEMA_TARGET_RESOL	0x0b0

// Target ClipMin
#define NEMA_TARGET_CLIPMIN	0x0b4

// Target ClipMax
#define NEMA_TARGET_CLIPMAX	0x0b8

// Control Z Buffer and Stencil
#define NEMA_ZSTENCIL_CTRL	0x0bc

// Z Stencil Base Addr
#define NEMA_ZSTENCIL_BAR	0x0d0

// Z Stencil Stride
#define NEMA_ZSTENCIL_STRIDE	0x0d4

// Texture Mapping Context Addr
#define NEMA_TEXIMGADDR	0x0c0

// Texture Mapping Context Addr
#define NEMA_TEXIMGDATA	0x0c4

// Constant Regs Addr
#define NEMA_CONSTREG_ADDR	0x0c8

// Constant Regs Data
#define NEMA_CONSTREG_DATA	0x0cc

// Nema Magic
#define NEMA_MAGIC	0x0f8

// Nema Busy Status
#define NEMA_STATUS	0x0fc

// Cluster ID Number
#define NEMA_CLUSTERID	0x100

// Core Load
#define NEMA_CORELOAD	0x104

// Cluster's cores load
#define NEMA_CORELOAD0	0x108

// Cluster's cores load
#define NEMA_CORELOAD1	0x10c

// Cluster's cores load
#define NEMA_CORELOAD2	0x110

// Cluster's cores load
#define NEMA_CORELOAD3	0x114

// Upper 32 bit timer
#define NEMA_TIMERHIGH	0x200

// Lower 32 bit timer
#define NEMA_TIMERLOW	0x204

// Number of Vertices
#define NEMA_VERTEX_NUMBER	0x208

// Vertex Attribute Control
#define NEMA_ATTRIB_CTRL	0x20c

// VAR0 Vertex 0
#define NEMA_VAR0_V0  	0x21c
#define NEMA_VAR0_V0_0	0x21c
#define NEMA_VAR0_V0_W	0x21c
#define NEMA_VAR0_V0_A	0x21c
#define NEMA_VAR0_V0_Q	0x21c
#define NEMA_VAR0_V0_1	0x218
#define NEMA_VAR0_V0_Z	0x218
#define NEMA_VAR0_V0_B	0x218
#define NEMA_VAR0_V0_P	0x218
#define NEMA_VAR0_V0_2	0x214
#define NEMA_VAR0_V0_Y	0x214
#define NEMA_VAR0_V0_G	0x214
#define NEMA_VAR0_V0_T	0x214
#define NEMA_VAR0_V0_3	0x210
#define NEMA_VAR0_V0_X	0x210
#define NEMA_VAR0_V0_R	0x210
#define NEMA_VAR0_V0_S	0x210

// VAR0 Vertex 1
#define NEMA_VAR0_V1  	0x22c
#define NEMA_VAR0_V1_0	0x22c
#define NEMA_VAR0_V1_W	0x22c
#define NEMA_VAR0_V1_A	0x22c
#define NEMA_VAR0_V1_Q	0x22c
#define NEMA_VAR0_V1_1	0x228
#define NEMA_VAR0_V1_Z	0x228
#define NEMA_VAR0_V1_B	0x228
#define NEMA_VAR0_V1_P	0x228
#define NEMA_VAR0_V1_2	0x224
#define NEMA_VAR0_V1_Y	0x224
#define NEMA_VAR0_V1_G	0x224
#define NEMA_VAR0_V1_T	0x224
#define NEMA_VAR0_V1_3	0x220
#define NEMA_VAR0_V1_X	0x220
#define NEMA_VAR0_V1_R	0x220
#define NEMA_VAR0_V1_S	0x220

// VAR0 Vertex 2
#define NEMA_VAR0_V2  	0x23c
#define NEMA_VAR0_V2_0	0x23c
#define NEMA_VAR0_V2_W	0x23c
#define NEMA_VAR0_V2_A	0x23c
#define NEMA_VAR0_V2_Q	0x23c
#define NEMA_VAR0_V2_1	0x238
#define NEMA_VAR0_V2_Z	0x238
#define NEMA_VAR0_V2_B	0x238
#define NEMA_VAR0_V2_P	0x238
#define NEMA_VAR0_V2_2	0x234
#define NEMA_VAR0_V2_Y	0x234
#define NEMA_VAR0_V2_G	0x234
#define NEMA_VAR0_V2_T	0x234
#define NEMA_VAR0_V2_3	0x230
#define NEMA_VAR0_V2_X	0x230
#define NEMA_VAR0_V2_R	0x230
#define NEMA_VAR0_V2_S	0x230

// VAR1 Vertex 0
#define NEMA_VAR1_V0  	0x24c
#define NEMA_VAR1_V0_0	0x24c
#define NEMA_VAR1_V0_W	0x24c
#define NEMA_VAR1_V0_A	0x24c
#define NEMA_VAR1_V0_Q	0x24c
#define NEMA_VAR1_V0_1	0x248
#define NEMA_VAR1_V0_Z	0x248
#define NEMA_VAR1_V0_B	0x248
#define NEMA_VAR1_V0_P	0x248
#define NEMA_VAR1_V0_2	0x244
#define NEMA_VAR1_V0_Y	0x244
#define NEMA_VAR1_V0_G	0x244
#define NEMA_VAR1_V0_T	0x244
#define NEMA_VAR1_V0_3	0x240
#define NEMA_VAR1_V0_X	0x240
#define NEMA_VAR1_V0_R	0x240
#define NEMA_VAR1_V0_S	0x240

// VAR1 Vertex 1
#define NEMA_VAR1_V1  	0x25c
#define NEMA_VAR1_V1_0	0x25c
#define NEMA_VAR1_V1_W	0x25c
#define NEMA_VAR1_V1_A	0x25c
#define NEMA_VAR1_V1_Q	0x25c
#define NEMA_VAR1_V1_1	0x258
#define NEMA_VAR1_V1_Z	0x258
#define NEMA_VAR1_V1_B	0x258
#define NEMA_VAR1_V1_P	0x258
#define NEMA_VAR1_V1_2	0x254
#define NEMA_VAR1_V1_Y	0x254
#define NEMA_VAR1_V1_G	0x254
#define NEMA_VAR1_V1_T	0x254
#define NEMA_VAR1_V1_3	0x250
#define NEMA_VAR1_V1_X	0x250
#define NEMA_VAR1_V1_R	0x250
#define NEMA_VAR1_V1_S	0x250

// VAR1 Vertex 2
#define NEMA_VAR1_V2  	0x26c
#define NEMA_VAR1_V2_0	0x26c
#define NEMA_VAR1_V2_W	0x26c
#define NEMA_VAR1_V2_A	0x26c
#define NEMA_VAR1_V2_Q	0x26c
#define NEMA_VAR1_V2_1	0x268
#define NEMA_VAR1_V2_Z	0x268
#define NEMA_VAR1_V2_B	0x268
#define NEMA_VAR1_V2_P	0x268
#define NEMA_VAR1_V2_2	0x264
#define NEMA_VAR1_V2_Y	0x264
#define NEMA_VAR1_V2_G	0x264
#define NEMA_VAR1_V2_T	0x264
#define NEMA_VAR1_V2_3	0x260
#define NEMA_VAR1_V2_X	0x260
#define NEMA_VAR1_V2_R	0x260
#define NEMA_VAR1_V2_S	0x260

// VAR2 Vertex 0
#define NEMA_VAR2_V0  	0x27c
#define NEMA_VAR2_V0_0	0x27c
#define NEMA_VAR2_V0_W	0x27c
#define NEMA_VAR2_V0_A	0x27c
#define NEMA_VAR2_V0_Q	0x27c
#define NEMA_VAR2_V0_1	0x278
#define NEMA_VAR2_V0_Z	0x278
#define NEMA_VAR2_V0_B	0x278
#define NEMA_VAR2_V0_P	0x278
#define NEMA_VAR2_V0_2	0x274
#define NEMA_VAR2_V0_Y	0x274
#define NEMA_VAR2_V0_G	0x274
#define NEMA_VAR2_V0_T	0x274
#define NEMA_VAR2_V0_3	0x270
#define NEMA_VAR2_V0_X	0x270
#define NEMA_VAR2_V0_R	0x270
#define NEMA_VAR2_V0_S	0x270

// VAR2 Vertex 1
#define NEMA_VAR2_V1  	0x28c
#define NEMA_VAR2_V1_0	0x28c
#define NEMA_VAR2_V1_W	0x28c
#define NEMA_VAR2_V1_A	0x28c
#define NEMA_VAR2_V1_Q	0x28c
#define NEMA_VAR2_V1_1	0x288
#define NEMA_VAR2_V1_Z	0x288
#define NEMA_VAR2_V1_B	0x288
#define NEMA_VAR2_V1_P	0x288
#define NEMA_VAR2_V1_2	0x284
#define NEMA_VAR2_V1_Y	0x284
#define NEMA_VAR2_V1_G	0x284
#define NEMA_VAR2_V1_T	0x284
#define NEMA_VAR2_V1_3	0x280
#define NEMA_VAR2_V1_X	0x280
#define NEMA_VAR2_V1_R	0x280
#define NEMA_VAR2_V1_S	0x280

// VAR2 Vertex 2
#define NEMA_VAR2_V2  	0x29c
#define NEMA_VAR2_V2_0	0x29c
#define NEMA_VAR2_V2_W	0x29c
#define NEMA_VAR2_V2_A	0x29c
#define NEMA_VAR2_V2_Q	0x29c
#define NEMA_VAR2_V2_1	0x298
#define NEMA_VAR2_V2_Z	0x298
#define NEMA_VAR2_V2_B	0x298
#define NEMA_VAR2_V2_P	0x298
#define NEMA_VAR2_V2_2	0x294
#define NEMA_VAR2_V2_Y	0x294
#define NEMA_VAR2_V2_G	0x294
#define NEMA_VAR2_V2_T	0x294
#define NEMA_VAR2_V2_3	0x290
#define NEMA_VAR2_V2_X	0x290
#define NEMA_VAR2_V2_R	0x290
#define NEMA_VAR2_V2_S	0x290

// VAR3 Vertex 0
#define NEMA_VAR3_V0  	0x2ac
#define NEMA_VAR3_V0_0	0x2ac
#define NEMA_VAR3_V0_W	0x2ac
#define NEMA_VAR3_V0_A	0x2ac
#define NEMA_VAR3_V0_Q	0x2ac
#define NEMA_VAR3_V0_1	0x2a8
#define NEMA_VAR3_V0_Z	0x2a8
#define NEMA_VAR3_V0_B	0x2a8
#define NEMA_VAR3_V0_P	0x2a8
#define NEMA_VAR3_V0_2	0x2a4
#define NEMA_VAR3_V0_Y	0x2a4
#define NEMA_VAR3_V0_G	0x2a4
#define NEMA_VAR3_V0_T	0x2a4
#define NEMA_VAR3_V0_3	0x2a0
#define NEMA_VAR3_V0_X	0x2a0
#define NEMA_VAR3_V0_R	0x2a0
#define NEMA_VAR3_V0_S	0x2a0

// VAR3 Vertex 1
#define NEMA_VAR3_V1  	0x2bc
#define NEMA_VAR3_V1_0	0x2bc
#define NEMA_VAR3_V1_W	0x2bc
#define NEMA_VAR3_V1_A	0x2bc
#define NEMA_VAR3_V1_Q	0x2bc
#define NEMA_VAR3_V1_1	0x2b8
#define NEMA_VAR3_V1_Z	0x2b8
#define NEMA_VAR3_V1_B	0x2b8
#define NEMA_VAR3_V1_P	0x2b8
#define NEMA_VAR3_V1_2	0x2b4
#define NEMA_VAR3_V1_Y	0x2b4
#define NEMA_VAR3_V1_G	0x2b4
#define NEMA_VAR3_V1_T	0x2b4
#define NEMA_VAR3_V1_3	0x2b0
#define NEMA_VAR3_V1_X	0x2b0
#define NEMA_VAR3_V1_R	0x2b0
#define NEMA_VAR3_V1_S	0x2b0

// VAR3 Vertex 2
#define NEMA_VAR3_V2  	0x2cc
#define NEMA_VAR3_V2_0	0x2cc
#define NEMA_VAR3_V2_W	0x2cc
#define NEMA_VAR3_V2_A	0x2cc
#define NEMA_VAR3_V2_Q	0x2cc
#define NEMA_VAR3_V2_1	0x2c8
#define NEMA_VAR3_V2_Z	0x2c8
#define NEMA_VAR3_V2_B	0x2c8
#define NEMA_VAR3_V2_P	0x2c8
#define NEMA_VAR3_V2_2	0x2c4
#define NEMA_VAR3_V2_Y	0x2c4
#define NEMA_VAR3_V2_G	0x2c4
#define NEMA_VAR3_V2_T	0x2c4
#define NEMA_VAR3_V2_3	0x2c0
#define NEMA_VAR3_V2_X	0x2c0
#define NEMA_VAR3_V2_R	0x2c0
#define NEMA_VAR3_V2_S	0x2c0

// VAR4 Vertex 0
#define NEMA_VAR4_V0  	0x2dc
#define NEMA_VAR4_V0_0	0x2dc
#define NEMA_VAR4_V0_W	0x2dc
#define NEMA_VAR4_V0_A	0x2dc
#define NEMA_VAR4_V0_Q	0x2dc
#define NEMA_VAR4_V0_1	0x2d8
#define NEMA_VAR4_V0_Z	0x2d8
#define NEMA_VAR4_V0_B	0x2d8
#define NEMA_VAR4_V0_P	0x2d8
#define NEMA_VAR4_V0_2	0x2d4
#define NEMA_VAR4_V0_Y	0x2d4
#define NEMA_VAR4_V0_G	0x2d4
#define NEMA_VAR4_V0_T	0x2d4
#define NEMA_VAR4_V0_3	0x2d0
#define NEMA_VAR4_V0_X	0x2d0
#define NEMA_VAR4_V0_R	0x2d0
#define NEMA_VAR4_V0_S	0x2d0

// VAR4 Vertex 1
#define NEMA_VAR4_V1  	0x2ec
#define NEMA_VAR4_V1_0	0x2ec
#define NEMA_VAR4_V1_W	0x2ec
#define NEMA_VAR4_V1_A	0x2ec
#define NEMA_VAR4_V1_Q	0x2ec
#define NEMA_VAR4_V1_1	0x2e8
#define NEMA_VAR4_V1_Z	0x2e8
#define NEMA_VAR4_V1_B	0x2e8
#define NEMA_VAR4_V1_P	0x2e8
#define NEMA_VAR4_V1_2	0x2e4
#define NEMA_VAR4_V1_Y	0x2e4
#define NEMA_VAR4_V1_G	0x2e4
#define NEMA_VAR4_V1_T	0x2e4
#define NEMA_VAR4_V1_3	0x2e0
#define NEMA_VAR4_V1_X	0x2e0
#define NEMA_VAR4_V1_R	0x2e0
#define NEMA_VAR4_V1_S	0x2e0

// VAR4 Vertex 2
#define NEMA_VAR4_V2  	0x2fc
#define NEMA_VAR4_V2_0	0x2fc
#define NEMA_VAR4_V2_W	0x2fc
#define NEMA_VAR4_V2_A	0x2fc
#define NEMA_VAR4_V2_Q	0x2fc
#define NEMA_VAR4_V2_1	0x2f8
#define NEMA_VAR4_V2_Z	0x2f8
#define NEMA_VAR4_V2_B	0x2f8
#define NEMA_VAR4_V2_P	0x2f8
#define NEMA_VAR4_V2_2	0x2f4
#define NEMA_VAR4_V2_Y	0x2f4
#define NEMA_VAR4_V2_G	0x2f4
#define NEMA_VAR4_V2_T	0x2f4
#define NEMA_VAR4_V2_3	0x2f0
#define NEMA_VAR4_V2_X	0x2f0
#define NEMA_VAR4_V2_R	0x2f0
#define NEMA_VAR4_V2_S	0x2f0

// VAR5 Vertex 0
#define NEMA_VAR5_V0  	0x30c
#define NEMA_VAR5_V0_0	0x30c
#define NEMA_VAR5_V0_W	0x30c
#define NEMA_VAR5_V0_A	0x30c
#define NEMA_VAR5_V0_Q	0x30c
#define NEMA_VAR5_V0_1	0x308
#define NEMA_VAR5_V0_Z	0x308
#define NEMA_VAR5_V0_B	0x308
#define NEMA_VAR5_V0_P	0x308
#define NEMA_VAR5_V0_2	0x304
#define NEMA_VAR5_V0_Y	0x304
#define NEMA_VAR5_V0_G	0x304
#define NEMA_VAR5_V0_T	0x304
#define NEMA_VAR5_V0_3	0x300
#define NEMA_VAR5_V0_X	0x300
#define NEMA_VAR5_V0_R	0x300
#define NEMA_VAR5_V0_S	0x300

// VAR5 Vertex 1
#define NEMA_VAR5_V1  	0x31c
#define NEMA_VAR5_V1_0	0x31c
#define NEMA_VAR5_V1_W	0x31c
#define NEMA_VAR5_V1_A	0x31c
#define NEMA_VAR5_V1_Q	0x31c
#define NEMA_VAR5_V1_1	0x318
#define NEMA_VAR5_V1_Z	0x318
#define NEMA_VAR5_V1_B	0x318
#define NEMA_VAR5_V1_P	0x318
#define NEMA_VAR5_V1_2	0x314
#define NEMA_VAR5_V1_Y	0x314
#define NEMA_VAR5_V1_G	0x314
#define NEMA_VAR5_V1_T	0x314
#define NEMA_VAR5_V1_3	0x310
#define NEMA_VAR5_V1_X	0x310
#define NEMA_VAR5_V1_R	0x310
#define NEMA_VAR5_V1_S	0x310

// VAR5 Vertex 2
#define NEMA_VAR5_V2  	0x32c
#define NEMA_VAR5_V2_0	0x32c
#define NEMA_VAR5_V2_W	0x32c
#define NEMA_VAR5_V2_A	0x32c
#define NEMA_VAR5_V2_Q	0x32c
#define NEMA_VAR5_V2_1	0x328
#define NEMA_VAR5_V2_Z	0x328
#define NEMA_VAR5_V2_B	0x328
#define NEMA_VAR5_V2_P	0x328
#define NEMA_VAR5_V2_2	0x324
#define NEMA_VAR5_V2_Y	0x324
#define NEMA_VAR5_V2_G	0x324
#define NEMA_VAR5_V2_T	0x324
#define NEMA_VAR5_V2_3	0x320
#define NEMA_VAR5_V2_X	0x320
#define NEMA_VAR5_V2_R	0x320
#define NEMA_VAR5_V2_S	0x320

// VAR6 Vertex 0
#define NEMA_VAR6_V0  	0x33c
#define NEMA_VAR6_V0_0	0x33c
#define NEMA_VAR6_V0_W	0x33c
#define NEMA_VAR6_V0_A	0x33c
#define NEMA_VAR6_V0_Q	0x33c
#define NEMA_VAR6_V0_1	0x338
#define NEMA_VAR6_V0_Z	0x338
#define NEMA_VAR6_V0_B	0x338
#define NEMA_VAR6_V0_P	0x338
#define NEMA_VAR6_V0_2	0x334
#define NEMA_VAR6_V0_Y	0x334
#define NEMA_VAR6_V0_G	0x334
#define NEMA_VAR6_V0_T	0x334
#define NEMA_VAR6_V0_3	0x330
#define NEMA_VAR6_V0_X	0x330
#define NEMA_VAR6_V0_R	0x330
#define NEMA_VAR6_V0_S	0x330

// VAR6 Vertex 1
#define NEMA_VAR6_V1  	0x34c
#define NEMA_VAR6_V1_0	0x34c
#define NEMA_VAR6_V1_W	0x34c
#define NEMA_VAR6_V1_A	0x34c
#define NEMA_VAR6_V1_Q	0x34c
#define NEMA_VAR6_V1_1	0x348
#define NEMA_VAR6_V1_Z	0x348
#define NEMA_VAR6_V1_B	0x348
#define NEMA_VAR6_V1_P	0x348
#define NEMA_VAR6_V1_2	0x344
#define NEMA_VAR6_V1_Y	0x344
#define NEMA_VAR6_V1_G	0x344
#define NEMA_VAR6_V1_T	0x344
#define NEMA_VAR6_V1_3	0x340
#define NEMA_VAR6_V1_X	0x340
#define NEMA_VAR6_V1_R	0x340
#define NEMA_VAR6_V1_S	0x340

// VAR6 Vertex 2
#define NEMA_VAR6_V2  	0x35c
#define NEMA_VAR6_V2_0	0x35c
#define NEMA_VAR6_V2_W	0x35c
#define NEMA_VAR6_V2_A	0x35c
#define NEMA_VAR6_V2_Q	0x35c
#define NEMA_VAR6_V2_1	0x358
#define NEMA_VAR6_V2_Z	0x358
#define NEMA_VAR6_V2_B	0x358
#define NEMA_VAR6_V2_P	0x358
#define NEMA_VAR6_V2_2	0x354
#define NEMA_VAR6_V2_Y	0x354
#define NEMA_VAR6_V2_G	0x354
#define NEMA_VAR6_V2_T	0x354
#define NEMA_VAR6_V2_3	0x350
#define NEMA_VAR6_V2_X	0x350
#define NEMA_VAR6_V2_R	0x350
#define NEMA_VAR6_V2_S	0x350

// VAR7 Vertex 0
#define NEMA_VAR7_V0  	0x36c
#define NEMA_VAR7_V0_0	0x36c
#define NEMA_VAR7_V0_W	0x36c
#define NEMA_VAR7_V0_A	0x36c
#define NEMA_VAR7_V0_Q	0x36c
#define NEMA_VAR7_V0_1	0x368
#define NEMA_VAR7_V0_Z	0x368
#define NEMA_VAR7_V0_B	0x368
#define NEMA_VAR7_V0_P	0x368
#define NEMA_VAR7_V0_2	0x364
#define NEMA_VAR7_V0_Y	0x364
#define NEMA_VAR7_V0_G	0x364
#define NEMA_VAR7_V0_T	0x364
#define NEMA_VAR7_V0_3	0x360
#define NEMA_VAR7_V0_X	0x360
#define NEMA_VAR7_V0_R	0x360
#define NEMA_VAR7_V0_S	0x360

// VAR7 Vertex 1
#define NEMA_VAR7_V1  	0x37c
#define NEMA_VAR7_V1_0	0x37c
#define NEMA_VAR7_V1_W	0x37c
#define NEMA_VAR7_V1_A	0x37c
#define NEMA_VAR7_V1_Q	0x37c
#define NEMA_VAR7_V1_1	0x378
#define NEMA_VAR7_V1_Z	0x378
#define NEMA_VAR7_V1_B	0x378
#define NEMA_VAR7_V1_P	0x378
#define NEMA_VAR7_V1_2	0x374
#define NEMA_VAR7_V1_Y	0x374
#define NEMA_VAR7_V1_G	0x374
#define NEMA_VAR7_V1_T	0x374
#define NEMA_VAR7_V1_3	0x370
#define NEMA_VAR7_V1_X	0x370
#define NEMA_VAR7_V1_R	0x370
#define NEMA_VAR7_V1_S	0x370

// VAR7 Vertex 2
#define NEMA_VAR7_V2  	0x38c
#define NEMA_VAR7_V2_0	0x38c
#define NEMA_VAR7_V2_W	0x38c
#define NEMA_VAR7_V2_A	0x38c
#define NEMA_VAR7_V2_Q	0x38c
#define NEMA_VAR7_V2_1	0x388
#define NEMA_VAR7_V2_Z	0x388
#define NEMA_VAR7_V2_B	0x388
#define NEMA_VAR7_V2_P	0x388
#define NEMA_VAR7_V2_2	0x384
#define NEMA_VAR7_V2_Y	0x384
#define NEMA_VAR7_V2_G	0x384
#define NEMA_VAR7_V2_T	0x384
#define NEMA_VAR7_V2_3	0x380
#define NEMA_VAR7_V2_X	0x380
#define NEMA_VAR7_V2_R	0x380
#define NEMA_VAR7_V2_S	0x380

// DEBUG0
#define NEMA_DEBUG0	0x390

// DEBUG1
#define NEMA_DEBUG1	0x394

// DEBUG2
#define NEMA_DEBUG2	0x398

// DEBUG3
#define NEMA_DEBUG3	0x39c

// DEBUG4
#define NEMA_DEBUG4	0x3a0

// DEBUG5
#define NEMA_DEBUG5	0x3a4

// DEBUG6
#define NEMA_DEBUG6	0x3a8

// DEBUG7
#define NEMA_DEBUG7	0x3ac

// DEBUG8
#define NEMA_DEBUG8	0x3b0

// DEBUG9
#define NEMA_DEBUG9	0x3b4

// DEBUGA
#define NEMA_DEBUGA	0x3b8

// DEBUGB
#define NEMA_DEBUGB	0x3bc

// DEBUGC
#define NEMA_DEBUGC	0x3c0

// DEBUGD
#define NEMA_DEBUGD	0x3c4

// DEBUGE
#define NEMA_DEBUGE	0x3c8

// DEBUGF
#define NEMA_DEBUGF	0x3cc

// End of HW registers
#define NEMA_MAX_HW_REGISTER	0x3fc

#endif
//----------------------------------------------
