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
	virtual imbxInt32 getSignedLong();
	virtual imbxUint32 getUnsignedLong();
	virtual double getDouble();
	virtual void setSignedLong(imbxInt32 value);
	virtual void setUnsignedLong(imbxUint32 value);
	virtual void setDouble(double value);

protected:
	virtual wchar_t getSeparator();

	void parseDate(
		std::wstring dateString, 		
		imbxInt32* pYear, 
		imbxInt32* pMonth, 
		imbxInt32* pDay);

	std::wstring buildDate(
		imbxUint32 year,
		imbxUint32 month,
		imbxUint32 day);
	
	void parseTime(
		std::wstring timeString, 		
		imbxInt32* pHour, 
		imbxInt32* pMinutes,
		imbxInt32* pSeconds,
		imbxInt32* pNanoseconds,
		imbxInt32* pOffsetHours,
		imbxInt32* pOffsetMinutes);

	std::wstring buildTime(
		imbxInt32 hour,
		imbxInt32 minutes,
		imbxInt32 seconds,
		imbxInt32 nanoseconds,
		imbxInt32 offsetHours,
		imbxInt32 offsetMinutes
		);

	void split(std::wstring timeString, std::wstring separators, std::vector<std::wstring> *pComponents);
	std::wstring padLeft(std::wstring source, std::wstring fillChar, size_t length);
};

} // namespace handlers

} // namespace imebra

} // namespace puntoexe

#endif // !defined(imebraDataHandlerDateTimeBase_85665C7B_8DDF_479e_8CC0_83E95CB625DC__INCLUDED_)
