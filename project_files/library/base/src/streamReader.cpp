/*
$fileHeader$
*/

/*! \file streamReader.cpp
    \brief Implementation of the streamReader class.

*/

#include "../include/streamReader.h"
#include <string.h>

namespace puntoexe
{

///////////////////////////////////////////////////////////
//
// Constructor
//
///////////////////////////////////////////////////////////
streamReader::streamReader(ptr<baseStream> pControlledStream, imbxUint32 virtualStart /* =0 */, imbxUint32 virtualLength /* =0 */):
	streamController(pControlledStream, virtualStart, virtualLength),
	m_inBitsBuffer(0),
	m_inBitsNum(0)
{
}


///////////////////////////////////////////////////////////
//
// Returns true if the last byte has been read
//
///////////////////////////////////////////////////////////
bool streamReader::endReached()
{
    return (m_pDataBufferCurrent == m_pDataBufferEnd && fillDataBuffer() == 0);
}


///////////////////////////////////////////////////////////
//
// Refill the data buffer
//
///////////////////////////////////////////////////////////
imbxUint32 streamReader::fillDataBuffer()
{
	PUNTOEXE_FUNCTION_START(L"streamReader::fillDataBuffer");

	imbxUint32 readLength = (imbxUint32)(m_pDataBufferMaxEnd - m_pDataBufferStart);
	imbxUint32 readBytes = fillDataBuffer(m_pDataBufferStart, readLength);
	if(readBytes == 0)
	{
		m_pDataBufferCurrent = m_pDataBufferEnd = m_pDataBufferStart;
		return 0;
	}
	m_pDataBufferEnd = m_pDataBufferStart + readBytes;
	m_pDataBufferCurrent = m_pDataBufferStart;
	return readBytes;

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
//
// Read data from the stream into the specified buffer
//
///////////////////////////////////////////////////////////
imbxUint32 streamReader::fillDataBuffer(imbxUint8* pDestinationBuffer, imbxUint32 readLength)
{
	imbxUint32 currentPosition = position();
	if(m_virtualLength != 0)
	{
		if(currentPosition >= m_virtualLength)
		{
			m_dataBufferStreamPosition = m_virtualLength;
			return 0;
		}
		if(currentPosition + readLength > m_virtualLength)
		{
			readLength = m_virtualLength - currentPosition;
		}
	}
	m_dataBufferStreamPosition = currentPosition;
	return m_pControlledStream->read(currentPosition + m_virtualStart, pDestinationBuffer, readLength);
}



///////////////////////////////////////////////////////////
//
// Return the specified number of bytes from the stream
//
///////////////////////////////////////////////////////////
void streamReader::read(imbxUint8* pBuffer, imbxUint32 bufferLength)
{
	while(bufferLength != 0)
	{
		// Update the data buffer if it is empty
		///////////////////////////////////////////////////////////
		if(m_pDataBufferCurrent == m_pDataBufferEnd)
		{
			if(bufferLength >= m_pDataBufferMaxEnd - m_pDataBufferStart)
			{
				// read the data directly into the destination buffer
				///////////////////////////////////////////////////////////
				if(fillDataBuffer(pBuffer, bufferLength) != bufferLength)
				{
					throw(streamExceptionEOF("Attempt to read past the end of the file"));
				}
				return;

			}

			if(fillDataBuffer() == 0)
			{
				throw(streamExceptionEOF("Attempt to read past the end of the file"));
			}
		}

		// Copy the available data into the return buffer
		///////////////////////////////////////////////////////////
		imbxUint32 copySize = bufferLength;
		imbxUint32 maxSize = (imbxUint32)(m_pDataBufferEnd - m_pDataBufferCurrent);
		if(copySize > maxSize)
		{
			copySize = maxSize;
		}
		::memcpy(pBuffer, m_pDataBufferCurrent, (size_t)copySize);
		bufferLength -= copySize;
		pBuffer += copySize;
		m_pDataBufferCurrent += copySize;
	}
}


///////////////////////////////////////////////////////////
//
// Seek the read position
//
///////////////////////////////////////////////////////////
void streamReader::seek(imbxInt32 newPosition, bool bCurrent /* =false */)
{
	// Calculate the absolute position
	///////////////////////////////////////////////////////////
	imbxUint32 finalPosition = bCurrent ? (position() + newPosition) : newPosition;

	// The requested position is already in the data buffer?
	///////////////////////////////////////////////////////////
	imbxUint32 bufferEndPosition = m_dataBufferStreamPosition + (imbxUint32)(m_pDataBufferEnd - m_pDataBufferStart);
	if(finalPosition >= m_dataBufferStreamPosition && finalPosition < bufferEndPosition)
	{
		m_pDataBufferCurrent = m_pDataBufferStart + finalPosition - m_dataBufferStreamPosition;
		return;
	}

	// The requested position is not in the data buffer
	///////////////////////////////////////////////////////////
	m_pDataBufferCurrent = m_pDataBufferEnd = m_pDataBufferStart;
	m_dataBufferStreamPosition = finalPosition;

}



} // namespace puntoexe
