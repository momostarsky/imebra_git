/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement 
 that your application must also be GPL), you may purchase a commercial 
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

/*! \file data.cpp
    \brief Implementation of the data class.

*/

#include "exceptionImpl.h"
#include "streamReaderImpl.h"
#include "streamWriterImpl.h"
#include "fileStreamImpl.h"
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
data::data(tagVR_t tagVR, const charsetsList::tCharsetsList &defaultCharsets):
    m_charsetsList(defaultCharsets), m_tagVR(tagVR)
{
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Destructor
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
data::~data()
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
    if(bufferId >= m_buffers.size())
    {
        m_buffers.resize(bufferId + 1);
    }
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
tagVR_t data::getDataType() const
{
    return m_tagVR;
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
    std::lock_guard<std::mutex> lock(m_mutex);

    return bufferId < m_buffers.size() && m_buffers.at(bufferId) != nullptr;
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

    return getBuffer(bufferId)->getBufferSizeBytes();

	IMEBRA_FUNCTION_END();
}


std::shared_ptr<buffer> data::getBuffer(size_t bufferId) const
{
    IMEBRA_FUNCTION_START();

    std::lock_guard<std::mutex> lock(m_mutex);

    // Retrieve the buffer
    ///////////////////////////////////////////////////////////
    if(bufferId >= m_buffers.size() || m_buffers.at(bufferId) == nullptr)
    {
        IMEBRA_THROW(MissingBufferError, "The buffer with ID " << bufferId << " is missing");
    }
    return m_buffers.at(bufferId);

    IMEBRA_FUNCTION_END();

}


std::shared_ptr<buffer> data::getBufferCreate(size_t bufferId)
{
    IMEBRA_FUNCTION_START();

    std::lock_guard<std::mutex> lock(m_mutex);

    // Retrieve the buffer
    ///////////////////////////////////////////////////////////
    if(bufferId < m_buffers.size() && m_buffers.at(bufferId) != nullptr)
    {
        return m_buffers.at(bufferId);
    }

    std::shared_ptr<buffer> pNewBuffer(std::make_shared<buffer>());
    pNewBuffer->setCharsetsList(m_charsetsList);
    if(bufferId >= m_buffers.size())
    {
        m_buffers.resize(bufferId + 1);
    }
    m_buffers[bufferId] = pNewBuffer;

    return pNewBuffer;

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

    return getBuffer(bufferId)->getReadingDataHandler(m_tagVR);

	IMEBRA_FUNCTION_END();
}


std::shared_ptr<handlers::writingDataHandler> data::getWritingDataHandler(size_t bufferId)
{
    IMEBRA_FUNCTION_START();

    return getBufferCreate(bufferId)->getWritingDataHandler(m_tagVR);

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

    return getBuffer(bufferId)->getReadingDataHandlerRaw(m_tagVR);

	IMEBRA_FUNCTION_END();
}


std::shared_ptr<handlers::writingDataHandlerRaw> data::getWritingDataHandlerRaw(size_t bufferId)
{
    IMEBRA_FUNCTION_START();

    return getBufferCreate(bufferId)->getWritingDataHandlerRaw(m_tagVR);

    IMEBRA_FUNCTION_END();
}


std::shared_ptr<handlers::readingDataHandlerNumericBase> data::getReadingDataHandlerNumeric(size_t bufferId) const
{
    IMEBRA_FUNCTION_START();

    return getBuffer(bufferId)->getReadingDataHandlerNumeric(m_tagVR);

    IMEBRA_FUNCTION_END();
}


std::shared_ptr<handlers::writingDataHandlerNumericBase> data::getWritingDataHandlerNumeric(size_t bufferId)
{
    IMEBRA_FUNCTION_START();

    return getBufferCreate(bufferId)->getWritingDataHandlerNumeric(m_tagVR);

    IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Check if the buffer has an external stream
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
bool data::hasExternalStream(size_t bufferId) const
{
    return getBuffer(bufferId)->hasExternalStream();
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

    return getBuffer(bufferId)->getStreamReader();

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
std::shared_ptr<streamWriter> data::getStreamWriter(size_t bufferId)
{
    IMEBRA_FUNCTION_START();

    return getBufferCreate(bufferId)->getStreamWriter(m_tagVR);

	IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Set a stream content as tag's content
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void data::setExternalStream(size_t bufferId, std::shared_ptr<fileStreamInput> pExternalStream)
{
    IMEBRA_FUNCTION_START();

    setBuffer(bufferId, std::make_shared<buffer>(pExternalStream,
                                                 0,
                                                 pExternalStream->getSize(),
                                                 dicomDictionary::getDicomDictionary()->getWordSize(getDataType()),
                                                 streamController::getPlatformEndian()));

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
// Append a data set
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::shared_ptr<dataSet> data::appendSequenceItem()
{
    IMEBRA_FUNCTION_START();

    std::lock_guard<std::mutex> lock(m_mutex);

    std::shared_ptr<dataSet> pDataSet(std::make_shared<dataSet>());
    pDataSet->setCharsetsList(m_charsetsList);
    m_embeddedDataSets.push_back(pDataSet);

    return pDataSet;

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

    for(tEmbeddedDatasetsVector::iterator scanEmbeddedDataSets = m_embeddedDataSets.begin(); scanEmbeddedDataSets != m_embeddedDataSets.end(); ++scanEmbeddedDataSets)
	{
        (*scanEmbeddedDataSets)->setChildrenCharsetsList(charsetsList);
	}

    for(const std::shared_ptr<buffer>& pBuffer: m_buffers)
	{
        pBuffer->setCharsetsList(charsetsList);
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

    for(tEmbeddedDatasetsVector::const_iterator scanEmbeddedDataSets = m_embeddedDataSets.begin(); scanEmbeddedDataSets != m_embeddedDataSets.end(); ++scanEmbeddedDataSets)
	{
		charsetsList::tCharsetsList charsets;
		(*scanEmbeddedDataSets)->getCharsetsList(&charsets);
        charsetsList::updateCharsets(&charsets, pCharsetsList);
	}

    for(const std::shared_ptr<buffer>& pBuffer: m_buffers)
	{
		charsetsList::tCharsetsList charsets;
        pBuffer->getCharsetsList(&charsets);
        charsetsList::updateCharsets(&charsets, pCharsetsList);
	}

	IMEBRA_FUNCTION_END();
}


} // namespace implementation

} // namespace imebra
