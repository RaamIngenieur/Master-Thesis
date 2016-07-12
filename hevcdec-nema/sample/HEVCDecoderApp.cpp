/*
 * \file    HEVCDecoderApp.cpp
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

#include <list>
#include <vector>
#include <fcntl.h>
#include <cassert>
#include <time.h>
#include <chrono>
#include <thread>
#include <cstring>
#include <string>
#include <sys/stat.h>
#include <algorithm>
#ifdef __APPLE__
#include <malloc/malloc.h>
#elif __tilegx__
#include <tmc/alloc.h>
#include <malloc.h>
#else
#include <malloc.h>
#endif

#include "HEVCDecoderApp.h"
#include "AnnexBread.h"
#include "nema.h"
#include "program_options_lite.h"

using namespace std;
namespace po = df::program_options_lite;


#ifdef WIN32
#define strdup _strdup
#endif

#if defined(__i386__) || defined(i386) || defined(__x86_64__) || defined(_M_IX86) || defined(_M_X64)
#define X86 1
#elif defined (__tilegx__)
#define TILEGX 1
#elif defined (__ARM_NEON__)
#define ARM 1
#endif

#if _WIN32
# define xMallocAlign( type, len, align )  _aligned_malloc(sizeof(type)*(len), align)
# define xFreeAlign( ptr )                 _aligned_free(ptr)
#else
# define xMallocAlign(type, len, align)    memalign(align, sizeof(type)*(len))
# define xFreeAlign( ptr )                 free(ptr)
#endif

#define xMalloc( type, len )        malloc   ( sizeof(type)*(len) )
#define xFree( ptr )                free     ( ptr )

// ====================================================================================================================
// Constructor / destructor / initialization / destroy
// ====================================================================================================================

HEVCDecoderApp::HEVCDecoderApp()
{
  m_pchBitstreamFile = NULL;
  m_pchReconFile = NULL;
  m_iSkipFrame = 0;
  m_outputBitDepth = 8;
  m_iMaxTemporalLayer = 0;
  m_decodedPictureHashSEIEnabled = true;
  m_iNumThreads = 1;
  m_iNumPicInFlight =1 ;
  m_bPinning = false;
  m_iSIMDExtension = -1;
  m_bChromaIntl = false;
  m_bGrid = false;
  m_dFps = 0.0;
  m_bProfile = false;
  m_verbose = 0;
  m_iOutputBufferThres = 0;
  m_iOutputBufferBurst = 0;
  m_iOutputBufferMax = 0;
  m_bUseInternalPics = false;
  m_bUseNema = false;

  m_iPOCLastDisplay  = -1;
  m_bMD5MisMatch = false;
  m_bDescriptInitialized = false;
  m_startoutputtime = 0.0;
  m_stopoutputtime= 0.0;
  m_outframes = 0;
  m_slicebytes = 0;
  m_outputThread = NULL;
  m_bLimitFps = false;
  m_next = 0.0;
  m_frametime = 0;
  m_filesize = 0;
  m_uiPts = 0;
  m_hHEVCDecoder = NULL;
}

/** \param argc number of arguments
    \param argv array of arguments
 */
