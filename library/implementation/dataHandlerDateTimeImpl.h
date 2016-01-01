/*
$fileHeader$
*/

/*! \file dataHandlerDateTime.h
    \brief Declaration of the handler for the date and time.

*/

#if !defined(imebraDataHandlerDateTime_85665C7B_8DDF_479e_8CC0_83E95CB625DC__INCLUDED_)
#define imebraDataHandlerDateTime_85665C7B_8DDF_479e_8CC0_83E95CB625DC__INCLUDED_

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

class readingDataHandlerDateTime : public readingDataHandlerDateTimeBase
{

public:
    readingDataHandlerDateTime(const memory& parseMemory);

	virtual void getDate(const size_t index,
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

class writingDataHandlerDateTime: public writingDataHandlerDateTimeBase
{
public:
    writingDataHandlerDateTime(const std::shared_ptr<buffer>& pBuffer);

    virtual void setDate(const size_t index,
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

#endif // !defined(imebraDataHandlerDateTime_85665C7B_8DDF_479e_8CC0_83E95CB625DC__INCLUDED_)
