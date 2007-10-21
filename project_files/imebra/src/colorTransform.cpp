/*
$fileHeader$
*/

/*! \file colorTransform.cpp
    \brief Implementation of the base class for the color transforms.

*/

#include "../../base/include/exception.h"
#include "../include/colorTransform.h"
#include "../include/colorTransformsFactory.h"
#include "../include/image.h"


namespace puntoexe
{

namespace imebra
{

namespace transforms
{

namespace colorTransforms
{

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
//
// colorTransform
//
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Transformation
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void colorTransform::doTransform()
{
	PUNTOEXE_FUNCTION_START(L"colorTransform::doTransform");

	// Process all the input images
	///////////////////////////////////////////////////////////
	for(int scanImages = 0; ; ++scanImages)
	{
		// Get the input image
		///////////////////////////////////////////////////////////
		ptr<image> pInputImage=getInputImage(scanImages);

		// If the input image doesn't exist, then exit
		///////////////////////////////////////////////////////////
		if(pInputImage == 0)
			break;

		// Check the input color space
		///////////////////////////////////////////////////////////
		if(pInputImage->getColorSpace()!=getInitialColorSpace())
		{
			PUNTOEXE_THROW(colorTransformExceptionWrongColorSpace, "the image's color space cannot be handled by the transform");
		}

		// Get the output image
		///////////////////////////////////////////////////////////
		ptr<image> pOutputImage=getOutputImage(scanImages);
		if(pOutputImage == 0)
		{
			ptr<image> tempImage(new image);
			pOutputImage=tempImage;
			declareOutputImage(scanImages, pOutputImage);
		}

		// Get the input image's attributes and the data handler
		///////////////////////////////////////////////////////////
		imbxUint32 sizeX, sizeY;
		pInputImage->getSize(&sizeX, &sizeY);

		double sizeMmX, sizeMmY;
		pInputImage->getSizeMm(&sizeMmX, &sizeMmY);
		pOutputImage->setSizeMm(sizeMmX, sizeMmY);

		image::bitDepth inputDepth=pInputImage->getDepth();
		image::bitDepth outputDepth=inputDepth;
		imbxUint32  highBit=pInputImage->getHighBit();
		imbxUint32 totalPixelsNumber=sizeX*sizeY;
		
		imbxInt32 inputMinValue = 0;
		imbxInt32 inputMaxValue = (1L<<(highBit+1))-1L;
		imbxInt32 outputMinValue = inputMinValue;
		imbxInt32 outputMaxValue = inputMaxValue;

		if(inputDepth==image::depthS8 || inputDepth==image::depthS16)
		{
			inputMinValue-=1L<<highBit;
			inputMaxValue-=1L<<highBit;

			std::wstring outputColorSpace = getFinalColorSpace();
			if(outputColorSpace == L"MONOCHROME2" || outputColorSpace == L"MONOCHROME1")
			{
				outputMinValue-=1L<<highBit;
				outputMaxValue-=1L<<highBit;
			}
			else
			{
				if(inputDepth==image::depthS8)
					outputDepth = image::depthU8;
				if(inputDepth==image::depthS16)
					outputDepth = image::depthU16;
			}
		}

		// Get the data handler for the input and the output
		//  images
		///////////////////////////////////////////////////////////
		imbxUint32 rowSize, channelPixelSize, channelsNumber;
		ptr<handlers::imageHandler> pInputDataHandler = pInputImage->getDataHandler(false, &rowSize, &channelPixelSize, &channelsNumber);
		if(pInputDataHandler->getSize() < totalPixelsNumber * channelsNumber)
		{
			PUNTOEXE_THROW(colorTransformExceptionWrongColorSpace, "the input image's size doesn't match the requested size");
		}
		
		ptr<handlers::imageHandler> pOutputDataHandler = pOutputImage->create(sizeX, sizeY, outputDepth, getFinalColorSpace(), (imbxUint8)highBit);
		channelsNumber = pOutputImage->getChannelsNumber();
		if(pOutputDataHandler->getSize() < totalPixelsNumber * channelsNumber)
		{
			PUNTOEXE_THROW(colorTransformExceptionWrongColorSpace, "the output image's size doesn't match the requested size");
		}

		doColorTransform(pInputDataHandler->getMemoryBuffer(), pOutputDataHandler->getMemoryBuffer(), totalPixelsNumber, inputMinValue, inputMaxValue, outputMinValue, outputMaxValue);
	}
	
	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
//
// registerColorTransform
//
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Constructor
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
registerColorTransform::registerColorTransform(ptr<colorTransform> newColorTransform)
{
	PUNTOEXE_FUNCTION_START(L"registerColorTransform::registerColorTransform");

	ptr<colorTransformsFactory> pFactory(colorTransformsFactory::getColorTransformsFactory());
	pFactory->registerTransform(newColorTransform);

	PUNTOEXE_FUNCTION_END();
}


} // namespace colorTransforms

} // namespace transforms

} // namespace imebra

} // namespace puntoexe