bool HEVCDecoderApp::parseCfg( int argc, char* argv[] )
{
  bool do_help = false;
  string cfg_BitstreamFile;
  string cfg_ReconFile;
  string sThreadOrder;
#if X86 || ARM || TILEGX
  std::string cfg_sSIMDExtension;
#endif

  po::Options opts;
  opts.addOptions()
  ("help", do_help, false, "this help text")
  ("BitstreamFile,b", cfg_BitstreamFile, string(""), "bitstream input file name")
  ("ReconFile,o",     cfg_ReconFile,     string(""), "reconstructed YUV output file name\n"
                                                     "YUV writing is skipped if omitted")
  ("DrawGrid", m_bGrid, false, "Draw CTB grid (64x64) in output YUV\n")
  ("OutputBitDepth,d", m_outputBitDepth, 8u, "bit depth of YUV output file (default 8 bit)")
//  ("MaxTemporalLayer,t", m_iMaxTemporalLayer, -1, "Maximum Temporal Layer to be decoded. -1 to decode all layers")
  ("Verbose,v", m_verbose, 0, "Output information per frame")
  ("CheckHash,c", m_decodedPictureHashSEIEnabled, 1, "Control handling of picture_digest SEI messages\n"
                                              "\t3: checksum\n"
                                              "\t2: CRC\n"
                                              "\t1: MD5\n"
                                              "\t0: ignore")
  ("NumThreads,t", m_iNumThreads, 1, "number of threads")
  ("NumPicInFlight,f", m_iNumPicInFlight, 1, "number of pictures in flight")
//  ("ThreadNumOffset,e", m_iThreadNumOffset, 0, "thread num offset for pinning")
  ("ChromaIntl", m_bChromaIntl, false, "use one interleaved chroma plane (NV12/P010)")
  ("Pinning,p", m_bPinning, false, "thread pinning")
  ("ThreadOrder", sThreadOrder, string(""), "thread pinning order in space separated string")
#if X86
  ("SIMDExtension,x", cfg_sSIMDExtension, string("auto"), "SIMD extensions (scalar, sse2, sse3, ssse3, sse4.1, sse4.2, avx, xop, avx2, auto(default))")
#elif ARM
  ("SIMDExtension,x", cfg_sSIMDExtension, string("scalar"), "SIMD extensions (scalar(default), neon)")
#elif TILEGX
  ("SIMDExtension,x", cfg_sSIMDExtension, string("scalar"), "SIMD extensions (scalar(default), tilegx)")
#endif
  ("Profile", m_bProfile, false, "Enable profiling, sampling or instrumentation depending on build")
  ("Framerate", m_dFps, 0.0, "Frame rate (default unconstrained)")
  ("OutputBuffer", m_iOutputBufferThres, 1, "Number of output buffer slots before outputting pictures")
  ("OutputBufferBurst", m_iOutputBufferBurst, 0, "Additional output buffers for burst decode simulation")
  ("InternalPics", m_bUseInternalPics, false, "Use internal pictures with copy at output")
  ("UseNema", m_bUseNema, false, "Use Nema")
  ("DrawFrames", m_bDraw, false, "Draw frames to the frame buffer")
  ;

  po::setDefaults(opts);
  const list<const char*>& argv_unhandled = po::scanArgv(opts, argc, (const char**) argv);

  for (list<const char*>::const_iterator it = argv_unhandled.begin(); it != argv_unhandled.end(); it++)
  {
    fprintf(stderr, "Unhandled argument ignored: `%s'\n", *it);
  }

  if (argc == 1 || do_help)
  {
    po::doHelp(cout, opts);
    return false;
  }

  /* convert std::string to c string for compatability */
  m_pchBitstreamFile = cfg_BitstreamFile.empty() ? NULL : strdup(cfg_BitstreamFile.c_str());
  m_pchReconFile = cfg_ReconFile.empty() ? NULL : strdup(cfg_ReconFile.c_str());

  if (!m_pchBitstreamFile)
  {
    fprintf(stderr, "No input file specifed, aborting\n");
    return false;
  }

  if (m_bPinning && !sThreadOrder.empty() )
  {
    char* pch = strdup(sThreadOrder.c_str());
    pch = strtok (pch, " ");
    while (pch != NULL)
    {
      m_vThreadOrder.push_back(atoi(pch));
      pch = strtok (NULL, " ");
    }

    if (m_iNumThreads > m_vThreadOrder.size())
    {
      std::cerr << "Insufficient thread numbers specified to override thread pinning order" << std::endl;
      return false;
    }
  }

  m_iOutputBufferMax = m_iOutputBufferThres+ m_iOutputBufferBurst;

#if X86
  enum{
    SCALAR=0,
    SSE2,
    SSE3,
    SSSE3_SLM,
    SSSE3,
    SSE41,
    SSE42,
    AVX,
    XOP,
    AVX2,
    AUTO,
  };

  m_iSIMDExtension = AUTO;
  if (cfg_sSIMDExtension == "scalar"){
    m_iSIMDExtension = SCALAR;
  } else if (cfg_sSIMDExtension == "sse2"){
    m_iSIMDExtension = SSE2;
  }else if (cfg_sSIMDExtension == "sse3"){
    m_iSIMDExtension = SSE3;
  }else if (cfg_sSIMDExtension == "ssse3"){
    m_iSIMDExtension = SSSE3;
  }else if (cfg_sSIMDExtension == "sse4.1"){
    m_iSIMDExtension = SSE41;
  }else if (cfg_sSIMDExtension == "sse4.2"){
    m_iSIMDExtension = SSE42;
  }else if (cfg_sSIMDExtension == "avx"){
    m_iSIMDExtension = AVX;
  }else if (cfg_sSIMDExtension == "xop"){
    m_iSIMDExtension = XOP;
  }else if (cfg_sSIMDExtension == "avx2"){
    m_iSIMDExtension = AVX2;
  }else if (cfg_sSIMDExtension == "auto"){
    m_iSIMDExtension = AUTO;
  }
#elif ARM
  enum{
    SCALAR=0,
    NEON,
  };

  m_iSIMDExtension = SCALAR;
  if (cfg_sSIMDExtension == "scalar"){
    m_iSIMDExtension = SCALAR;
  }else if (cfg_sSIMDExtension == "neon"){
    m_iSIMDExtension = NEON;
  }
#elif TILEGX
  enum{
    SCALAR=0,
    TILEGX,
  };

  m_iSIMDExtension = SCALAR;
  if (cfg_sSIMDExtension == "scalar"){
    m_iSIMDExtension = SCALAR;
  }else if (cfg_sSIMDExtension == "tilegx"){
    m_iSIMDExtension = TILEGX;
  }
#endif
#if X86 ||ARM || TILEGX
  else {
    cerr << "unknown SIMD extension " <<cfg_sSIMDExtension<< endl; //let cpu detection decide
  }
#endif
  return true;
}

