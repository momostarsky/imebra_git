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
    std::uint32_t highBit = 7;
    image::bitDepth depth = image::depthU8;
	if(m_transformsChain->isEmpty())
	{
		initialColorSpace = m_image->getColorSpace();
        highBit = m_image->getHighBit();
        depth = m_image->getDepth();
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

    if(highBit != 7 || depth != image::depthU8)
    {
        ptr<transforms::transformHighBit> highBitTransform(new transforms::transformHighBit());
        m_transformsChain->addTransform(highBitTransform);
    }

	std::uint32_t width, height;
	m_image->getSize(&width, &height);
    if(m_transformsChain->isEmpty())
	{
		m_finalImage = m_image;
	}
	else
	{
        m_finalImage = new image;
        m_finalImage->create(width, 1, image::depthU8, L"RGB", 7);
    }
}


} // namespace imebra

} // namespace puntoexe
