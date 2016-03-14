/*
$fileHeader$
*/

/*! \file dataHandler.cpp
    \brief Implementation of the classes ReadingDataHandler & WritingDataHandler.
*/

#include "../include/imebra/readingDataHandlerNumeric.h"
#include "../implementation/dataHandlerImpl.h"
#include "../implementation/dataHandlerNumericImpl.h"
#include <cstring>

namespace imebra
{

ReadingDataHandlerNumeric::ReadingDataHandlerNumeric(std::shared_ptr<implementation::handlers::readingDataHandlerNumericBase> pDataHandler):
    ReadingDataHandler(pDataHandler)
{
}

ReadingDataHandlerNumeric::ReadingDataHandlerNumeric(const ReadingDataHandlerNumeric &right):
    ReadingDataHandler(right)
{
}

ReadingDataHandlerNumeric& ReadingDataHandlerNumeric::operator=(const ReadingDataHandlerNumeric& right)
{
    m_pDataHandler = right.m_pDataHandler;
    return *this;
}

const ReadMemory ReadingDataHandlerNumeric::getMemory() const
{
    std::shared_ptr<imebra::implementation::handlers::readingDataHandlerNumericBase> numericDataHandler = std::dynamic_pointer_cast<imebra::implementation::handlers::readingDataHandlerNumericBase>(m_pDataHandler);
    return ReadMemory(numericDataHandler->getMemory());
}

size_t ReadingDataHandlerNumeric::data(char* destination, size_t destinationSize) const
{
    std::shared_ptr<imebra::implementation::handlers::readingDataHandlerNumericBase> numericDataHandler = std::dynamic_pointer_cast<imebra::implementation::handlers::readingDataHandlerNumericBase>(m_pDataHandler);
    size_t memorySize = numericDataHandler->getMemorySize();
    if(destination != 0 && destinationSize >= memorySize && memorySize != 0)
    {
        ::memcpy(destination, numericDataHandler->getMemoryBuffer(), memorySize);
    }
    return memorySize;
}

const char* ReadingDataHandlerNumeric::data(size_t* pDataSize) const
{
    std::shared_ptr<imebra::implementation::handlers::readingDataHandlerNumericBase> numericDataHandler = std::dynamic_pointer_cast<imebra::implementation::handlers::readingDataHandlerNumericBase>(m_pDataHandler);
    *pDataSize = numericDataHandler->getMemorySize();
    return (const char*)numericDataHandler->getMemoryBuffer();
}

size_t ReadingDataHandlerNumeric::getUnitSize() const
{
    std::shared_ptr<imebra::implementation::handlers::readingDataHandlerNumericBase> numericDataHandler = std::dynamic_pointer_cast<imebra::implementation::handlers::readingDataHandlerNumericBase>(m_pDataHandler);
    return numericDataHandler->getUnitSize();
}

bool ReadingDataHandlerNumeric::isSigned() const
{
    std::shared_ptr<imebra::implementation::handlers::readingDataHandlerNumericBase> numericDataHandler = std::dynamic_pointer_cast<imebra::implementation::handlers::readingDataHandlerNumericBase>(m_pDataHandler);
    return numericDataHandler->isSigned();
}

}