void HEVCDecoderApp::create()
{
  if (m_dFps > 0){
    m_bLimitFps = true;
    m_frametime = 1/m_dFps;
  } else {
    m_bLimitFps = false;
    m_frametime = 0;
  }

  if ( m_pchReconFile ) {
    m_cTVideoIOYuvReconFile.open( m_pchReconFile, true, m_outputBitDepth); // write mode
  }

  m_cTVideoIOYuvReconFile.openFrameBuffer();

  if(m_bUseNema) {
    nema.init(m_cTVideoIOYuvReconFile.getVinfo());
  }

  struct stat filestatus;
  stat( m_pchBitstreamFile, &filestatus );
  m_filesize = filestatus.st_size;

  unsigned int i_opt_flags =0;
  if ( m_bPinning ) i_opt_flags |= D_PINTHREADS;
  if ( m_bChromaIntl ) i_opt_flags |= D_CHROMAINTL;
  if ( m_bProfile  ) i_opt_flags |= D_PROFILE;
  if ( m_decodedPictureHashSEIEnabled ) i_opt_flags |= D_CALCHASH;
  if ( m_iSIMDExtension) i_opt_flags |= (m_iSIMDExtension<<16) ;
  int* thread_order = m_vThreadOrder.empty() ? NULL: &m_vThreadOrder[0];

  if ( m_bUseInternalPics ){
    if ( HEVCDecLib_Open(m_hHEVCDecoder,
        NULL, NULL, NULL, NULL,
        m_iNumThreads, thread_order, m_iNumPicInFlight, i_opt_flags) ){
      assert(0);
    }
  } else {
    if ( HEVCDecLib_Open(m_hHEVCDecoder,(Callback_Handle) this, get_new_picture_buffer, link_picture_buffer, unlink_picture_buffer,
        m_iNumThreads, thread_order, m_iNumPicInFlight, i_opt_flags) ){
      assert(0);
    }
  }

  if (m_dFps > 0.0) {
    m_outputThread = new std::thread(&HEVCDecoderApp::outputThread, this);
  } else {
    m_startoutputtime = HEVCDecLib_GetRealTime();
  }
}

