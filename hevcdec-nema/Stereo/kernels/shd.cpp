#include "macros.h"

extern "C" 
{

  #define USE_PIXOUT

  __attribute__((naked)) void shd()
  {
    int row, column, drange, y;
    unsigned int  *exoradd,*hdis,*result, *w;

    read_reg(row, "v128.x");
    read_reg(column, "v128.y");
    read_reg(drange, "v128.z");
  
    ui_vec4 coords;
    read_coords(coords);
    
    read_reg(exoradd, "v0.w"); /// Read value from interpolator 0
    read_reg(hdis, "v0.z"); /// Read value from interpolator 1
    read_reg(result, "v0.y"); /// Read value from interpolator 2

    y = 0;
    if(coords.x>5 && coords.x<(column-6-drange) &&coords.y>5 && coords.y<(row-6))
    {
      w = exoradd - 6*(column + 1);
      for (int k = 12; k >= 0; k--)
      {
        for (int l = 12; l >= 0; l--)
        {
          y+= *w;
          if (y>*hdis) break;
          w++;
        }
        if (y>*hdis) break;
        w = w + (column - 13);
      }

      if (y<*hdis)
      {
        *hdis = y;
        *result = drange;
      }
    }
  }

} // extern "C"
