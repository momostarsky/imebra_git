/*
$fileHeader$
*/

/*! \file memory_swig.cpp
    \brief Implementation of the Memory class for SWIG.

*/

#include "../include/imebra/memory.h"
#include "../implementation/memoryImpl.h"
#include <cstring>

namespace imebra
{

Memory::Memory(): m_pMemory(new puntoexe::memory())
{}

Memory::Memory(size_t requestedSize): m_pMemory(puntoexe::memoryPool::getMemoryPool()->getMemory((imbxUint32)requestedSize))
{}

Memory::Memory(puntoexe::ptr<puntoexe::memory> pMemory): m_pMemory(pMemory)
{}

void Memory::transfer(Memory& transferFrom)
{
    m_pMemory->transfer(transferFrom.m_pMemory);
}

void Memory::copyFrom(Memory& copyFrom)
{
    m_pMemory->copyFrom(copyFrom.m_pMemory);
}

void Memory::clear()
{
    m_pMemory->clear();
}

void Memory::resize(size_t newSize)
{
    m_pMemory->resize((imbxUint32)newSize);
}

void Memory::reserve(size_t reserveSize)
{
    m_pMemory->reserve((imbxUint32)reserveSize);
}

size_t Memory::size() const
{
    return m_pMemory->size();
}

std::uint8_t* Memory::data() const
{
    return m_pMemory->data();
}

size_t Memory::data(char* bufferOut, size_t bufferSize) const
{
    size_t memorySize = (size_t)m_pMemory->size();
    if(memorySize == 0)
    {
       return 0;
    }
    if(bufferOut != 0 && (size_t)bufferSize >= memorySize)
    {
        ::memcpy(bufferOut, m_pMemory->data(), memorySize);
    }
    return memorySize;
}

void Memory::assign(char* buffer, size_t bufferSize)
{
    m_pMemory->assign((imbxUint8*)buffer, (size_t)bufferSize);
}


bool Memory::empty() const
{
    return m_pMemory->empty();
}

void MemoryPool::flush()
{
    puntoexe::memoryPool::getMemoryPool()->flush();
}

}
