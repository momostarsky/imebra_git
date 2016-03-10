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

WritingDataHandler::WritingDataHandler(const WritingDataHandler& right) : m_pDataHandler(right.m_pDataHandler)
{}

WritingDataHandler::~WritingDataHandler()
{
}

WritingDataHandler& WritingDataHandler::operator=(const WritingDataHandler& right)
{
    m_pDataHandler = right.m_pDataHandler;
    return *this;
}

WritingDataHandler::WritingDataHandler(std::shared_ptr<imebra::implementation::handlers::writingDataHandler> pDataHandler): m_pDataHandler(pDataHandler)
{}

void WritingDataHandler::close()
{
    m_pDataHandler.reset();
}

void WritingDataHandler::setSize(const size_t elementsNumber)
{
    m_pDataHandler->setSize(elementsNumber);
}

size_t WritingDataHandler::getSize() const
{
    return m_pDataHandler->getSize();
}

std::string WritingDataHandler::getDataType() const
{
    return m_pDataHandler->getDataType();
}


WritingDataHandler& WritingDataHandler::setDate(const size_t index, const Date& date)
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

WritingDataHandler& WritingDataHandler::setAge(const size_t index, const Age& age)
{
    m_pDataHandler->setAge(index, age.age, age.units);
    return *this;
}

WritingDataHandler& WritingDataHandler::setSignedLong(const size_t index, const std::int32_t value)
{
    m_pDataHandler->setSignedLong(index, value);
    return *this;
}

WritingDataHandler& WritingDataHandler::setUnsignedLong(const size_t index, const std::uint32_t value)
{
    m_pDataHandler->setUnsignedLong(index, value);
    return *this;
}

WritingDataHandler& WritingDataHandler::setDouble(const size_t index, const double value)
{
    m_pDataHandler->setDouble(index, value);
    return *this;
}

WritingDataHandler& WritingDataHandler::setString(const size_t index, const std::string& value)
{
    m_pDataHandler->setString(index, value);
    return *this;
}

WritingDataHandler& WritingDataHandler::setUnicodeString(const size_t index, const std::wstring& value)
{
    m_pDataHandler->setUnicodeString(index, value);
    return *this;
}

}
