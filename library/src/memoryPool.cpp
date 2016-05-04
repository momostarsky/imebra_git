#include "../include/imebra/memoryPool.h"

#include "../implementation/memoryImpl.h"

namespace imebra
{

void MemoryPool::flush()
{
    implementation::memoryPoolGetter::getMemoryPoolLocal().flush();
}

size_t MemoryPool::getUnusedMemorySize()
{
    return implementation::memoryPoolGetter::getMemoryPoolLocal().getUnusedMemorySize();
}

void MemoryPool::setMemoryPoolSize(size_t minMemoryBlockSize, size_t maxMemoryPoolSize)
{
    implementation::memoryPoolGetter::getMemoryPoolLocal().setMinMaxMemory(minMemoryBlockSize, maxMemoryPoolSize);
}

}
