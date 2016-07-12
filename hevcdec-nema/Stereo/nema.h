#ifndef __NEMA_H__
#define __NEMA_H__

#include <linux/fb.h>

class Nema {
public:
  Nema(void);
  ~Nema() {}

  bool init(int row, int column);
  void shutDown(void);
  void *nema_malloc(size_t size);
  void nema_free(void *ptr);
  void wait_for_interrupt(void);
  void wait_for_status(void);
  void negate(unsigned int  *pic, int row, int column);
  void erode(unsigned char* input,unsigned char *output, int row, int column);
  void dilate(unsigned char* input,unsigned char *output, int row, int column);
  void c11(unsigned char* input,unsigned int *output, int row, int column);
  void exoradd(unsigned int* exoradd, unsigned int  *lct, unsigned int  *rct, int row, int column, int drange,bool load);
  void shd(unsigned int* exoradd, unsigned int* hdis, unsigned int *result, int row, int column,int drange,bool load);


private:
  bool m_isInited;
  uint32_t m_fbp;   /// Pointer to frame buffer
  int m_xres, m_yres;
  double total_time;
};

#endif
