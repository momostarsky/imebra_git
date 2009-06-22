/*
$fileHeader$
*/

/*! \file memoryStream.cpp
    \brief Implementation of the memoryStream class.

*/

#include "../include/exception.h"
#include "../include/memoryStream.h"
#include <string.h>

namespace puntoexe
{

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
//
// memoryStream
//
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Constructor
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
memoryStream::memoryStream(ptr<memory> memoryStream): m_memory(memoryStream)
{
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Write raw data into the stream
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void memoryStream::write(imbxUint32 startPosition, const imbxUint8* pBuffer, imbxUint32 bufferLength)
{
	PUNTOEXE_FUNCTION_START(L"memoryStream::write");

	// Nothing happens if we have nothing to write
	///////////////////////////////////////////////////////////
	if(bufferLength == 0)
	{
		return;
	}

	lockObject lockThis(this);

	// Copy the buffer into the memory
	///////////////////////////////////////////////////////////
	if(startPosition + bufferLength > m_memory->size())
	{
		imbxUint32 newSize = startPosition + bufferLength;
		imbxUint32 reserveSize = ((newSize + 1023) >> 10) << 10; // preallocate blocks of 1024 bytes
		m_memory->reserve(reserveSize);
		m_memory->resize(startPosition + bufferLength);
	}

	::memcpy(m_memory->data() + startPosition, pBuffer, bufferLength);

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Read raw data from the stream
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
imbxUint32 memoryStream::read(imbxUint32 startPosition, imbxUint8* pBuffer, imbxUint32 bufferLength)
{
	PUNTOEXE_FUNCTION_START(L"memoryStream::read");

	if(bufferLength == 0)
	{
		return 0;
	}

	lockObject lockThis(this);

	// Don't read if the requested position isn't valid
	///////////////////////////////////////////////////////////
	imbxUint32 memorySize = m_memory->size();
	if(startPosition >= memorySize)
	{
		return 0;
	}

	// Check if all the bytes are available
	///////////////////////////////////////////////////////////
	imbxUint32 copySize = bufferLength;
	if(startPosition + bufferLength > memorySize)
	{
		copySize = memorySize - startPosition;
	}

	if(copySize == 0)
	{
		return 0;
	}

	::memcpy(pBuffer, m_memory->data() + startPosition, copySize);

	return copySize;

	PUNTOEXE_FUNCTION_END();
}


} // namespace puntoexe
