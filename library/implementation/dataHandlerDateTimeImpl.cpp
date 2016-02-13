/*
$fileHeader$
*/

/*! \file dataHandlerDateTime.cpp
    \brief Implementation of the dataHandlerDateTime class.

*/

#include <sstream>
#include <iomanip>
#include <stdlib.h>

#include "exceptionImpl.h"
#include "dataHandlerDateTimeImpl.h"

namespace imebra
{

namespace implementation
{

namespace handlers
{

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
//
// dataHandlerDateTime
//
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

readingDataHandlerDateTime::readingDataHandlerDateTime(const memory& parseMemory): readingDataHandlerDateTimeBase(parseMemory, "DT")
{

}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
//
// Retrieve the date
//
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void readingDataHandlerDateTime::getDate(const size_t index,
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
    IMEBRA_FUNCTION_START();

    std::string dateTimeString = getString(index);

    parseDate(dateTimeString.substr(0, 8), pYear, pMonth, pDay);

    if(dateTimeString.size() <= 8)
    {
        parseTime("", pHour, pMinutes, pSeconds, pNanoseconds, pOffsetHours, pOffsetMinutes);
    }
    else
    {
        parseTime(dateTimeString.substr(8), pHour, pMinutes, pSeconds, pNanoseconds, pOffsetHours, pOffsetMinutes);
    }

	IMEBRA_FUNCTION_END();
}


writingDataHandlerDateTime::writingDataHandlerDateTime(const std::shared_ptr<buffer> &pBuffer):
    writingDataHandlerDateTimeBase(pBuffer, "DT", 0, 54)
{

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
void writingDataHandlerDateTime::setDate(const size_t index,
        std::uint32_t year,
        std::uint32_t month,
        std::uint32_t day,
        std::uint32_t hour,
        std::uint32_t minutes,
        std::uint32_t seconds,
        std::uint32_t nanoseconds,
		std::int32_t offsetHours,
		std::int32_t offsetMinutes)
{
    IMEBRA_FUNCTION_START();

    std::string dateTimeString;
	dateTimeString = buildDate(year, month, day);
	dateTimeString += buildTime(hour, minutes, seconds, nanoseconds, offsetHours, offsetMinutes);
    setString(index, dateTimeString);

	IMEBRA_FUNCTION_END();
}


} // namespace handlers

} // namespace implementation

} // namespace imebra
