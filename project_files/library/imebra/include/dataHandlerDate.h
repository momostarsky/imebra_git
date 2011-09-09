/*
$fileHeader$
*/

/*! \file dataHandlerDate.h
    \brief Declaration of the data handler able to handle the dicom tags
	        of type "DA" (date).

*/

#if !defined(imebraDataHandlerDate_BAA5E237_A37C_40bc_96EF_460B2D53DC12__INCLUDED_)
#define imebraDataHandlerDate_BAA5E237_A37C_40bc_96EF_460B2D53DC12__INCLUDED_

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

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This %data handler is returned by the class
///         buffer when the application wants to deal
///         with a dicom tag of type "DA" (date)
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class dataHandlerDate : public dataHandlerDateTimeBase
{
public:
	virtual imbxUint32 getUnitSize() const;

	virtual void getDate(const imbxUint32 index,
		imbxInt32* pYear, 
		imbxInt32* pMonth, 
		imbxInt32* pDay, 
		imbxInt32* pHour, 
		imbxInt32* pMinutes,
		imbxInt32* pSeconds,
		imbxInt32* pNanoseconds,
		imbxInt32* pOffsetHours,
		imbxInt32* pOffsetMinutes) const;

	virtual void setDate(const imbxUint32 index,
		imbxInt32 year, 
		imbxInt32 month, 
		imbxInt32 day, 
		imbxInt32 hour, 
		imbxInt32 minutes,
		imbxInt32 seconds,
		imbxInt32 nanoseconds,
		imbxInt32 offsetHours,
		imbxInt32 offsetMinutes);

	/// \brief Return a string representing the date stored in 
	///         the buffer.
	///
	/// The returned string has the format: "YYYY-MM-DD"
	///  where:
	///  - YYYY is the year
	///  - MM is the month
	///  - DD is the day
	///
	/// @param index the zero based index of the date to
	///         retrieve
	/// @return a string representing the date stored in the
	///          buffer
	///
	///////////////////////////////////////////////////////////
	virtual std::wstring getUnicodeString(const imbxUint32 index) const;

	/// \brief Set the date from a string.
	///
	/// The string must have the format: "YYYY-MM-DD"
	///  where:
	///  - YYYY is the year
	///  - MM is the month
	///  - DD is the day
	///
	/// @param index the zero based index of the date to be
	///         set
	/// @param value the string representing the date to be set
	///
	///////////////////////////////////////////////////////////
	virtual void setUnicodeString(const imbxUint32 index, const std::wstring& value);

	void parseBuffer(const ptr<memory>& memoryBuffer);

protected:
	virtual imbxUint32 maxSize() const;
};

} // namespace handlers

} // namespace imebra

} // namespace puntoexe

#endif // !defined(imebraDataHandlerDate_BAA5E237_A37C_40bc_96EF_460B2D53DC12__INCLUDED_)
