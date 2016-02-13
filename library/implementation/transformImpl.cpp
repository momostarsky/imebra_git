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
#include "../include/imebra/exceptions.h"

namespace imebra
{

namespace implementation
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
bool transform::isEmpty() const
{
	return false;
}


void transform::runTransform(
            const std::shared_ptr<const image>& inputImage,
            std::uint32_t inputTopLeftX, std::uint32_t inputTopLeftY, std::uint32_t inputWidth, std::uint32_t inputHeight,
            const std::shared_ptr<image>& outputImage,
            std::uint32_t outputTopLeftX, std::uint32_t outputTopLeftY) const
{
    IMEBRA_FUNCTION_START();

    std::uint32_t inputImageWidth, inputImageHeight;
    inputImage->getSize(&inputImageWidth, &inputImageHeight);
    std::uint32_t outputImageWidth, outputImageHeight;
    outputImage->getSize(&outputImageWidth, &outputImageHeight);

    if(inputTopLeftX + inputWidth > inputImageWidth ||
        inputTopLeftY + inputHeight > inputImageHeight ||
        outputTopLeftX + inputWidth > outputImageWidth ||
        outputTopLeftY + inputHeight > outputImageHeight)
    {
        IMEBRA_THROW(TransformInvalidAreaError, "The input and/or output areas are invalid");
    }

    std::shared_ptr<handlers::readingDataHandlerNumericBase> inputHandler(inputImage->getReadingDataHandler());
	std::shared_ptr<palette> inputPalette(inputImage->getPalette());
    std::string inputColorSpace(inputImage->getColorSpace());
	std::uint32_t inputHighBit(inputImage->getHighBit());
    std::uint64_t inputNumValues((std::uint64_t)1 << (inputHighBit + 1));
    std::int32_t inputMinValue(0);
    bitDepth inputDepth(inputImage->getDepth());
    if(inputDepth == bitDepth::depthS32 || inputDepth == bitDepth::depthS16 || inputDepth == bitDepth::depthS8)
	{
		inputMinValue -= (std::int32_t)(inputNumValues >> 1);
	}

    std::shared_ptr<handlers::writingDataHandlerNumericBase> outputHandler(outputImage->getWritingDataHandler());
	std::shared_ptr<palette> outputPalette(outputImage->getPalette());
    std::string outputColorSpace(outputImage->getColorSpace());
	std::uint32_t outputHighBit(outputImage->getHighBit());
    std::uint64_t outputNumValues((std::uint64_t)1 << (outputHighBit + 1));
	std::int32_t outputMinValue(0);
    bitDepth outputDepth(outputImage->getDepth());
    if(outputDepth == bitDepth::depthS32 || outputDepth == bitDepth::depthS16 || outputDepth == bitDepth::depthS8)
	{
		outputMinValue -= (std::int32_t)(outputNumValues >> 1);
	}

	if(isEmpty())
	{
        std::shared_ptr<transformHighBit> emptyTransform(std::make_shared<transformHighBit>());
        emptyTransform->runTransformHandlers(inputHandler, inputDepth, inputImageWidth, inputColorSpace, inputPalette, inputHighBit,
											 inputTopLeftX, inputTopLeftY, inputWidth, inputHeight,
                                             outputHandler, outputDepth, outputImageWidth, outputColorSpace, outputPalette, outputHighBit,
											 outputTopLeftX, outputTopLeftY);
		return;
	}

    runTransformHandlers(inputHandler, inputDepth, inputImageWidth, inputColorSpace, inputPalette, inputHighBit,
		inputTopLeftX, inputTopLeftY, inputWidth, inputHeight,
        outputHandler, outputDepth, outputImageWidth, outputColorSpace, outputPalette, outputHighBit,
		outputTopLeftX, outputTopLeftY);

    IMEBRA_FUNCTION_END();
}




} // namespace transforms

} // namespace implementation

} // namespace imebra
