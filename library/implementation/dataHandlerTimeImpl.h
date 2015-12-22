/*
$fileHeader$
*/

/*! \file dataHandlerTime.h
    \brief Declaration of the class dataHandlerTime.

*/

#if !defined(imebraDataHandlerTime_22271468_E9BC_4c3e_B733_6EA5C9DC858E__INCLUDED_)
#define imebraDataHandlerTime_22271468_E9BC_4c3e_B733_6EA5C9DC858E__INCLUDED_

#include "dataHandlerDateTimeBaseImpl.h"


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

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This %data handler is returned by the class
///         buffer when the application wants to deal
///         with a dicom tag of type "TM" (time)
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class dataHandlerTime : public dataHandlerDateTimeBase
{

public:
	virtual std::uint32_t getUnitSize() const;

	virtual void getDate(
                const std::uint32_t index,
		std::int32_t* pYear, 
		std::int32_t* pMonth, 
		std::int32_t* pDay, 
		std::int32_t* pHour, 
		std::int32_t* pMinutes,
		std::int32_t* pSeconds,
		std::int32_t* pNanoseconds,
		std::int32_t* pOffsetHours,
		std::int32_t* pOffsetMinutes) const;

	virtual void setDate(
                const std::uint32_t index,
		std::int32_t year, 
		std::int32_t month, 
		std::int32_t day, 
		std::int32_t hour, 
		std::int32_t minutes,
		std::int32_t seconds,
		std::int32_t nanoseconds,
		std::int32_t offsetHours,
		std::int32_t offsetMinutes);

	/// \brief Return a string representing the time stored in 
	///         the buffer.
	///
	/// The returned string has the format: "HH:MM:SS.FFFFFF"
	///  where:
	///  - HH is the hour
	///  - MM is the minute
	///  - SS is the second
	///  - FFFFFF is the fraction of seconds in nanoseconds
	///
	/// @param index the zero based index of the time value to
	///               read
	/// @return a string representing the time stored in the
	///          buffer
	///
	///////////////////////////////////////////////////////////
	virtual std::wstring getUnicodeString(const std::uint32_t index) const;

	/// \brief Set the date from a string.
	///
	/// The string must have the format: "HH:MM:SS.FFFFFF"
	///  where:
	///  - HH is the hour
	///  - MM is the minute
	///  - SS is the second
	///  - FFFFFF is the fraction of seconds in nanoseconds
	///
	/// @param index the zero based index of the time value to
	///               modify
	/// @param value the string representing the time to be set
	///
	///////////////////////////////////////////////////////////
	virtual void setUnicodeString(const std::uint32_t index, const std::wstring& value);

	void parseBuffer(const std::shared_ptr<memory>& memoryBuffer);

protected:
	virtual std::uint32_t maxSize() const;
};

} // namespace handlers

} // namespace imebra

} // namespace puntoexe

#endif // !defined(imebraDataHandlerTime_22271468_E9BC_4c3e_B733_6EA5C9DC858E__INCLUDED_)
