#include <imebra/imebra.h>
#include "buildImageForTest.h"
#include <gtest/gtest.h>

namespace imebra
{

namespace tests
{

TEST(drawBitmapTest, testDrawBitmap)
{
	for(int monochrome(0); monochrome != 2; ++monochrome)
	{
		for(int subsample = 1; subsample != 4; subsample <<= 1)
		{
            Image testImage(buildImageForTest(
                    401,
                    301,
                    bitDepth_t::depthU8,
					7,
                    401,
                    301,
                    monochrome == 1 ? "MONOCHROME2" :
                                      "RGB",
					50));

            DataSet testDataSet;
            testDataSet.setImage(0, testImage, "1.2.840.10008.1.2", imageQuality_t::high);

            DrawBitmap testDraw;
            ReadWriteMemory bitmapBuffer(testDraw.getBitmap(testImage, drawBitmapType_t::drawBitmapRGB, 1));
            size_t bufferSize;
            char* pBuffer(bitmapBuffer.data(&bufferSize));

            ReadingDataHandler imageHandler = testImage.getReadingDataHandler();

            std::uint32_t red, green, blue;
            size_t index(0);
            for(int scanY = 0; scanY != testImage.getHeight(); ++scanY)
			{
                for(int scanX = 0; scanX != testImage.getWidth(); ++scanX)
				{
                    if(monochrome)
                    {
                        red = imageHandler.getUnsignedLong(index++);
                        green = blue = red;
                    }
                    else
                    {
                        red = imageHandler.getUnsignedLong(index++);
                        green = imageHandler.getUnsignedLong(index++);
                        blue = imageHandler.getUnsignedLong(index++);
                    }

					std::uint8_t displayRed(*pBuffer++);
					std::uint8_t displayGreen(*pBuffer++);
					std::uint8_t displayBlue(*pBuffer++);
                    EXPECT_EQ(red, displayRed);
                    EXPECT_EQ(green, displayGreen);
                    EXPECT_EQ(blue, displayBlue);
				}

			}
		}
	}

}


} // namespace tests

} // namespace imebra
