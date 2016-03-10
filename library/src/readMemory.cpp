#include "../include/imebra/readMemory.h"
#include "../implementation/memoryImpl.h"

namespace imebra
{

ReadMemory::ReadMemory(): m_pMemory(std::make_shared<const implementation::memory>())
{
}

ReadMemory::ReadMemory(const char* buffer, size_t bufferSize):
    m_pMemory(std::make_shared<const implementation::memory>(new implementation::stringUint8((const std::uint8_t*)buffer, bufferSize)))
{
}

ReadMemory::ReadMemory(const ReadMemory &right): m_pMemory(right.m_pMemory)
{
}

ReadMemory::ReadMemory(std::shared_ptr<const implementation::memory> pMemory): m_pMemory(pMemory)
{
}

ReadMemory::~ReadMemory()
{
}

ReadMemory& ReadMemory::operator=(const ReadMemory& right)
{
    m_pMemory = right.m_pMemory;
    return *this;
}

size_t ReadMemory::size() const
{
    return m_pMemory->size();
}

const char* ReadMemory::data() const
{
    return (const char*)(m_pMemory->data());
}

bool ReadMemory::empty() const
{
    return m_pMemory->empty();
}

}
