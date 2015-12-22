/*
$fileHeader$
*/

/*! \file dataGroup.cpp
    \brief Implementation of the dataGroup class.

*/

#include "exceptionImpl.h"
#include "streamReaderImpl.h"
#include "streamWriterImpl.h"
#include "dataSetImpl.h"
#include "dataGroupImpl.h"
#include "dataHandlerNumericImpl.h"
#include "dicomDictImpl.h"
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
// imebraDataGroup
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
// Retrieve the requested tag
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::shared_ptr<data> dataGroup::getTag(std::uint16_t tagId, bool bCreate /* =false */)
{
	PUNTOEXE_FUNCTION_START(L"dataGroup::getTag");

	std::shared_ptr<data> pData=getData(tagId, 0);
	if(pData == 0 && bCreate)
	{
        std::shared_ptr<data> tempData(std::make_shared<data>());
		pData = tempData;
		setData(tagId, 0, pData);
	}

	return pData;

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Get a data handler (raw or normal) for the requested tag
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::shared_ptr<handlers::dataHandler> dataGroup::getDataHandler(std::uint16_t tagId, std::uint32_t bufferId, bool bWrite, const std::string& defaultType)
{
	PUNTOEXE_FUNCTION_START(L"dataGroup::getDataHandler");

	std::shared_ptr<data> tag=getTag(tagId, bWrite);

	if(tag == 0)
	{
		return std::shared_ptr<handlers::dataHandler>(0);
	}

	return tag->getDataHandler(bufferId, bWrite, defaultType);

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Get a stream reader that works on the specified tag
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::shared_ptr<streamReader> dataGroup::getStreamReader(std::uint16_t tagId, std::uint32_t bufferId)
{
	PUNTOEXE_FUNCTION_START(L"dataGroup::getStreamReader");

	std::shared_ptr<streamReader> returnStream;

	std::shared_ptr<data> tag=getTag(tagId, false);

	if(tag != 0)
	{
		returnStream = tag->getStreamReader(bufferId);
	}

	return returnStream;

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Get a stream writer that works on the specified tag
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::shared_ptr<streamWriter> dataGroup::getStreamWriter(std::uint16_t tagId, std::uint32_t bufferId, const std::string& dataType /* = "" */)
{
	PUNTOEXE_FUNCTION_START(L"dataGroup::getStream");

	std::shared_ptr<streamWriter> returnStream;

	std::shared_ptr<data> tag=getTag(tagId, true);

	if(tag != 0)
	{
		returnStream = tag->getStreamWriter(bufferId, dataType);
	}

	return returnStream;

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Return a raw data handler for the specified tag
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::shared_ptr<handlers::dataHandlerRaw> dataGroup::getDataHandlerRaw(std::uint16_t tagId, std::uint32_t bufferId, bool bWrite, const std::string& defaultType)
{
	PUNTOEXE_FUNCTION_START(L"dataGroup::getDataHandlerRaw");

	std::shared_ptr<data> tag=getTag(tagId, bWrite);

	if(tag == 0)
	{
		std::shared_ptr<handlers::dataHandlerRaw> emptyDataHandler;
		return emptyDataHandler;
	}

	return tag->getDataHandlerRaw(bufferId, bWrite, defaultType);

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Return the tag's data type
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::string dataGroup::getDataType(std::uint16_t tagId)
{
	PUNTOEXE_FUNCTION_START(L"dataGroup::getDataType");

	std::string bufferType;
	std::shared_ptr<data> tag = getTag(tagId, false);
	if(tag != 0)
	{
		bufferType = tag->getDataType();
	}

	return bufferType;

	PUNTOEXE_FUNCTION_END();
}

} // namespace imebra

} // namespace puntoexe
