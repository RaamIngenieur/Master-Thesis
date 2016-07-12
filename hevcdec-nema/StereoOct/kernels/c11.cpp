#include "macros.h"

extern "C" {

#define USE_PIXOUT

__attribute__((naked)) void shd()
{
  int row, column, x;
  unsigned char *input, *input1;
  unsigned int  *output;

  read_reg(row, "v128.x");
  read_reg(column, "v128.y");
  
  ui_vec4 coords;
  read_coords(coords);
    
  read_reg(input, "v0.w"); /// Read value from interpolator 0
  read_reg(output, "v0.z"); /// Read value from interpolator 1

  x = 0;
  *output = 0;

  if(coords.x>4 && coords.x<(column-5) &&coords.y>4 && coords.y<(row-5))
  {
    input1= input - 5 * (1+column);
    for (int k = -5; k <= 5; k++)
    {
      for (int l = -5; l <= 5; l++)
      {
        if (~(k == 0 && l == 0))
        {
          *output = *output << 1;

          if (*input1 < *input)
          {
            *output = *output + 1;
          }
          x++;
          if (x%32==0)
          {
            output = output + 1;
            *output = 0;
          }

        }
        input1++;
      }
      input1 = input1 + column - 11;
    }
  }


}

} // extern "C"
