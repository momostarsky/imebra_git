#include <cppunit/extensions/HelperMacros.h>
#include "jpegCodecTest.h"

#include "../../imebra/include/imebra.h"

namespace puntoexe
{

namespace imebra
{

namespace tests
{

CPPUNIT_TEST_SUITE_REGISTRATION(puntoexe::imebra::tests::jpegCodecTest);


// A buffer initialized to a default data type should use the data type OB
void jpegCodecTest::testBaseline()
{
	imbxUint32 sizeX = 600;
	imbxUint32 sizeY = 400;
	ptr<image> baselineImage(new image);
	baselineImage->create(sizeX, sizeY, image::depthU8, L"RGB", 7);

	imbxUint32 rowSize, channelsPixelSize, channelsNumber;
	ptr<handlers::imageHandler> imageHandler = baselineImage->getDataHandler(true, &rowSize, &channelsPixelSize, &channelsNumber);

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

	ptr<transforms::colorTransforms::colorTransformsFactory> colorFactory;
	colorFactory = transforms::colorTransforms::colorTransformsFactory::getColorTransformsFactory();
	ptr<transforms::transform> colorTransform = colorFactory->getTransform(L"RGB", L"YBR_FULL");
	colorTransform->declareInputImage(0, baselineImage);
	colorTransform->doTransform();
	ptr<image> ybrImage = colorTransform->getOutputImage(0);

	ptr<memory> streamMemory(new memory);
	{
		ptr<baseStream> writeStream(new memoryStream(streamMemory));
		ptr<streamWriter> writer(new streamWriter(writeStream));
		codecs::jpegCodec testCodec;
		testCodec.setImage(writer, ybrImage, L"1.2.840.10008.1.2.4.50", codecs::codec::medium, "OB", 8, false, false, false, false);
	}

	ptr<baseStream> readStream(new memoryStream(streamMemory));
	ptr<streamReader> reader(new streamReader(readStream));
		
	codecs::jpegCodec testCodec;
	ptr<dataSet> readDataSet = testCodec.read(reader);
	ptr<image> checkImage = readDataSet->getImage(0);
	imbxUint32 checkSizeX, checkSizeY;
	checkImage->getSize(&checkSizeX, &checkSizeY);

	colorTransform = colorFactory->getTransform(L"YBR_FULL", L"RGB");
	colorTransform->declareInputImage(0, checkImage);
	colorTransform->doTransform();
	ptr<image> rgbImage = colorTransform->getOutputImage(0);
	ptr<handlers::imageHandler> rgbHandler = rgbImage->getDataHandler(false, &rowSize, &channelsPixelSize, &channelsNumber);
	ptr<handlers::imageHandler> originalHandler = baselineImage->getDataHandler(false, &rowSize, &channelsPixelSize, &channelsNumber);

	// Compare the buffers. A little difference is allowed
	CPPUNIT_ASSERT(checkSizeX == sizeX);
	CPPUNIT_ASSERT(checkSizeY == sizeY);

	imbxUint32 difference = 0;
	for(imbxUint32 checkY = 0; checkY < sizeY; ++checkY)
	{
		for(imbxUint32 checkX = 0; checkX < sizeX; ++checkX)
		{
			for(imbxUint32 channel = 3; channel != 0; --channel)
			{
				imbxInt32 value0 = rgbHandler->getUnsignedLongIncPointer();
				imbxInt32 value1 = originalHandler->getUnsignedLongIncPointer();
				if(value0 > value1)
				{
					difference += value0 - value1;
				}
				else
				{
					difference += value1 - value0;
				}
			}
		}
	}
	CPPUNIT_ASSERT(difference < sizeX * sizeY * 12);

}


void jpegCodecTest::testBaselineSubsampled()
{
	imbxUint32 sizeX = 600;
	imbxUint32 sizeY = 400;
	ptr<image> baselineImage(new image);
	baselineImage->create(sizeX, sizeY, image::depthU8, L"RGB", 7);

	imbxUint32 rowSize, channelsPixelSize, channelsNumber;
	ptr<handlers::imageHandler> imageHandler = baselineImage->getDataHandler(true, &rowSize, &channelsPixelSize, &channelsNumber);

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

	ptr<transforms::colorTransforms::colorTransformsFactory> colorFactory;
	colorFactory = transforms::colorTransforms::colorTransformsFactory::getColorTransformsFactory();
	ptr<transforms::transform> colorTransform = colorFactory->getTransform(L"RGB", L"YBR_FULL");
	colorTransform->declareInputImage(0, baselineImage);
	colorTransform->doTransform();
	ptr<image> ybrImage = colorTransform->getOutputImage(0);

	ptr<memory> streamMemory(new memory);
	{
		ptr<baseStream> writeStream(new memoryStream(streamMemory));
		ptr<streamWriter> writer(new streamWriter(writeStream));

		codecs::jpegCodec testCodec;
		testCodec.setImage(writer, ybrImage, L"1.2.840.10008.1.2.4.50", codecs::codec::medium, "OB", 8, true, true, false, false);
	}

	ptr<baseStream> readStream(new memoryStream(streamMemory));
	ptr<streamReader> reader(new streamReader(readStream));
		
	codecs::jpegCodec testCodec;
	ptr<dataSet> readDataSet = testCodec.read(reader);
	ptr<image> checkImage = readDataSet->getImage(0);
	imbxUint32 checkSizeX, checkSizeY;
	checkImage->getSize(&checkSizeX, &checkSizeY);

	colorTransform = colorFactory->getTransform(L"YBR_FULL", L"RGB");
	colorTransform->declareInputImage(0, checkImage);
	colorTransform->doTransform();
	ptr<image> rgbImage = colorTransform->getOutputImage(0);
	ptr<handlers::imageHandler> rgbHandler = rgbImage->getDataHandler(false, &rowSize, &channelsPixelSize, &channelsNumber);
	ptr<handlers::imageHandler> originalHandler = baselineImage->getDataHandler(false, &rowSize, &channelsPixelSize, &channelsNumber);

	// Compare the buffers. A little difference is allowed
	CPPUNIT_ASSERT(checkSizeX == sizeX);
	CPPUNIT_ASSERT(checkSizeY == sizeY);

	imbxUint32 difference = 0;
	for(imbxUint32 checkY = 0; checkY < sizeY; ++checkY)
	{
		for(imbxUint32 checkX = 0; checkX < sizeX; ++checkX)
		{
			for(imbxUint32 channel = 3; channel != 0; --channel)
			{
				imbxInt32 value0 = rgbHandler->getUnsignedLongIncPointer();
				imbxInt32 value1 = originalHandler->getUnsignedLongIncPointer();
				if(value0 > value1)
				{
					difference += value0 - value1;
				}
				else
				{
					difference += value1 - value0;
				}
			}
		}
	}
	CPPUNIT_ASSERT(difference < sizeX * sizeY * 12);

}

void jpegCodecTest::testLossless()
{
	imbxUint32 sizeX = 115;
	imbxUint32 sizeY = 400;
	ptr<image> baselineImage(new image);
	baselineImage->create(sizeX, sizeY, image::depthU8, L"RGB", 7);

	imbxUint32 rowSize, channelsPixelSize, channelsNumber;
	ptr<handlers::imageHandler> imageHandler = baselineImage->getDataHandler(true, &rowSize, &channelsPixelSize, &channelsNumber);

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

	ptr<memory> streamMemory(new memory);
	{
		ptr<baseStream> writeStream(new memoryStream(streamMemory));
		ptr<streamWriter> writer(new streamWriter(writeStream));
		codecs::jpegCodec testCodec;
		testCodec.setImage(writer, baselineImage, L"1.2.840.10008.1.2.4.57", codecs::codec::medium, "OB", 8, false, false, false, false);
	}

	ptr<baseStream> readStream(new memoryStream(streamMemory));
	ptr<streamReader> reader(new streamReader(readStream));
		
	codecs::jpegCodec testCodec;
	ptr<dataSet> readDataSet = testCodec.read(reader);
	ptr<image> checkImage = readDataSet->getImage(0);
	imbxUint32 checkSizeX, checkSizeY;
	checkImage->getSize(&checkSizeX, &checkSizeY);

	ptr<handlers::imageHandler> rgbHandler = checkImage->getDataHandler(false, &rowSize, &channelsPixelSize, &channelsNumber);
	ptr<handlers::imageHandler> originalHandler = baselineImage->getDataHandler(false, &rowSize, &channelsPixelSize, &channelsNumber);

	// Compare the buffers. A little difference is allowed
	CPPUNIT_ASSERT(checkSizeX == sizeX);
	CPPUNIT_ASSERT(checkSizeY == sizeY);

	for(imbxUint32 checkY = 0; checkY < sizeY; ++checkY)
	{
		for(imbxUint32 checkX = 0; checkX < sizeX; ++checkX)
		{
			for(imbxUint32 channel = 3; channel != 0; --channel)
			{
				imbxInt32 value0 = rgbHandler->getUnsignedLongIncPointer();
				imbxInt32 value1 = originalHandler->getUnsignedLongIncPointer();
				CPPUNIT_ASSERT(value0 == value1);
			}
		}
	}

}


} // namespace tests

} // namespace imebra

} // namespace puntoexe