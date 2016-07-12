#include "macros.h"

extern "C" 
{

  #define USE_PIXOUT

  __attribute__((naked)) void shd()
  {
    unsigned int* left,*right,*result, pos;
    int row, column, y;
    unsigned int  *lp,*rp,x,hdis = 28561;

    read_reg(row, "v128.x");
    read_reg(column, "v128.y");
  
    ui_vec4 coords;
    read_coords(coords);
    
    read_reg(left, "v0.w"); /// Read value from interpolator 0
    read_reg(right, "v0.z"); /// Read value from interpolator 1
    read_reg(result, "v0.y"); /// Read value from interpolator 2
  
    for (int drange = 100; drange >= 0; drange--)
    {
      if ((unsigned int)coords.x + 12 + drange < (unsigned int) column)
      {
        y = 0;
        lp = left + (coords.y*column + coords.x + drange) * 6;
        rp = right + (coords.y*column + coords.x) * 6;
        for (int k = 12; k >= 0; k--)
        {
          for (int l = 77; l >= 0; l--)
          {
            x = *lp^*rp;
            y = y + __builtin_popcount(x);
            if (y>hdis) break;
            lp = lp + 1;
            rp = rp + 1;
          }
          if (y>hdis) break;
          lp = lp + (column - 13) * 6;
          rp = rp + (column - 13) * 6;
        }

        if (y<hdis)
        {
          hdis = y;
          pos = drange;
        }
      }
    }
    *(result+(coords.y+6)*column+coords.x+6) = pos;
  }

} // extern "C"
