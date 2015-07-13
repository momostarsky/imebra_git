/*
$fileHeader$
*/

/*! \file dataGroup.cpp
    \brief Implementation of the dataGroup class.

*/

#include "../../base/include/exception.h"
#include "../../base/include/streamReader.h"
#include "../../base/include/streamWriter.h"
#include "../include/dataSet.h"
#include "../include/dataGroup.h"
#include "../include/dataHandlerNumeric.h"
#include "../include/dicomDict.h"
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
ptr<data> dataGroup::getTag(std::uint16_t tagId, bool bCreate /* =false */)
{
	PUNTOEXE_FUNCTION_START(L"dataGroup::getTag");

	ptr<data> pData=getData(tagId, 0);
	if(pData == 0 && bCreate)
	{
		ptr<data> tempData(new data(this));
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
ptr<handlers::dataHandler> dataGroup::getDataHandler(std::uint16_t tagId, std::uint32_t bufferId, bool bWrite, std::string defaultType)
{
	PUNTOEXE_FUNCTION_START(L"dataGroup::getDataHandler");

	lockObject lockAccess(this);

	ptr<data> tag=getTag(tagId, bWrite);

	if(tag == 0)
	{
		return ptr<handlers::dataHandler>(0);
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
ptr<streamReader> dataGroup::getStreamReader(std::uint16_t tagId, std::uint32_t bufferId)
{
	PUNTOEXE_FUNCTION_START(L"dataGroup::getStreamReader");

	lockObject lockAccess(this);

	ptr<streamReader> returnStream;

	ptr<data> tag=getTag(tagId, false);

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
ptr<streamWriter> dataGroup::getStreamWriter(std::uint16_t tagId, std::uint32_t bufferId, std::string dataType /* = "" */)
{
	PUNTOEXE_FUNCTION_START(L"dataGroup::getStream");

	lockObject lockAccess(this);

	ptr<streamWriter> returnStream;

	ptr<data> tag=getTag(tagId, true);

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
ptr<handlers::dataHandlerRaw> dataGroup::getDataHandlerRaw(std::uint16_t tagId, std::uint32_t bufferId, bool bWrite, std::string defaultType)
{
	PUNTOEXE_FUNCTION_START(L"dataGroup::getDataHandlerRaw");

	lockObject lockAccess(this);

	ptr<data> tag=getTag(tagId, bWrite);

	if(tag == 0)
	{
		ptr<handlers::dataHandlerRaw> emptyDataHandler;
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
	ptr<data> tag = getTag(tagId, false);
	if(tag != 0)
	{
		bufferType = tag->getDataType();
	}

	return bufferType;

	PUNTOEXE_FUNCTION_END();
}

} // namespace imebra

} // namespace puntoexe
