/*
$fileHeader$
*/

/*! \file codec.cpp
    \brief Implementation of the base class for the codecs.

*/

#include "exceptionImpl.h"
#include "streamReaderImpl.h"
#include "streamWriterImpl.h"
#include "codecImpl.h"
#include "dataSetImpl.h"
#include "codecFactoryImpl.h"
#include <string.h>


namespace puntoexe
{

namespace imebra
{

namespace codecs
{

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Read a stream and write it into a dataset.
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
ptr<dataSet> codec::read(ptr<streamReader> pSourceStream, std::uint32_t maxSizeBufferLoad /* = 0xffffffff */)
{
	PUNTOEXE_FUNCTION_START(L"codec::read");

	// Reset the codec's bits buffer
	///////////////////////////////////////////////////////////
	pSourceStream->resetInBitsBuffer();

	// Store the stream's position
	///////////////////////////////////////////////////////////
	std::uint32_t position=pSourceStream->position();

	// Create a new dataset
	///////////////////////////////////////////////////////////
	ptr<dataSet> pDestDataSet(new dataSet);

	// Read the stream
	///////////////////////////////////////////////////////////
	try
	{
		readStream(pSourceStream, pDestDataSet, maxSizeBufferLoad);
	}
	catch(codecExceptionWrongFormat&)
	{
		pSourceStream->seek((std::int32_t)position);
		PUNTOEXE_RETHROW("Detected a wrong format. Rewinding file");
	}

	// Update the charsets in the tags
	///////////////////////////////////////////////////////////
	pDestDataSet->updateTagsCharset();

	return pDestDataSet;

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Write a dataset into a stream.
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void codec::write(ptr<streamWriter> pDestStream, ptr<dataSet> pSourceDataSet)
{
	PUNTOEXE_FUNCTION_START(L"codec::write");

	// Update charsets tag
	///////////////////////////////////////////////////////////
	pSourceDataSet->updateCharsetTag();

	pDestStream->resetOutBitsBuffer();
	writeStream(pDestStream, pSourceDataSet);
	pDestStream->flushDataBuffer();

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Allocate a channel's memory
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void channel::allocate(std::uint32_t sizeX, std::uint32_t sizeY)
{
	PUNTOEXE_FUNCTION_START(L"channel::allocate");

	m_sizeX = sizeX;
	m_sizeY = sizeY;
	m_bufferSize = sizeX * sizeY;
	m_memory = ptr<memory>(memoryPool::getMemoryPool()->getMemory(m_bufferSize * sizeof(std::int32_t) ));
	m_pBuffer = (std::int32_t*)(m_memory->data());

	::memset(m_pBuffer, 0, m_bufferSize * sizeof(std::int32_t));

	PUNTOEXE_FUNCTION_END();
}



} // namespace codecs

} // namespace imebra

} // namespace puntoexe

