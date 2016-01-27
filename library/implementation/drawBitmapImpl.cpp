/*
$fileHeader$
*/

/*! \file drawBitmap.cpp
    \brief Implementation of the transform drawBitmap.

*/

#include "drawBitmapImpl.h"
#include "imageImpl.h"
#include "colorTransformsFactoryImpl.h"
#include "transformHighBitImpl.h"

namespace imebra
{

namespace implementation
{


drawBitmap::drawBitmap(std::shared_ptr<image> sourceImage, std::shared_ptr<transforms::transformsChain> transformsChain):
    m_image(sourceImage), m_transformsChain(std::make_shared<transforms::transformsChain>())
{
	if(transformsChain != 0 && !transformsChain->isEmpty())
	{
		m_transformsChain->addTransform(transformsChain);
	}

	// Allocate the transforms that obtain an RGB24 image
    std::string initialColorSpace;
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
		std::shared_ptr<image> startImage(m_transformsChain->allocateOutputImage(m_image, 1, 1));
		initialColorSpace = startImage->getColorSpace();
	}
    std::shared_ptr<transforms::colorTransforms::colorTransformsFactory> pColorTransformsFactory(transforms::colorTransforms::colorTransformsFactory::getColorTransformsFactory());
    std::shared_ptr<transforms::transform> rgbColorTransform(pColorTransformsFactory->getTransform(initialColorSpace, "RGB"));
	if(rgbColorTransform != 0)
	{
		m_transformsChain->addTransform(rgbColorTransform);
	}

    if(highBit != 7 || depth != image::depthU8)
    {
        std::shared_ptr<transforms::transformHighBit> highBitTransform(std::make_shared<transforms::transformHighBit>());
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
        m_finalImage = std::make_shared<image>();
        m_finalImage->create(width, 1, image::depthU8, "RGB", 7);
    }
}


} // namespace implementation

} // namespace imebra
