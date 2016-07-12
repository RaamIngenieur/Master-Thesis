#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <iostream>
#include <vector>
#include <time.h>
#include <sys/time.h>

#include "nema.h"
#include "NemaDriver/Think2D.h"
#include "NemaDriver/NemaUtils.h"
#include "NemaDriver/tsi_cmdlist.h"
#include "NemaDriver/NemaRegs.h"

#define HOLD_DMA        0xff000000

static void
Nema_setconst(int reg, int comp, uint32_t value)
{
	tsi_cmdl_add_cmd(NEMA_CONSTREG_ADDR,(reg<<4) | (1<<comp) );
	tsi_cmdl_add_cmd(NEMA_CONSTREG_DATA, value );
}

Nema::Nema(void)
{
  m_isInited = false;
}

void
Nema::shutDown(void)
{
  printf("\nTotal time spent memcpy'ing: %.3f\n", total_time);
  ::nema_shutdown();
}

bool
Nema::init(int row, int column)
{
  if(nema_init()) {
    std::cerr << "Error initializing nema." << std::endl;
    return false;
  }

  m_isInited = true;

  m_xres = column;
  m_yres = row;

  total_time = 0.0;

 /*
  /// Get frame buffer pointer
  thinklcdml_reg_read(0x3c, &m_fbp);
  printf("m_fbp: 0x%08x\n", m_fbp);
  printf("point2\n");

  /// Set up blender
  tsi_cmdl_add_cmd(NEMA_TARGET_MODE,    T2D_LUT8);
  tsi_cmdl_add_cmd(NEMA_TARGET_BAR,     m_fbp);
  tsi_cmdl_add_cmd(NEMA_TARGET_STRIDE,  m_xres);
  tsi_cmdl_add_cmd(NEMA_TARGET_RESOL,   (m_yres << 16) | m_xres);*/
  tsi_cmdl_add_cmd(NEMA_TARGET_CLIPMAX, ((m_yres-1) << 16) | (m_xres-1));
  tsi_cmdl_add_cmd(NEMA_TARGET_BLEND,   (DSBF_ZERO << 16) | (DSBF_ONE));

  /// Set up rasterizer
  tsi_cmdl_add_cmd(NEMA_VERTEX0_X, 0);
  tsi_cmdl_add_cmd(NEMA_VERTEX0_Y, 0);

  tsi_cmdl_add_cmd(NEMA_VERTEX1_X, m_xres - 1);
  tsi_cmdl_add_cmd(NEMA_VERTEX1_Y, m_yres - 1);

  tsi_cmdl_add_cmd(NEMA_VAR1_V0_3, 1); /// stepx
  tsi_cmdl_add_cmd(NEMA_VAR1_V0_2, 1); /// stepy

 /* 
  int reg = 0, index = 0;
  tsi_cmdl_add_cmd(NEMA_CONSTREG_ADDR,(reg<<4) | (1<<index));
  tsi_cmdl_add_cmd(NEMA_CONSTREG_DATA, (uint32_t)m_fbp);
*/

  return true;
}

void Nema::erode(unsigned char* input,unsigned char *output, int row, int column)
{
  int width, height;

  /// Load binary
  void *bin = nema_load_binary("kernels/erode.bin");
  assert(bin);

  tsi_cmdl_add_cmd(NEMA_FRAG_PTR, ::nema_virt_to_phys((uint32_t)bin));

  /// Now that the video dimensions are known reprogram rasterizer and the interpolators
  width  = column;
  height = row;

    /// Everything drawn outside this viewport is clipped out
  tsi_cmdl_add_cmd(NEMA_TARGET_RESOL,  (height << 16) | width);

    /// Set up rasterizer dimensions
    /// The rasterizer will generate ( width - 1 ) x ( height - 1 ) threads
  tsi_cmdl_add_cmd(NEMA_VERTEX1_X, width - 1);
  tsi_cmdl_add_cmd(NEMA_VERTEX1_Y, height - 1);

  tsi_cmdl_add_cmd(NEMA_VAR0_V1_0, width);   /// Interpolator 0 stride
  tsi_cmdl_add_cmd(NEMA_VAR0_V2_0, 1);       /// Interpolator 0 step

  tsi_cmdl_add_cmd(NEMA_VAR0_V1_1, width);   /// Interpolator 1 stride
  tsi_cmdl_add_cmd(NEMA_VAR0_V2_1, 1);       /// Interpolator 1 step

  /// Setup Interpolators
  tsi_cmdl_add_cmd(NEMA_VAR0_V0_0, (uint32_t)nema_virt_to_phys((uint32_t)input)); /// Interpolator 0 start
  tsi_cmdl_add_cmd(NEMA_VAR0_V0_1, (uint32_t)nema_virt_to_phys((uint32_t)output)); /// Interpolator 1 start

  Nema_setconst(0, 0, row);
  Nema_setconst(0, 1, column);

  /// RAST GO
  tsi_cmdl_add_cmd(HOLD_DMA | NEMA_RAST_CMD, 0x02);


  nema_cmdl_flush_caches();
  tsi_cmdl_emit_commands(0);
}

