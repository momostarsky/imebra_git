/*
$fileHeader$
*/

/*! \file dataHandlerNumeric.cpp
    \brief Implementation of the handler for the numeric tags.

*/

#include "dataHandlerNumericImpl.h"
#include "memoryImpl.h"
#include "bufferImpl.h"

namespace puntoexe
{

namespace imebra
{

namespace handlers
{

readingDataHandlerNumericBase::readingDataHandlerNumericBase(const std::shared_ptr<const memory>& parseMemory, const std::string& dataType):
    readingDataHandler(dataType), m_pMemory(parseMemory)
{
}

const std::uint8_t* readingDataHandlerNumericBase::getMemoryBuffer() const
{
    return m_pMemory->data();
}

size_t readingDataHandlerNumericBase::getMemorySize() const
{
    return m_pMemory->size();
}

std::shared_ptr<const memory> readingDataHandlerNumericBase::getMemory() const
{
    return m_pMemory;
}

writingDataHandlerNumericBase::writingDataHandlerNumericBase(const std::shared_ptr<buffer> &pBuffer, const size_t initialSize, const std::string &dataType, size_t unitSize):
    writingDataHandler(pBuffer, dataType, 0), m_pMemory(std::make_shared<memory>(initialSize)), m_unitSize(unitSize)
{
}

size_t writingDataHandlerNumericBase::getSize() const
{
    return m_pMemory->size() / m_unitSize;
}

std::shared_ptr<memory> writingDataHandlerNumericBase::getMemory() const
{
    return m_pMemory;
}

// Set the buffer's size, in data elements
///////////////////////////////////////////////////////////
void writingDataHandlerNumericBase::setSize(const size_t elementsNumber)
{
    PUNTOEXE_FUNCTION_START(L"dataHandlerNumeric::setSize");

    m_pMemory->resize(elementsNumber * m_unitSize);

    PUNTOEXE_FUNCTION_END();
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

        m_buffer->commit(m_pMemory, m_dataType);
    }
}

std::uint8_t* writingDataHandlerNumericBase::getMemoryBuffer() const
{
    return m_pMemory->data();
}

size_t writingDataHandlerNumericBase::getMemorySize() const
{
    return m_pMemory->size();
}



}

}

}
