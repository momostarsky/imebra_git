#include <imebra/imebra.h>
#include <gtest/gtest.h>
#include <thread>
#include <functional>

namespace imebra
{

namespace tests
{

void feedDataThread(Pipe& source, size_t maxBlockBytes, unsigned int delayMs, unsigned int closeWait)
{
    for(size_t blockBytes(1); blockBytes != maxBlockBytes; ++blockBytes)
    {

        std::vector<std::uint8_t> values(blockBytes);
        for(size_t resetBlock(0); resetBlock != blockBytes; ++resetBlock)
        {
            values[resetBlock] = (std::uint8_t)(resetBlock & 0xff);
        }
        ReadMemory block((char*)values.data(), blockBytes);
        source.feed(block);
        if(delayMs != 0)
        {
            ::usleep(delayMs * 1000);
        }
    }
    source.close(closeWait);
}

TEST(pipeTest, sendReceive)
{
    Pipe source(1024);

    size_t maxBlockBytes(3000);
    std::thread feedData(imebra::tests::feedDataThread, std::ref(source), maxBlockBytes, 0, 1000);

    std::string buffer;

    ReadWriteMemory block(maxBlockBytes);

    for(size_t blockBytes(1); blockBytes != maxBlockBytes; ++blockBytes)
    {
        while(buffer.size() < blockBytes)
        {
            size_t dataSize(source.sink(block));
            size_t dummy;
            const char* pData(block.data(&dummy));
            buffer.append(pData, dataSize);

        }
        for(size_t checkBlock(0); checkBlock != blockBytes; ++checkBlock)
        {
            ASSERT_EQ((std::uint8_t)(checkBlock & 0xff), (std::uint8_t)(buffer[checkBlock]));
        }
        buffer.erase(0, blockBytes);
    }
    feedData.join();
}


TEST(pipeTest, sendReceiveCloseAndWait)
{
    Pipe source(1024);

    size_t maxBlockBytes(5);
    std::thread feedData(imebra::tests::feedDataThread, std::ref(source), maxBlockBytes, 0, 10000);

    std::string buffer;

    ReadWriteMemory block(maxBlockBytes);

    for(size_t blockBytes(1); blockBytes != maxBlockBytes; ++blockBytes)
    {
        ::usleep(1000000);
        while(buffer.size() < blockBytes)
        {
            size_t dataSize(source.sink(block));
            size_t dummy;
            const char* pData(block.data(&dummy));
            buffer.append(pData, dataSize);

        }
        for(size_t checkBlock(0); checkBlock != blockBytes; ++checkBlock)
        {
            ASSERT_EQ((std::uint8_t)(checkBlock & 0xff), (std::uint8_t)(buffer[checkBlock]));
        }
        buffer.erase(0, blockBytes);
    }
    feedData.join();
}


TEST(pipeTest, sendReceiveCloseNoWait)
{
    Pipe source(1024);

    size_t maxBlockBytes(5);
    std::thread feedData(imebra::tests::feedDataThread, std::ref(source), maxBlockBytes, 0, 0);

    std::string buffer;

    ReadWriteMemory block(maxBlockBytes);

    try
    {
        for(size_t blockBytes(1); blockBytes != maxBlockBytes; ++blockBytes)
        {
            ::usleep(5000000);
            while(buffer.size() < blockBytes)
            {
                size_t dataSize(source.sink(block));
                size_t dummy;
                const char* pData(block.data(&dummy));
                buffer.append(pData, dataSize);

            }
            for(size_t checkBlock(0); checkBlock != blockBytes; ++checkBlock)
            {
                ASSERT_EQ((std::uint8_t)(checkBlock & 0xff), (std::uint8_t)(buffer[checkBlock]));
            }
            buffer.erase(0, blockBytes);
        }
        EXPECT_TRUE(false);
    }
    catch(const imebra::StreamEOFError&)
    {
        EXPECT_TRUE(true);
    }
    catch(...)
    {
        EXPECT_TRUE(false);
    }

    feedData.join();
}

} // namespace tests

} // namespace imebra