void Nema::dilate(unsigned char* input,unsigned char *output, int row, int column)
{
  int width, height;

  /// Load binary
  void *bin = nema_load_binary("kernels/dilate.bin");
  assert(bin);

  tsi_cmdl_add_cmd(NEMA_FRAG_PTR, ::nema_virt_to_phys((uint32_t)bin));

  /// Now that the video dimensions are known reprogram rasterizer and the interpolators
  width  = column;
  height = row;

    /// Everything drawn outside this viewport is clipped out
  tsi_cmdl_add_cmd(NEMA_TARGET_RESOL,  (height << 16) | width);

    /// Set up rasterizer dimensions
    /// The rasterizer will generate ( width - 1 ) x ( height - 1 ) threads
  tsi_cmdl_add_cmd(NEMA_VERTEX1_X, width - 1);
  tsi_cmdl_add_cmd(NEMA_VERTEX1_Y, height - 1);

  tsi_cmdl_add_cmd(NEMA_VAR0_V1_0, width);   /// Interpolator 0 stride
  tsi_cmdl_add_cmd(NEMA_VAR0_V2_0, 1);       /// Interpolator 0 step

  tsi_cmdl_add_cmd(NEMA_VAR0_V1_1, width);   /// Interpolator 1 stride
  tsi_cmdl_add_cmd(NEMA_VAR0_V2_1, 1);       /// Interpolator 1 step

  /// Setup Interpolators
  tsi_cmdl_add_cmd(NEMA_VAR0_V0_0, (uint32_t)nema_virt_to_phys((uint32_t)input)); /// Interpolator 0 start
  tsi_cmdl_add_cmd(NEMA_VAR0_V0_1, (uint32_t)nema_virt_to_phys((uint32_t)output)); /// Interpolator 1 start

  Nema_setconst(0, 0, row);
  Nema_setconst(0, 1, column);

  /// RAST GO
  tsi_cmdl_add_cmd(HOLD_DMA | NEMA_RAST_CMD, 0x02);


  nema_cmdl_flush_caches();
  tsi_cmdl_emit_commands(0);
}

void Nema::c11(unsigned char* input,unsigned int *output, int row, int column)
{
  int width, height;

  /// Load binary
  void *bin = nema_load_binary("kernels/c11.bin");
  assert(bin);

  tsi_cmdl_add_cmd(NEMA_FRAG_PTR, ::nema_virt_to_phys((uint32_t)bin));

  /// Now that the video dimensions are known reprogram rasterizer and the interpolators
  width  = column;
  height = row;

    /// Everything drawn outside this viewport is clipped out
  tsi_cmdl_add_cmd(NEMA_TARGET_RESOL,  (height << 16) | width);

    /// Set up rasterizer dimensions
    /// The rasterizer will generate ( width - 1 ) x ( height - 1 ) threads
  tsi_cmdl_add_cmd(NEMA_VERTEX1_X, width - 1);
  tsi_cmdl_add_cmd(NEMA_VERTEX1_Y, height - 1);

  tsi_cmdl_add_cmd(NEMA_VAR0_V1_0, width);   /// Interpolator 0 stride
  tsi_cmdl_add_cmd(NEMA_VAR0_V2_0, 1);       /// Interpolator 0 step

  tsi_cmdl_add_cmd(NEMA_VAR0_V1_1, width*16);   /// Interpolator 1 stride
  tsi_cmdl_add_cmd(NEMA_VAR0_V2_1, 16);       /// Interpolator 1 step

  /// Setup Interpolators
  tsi_cmdl_add_cmd(NEMA_VAR0_V0_0, (uint32_t)nema_virt_to_phys((uint32_t)input)); /// Interpolator 0 start
  tsi_cmdl_add_cmd(NEMA_VAR0_V0_1, (uint32_t)nema_virt_to_phys((uint32_t)output)); /// Interpolator 1 start

  Nema_setconst(0, 0, row);
  Nema_setconst(0, 1, column);

  /// RAST GO
  tsi_cmdl_add_cmd(HOLD_DMA | NEMA_RAST_CMD, 0x02);



  nema_cmdl_flush_caches();
  tsi_cmdl_emit_commands(0);
}

