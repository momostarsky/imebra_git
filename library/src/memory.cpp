#include "../include/imebra/memory.h"

#include "../implementation/memoryImpl.h"

namespace imebra
{


Memory::Memory(): m_pMemory(std::make_shared<implementation::memory>())
{
}

Memory::Memory(size_t initialSize): m_pMemory(std::make_shared<implementation::memory>(initialSize))
{
}

Memory::Memory(const char* buffer, size_t bufferSize):
    m_pMemory(std::make_shared<implementation::memory>(new implementation::stringUint8((const std::uint8_t*)buffer, bufferSize)))
{
}

Memory::Memory(std::shared_ptr<implementation::memory> pMemory): m_pMemory(pMemory)
{
}

void Memory::transfer(Memory& transferFrom)
{
    m_pMemory->transfer(transferFrom.m_pMemory);
}

void Memory::copyFrom(const Memory& sourceMemory)
{
    m_pMemory->copyFrom(sourceMemory.m_pMemory);
}

void Memory::clear()
{
    m_pMemory->clear();
}

void Memory::resize(size_t newSize)
{
    m_pMemory->resize(newSize);
}

void Memory::reserve(size_t reserveSize)
{
    m_pMemory->reserve(reserveSize);
}

size_t Memory::size() const
{
    return m_pMemory->size();
}

char* Memory::data()
{
    return (char*)(m_pMemory->data());
}

const char* Memory::data() const
{
    return (const char*)(m_pMemory->data());
}

bool Memory::empty() const
{
    return m_pMemory->empty();
}

void Memory::assign(const char* pSource, const size_t sourceLength)
{
    m_pMemory->assign((const std::uint8_t*)pSource, sourceLength);
}

void MemoryPool::flush()
{
    implementation::memoryPoolGetter::getMemoryPoolLocal().flush();
}

void MemoryPool::setMemoryPoolSize(size_t minMemoryBlockSize, size_t maxMemoryPoolSize)
{
    implementation::memoryPoolGetter::getMemoryPoolLocal().setMinMaxMemory(minMemoryBlockSize, maxMemoryPoolSize);
}

}
