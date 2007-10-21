/*
$fileHeader$
*/

/*! \file streamReader.cpp
    \brief Implementation of the streamReader class.

*/

#include "../include/streamReader.h"

namespace puntoexe
{

///////////////////////////////////////////////////////////
//
// Constructor
//
///////////////////////////////////////////////////////////
streamReader::streamReader(ptr<baseStream> pControlledStream, imbxUint32 virtualStart /* =0 */, imbxUint32 virtualLength /* =0 */):
	m_inBitsBuffer(0),
	m_inBitsNum(0),
	streamController(pControlledStream, virtualStart, virtualLength)
{
}


///////////////////////////////////////////////////////////
//
// Refill the data buffer
//
///////////////////////////////////////////////////////////
imbxUint32 streamReader::fillDataBuffer()
{
	PUNTOEXE_FUNCTION_START(L"streamReader::fillDataBuffer");

	imbxUint32 currentPosition = position();
	imbxUint32 readLength = (imbxUint32)(m_pDataBufferMaxEnd - m_pDataBufferStart);
	if(m_virtualLength != 0)
	{
		if(currentPosition >= m_virtualLength)
		{
			m_dataBufferStreamPosition = m_virtualLength;
			m_pDataBufferCurrent = m_pDataBufferEnd = m_pDataBufferStart;
			if(m_bEof)
			{
				PUNTOEXE_THROW(streamExceptionEOF, "End of the stream already reached");
			}
			
			m_bEof = true;
			return 0;
		}
		if(currentPosition + readLength > m_virtualLength)
		{
			readLength = m_virtualLength - currentPosition;
		}
	}
	imbxUint32 readBytes = m_pControlledStream->read(currentPosition + m_virtualStart, m_pDataBufferStart, readLength);
	m_dataBufferStreamPosition = currentPosition;
	m_pDataBufferEnd = m_pDataBufferStart + readBytes;
	m_pDataBufferCurrent = m_pDataBufferStart;
	if(readBytes == 0)
	{
		if(m_bEof)
		{
			PUNTOEXE_THROW(streamExceptionEOF, "End of the stream already reached");
		}
		m_bEof = true;
		return 0;
	}
	m_bEof = false;
	return readBytes;

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
//
// Return the specified number of bytes from the stream
//
///////////////////////////////////////////////////////////
imbxUint32 streamReader::read(imbxUint8* pBuffer, imbxUint32 bufferLength)
{
	imbxUint32 readBytes(0);

	while(bufferLength != 0)
	{
		// Update the data buffer if it is empty
		///////////////////////////////////////////////////////////
		if(m_pDataBufferCurrent == m_pDataBufferEnd)
		{
			// EOF?
			///////////////////////////////////////////////////////////
			if(fillDataBuffer() == 0)
			{
				return readBytes;
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
		readBytes += copySize;
	}

	return readBytes;
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

	fillDataBuffer();
}



} // namespace puntoexe