void HEVCDecoderApp::destroy()
{
  if (m_pchBitstreamFile){
    free(m_pchBitstreamFile);
  }
  if (m_dFps > 0.0) {
    m_outputThread->join();
  } else {
    m_stopoutputtime = HEVCDecLib_GetRealTime();
  }
  if ( m_pchReconFile ){
    m_cTVideoIOYuvReconFile. close();
  }

  m_cTVideoIOYuvReconFile.closeFrameBuffer();
  if(m_bUseNema) {
    nema.shutDown();
  }


  if ( HEVCDecLib_Close(m_hHEVCDecoder) ){
    assert(0);
  }

  std::list<PictureContainer*>::iterator ppic = m_lDecPicPool.begin();
  for (; ppic != m_lDecPicPool.end(); ppic++){
    assert((*ppic)->planes !=NULL);
//    if(m_bUseNema) {
//      nema.nema_free((*ppic)->planes);
//    } else {
//      xFreeAlign((*ppic)->planes);
//    }
    delete (*ppic)->pHEVCPic;
    delete *ppic;
  }
  m_lDecPicPool.empty();

  printf("\n");
  printf("Fps   %.3f\n", m_outframes/ (m_stopoutputtime-m_startoutputtime));
  if (m_dFps != 0.0){
    printf("Mbps  %.3f\n", 8*m_filesize/(1000000*m_outframes/m_dFps));
  }
  printf("Kbpf  %.3f\n\n", (double)8*(m_slicebytes/1000)/m_outframes);
  if (m_verbose>=1){
    double total_time=0.0;
    for(std::vector<double>::iterator it = m_vFrameTimes.begin(); it != m_vFrameTimes.end(); ++it) {
      total_time+=*it;
    }
    double avg_frame_time = total_time/ m_vFrameTimes.size();
    double variance =0.0;
    for(std::vector<double>::iterator it = m_vFrameTimes.begin(); it != m_vFrameTimes.end(); ++it) {
      double diff = avg_frame_time-(*it);
      variance += diff*diff;
    }
    double std = sqrt(variance/m_vFrameTimes.size());
    printf("MEAN %.2f ms STD %.2f ms\n", avg_frame_time*1000, std*1000);
  }
}

// ====================================================================================================================
// Public member functions
// ====================================================================================================================
/**
 - create internal class
 - initialize internal class
 - until the end of the bitstream, call decoding function in TDecTop class
 - delete allocated buffers
 - destroy internal class
 .
 */
