/*
$fileHeader$
*/

/*! \file drawBitmap.cpp
    \brief Implementation of the transform drawBitmap.

*/

#include "../include/drawBitmap.h"
#include "../include/image.h"
#include "../include/colorTransformsFactory.h"
#include "../include/transformHighBit.h"

namespace puntoexe
{

namespace imebra
{


drawBitmap::drawBitmap(ptr<image> sourceImage, ptr<transforms::transformsChain> transformsChain):
	m_image(sourceImage), m_transformsChain(new transforms::transformsChain)
{
	if(transformsChain != 0 && !transformsChain->isEmpty())
	{
		m_transformsChain->addTransform(transformsChain);
	}

	// Allocate the transforms that obtain an RGB24 image
	std::wstring initialColorSpace;
	if(m_transformsChain->isEmpty())
	{
		initialColorSpace = m_image->getColorSpace();
	}
	else
	{
		ptr<image> startImage(m_transformsChain->allocateOutputImage(m_image, 1, 1));
		initialColorSpace = startImage->getColorSpace();
	}
	transforms::colorTransforms::colorTransformsFactory* pColorTransformsFactory(transforms::colorTransforms::colorTransformsFactory::getColorTransformsFactory());
	ptr<transforms::colorTransforms::colorTransform> rgbColorTransform(pColorTransformsFactory->getTransform(initialColorSpace, L"RGB"));
	if(rgbColorTransform != 0)
	{
		m_transformsChain->addTransform(rgbColorTransform);
	}

	std::uint32_t width, height;
	m_image->getSize(&width, &height);
	if(m_transformsChain->isEmpty())
	{
		m_finalImage = m_image;
	}
	else
	{
		m_finalImage = m_transformsChain->allocateOutputImage(m_image, width, 1);
	}

	if(m_finalImage->getDepth() != image::depthU8 || m_finalImage->getHighBit() != 7)
	{
		m_finalImage = new image;
		m_finalImage->create(width, 1, image::depthU8, L"RGB", 7);
		m_transformsChain->addTransform(new transforms::transformHighBit);
	}
}


} // namespace imebra

} // namespace puntoexe
