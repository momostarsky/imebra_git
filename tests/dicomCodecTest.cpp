#include <imebra/imebra.h>
#include "buildImageForTest.h"
#include <gtest/gtest.h>


namespace imebra
{

namespace tests
{

Image* makeTestImage()
{
    std::uint32_t width = 301;
    std::uint32_t height = 201;
    std::unique_ptr<Image> dicomImage(new Image(width, height, bitDepth_t::depthU16, "RGB", 15));

    std::unique_ptr<WritingDataHandler> imageHandler(dicomImage->getWritingDataHandler());

	// Make 3 bands (RGB)
	size_t pointer(0);
	for(std::uint32_t y=0; y<height; ++y)
	{
		for(std::uint32_t x=0; x<width; ++x)
		{
			std::int32_t r, g, b;
			std::uint32_t value = y * 255 / height;
			r = g = 0;
			b = value;
			if(x < width - width/3)
			{
				r = 0;
				g = value;
				b = 0;
			}
			if(x < width / 3)
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
    return dicomImage.release();
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
                    bitDepth_t depth(sign == 0 ? bitDepth_t::depthU8 : bitDepth_t::depthS8);
					if(highBit > 7)
					{
                        depth = (sign == 0 ? bitDepth_t::depthU16 : bitDepth_t::depthS16);
					}
					if(highBit > 15)
					{
                        depth = (sign == 0 ? bitDepth_t::depthU32 : bitDepth_t::depthS32);
					}

                    std::unique_ptr<Image> dicomImage0(buildImageForTest(
                            301,
                            201,
							depth,
							highBit,
							30,
							20,
                            "RGB",
                            1));
                    std::unique_ptr<Image> dicomImage1(buildImageForTest(
                            301,
                            201,
							depth,
							highBit,
							30,
							20,
                            "RGB",
							100));
                    std::unique_ptr<Image> dicomImage2(buildImageForTest(
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

                    ReadWriteMemory streamMemory;
					{
                        DataSet testDataSet;
                        std::unique_ptr<WritingDataHandler> writingDataHandler(testDataSet.getWritingDataHandler(TagId(0x0010, 0x0010), 0));
                        writingDataHandler->setString(0, "AAAaa");
                        writingDataHandler->setString(1, "BBBbbb");
                        writingDataHandler->setString(2, "");
                        writingDataHandler.reset();
                        testDataSet.setUnsignedLong(TagId(imebra::tagId_t::PlanarConfiguration_0028_0006), interleaved);
                        testDataSet.setImage(0, *dicomImage0, transferSyntax, imageQuality_t::veryHigh);
                        testDataSet.setImage(1, *dicomImage1, transferSyntax, imageQuality_t::veryHigh);
                        testDataSet.setImage(2, *dicomImage2, transferSyntax, imageQuality_t::veryHigh);

                        MemoryStreamOutput writeStream(streamMemory);
                        StreamWriter writer(writeStream);
                        CodecFactory::save(testDataSet, writer, codecType_t::dicom);
					}

                    MemoryStreamInput readStream(streamMemory);
                    StreamReader reader(readStream);
                    std::unique_ptr<DataSet> testDataSet(CodecFactory::load(reader, 1));

                    EXPECT_EQ(std::string("AAAaa"), testDataSet->getString(TagId(imebra::tagId_t::PatientName_0010_0010), 0));
                    EXPECT_EQ(std::string("BBBbbb"), testDataSet->getString(TagId(imebra::tagId_t::PatientName_0010_0010), 1));
                    EXPECT_EQ(std::string(""), testDataSet->getString(TagId(imebra::tagId_t::PatientName_0010_0010), 2));
                    EXPECT_EQ(interleaved, testDataSet->getSignedLong(TagId(imebra::tagId_t::PlanarConfiguration_0028_0006), 0));

                    std::unique_ptr<Image> checkImage0(testDataSet->getImage(0));
                    std::unique_ptr<Image> checkImage1(testDataSet->getImage(1));
                    std::unique_ptr<Image> checkImage2(testDataSet->getImage(2));

                    ASSERT_TRUE(compareImages(*checkImage0, *dicomImage0) < 0.0001);
                    ASSERT_TRUE(compareImages(*checkImage1, *dicomImage1) < 0.0001);
                    ASSERT_TRUE(compareImages(*checkImage2, *dicomImage2) < 0.0001);
				}
			}
		}
	} // transferSyntaxId
}


} // namespace tests

} // namespace imebra

