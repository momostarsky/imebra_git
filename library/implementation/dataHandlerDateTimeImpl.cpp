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
// dataHandlerDateTime
//
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

dataHandlerDateTime::dataHandlerDateTime(): dataHandlerDateTimeBase("DT")
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
void dataHandlerDateTime::getDate(const std::uint32_t index,
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
	PUNTOEXE_FUNCTION_START(L"dataHandlerDateTime::getDate");

	std::wstring dateTimeString=dataHandlerDateTimeBase::getUnicodeString(index);

    parseDate(dateTimeString, pYear, pMonth, pDay);

    if(dateTimeString.size() <= 8)
    {
        parseTime(L"", pHour, pMinutes, pSeconds, pNanoseconds, pOffsetHours, pOffsetMinutes);
    }
    else
    {
        parseTime(dateTimeString.substr(8), pHour, pMinutes, pSeconds, pNanoseconds, pOffsetHours, pOffsetMinutes);
    }

	PUNTOEXE_FUNCTION_END();
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
void dataHandlerDateTime::setDate(const std::uint32_t index,
		std::int32_t year, 
		std::int32_t month, 
		std::int32_t day, 
		std::int32_t hour, 
		std::int32_t minutes,
		std::int32_t seconds,
		std::int32_t nanoseconds,
		std::int32_t offsetHours,
		std::int32_t offsetMinutes)
{
	PUNTOEXE_FUNCTION_START(L"dataHandlerDateTime::setDate");

	std::wstring dateTimeString;
	dateTimeString = buildDate(year, month, day);
	dateTimeString += buildTime(hour, minutes, seconds, nanoseconds, offsetHours, offsetMinutes);
	dataHandlerDateTimeBase::setUnicodeString(index, dateTimeString);

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Get a string representation of the date
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::wstring dataHandlerDateTime::getUnicodeString(const std::uint32_t index) const
{
	PUNTOEXE_FUNCTION_START(L"dataHandlerDateTime::getUnicodeString");

	std::int32_t year, month, day, hour, minutes, seconds, nanoseconds, offsetHours, offsetMinutes;
	getDate(index, &year, &month, &day, &hour, &minutes, &seconds, &nanoseconds, &offsetHours, &offsetMinutes);

	std::wostringstream convStream;
	convStream << std::setfill(L'0');
	convStream << std::setw(4) << year;
	convStream << std::setw(1) << L"-";
	convStream << std::setw(2) << month;
	convStream << std::setw(1) << L"-";
	convStream << std::setw(2) << day;
	convStream << std::setw(1) << L" ";
	convStream << std::setw(2) << hour;
	convStream << std::setw(1) << L":";
	convStream << std::setw(2) << minutes;
	convStream << std::setw(1) << L":";
	convStream << std::setw(2) << seconds;
	convStream << std::setw(1) << L".";
	convStream << std::setw(6) << nanoseconds;
	if(offsetHours != 0 && offsetMinutes != 0)
	{
		convStream << std::setw(1) << (offsetHours < 0 ? L"-" : L"+");
		convStream << std::setw(2) << labs(offsetHours);
		convStream << std::setw(1) << L":";
		convStream << std::setw(2) << labs(offsetMinutes);
	}

	return convStream.str();

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Set a string representation of the date
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void dataHandlerDateTime::setUnicodeString(const std::uint32_t index, const std::wstring& value)
{
	PUNTOEXE_FUNCTION_START(L"dataHandlerDateTime::setUnicodeString");

	std::vector<std::wstring> components;
	split(value, L"-/.: +-", &components);

	std::int32_t year, month, day, hour, minutes, seconds, nanoseconds, offsetHours, offsetMinutes;
	year = 0;
	month = 1;
	day = 1;
	hour = 0;
	minutes = 0;
	seconds = 0;
	nanoseconds = 0;
	offsetHours = 0;
	offsetMinutes = 0;

	if(components.size() > 0)
	{
		std::wistringstream convStream(components[0]);
		convStream >> year;
	}
	
	if(components.size() > 1)
	{
		std::wistringstream convStream(components[1]);
		convStream >> month;
	}

	if(components.size() > 2)
	{
		std::wistringstream convStream(components[2]);
		convStream >> day;
	}

	if(components.size() > 3)
	{
		std::wistringstream convStream(components[3]);
		convStream >> hour;
	}

	if(components.size() > 4)
	{
		std::wistringstream convStream(components[4]);
		convStream >> minutes;
	}

	if(components.size() > 5)
	{
		std::wistringstream convStream(components[5]);
		convStream >> seconds;
	}

	if(components.size() > 6)
	{
		std::wistringstream convStream(components[6]);
		convStream >> nanoseconds;
	}

	if(components.size() > 7)
	{
		std::wistringstream convStream(components[7]);
		convStream >> offsetHours;
	}

	if(components.size() > 8)
	{
		std::wistringstream convStream(components[8]);
		convStream >> offsetMinutes;
	}

	if(value.find(L'+') == value.npos)
	{
		offsetHours = -offsetHours;
		offsetMinutes = -offsetMinutes;
	}


	setDate(index, year, month, day, hour, minutes, seconds, nanoseconds, offsetHours, offsetMinutes);

	PUNTOEXE_FUNCTION_END();
}



///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Return the buffer's max size
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::uint32_t dataHandlerDateTime::maxSize() const
{
	return 26;
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Return the unit size
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::uint32_t dataHandlerDateTime::getUnitSize() const
{
	return 0;
}

} // namespace handlers

} // namespace imebra

} // namespace puntoexe
