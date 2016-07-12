#include "macros.h"

extern "C" {

#define convertYUVtoARGB(y, b, g,r) ((ui_vec4){y+b, y+g, y+r})

//static inline ui_vec4
//convertYUVtoARGB(int y, int b1, int g1, int r1) {
//  ui_vec4 color;
//
//  color.x = y + b1;
//  color.y = y + g1;
//  color.z = y + r1;
//
//  return color;
//}

#define USE_PIXOUT

__attribute__((naked)) void yuv2rgba()
{
  int Y;
  ui_vec4 color;
  unsigned int uiLStride;
  unsigned char *pChromaCb;
  unsigned char *pChromaCr;
  unsigned char *pLuma_interp;

  ui_vec4 coords;
  read_coords(coords);

#ifndef USE_PIXOUT
  unsigned int *fbp;
  read_reg(fbp, "v0.z");
#endif

  /// Read value from interpolator 2
  read_reg(pChromaCb, "v0.y");
  /// Read value from interpolator 3
  read_reg(pChromaCr, "v0.x");

  float Cb = (float)*(pChromaCb + coords.x) - 128.0f;
  float Cr = (float)*(pChromaCr + coords.x) - 128.0f;
  int b1 = 1.772f * Cb;
  int g1 = -(0.344f * Cr + 0.714f * Cb);
  int r1 = 1.402f  * Cr;

  coords.x *= 2;
  coords.y *= 2;

  /// Read value from interpolator 0
  read_reg(pLuma_interp, "v0.w");

  /// Read from const register
  read_reg(uiLStride, "v128.x");

  Y = *(pLuma_interp);
  color = convertYUVtoARGB(Y, b1, g1, r1);

#ifndef  USE_PIXOUT
  fbp[0] = 0xff0000ff;
#else
  pixout(coords, color, PIXOUT_FLAG);
#endif

  Y = *(pLuma_interp + 1);
  color = convertYUVtoARGB(Y, b1, g1, r1);
#ifndef  USE_PIXOUT
  fbp[1] = 0x00ff00ff;
#else
  coords.x += 1;
  pixout(coords, color, PIXOUT_FLAG);
#endif

  Y = *(pLuma_interp + uiLStride + 1);
  color = convertYUVtoARGB(Y, b1, g1, r1);
#ifndef  USE_PIXOUT
  fbp[800+1] = 0x0000ffff;
#else
  ++coords.y;
  pixout(coords, color, PIXOUT_FLAG);
#endif

  Y = *(pLuma_interp + uiLStride);
  color = convertYUVtoARGB(Y, b1, g1, r1);
#ifndef  USE_PIXOUT
  fbp[800] = 0xffffffff;
  yield;
#else
  --coords.x;
  pixout_y(((ui_vec4){coords.x, coords.y}), color, PIXOUT_FLAG);
#endif

}
} // extern "C"
