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
class readingDataHandlerDateTimeBase : public readingDataHandlerString
{

public:
    readingDataHandlerDateTimeBase(const memory& parseMemory, const std::string& dataType);

    virtual std::int32_t getSignedLong(const size_t index) const;
    virtual std::uint32_t getUnsignedLong(const size_t index) const;
    virtual double getDouble(const size_t index) const;

protected:
	void parseDate(
        const std::string& dateString,
        std::uint32_t* pYear,
        std::uint32_t* pMonth,
        std::uint32_t* pDay) const;

	void parseTime(
        const std::string& timeString,
        std::uint32_t* pHour,
        std::uint32_t* pMinutes,
        std::uint32_t* pSeconds,
        std::uint32_t* pNanoseconds,
		std::int32_t* pOffsetHours,
		std::int32_t* pOffsetMinutes) const;

    void split(const std::string& timeString, const std::string& separators, std::vector<std::string> *pComponents) const;
};

class writingDataHandlerDateTimeBase: public writingDataHandlerString
{
public:
    writingDataHandlerDateTimeBase(const std::shared_ptr<buffer>& pBuffer, const std::string& dataType, const size_t unitSize, const size_t maxSize);

    virtual void setSignedLong(const size_t index, const std::int32_t value);
    virtual void setUnsignedLong(const size_t index, const std::uint32_t value);
    virtual void setDouble(const size_t index, const double value);

protected:
    std::string buildDate(
        std::uint32_t year,
        std::uint32_t month,
        std::uint32_t day) const;

    std::string buildTime(
        std::int32_t hour,
        std::int32_t minutes,
        std::int32_t seconds,
        std::int32_t nanoseconds,
        std::int32_t offsetHours,
        std::int32_t offsetMinutes
        ) const;

    std::string padLeft(const std::string& source, const char fillChar, const size_t length) const;

};

} // namespace handlers

} // namespace imebra

} // namespace puntoexe

#endif // !defined(imebraDataHandlerDateTimeBase_85665C7B_8DDF_479e_8CC0_83E95CB625DC__INCLUDED_)
