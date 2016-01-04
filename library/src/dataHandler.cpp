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

Age::Age(uint32_t age, ageUnit_t units):
    age(age), units(units)
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
    return (int)(m_pDataHandler->getSignedLong((const imbxUint32)index));
}

int ReadingDataHandler::getUnsignedLong(const int index) const
{
    return (int)(m_pDataHandler->getUnsignedLong((const imbxUint32)index));
}

double ReadingDataHandler::getDouble(const int index) const
{
    return m_pDataHandler->getDouble((const imbxUint32)index);
}

std::wstring ReadingDataHandler::getString(const int index) const
{
    return m_pDataHandler->getUnicodeString((const imbxUint32)index);
}

void ReadingDataHandler::getDate(const int index,
		int* pYear,
		int* pMonth,
		int* pDay,
		int* pHour,
		int* pMinutes,
		int* pSeconds,
		int* pNanoseconds,
		int* pOffsetHours,
		int* pOffsetMinutes) const
{
    imbxInt32 year, month, day, hour, minutes, seconds, nanoseconds, offsetHours, offsetMinutes;
    m_pDataHandler->getDate((imbxUint32)index, &year, &month, &day, &hour, &minutes, &seconds, &nanoseconds, &offsetHours, &offsetMinutes);

    *pYear = (int)year;
    *pMonth = (int)month;
    *pDay = (int)day;
    *pHour = (int)hour;
    *pMinutes = (int)minutes;
    *pSeconds = (int)seconds;
    *pNanoseconds = (int)nanoseconds;
    *pOffsetHours = (int)offsetHours;
    *pOffsetMinutes = (int)offsetMinutes;
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
    m_pDataHandler->setSize((const imbxUint32)elementsNumber);
}

size_t WritingDataHandler::getSize() const
{
    return m_pDataHandler->getSize();
}

std::string WritingDataHandler::getDataType() const
{
    return m_pDataHandler->getDataType();
}


void WritingDataHandler::setDate(const int index,
        int year,
        int month,
        int day,
        int hour,
        int minutes,
        int seconds,
        int nanoseconds,
        int offsetHours,
        int offsetMinutes)
{
    m_pDataHandler->setDate(
        (imbxUint32)index,
        (imbxInt32)year,
        (imbxInt32)month,
        (imbxInt32)day,
        (imbxInt32)hour,
        (imbxInt32)minutes,
        (imbxInt32)seconds,
        (imbxInt32)nanoseconds,
        (imbxInt32)offsetHours,
        (imbxInt32)offsetMinutes);
}

void WritingDataHandler::setAge(const size_t index, const Age& age)
{
    m_pDataHandler->setAge(index, age.age, age.units);
}

void WritingDataHandler::setSignedLong(const int index, const int value)
{
    m_pDataHandler->setSignedLong((imbxUint32)index, (imbxInt32)value);
}

void WritingDataHandler::setUnsignedLong(const int index, const int value)
{
    m_pDataHandler->setUnsignedLong((imbxUint32)index, (imbxUint32)value);
}

void WritingDataHandler::setDouble(const int index, const double value)
{
    m_pDataHandler->setDouble((imbxUint32)index, value);
}

void WritingDataHandler::setString(const int index, const std::wstring& value)
{
    m_pDataHandler->setUnicodeString((imbxUint32)index, value);
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