void HEVCDecoderApp::decode()
{
  ifstream bitstreamFile(m_pchBitstreamFile, ifstream::in | ifstream::binary);
  if (!bitstreamFile)
  {
    fprintf(stderr, "\nfailed to open bitstream file `%s' for reading\n", m_pchBitstreamFile);
    exit(EXIT_FAILURE);
  }

  InputByteStream bytestream(bitstreamFile);

  m_iPOCLastDisplay += m_iSkipFrame;      // set the last displayed POC correctly for skip forward.

  uint8_t *nalUnit=NULL;
  HEVCDecLib_Picture* picout=NULL;
  while (!bytestream.isEOF() || bytestream.m_BufferIdx < bytestream.m_ReadSize) {
    int size;

    byteStreamNALUnit(bytestream, nalUnit, size);
    // call actual decoding function
    if(size == 0) {
      /* this can happen if the following occur:
       *  - empty input file
       *  - two back-to-back start_code_prefixes
       *  - start_code_prefix immediately followed by EOF
       */
      fprintf(stderr, "Warning: Attempt to decode an empty NAL unit\n");
    } else {
      int ret;
      if ( m_bUseInternalPics ){
        if (picout == NULL){
          picout = getNewPictureBuffer();
        }
      }
      if ( (ret = HEVCDecLib_DecodeNALU(m_hHEVCDecoder, nalUnit, size, 0, &picout)) ){
        assert( ret==1 );
        xCheckMD5( picout );
        xWriteOutput( (PictureContainer*) picout->opaque, false );

        if ( m_bUseInternalPics ){
          picout = NULL;
        }
      }
    }
  }
  free(nalUnit);

  HEVCDecLib_FlushInFlightPictures(m_hHEVCDecoder);

  if ( m_bUseInternalPics ){
    if (picout == NULL){
      picout = getNewPictureBuffer();
    }
  }
  while ( HEVCDecLib_GetDecPicture(m_hHEVCDecoder, &picout, true) ){
    xCheckMD5( picout);
    xWriteOutput((PictureContainer*) picout->opaque, false);
    if ( m_bUseInternalPics ){
      picout = getNewPictureBuffer();
    }
  }

  if (m_dFps > 0.0) {
    xWriteOutput(NULL, false);
  }

}

// ====================================================================================================================
// Protected member functions
// ====================================================================================================================


/**
 * Produce an ascii(hex) representation of picture digest.
 *
 * Returns: a statically allocated null-terminated string.  DO NOT FREE.
 */
const char* digestToString(unsigned char digest[3][16], int numChar)
{
  const char* hex = "0123456789abcdef";
  static char string[99];
  int cnt=0;
  for(int yuvIdx=0; yuvIdx<3; yuvIdx++)
  {
    for (int i = 0; i < numChar; i++)
    {
      string[cnt++] = hex[digest[yuvIdx][i] >> 4];
      string[cnt++] = hex[digest[yuvIdx][i] & 0xf];
    }
    string[cnt++] = ',';
  }

  string[cnt-1] = '\0';
  return string;
}

/**
 * Calculate and print hash for pic, compare to picture_digest SEI if
 * present in seis.  seis may be NULL.  Hash is printed to stdout, in
 * a manner suitable for the status line. Theformat is:
 *  [Hash_type:xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx,(yyy)]
 * Where, x..x is the hash
 *        yyy has the following meanings:
 *            OK          - calculated hash matches the SEI message
 *            ***ERROR*** - calculated hash does not match the SEI message
 *            unk         - no SEI message was available for comparison
 */
void HEVCDecoderApp::xCheckMD5( HEVCDecLib_Picture* pHEVCPic )
{
  double frame_time;
  if (m_verbose > 0 ){
    frame_time = pHEVCPic->dStopTime -pHEVCPic->dStartTime;
    m_vFrameTimes.push_back(frame_time);
  }

  if ( ( m_decodedPictureHashSEIEnabled  && pHEVCPic->hashType ) || m_verbose>1 ){
    char c = (pHEVCPic->uiPicType == I_FRAME ? 'I' : pHEVCPic->uiPicType == P_FRAME ? 'P' : 'B');
    if (!pHEVCPic->bReferenced) c += 32;

    //-- For time output for each slice
    printf("\nPOC %4d TId: %1d NAL: %3d ( %c-SLICE, QP%3d ) ",
        pHEVCPic->uiPOC,
        pHEVCPic->uiTLayer,
        pHEVCPic->uiNalType,
        c,
        pHEVCPic->uiQp);
  }
  if(m_verbose>1){
    printf("[DT %7.2f ms] [CPS %7d B] ",
          1000*frame_time,
          pHEVCPic->uiCodedPicSize);
  }
  m_slicebytes += pHEVCPic->uiCodedPicSize;


  if ( m_decodedPictureHashSEIEnabled  && pHEVCPic->hashType ){
    /* compare digest against received version */
    const char* ok = "(unk)";
    bool mismatch = false;

    int numChar = 0;
    if ( strcmp(pHEVCPic->hashType,"MD5")==0 ){
      numChar = 16;
    } else if ( strcmp(pHEVCPic->hashType,"CRC")==0 ){
      numChar = 2;
    } else if ( strcmp(pHEVCPic->hashType,"Checksum")==0 ){
      numChar = 4;
    }

    if ( numChar > 0 ){
      ok = "(OK)";
      for(int yuvIdx = 0; yuvIdx < 3; yuvIdx++)
      {
        for (unsigned i = 0; i < numChar; i++)
        {
          if (pHEVCPic->refDigest[yuvIdx][i] != pHEVCPic->recDigest[yuvIdx][i])
          {
            ok = "(***ERROR***)";
            mismatch = true;
          }
        }
      }
    }

    printf("[%s:%s,%s] ", pHEVCPic->hashType, digestToString( pHEVCPic->recDigest, numChar), ok);
    if (mismatch)
    {
      m_bMD5MisMatch = true;
      printf("[rx%s:%s] ", pHEVCPic->hashType, digestToString( pHEVCPic->refDigest, numChar));
    }
  }
}

