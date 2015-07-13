/*
$fileHeader$
*/

/*! \file dataHandlerDateTime.h
    \brief Declaration of the handler for the date and time.

*/

#if !defined(imebraDataHandlerDateTime_85665C7B_8DDF_479e_8CC0_83E95CB625DC__INCLUDED_)
#define imebraDataHandlerDateTime_85665C7B_8DDF_479e_8CC0_83E95CB625DC__INCLUDED_

#include "dataHandlerDateTimeBase.h"


///////////////////////////////////////////////////////////
//
// Everything is in the namespace puntoexe::imebra
//
///////////////////////////////////////////////////////////
namespace puntoexe
{

namespace imebra
{

namespace handlers
{

class dataHandlerDateTime : public dataHandlerDateTimeBase
{

public:
	virtual void getDate(const std::uint32_t index,
		std::int32_t* pYear, 
		std::int32_t* pMonth, 
		std::int32_t* pDay, 
		std::int32_t* pHour, 
		std::int32_t* pMinutes,
		std::int32_t* pSeconds,
		std::int32_t* pNanoseconds,
		std::int32_t* pOffsetHours,
		std::int32_t* pOffsetMinutes) const;

	virtual void setDate(const std::uint32_t index,
		std::int32_t year, 
		std::int32_t month, 
		std::int32_t day, 
		std::int32_t hour, 
		std::int32_t minutes,
		std::int32_t seconds,
		std::int32_t nanoseconds,
		std::int32_t offsetHours,
		std::int32_t offsetMinutes);

	/// \brief Return a string representing the date stored in 
	///         the buffer.
	///
	/// The returned string has the format: 
	///  "YYYY-MM-DD HH:MM:SS.FFFFFF"
	///  where:
	///  - YYYY is the year
	///  - MM is the month
	///  - DD is the day of the month
	///  - HH is the hour
	///  - MM are the minutes
	///  - SS are the seconds
	///  - FFFFFF are the nanoseconds
	///
	/// @return a string representing the date stored in the
	///          buffer
	///
	///////////////////////////////////////////////////////////
	virtual std::wstring getUnicodeString(const std::uint32_t index) const;

	/// \brief Set the date from a string.
	///
	/// The string must have the format:
	///  "YYYY-MM-DD HH:MM:SS.FFFFFF"
	///  where:
	///  - YYYY is the year
	///  - MM is the month
	///  - DD is the day
	///  - HH is the hour
	///  - MM are the minutes
	///  - SS are the seconds
	///  - FFFFFF are the nanoseconds
	///
	/// @param value the string representing the date to be set
	///
	///////////////////////////////////////////////////////////
	virtual void setUnicodeString(const std::uint32_t index, const std::wstring& value);

	virtual std::uint32_t getUnitSize() const;

protected:
	virtual std::uint32_t maxSize() const;
};

} // namespace handlers

} // namespace imebra

} // namespace puntoexe

#endif // !defined(imebraDataHandlerDateTime_85665C7B_8DDF_479e_8CC0_83E95CB625DC__INCLUDED_)
