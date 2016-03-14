/*
$fileHeader$
*/

/*! \file dataHandler.cpp
    \brief Implementation of the classes ReadingDataHandler & WritingDataHandler.
*/

#include "../include/imebra/writingDataHandlerNumeric.h"
#include "../implementation/dataHandlerImpl.h"
#include "../implementation/dataHandlerNumericImpl.h"
#include <cstring>

namespace imebra
{

WritingDataHandlerNumeric::WritingDataHandlerNumeric(std::shared_ptr<implementation::handlers::writingDataHandlerNumericBase> pDataHandler):
    WritingDataHandler(pDataHandler)
{
}

WritingDataHandlerNumeric::WritingDataHandlerNumeric(const WritingDataHandlerNumeric &right):
    WritingDataHandler(right)
{
}

WritingDataHandlerNumeric& WritingDataHandlerNumeric::operator=(const WritingDataHandlerNumeric& right)
{
    m_pDataHandler = right.m_pDataHandler;
    return *this;
}

ReadWriteMemory WritingDataHandlerNumeric::getMemory() const
{
    std::shared_ptr<imebra::implementation::handlers::writingDataHandlerNumericBase> numericDataHandler = std::dynamic_pointer_cast<imebra::implementation::handlers::writingDataHandlerNumericBase>(m_pDataHandler);
    return ReadWriteMemory(numericDataHandler->getMemory());
}

void WritingDataHandlerNumeric::assign(const char* source, size_t sourceSize)
{
    std::shared_ptr<imebra::implementation::handlers::writingDataHandlerNumericBase> numericDataHandler = std::dynamic_pointer_cast<imebra::implementation::handlers::writingDataHandlerNumericBase>(m_pDataHandler);
    numericDataHandler->getMemory()->assign((std::uint8_t*) source, sourceSize);
}

char* WritingDataHandlerNumeric::data(size_t* pDataSize) const
{
    std::shared_ptr<imebra::implementation::handlers::writingDataHandlerNumericBase> numericDataHandler = std::dynamic_pointer_cast<imebra::implementation::handlers::writingDataHandlerNumericBase>(m_pDataHandler);
    *pDataSize = numericDataHandler->getMemorySize();
    return (char*)numericDataHandler->getMemoryBuffer();
}

size_t WritingDataHandlerNumeric::data(char* destination, size_t destinationSize) const
{
    std::shared_ptr<imebra::implementation::handlers::writingDataHandlerNumericBase> numericDataHandler = std::dynamic_pointer_cast<imebra::implementation::handlers::writingDataHandlerNumericBase>(m_pDataHandler);
    size_t memorySize = numericDataHandler->getMemorySize();
    if(destination != 0 && destinationSize >= memorySize && memorySize != 0)
    {
        ::memcpy(destination, numericDataHandler->getMemoryBuffer(), memorySize);
    }
    return memorySize;
}

size_t WritingDataHandlerNumeric::getUnitSize() const
{
    std::shared_ptr<imebra::implementation::handlers::writingDataHandlerNumericBase> numericDataHandler = std::dynamic_pointer_cast<imebra::implementation::handlers::writingDataHandlerNumericBase>(m_pDataHandler);
    return numericDataHandler->getUnitSize();
}

bool WritingDataHandlerNumeric::isSigned() const
{
    std::shared_ptr<imebra::implementation::handlers::writingDataHandlerNumericBase> numericDataHandler = std::dynamic_pointer_cast<imebra::implementation::handlers::writingDataHandlerNumericBase>(m_pDataHandler);
    return numericDataHandler->isSigned();
}

}
