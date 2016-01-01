/*
$fileHeader$
*/

/*! \file transform.cpp
    \brief Implementation of the base class used by the transforms.

*/

#include "exceptionImpl.h"
#include "transformImpl.h"
#include "imageImpl.h"
#include "transformHighBitImpl.h"


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
            const std::shared_ptr<image>& inputImage,
            std::uint32_t inputTopLeftX, std::uint32_t inputTopLeftY, std::uint32_t inputWidth, std::uint32_t inputHeight,
            const std::shared_ptr<image>& outputImage,
            std::uint32_t outputTopLeftX, std::uint32_t outputTopLeftY)
{
    PUNTOEXE_FUNCTION_START(L"transformHandlers::runTransform");

    std::uint32_t inputImageWidth, inputImageHeight;
    inputImage->getSize(&inputImageWidth, &inputImageHeight);
    std::uint32_t outputImageWidth, outputImageHeight;
    outputImage->getSize(&outputImageWidth, &outputImageHeight);

    if(inputTopLeftX + inputWidth > inputImageWidth ||
        inputTopLeftY + inputHeight > inputImageHeight ||
        outputTopLeftX + inputWidth > outputImageWidth ||
        outputTopLeftY + inputHeight > outputImageHeight)
    {
        PUNTOEXE_THROW(transformExceptionInvalidArea, "The input and/or output areas are invalid");
    }

    std::shared_ptr<handlers::readingDataHandlerNumericBase> inputHandler(inputImage->getReadingDataHandler());
	std::shared_ptr<palette> inputPalette(inputImage->getPalette());
	std::wstring inputColorSpace(inputImage->getColorSpace());
	std::uint32_t inputHighBit(inputImage->getHighBit());
    std::uint64_t inputNumValues((std::uint64_t)1 << (inputHighBit + 1));
    std::int32_t inputMinValue(0);
	image::bitDepth inputDepth(inputImage->getDepth());
    if(inputDepth == image::depthS32 || inputDepth == image::depthS16 || inputDepth == image::depthS8)
	{
		inputMinValue -= (std::int32_t)(inputNumValues >> 1);
	}

    std::shared_ptr<handlers::writingDataHandlerNumericBase> outputHandler(outputImage->getWritingDataHandler());
	std::shared_ptr<palette> outputPalette(outputImage->getPalette());
	std::wstring outputColorSpace(outputImage->getColorSpace());
	std::uint32_t outputHighBit(outputImage->getHighBit());
    std::uint64_t outputNumValues((std::uint64_t)1 << (outputHighBit + 1));
	std::int32_t outputMinValue(0);
	image::bitDepth outputDepth(outputImage->getDepth());
    if(outputDepth == image::depthS32 || outputDepth == image::depthS16 || outputDepth == image::depthS8)
	{
		outputMinValue -= (std::int32_t)(outputNumValues >> 1);
	}

	if(isEmpty())
	{
		std::shared_ptr<transformHighBit> emptyTransform(new transformHighBit);
        emptyTransform->runTransformHandlers(inputHandler, inputImageWidth, inputColorSpace, inputPalette, inputMinValue, inputHighBit,
											 inputTopLeftX, inputTopLeftY, inputWidth, inputHeight,
                                             outputHandler, outputImageWidth, outputColorSpace, outputPalette, outputMinValue, outputHighBit,
											 outputTopLeftX, outputTopLeftY);
		return;
	}

    runTransformHandlers(inputHandler, inputImageWidth, inputColorSpace, inputPalette, inputMinValue, inputHighBit,
		inputTopLeftX, inputTopLeftY, inputWidth, inputHeight,
        outputHandler, outputImageWidth, outputColorSpace, outputPalette, outputMinValue, outputHighBit,
		outputTopLeftX, outputTopLeftY);

    PUNTOEXE_FUNCTION_END();
}




} // namespace transforms

} // namespace imebra

} // namespace puntoexe
