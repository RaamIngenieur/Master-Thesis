/*
 * \file    VideoIOYuv.h
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

#ifndef VIDEOIOYUV_H_
#define VIDEOIOYUV_H_

#include <stdio.h>
#include <fstream>
#include <iostream>

#include <linux/fb.h>

#include "TUB-AES-HEVCDecLib.h"

using namespace std;

// ====================================================================================================================
// Class definition
// ====================================================================================================================

/// YUV file I/O class
class VideoIOYuv
{
private:
  fstream   m_cHandle;          ///< file handle
  unsigned int m_fileBitdepth;  ///< bitdepth of input/output video file

  template<typename T, typename Tin>
  bool invScaleWrite(Tin* pLuma, int width, int height, int stride, int bitdepthshift, int outbitdepth, bool bgrid=false);

  size_t        screensize;
  void *        fbp;
  struct        fb_var_screeninfo vinfo;

public:
  VideoIOYuv()   {m_fileBitdepth = 8; fbp = NULL;}
  ~VideoIOYuv()  {}

  void  open  ( char* pchFile, bool bWriteMode, unsigned int fileBitDepth); ///< open or create file
  void  close ();                                           ///< close file

  inline fb_var_screeninfo getVinfo(void) { return vinfo; }

  bool  write(  HEVCDecLib_Picture* pPic, bool bDrawGrid);
  bool  draw (  HEVCDecLib_Picture* pPic, bool bDrawGrid);

  void openFrameBuffer(void);
  void closeFrameBuffer(void);
};

#endif // VIDEOIOYUV_H_

