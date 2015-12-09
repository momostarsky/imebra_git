/*
$fileHeader$
*/

/*! \file memory_swig.cpp
    \brief Implementation of the Memory class for SWIG.

*/

#include "../include/imebra/memory.h"
#include "../implementation/memoryImpl.h"
#include <cstring>

Memory::Memory(): m_pMemory(new puntoexe::memory())
{}

Memory::Memory(int requestedSize): m_pMemory(puntoexe::memoryPool::getMemoryPool()->getMemory((imbxUint32)requestedSize))
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

void Memory::resize(int newSize)
{
    m_pMemory->resize((imbxUint32)newSize);
}

void Memory::reserve(int reserveSize)
{
    m_pMemory->reserve((imbxUint32)reserveSize);
}

int Memory::size()
{
    return (int)m_pMemory->size();
}

size_t Memory::data(char* bufferOut, int bufferSize)
{
    size_t memorySize = (size_t)m_pMemory->size();
    if(memorySize == 0)
    {
       return 0;
    }
    if((size_t)bufferSize >= memorySize)
    {
        ::memcpy(bufferOut, m_pMemory->data(), memorySize);
    }
    return memorySize;
}

void Memory::assign(char* buffer, int bufferSize)
{
    m_pMemory->assign((imbxUint8*)buffer, (size_t)bufferSize);
}


bool Memory::empty()
{
    return m_pMemory->empty();
}

void MemoryPool::flush()
{
    puntoexe::memoryPool::getMemoryPool()->flush();
}



