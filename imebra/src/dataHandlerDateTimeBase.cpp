/*
$fileHeader$
*/

/*! \file dataHandlerDateTimeBase.cpp
    \brief Implementation of the base class for the date/time handlers.

*/

#include "../../base/include/exception.h"
#include "../include/dataHandlerDateTimeBase.h"
#include <time.h>
#include <stdlib.h>
#include <sstream>
#include <iomanip>

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
// dataHandlerDateTimeBase
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
// Returns a long integer representing the date/time (UTC)
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
imbxInt32 dataHandlerDateTimeBase::getSignedLong()
{
	PUNTOEXE_FUNCTION_START(L"dataHandlerDateTimeBase::getSignedLong");

#ifdef _WIN32_WCE
	return -1;
#else
	imbxInt32 year, month, day, hour, minutes, seconds, nanoseconds, offsetHours, offsetMinutes;
	getDate(&year, &month, &day, &hour, &minutes, &seconds, &nanoseconds, &offsetHours, &offsetMinutes);

	tm timeStructure;
	timeStructure.tm_isdst= -1;
	timeStructure.tm_wday= 0;
	timeStructure.tm_yday= 0;
	timeStructure.tm_year = year;
	timeStructure.tm_mon = month-1;
	timeStructure.tm_mday = day;
	timeStructure.tm_hour = hour;
	timeStructure.tm_min = minutes;
	timeStructure.tm_sec = seconds;
	
	return (imbxInt32)mktime(&timeStructure);
#endif

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Cast getSignedLong to unsigned long
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
imbxUint32 dataHandlerDateTimeBase::getUnsignedLong()
{
	PUNTOEXE_FUNCTION_START(L"dataHandlerDateTimeBase::getUnsignedLong");

	return (imbxUint32)getSignedLong();

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Cast getSignedLong to double
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
double dataHandlerDateTimeBase::getDouble()
{
	PUNTOEXE_FUNCTION_START(L"dataHandlerDateTimeBase::getDouble");

	return (double)getSignedLong();

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Set the date as a signed long (from time_t)
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void dataHandlerDateTimeBase::setSignedLong(imbxInt32 value)
{
	PUNTOEXE_FUNCTION_START(L"dataHandlerDateTimeBase::setSignedLong");

#ifdef _WIN32_WCE
	return;
#else
	tm* timeStructure = localtime((time_t*)&value);
	imbxInt32 year = timeStructure->tm_year;
	imbxInt32 month = timeStructure->tm_mon + 1;
	imbxInt32 day = timeStructure->tm_mday;
	imbxInt32 hour = timeStructure->tm_hour;
	imbxInt32 minutes = timeStructure->tm_min;
	imbxInt32 seconds = timeStructure->tm_sec;
	setDate(year, month, day, hour, minutes, seconds, 0, 0, 0);
#endif

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Set the date as a long (from time_t)
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void dataHandlerDateTimeBase::setUnsignedLong(imbxUint32 value)
{
	PUNTOEXE_FUNCTION_START(L"dataHandlerDateTimeBase::setUnsignedLong");

	setSignedLong((imbxInt32)value);

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Set the date as a double (from time_t)
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void dataHandlerDateTimeBase::setDouble(double value)
{
	PUNTOEXE_FUNCTION_START(L"dataHandlerDateTimeBase::setDouble");

	setSignedLong((imbxInt32)value);

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Return the separator
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
wchar_t dataHandlerDateTimeBase::getSeparator()
{
	return 0;
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Parse a date string
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void dataHandlerDateTimeBase::parseDate(
		std::wstring dateString, 		
		imbxInt32* pYear, 
		imbxInt32* pMonth, 
		imbxInt32* pDay)
{
	PUNTOEXE_FUNCTION_START(L"dataHandlerDateTimeBase::parseDate");

	if(dateString.size()<8)
		dateString.resize(8, L'0');

	std::wstring dateYear=dateString.substr(0, 4);
	std::wstring dateMonth=dateString.substr(4, 2);
	std::wstring dateDay=dateString.substr(6, 2);

	std::wistringstream yearStream(dateYear);
	yearStream >> (*pYear);

	std::wistringstream monthStream(dateMonth);
	monthStream >> (*pMonth);

	std::wistringstream dayStream(dateDay);
	dayStream >> (*pDay);

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Build a date string
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::wstring dataHandlerDateTimeBase::buildDate(
		imbxUint32 year,
		imbxUint32 month,
		imbxUint32 day)
{
	PUNTOEXE_FUNCTION_START(L"dataHandlerDateTimeBase::buildDate");

	if((year < 0) || (year > 9999) || (month < 1) || (month>12) || (day<1) || (day>31))
	{
		year = month = day = 0;
	}

	std::wostringstream dateStream;
	dateStream << std::setfill(L'0');
	dateStream << std::setw(4) << year;
	dateStream << std::setw(2) << month;
	dateStream << std::setw(2) << day;

	return dateStream.str();

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Parse a time string
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void dataHandlerDateTimeBase::parseTime(
		std::wstring timeString, 		
		imbxInt32* pHour, 
		imbxInt32* pMinutes,
		imbxInt32* pSeconds,
		imbxInt32* pNanoseconds,
		imbxInt32* pOffsetHours,
		imbxInt32* pOffsetMinutes)
{
	PUNTOEXE_FUNCTION_START(L"dataHandlerDateTimeBase::parseTime");

	if(timeString.size() < 6)
	{
		timeString.resize(6, L'0');
	}
	if(timeString.size() < 7)
	{
		timeString += L'.';
	}
	if(timeString.size() < 13)
	{
		timeString.resize(13, L'0');
	}
	if(timeString.size() < 14)
	{
		timeString += L'+';
	}
	if(timeString.size() < 18)
	{
		timeString.resize(18, L'0');
	}
	
	std::wstring timeHour = timeString.substr(0, 2);
	std::wstring timeMinutes = timeString.substr(2, 2);
	std::wstring timeSeconds = timeString.substr(4, 2);
	std::wstring timeNanoseconds = timeString.substr(7, 6);
	std::wstring timeOffsetHours = timeString.substr(13, 3);
	std::wstring timeOffsetMinutes = timeString.substr(16, 2);

	std::wistringstream hourStream(timeHour);
	hourStream >> (*pHour);

	std::wistringstream minutesStream(timeMinutes);
	minutesStream >> (*pMinutes);

	std::wistringstream secondsStream(timeSeconds);
	secondsStream >> (*pSeconds);

	std::wistringstream nanosecondsStream(timeNanoseconds);
	nanosecondsStream >> (*pNanoseconds);

	std::wistringstream offsetHoursStream(timeOffsetHours);
	offsetHoursStream >> (*pOffsetHours);

	std::wistringstream offsetMinutesStream(timeOffsetMinutes);
	offsetMinutesStream >> (*pOffsetMinutes);

	if(*pOffsetHours < 0)
	{
		*pOffsetMinutes= - *pOffsetMinutes;
	}

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Build the time string
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::wstring dataHandlerDateTimeBase::buildTime(
		imbxInt32 hour,
		imbxInt32 minutes,
		imbxInt32 seconds,
		imbxInt32 nanoseconds,
		imbxInt32 offsetHours,
		imbxInt32 offsetMinutes
		)
{
	PUNTOEXE_FUNCTION_START(L"dataHandlerDateTimeBase::buildTime");

	if(
		   (hour < 0)
		|| (hour >= 24)
		|| (minutes < 0)
		|| (minutes >= 60)
		|| (seconds <0)
		|| (seconds >= 60)
		|| (nanoseconds < 0)
		|| (nanoseconds > 999999)
		|| (offsetHours < -12)
		|| (offsetHours > 12)
		|| (offsetMinutes < -59)
		|| (offsetMinutes > 59))
	{
		hour = minutes = seconds = nanoseconds = offsetHours = offsetMinutes = 0;
	}

	bool bMinus=offsetHours < 0;

	std::wostringstream timeStream;
	timeStream << std::setfill(L'0');
	timeStream << std::setw(2) << hour;
	timeStream << std::setw(2) << minutes;
	timeStream << std::setw(2) << seconds;
	timeStream << std::setw(1) << L".";
	timeStream << std::setw(6) << nanoseconds;
	timeStream << std::setw(1) << (bMinus ? L"-" : L"+");
	timeStream << std::setw(2) << labs(offsetHours);
	timeStream << std::setw(2) << labs(offsetMinutes);
	
	return timeStream.str();

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Split several parts of a string
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void dataHandlerDateTimeBase::split(std::wstring timeString, std::wstring separators, std::vector<std::wstring> *pComponents)
{
	PUNTOEXE_FUNCTION_START(L"dataHandlerDateTimeBase::split");

	for(size_t sepPos = timeString.find_first_of(separators); sepPos != timeString.npos; sepPos = timeString.find_first_of(separators))
	{
		std::wstring left = timeString.substr(0, sepPos);
		std::wstring right = timeString.substr(++sepPos);

		pComponents->push_back(left);
		timeString = right;
	}
	pComponents->push_back(timeString);

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Add the specified char to the left of a string until
//  its length reaches the desidered value
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::wstring dataHandlerDateTimeBase::padLeft(std::wstring source, std::wstring fillChar, size_t length)
{
	PUNTOEXE_FUNCTION_START(L"dataHandlerDateTimeBase::padLeft");

	while(source.size() < length)
	{
		source.insert(0, fillChar);
	}
	return source;

	PUNTOEXE_FUNCTION_END();
}

} // namespace handlers

} // namespace imebra

} // namespace puntoexe