void HEVCDecoderApp::outputThread()
{
  std::unique_lock<std::mutex> lock(m_ReadyQlock);
  while (m_qReadyPics.size() < m_iOutputBufferThres){
    m_ReadyQCond.wait(lock);
  }
  lock.unlock();

  m_next = HEVCDecLib_GetRealTime();
  m_startoutputtime =m_next;

  while (1)
  {
    lock.lock();
    while (m_qReadyPics.empty()){
      m_ReadyQCond.wait(lock);
    }
    PictureContainer* pNextPicOut = m_qReadyPics.front();
    m_qReadyPics.pop();
    if (m_qReadyPics.size()< m_iOutputBufferThres){
      m_ReadyQCond.notify_one();
    }
    lock.unlock();

    if (m_bLimitFps ){
      double curtime, difftime;
      curtime = HEVCDecLib_GetRealTime();
      difftime = m_next- curtime ;
      if (difftime > 0 ){
        m_next += m_frametime;
        std::this_thread::sleep_for(std::chrono::milliseconds((int)(difftime*1000)));
      } else {
    	m_next = curtime+m_frametime; //this will make sure late frames are reflected in over time (not allow catchup)
      }
    }
    if (pNextPicOut == NULL)
      break;

    // write to file
    if ( m_pchReconFile ) {
      m_cTVideoIOYuvReconFile.write( pNextPicOut->pHEVCPic, m_bGrid);
    }

    assert(0);

    if(m_bDraw) {
      if(m_bUseNema) {
        nema.yuv2rgb(pNextPicOut->pHEVCPic);
      } else {
        m_cTVideoIOYuvReconFile.draw(pNextPicOut->pHEVCPic, m_bGrid);
      }
    }

    if ( !m_bUseInternalPics )
      returnPictureBuffer(pNextPicOut);
    m_outframes++;
  }
  m_stopoutputtime = HEVCDecLib_GetRealTime();
}

/** \param pcListPic list of pictures to be written to file
    \todo            DYN_REF_FREE should be revised
 */
void HEVCDecoderApp::xWriteOutput(PictureContainer* pPicOut, bool bFlush)
{
  if (m_dFps> 0.0){
    std::unique_lock<std::mutex> lock(m_ReadyQlock);
    while (m_qReadyPics.size() >= m_iOutputBufferMax){
      m_ReadyQCond.wait(lock);
    }
    m_qReadyPics.push(pPicOut);
    m_ReadyQCond.notify_one();
    lock.unlock();
    return;
  } else {
    // write to file
    if ( m_pchReconFile ) {
      m_cTVideoIOYuvReconFile.write( pPicOut->pHEVCPic, m_bGrid);
    }

    if(m_bDraw) {
      if(m_bUseNema) {
        nema.yuv2rgb(pPicOut->pHEVCPic);
      } else {
        m_cTVideoIOYuvReconFile.draw(pPicOut->pHEVCPic, m_bGrid);
      }
    }

    returnPictureBuffer(pPicOut);

    m_outframes++;
  }
}

