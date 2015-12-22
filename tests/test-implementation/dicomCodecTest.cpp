#include "../../library/implementation/imebraImpl.h"
#include "buildImageForTest.h"
#include <gtest/gtest.h>

namespace puntoexe
{

namespace imebra
{

namespace tests
{

std::shared_ptr<image> makeTestImage()
{
    std::uint32_t sizeX = 301;
    std::uint32_t sizeY = 201;
	std::shared_ptr<image> dicomImage(new image);
	dicomImage->create(sizeX, sizeY, image::depthU16, L"RGB", 15);

	std::uint32_t rowSize, channelsPixelSize, channelsNumber;
	std::shared_ptr<handlers::dataHandlerNumericBase> imageHandler = dicomImage->getDataHandler(true, &rowSize, &channelsPixelSize, &channelsNumber);

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
			imageHandler->setUnsignedLong(pointer++, r);
			imageHandler->setUnsignedLong(pointer++, g);
			imageHandler->setUnsignedLong(pointer++, b);
		}
	}
    imageHandler.reset();

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
					puntoexe::imebra::image::bitDepth depth(sign == 0 ? puntoexe::imebra::image::depthU8 : puntoexe::imebra::image::depthS8);
					if(highBit > 7)
					{
						depth = (sign == 0 ? puntoexe::imebra::image::depthU16 : puntoexe::imebra::image::depthS16);
					}
					if(highBit > 15)
					{
						depth = (sign == 0 ? puntoexe::imebra::image::depthU32 : puntoexe::imebra::image::depthS32);
					}

					std::shared_ptr<image> dicomImage0(buildImageForTest(
                            301,
                            201,
							depth,
							highBit,
							30,
							20,
							L"RGB",
                            1));
					std::shared_ptr<image> dicomImage1(buildImageForTest(
                            301,
                            201,
							depth,
							highBit,
							30,
							20,
							L"RGB",
							100));
					std::shared_ptr<image> dicomImage2(buildImageForTest(
                            301,
                            201,
							depth,
							highBit,
							30,
							20,
							L"RGB",
							150));

					std::wstring transferSyntax;

					switch(transferSyntaxId)
					{
					case 0:
						transferSyntax = L"1.2.840.10008.1.2";
						break;
					case 1:
						transferSyntax = L"1.2.840.10008.1.2.1";
						break;
					case 2:
						transferSyntax = L"1.2.840.10008.1.2.2";
                        break;
                    case 3:
                        transferSyntax = L"1.2.840.10008.1.2.5";
						break;
					}

					std::shared_ptr<memory> streamMemory(new memory);
					{
						std::shared_ptr<dataSet> testDataSet(new dataSet);
						testDataSet->setString(0x0010, 0, 0x0010, 0, "AAAaa");
						testDataSet->setString(0x0010, 0, 0x0010, 1, "BBBbbb");
						testDataSet->setString(0x0010, 0, 0x0010, 2, "");
						testDataSet->setUnsignedLong(0x0028, 0x0, 0x0006, 0x0, interleaved);
						testDataSet->setImage(0, dicomImage0, transferSyntax, codecs::codec::veryHigh);
						testDataSet->setImage(1, dicomImage1, transferSyntax, codecs::codec::veryHigh);
						testDataSet->setImage(2, dicomImage2, transferSyntax, codecs::codec::veryHigh);

						std::shared_ptr<memoryStream> writeStream(new memoryStream(streamMemory));

						std::shared_ptr<codecs::dicomCodec> testCodec(new codecs::dicomCodec);
						testCodec->write(std::shared_ptr<streamWriter>(new streamWriter(writeStream)), testDataSet);
					}

					std::shared_ptr<baseStream> readStream(new memoryStream(streamMemory));
					std::shared_ptr<dataSet> testDataSet = codecs::codecFactory::getCodecFactory()->load(std::shared_ptr<streamReader>(new streamReader(readStream)));

                    EXPECT_EQ(std::string("AAAaa"), testDataSet->getString(0x0010, 0, 0x0010, 0));
                    EXPECT_EQ(std::string("BBBbbb"), testDataSet->getString(0x0010, 0, 0x0010, 1));
                    EXPECT_EQ(std::string(""), testDataSet->getString(0x0010, 0, 0x0010, 2));
                    EXPECT_EQ(interleaved, testDataSet->getSignedLong(0x0028, 0, 0x0006, 0));

					std::shared_ptr<image> checkImage0 = testDataSet->getImage(0);
					std::shared_ptr<image> checkImage1 = testDataSet->getImage(1);
					std::shared_ptr<image> checkImage2 = testDataSet->getImage(2);

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

} // namespace puntoexe
