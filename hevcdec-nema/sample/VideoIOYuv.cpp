/*
 * \file    VideoIOYuv.cpp
 * \brief   YUV file I/O class
 * \author  chi.c.chi@tu-berlin.de
 * \date    16/06/2013
 *
 * Copyright:
 * Technische Universit�t Berlin
 * Architektur Eingebetteter Systeme (AES)
 * Einsteinufer 17
 * 10587 Berlin
 * Deutschland
 */

#include <cstdlib>
#include <cassert>
#include <fstream>
#include <iostream>
#include <cstdint>
#include <algorithm>

#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include "VideoIOYuv.h"

using namespace std;

// ====================================================================================================================
// Public member functions
// ====================================================================================================================

/**
 * Open file for reading/writing Y'CbCr frames.
 *
 * Frames read/written have bitdepth fileBitDepth, and are automatically
 * formatted as 8 or 16 bit word values (see TVideoIOYuv::write()).
 *
 * Image data read or written is converted to/from internalBitDepth
 * (See scalePlane(), TVideoIOYuv::read() and TVideoIOYuv::write() for
 * further details).
 *
 * \param pchFile          file name string
 * \param bWriteMode       file open mode: true=read, false=write
 * \param fileBitDepth     bit-depth of input/output file data.
 * \param internalBitDepth bit-depth to scale image data to/from when reading/writing.
 */
void VideoIOYuv::open( char* pchFile, bool bWriteMode, unsigned int fileBitDepth )
{
  m_fileBitdepth = fileBitDepth;

  if ( bWriteMode )
  {
    m_cHandle.open( pchFile, ios::binary | ios::out );

    if( m_cHandle.fail() )
    {
      fprintf(stdout, "\nfailed to write reconstructed YUV file\n");
      exit(0);
    }
  }
  else
  {
    m_cHandle.open( pchFile, ios::binary | ios::in );

    if( m_cHandle.fail() )
    {
      fprintf(stdout, "\nfailed to open Input YUV file\n");
      exit(0);
    }
  }

  openFrameBuffer();

  return;
}

void VideoIOYuv::close()
{
  m_cHandle.close();
}

template <typename T>
inline T Clip3( T minVal, T maxVal, T v) {
  return min<T> (max<T> (minVal, v) , maxVal);
}

template<typename T, typename Tin>
bool VideoIOYuv::invScaleWrite(Tin* pLuma, int width, int height, int stride, int bitdepthshift, int outbitdepth, bool bgrid)
{
  T minval = 0;
  T maxval = (1 << outbitdepth) - 1;

  T* linebuffer = new T[width];

  T* lineptr;
  T offset = 1 << (bitdepthshift-1);
  for (int y = 0; y < height; y++) {
    if (bitdepthshift>0 || bgrid){
      for (int x = 0; x < width; x++) {
        linebuffer[x] = Clip3<T>(minval, maxval, ((pLuma[x+y*stride] + offset) >> bitdepthshift));

        if (bgrid && (x%64 ==0 || y%64 ==0) ){
          linebuffer[x] = maxval;
        }
      }
      lineptr=linebuffer;
    } else {
      lineptr = (T*)&pLuma[y*stride]; //bitdepthshift==0 => input and output type is same
    }
    m_cHandle.write(reinterpret_cast<char*>(lineptr), width*sizeof(T));
    if (m_cHandle.eof() || m_cHandle.fail() ) {
      delete[] linebuffer;
      return false;
    }
  }
  delete[] linebuffer;
  return true;
}

/**
 * Write one Y'CbCr frame
 * @return true for success, false in case of error
 */
