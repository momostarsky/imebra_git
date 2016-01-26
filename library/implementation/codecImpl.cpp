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
#include "../include/imebra/exceptions.h"
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
std::shared_ptr<dataSet> codec::read(std::shared_ptr<streamReader> pSourceStream, std::uint32_t maxSizeBufferLoad /* = 0xffffffff */)
{
	IMEBRA_FUNCTION_START(L"codec::read");

	// Reset the codec's bits buffer
	///////////////////////////////////////////////////////////
	pSourceStream->resetInBitsBuffer();

	// Store the stream's position
	///////////////////////////////////////////////////////////
    size_t position = pSourceStream->position();

	// Create a new dataset
	///////////////////////////////////////////////////////////
    std::shared_ptr<dataSet> pDestDataSet(std::make_shared<dataSet>());

	// Read the stream
	///////////////////////////////////////////////////////////
	try
	{
		readStream(pSourceStream, pDestDataSet, maxSizeBufferLoad);
	}
    catch(::imebra::codecExceptionWrongFormat&)
	{
        pSourceStream->seek(position);
        IMEBRA_RETHROW("Detected a wrong format. Rewinding file");
	}

	// Update the charsets in the tags
	///////////////////////////////////////////////////////////
	pDestDataSet->updateTagsCharset();

	return pDestDataSet;

	IMEBRA_FUNCTION_END();
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
void codec::write(std::shared_ptr<streamWriter> pDestStream, std::shared_ptr<dataSet> pSourceDataSet)
{
	IMEBRA_FUNCTION_START(L"codec::write");

	// Update charsets tag
	///////////////////////////////////////////////////////////
	pSourceDataSet->updateCharsetTag();

	pDestStream->resetOutBitsBuffer();
	writeStream(pDestStream, pSourceDataSet);
	pDestStream->flushDataBuffer();

	IMEBRA_FUNCTION_END();
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
	IMEBRA_FUNCTION_START(L"channel::allocate");

	m_sizeX = sizeX;
	m_sizeY = sizeY;
	m_bufferSize = sizeX * sizeY;
	m_memory = std::shared_ptr<memory>(memoryPool::getMemoryPool()->getMemory(m_bufferSize * sizeof(std::int32_t) ));
	m_pBuffer = (std::int32_t*)(m_memory->data());

	::memset(m_pBuffer, 0, m_bufferSize * sizeof(std::int32_t));

	IMEBRA_FUNCTION_END();
}



} // namespace codecs

} // namespace imebra

} // namespace puntoexe

