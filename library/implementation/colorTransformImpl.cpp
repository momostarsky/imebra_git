/*
$fileHeader$
*/

/*! \file colorTransform.cpp
    \brief Implementation of the base class for the color transforms.

*/

#include "exceptionImpl.h"
#include "colorTransformImpl.h"
#include "colorTransformsFactoryImpl.h"
#include "imageImpl.h"
#include "../include/imebra/exceptions.h"

namespace imebra
{

namespace implementation
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
void colorTransform::checkColorSpaces(const std::string& inputHandlerColorSpace, const std::string& outputHandlerColorSpace)
{
    IMEBRA_FUNCTION_START();

	if(inputHandlerColorSpace != getInitialColorSpace())
	{
        IMEBRA_THROW(ColorTransformWrongColorSpaceError, "The image's color space cannot be handled by the transform");
	}

	if(outputHandlerColorSpace != getFinalColorSpace())
	{
        IMEBRA_THROW(ColorTransformWrongColorSpaceError, "The image's color space cannot be handled by the transform");
	}

	IMEBRA_FUNCTION_END();
}


std::shared_ptr<image> colorTransform::allocateOutputImage(std::shared_ptr<image> pInputImage, std::uint32_t width, std::uint32_t height)
{
    std::shared_ptr<image> newImage(std::make_shared<image>());
	newImage->create(width, height, pInputImage->getDepth(), getFinalColorSpace(), pInputImage->getHighBit());
	return newImage;
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
registerColorTransform::registerColorTransform(std::shared_ptr<colorTransform> newColorTransform)
{
    IMEBRA_FUNCTION_START();

	std::shared_ptr<colorTransformsFactory> pFactory(colorTransformsFactory::getColorTransformsFactory());
	pFactory->registerTransform(newColorTransform);

	IMEBRA_FUNCTION_END();
}


} // namespace colorTransforms

} // namespace transforms

} // namespace implementation

} // namespace imebra
