#include <imebra/image.h>
#include <imebra/definitions.h>
#include <imebra/dataSet.h>

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
    Image testImage0(buildImageForTest(
		400, 
		300, 
        imebra::Image::bitDepth::depthU8,
		7, 
		400, 
		300, 
        "RGB",
		50));

    Image testImage1(buildImageForTest(
		400, 
		300, 
        imebra::Image::bitDepth::depthU8,
		7, 
		400, 
		300, 
        "RGB",
		20));

    imebra::DataSet testDataSet;
    testDataSet.setImage(0, testImage0, "1.2.840.10008.1.2.4.70", imageQuality_t::high);
    testDataSet.setImage(1, testImage1, "1.2.840.10008.1.2.4.70", imageQuality_t::high);

    // Verify the two images
    imebra::Image verifyImage0 = testDataSet.getImage(0);
    ASSERT_TRUE(compareImages(testImage0, verifyImage0) < 0.000001);
    imebra::Image verifyImage1 = testDataSet.getImage(1);
    ASSERT_TRUE(compareImages(testImage1, verifyImage1) < 0.000001);

    {
        std::uint32_t offset(0);
        WritingDataHandler offsetHandler = testDataSet.getWritingDataHandler(0x7fe0, 0, 0x0010, 0, "OB");

        std::list<WritingDataHandler> handlers;

        // Get the images 1 & 2, fragment them
        //////////////////////////////////////
        for(std::uint32_t scanBuffers = 1; scanBuffers != 3; ++scanBuffers)
        {
            size_t dataSize;
            offsetHandler.setSize(sizeof(std::uint32_t) * scanBuffers);
            std::uint32_t* pOffsetMemory = (std::uint32_t*)offsetHandler.data(&dataSize);
            pOffsetMemory[scanBuffers - 1] = offset;
            //streamController::adjustEndian((std::uint8_t*)&(pOffsetMemory[scanBuffers - 1]), sizeof(pOffsetMemory[0]), streamController::lowByteEndian, 1);

            imebra::ReadingDataHandler wholeHandler = testDataSet.getReadingDataHandler(0x7fe0, 0, 0x0010, scanBuffers);
            size_t totalSize;
            const char* pWholeMemory = wholeHandler.data(&totalSize);
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
                WritingDataHandler newHandler = testDataSet.getWritingDataHandler(0x7fe0, 0, 0x0010, handlers.size() + 1, "OB");
                newHandler.setSize(thisSize);
                newHandler.assign(pWholeMemory, thisSize);
                handlers.push_back(newHandler);
                offset += thisSize + 8;
                totalSize -= thisSize;
                pWholeMemory += thisSize;
            }
        }
    }

    Image compareImage0 = testDataSet.getImage(0);
        ASSERT_TRUE(compareImages(testImage0, compareImage0) < 0.000001);
    Image compareImage1 = testDataSet.getImage(1);
        ASSERT_TRUE(compareImages(testImage1, compareImage1) < 0.000001);
        ASSERT_TRUE(compareImages(testImage0, compareImage1) > 30);
}

} // namespace tests

} // namespace imebra
