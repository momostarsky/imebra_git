/*
$fileHeader$
*/

/*! \file dataHandlerTime.cpp
    \brief Implementation of the class dataHandlerTime.

*/

#include <sstream>
#include <iomanip>
#include <stdlib.h>

#include "exceptionImpl.h"
#include "dataHandlerTimeImpl.h"

namespace puntoexe
{

namespace imebra
{

namespace handlers
{

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
//
// dataHandlerTime
//
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

readingDataHandlerTime::readingDataHandlerTime(const memory& parseMemory): readingDataHandlerDateTimeBase(parseMemory, "TM")
{
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Get the date/time
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void readingDataHandlerTime::getDate(const size_t index,
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
    IMEBRA_FUNCTION_START(L"dataHandlerTime::getDate");

    *pYear = 0;
    *pMonth = 0;
    *pDay = 0;
    *pHour = 0;
    *pMinutes = 0;
    *pSeconds = 0;
    *pNanoseconds = 0;
    *pOffsetHours = 0;
    *pOffsetMinutes = 0;

    parseTime(getString(index), pHour, pMinutes, pSeconds, pNanoseconds, pOffsetHours, pOffsetMinutes);

    IMEBRA_FUNCTION_END();

}

writingDataHandlerTime::writingDataHandlerTime(const std::shared_ptr<buffer> &pBuffer):
    writingDataHandlerDateTimeBase(pBuffer, "TM", 0, 16)
{

}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Set the date/time
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void writingDataHandlerTime::setDate(const size_t index,
         std::uint32_t /* year */,
         std::uint32_t /* month */,
         std::uint32_t /* day */,
         std::uint32_t hour,
         std::uint32_t minutes,
         std::uint32_t seconds,
         std::uint32_t nanoseconds,
		 std::int32_t offsetHours,
		 std::int32_t offsetMinutes)
{
	IMEBRA_FUNCTION_START(L"dataHandlerTime::setDate");

    std::string timeString = buildTime(hour, minutes, seconds, nanoseconds, offsetHours, offsetMinutes);
	timeString.resize(13);
    setString(index, timeString);

	IMEBRA_FUNCTION_END();
}


} // namespace handlers

} // namespace imebra

} // namespace puntoexe
