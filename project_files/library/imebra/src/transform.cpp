/*
$fileHeader$
*/

/*! \file transform.cpp
    \brief Implementation of the base class used by the transforms.

*/

#include "../../base/include/exception.h"
#include "../include/transform.h"
#include "../include/image.h"


namespace puntoexe
{

namespace imebra
{

namespace transforms
{

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Declare an input parameter
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
bool transform::isEmpty()
{
	return false;
}


void transformHandlers::runTransform(
            const ptr<image>& inputImage,
            imbxUint32 inputTopLeftX, imbxUint32 inputTopLeftY, imbxUint32 inputWidth, imbxUint32 inputHeight,
            const ptr<image>& outputImage,
            imbxUint32 outputTopLeftX, imbxUint32 outputTopLeftY)
{
	imbxUint32 rowSize, numPixels, channels;
	ptr<handlers::dataHandlerNumericBase> inputHandler(inputImage->getDataHandler(false, &rowSize, &numPixels, &channels));
	imbxUint32 inputImageWidth, inputImageHeight;
	inputImage->getSize(&inputImageWidth, &inputImageHeight);
	ptr<palette> inputPalette(inputImage->getPalette());
	std::wstring inputColorSpace(inputImage->getColorSpace());
	imbxUint32 inputHighBit(inputImage->getHighBit());
	imbxUint32 inputNumValues((imbxUint32)1 << (inputHighBit + 1));
	imbxInt32 inputMinValue(0);
	image::bitDepth inputDepth(inputImage->getDepth());
	if(inputDepth == image::depthS16 || inputDepth == image::depthS8)
	{
		inputMinValue -= (imbxInt32)(inputNumValues >> 1);
	}

	ptr<handlers::dataHandlerNumericBase> outputHandler(outputImage->getDataHandler(false, &rowSize, &numPixels, &channels));
	imbxUint32 outputImageWidth, outputImageHeight;
	outputImage->getSize(&outputImageWidth, &outputImageHeight);
	ptr<palette> outputPalette(outputImage->getPalette());
	std::wstring outputColorSpace(outputImage->getColorSpace());
	imbxUint32 outputHighBit(outputImage->getHighBit());
	imbxUint32 outputNumValues((imbxUint32)1 << (outputHighBit + 1));
	imbxInt32 outputMinValue(0);
	image::bitDepth outputDepth(outputImage->getDepth());
	if(outputDepth == image::depthS16 || outputDepth == image::depthS8)
	{
		outputMinValue -= (imbxInt32)(outputNumValues >> 1);
	}

	runTransformHandlers(inputHandler, inputImageWidth, inputColorSpace, inputPalette, inputMinValue, inputNumValues,
		inputTopLeftX, inputTopLeftY, inputWidth, inputHeight,
		outputHandler, outputImageWidth, outputColorSpace, outputPalette, outputMinValue, outputNumValues,
		outputTopLeftX, outputTopLeftY);

}


} // namespace transforms

} // namespace imebra

} // namespace puntoexe
