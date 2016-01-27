/*
$fileHeader$
*/

/*! \file streamWriter.cpp
    \brief Implementation of the streamWriter class.

*/

#include "streamWriterImpl.h"
#include <string.h>

namespace imebra
{

namespace implementation
{

///////////////////////////////////////////////////////////
//
// Constructor
//
///////////////////////////////////////////////////////////
streamWriter::streamWriter(std::shared_ptr<baseStreamOutput> pControlledStream, size_t virtualStart /* =0 */, size_t virtualLength /* =0 */):
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
    if(m_dataBufferCurrent == 0)
	{
		return;
	}
    m_pControlledStream->write(m_dataBufferStreamPosition + m_virtualStart, m_dataBuffer.data(), m_dataBufferCurrent);
    m_dataBufferStreamPosition += m_dataBufferCurrent;
    m_dataBufferCurrent = 0;
}


///////////////////////////////////////////////////////////
//
// Write into the stream
//
///////////////////////////////////////////////////////////
void streamWriter::write(const std::uint8_t* pBuffer, size_t bufferLength)
{
	while(bufferLength != 0)
	{
        if(m_dataBufferCurrent == m_dataBuffer.size())
		{
			flushDataBuffer();
            if(bufferLength > (size_t)(m_dataBuffer.size() - m_dataBufferCurrent) )
            {
                m_pControlledStream->write(m_dataBufferStreamPosition + m_virtualStart, pBuffer, bufferLength);
                m_dataBufferStreamPosition += bufferLength;
                return;
            }
		}
        size_t copySize = (size_t)(m_dataBuffer.size() - m_dataBufferCurrent);
		if(copySize > bufferLength)
		{
			copySize = bufferLength;
		}
        ::memcpy(&(m_dataBuffer[m_dataBufferCurrent]), pBuffer, copySize);
		pBuffer += copySize;
		bufferLength -= copySize;
        m_dataBufferCurrent += copySize;
        m_dataBufferEnd = m_dataBufferCurrent;
	}
}

} // namespace implementation

} // namespace imebra
