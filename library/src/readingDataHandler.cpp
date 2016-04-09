/*
$fileHeader$
*/

/*! \file dataHandler.cpp
    \brief Implementation of the classes ReadingDataHandler & WritingDataHandler.
*/

#include "../include/imebra/readingDataHandler.h"
#include "../implementation/dataHandlerImpl.h"
#include "../implementation/dataHandlerNumericImpl.h"
#include <cstring>

namespace imebra
{

ReadingDataHandler::~ReadingDataHandler()
{
}

ReadingDataHandler::ReadingDataHandler(std::shared_ptr<imebra::implementation::handlers::readingDataHandler> pDataHandler): m_pDataHandler(pDataHandler)
{}

size_t ReadingDataHandler::getSize() const
{
    return m_pDataHandler->getSize();
}

tagVR_t ReadingDataHandler::getDataType() const
{
    return m_pDataHandler->getDataType();
}

std::int32_t ReadingDataHandler::getSignedLong(size_t index) const
{
    return m_pDataHandler->getSignedLong(index);
}

std::uint32_t ReadingDataHandler::getUnsignedLong(size_t index) const
{
    return m_pDataHandler->getUnsignedLong(index);
}

double ReadingDataHandler::getDouble(size_t index) const
{
    return m_pDataHandler->getDouble(index);
}

std::string ReadingDataHandler::getString(size_t index) const
{
    return m_pDataHandler->getString(index);
}

std::wstring ReadingDataHandler::getUnicodeString(size_t index) const
{
    return m_pDataHandler->getUnicodeString(index);
}

Date ReadingDataHandler::getDate(size_t index) const
{
    std::uint32_t year, month, day, hour, minutes, seconds, nanoseconds;
    std::int32_t offsetHours, offsetMinutes;
    m_pDataHandler->getDate(index, &year, &month, &day, &hour, &minutes, &seconds, &nanoseconds, &offsetHours, &offsetMinutes);

    return Date(
                (unsigned int)year,
                (unsigned int)month,
                (unsigned int)day,
                (unsigned int)hour,
                (unsigned int)minutes,
                (unsigned int)seconds,
                (unsigned int)nanoseconds,
                (int)offsetHours,
                (int)offsetMinutes);
}

Age ReadingDataHandler::getAge(size_t index) const
{
    imebra::ageUnit_t ageUnits;
    std::uint32_t age = m_pDataHandler->getAge(index, &ageUnits);
    return Age(age, ageUnits);
}

}
