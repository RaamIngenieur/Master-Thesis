#ifndef __NEMA_H__
#define __NEMA_H__

#include "TUB-AES-HEVCDecLib.h"
#include <linux/fb.h>

class Nema {
public:
  Nema(void);
  ~Nema() {}

  bool init(fb_var_screeninfo vinfo);
  void shutDown(void);
  void *nema_malloc(size_t size);
  void nema_free(void *ptr);

  void yuv2rgb(HEVCDecLib_Picture *pic);

private:
  bool m_isInited;
  uint32_t m_fbp;   /// Pointer to frame buffer
  int m_xres, m_yres;
  double total_time;
};

#endif
