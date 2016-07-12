#include "macros.h"

extern "C" 
{

  #define USE_PIXOUT

  __attribute__((naked)) void shd()
  {
    unsigned char *input, *output, min;
    int row, column;

    read_reg(row, "v128.x");
    read_reg(column, "v128.y");
  
    ui_vec4 coords;
    read_coords(coords);
    
    read_reg(input, "v0.w"); /// Read value from interpolator 0
    read_reg(output, "v0.z"); /// Read value from interpolator 1
  
    if(coords.x>1 && coords.x<(column-1) &&coords.y>1 && coords.y<(row-1))
    {
      min = *input;
      for (int k = -1; k <= 1; k++)
      {
        for (int l = -1; l <= 1; l++)
        {
          if (*(input+ k*column+ l) < min)
          {
            min = *(input + k*column + l);
          }
        }
      }
      *output = min;
    }
  }

} // extern "C"
