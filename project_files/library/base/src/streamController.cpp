/*
$fileHeader$
*/

/*! \file streamController.cpp
    \brief Implementation of the streamController class.

*/

#include "../include/streamController.h"

namespace puntoexe
{

// Used for the endian check
///////////////////////////////////////////////////////////
static const std::uint16_t m_endianCheck(0x00ff);
static std::uint8_t const * const pBytePointer((std::uint8_t*)&m_endianCheck);
static const streamController::tByteOrdering m_platformByteOrder((*pBytePointer)==0xff ? streamController::lowByteEndian : streamController::highByteEndian);

///////////////////////////////////////////////////////////
//
// Constructor
//
///////////////////////////////////////////////////////////
streamController::streamController(ptr<baseStream> pControlledStream, std::uint32_t virtualStart /* =0 */, std::uint32_t virtualLength /* =0 */):
	m_bJpegTags(false),
        m_pControlledStream(pControlledStream),
		m_dataBuffer(new std::uint8_t[IMEBRA_STREAM_CONTROLLER_MEMORY_SIZE]),
		m_virtualStart(virtualStart),
		m_virtualLength(virtualLength),
		m_dataBufferStreamPosition(0)
{
    m_pDataBufferStart = m_pDataBufferEnd = m_pDataBufferCurrent = m_dataBuffer;
	m_pDataBufferMaxEnd = m_pDataBufferStart + IMEBRA_STREAM_CONTROLLER_MEMORY_SIZE;
}


///////////////////////////////////////////////////////////
//
// Destructor
//
///////////////////////////////////////////////////////////
streamController::~streamController()
{
    delete[] m_dataBuffer;
}


///////////////////////////////////////////////////////////
//
// Retrieve the current position
//
///////////////////////////////////////////////////////////
std::uint32_t streamController::position()
{
	return m_dataBufferStreamPosition + (std::uint32_t)(m_pDataBufferCurrent - m_pDataBufferStart);
}


///////////////////////////////////////////////////////////
//
// Retrieve a pointer to the controlled stream
//
///////////////////////////////////////////////////////////
ptr<baseStream> streamController::getControlledStream()
{
	return m_pControlledStream;
}


///////////////////////////////////////////////////////////
//
// Retrieve the position without considering the virtual
//  start's position
//
///////////////////////////////////////////////////////////
std::uint32_t streamController::getControlledStreamPosition()
{
	return m_dataBufferStreamPosition + (std::uint32_t)(m_pDataBufferCurrent - m_pDataBufferStart) + m_virtualStart;
}


///////////////////////////////////////////////////////////
//
// Adjust the byte ordering of pBuffer
//
///////////////////////////////////////////////////////////
void streamController::adjustEndian(std::uint8_t* pBuffer, const std::uint32_t wordLength, const tByteOrdering endianType, const std::uint32_t words /* =1 */)
{
	if(endianType == m_platformByteOrder || wordLength<2L)
	{
		return;
	}

	switch(wordLength)
	{
	case 2:
		{ // Block needed by evc4. Prevent error on multiple definitions of scanWords
			std::uint8_t tempByte;
			for(std::uint32_t scanWords = words; scanWords != 0; --scanWords)
			{
				tempByte=*pBuffer;
				*pBuffer=*(pBuffer+1);
				*(++pBuffer)=tempByte;
				++pBuffer;
			}
		}
		return;
	case 4:
		{ // Block needed by evc4. Prevent error on multiple definitions of scanWords
			std::uint8_t tempByte0;
			std::uint8_t tempByte1;
			for(std::uint32_t scanWords = words; scanWords != 0; --scanWords)
			{
				tempByte0 = *pBuffer;
				*pBuffer = *(pBuffer+3);
				tempByte1 = *(++pBuffer);
				*pBuffer = *(pBuffer + 1);
				*(++pBuffer) = tempByte1;
				*(++pBuffer) = tempByte0;
				++pBuffer;
			}
		}
		return;
	}
}





} // namespace puntoexe
