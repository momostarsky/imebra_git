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
void colorTransform::checkColorSpaces(const std::wstring& inputHandlerColorSpace, const std::wstring& outputHandlerColorSpace)
{
	PUNTOEXE_FUNCTION_START(L"colorTransform::runTransform");

	if(inputHandlerColorSpace != getInitialColorSpace())
	{
		PUNTOEXE_THROW(colorTransformExceptionWrongColorSpace, "The image's color space cannot be handled by the transform");
	}

	if(outputHandlerColorSpace != getFinalColorSpace())
	{
		PUNTOEXE_THROW(colorTransformExceptionWrongColorSpace, "The image's color space cannot be handled by the transform");
	}

	PUNTOEXE_FUNCTION_END();
}


std::shared_ptr<image> colorTransform::allocateOutputImage(std::shared_ptr<image> pInputImage, std::uint32_t width, std::uint32_t height)
{
    std::shared_ptr<image> newImage(new image());
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
	PUNTOEXE_FUNCTION_START(L"registerColorTransform::registerColorTransform");

	std::shared_ptr<colorTransformsFactory> pFactory(colorTransformsFactory::getColorTransformsFactory());
	pFactory->registerTransform(newColorTransform);

	PUNTOEXE_FUNCTION_END();
}


} // namespace colorTransforms

} // namespace transforms

} // namespace imebra

} // namespace puntoexe
