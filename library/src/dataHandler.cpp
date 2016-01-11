/*
$fileHeader$
*/

/*! \file dataHandler_swig.cpp
    \brief Implementation of the class DataHandler for SWIG.
*/

#include "../include/imebra/dataHandler.h"
#include "../implementation/dataHandlerImpl.h"
#include "../implementation/dataHandlerNumericImpl.h"

namespace imebra
{

Age::Age(uint32_t initialAge, ageUnit_t initialUnits):
    age(initialAge), units(initialUnits)
{

}

Date::Date(
        const unsigned int initialYear,
        const unsigned int initialMonth,
        const unsigned int initialDay,
        const unsigned int initialHour,
        const unsigned int initialMinutes,
        const unsigned int initialSeconds,
        const unsigned int initialNanoseconds,
        const signed int initialOffsetHours,
        const signed int initialOffsetMinutes):
    year(initialYear),
    month(initialMonth),
    day(initialDay),
    hour(initialHour),
    minutes(initialMinutes),
    seconds(initialSeconds),
    nanoseconds(initialNanoseconds),
    offsetHours(initialOffsetHours),
    offsetMinutes(initialOffsetMinutes)
{

}

ReadingDataHandler::ReadingDataHandler(const ReadingDataHandler& right) : m_pDataHandler(right.m_pDataHandler)
{}

ReadingDataHandler& ReadingDataHandler::operator=(const ReadingDataHandler& right)
{
    m_pDataHandler = right.m_pDataHandler;
    return *this;
}

ReadingDataHandler::ReadingDataHandler(std::shared_ptr<puntoexe::imebra::handlers::readingDataHandler> pDataHandler): m_pDataHandler(pDataHandler)
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

int ReadingDataHandler::getSignedLong(const int index) const
{
    return (int)(m_pDataHandler->getSignedLong(index));
}

unsigned int ReadingDataHandler::getUnsignedLong(const int index) const
{
    return (int)(m_pDataHandler->getUnsignedLong(index));
}

double ReadingDataHandler::getDouble(const int index) const
{
    return m_pDataHandler->getDouble(index);
}

std::wstring ReadingDataHandler::getString(const int index) const
{
    return m_pDataHandler->getUnicodeString(index);
}

Date ReadingDataHandler::getDate(const int index) const
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
    std::shared_ptr<puntoexe::imebra::handlers::readingDataHandlerNumericBase> numericDataHandler = std::dynamic_pointer_cast<puntoexe::imebra::handlers::readingDataHandlerNumericBase>(m_pDataHandler);
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
    std::shared_ptr<puntoexe::imebra::handlers::readingDataHandlerNumericBase> numericDataHandler = std::dynamic_pointer_cast<puntoexe::imebra::handlers::readingDataHandlerNumericBase>(m_pDataHandler);
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

WritingDataHandler::WritingDataHandler(std::shared_ptr<puntoexe::imebra::handlers::writingDataHandler> pDataHandler): m_pDataHandler(pDataHandler)
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


void WritingDataHandler::setDate(const int index, const Date& date)
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
}

void WritingDataHandler::setAge(const size_t index, const Age& age)
{
    m_pDataHandler->setAge(index, age.age, age.units);
}

void WritingDataHandler::setSignedLong(const int index, const int value)
{
    m_pDataHandler->setSignedLong(index, value);
}

void WritingDataHandler::setUnsignedLong(const int index, const unsigned int value)
{
    m_pDataHandler->setUnsignedLong(index, value);
}

void WritingDataHandler::setDouble(const int index, const double value)
{
    m_pDataHandler->setDouble(index, value);
}

void WritingDataHandler::setString(const int index, const std::wstring& value)
{
    m_pDataHandler->setUnicodeString(index, value);
}

void WritingDataHandler::assign(const char *buffer, const size_t bufferSize)
{
    std::shared_ptr<puntoexe::imebra::handlers::writingDataHandlerNumericBase> numericDataHandler = std::dynamic_pointer_cast<puntoexe::imebra::handlers::writingDataHandlerNumericBase>(m_pDataHandler);
    if(numericDataHandler == 0)
    {
        return;
    }

    numericDataHandler->getMemory()->assign((std::uint8_t*) buffer, bufferSize);
}

char* WritingDataHandler::data(size_t* pDataSize) const
{
    std::shared_ptr<puntoexe::imebra::handlers::writingDataHandlerNumericBase> numericDataHandler = std::dynamic_pointer_cast<puntoexe::imebra::handlers::writingDataHandlerNumericBase>(m_pDataHandler);
    if(numericDataHandler == 0)
    {
        *pDataSize = 0;
        return 0;
    }
    *pDataSize = numericDataHandler->getMemorySize();
    return (char*)numericDataHandler->getMemoryBuffer();

}


}
