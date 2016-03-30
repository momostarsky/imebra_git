/*
$fileHeader$
*/

/*! \file dataHandlerNumeric.cpp
    \brief Implementation of the handler for the numeric tags.

*/

#include "dataHandlerNumericImpl.h"
#include "memoryImpl.h"
#include "bufferImpl.h"

namespace imebra
{

namespace implementation
{

namespace handlers
{

readingDataHandlerNumericBase::readingDataHandlerNumericBase(const std::shared_ptr<const memory>& parseMemory, tagVR_t dataType):
    readingDataHandler(dataType), m_pMemory(parseMemory)
{
}

const std::uint8_t* readingDataHandlerNumericBase::getMemoryBuffer() const
{
    IMEBRA_FUNCTION_START();

    return m_pMemory->data();

    IMEBRA_FUNCTION_END();
}

size_t readingDataHandlerNumericBase::getMemorySize() const
{
    IMEBRA_FUNCTION_START();

    return m_pMemory->size();

    IMEBRA_FUNCTION_END();
}

std::shared_ptr<const memory> readingDataHandlerNumericBase::getMemory() const
{
    IMEBRA_FUNCTION_START();

    return m_pMemory;

    IMEBRA_FUNCTION_END();
}

writingDataHandlerNumericBase::writingDataHandlerNumericBase(const std::shared_ptr<buffer> &pBuffer, const size_t initialSize, tagVR_t dataType, size_t unitSize, bool bIsSigned):
    writingDataHandler(pBuffer, dataType, 0), m_pMemory(std::make_shared<memory>(initialSize * unitSize)), m_unitSize(unitSize), m_bIsSigned(bIsSigned)
{
}

size_t writingDataHandlerNumericBase::getSize() const
{
    IMEBRA_FUNCTION_START();

    return m_pMemory->size() / m_unitSize;

    IMEBRA_FUNCTION_END();
}

std::shared_ptr<memory> writingDataHandlerNumericBase::getMemory() const
{
    return m_pMemory;
}

// Set the buffer's size, in data elements
///////////////////////////////////////////////////////////
void writingDataHandlerNumericBase::setSize(const size_t elementsNumber)
{
    IMEBRA_FUNCTION_START();

    m_pMemory->resize(elementsNumber * m_unitSize);

    IMEBRA_FUNCTION_END();
}

bool writingDataHandlerNumericBase::isSigned() const
{
    IMEBRA_FUNCTION_START();

    return m_bIsSigned;

    IMEBRA_FUNCTION_END();
}

size_t writingDataHandlerNumericBase::getUnitSize() const
{
    IMEBRA_FUNCTION_START();

    return m_unitSize;

    IMEBRA_FUNCTION_END();
}


writingDataHandlerNumericBase::~writingDataHandlerNumericBase()
{
    if(m_buffer != 0)
    {
        // The buffer's size must be an even number
        ///////////////////////////////////////////////////////////
        size_t memorySize = m_pMemory->size();
        if((memorySize & 0x1) != 0)
        {
            m_pMemory->resize(++memorySize);
            *(m_pMemory->data() + (memorySize - 1)) = m_paddingByte;
        }

        m_buffer->commit(m_pMemory);
    }
}

std::uint8_t* writingDataHandlerNumericBase::getMemoryBuffer() const
{
    IMEBRA_FUNCTION_START();

    return m_pMemory->data();

    IMEBRA_FUNCTION_END();
}

size_t writingDataHandlerNumericBase::getMemorySize() const
{
    IMEBRA_FUNCTION_START();

    return m_pMemory->size();

    IMEBRA_FUNCTION_END();
}



}

}

}
