/*
$fileHeader$
*/

#include "../include/imebra/memoryStreamInput.h"
#include "../include/imebra/readMemory.h"
#include "../include/imebra/readWriteMemory.h"
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

}
