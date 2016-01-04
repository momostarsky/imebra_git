/*
$fileHeader$
*/

/*! \file dataHandler.cpp
    \brief Implementation of the base class for the data handlers.

*/

#include "exceptionImpl.h"
#include "dataHandlerImpl.h"
#include "memoryImpl.h"

namespace puntoexe
{

namespace imebra
{

namespace handlers
{


readingDataHandler::readingDataHandler(const std::string& dataType): m_dataType(dataType)
{
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Retrieve the data 's type
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::string readingDataHandler::getDataType() const
{
    return m_dataType;
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Retrieve the date
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void readingDataHandler::getDate(const size_t /* index */,
		std::int32_t* pYear, 
		std::int32_t* pMonth, 
		std::int32_t* pDay, 
		std::int32_t* pHour, 
		std::int32_t* pMinutes,
		std::int32_t* pSeconds,
		std::int32_t* pNanoseconds,
		std::int32_t* pOffsetHours,
		std::int32_t* pOffsetMinutes) const
{
	*pYear = 0;
	*pMonth = 0;
	*pDay = 0;
	*pHour = 0;
	*pMinutes = 0;
	*pSeconds = 0;
	*pNanoseconds = 0;
	*pOffsetHours = 0;
	*pOffsetMinutes = 0;
}

std::uint32_t readingDataHandler::getAge(const size_t /* index */, ::imebra::ageUnit_t *pUnit) const
{
    *pUnit = ::imebra::ageUnit_t::years;
    return 0;
}


writingDataHandler::writingDataHandler(const std::shared_ptr<buffer> &pBuffer, const std::string &dataType, const uint8_t paddingByte):
    m_dataType(dataType), m_buffer(pBuffer), m_paddingByte(paddingByte)
{

}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Retrieve the data 's type
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::string writingDataHandler::getDataType() const
{
    return m_dataType;
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Set the date
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void writingDataHandler::setDate(const size_t /* index */,
		std::int32_t /* year */, 
		std::int32_t /* month */, 
		std::int32_t /* day */, 
		std::int32_t /* hour */, 
		std::int32_t /*minutes */,
		std::int32_t /*seconds */,
		std::int32_t /*nanoseconds */,
		std::int32_t /*offsetHours */,
		std::int32_t /*offsetMinutes */)
{
    throw;
}

void writingDataHandler::setAge(const size_t /* index */, const std::uint32_t /* age */, const ::imebra::ageUnit_t /* unit */)
{
    throw;
}

} // namespace handlers

} // namespace imebra

} // namespace puntoexe
