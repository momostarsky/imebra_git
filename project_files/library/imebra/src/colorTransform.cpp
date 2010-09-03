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


ptr<image> colorTransform::allocateOutputImage(ptr<image> pInputImage, imbxUint32 width, imbxUint32 height)
{
	ptr<image> newImage(new image);
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
