/*
$fileHeader$
*/

/*! \file dataHandler.cpp
    \brief Implementation of the classes ReadingDataHandler & WritingDataHandler.
*/

#include "../include/imebra/writingDataHandler.h"
#include "../implementation/dataHandlerImpl.h"
#include "../implementation/dataHandlerNumericImpl.h"
#include <cstring>

namespace imebra
{

WritingDataHandler::~WritingDataHandler()
{
}

WritingDataHandler::WritingDataHandler(std::shared_ptr<imebra::implementation::handlers::writingDataHandler> pDataHandler): m_pDataHandler(pDataHandler)
{}

void WritingDataHandler::setSize(size_t elementsNumber)
{
    m_pDataHandler->setSize(elementsNumber);
}

size_t WritingDataHandler::getSize() const
{
    return m_pDataHandler->getSize();
}

tagVR_t WritingDataHandler::getDataType() const
{
    return m_pDataHandler->getDataType();
}


WritingDataHandler& WritingDataHandler::setDate(size_t index, const Date& date)
{
    m_pDataHandler->setDate(
        (std::uint32_t)index,
        (std::uint32_t)date.year,
        (std::uint32_t)date.month,
        (std::uint32_t)date.day,
        (std::uint32_t)date.hour,
        (std::uint32_t)date.minutes,
        (std::uint32_t)date.seconds,
        (std::uint32_t)date.nanoseconds,
        (std::int32_t)date.offsetHours,
        (std::int32_t)date.offsetMinutes);
    return *this;
}

WritingDataHandler& WritingDataHandler::setAge(size_t index, const Age& age)
{
    m_pDataHandler->setAge(index, age.age, age.units);
    return *this;
}

WritingDataHandler& WritingDataHandler::setSignedLong(size_t index, std::int32_t value)
{
    m_pDataHandler->setSignedLong(index, value);
    return *this;
}

WritingDataHandler& WritingDataHandler::setUnsignedLong(size_t index, std::uint32_t value)
{
    m_pDataHandler->setUnsignedLong(index, value);
    return *this;
}

WritingDataHandler& WritingDataHandler::setDouble(size_t index, double value)
{
    m_pDataHandler->setDouble(index, value);
    return *this;
}

WritingDataHandler& WritingDataHandler::setString(size_t index, const std::string& value)
{
    m_pDataHandler->setString(index, value);
    return *this;
}

WritingDataHandler& WritingDataHandler::setUnicodeString(size_t index, const std::wstring& value)
{
    m_pDataHandler->setUnicodeString(index, value);
    return *this;
}

}
