/*
$fileHeader$
*/

/*! \file dataHandler.cpp
    \brief Implementation of the base class for the data handlers.

*/

#include "../include/imebra/exceptions.h"
#include "exceptionImpl.h"
#include "dataHandlerImpl.h"
#include "memoryImpl.h"

namespace imebra
{

namespace implementation
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
        std::uint32_t* pYear,
        std::uint32_t* pMonth,
        std::uint32_t* pDay,
        std::uint32_t* pHour,
        std::uint32_t* pMinutes,
        std::uint32_t* pSeconds,
        std::uint32_t* pNanoseconds,
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

std::uint32_t readingDataHandler::getAge(const size_t /* index */, ageUnit_t *pUnit) const
{
    *pUnit = ageUnit_t::years;
    return 0;
}


writingDataHandler::writingDataHandler(const std::shared_ptr<buffer> &pBuffer, const std::string &dataType, const uint8_t paddingByte):
    m_dataType(dataType), m_buffer(pBuffer), m_paddingByte(paddingByte)
{
}

writingDataHandler::~writingDataHandler()
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
        std::uint32_t /* year */,
        std::uint32_t /* month */,
        std::uint32_t /* day */,
        std::uint32_t /* hour */,
        std::uint32_t /*minutes */,
        std::uint32_t /*seconds */,
        std::uint32_t /*nanoseconds */,
		std::int32_t /*offsetHours */,
		std::int32_t /*offsetMinutes */)
{
    IMEBRA_FUNCTION_START();

    IMEBRA_THROW(DataHandlerDeniedConversionError, "Cannot convert VR "<< getDataType() << " to Date");

    IMEBRA_FUNCTION_END();
}

void writingDataHandler::setAge(const size_t /* index */, const std::uint32_t /* age */, const ageUnit_t /* unit */)
{
    IMEBRA_FUNCTION_START();

    IMEBRA_THROW(DataHandlerDeniedConversionError, "Cannot convert VR "<< getDataType() << " to Age");

    IMEBRA_FUNCTION_END();
}

} // namespace handlers

} // namespace implementation

} // namespace imebra
