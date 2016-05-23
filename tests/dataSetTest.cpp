#include <imebra/imebra.h>

#include "buildImageForTest.h"
#include <list>
#include <string.h>
#include <memory>
#include <gtest/gtest.h>

namespace imebra
{

namespace tests
{

using namespace imebra;

TEST(dataSetTest, testFragmentation)
{
    // Add two images to a dataset, then fragment the first image
    std::unique_ptr<Image> testImage0(buildImageForTest(
		400, 
		300, 
        imebra::bitDepth_t::depthU8,
		7, 
		400, 
		300, 
        "RGB",
		50));

    std::unique_ptr<Image> testImage1(buildImageForTest(
		400, 
		300, 
        imebra::bitDepth_t::depthU8,
		7, 
		400, 
		300, 
        "RGB",
		20));

    imebra::DataSet testDataSet;
    testDataSet.setImage(0, *testImage0, "1.2.840.10008.1.2.4.70", imageQuality_t::high);
    testDataSet.setImage(1, *testImage1, "1.2.840.10008.1.2.4.70", imageQuality_t::high);

    // Verify the two images
    std::unique_ptr<Image> verifyImage0(testDataSet.getImage(0));
    ASSERT_TRUE(compareImages(*testImage0, *verifyImage0) < 0.000001);
    std::unique_ptr<Image> verifyImage1(testDataSet.getImage(1));
    ASSERT_TRUE(compareImages(*testImage1, *verifyImage1) < 0.000001);

    {
        std::uint32_t offset(0);
        std::unique_ptr<WritingDataHandlerNumeric> offsetHandler(testDataSet.getWritingDataHandlerNumeric(TagId(imebra::tagId_t::PixelData_7FE0_0010), 0, tagVR_t::OB));

        std::list<std::shared_ptr<WritingDataHandler> > handlers;

        // Get the images 1 & 2, fragment them
        //////////////////////////////////////
        for(std::uint32_t scanBuffers = 1; scanBuffers != 3; ++scanBuffers)
        {
            size_t dataSize;
            offsetHandler->setSize(sizeof(std::uint32_t) * scanBuffers);
            std::uint32_t* pOffsetMemory = (std::uint32_t*)offsetHandler->data(&dataSize);
            pOffsetMemory[scanBuffers - 1] = offset;

            std::unique_ptr<ReadingDataHandlerNumeric> wholeHandler(testDataSet.getReadingDataHandlerNumeric(TagId(imebra::tagId_t::PixelData_7FE0_0010), scanBuffers));
            size_t totalSize;
            const char* pWholeMemory = wholeHandler->data(&totalSize);
            size_t fragmentedSize = totalSize / 3;
            if(fragmentedSize & 0x1)
            {
                ++fragmentedSize;
            }
            while(totalSize != 0)
            {
                size_t thisSize = totalSize;
                if(thisSize > fragmentedSize)
                {
                    thisSize = fragmentedSize;
                }
                std::shared_ptr<WritingDataHandlerNumeric> newHandler(testDataSet.getWritingDataHandlerNumeric(TagId(imebra::tagId_t::PixelData_7FE0_0010), handlers.size() + 1, tagVR_t::OB));
                newHandler->setSize(thisSize);
                newHandler->assign(pWholeMemory, thisSize);
                handlers.push_back(newHandler);
                offset += thisSize + 8;
                totalSize -= thisSize;
                pWholeMemory += thisSize;
            }
        }
    }

    std::unique_ptr<Image> compareImage0(testDataSet.getImage(0));
        ASSERT_TRUE(compareImages(*testImage0, *compareImage0) < 0.000001);
    std::unique_ptr<Image> compareImage1(testDataSet.getImage(1));
        ASSERT_TRUE(compareImages(*testImage1, *compareImage1) < 0.000001);
        ASSERT_TRUE(compareImages(*testImage0, *compareImage1) > 30);
}


TEST(dataSetTest, testVOIs)
{
    DataSet testDataSet;

    vois_t vois0 = testDataSet.getVOIs();
    ASSERT_TRUE(vois0.empty());

    {
        std::unique_ptr<WritingDataHandler> centerHandler(testDataSet.getWritingDataHandler(TagId(0x0028, 0x1050), 0));
        centerHandler->setDouble(0, 10.4);
        centerHandler->setDouble(1, 20.4);

        std::unique_ptr<WritingDataHandler> widthHandler(testDataSet.getWritingDataHandler(TagId(0x0028, 0x1051), 0));
        widthHandler->setDouble(0, 12.5);
        widthHandler->setDouble(1, 22.5);

        std::unique_ptr<WritingDataHandler> descriptionHandler(testDataSet.getWritingDataHandler(TagId(0x0028, 0x1055), 0));
        descriptionHandler->setUnicodeString(0, L"Test1");
        descriptionHandler->setUnicodeString(1, L"Test2");
    }

    vois_t vois1 = testDataSet.getVOIs();
    ASSERT_EQ(2, vois1.size());
    ASSERT_DOUBLE_EQ(10.4, vois1.at(0).center);
    ASSERT_DOUBLE_EQ(12.5, vois1.at(0).width);
    ASSERT_EQ(L"Test1", vois1.at(0).description);

    ASSERT_DOUBLE_EQ(20.4, vois1.at(1).center);
    ASSERT_DOUBLE_EQ(22.5, vois1.at(1).width);
    ASSERT_EQ(L"Test2", vois1.at(1).description);
}

} // namespace tests

} // namespace imebra
