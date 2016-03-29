/*
$fileHeader$
*/

#include "../include/imebra/memoryStreamOutput.h"
#include "../include/imebra/readWriteMemory.h"
#include "../implementation/memoryStreamImpl.h"
#include <memory>

namespace imebra
{

MemoryStreamOutput::MemoryStreamOutput(const ReadWriteMemory& memory):
    BaseStreamOutput(std::make_shared<implementation::memoryStreamOutput>(std::const_pointer_cast<implementation::memory>(memory.m_pMemory)))
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

}
