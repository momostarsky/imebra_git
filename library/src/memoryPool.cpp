#include "../include/imebra/memoryPool.h"

#include "../implementation/memoryImpl.h"

namespace imebra
{

void MemoryPool::flush()
{
    implementation::memoryPoolGetter::getMemoryPoolLocal().flush();
}

void MemoryPool::setMemoryPoolSize(size_t minMemoryBlockSize, size_t maxMemoryPoolSize)
{
    implementation::memoryPoolGetter::getMemoryPoolLocal().setMinMaxMemory(minMemoryBlockSize, maxMemoryPoolSize);
}

}
