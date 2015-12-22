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

DataHandler::DataHandler(const DataHandler& right) : m_pDataHandler(right.m_pDataHandler)
{}

DataHandler& DataHandler::operator=(const DataHandler& right)
{
    m_pDataHandler = right.m_pDataHandler;
    return *this;
}

DataHandler::DataHandler(std::shared_ptr<puntoexe::imebra::handlers::dataHandler> pDataHandler): m_pDataHandler(pDataHandler)
{}

void DataHandler::close()
{
    m_pDataHandler.reset();
}

bool DataHandler::pointerIsValid(const size_t index) const
{
    return m_pDataHandler->pointerIsValid((const imbxUint32)index);
}

void DataHandler::setSize(const size_t elementsNumber)
{
    m_pDataHandler->setSize((const imbxUint32)elementsNumber);
}

size_t DataHandler::getSize() const
{
    return (size_t)(m_pDataHandler->getSize());
}

size_t DataHandler::getUnitSize() const
{
    return (size_t)(m_pDataHandler->getUnitSize());
}

std::string DataHandler::getDataType() const
{
    return m_pDataHandler->getDataType();
}

char DataHandler::getPaddingByte() const
{
    return (char)(m_pDataHandler->getPaddingByte());
}

int DataHandler::getSignedLong(const int index) const
{
    return (int)(m_pDataHandler->getSignedLong((const imbxUint32)index));
}

int DataHandler::getUnsignedLong(const int index) const
{
    return (int)(m_pDataHandler->getUnsignedLong((const imbxUint32)index));
}

double DataHandler::getDouble(const int index) const
{
    return m_pDataHandler->getDouble((const imbxUint32)index);
}

std::wstring DataHandler::getString(const int index) const
{
    return m_pDataHandler->getUnicodeString((const imbxUint32)index);
}

void DataHandler::getDate(const int index,
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

void DataHandler::setDate(const int index,
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

void DataHandler::setSignedLong(const int index, const int value)
{
    m_pDataHandler->setSignedLong((imbxUint32)index, (imbxInt32)value);
}

void DataHandler::setUnsignedLong(const int index, const int value)
{
    m_pDataHandler->setUnsignedLong((imbxUint32)index, (imbxUint32)value);
}

void DataHandler::setDouble(const int index, const double value)
{
    m_pDataHandler->setDouble((imbxUint32)index, value);
}

void DataHandler::setString(const int index, const std::wstring& value)
{
    m_pDataHandler->setUnicodeString((imbxUint32)index, value);
}

Memory DataHandler::getMemory()
{
    std::shared_ptr<puntoexe::imebra::handlers::dataHandlerNumericBase> pDataHandler(std::dynamic_pointer_cast<puntoexe::imebra::handlers::dataHandlerNumericBase>(m_pDataHandler));
    if(pDataHandler == 0)
    {
        return Memory();
    }
    return Memory(pDataHandler->getMemory());
}

}
