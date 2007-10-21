/*
$fileHeader$
*/

/*! \file data.cpp
    \brief Implementation of the data class.

*/

#include "../../base/include/exception.h"
#include "../../base/include/streamReader.h"
#include "../../base/include/streamWriter.h"
#include "../include/data.h"
#include "../include/dataSet.h"
#include "../include/buffer.h"
#include "../include/dataHandler.h"
#include "../include/dataHandlerNumeric.h"
#include <iostream>

namespace puntoexe
{

namespace imebra
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
void data::setBuffer(imbxUint32 bufferId, ptr<buffer> newBuffer)
{
	PUNTOEXE_FUNCTION_START(L"data::setBuffer");

	lockObject lockAccess(this);

	// Assign the new buffer
	///////////////////////////////////////////////////////////
	m_buffers[bufferId] = newBuffer;

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Remove a buffer
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void data::deleteBuffer(imbxUint32 bufferId)
{
	PUNTOEXE_FUNCTION_START(L"data::deleteBuffer");

	// Lock the object
	///////////////////////////////////////////////////////////
	lockObject lockAccess(this);

	// Remove the buffer
	///////////////////////////////////////////////////////////
	tBuffersMap::iterator findBuffer = m_buffers.find(bufferId);
	if(findBuffer != m_buffers.end())
	{
		m_buffers.erase(findBuffer);
	}

	PUNTOEXE_FUNCTION_END();
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
std::string data::getDataType()
{
	PUNTOEXE_FUNCTION_START(L"data::getDataType");

	// Lock the object
	///////////////////////////////////////////////////////////
	lockObject lockAccess(this);

	tBuffersMap::iterator findBuffer = m_buffers.find(0);
	if(findBuffer != m_buffers.end())
	{
		return findBuffer->second->getDataType();
	}
	
	return "";

	PUNTOEXE_FUNCTION_END();
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
bool data::bufferExists(imbxUint32 bufferId)
{
	PUNTOEXE_FUNCTION_START(L"data::bufferExists");

	// Lock the object
	///////////////////////////////////////////////////////////
	lockObject lockAccess(this);

	// Retrieve the buffer
	///////////////////////////////////////////////////////////
	tBuffersMap::iterator findBuffer = m_buffers.find(bufferId);
	return (findBuffer != m_buffers.end());

	PUNTOEXE_FUNCTION_END();
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
imbxUint32 data::getBufferSize(imbxUint32 bufferId)
{
	PUNTOEXE_FUNCTION_START(L"data::getBufferSize");

	// Lock the object
	///////////////////////////////////////////////////////////
	lockObject lockAccess(this);

	// Retrieve the buffer
	///////////////////////////////////////////////////////////
	tBuffersMap::iterator findBuffer = m_buffers.find(bufferId);
	if(findBuffer == m_buffers.end())
	{
		return 0;
	}

	// Retrieve the buffer's size
	///////////////////////////////////////////////////////////
	return findBuffer->second->getBufferSizeBytes();

	PUNTOEXE_FUNCTION_END();
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
ptr<handlers::dataHandler> data::getDataHandler(imbxUint32 bufferId, bool bWrite, std::string defaultType)
{
	PUNTOEXE_FUNCTION_START(L"data::getDataHandler");

	// Lock the object
	///////////////////////////////////////////////////////////
	lockObject lockAccess(this);

	// Retrieve the buffer
	///////////////////////////////////////////////////////////
	ptr<buffer> pTempBuffer;
	tBuffersMap::iterator findBuffer = m_buffers.find(bufferId);
	if(findBuffer != m_buffers.end())
	{
		pTempBuffer = findBuffer->second;
	}

	// If a buffer already exists, then use the already defined
	//  datatype
	///////////////////////////////////////////////////////////
	if( !m_buffers.empty() )
	{
		defaultType = (m_buffers.begin())->second->getDataType();
	}

	// If the buffer doesn't exist, then create a new one
	///////////////////////////////////////////////////////////
	if(pTempBuffer == 0 && bWrite)
	{
		ptr<buffer> ptrBuffer(new buffer(m_externalLock, defaultType));
		pTempBuffer=ptrBuffer;
		pTempBuffer->setCharsetsList(&m_charsets);
		m_buffers[bufferId]=pTempBuffer;
	}

	// Retrieve the data handler
	///////////////////////////////////////////////////////////
	if(pTempBuffer == 0)
	{
		ptr<handlers::dataHandler> emptyDataHandler;
		return emptyDataHandler;
	}
	
	return pTempBuffer->getDataHandler(bWrite);

	PUNTOEXE_FUNCTION_END();
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
ptr<handlers::dataHandlerRaw> data::getDataHandlerRaw(imbxUint32 bufferId, bool bWrite, std::string defaultType)
{
	PUNTOEXE_FUNCTION_START(L"data::getDataHandlerRaw");

	// Lock the object
	///////////////////////////////////////////////////////////
	lockObject lockAccess(this);

	// Retrieve the buffer
	///////////////////////////////////////////////////////////
	ptr<buffer> pTempBuffer;
	tBuffersMap::iterator findBuffer = m_buffers.find(bufferId);
	if(findBuffer != m_buffers.end() )
	{
		pTempBuffer = findBuffer->second;
	}

	// If a buffer already exists, then use the already defined
	//  datatype
	///////////////////////////////////////////////////////////
	if( !m_buffers.empty() )
	{
		defaultType = (m_buffers.begin())->second->getDataType();
	}

	// If the buffer doesn't exist, then create a new one
	///////////////////////////////////////////////////////////
	if( pTempBuffer == 0 && bWrite )
	{
		ptr<buffer> ptrBuffer(new buffer(m_externalLock, defaultType));
		pTempBuffer=ptrBuffer;
		pTempBuffer->setCharsetsList(&m_charsets);
		m_buffers[bufferId]=pTempBuffer;
	}

	// Retrieve the data handler
	///////////////////////////////////////////////////////////
	if( pTempBuffer == 0 )
	{
		ptr<handlers::dataHandlerRaw> emptyDataHandler;
		return emptyDataHandler;
	}

	return pTempBuffer->getDataHandlerRaw(bWrite);

	PUNTOEXE_FUNCTION_END();
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
ptr<streamReader> data::getStreamReader(imbxUint32 bufferId)
{
	PUNTOEXE_FUNCTION_START(L"data::getStreamReader");

	// Lock the object
	///////////////////////////////////////////////////////////
	lockObject lockAccess(this);

	// Retrieve the buffer
	///////////////////////////////////////////////////////////
	ptr<buffer> pTempBuffer;
	tBuffersMap::iterator findBuffer = m_buffers.find(bufferId);
	if(findBuffer != m_buffers.end())
	{
		return findBuffer->second->getStreamReader();
	}

	ptr<streamReader> emptyStream;
	return emptyStream;

	PUNTOEXE_FUNCTION_END();
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
ptr<streamWriter> data::getStreamWriter(imbxUint32 bufferId, std::string dataType /* = "" */)
{
	PUNTOEXE_FUNCTION_START(L"data::getStream");

	// Lock the object
	///////////////////////////////////////////////////////////
	lockObject lockAccess(this);

	// Retrieve the buffer
	///////////////////////////////////////////////////////////
	ptr<buffer> pTempBuffer;
	tBuffersMap::iterator findBuffer = m_buffers.find(bufferId);
	if(findBuffer != m_buffers.end())
	{
		pTempBuffer = findBuffer->second;
	}

	// If a buffer already exists, then use the already defined
	//  datatype
	///////////////////////////////////////////////////////////
	if( !m_buffers.empty() )
	{
		dataType = (m_buffers.begin())->second->getDataType();
	}

	// If the buffer doesn't exist, then create a new one
	///////////////////////////////////////////////////////////
	if(pTempBuffer == 0)
	{
		ptr<buffer> ptrBuffer(new buffer(m_externalLock, dataType));
		pTempBuffer=ptrBuffer;
		m_buffers[bufferId]=pTempBuffer;
	}

	// Retrieve the data handler
	///////////////////////////////////////////////////////////
	if(pTempBuffer == 0)
	{
		ptr<streamWriter> emptyStream;
		return emptyStream;
	}
	
	return pTempBuffer->getStreamWriter();

	PUNTOEXE_FUNCTION_END();
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
ptr<dataSet> data::getDataSet(imbxUint32 dataSetId)
{
	PUNTOEXE_FUNCTION_START(L"data::getDataSet");

	// Lock the object
	///////////////////////////////////////////////////////////
	lockObject lockAccess(this);

	// Reset the return pointer
	///////////////////////////////////////////////////////////
	ptr<dataSet> pDataSet;

	// Retrieve the buffer
	///////////////////////////////////////////////////////////
	tEmbeddedDatasetsMap::iterator findEmbeddedDataSet = m_embeddedDataSets.find(dataSetId);
	if(findEmbeddedDataSet != m_embeddedDataSets.end())
	{
		pDataSet = findEmbeddedDataSet->second;
	}

	// Return the data set
	///////////////////////////////////////////////////////////
	return pDataSet;

	PUNTOEXE_FUNCTION_END();
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
void data::setDataSet(imbxUint32 dataSetId, ptr<dataSet> pDataSet)
{
	PUNTOEXE_FUNCTION_START(L"data::setDataSet");

	// Lock the object
	///////////////////////////////////////////////////////////
	lockObject lockAccess(this);

	m_embeddedDataSets[dataSetId]=pDataSet;

	PUNTOEXE_FUNCTION_END();
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
void data::setCharsetsList(tCharsetsList* pCharsetsList)
{
	PUNTOEXE_FUNCTION_START(L"data::setCharsetsList");

	lockObject lockAccess(this);

	m_charsets.clear();
	updateCharsets(pCharsetsList, &m_charsets);

	for(tEmbeddedDatasetsMap::iterator scanEmbeddedDataSets = m_embeddedDataSets.begin(); scanEmbeddedDataSets != m_embeddedDataSets.end(); ++scanEmbeddedDataSets)
	{
		scanEmbeddedDataSets->second->setCharsetsList(pCharsetsList);
	}

	for(tBuffersMap::iterator scanBuffers = m_buffers.begin(); scanBuffers != m_buffers.end(); ++scanBuffers)
	{
		scanBuffers->second->setCharsetsList(pCharsetsList);
	}

	PUNTOEXE_FUNCTION_END();
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
void data::getCharsetsList(tCharsetsList* pCharsetsList)
{
	PUNTOEXE_FUNCTION_START(L"data::getCharsetsList");

	lockObject lockAccess(this);
	
	m_charsets.clear();

	for(tEmbeddedDatasetsMap::iterator scanEmbeddedDataSets = m_embeddedDataSets.begin(); scanEmbeddedDataSets != m_embeddedDataSets.end(); ++scanEmbeddedDataSets)
	{
		tCharsetsList charsets;
		scanEmbeddedDataSets->second->getCharsetsList(&charsets);
		updateCharsets(&charsets, &m_charsets);
	}

	for(tBuffersMap::iterator scanBuffers = m_buffers.begin(); scanBuffers != m_buffers.end(); ++scanBuffers)
	{
		tCharsetsList charsets;
		scanBuffers->second->getCharsetsList(&charsets);
		updateCharsets(&charsets, &m_charsets);
	}

	copyCharsets(&m_charsets, pCharsetsList);

	PUNTOEXE_FUNCTION_END();
}


} // namespace imebra

} // namespace puntoexe
