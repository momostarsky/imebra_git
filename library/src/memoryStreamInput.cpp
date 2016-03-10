/*
$fileHeader$
*/

#include "../include/imebra/memoryStreamInput.h"

#include "../implementation/memoryStreamImpl.h"
#include <memory>

namespace imebra
{

MemoryStreamInput::MemoryStreamInput(const ReadMemory& memory): BaseStreamInput(std::make_shared<implementation::memoryStreamInput>(memory.m_pMemory))
{
}

MemoryStreamInput::MemoryStreamInput(const ReadWriteMemory& memory): BaseStreamInput(std::make_shared<implementation::memoryStreamInput>(memory.m_pMemory))
{
}

MemoryStreamInput::MemoryStreamInput(const MemoryStreamInput& right): BaseStreamInput(right.m_pStream)
{
}

MemoryStreamInput& MemoryStreamInput::operator=(const MemoryStreamInput& right)
{
    m_pStream = right.m_pStream;
    return *this;
}

}
