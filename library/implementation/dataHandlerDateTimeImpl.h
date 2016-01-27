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
// Everything is in the namespace imebra::implementation
//
///////////////////////////////////////////////////////////
namespace imebra
{

namespace implementation
{

namespace handlers
{

class readingDataHandlerDateTime : public readingDataHandlerDateTimeBase
{

public:
    readingDataHandlerDateTime(const memory& parseMemory);

	virtual void getDate(const size_t index,
        std::uint32_t* pYear,
        std::uint32_t* pMonth,
        std::uint32_t* pDay,
        std::uint32_t* pHour,
        std::uint32_t* pMinutes,
        std::uint32_t* pSeconds,
        std::uint32_t* pNanoseconds,
		std::int32_t* pOffsetHours,
		std::int32_t* pOffsetMinutes) const;

};

class writingDataHandlerDateTime: public writingDataHandlerDateTimeBase
{
public:
    writingDataHandlerDateTime(const std::shared_ptr<buffer>& pBuffer);

    virtual void setDate(const size_t index,
        std::uint32_t year,
        std::uint32_t month,
        std::uint32_t day,
        std::uint32_t hour,
        std::uint32_t minutes,
        std::uint32_t seconds,
        std::uint32_t nanoseconds,
        std::int32_t offsetHours,
        std::int32_t offsetMinutes);
};

} // namespace handlers

} // namespace implementation

} // namespace imebra

#endif // !defined(imebraDataHandlerDateTime_85665C7B_8DDF_479e_8CC0_83E95CB625DC__INCLUDED_)
