/*
$fileHeader$
*/

/*! \file dataHandler_swig.cpp
    \brief Implementation of the class DataHandler for SWIG.
*/

#include "../include/imebra/dataHandler.h"
#include "../implementation/dataHandlerImpl.h"
#include "../implementation/dataHandlerNumericImpl.h"
#include <cstring>

namespace imebra
{

ReadingDataHandler::ReadingDataHandler(const ReadingDataHandler& right) : m_pDataHandler(right.m_pDataHandler)
{}

ReadingDataHandler& ReadingDataHandler::operator=(const ReadingDataHandler& right)
{
    m_pDataHandler = right.m_pDataHandler;
    return *this;
}

ReadingDataHandler::ReadingDataHandler(std::shared_ptr<imebra::implementation::handlers::readingDataHandler> pDataHandler): m_pDataHandler(pDataHandler)
{}

void ReadingDataHandler::close()
{
    m_pDataHandler.reset();
}

size_t ReadingDataHandler::getSize() const
{
    return m_pDataHandler->getSize();
}

std::string ReadingDataHandler::getDataType() const
{
    return m_pDataHandler->getDataType();
}

std::int32_t ReadingDataHandler::getSignedLong(const size_t index) const
{
    return m_pDataHandler->getSignedLong(index);
}

std::uint32_t ReadingDataHandler::getUnsignedLong(const size_t index) const
{
    return m_pDataHandler->getUnsignedLong(index);
}

double ReadingDataHandler::getDouble(const size_t index) const
{
    return m_pDataHandler->getDouble(index);
}

std::string ReadingDataHandler::getString(const size_t index) const
{
    return m_pDataHandler->getString(index);
}

std::wstring ReadingDataHandler::getUnicodeString(const size_t index) const
{
    return m_pDataHandler->getUnicodeString(index);
}

Date ReadingDataHandler::getDate(const size_t index) const
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

Age ReadingDataHandler::getAge(const size_t index) const
{
    imebra::ageUnit_t ageUnits;
    std::uint32_t age = m_pDataHandler->getAge(index, &ageUnits);
    return Age(age, ageUnits);
}

size_t ReadingDataHandler::data(char* bufferOut, const size_t bufferSize) const
{
    std::shared_ptr<imebra::implementation::handlers::readingDataHandlerNumericBase> numericDataHandler = std::dynamic_pointer_cast<imebra::implementation::handlers::readingDataHandlerNumericBase>(m_pDataHandler);
    if(numericDataHandler == 0)
    {
        return 0;
    }
    size_t memorySize = numericDataHandler->getMemorySize();
    if(memorySize == 0)
    {
       return 0;
    }
    if(bufferOut != 0 && bufferSize >= memorySize)
    {
        ::memcpy(bufferOut, numericDataHandler->getMemoryBuffer(), memorySize);
    }
    return memorySize;
}

const char* ReadingDataHandler::data(size_t* pDataSize) const
{
    std::shared_ptr<imebra::implementation::handlers::readingDataHandlerNumericBase> numericDataHandler = std::dynamic_pointer_cast<imebra::implementation::handlers::readingDataHandlerNumericBase>(m_pDataHandler);
    if(numericDataHandler == 0)
    {
        *pDataSize = 0;
        return 0;
    }
    *pDataSize = numericDataHandler->getMemorySize();
    return (const char*)numericDataHandler->getMemoryBuffer();
}


WritingDataHandler::WritingDataHandler(const WritingDataHandler& right) : m_pDataHandler(right.m_pDataHandler)
{}

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

void WritingDataHandler::assign(const char *buffer, const size_t bufferSize)
{
    std::shared_ptr<imebra::implementation::handlers::writingDataHandlerNumericBase> numericDataHandler = std::dynamic_pointer_cast<imebra::implementation::handlers::writingDataHandlerNumericBase>(m_pDataHandler);
    if(numericDataHandler == 0)
    {
        return;
    }

    numericDataHandler->getMemory()->assign((std::uint8_t*) buffer, bufferSize);
}

char* WritingDataHandler::data(size_t* pDataSize) const
{
    std::shared_ptr<imebra::implementation::handlers::writingDataHandlerNumericBase> numericDataHandler = std::dynamic_pointer_cast<imebra::implementation::handlers::writingDataHandlerNumericBase>(m_pDataHandler);
    if(numericDataHandler == 0)
    {
        *pDataSize = 0;
        return 0;
    }
    *pDataSize = numericDataHandler->getMemorySize();
    return (char*)numericDataHandler->getMemoryBuffer();

}


}