bool VideoIOYuv::write( HEVCDecLib_Picture* pPic, bool bDrawGrid)
{
  // compute actual YUV frame size excluding padding size
  int iLStride = pPic->uiLStride;
  int iCStride = pPic->uiCStride;
  unsigned width   = pPic->uiLWidth ;
  unsigned height  = pPic->uiLHeight;
  bool is16bit = m_fileBitdepth > 8;
  assert (pPic->uiBitDepthY >=8);
  assert (pPic->uiBitDepthC >=8);
  bool retval = true;

  int ibitdepthShiftY = pPic->uiBitDepthY - m_fileBitdepth;
  int ibitdepthShiftC = pPic->uiBitDepthC - m_fileBitdepth;

  void* pLuma = pPic->pLuma;
  void* pChromaCb = pPic->pCb;
  void* pChromaCr = pPic->pCr;
  void* pChroma = pPic->pChroma;

  if (is16bit){
    if (pPic->uiBitDepthY>8){
      if (!invScaleWrite<short, short>((short*) pLuma, width, height, iLStride, ibitdepthShiftY, m_fileBitdepth, bDrawGrid)){
        return false;
      }
    } else {
      if (!invScaleWrite<short, uint8_t>((uint8_t*) pLuma, width, height, iLStride, ibitdepthShiftY, m_fileBitdepth, bDrawGrid)){
        return false;
      }
    }
  } else {
    if (pPic->uiBitDepthY>8){
      if (!invScaleWrite<uint8_t, short>((short*) pLuma, width, height, iLStride, ibitdepthShiftY, m_fileBitdepth, bDrawGrid)){
        return false;
      }
    } else {
      if (!invScaleWrite<uint8_t, uint8_t>((uint8_t*) pLuma, width, height, iLStride, ibitdepthShiftY, m_fileBitdepth, bDrawGrid)){
        return false;
      }
    }
  }

  width  = pPic->uiCWidth;
  height = pPic->uiCHeight;
  if (is16bit){
    if (pPic->uiBitDepthC>8){
      if (pPic->bChromaIntl){
        if (!invScaleWrite<short, short>((short*) pChroma, width, height, iCStride, ibitdepthShiftC, m_fileBitdepth)){
          return false;
        }
      } else {
        if (!invScaleWrite<short, short>((short*) pChromaCb, width, height, iCStride, ibitdepthShiftC, m_fileBitdepth)){
          return false;
        }
        if (!invScaleWrite<short, short>((short*) pChromaCr, width, height, iCStride, ibitdepthShiftC, m_fileBitdepth)){
          return false;
        }
      }
    } else {
      if (pPic->bChromaIntl){
        if (!invScaleWrite<short, uint8_t>((uint8_t*) pChroma, width, height, iCStride, ibitdepthShiftC, m_fileBitdepth)){
          return false;
        }
      } else {
        if (!invScaleWrite<short, uint8_t>((uint8_t*) pChromaCb, width, height, iCStride, ibitdepthShiftC, m_fileBitdepth)){
          return false;
        }
        if (!invScaleWrite<short, uint8_t>((uint8_t*) pChromaCr, width, height, iCStride, ibitdepthShiftC, m_fileBitdepth)){
          return false;
        }
      }
    }
  } else {
    if (pPic->uiBitDepthC>8){
      if (pPic->bChromaIntl){
        if (!invScaleWrite<uint8_t, short>((short*) pChroma, width, height, iCStride, ibitdepthShiftC, m_fileBitdepth)){
          return false;
        }
      } else {
        if (!invScaleWrite<uint8_t, short>((short*) pChromaCb, width, height, iCStride, ibitdepthShiftC, m_fileBitdepth)){
          return false;
        }
        if (!invScaleWrite<uint8_t, short>((short*) pChromaCr, width, height, iCStride, ibitdepthShiftC, m_fileBitdepth)){
          return false;
        }
      }
    } else {
      if (pPic->bChromaIntl){
        if (!invScaleWrite<uint8_t, uint8_t>((uint8_t*) pChroma, width, height, iCStride, ibitdepthShiftC, m_fileBitdepth)){
          return false;
        }
      } else {
        if (!invScaleWrite<uint8_t, uint8_t>((uint8_t*) pChromaCb, width, height, iCStride, ibitdepthShiftC, m_fileBitdepth)){
          return false;
        }
        if (!invScaleWrite<uint8_t, uint8_t>((uint8_t*) pChromaCr, width, height, iCStride, ibitdepthShiftC, m_fileBitdepth)){
          return false;
        }
      }
    }
  }

  return retval;
}