int HEVCDecoderApp::allocPictureBuffer(PictureContainer* pPicCon)
{
  HEVCDecLib_Picture* pic = new HEVCDecLib_Picture;
  memset(pic, 0, sizeof(HEVCDecLib_Picture));
  pic->uiLHeight = m_hDescript.uiHeight;
  pic->uiCHeight = m_hDescript.uiHeight >> (int)(m_hDescript.uiChromaFormat==1);
  pic->uiLWidth  = m_hDescript.uiWidth;
  pic->uiCWidth  = m_hDescript.uiWidth  >> (int)(m_hDescript.uiChromaFormat==1||m_hDescript.uiChromaFormat==2);

  pic->uiBitDepthY = m_hDescript.uiBitDepthY;
  pic->uiBitDepthC = m_hDescript.uiBitDepthC;
  int pelsizeL = (pic->uiBitDepthY+7)/8;
  int pelsizeC = (pic->uiBitDepthC+7)/8;
  int align    = m_hDescript.uiAlign;

  int marginleftL = m_hDescript.uiMarginL;
  int marginrightL = m_hDescript.uiMarginR;
  pic->uiLOffset = marginleftL;
  pic->uiLStride = marginleftL + pic->uiLWidth + marginrightL;

  int marginleftC = marginleftL >> (int)(m_hDescript.uiChromaFormat==1||m_hDescript.uiChromaFormat==2);
  int marginrightC = marginrightL >> (int)(m_hDescript.uiChromaFormat==1||m_hDescript.uiChromaFormat==2);
  pic->uiCOffset = marginleftC;
  pic->uiCStride = marginleftC + pic->uiCWidth + marginrightC;

  int margintopC = m_hDescript.uiMarginT >> (int)(m_hDescript.uiChromaFormat==1);
  int marginbottomC = m_hDescript.uiMarginB >> (int)(m_hDescript.uiChromaFormat==1);
  int linesL = m_hDescript.uiMarginT + m_hDescript.uiMarginB + pic->uiLHeight;
  int linesC = margintopC + marginbottomC + pic->uiCHeight;
  int allocsizeL = linesL*pic->uiLStride*pelsizeL;
  int allocsizeC = linesC*pic->uiCStride*pelsizeC;

  pic->uiLOffset = marginleftL;
  pic->uiLStride = marginleftL + pic->uiLWidth + marginrightL;
  pic->uiCOffset = marginleftC;
  pic->uiCStride = marginleftC + pic->uiCWidth + marginrightC;


  if (m_bUseInternalPics){
    pic->uiLOffset = 0;
    pic->uiLStride = pic->uiLWidth;
    pic->uiCOffset = 0;
    pic->uiCStride = pic->uiCWidth;
    margintopC = marginbottomC = 0;
    linesL = pic->uiLHeight;
    linesC = pic->uiCHeight;
    allocsizeL = linesL*pic->uiLStride*pelsizeL;
    allocsizeC = linesC*pic->uiCStride*pelsizeC;
  }

  pic->bChromaIntl = m_bChromaIntl;
  unsigned char* planes;
  unsigned char* planes_nema = NULL;

  if(m_bUseNema) {
    planes_nema = (unsigned char*) nema.nema_malloc(allocsizeL + 2*allocsizeC);
  }

  planes = (unsigned char*) xMallocAlign(unsigned char, allocsizeL + 2*allocsizeC, align);

  pic->pLuma = planes + (pic->uiLOffset + m_hDescript.uiMarginT*pic->uiLStride)*pelsizeL;

  if(m_bUseNema) {
    pic->pLuma_nema = planes_nema + (pic->uiLOffset + m_hDescript.uiMarginT*pic->uiLStride)*pelsizeL;
  }

  if(m_bChromaIntl) {
    pic->pChroma = planes + allocsizeL + 2*(pic->uiCOffset + margintopC*pic->uiCStride)*pelsizeC;
    pic->uiCWidth  *=2;
    pic->uiCStride *=2;

    if(m_bUseNema) {
      pic->pChroma_nema = planes_nema + allocsizeL + 2*(pic->uiCOffset + margintopC*pic->uiCStride)*pelsizeC;
    }
  } else {
    pic->pCb = planes + allocsizeL + (pic->uiCOffset + margintopC*pic->uiCStride)*pelsizeC;
    pic->pCr = planes + allocsizeL + allocsizeC + (pic->uiCOffset + margintopC*pic->uiCStride)*pelsizeC;

    if(m_bUseNema) {
      pic->pCb_nema = planes_nema + allocsizeL + (pic->uiCOffset + margintopC*pic->uiCStride)*pelsizeC;
      pic->pCr_nema = planes_nema + allocsizeL + allocsizeC + (pic->uiCOffset + margintopC*pic->uiCStride)*pelsizeC;
    }
  }

  pic->opaque         = pPicCon;
  pPicCon->pHEVCPic   = pic;
  pPicCon->planes     = planes;
  pPicCon->needoutput = true;
  pPicCon->refcount   = 0;

  return 0;
}

