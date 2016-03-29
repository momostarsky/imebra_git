/*
$fileHeader$
*/

/*! \file data.cpp
    \brief Implementation of the data class.

*/

#include "exceptionImpl.h"
#include "streamReaderImpl.h"
#include "streamWriterImpl.h"
#include "dataImpl.h"
#include "dataSetImpl.h"
#include "dicomDictImpl.h"
#include "bufferImpl.h"
#include "dataHandlerImpl.h"
#include "dataHandlerNumericImpl.h"
#include "../include/imebra/exceptions.h"
#include <iostream>

namespace imebra
{

namespace implementation
{

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
//
// data
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
data::data(const charsetsList::tCharsetsList &defaultCharsets):
    m_charsetsList(defaultCharsets)
{
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Set a buffer
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void data::setBuffer(size_t bufferId, const std::shared_ptr<buffer>& newBuffer)
{
    IMEBRA_FUNCTION_START();

    std::lock_guard<std::mutex> lock(m_mutex);

    // Assign the new buffer
    ///////////////////////////////////////////////////////////
    m_buffers[bufferId] = newBuffer;

    IMEBRA_FUNCTION_END();
}



///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Return the buffer's data type
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
tagVR_t data::getDataType(size_t bufferId) const
{
    IMEBRA_FUNCTION_START();

    std::shared_ptr<buffer> pTempBuffer;

    {
        std::lock_guard<std::mutex> lock(m_mutex);
        tBuffersMap::const_iterator findBuffer = m_buffers.find(bufferId);
        if(findBuffer == m_buffers.end())
        {
            IMEBRA_THROW(MissingBufferError, "The buffer with ID " << bufferId << " is missing");
        }
        pTempBuffer = findBuffer->second;
    }

    return pTempBuffer->getDataType();
	


	IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Return the number of buffers in the tag
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
size_t data::getBuffersCount() const
{
    IMEBRA_FUNCTION_START();

    std::lock_guard<std::mutex> lock(m_mutex);

	// Returns the number of buffers
	///////////////////////////////////////////////////////////
	return m_buffers.size();

	IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Return true if the specified buffer exists
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
bool data::bufferExists(size_t bufferId) const
{
    IMEBRA_FUNCTION_START();

    std::lock_guard<std::mutex> lock(m_mutex);

	// Retrieve the buffer
	///////////////////////////////////////////////////////////
    tBuffersMap::const_iterator findBuffer = m_buffers.find(bufferId);
	return (findBuffer != m_buffers.end());

	IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Return the size of a buffer
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
size_t data::getBufferSize(size_t bufferId) const
{
    IMEBRA_FUNCTION_START();

    std::shared_ptr<buffer> pTempBuffer;

    {
        std::lock_guard<std::mutex> lock(m_mutex);

        // Retrieve the buffer
        ///////////////////////////////////////////////////////////
        tBuffersMap::const_iterator findBuffer = m_buffers.find(bufferId);
        if(findBuffer == m_buffers.end())
        {
            IMEBRA_THROW(MissingBufferError, "The buffer with ID " << bufferId << " is missing");
        }
        pTempBuffer = findBuffer->second;
    }

	// Retrieve the buffer's size
	///////////////////////////////////////////////////////////
    return pTempBuffer->getBufferSizeBytes();

	IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Get an handler (normal or raw) for the buffer
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::shared_ptr<handlers::readingDataHandler> data::getReadingDataHandler(size_t bufferId) const
{
    IMEBRA_FUNCTION_START();

    std::shared_ptr<buffer> pTempBuffer;

    {
        std::lock_guard<std::mutex> lock(m_mutex);

        // Retrieve the buffer
        ///////////////////////////////////////////////////////////
        tBuffersMap::const_iterator findBuffer = m_buffers.find(bufferId);
        if(findBuffer == m_buffers.end())
        {
            IMEBRA_THROW(MissingBufferError, "The buffer with ID " << bufferId << " is missing");
        }
        pTempBuffer = findBuffer->second;
    }

    return pTempBuffer->getReadingDataHandler();

	IMEBRA_FUNCTION_END();
}


std::shared_ptr<handlers::writingDataHandler> data::getWritingDataHandler(size_t bufferId, tagVR_t tagVR)
{
    IMEBRA_FUNCTION_START();

    std::shared_ptr<buffer> pTempBuffer;
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        // Retrieve the buffer
        ///////////////////////////////////////////////////////////
        tBuffersMap::iterator findBuffer = m_buffers.find(bufferId);
        if(findBuffer != m_buffers.end())
        {
            pTempBuffer = findBuffer->second;
        }

        // If the buffer doesn't exist, then create a new one
        ///////////////////////////////////////////////////////////
        if(pTempBuffer == 0)
        {
            // If a buffer already exists, then check the already defined
            //  datatype
            /////////////////////////////////////////////////////////////
            if(
                    !m_buffers.empty() &&
                    tagVR != m_buffers.begin()->second->getDataType())
            {
                throw;
            }
            pTempBuffer = std::make_shared<buffer>(tagVR);

            pTempBuffer->setCharsetsList(m_charsetsList);
            m_buffers[bufferId]=pTempBuffer;
        }
    }

    return pTempBuffer->getWritingDataHandler();

    IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Get a raw data handler
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::shared_ptr<handlers::readingDataHandlerRaw> data::getReadingDataHandlerRaw(size_t bufferId) const
{
    IMEBRA_FUNCTION_START();

	std::shared_ptr<buffer> pTempBuffer;
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        tBuffersMap::const_iterator findBuffer = m_buffers.find(bufferId);
        if(findBuffer == m_buffers.end() )
        {
            IMEBRA_THROW(MissingBufferError, "The buffer with ID " << bufferId << " is missing");
        }
        pTempBuffer = findBuffer->second;
    }

    return pTempBuffer->getReadingDataHandlerRaw();

	IMEBRA_FUNCTION_END();
}


std::shared_ptr<handlers::writingDataHandlerRaw> data::getWritingDataHandlerRaw(size_t bufferId, tagVR_t tagVR)
{
    IMEBRA_FUNCTION_START();

    std::shared_ptr<buffer> pTempBuffer;

    {
        std::lock_guard<std::mutex> lock(m_mutex);

        tBuffersMap::iterator findBuffer = m_buffers.find(bufferId);
        if(findBuffer != m_buffers.end() )
        {
            pTempBuffer = findBuffer->second;
        }

        // If the buffer doesn't exist, then create a new one
        ///////////////////////////////////////////////////////////
        if(pTempBuffer == 0)
        {
            // If a buffer already exists, then use the already defined
            //  datatype
            ///////////////////////////////////////////////////////////
            if( !m_buffers.empty() )
            {
                pTempBuffer = std::make_shared<buffer>(m_buffers.begin()->second->getDataType());
            }
            else
            {
                pTempBuffer = std::make_shared<buffer>(tagVR);
            }

            pTempBuffer->setCharsetsList(m_charsetsList);
            m_buffers[bufferId]=pTempBuffer;
        }
    }

    return pTempBuffer->getWritingDataHandlerRaw();

    IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Get a stream reader that works on the buffer's data
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::shared_ptr<streamReader> data::getStreamReader(size_t bufferId)
{
    IMEBRA_FUNCTION_START();

	std::shared_ptr<buffer> pTempBuffer;

    {
        std::lock_guard<std::mutex> lock(m_mutex);

        tBuffersMap::iterator findBuffer = m_buffers.find(bufferId);
        if(findBuffer == m_buffers.end())
        {
            IMEBRA_THROW(MissingBufferError, "The buffer with ID " << bufferId << " is missing");
        }
        pTempBuffer = findBuffer->second;
    }

    return pTempBuffer->getStreamReader();

	IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Get a stream writer that works on the buffer's data
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::shared_ptr<streamWriter> data::getStreamWriter(size_t bufferId, tagVR_t tagVR)
{
    IMEBRA_FUNCTION_START();

	std::shared_ptr<buffer> pTempBuffer;

    {
        std::lock_guard<std::mutex> lock(m_mutex);

        tBuffersMap::iterator findBuffer = m_buffers.find(bufferId);
        if(findBuffer != m_buffers.end())
        {
            pTempBuffer = findBuffer->second;
        }

        // If the buffer doesn't exist, then create a new one
        ///////////////////////////////////////////////////////////
        if(pTempBuffer == 0)
        {
            // If a buffer already exists, then use the already defined
            //  datatype
            ///////////////////////////////////////////////////////////
            if( !m_buffers.empty() )
            {
                pTempBuffer = std::make_shared<buffer>(m_buffers.begin()->second->getDataType());
            }
            else
            {
                pTempBuffer = std::make_shared<buffer>(tagVR);
            }

            m_buffers[bufferId] = pTempBuffer;
        }
    }

	return pTempBuffer->getStreamWriter();

	IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Retrieve an embedded data set.
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::shared_ptr<dataSet> data::getSequenceItem(size_t dataSetId) const
{
    IMEBRA_FUNCTION_START();

    std::lock_guard<std::mutex> lock(m_mutex);

    if(m_embeddedDataSets.size() <= dataSetId)
	{
        IMEBRA_THROW(MissingItemError, "The requested sequence item does not exist");
	}

	return m_embeddedDataSets[dataSetId];

	IMEBRA_FUNCTION_END();
}

bool data::dataSetExists(size_t dataSetId) const
{
    IMEBRA_FUNCTION_START();

    std::lock_guard<std::mutex> lock(m_mutex);

    return m_embeddedDataSets.size() > dataSetId;

    IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Set a data set
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void data::setDataSet(size_t dataSetId, std::shared_ptr<dataSet> pDataSet)
{
    IMEBRA_FUNCTION_START();

    std::lock_guard<std::mutex> lock(m_mutex);

	if(dataSetId >= m_embeddedDataSets.size())
	{
		m_embeddedDataSets.resize(dataSetId + 1);
	}
	m_embeddedDataSets[dataSetId] = pDataSet;

	IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Append a data set
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void data::appendDataSet(std::shared_ptr<dataSet> pDataSet)
{
    IMEBRA_FUNCTION_START();

    std::lock_guard<std::mutex> lock(m_mutex);

    pDataSet->setCharsetsList(m_charsetsList);
    m_embeddedDataSets.push_back(pDataSet);

	IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Define the charset to use in the buffers and embedded
//  datasets
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void data::setCharsetsList(const charsetsList::tCharsetsList& charsetsList)
{
    IMEBRA_FUNCTION_START();

    std::lock_guard<std::mutex> lock(m_mutex);

    m_charsetsList = charsetsList;

	for(tEmbeddedDatasetsMap::iterator scanEmbeddedDataSets = m_embeddedDataSets.begin(); scanEmbeddedDataSets != m_embeddedDataSets.end(); ++scanEmbeddedDataSets)
	{
        (*scanEmbeddedDataSets)->setCharsetsList(charsetsList);
	}

	for(tBuffersMap::iterator scanBuffers = m_buffers.begin(); scanBuffers != m_buffers.end(); ++scanBuffers)
	{
        scanBuffers->second->setCharsetsList(charsetsList);
	}

	IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Get the charset used by the buffers and the embedded
//  datasets
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void data::getCharsetsList(charsetsList::tCharsetsList* pCharsetsList) const
{
    IMEBRA_FUNCTION_START();

    std::lock_guard<std::mutex> lock(m_mutex);

    for(tEmbeddedDatasetsMap::const_iterator scanEmbeddedDataSets = m_embeddedDataSets.begin(); scanEmbeddedDataSets != m_embeddedDataSets.end(); ++scanEmbeddedDataSets)
	{
		charsetsList::tCharsetsList charsets;
		(*scanEmbeddedDataSets)->getCharsetsList(&charsets);
        charsetsList::updateCharsets(&charsets, pCharsetsList);
	}

    for(tBuffersMap::const_iterator scanBuffers = m_buffers.begin(); scanBuffers != m_buffers.end(); ++scanBuffers)
	{
		charsetsList::tCharsetsList charsets;
		scanBuffers->second->getCharsetsList(&charsets);
        charsetsList::updateCharsets(&charsets, pCharsetsList);
	}

	IMEBRA_FUNCTION_END();
}


} // namespace implementation

} // namespace imebra
