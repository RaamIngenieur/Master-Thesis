#include "macros.h"

extern "C" 
{

  #define USE_PIXOUT

  __attribute__((naked)) void negate()
  {
    unsigned int* pic;
    
    read_reg(pic, "v0.w"); /// Read value from interpolator 0
  
    *pic=255-*pic;

  }

} // extern "C"
