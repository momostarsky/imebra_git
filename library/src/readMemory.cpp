#include "../include/imebra/readMemory.h"
#include "../implementation/memoryImpl.h"
#include <memory.h>

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

const char* ReadMemory::data(size_t* pDataSize) const
{
    *pDataSize = m_pMemory->size();
    return (char*)m_pMemory->data();
}

size_t ReadMemory::data(char* destination, size_t destinationSize) const
{
    size_t memorySize = m_pMemory->size();
    if(destination != 0 && destinationSize >= memorySize && memorySize != 0)
    {
        ::memcpy(destination, m_pMemory->data(), memorySize);
    }
    return memorySize;
}

bool ReadMemory::empty() const
{
    return m_pMemory->empty();
}

}
