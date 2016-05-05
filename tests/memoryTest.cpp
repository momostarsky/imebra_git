#include <gtest/gtest.h>
#include <imebra/imebra.h>
#include <thread>
#include <array>

namespace imebra
{

namespace tests
{

void memoryThread(size_t minSize, size_t maxSize)
{
    MemoryPool::setMemoryPoolSize(minSize, maxSize);

    // Wait for the other threads to settle. This is done to
    // check that every thread is using its own private MemoryPool
    // object
    //////////////////////////////////////////////////////////////
    ::sleep(2);


    // Small memory chuncks should not go in the memory pool
    ////////////////////////////////////////////////////////
    {
        ReadWriteMemory memory(1);
        size_t dataSize;
        *memory.data(&dataSize) = 2;
        EXPECT_EQ(1, dataSize);
    }
    ::sleep(2);
    EXPECT_EQ(0, MemoryPool::getUnusedMemorySize());

    // Check that released memory goes into the memory pool
    ///////////////////////////////////////////////////////
    {
        ReadWriteMemory memory(minSize);
        size_t dataSize;
        char* pData = memory.data(&dataSize);
        for(size_t writeMemory(0); writeMemory != dataSize; ++writeMemory)
        {
            *pData = 3;
        }
    }
    ::sleep(2);
    EXPECT_EQ(minSize, MemoryPool::getUnusedMemorySize());
    MemoryPool::flush();
    EXPECT_EQ(0, MemoryPool::getUnusedMemorySize());

    // Release memory and reallocate the same size: it should retrieve
    //  it from the memory pool
    //////////////////////////////////////////////////////////////////
    {
        ReadWriteMemory memory(minSize);
        size_t dataSize;
        char* pData = memory.data(&dataSize);
        for(size_t writeMemory(0); writeMemory != dataSize; ++writeMemory)
        {
            *pData = 3;
        }
    }

    ::sleep(2);
    EXPECT_EQ(minSize, MemoryPool::getUnusedMemorySize());
    {
        ReadWriteMemory retrieveMemory(minSize);
        EXPECT_EQ(0, MemoryPool::getUnusedMemorySize());
    }
    MemoryPool::flush();
    EXPECT_EQ(0, MemoryPool::getUnusedMemorySize());

    // Release more memory than the memory pool can hold. Check how
    // much memory it keeps
    ///////////////////////////////////////////////////////////////
    for(size_t memorySize(minSize), totalAllocated(0); totalAllocated < maxSize + 100; ++memorySize)
    {
        ReadWriteMemory memory(memorySize);
        totalAllocated += memorySize;
    }
    EXPECT_GT(MemoryPool::getUnusedMemorySize(), minSize);
    EXPECT_LE(MemoryPool::getUnusedMemorySize(), maxSize);
}

// Launch several threads each one testing its own MemoryPool object
TEST(memoryTest, testMemoryPool)
{
    std::array<std::unique_ptr<std::thread>, 3> threads;
    for(size_t initializeThreads(0); initializeThreads != threads.size(); ++initializeThreads)
    {
        threads[initializeThreads].reset(new std::thread(memoryThread, 100, 500));
    }

    for(size_t joinThreads(0); joinThreads != threads.size(); ++joinThreads)
    {
        threads[joinThreads]->join();
    }
}



} // namespace tests

} // namespace imebra

