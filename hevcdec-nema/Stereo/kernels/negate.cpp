#include "macros.h"

extern "C" 
{

  #define USE_PIXOUT

  __attribute__((naked)) void shd()
  {
    unsigned int* pic;
    int row, column, y;

    read_reg(row, "v128.x");
    read_reg(column, "v128.y");
  
    ui_vec4 coords;
    read_coords(coords);
    
    read_reg(pic, "v0.w"); /// Read value from interpolator 0
  
    if(coords.x>5 && coords.x<(column-6) &&coords.y>5 && coords.y<(row-6))
    {
      *pic=255-*pic;
    }
  }

} // extern "C"
