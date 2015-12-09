/*
$fileHeader$
*/

/*! \file dataHandlerDateTimeBase.h
    \brief Declaration of the base class for the time/date handlers.

*/

#if !defined(imebraDataHandlerDateTimeBase_85665C7B_8DDF_479e_8CC0_83E95CB625DC__INCLUDED_)
#define imebraDataHandlerDateTimeBase_85665C7B_8DDF_479e_8CC0_83E95CB625DC__INCLUDED_

#include "dataHandlerStringImpl.h"


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
/// \brief This class is used as base class by the handlers
///         that manage the date and the time
///
/// This class supplies the methods setSignedLong(), 
///  setUnsignedLong(), setDouble(), getSignedLong(),
///  getUnsignedLong(), getDouble(). Those methods work
///  with time_t structure
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class dataHandlerDateTimeBase : public dataHandlerString {

public:
	virtual std::int32_t getSignedLong(const std::uint32_t index) const;
	virtual std::uint32_t getUnsignedLong(const std::uint32_t index) const;
	virtual double getDouble(const std::uint32_t index) const;
	virtual void setSignedLong(const std::uint32_t index, const std::int32_t value);
	virtual void setUnsignedLong(const std::uint32_t index, const std::uint32_t value);
	virtual void setDouble(const std::uint32_t index, const double value);

protected:
	virtual wchar_t getSeparator() const;

	void parseDate(
		std::wstring dateString,
		std::int32_t* pYear, 
		std::int32_t* pMonth, 
		std::int32_t* pDay) const;

	std::wstring buildDate(
		std::uint32_t year,
		std::uint32_t month,
		std::uint32_t day) const;
	
	void parseTime(
		std::wstring timeString,
		std::int32_t* pHour, 
		std::int32_t* pMinutes,
		std::int32_t* pSeconds,
		std::int32_t* pNanoseconds,
		std::int32_t* pOffsetHours,
		std::int32_t* pOffsetMinutes) const;

	std::wstring buildTime(
		std::int32_t hour,
		std::int32_t minutes,
		std::int32_t seconds,
		std::int32_t nanoseconds,
		std::int32_t offsetHours,
		std::int32_t offsetMinutes
		) const;

	void split(const std::wstring& timeString, const std::wstring& separators, std::vector<std::wstring> *pComponents) const;
	std::wstring padLeft(const std::wstring& source, const wchar_t fillChar, const size_t length) const;
};

} // namespace handlers

} // namespace imebra

} // namespace puntoexe

#endif // !defined(imebraDataHandlerDateTimeBase_85665C7B_8DDF_479e_8CC0_83E95CB625DC__INCLUDED_)
