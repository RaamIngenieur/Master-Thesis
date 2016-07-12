/*
 * \file    hevcdec.cpp
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

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "HEVCDecoderApp.h"

// ====================================================================================================================
// Main function
// ====================================================================================================================

int main(int argc, char* argv[])
{
  HEVCDecoderApp  cHEVCDecoder;

  // print information
  fprintf( stdout, "\n" );
  fprintf( stdout, "TUB-AES HEVC Decoder %s - ", HEVCDecLib_GetVersion() );
#ifdef _WIN32
  fprintf( stdout, "Windows " );
#elif  __linux
  fprintf( stdout, "Linux " );
#elif  __CYGWIN__
  fprintf( stdout, "Cygwin " );
#elif __APPLE__
  fprintf( stdout, "Mac OS X " );
#else
  fprintf( stdout, "Unknown OS " );
#endif
  fprintf( stdout, "%d-bit ", (sizeof(void*) == 8 ? 64 : 32 ));
  fprintf( stdout, "\n" );

  // parse configuration
  if(!cHEVCDecoder.parseCfg( argc, argv ))
  {
    return 1;
  }

  // create application decoder class
  cHEVCDecoder.create();

  // call decoding function
  cHEVCDecoder.decode();
  bool mis_match = cHEVCDecoder.getMisMatch();
  if (mis_match)
  {
    printf("\n\n***ERROR*** A decoding mismatch occured: signalled md5sum does not match\n");
  }
  // destroy application decoder class
  cHEVCDecoder.destroy();

  return mis_match ? EXIT_FAILURE : EXIT_SUCCESS;
}
