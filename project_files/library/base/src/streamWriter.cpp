/*
$fileHeader$
*/

/*! \file streamWriter.cpp
    \brief Implementation of the streamWriter class.

*/

#include "../include/streamWriter.h"
#include <string.h>

namespace puntoexe
{

///////////////////////////////////////////////////////////
//
// Constructor
//
///////////////////////////////////////////////////////////
streamWriter::streamWriter(ptr<baseStream> pControlledStream, imbxUint32 virtualStart /* =0 */, imbxUint32 virtualLength /* =0 */):
	streamController(pControlledStream, virtualStart, virtualLength),
	m_outBitsBuffer(0),
	m_outBitsNum(0)
{
}


///////////////////////////////////////////////////////////
//
// Destructor
//
///////////////////////////////////////////////////////////
streamWriter::~streamWriter()
{
	flushDataBuffer();
}


///////////////////////////////////////////////////////////
//
// Flush the data buffer
//
///////////////////////////////////////////////////////////
void streamWriter::flushDataBuffer()
{
	imbxUint32 writeLength = (imbxUint32)(m_pDataBufferCurrent - m_pDataBufferStart);
	if(writeLength == 0)
	{
		return;
	}
	m_pControlledStream->write(m_dataBufferStreamPosition + m_virtualStart, m_pDataBufferStart, writeLength);
	m_pDataBufferCurrent = m_pDataBufferEnd = m_pDataBufferStart;
	m_dataBufferStreamPosition += writeLength;
}


///////////////////////////////////////////////////////////
//
// Write into the stream
//
///////////////////////////////////////////////////////////
void streamWriter::write(const imbxUint8* pBuffer, imbxUint32 bufferLength)
{
	while(bufferLength != 0)
	{
		if(m_pDataBufferCurrent == m_pDataBufferMaxEnd)
		{
			flushDataBuffer();
                        if(bufferLength > m_pDataBufferMaxEnd - m_pDataBufferCurrent)
                        {
                            m_pControlledStream->write(m_dataBufferStreamPosition + m_virtualStart, pBuffer, bufferLength);
                            m_dataBufferStreamPosition += bufferLength;
                            return;
                        }
		}
		imbxUint32 copySize = (imbxUint32)(m_pDataBufferMaxEnd - m_pDataBufferCurrent);
		if(copySize > bufferLength)
		{
			copySize = bufferLength;
		}
		::memcpy(m_pDataBufferCurrent, pBuffer, copySize);
		pBuffer += copySize;
		bufferLength -= copySize;
		m_pDataBufferCurrent += copySize;
		m_pDataBufferEnd = m_pDataBufferCurrent;
	}
}


} // namespace puntoexe
