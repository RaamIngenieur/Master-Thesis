#include "macros.h"

extern "C" 
{

  #define USE_PIXOUT

  __attribute__((naked)) void exoradd()
  {
    unsigned int* lct,*rct,*exoradd,z;
    int column, drange;
    
    read_reg(lct, "v0.w"); /// Read value from interpolator 0
    read_reg(rct, "v0.z"); /// Read value from interpolator 1
    read_reg(exoradd, "v0.y"); /// Read value from interpolator 2

    read_reg(column, "v128.y");
    read_reg(drange, "v128.z");

    ui_vec4 coords;
    read_coords(coords);
    *exoradd =0;

    if (coords.x<(column-drange))
    {
      for (int i=0;i<4;i++)
      {
        z= *lct ^ *rct;
        *exoradd += __builtin_popcount(z);
        lct++;
        rct++;
      } 
    }
  
  }

} // extern "C"
