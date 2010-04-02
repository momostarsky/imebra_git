/*
$fileHeader$
*/

/*! \file dataHandlerDateTimeBase.h
    \brief Declaration of the base class for the time/date handlers.

*/

#if !defined(imebraDataHandlerDateTimeBase_85665C7B_8DDF_479e_8CC0_83E95CB625DC__INCLUDED_)
#define imebraDataHandlerDateTimeBase_85665C7B_8DDF_479e_8CC0_83E95CB625DC__INCLUDED_

#include "dataHandlerString.h"


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
	virtual imbxInt32 getSignedLong(const imbxUint32 index) const;
	virtual imbxUint32 getUnsignedLong(const imbxUint32 index) const;
	virtual double getDouble(const imbxUint32 index) const;
	virtual void setSignedLong(const imbxUint32 index, const imbxInt32 value);
	virtual void setUnsignedLong(const imbxUint32 index, const imbxUint32 value);
	virtual void setDouble(const imbxUint32 index, const double value);

protected:
	virtual wchar_t getSeparator() const;

	void parseDate(
		std::wstring dateString,
		imbxInt32* pYear, 
		imbxInt32* pMonth, 
		imbxInt32* pDay) const;

	std::wstring buildDate(
		imbxUint32 year,
		imbxUint32 month,
		imbxUint32 day) const;
	
	void parseTime(
		std::wstring timeString,
		imbxInt32* pHour, 
		imbxInt32* pMinutes,
		imbxInt32* pSeconds,
		imbxInt32* pNanoseconds,
		imbxInt32* pOffsetHours,
		imbxInt32* pOffsetMinutes) const;

	std::wstring buildTime(
		imbxInt32 hour,
		imbxInt32 minutes,
		imbxInt32 seconds,
		imbxInt32 nanoseconds,
		imbxInt32 offsetHours,
		imbxInt32 offsetMinutes
		) const;

	void split(const std::wstring& timeString, const std::wstring& separators, std::vector<std::wstring> *pComponents) const;
	std::wstring padLeft(const std::wstring& source, const wchar_t fillChar, const size_t length) const;
};

} // namespace handlers

} // namespace imebra

} // namespace puntoexe

#endif // !defined(imebraDataHandlerDateTimeBase_85665C7B_8DDF_479e_8CC0_83E95CB625DC__INCLUDED_)
