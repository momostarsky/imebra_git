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

dataHandlerTime::dataHandlerTime(): dataHandlerDateTimeBase("TM")
{

}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Get the maximum size
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::uint32_t dataHandlerTime::maxSize() const
{
	return 16;
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Get the fixed size
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::uint32_t dataHandlerTime::getUnitSize() const
{
	return 0;
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Parse the buffer and build the local buffer
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void dataHandlerTime::parseBuffer(const std::shared_ptr<memory>& memoryBuffer)
{
	PUNTOEXE_FUNCTION_START(L"dataHandlerTime::parseBuffer");

	// Parse the string
	///////////////////////////////////////////////////////////
	dataHandlerString::parseBuffer(memoryBuffer);

	// Adjust the parsed string so it is a legal time
	///////////////////////////////////////////////////////////
    std::wstring unicodeString(dataHandlerString::getUnicodeString(0));

	// Remove trailing spaces an invalid chars
	///////////////////////////////////////////////////////////
	size_t removeTrail;
	for(removeTrail = unicodeString.size(); removeTrail != 0 && ( unicodeString[removeTrail - 1] == 0x20 || unicodeString[removeTrail - 1] == 0x0); --removeTrail){};
	unicodeString.resize(removeTrail);

	// Separate the components
	///////////////////////////////////////////////////////////
	std::vector<std::wstring> components;
	split(unicodeString, L":", &components);
	std::wstring normalizedTime;

	if(components.size() == 1)
	{
		normalizedTime = components.front();
	}
	else
	{
		if(components.size() > 0)
		{
			normalizedTime = padLeft(components[0], L'0', 2);
		}
		if(components.size() > 1)
		{
			normalizedTime += padLeft(components[1], L'0', 2);
		}
		if(components.size() > 2)
		{
			std::vector<std::wstring> secondsComponents;
			split(components[2], L".", &secondsComponents);
			if(secondsComponents.size() > 0)
			{
				normalizedTime += padLeft(secondsComponents[0], L'0', 2);
			}
			if(secondsComponents.size() > 1)
			{
				normalizedTime += L'.';
				normalizedTime += secondsComponents[1];
			}
		}
	}
	dataHandlerString::setUnicodeString(0, normalizedTime);

	PUNTOEXE_FUNCTION_END();
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
void dataHandlerTime::setDate(const std::uint32_t index,
		 std::int32_t /* year */,
		 std::int32_t /* month */,
		 std::int32_t /* day */,
		 std::int32_t hour,
		 std::int32_t minutes,
		 std::int32_t seconds,
		 std::int32_t nanoseconds,
		 std::int32_t offsetHours,
		 std::int32_t offsetMinutes)
{
	PUNTOEXE_FUNCTION_START(L"dataHandlerTime::setDate");

	std::wstring timeString = buildTime(hour, minutes, seconds, nanoseconds, offsetHours, offsetMinutes);
	timeString.resize(13);
	dataHandlerDateTimeBase::setUnicodeString(index, timeString);

	PUNTOEXE_FUNCTION_END();
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
void dataHandlerTime::getDate(const std::uint32_t index,
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
	PUNTOEXE_FUNCTION_START(L"dataHandlerTime::getDate");

	*pYear = 0;
	*pMonth = 0;
	*pDay = 0;
	*pHour = 0;
	*pMinutes = 0;
	*pSeconds = 0;
	*pNanoseconds = 0;
	*pOffsetHours = 0;
	*pOffsetMinutes = 0;

	std::wstring timeString(dataHandlerDateTimeBase::getUnicodeString(index));
	parseTime(timeString, pHour, pMinutes, pSeconds, pNanoseconds, pOffsetHours, pOffsetMinutes);

	PUNTOEXE_FUNCTION_END();

}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Get a string representation of the time
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::wstring dataHandlerTime::getUnicodeString(const std::uint32_t index) const
{
	PUNTOEXE_FUNCTION_START(L"dataHandlerTime::getUnicodeString");

	std::int32_t year, month, day, hour, minutes, seconds, nanoseconds, offsetHours, offsetMinutes;
	getDate(index, &year, &month, &day, &hour, &minutes, &seconds, &nanoseconds, &offsetHours, &offsetMinutes);

	std::wostringstream convStream;
	convStream << std::setfill(L'0');
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
// Set a string representation of the time
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void dataHandlerTime::setUnicodeString(const std::uint32_t index, const std::wstring& value)
{
	PUNTOEXE_FUNCTION_START(L"dataHandlerTime::setUnicodeString");

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
		convStream >> hour;
	}

	if(components.size() > 1)
	{
		std::wistringstream convStream(components[1]);
		convStream >> minutes;
	}

	if(components.size() > 2)
	{
		std::wistringstream convStream(components[2]);
		convStream >> seconds;
	}

	if(components.size() > 3)
	{
		std::wistringstream convStream(components[3]);
		convStream >> nanoseconds;
	}

	if(components.size() > 4)
	{
		std::wistringstream convStream(components[4]);
		convStream >> offsetHours;
	}

	if(components.size() > 5)
	{
		std::wistringstream convStream(components[5]);
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


} // namespace handlers

} // namespace imebra

} // namespace puntoexe
