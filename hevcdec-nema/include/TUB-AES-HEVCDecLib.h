/**
 * \file    TUB-AES-HEVCDecLib.h
 * \brief   HEVC Decoder header file
 * \author  chi.c.chi@tu-berlin.de
 * \date    12/08/2012
 *
 * Copyright:
 * Technische Universität Berlin
 * Architektur Eingebetteter Systeme (AES)
 * Einsteinufer 17
 * 10587 Berlin
 * Deutschland
 */

#ifndef __HEVCDECLIB_H__
#define __HEVCDECLIB_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct HEVCDecLib_Descriptor
{
  unsigned char profile;                  // profile IDC
  unsigned char level;                    // level IDC
  unsigned int uiHeight;                  // luma height
  unsigned int uiWidth;                   // luma width
  unsigned int uiMarginL;                 // luma margin left
  unsigned int uiMarginR;                 // luma margin right
  unsigned int uiMarginT;                 // luma margin top
  unsigned int uiMarginB;                 // luma margin bottom
                                          // chroma sizes derivable using chroma format
  unsigned int uiAlign;                   // picture alignment
  unsigned int uiBitDepthY;               // luma bit depth
  unsigned int uiBitDepthC;               // chromabit depth
  unsigned int uiChromaFormat;            // chroma format (0: 400, 1: 420, 2: 422, 3: 444)
} HEVCDecLib_Descript;

enum {
  I_FRAME = 0,
  P_FRAME,
  B_FRAME,
};

/// chroma formats (according to semantics of chroma_format_idc)
enum ChromaFormat
{
  CHROMA_400  = 0,
  CHROMA_420  = 1,
  CHROMA_422  = 2,
  CHROMA_444  = 3
};

typedef struct HEVCDecLib_Picture
{
  unsigned int uiLHeight;
  //! picture luma width
  unsigned int uiLWidth;
  //! picture chroma height
  unsigned int uiCHeight;
  //! picture chroma width
  unsigned int uiCWidth;
  //! picture luma stride
  unsigned int uiLStride;
  //! picture chroma stride
  unsigned int uiCStride;
  //! picture luma offset
  unsigned int uiLOffset;
  //! picture chroma offset
  unsigned int uiCOffset;

  unsigned int uiBitDepthY;
  unsigned int uiBitDepthC;
  //! picture planes
  void* pLuma;
  bool  bChromaIntl;
  void* pCb;
  void* pCr;
  void* pChroma;

  bool bReferenced; //fixme: can derived from nal
  unsigned int uiNalType;
  unsigned int uiPicType;
  unsigned int uiPOC;
  unsigned int uiTLayer;
  unsigned int uiQp;

  const char* hashType;
  unsigned char refDigest[3][16];
  unsigned char recDigest[3][16];

  //! TimeStamp
  unsigned long long ui64TimeStamp;

  unsigned int uiCodedPicSize;
  double dStartTime;
  double dStopTime;

//  unsigned int uiView;
//  unsigned int uiDid;
//  unsigned int uiQualityLevel;
//  unsigned int uiTemporalLevel;
//  unsigned int bFreezeFrame;
//  unsigned int uiCount;

  void* opaque;

  void* pLuma_nema;
  void* pCb_nema;
  void* pCr_nema;
  void* pChroma_nema;

} HEVCDecLib_Picture;

typedef void* HEVCDecLib_Handle;
typedef void* Callback_Handle;

typedef HEVCDecLib_Picture* (*pf_GetNewPictureBuffer)(Callback_Handle cbHandle);
typedef void (*pf_LinkPictureBuffer)(Callback_Handle cbHandle, HEVCDecLib_Picture* pPic);
typedef void (*pf_UnlinkPictureBuffer)(Callback_Handle cbHandle, HEVCDecLib_Picture* pPic);

/*!
************************************************************************
* \brief Decoder optional flags, can be combined through OR operation
************************************************************************/
enum {
  D_RESERVED                   = 0x0,            /*!< Not used */
  D_PINTHREADS                 = 0x1,            /*!< Pin decoding threads to cores (if available for platform) */
  D_CHROMAINTL                 = 0x2,            /*!< Use SIMD acceleration (if available for platform) */
  D_PROFILE                    = 0x4,            /*!< Profiling (depending on build sampling or instrumentation) */
  D_CALCHASH                   = 0x8             /*!< Calculate hash when SEI available */
};

#if _MSC_VER
#define HEVCDECLIB_API __declspec(dllexport)
#else
#define HEVCDECLIB_API
#endif


HEVCDECLIB_API int HEVCDecLib_Open( HEVCDecLib_Handle& hDecoder,
    Callback_Handle cbHandle,
    pf_GetNewPictureBuffer,
    pf_LinkPictureBuffer,
    pf_UnlinkPictureBuffer,
    unsigned int i_num_threads,
    int*         p_thread_order,
    unsigned int i_num_concurrent_pic,
    unsigned int i_opt_flags );

HEVCDECLIB_API int HEVCDecLib_Close( HEVCDecLib_Handle hDecoder );

HEVCDECLIB_API int HEVCDecLib_DecodeNALU( HEVCDecLib_Handle hDecoder,
    unsigned char*     p_buffer,
    unsigned int       i_buffer,
    unsigned long long ui_pts,
    HEVCDecLib_Picture** pp_hevcpic);

HEVCDECLIB_API int HEVCDecLib_GetDescription( HEVCDecLib_Handle hDecoder,
    HEVCDecLib_Descript& hDescript );

HEVCDECLIB_API int HEVCDecLib_GetDecPicture( HEVCDecLib_Handle hDecoder,
    HEVCDecLib_Picture** pp_hevcpic,
    bool b_flush );

HEVCDECLIB_API int HEVCDecLib_FlushInFlightPictures( HEVCDecLib_Handle hDecoder);

HEVCDECLIB_API int HEVCDecLib_InvalidateInFlightPictures( HEVCDecLib_Handle hDecoder);

HEVCDECLIB_API double HEVCDecLib_GetRealTime(void);

HEVCDECLIB_API const char* HEVCDecLib_GetVersion(void);

#ifdef __cplusplus
}
#endif
#endif