static inline uint32_t
convertYUVtoARGB(int y, int CB, int Cr) {
  int r, g, b;
  CB -= 128;
  Cr -= 128;

  r = y + (int)(1.402f * Cr);
  g = y - (int)(0.344f * Cr + 0.714f * CB);
  b = y + (int)(1.772f * CB);
  r = r > 255? 255 : r < 0 ? 0 : r;
  g = g > 255? 255 : g < 0 ? 0 : g;
  b = b > 255? 255 : b < 0 ? 0 : b;

  return 0xff000000 | (r<<16) | (g<<8) | b;
}

bool VideoIOYuv::draw( HEVCDecLib_Picture* pPic, bool bDrawGrid)
{
  // compute actual YUV frame size excluding padding size
  int iLStride = pPic->uiLStride;
  int iCStride = pPic->uiCStride;
  unsigned Lwidth   = pPic->uiLWidth;
  unsigned Lheight  = pPic->uiLHeight;

  assert (pPic->uiBitDepthY >= 8);
  assert (pPic->uiBitDepthC >= 8);

  uint8_t *pLuma = (uint8_t *)pPic->pLuma;
  uint8_t *pChromaCb = (uint8_t *)pPic->pCb;
  uint8_t *pChromaCr = (uint8_t *)pPic->pCr;
  void *pChroma = pPic->pChroma;
  assert(!pChroma);

  uint32_t *out = (uint32_t *)fbp;
  uint8_t r, g, b, Cr, Cb, Y;
  int x, y;

  int xRes = Lwidth > vinfo.xres ? vinfo.xres : Lwidth;
  int yRes = Lheight > vinfo.yres ? vinfo.yres : Lheight;
//  int xRes = Lwidth;
//  int yRes = Lheight;

//  printf("\n%d xx %d\n", xRes, yRes);

  for(y = 0; y < yRes; y++) {
    for(x = 0; x < xRes; x++) {
      Y  = *(pLuma + x);
      Cb = *(pChromaCb + x/2);
      Cr = *(pChromaCr + x/2);

      out[y * vinfo.xres + x] = convertYUVtoARGB(Y, Cb, Cr);
    }

    pLuma += iLStride;
    if(!(y%2) && y) {
      pChromaCb += iCStride;
      pChromaCr += iCStride;
    }
  }

  return true;
}

void
VideoIOYuv::closeFrameBuffer()
{
  int fbfd;

  fbfd = ::open("/dev/fb0", O_RDWR);
  if (fbfd == -1) {
    cerr << "Error: cannot open framebuffer device" << endl;
    exit(1);
  }

  if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
    cerr << "Error reading variable information" << endl;
    exit(3);
  }

  munmap(fbp, screensize);

  ::close(fbfd);
}

void
VideoIOYuv::openFrameBuffer(void)
{
  int fbfd;
  struct fb_fix_screeninfo finfo;

  fbfd = ::open("/dev/fb0", O_RDWR);
  if (fbfd == -1) {
    cerr << "Error: cannot open framebuffer device" << endl;
    exit(1);
  }
  cout << "The framebuffer device was opened successfully." << endl;

  /// Get fixed screen information
  if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) == -1) {
    cerr << "Error reading fixed information" << endl;
    exit(2);
  }

  /// Get variable screen information
  if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
    cerr << "Error reading variable information" << endl;
    exit(3);
  }

  cout << vinfo.xres << " x " << vinfo.yres << " (yres_virtual = " << vinfo.yres_virtual << ", xres_virtual = " << vinfo.xres_virtual << "), %bpp " << vinfo.bits_per_pixel << endl;

  /// Figure out the size of the screen in bytes
  screensize = vinfo.xres * vinfo.yres_virtual * vinfo.bits_per_pixel / 8;

  /// Map the device to memory
  fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
  if ((int)fbp == -1) {
    cerr << "Error: failed to map framebuffer device to memory" << endl;
    exit(4);
  }

  ::close(fbfd);
}
