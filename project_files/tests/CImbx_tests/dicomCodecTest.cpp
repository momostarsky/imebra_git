#include <cppunit/extensions/HelperMacros.h>
#include "dicomCodecTest.h"

#include "../../imebra/include/imebra.h"
#include "buildImageForTest.h"

namespace puntoexe
{

namespace imebra
{

namespace tests
{
CPPUNIT_TEST_SUITE_REGISTRATION(puntoexe::imebra::tests::dicomCodecTest);

ptr<image> dicomCodecTest::makeTestImage()
{
	imbxUint32 sizeX = 601;
	imbxUint32 sizeY = 401;
	ptr<image> dicomImage(new image);
	dicomImage->create(sizeX, sizeY, image::depthU16, L"RGB", 15);

	imbxUint32 rowSize, channelsPixelSize, channelsNumber;
	ptr<handlers::imageHandler> imageHandler = dicomImage->getDataHandler(true, &rowSize, &channelsPixelSize, &channelsNumber);

	// Make 3 bands (RGB)
	for(imbxUint32 y=0; y<sizeY; ++y)
	{
		for(imbxUint32 x=0; x<sizeX; ++x)
		{
			imbxInt32 r, g, b;
			imbxUint32 value = y * 255 / sizeY;
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
			imageHandler->setUnsignedLongIncPointer(r);
			imageHandler->setUnsignedLongIncPointer(g);
			imageHandler->setUnsignedLongIncPointer(b);
		}
	}
	imageHandler.release();

	return dicomImage;
}


// A buffer initialized to a default data type should use the data type OB
void dicomCodecTest::testUncompressedNotInterleaved()
{
	for(int trial(0); trial != 4; ++trial)
	{
		puntoexe::imebra::image::bitDepth depth;
		imbxUint32 highBit;
		switch(trial)
		{
		case 0:
			depth = puntoexe::imebra::image::depthU8;
			highBit = 7;
			break;
		case 1:
			depth = puntoexe::imebra::image::depthS8;
			highBit = 7;
			break;
		case 2:
			depth = puntoexe::imebra::image::depthU16;
			highBit = 15;
			break;
		case 3:
			depth = puntoexe::imebra::image::depthS16;
			highBit = 15;
			break;
		}
		ptr<image> dicomImage0(buildImageForTest(
			601, 
			401, 
			depth,
			highBit, 
			30, 
			20, 
			L"RGB", 
			50));
		ptr<image> dicomImage1(buildImageForTest(
			601, 
			401, 
			depth,
			highBit, 
			30, 
			20, 
			L"RGB", 
			100));
		ptr<image> dicomImage2(buildImageForTest(
			601, 
			401, 
			depth,
			highBit, 
			30, 
			20, 
			L"RGB", 
			150));

		ptr<memory> streamMemory(new memory);
		{
			ptr<dataSet> testDataSet(new dataSet);
			testDataSet->setString(0x0010, 0, 0x0010, 0, "AAAaa");
			testDataSet->setString(0x0010, 0, 0x0010, 1, "BBBbbb");
			testDataSet->setString(0x0010, 0, 0x0010, 2, "");
			testDataSet->setImage(0, dicomImage0, L"1.2.840.10008.1.2.1", codecs::codec::veryHigh);
			testDataSet->setImage(1, dicomImage1, L"1.2.840.10008.1.2.1", codecs::codec::veryHigh);
			testDataSet->setImage(2, dicomImage2, L"1.2.840.10008.1.2.1", codecs::codec::veryHigh);

			ptr<memoryStream> writeStream(new memoryStream(streamMemory));

			ptr<codecs::dicomCodec> testCodec(new codecs::dicomCodec);
			testCodec->write(ptr<streamWriter>(new streamWriter(writeStream)), testDataSet);
		}

		ptr<baseStream> readStream(new memoryStream(streamMemory));
		ptr<dataSet> testDataSet = codecs::codecFactory::getCodecFactory()->load(ptr<streamReader>(new streamReader(readStream)));

		CPPUNIT_ASSERT(testDataSet->getString(0x0010, 0, 0x0010, 0) == "AAAaa");
		CPPUNIT_ASSERT(testDataSet->getString(0x0010, 0, 0x0010, 1) == "BBBbbb");
		CPPUNIT_ASSERT(testDataSet->getString(0x0010, 0, 0x0010, 2) == "");

		ptr<image> checkImage0 = testDataSet->getImage(0);
		ptr<image> checkImage1 = testDataSet->getImage(1);
		ptr<image> checkImage2 = testDataSet->getImage(2);

		CPPUNIT_ASSERT(compareImages(checkImage0, dicomImage0) < 0.0001);
		CPPUNIT_ASSERT(compareImages(checkImage1, dicomImage1) < 0.0001);
		CPPUNIT_ASSERT(compareImages(checkImage2, dicomImage2) < 0.0001);
	}
}


void dicomCodecTest::testRLENotInterleaved()
{
	ptr<image> dicomImage = makeTestImage();
	imbxUint32 sizeX, sizeY;
	dicomImage->getSize(&sizeX, &sizeY);

	imbxUint32 rowSize, channelsPixelSize, channelsNumber;

	ptr<memory> streamMemory(new memory);
	{
		ptr<dataSet> testDataSet(new dataSet);
		testDataSet->setString(0x0010, 0, 0x0010, 0, "AAAaa");
		testDataSet->setString(0x0010, 0, 0x0010, 1, "BBBbbb");
		testDataSet->setImage(0, dicomImage, L"1.2.840.10008.1.2.5", codecs::codec::veryHigh);

		ptr<baseStream> writeStream(new memoryStream(streamMemory));

		ptr<codecs::dicomCodec> testCodec(new codecs::dicomCodec);
		testCodec->write(ptr<streamWriter>(new streamWriter(writeStream)), testDataSet);
	}

	{
		ptr<baseStream> readStream(new memoryStream(streamMemory));
		ptr<dataSet> testDataSet = codecs::codecFactory::getCodecFactory()->load(ptr<streamReader>(new streamReader(readStream)));

		CPPUNIT_ASSERT(testDataSet->getString(0x0010, 0, 0x0010, 0) == "AAAaa");
		CPPUNIT_ASSERT(testDataSet->getString(0x0010, 0, 0x0010, 1) == "BBBbbb");

		ptr<image> checkImage = testDataSet->getImage(0);
		
		imbxUint32 checkSizeX, checkSizeY;
		checkImage->getSize(&checkSizeX, &checkSizeY);

		ptr<handlers::imageHandler> checkHandler = checkImage->getDataHandler(false, &rowSize, &channelsPixelSize, &channelsNumber);
		ptr<handlers::imageHandler> originalHandler = dicomImage->getDataHandler(false, &rowSize, &channelsPixelSize, &channelsNumber);

		// Compare the buffers. A little difference is allowed
		CPPUNIT_ASSERT(checkSizeX == sizeX);
		CPPUNIT_ASSERT(checkSizeY == sizeY);

		for(imbxUint32 checkY = 0; checkY < sizeY; ++checkY)
		{
			for(imbxUint32 checkX = 0; checkX < sizeX; ++checkX)
			{
				for(imbxUint32 channel = 3; channel != 0; --channel)
				{
					imbxInt32 value0 = checkHandler->getUnsignedLongIncPointer();
					imbxInt32 value1 = originalHandler->getUnsignedLongIncPointer();
					CPPUNIT_ASSERT(value0 == value1);
				}
			}
		}
	}

}


} // namespace tests

} // namespace imebra

} // namespace puntoexe