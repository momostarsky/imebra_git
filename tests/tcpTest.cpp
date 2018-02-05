#include <imebra/imebra.h>
#include <gtest/gtest.h>
#include <iostream>
#include <thread>

namespace imebra
{

namespace tests
{

void sendDataThread(unsigned long maxConnections, std::string port)
{
    TCPActiveAddress connectToAddress("", port);

    for(unsigned long connectionNumber(0); connectionNumber != maxConnections; ++connectionNumber)
    {
        TCPStream newStream(connectToAddress);

        DataSet dataSet("1.2.840.10008.1.2.1");
        dataSet.setUnsignedLong(TagId(11, 11), connectionNumber, tagVR_t::UL);

        std::this_thread::sleep_for(std::chrono::seconds(5));

        StreamWriter writer(newStream);
        CodecFactory::save(dataSet, writer, codecType_t::dicom);
    }
}

TEST(tcpTest, sendReceive)
{
    const std::string listeningPort("20000");

    TCPPassiveAddress listeningAddress("", listeningPort);

    TCPListener listener(listeningAddress);

    unsigned long maxConnections(10);

    std::thread sendDataThread(imebra::tests::sendDataThread, maxConnections, listeningPort);

    for(unsigned long connectionNumber(0); connectionNumber != maxConnections; ++connectionNumber)
    {
        std::unique_ptr<TCPStream> newStream(listener.waitForConnection());

        StreamReader reader(*newStream);
        std::unique_ptr<DataSet> pDataSet(CodecFactory::load(reader));

        ASSERT_EQ(connectionNumber, pDataSet->getUnsignedLong(TagId(11, 11), 0));
    }

    sendDataThread.join();
}

void AcceptConnectionAndCloseThread(std::string port)
{
    TCPPassiveAddress listeningAddress("", port);

    TCPListener listener(listeningAddress);

    std::unique_ptr<TCPStream> newStream(listener.waitForConnection());

}

TEST(tcpTest, prematureClose)
{
    const std::string listeningPort("20000");

    std::thread acceptConnectionAndCloseThread(imebra::tests::AcceptConnectionAndCloseThread, listeningPort);

    std::this_thread::sleep_for(std::chrono::seconds(5));

    TCPActiveAddress connectToAddress("", listeningPort);

    TCPStream newStream(connectToAddress);

    std::this_thread::sleep_for(std::chrono::seconds(5));

    DataSet dataSet("1.2.840.10008.1.2.1");
    dataSet.setUnsignedLong(TagId(11, 11), 1, tagVR_t::UL);

    StreamWriter writer(newStream);

    try
    {
        for(int iterations(0); iterations != 100; ++iterations)
        {
            CodecFactory::save(dataSet, writer, codecType_t::dicom);
        }
        EXPECT_TRUE(false);
    }
    catch(const StreamClosedError&)
    {
        EXPECT_TRUE(true);
    }
    catch(...)
    {
        EXPECT_TRUE(false);
    }

    acceptConnectionAndCloseThread.join();
}


TEST(tcpTest, refusedConnection)
{
    TCPActiveAddress connectToAddress("", "20000");

    TCPStream newStream(connectToAddress);

    std::this_thread::sleep_for(std::chrono::seconds(5));

    DataSet dataSet("1.2.840.10008.1.2.1");
    dataSet.setUnsignedLong(TagId(11, 11), 1, tagVR_t::UL);

    StreamWriter writer(newStream);

    try
    {
        CodecFactory::save(dataSet, writer, codecType_t::dicom);
        EXPECT_TRUE(false);
    }
    catch(const TCPConnectionRefused&)
    {
        EXPECT_TRUE(true);
    }
    catch(const StreamClosedError&)
    {
        EXPECT_TRUE(true);
    }
    catch(const StreamError& e)
    {
        std::cout << "Caught wrong exception: " << e.what();
        EXPECT_TRUE(false);
    }

}



} // namespace tests

} // namespace imebra
