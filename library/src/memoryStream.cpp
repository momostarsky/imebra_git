/*
$fileHeader$
*/

#include "../include/imebra/memoryStream.h"

#include "../implementation/memoryStreamImpl.h"
#include <memory>

namespace imebra
{

MemoryStreamOutput::MemoryStreamOutput(Memory& memory): BaseStreamOutput(std::make_shared<implementation::memoryStreamOutput>(memory.m_pMemory))
{
}

MemoryStreamOutput::MemoryStreamOutput(const MemoryStreamOutput& right): BaseStreamOutput(right.m_pStream)
{
}

MemoryStreamOutput& MemoryStreamOutput::operator=(const MemoryStreamOutput& right)
{
	m_pStream = right.m_pStream;
	return *this;
}

MemoryStreamInput::MemoryStreamInput(const Memory& memory): BaseStreamInput(std::make_shared<implementation::memoryStreamInput>(memory.m_pMemory))
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
