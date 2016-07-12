#include "macros.h"

extern "C" 
{

  #define USE_PIXOUT

  __attribute__((naked)) void shd()
  {
    int row, column, drange, y;
    unsigned int  *exoradd,*HammDistY, *w;

    read_reg(row, "v128.x");
    read_reg(column, "v128.y");
    read_reg(drange, "v128.z");
  
    ui_vec4 coords;
    read_coords(coords);
    
    read_reg(exoradd, "v0.w"); /// Read value from interpolator 0
    read_reg(HammDistY, "v0.z"); /// Read value from interpolator 1

    y = 0;
    if(coords.y>5 && coords.y<(row-6))
    {
      w = exoradd - 6*column;
      for (int k = 12; k >= 0; k--)
      {
        y+= *w;
        w = w + column;
      }
        *HammDistY = y;
    }
  }

} // extern "C"
