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
class readingDataHandlerTime : public readingDataHandlerDateTimeBase
{

public:
    readingDataHandlerTime(const memory& parseMemory);

	virtual void getDate(
        const size_t index,
		std::int32_t* pYear, 
		std::int32_t* pMonth, 
		std::int32_t* pDay, 
		std::int32_t* pHour, 
		std::int32_t* pMinutes,
		std::int32_t* pSeconds,
		std::int32_t* pNanoseconds,
		std::int32_t* pOffsetHours,
		std::int32_t* pOffsetMinutes) const;

};

class writingDataHandlerTime: public writingDataHandlerDateTimeBase
{
public:
    writingDataHandlerTime(const std::shared_ptr<buffer>& pBuffer);

    virtual void setDate(
        const size_t index,
        std::int32_t year,
        std::int32_t month,
        std::int32_t day,
        std::int32_t hour,
        std::int32_t minutes,
        std::int32_t seconds,
        std::int32_t nanoseconds,
        std::int32_t offsetHours,
        std::int32_t offsetMinutes);
};

} // namespace handlers

} // namespace imebra

} // namespace puntoexe

#endif // !defined(imebraDataHandlerTime_22271468_E9BC_4c3e_B733_6EA5C9DC858E__INCLUDED_)
