/*
 * \file    AnnexBread.cpp
 * \brief
 * \author  chi.c.chi@tu-berlin.de
 * \date    14/07/2012
 *
 * Copyright:
 * Technische Universit�t Berlin
 * Architektur Eingebetteter Systeme (AES)
 * Einsteinufer 17
 * 10587 Berlin
 * Deutschland
 */

#include <stdint.h>
#include <iostream>
#include <cassert>
#include <stdlib.h>
#include "AnnexBread.h"

using namespace std;

/**
 * Parse an AVC AnnexB Bytestream bs to extract a single nalUnit
 * while accumulating bytestream statistics into stats.
 *
 * Returns false if EOF was reached (NB, nalunit data may be valid),
 *         otherwise true.
 */
bool byteStreamNALUnit( InputByteStream& bs, uint8_t*& nalbuf, int& size)
{
  nalbuf = (uint8_t*)realloc(nalbuf, bs.m_ReadSize- bs.m_BufferIdx+8);
  int nalbufidx=0;
  if (bs.m_BufferIdx>=0){
    bs.m_State=0;
  }else {
    bs.m_State = -bs.m_BufferIdx;
    bs.m_BufferIdx = 0;
  }
  while (1){
    if ( bs.isEOF() && bs.m_BufferIdx == bs.m_ReadSize){
      size=nalbufidx;
      nalbuf[nalbufidx]   = 0; //allow 3 byte overread without valgrind complaint
      nalbuf[nalbufidx+1] = 0;
      nalbuf[nalbufidx+2] = 0;
      return true;
    } else if (bs.m_BufferIdx == bs.m_ReadSize){
      bs.readNextChunk();
      nalbuf = (uint8_t*)realloc(nalbuf, nalbufidx+bs.m_ReadSize+8);
    }

    while (bs.m_BufferIdx < bs.m_ReadSize ){
      switch (bs.m_State){
      case 0:
        if (bs.m_Buffer[bs.m_BufferIdx] == 0)
          bs.m_State =1;
        bs.m_BufferIdx++;
        break;
      case 1:
        if (bs.m_Buffer[bs.m_BufferIdx] == 0)
          bs.m_State =2;
        else{
          bs.m_State =0;
        }
        bs.m_BufferIdx++;
        break;
      case 2:
        if (bs.m_Buffer[bs.m_BufferIdx] == 1)
          bs.m_State =3;
        else if (bs.m_Buffer[bs.m_BufferIdx] > 1){
          bs.m_State = 0;
        }
        bs.m_BufferIdx++;
        break;
      case 3:
        while(bs.m_BufferIdx < bs.m_ReadSize -8){
          if (!((~*(const uint64_t*)(bs.m_Buffer+ bs.m_BufferIdx) &
              (*(const uint64_t*)(bs.m_Buffer+ bs.m_BufferIdx) - 0x0101010101010101ULL)) & 0x8080808080808080ULL)){
            *(uint64_t*)(nalbuf+nalbufidx) = *(const uint64_t*)(bs.m_Buffer+ bs.m_BufferIdx);            
            nalbufidx+=8;
            bs.m_BufferIdx+=8;

          } else {
            break;
          }
        }
        for (;bs.m_BufferIdx < bs.m_ReadSize;){
          if (bs.m_Buffer[bs.m_BufferIdx]!=0){
            nalbuf[nalbufidx++] = bs.m_Buffer[bs.m_BufferIdx++];
          }
          else{
            bs.m_State= 4;
            bs.m_BufferIdx++;
            break;
          }
        }
        break;
      case 4:
        if (bs.m_Buffer[bs.m_BufferIdx]!=0){
          nalbuf[nalbufidx++] = 0;
          nalbuf[nalbufidx++] = bs.m_Buffer[bs.m_BufferIdx++];
          bs.m_State= 3;
        }else {
          bs.m_BufferIdx++;
          bs.m_State= 5;
        }
        break;
      case 5:
        if (bs.m_Buffer[bs.m_BufferIdx]==1){
          bs.m_BufferIdx-=2;
          nalbuf[nalbufidx]   = 0; //allow 3 byte overread without valgrind complaint
          nalbuf[nalbufidx+1] = 0;
          nalbuf[nalbufidx+2] = 0;
          size=nalbufidx;
          return false;
        }else if(bs.m_Buffer[bs.m_BufferIdx] > 1){
          nalbuf[nalbufidx++] = 0;
          nalbuf[nalbufidx++] = 0;
          nalbuf[nalbufidx++] = bs.m_Buffer[bs.m_BufferIdx];
          bs.m_State= 3;
        }
        bs.m_BufferIdx++;
        break;
      }
    }
  }
  assert(0);
  return false;
}