void Nema::exoradd(unsigned int* exoradd, unsigned int  *lct, unsigned int  *rct, int row, int column, int drange,bool load)
{
  int width, height;
  /// Now that the video dimensions are known reprogram rasterizer and the interpolators
  width  = column;
  height = row;


    /// Load binary
    void *bin = nema_load_binary("kernels/exoradd.bin");
    assert(bin);

    tsi_cmdl_add_cmd(NEMA_FRAG_PTR, ::nema_virt_to_phys((uint32_t)bin));

    /// Set up window clip coordinates (viewport) to (0, width) x (0, height)
    /// Everything drawn outside this viewport is clipped out
    tsi_cmdl_add_cmd(NEMA_TARGET_RESOL,  (height << 16) | width);

    /// Set up rasterizer dimensions
    /// The rasterizer will generate ( width - 1 ) x ( height - 1 ) threads
    tsi_cmdl_add_cmd(NEMA_VERTEX1_X, width - 1);
    tsi_cmdl_add_cmd(NEMA_VERTEX1_Y, height - 1);
  

  tsi_cmdl_add_cmd(NEMA_VAR0_V1_0, width * 16);   /// Interpolator 0 stride
  tsi_cmdl_add_cmd(NEMA_VAR0_V2_0, 16);       /// Interpolator 0 step

  tsi_cmdl_add_cmd(NEMA_VAR0_V1_1, width * 16);   /// Interpolator 1 stride
  tsi_cmdl_add_cmd(NEMA_VAR0_V2_1, 16);       /// Interpolator 1 step

  tsi_cmdl_add_cmd(NEMA_VAR0_V1_2, width * 4);   /// Interpolator 2 stride
  tsi_cmdl_add_cmd(NEMA_VAR0_V2_2, 4);       /// Interpolator 2 step

  /// Setup Interpolators
  ///v0.w
  tsi_cmdl_add_cmd(NEMA_VAR0_V0_0, (uint32_t)nema_virt_to_phys((uint32_t)(lct+drange*4))); /// Interpolator 0 start
  tsi_cmdl_add_cmd(NEMA_VAR0_V0_1, (uint32_t)nema_virt_to_phys((uint32_t)rct)); /// Interpolator 1 start
  tsi_cmdl_add_cmd(NEMA_VAR0_V0_2, (uint32_t)nema_virt_to_phys((uint32_t)exoradd)); /// Interpolator 2 start

  Nema_setconst(0, 0, row);
  Nema_setconst(0, 1, column);
  Nema_setconst(0, 2, drange);
  Nema_setconst(0, 3, 0);
//  Nema_setconst(0, 1, (uint32_t)nema_virt_to_phys((uint32_t)pic->pCb_nema));
//  Nema_setconst(0, 2, (uint32_t)nema_virt_to_phys((uint32_t)pic->pCr_nema));
//  Nema_setconst(0, 3, (uint32_t)nema_virt_to_phys((uint32_t)pic->pLuma_nema));

  /// RAST GO
  tsi_cmdl_add_cmd(HOLD_DMA | NEMA_RAST_CMD, 0x02);



  nema_cmdl_flush_caches();

  /// Flush command list
//  nema_flush();
    tsi_cmdl_emit_commands(0);
}

