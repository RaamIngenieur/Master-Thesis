/*
 * \file    HEVCDecoderApp.h
 * \brief
 * \author  chi.c.chi@tu-berlin.de
 * \date    16/06/2013
 *
 * Copyright:
 * Technische Universität Berlin
 * Architektur Eingebetteter Systeme (AES)
 * Einsteinufer 17
 * 10587 Berlin
 * Deutschland
 */

#ifndef __HEVCDECODER_APP__
#define __HEVCDECODER_APP__

#include <time.h>
#include <list>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <cstdint>

#include "TUB-AES-HEVCDecLib.h"
#include "VideoIOYuv.h"
#include "nema.h"

// ====================================================================================================================
// Class definition
// ====================================================================================================================

/// decoder application class
class HEVCDecoderApp
{
  typedef struct PictureContainer{
    HEVCDecLib_Picture* pHEVCPic;
    unsigned char* planes;
    int refcount;
    bool needoutput;
  } PictureContainer ;

  // cmd line variables
  char*         m_pchBitstreamFile;                   ///< input bitstream file name
  char*         m_pchReconFile;                       ///< output reconstruction file name
  int           m_iSkipFrame;                         ///< counter for frames prior to the random access point to skip
  uint          m_outputBitDepth;                     ///< bit depth used for writing output

  int           m_iMaxTemporalLayer;                  ///< maximum temporal layer to be decoded

  int           m_decodedPictureHashSEIEnabled;       ///< Checksum(3)/CRC(2)/MD5(1)/disable(0) acting on SEI picture_digest message
  int           m_iNumThreads;                        ///< number of threads
  int           m_iNumPicInFlight;                    ///< number of pictures in flight
  bool          m_bPinning;                           /// thread pinning
  std::vector<int> m_vThreadOrder;                    /// thread pinning order
  int           m_iSIMDExtension;                     /// sse2=1, sse3=2, ssse3=3, sse4.1=4, sse4.2=5, avx=6, avx2=7)
  bool          m_bChromaIntl;
  bool          m_bGrid;
  double        m_dFps;
  bool          m_bProfile;
  int           m_verbose;
  int           m_iOutputBufferThres;
  int           m_iOutputBufferBurst;
  int           m_iOutputBufferMax;
  bool          m_bUseInternalPics;                   /// Use internal pictures with copy at output
  bool          m_bUseNema;
  bool          m_bDraw;

  Nema nema;

public:
  // class interface
  HEVCDecLib_Handle               m_hHEVCDecoder;                     ///< decoder class
  VideoIOYuv                      m_cTVideoIOYuvReconFile;        ///< reconstruction YUV class

  // for output control
  int                             m_iPOCLastDisplay;              ///< last POC in display order
  bool                            m_bMD5MisMatch;
  uint64_t                        m_uiPts;
  //lock not needed unless library uses callback functions in different threads
//  std::mutex                      m_cMutexDecPicPool;
  std::list<PictureContainer*>    m_lDecPicPool;
  std::mutex                      m_ReadyQlock;
  std::condition_variable         m_ReadyQCond;
  std::thread*                    m_outputThread;
  std::queue<PictureContainer*>   m_qReadyPics;

  bool                            m_bDescriptInitialized;
  HEVCDecLib_Descript             m_hDescript;

  bool m_bLimitFps;
  double m_frametime;
  double m_next;
  double m_startoutputtime;
  double m_stopoutputtime;
  int m_outframes;
  int64_t m_filesize;
  int64_t m_slicebytes;

  std::vector<double>              m_vFrameTimes;

public:
  HEVCDecoderApp();
  ~HEVCDecoderApp() {}

  bool  parseCfg          ( int argc, char* argv[] );   ///< parse argv
  void  create            (); ///< create internal members
  void  destroy           (); ///< destroy internal members
  void  decode            (); ///< main decoding function
  bool  getMisMatch       () { return m_bMD5MisMatch; }

private:
  int   allocPictureBuffer( PictureContainer* pPicCon);
  void  xCreateDecLib     (); ///< create internal classes
  void  xDestroyDecLib    (); ///< destroy internal classes
  void  xInitDecLib       (); ///< initialize decoder class

  void  xCheckMD5         ( HEVCDecLib_Picture*  pHEVCPic );
  void  xWriteOutput      ( PictureContainer* pPicCon, bool bFlush); ///< write YUV to file
  void  outputThread      ( );

  HEVCDecLib_Picture* getNewPictureBuffer();
  void  returnPictureBuffer (PictureContainer* pPicCon);
  void  linkPictureBuffer   (PictureContainer* pPicCon);
  void  unLinkPictureBuffer (PictureContainer* pPicCon);
  static HEVCDecLib_Picture* get_new_picture_buffer(Callback_Handle cbHandle);
  static void link_picture_buffer(Callback_Handle cbHandle, HEVCDecLib_Picture* pPic);
  static void unlink_picture_buffer(Callback_Handle cbHandle, HEVCDecLib_Picture* pPic);

};

#endif

