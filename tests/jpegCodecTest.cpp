#include <imebra/imebra.h>
#include <gtest/gtest.h>
#include "buildImageForTest.h"

namespace imebra
{

namespace tests
{

// A buffer initialized to a default data type should use the data type OB
TEST(jpegCodecTest, testBaseline)
{
	for(int precision=0; precision != 2; ++precision)
	{
        std::uint32_t bits = precision == 0 ? 7 : 11;
        std::cout << "Testing baseline jpeg (" << (bits + 1) << " bits)"<< std::endl;

        DataSet dataset;

        std::uint32_t width = 600;
        std::uint32_t height = 400;

        Image baselineImage(buildImageForTest(width, height, precision == 0 ? bitDepth_t::depthU8 : bitDepth_t::depthU16, bits, 30, 20, "RGB", 50));

        Transform colorTransform = ColorTransformsFactory::getTransform("RGB", "YBR_FULL");
        Image ybrImage = colorTransform.allocateOutputImage(baselineImage, width, height);
        colorTransform.runTransform(baselineImage, 0, 0, width, height, ybrImage, 0, 0);

		std::wstring fileName;
		if(precision == 0)
		{
            fileName = L"testDicomLossyJpeg8bit.dcm";
            dataset.setImage(0, ybrImage, "1.2.840.10008.1.2.4.50", imageQuality_t::veryHigh);
		}
		else
		{
			fileName = L"testDicomLossyJpeg12bit.dcm";
            dataset.setImage(0, ybrImage, "1.2.840.10008.1.2.4.51", imageQuality_t::veryHigh);
		}

        CodecFactory::save(dataset, fileName, codecType_t::dicom);

        Image checkImage = dataset.getImage(0);

        std::uint32_t checkWidth(checkImage.getWidth()), checkHeight(checkImage.getHeight());
        colorTransform = ColorTransformsFactory::getTransform("YBR_FULL", "RGB");
        Image rgbImage = colorTransform.allocateOutputImage(checkImage, checkWidth, checkHeight);
        colorTransform.runTransform(checkImage, 0, 0, checkWidth, checkHeight, rgbImage, 0, 0);

		// Compare the buffers. A little difference is allowed
        double differenceRGB = compareImages(baselineImage, rgbImage);
        double differenceYBR = compareImages(ybrImage, checkImage);
        ASSERT_LE(differenceRGB, 5);
        ASSERT_LE(differenceYBR, 1);
	}
}


TEST(jpegCodecTest, testBaselineSubsampled)
{
    for(int subsampledX = 0; subsampledX != 2; ++subsampledX)
    {
        for(int subsampledY = 0; subsampledY != 2; ++subsampledY)
        {
            for(int interleaved = 0; interleaved != 2; ++interleaved)
            {
                std::uint32_t width = 600;
                std::uint32_t height = 400;
                Image baselineImage(buildImageForTest(width, height, bitDepth_t::depthU8, 7, 30, 20, "RGB", 50));

                Transform colorTransform = ColorTransformsFactory::getTransform("RGB", "YBR_FULL");
                Image ybrImage = colorTransform.allocateOutputImage(baselineImage, width, height);
                colorTransform.runTransform(baselineImage, 0, 0, width, height, ybrImage, 0, 0);

                ReadWriteMemory savedJpeg;
                {
                    MemoryStreamOutput saveStream(savedJpeg);
                    StreamWriter writer(saveStream);

                    CodecFactory::saveImage(writer, ybrImage, "1.2.840.10008.1.2.4.50", imageQuality_t::veryHigh, "OB", 8, subsampledX != 0, subsampledY != 0, interleaved != 0, false);
                }

                MemoryStreamInput loadStream(savedJpeg);
                StreamReader reader(loadStream);

                DataSet readDataSet = CodecFactory::load(reader, 0xffff);

                Image checkImage = readDataSet.getImage(0);

                std::uint32_t checkWidth(checkImage.getWidth()), checkHeight(checkImage.getHeight());
                colorTransform = ColorTransformsFactory::getTransform("YBR_FULL", "RGB");
                Image rgbImage = colorTransform.allocateOutputImage(checkImage, checkWidth, checkHeight);
                colorTransform.runTransform(checkImage, 0, 0, checkWidth, checkHeight, rgbImage, 0, 0);

                // Compare the buffers. A little difference is allowed
                double differenceRGB = compareImages(baselineImage, rgbImage);
                double differenceYBR = compareImages(ybrImage, checkImage);
                ASSERT_LE(differenceRGB, 5);
                ASSERT_LE(differenceYBR, 1);
            }
        }
    }
}


TEST(jpegCodecTest, testLossless)
{
    for(int interleaved = 0; interleaved != 2; ++interleaved)
    {
        for(int bits = 8; bits <= 16; bits += 8)
        {
            for(int firstOrderPrediction = 0; firstOrderPrediction != 2; ++firstOrderPrediction)
            {
                for(int b2Complement = 0; b2Complement != 2; ++b2Complement)
                {
                    std::cout <<
                                 "Testing lossless jpeg (" << (bits) <<
                                 " bits, interleaved=" << interleaved <<
                                 ", firstOrderPrediction=" << firstOrderPrediction <<
                                 ", 2complement=" << b2Complement<<
                                 ")"<< std::endl;

                    DataSet dataset;

                    std::uint32_t width = 115;
                    std::uint32_t height = 400;

                    bitDepth_t depth;
                    if(bits <= 8)
                    {
                        depth = (b2Complement == 1) ? bitDepth_t::depthS8 : bitDepth_t::depthU8;
                    }
                    else
                    {
                        depth = (b2Complement == 1) ? bitDepth_t::depthS16 : bitDepth_t::depthU16;
                    }

                    Image image(buildImageForTest(width, height, depth, bits, 30, 20, "RGB", 50));

                    std::string transferSyntax = (firstOrderPrediction == 0) ? "1.2.840.10008.1.2.4.57" : "1.2.840.10008.1.2.4.70";

                    ReadWriteMemory savedJpeg;
                    {
                        DataSet dataSet;
                        dataSet.setImage(0, image, transferSyntax, imageQuality_t::veryHigh);

                        MemoryStreamOutput saveStream(savedJpeg);
                        StreamWriter writer(saveStream);
                        CodecFactory::save(dataSet, writer, codecType_t::dicom);
                    }

                    MemoryStreamInput loadStream(savedJpeg);
                    StreamReader reader(loadStream);

                    DataSet readDataSet = CodecFactory::load(reader, 0xffff);

                    Image checkImage = readDataSet.getImage(0);

                    // Compare the buffers
                    double difference = compareImages(image, checkImage);
                    ASSERT_FLOAT_EQ(difference, 0);

                }
            }
        }
    }
}

} // namespace tests

} // namespace imebra