void Nema::shd(unsigned int* exoradd, unsigned int* hdis, unsigned int *result, int row, int column,int drange,bool load)
{
  int width, height;

  /// Now that the video dimensions are known reprogram rasterizer and the interpolators
  width  = column;
  height = row;

    /// Load binary
    void *bin = nema_load_binary("kernels/shd.bin");
    assert(bin);

    tsi_cmdl_add_cmd(NEMA_FRAG_PTR, ::nema_virt_to_phys((uint32_t)bin));

    /// Set up window clip coordinates (viewport) to (0, width) x (0, height)
    /// Everything drawn outside this viewport is clipped out
    tsi_cmdl_add_cmd(NEMA_TARGET_RESOL,  (height << 16) | width);

    /// Set up rasterizer dimensionsms pain
    /// The rasterizer will generate ( width - 1 ) x ( height - 1 ) threads
    tsi_cmdl_add_cmd(NEMA_VERTEX1_X, width - 1);
    tsi_cmdl_add_cmd(NEMA_VERTEX1_Y, height - 1);


  tsi_cmdl_add_cmd(NEMA_VAR0_V1_0, width * 4);   /// Interpolator 0 stride
  tsi_cmdl_add_cmd(NEMA_VAR0_V2_0, 4);       /// Interpolator 0 step

  tsi_cmdl_add_cmd(NEMA_VAR0_V1_1, width * 4);   /// Interpolator 1 stride
  tsi_cmdl_add_cmd(NEMA_VAR0_V2_1, 4);       /// Interpolator 1 step

  tsi_cmdl_add_cmd(NEMA_VAR0_V1_2, width * 4);   /// Interpolator 1 stride
  tsi_cmdl_add_cmd(NEMA_VAR0_V2_2, 4);       /// Interpolator 1 step


  /// Setup Interpolators
  ///v0.w
  tsi_cmdl_add_cmd(NEMA_VAR0_V0_0, (uint32_t)nema_virt_to_phys((uint32_t)exoradd)); /// Interpolator 0 start
  tsi_cmdl_add_cmd(NEMA_VAR0_V0_1, (uint32_t)nema_virt_to_phys((uint32_t)hdis)); /// Interpolator 1 start
  tsi_cmdl_add_cmd(NEMA_VAR0_V0_2, (uint32_t)nema_virt_to_phys((uint32_t)result)); /// Interpolator 1 start

  Nema_setconst(0, 0, row);
  Nema_setconst(0, 1, column);
  Nema_setconst(0, 2, drange);
  Nema_setconst(0, 3, 1);
//  Nema_setconst(0, 1, (uint32_t)nema_virt_to_phys((uint32_t)pic->pCb_nema));
//  Nema_setconst(0, 2, (uint32_t)nema_virt_to_phys((uint32_t)pic->pCr_nema));
//  Nema_setconst(0, 3, (uint32_t)nema_virt_to_phys((uint32_t)pic->pLuma_nema));

  /// RAST GO
  tsi_cmdl_add_cmd(HOLD_DMA | NEMA_RAST_CMD, 0x02);



  nema_cmdl_flush_caches();

  /// Flush command list
//  nema_flush();
    tsi_cmdl_emit_commands(0);
}

void Nema::negate(unsigned int  *pic, int row, int column)
{
  int width, height;

  /// Load binary
  void *bin = nema_load_binary("kernels/negate.bin");
  assert(bin);

  tsi_cmdl_add_cmd(NEMA_FRAG_PTR, ::nema_virt_to_phys((uint32_t)bin));

  /// Now that the video dimensions are known reprogram rasterizer and the interpolators
  width  = column;
  height = row;
//    width = pic->uiCWidth * 2;
//    height = pic->uiCHeight * 2;

  printf("\n %d x %d \n", width, height);

    /// Set up window clip coordinates (viewport) to (0, width) x (0, height)
    /// Everything drawn outside this viewport is clipped out
  tsi_cmdl_add_cmd(NEMA_TARGET_RESOL,  (height << 16) | width);

    /// Set up rasterizer dimensions
    /// The rasterizer will generate ( width - 1 ) x ( height - 1 ) threads
  tsi_cmdl_add_cmd(NEMA_VERTEX1_X, width - 1);
  tsi_cmdl_add_cmd(NEMA_VERTEX1_Y, height - 1);

  tsi_cmdl_add_cmd(NEMA_VAR0_V1_0, width * 4);   /// Interpolator 0 stride
  tsi_cmdl_add_cmd(NEMA_VAR0_V2_0, 4);       /// Interpolator 0 step

  /// Setup Interpolators
  ///v0.w
  tsi_cmdl_add_cmd(NEMA_VAR0_V0_0, (uint32_t)nema_virt_to_phys((uint32_t)pic)); /// Interpolator 0 start

  Nema_setconst(0, 0, row);
  Nema_setconst(0, 1, column);
//  Nema_setconst(0, 1, (uint32_t)nema_virt_to_phys((uint32_t)pic->pCb_nema));
//  Nema_setconst(0, 2, (uint32_t)nema_virt_to_phys((uint32_t)pic->pCr_nema));
//  Nema_setconst(0, 3, (uint32_t)nema_virt_to_phys((uint32_t)pic->pLuma_nema));

  /// RAST GO
  tsi_cmdl_add_cmd(NEMA_RAST_CMD, 0x02);

  tsi_cmdl_add_cmd(HOLD_DMA | NEMA_INTERRUPT, 0x4);

  nema_cmdl_flush_caches();

  /// Flush command list
//  nema_flush();
    tsi_cmdl_emit_commands(0);
}


void *
Nema::nema_malloc(size_t size)
{
  return ::nema_malloc(size);
}

void
Nema::nema_free(void *ptr)
{
  ::nema_free(ptr);
}

void Nema::wait_for_interrupt(void)
{
    nema_wait_for_interrupt();
}

void Nema::wait_for_status(void)
{
    nema_wait_for_status();
}
