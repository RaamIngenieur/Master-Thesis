#include "macros.h"

extern "C" {

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

  
  /*
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
      
      /*if (drange == dmax)
      {
        dif1 = y;
        dif2 = 28561;
        dif3 = 28561;
        hdis = y;
      }
      else
      {
        dif3 = dif2;
        dif2 = dif1;
        dif1 = y;
      }
      if ((dif2 <= hdis) && (dif2 <= dif3) && (dif2 <= dif1))
      {
        num = ((float)(dif3 - dif1)) / 2;
        den = (float)(dif3 + dif1 - 2 * dif2);
        hdis = dif2;
        if (num == 0)
        {
          pos = (float)drange + 1;
        }
        else if (den == 0)
        {
          pos = (float)drange + (float)sgn(num) + 1;
        }
        else if (den/sgn(den) >= num/sgn(num))
        {
          pos = (float)drange + ((float)(sgn(num)*sgn(den)))*num / den + 1;
        }
        else
        {
          pos = (float)drange + (float)sgn(num)*sgn(den) + 1;
        }
      }
      
    }
  }
  *(result+(coords.y+6)*column+coords.x+6) = pos;
  */
}

} // extern "C"
