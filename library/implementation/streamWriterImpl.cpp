/*
$fileHeader$
*/

/*! \file streamWriter.cpp
    \brief Implementation of the streamWriter class.

*/

#include "streamWriterImpl.h"
#include <string.h>

namespace puntoexe
{

///////////////////////////////////////////////////////////
//
// Constructor
//
///////////////////////////////////////////////////////////
streamWriter::streamWriter(std::shared_ptr<baseStreamOutput> pControlledStream, std::uint32_t virtualStart /* =0 */, std::uint32_t virtualLength /* =0 */):
    streamController(virtualStart, virtualLength),
    m_pControlledStream(pControlledStream),
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
	std::uint32_t writeLength = (std::uint32_t)(m_pDataBufferCurrent - m_pDataBufferStart);
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
void streamWriter::write(const std::uint8_t* pBuffer, std::uint32_t bufferLength)
{
	while(bufferLength != 0)
	{
		if(m_pDataBufferCurrent == m_pDataBufferMaxEnd)
		{
			flushDataBuffer();
                        if(bufferLength > (std::uint32_t)(m_pDataBufferMaxEnd - m_pDataBufferCurrent) )
                        {
                            m_pControlledStream->write(m_dataBufferStreamPosition + m_virtualStart, pBuffer, bufferLength);
                            m_dataBufferStreamPosition += bufferLength;
                            return;
                        }
		}
		std::uint32_t copySize = (std::uint32_t)(m_pDataBufferMaxEnd - m_pDataBufferCurrent);
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
