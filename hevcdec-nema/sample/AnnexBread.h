/*
 * \file    AnnexBread.h
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


#ifndef ANNEXBREAD_H
#define ANNEXBREAD_H

#include <cstdint>
#include <istream>
#include <cstring>

#define BUFSIZE 4096
#define PADDING 0

class InputByteStream
{
public:
  /**
   * Create a bytestream reader that will extract bytes from
   * istream.
   *
   * NB, it isn't safe to access istream while in use by a
   * InputByteStream.
   *
   * Side-effects: the exception mask of istream is set to eofbit
   */
  InputByteStream(std::istream& istream)
  : m_Input(istream)
  , m_BufferIdx(0)
  , m_State(0)
  {
    ::memset(m_Buffer, 0, BUFSIZE+PADDING);
    readNextChunk();
  }

  void readNextChunk()
  {
    m_Input.read((char*)m_Buffer, BUFSIZE);
    m_ReadSize = (int) m_Input.gcount();
    m_BufferIdx = 0;
  }

  bool isEOF()
  {
    return m_Input.eof();
  }

private:
  std::istream& m_Input; /* Input stream to read from */
public:
  uint8_t m_Buffer[BUFSIZE+PADDING];
  int m_BufferIdx;
  int m_State;
  int m_ReadSize;
};

bool byteStreamNALUnit(InputByteStream& bs, uint8_t*& nalUnit, int& size);

#endif
