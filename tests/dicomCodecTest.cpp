#include <imebra/imebra.h>
#include "buildImageForTest.h"
#include <gtest/gtest.h>


namespace imebra
{

namespace tests
{

Image makeTestImage()
{
    std::uint32_t sizeX = 301;
    std::uint32_t sizeY = 201;
    Image dicomImage(sizeX, sizeY, bitDepth::depthU16, "RGB", 15);

    WritingDataHandler imageHandler = dicomImage.getWritingDataHandler();

	// Make 3 bands (RGB)
	size_t pointer(0);
	for(std::uint32_t y=0; y<sizeY; ++y)
	{
		for(std::uint32_t x=0; x<sizeX; ++x)
		{
			std::int32_t r, g, b;
			std::uint32_t value = y * 255 / sizeY;
			r = g = 0;
			b = value;
			if(x < sizeX - sizeX/3)
			{
				r = 0;
				g = value;
				b = 0;
			}
			if(x < sizeX / 3)
			{
				r = value;
				g = 0;
				b = 0;
			}
            imageHandler.setUnsignedLong(pointer++, r);
            imageHandler.setUnsignedLong(pointer++, g);
            imageHandler.setUnsignedLong(pointer++, b);
		}
	}
	return dicomImage;
}


// A buffer initialized to a default data type should use the data type OB
TEST(dicomCodecTest, testDicom)
{
    for(int transferSyntaxId(0); transferSyntaxId != 4; ++transferSyntaxId)
	{
		for(int interleaved(0); interleaved != 2; ++interleaved)
		{
			for(unsigned int sign=0; sign != 2; ++sign)
			{
				for(std::uint32_t highBit(0); highBit != 32; ++highBit)
				{
                    bitDepth depth(sign == 0 ? bitDepth::depthU8 : bitDepth::depthS8);
					if(highBit > 7)
					{
                        depth = (sign == 0 ? bitDepth::depthU16 : bitDepth::depthS16);
					}
					if(highBit > 15)
					{
                        depth = (sign == 0 ? bitDepth::depthU32 : bitDepth::depthS32);
					}

                    Image dicomImage0(buildImageForTest(
                            301,
                            201,
							depth,
							highBit,
							30,
							20,
                            "RGB",
                            1));
                    Image dicomImage1(buildImageForTest(
                            301,
                            201,
							depth,
							highBit,
							30,
							20,
                            "RGB",
							100));
                    Image dicomImage2(buildImageForTest(
                            301,
                            201,
							depth,
							highBit,
							30,
							20,
                            "RGB",
							150));

                    std::string transferSyntax;

					switch(transferSyntaxId)
					{
					case 0:
                        transferSyntax = "1.2.840.10008.1.2";
						break;
					case 1:
                        transferSyntax = "1.2.840.10008.1.2.1";
						break;
					case 2:
                        transferSyntax = "1.2.840.10008.1.2.2";
                        break;
                    case 3:
                        transferSyntax = "1.2.840.10008.1.2.5";
						break;
					}

                    std::cout << "Dicom test. Transfer syntax: " << transferSyntax;
                    std::cout << " interleaved: " << interleaved;
                    std::cout << " sign: " << sign;
                    std::cout << " highBit: " << highBit << std::endl;

                    Memory streamMemory;
					{
                        DataSet testDataSet;
                        testDataSet.getWritingDataHandler(0x0010, 0, 0x0010, 0)
                                .setString(0, "AAAaa")
                                .setString(1, "BBBbbb")
                                .setString(2, "");
                        testDataSet.setUnsignedLong(0x0028, 0, 0x0006, 0, interleaved);
                        testDataSet.setImage(0, dicomImage0, transferSyntax, veryHigh);
                        testDataSet.setImage(1, dicomImage1, transferSyntax, veryHigh);
                        testDataSet.setImage(2, dicomImage2, transferSyntax, veryHigh);

                        MemoryStreamOutput writeStream(streamMemory);
                        StreamWriter writer(writeStream);
                        CodecFactory::save(testDataSet, writer, CodecFactory::dicom);
					}

                    MemoryStreamInput readStream(streamMemory);
                    StreamReader reader(readStream);
                    DataSet testDataSet = CodecFactory::load(reader, 2048);

                    EXPECT_EQ(std::string("AAAaa"), testDataSet.getStringThrow(0x0010, 0, 0x0010, 0, 0));
                    EXPECT_EQ(std::string("BBBbbb"), testDataSet.getStringThrow(0x0010, 0, 0x0010, 0, 1));
                    //EXPECT_EQ(std::string(""), testDataSet.getStringThrow(0x0010, 0, 0x0010, 0, 2));
                    EXPECT_EQ(interleaved, testDataSet.getSignedLongThrow(0x0028, 0, 0x0006, 0, 0));

                    Image checkImage0 = testDataSet.getImage(0);
                    Image checkImage1 = testDataSet.getImage(1);
                    Image checkImage2 = testDataSet.getImage(2);

                    ASSERT_TRUE(compareImages(checkImage0, dicomImage0) < 0.0001);
                    ASSERT_TRUE(compareImages(checkImage1, dicomImage1) < 0.0001);
                    ASSERT_TRUE(compareImages(checkImage2, dicomImage2) < 0.0001);
				}
			}
		}
	} // transferSyntaxId
}


} // namespace tests

} // namespace imebra