HEVCDecLib_Picture* HEVCDecoderApp::getNewPictureBuffer()
{
  if (!m_bDescriptInitialized){
    if (HEVCDecLib_GetDescription(m_hHEVCDecoder, m_hDescript)){
      //cannot alloc picture without description
      return NULL;
    }
    m_bDescriptInitialized = true;
  }

//  std::lock_guard<std::mutex> lockDPList(m_cMutexDecPicPool);

  std::list<PictureContainer*>::iterator pic = m_lDecPicPool.begin();
  for (; pic != m_lDecPicPool.end(); pic++){
    if ((*pic)->refcount==0 && !(*pic)->needoutput){
      (*pic)->needoutput = true;
      return (*pic)->pHEVCPic;
    }
  }
  PictureContainer* pPicCon = new PictureContainer;
  if ( allocPictureBuffer(pPicCon) ){
    assert(0);
  }
  m_lDecPicPool.push_back(pPicCon);
  return pPicCon->pHEVCPic;
}

void HEVCDecoderApp::returnPictureBuffer(PictureContainer* pPicCon)
{
//  std::lock_guard<std::mutex> lockDPList(m_cMutexDecPicPool);
  pPicCon->needoutput = false;
}

void HEVCDecoderApp::linkPictureBuffer(PictureContainer* pPicCon)
{
//  std::lock_guard<std::mutex> lockDPList(m_cMutexDecPicPool);
  pPicCon->refcount++;
}

void HEVCDecoderApp::unLinkPictureBuffer(PictureContainer* pPicCon)
{
//  std::lock_guard<std::mutex> lockDPList(m_cMutexDecPicPool);
  assert(pPicCon->refcount>0);
  pPicCon->refcount--;
}

HEVCDecLib_Picture* HEVCDecoderApp::get_new_picture_buffer(Callback_Handle cbHandle)
{
  HEVCDecoderApp* pcTAppDecTop = (HEVCDecoderApp*) cbHandle;
  return pcTAppDecTop->getNewPictureBuffer();
}

void HEVCDecoderApp::link_picture_buffer(Callback_Handle cbHandle, HEVCDecLib_Picture* pPic)
{
  HEVCDecoderApp* pcTAppDecTop = (HEVCDecoderApp*) cbHandle;
  pcTAppDecTop->linkPictureBuffer((PictureContainer*)pPic->opaque);
}

void HEVCDecoderApp::unlink_picture_buffer(Callback_Handle cbHandle, HEVCDecLib_Picture* pPic)
{
  HEVCDecoderApp* pcTAppDecTop = (HEVCDecoderApp*) cbHandle;
  pcTAppDecTop->unLinkPictureBuffer((PictureContainer*)pPic->opaque);
}
