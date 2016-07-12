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
  if(nema_init())
  {
    std::cerr << "Error initializing nema." << std::endl;
    return false;
  }

  m_isInited = true;

  m_xres = column;
  m_yres = row;

  total_time = 0.0;


  tsi_cmdl_add_cmd(NEMA_TARGET_CLIPMAX, ((m_yres-1) << 16) | (m_xres-1));
  tsi_cmdl_add_cmd(NEMA_TARGET_BLEND,   (DSBF_ZERO << 16) | (DSBF_ONE));

  /// Set up rasterizer
  tsi_cmdl_add_cmd(NEMA_VERTEX0_X, 0);
  tsi_cmdl_add_cmd(NEMA_VERTEX0_Y, 0);

  tsi_cmdl_add_cmd(NEMA_VERTEX1_X, m_xres - 1);
  tsi_cmdl_add_cmd(NEMA_VERTEX1_Y, m_yres - 1);

  return true;
}

void Nema::negate(unsigned int  *pic, int row, int column)
{
  int width, height;



  /// Load binary
  void *bin = nema_load_binary("kernels/negate.bin");
  assert(bin);

  tsi_cmdl_add_cmd(NEMA_FRAG_PTR, ::nema_virt_to_phys((uint32_t)bin));

  width  = column;
  height = row;

        /// Set up rasterizer dimensions
    /// The rasterizer will generate ( width - 1 ) x ( height - 1 ) threads
  tsi_cmdl_add_cmd(NEMA_VERTEX1_X, width - 1);
  tsi_cmdl_add_cmd(NEMA_VERTEX1_Y, height - 1);



  /// Setup Interpolators
  tsi_cmdl_add_cmd(NEMA_VAR0_V1_0, width * 4);   /// Interpolator 0 stride
  tsi_cmdl_add_cmd(NEMA_VAR0_V2_0, 4);       /// Interpolator 0 step

  tsi_cmdl_add_cmd(NEMA_VAR0_V0_0, (uint32_t)nema_virt_to_phys((uint32_t)pic)); /// Interpolator 0 start



  /// RAST GO
  tsi_cmdl_add_cmd(HOLD_DMA | NEMA_RAST_CMD, 0x02);

  nema_cmdl_flush_caches();

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
