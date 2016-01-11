/*
$fileHeader$
*/

/*! \file colorTransformsFactory_swig.cpp
    \brief Implementation of the class ColorTransformsFactory for SWIG.
*/

#include "../include/imebra/colorTransformsFactory.h"
#include "../implementation/colorTransformsFactoryImpl.h"
#include "../include/imebra/exceptions.h"
namespace imebra
{

std::string ColorTransformsFactory::normalizeColorSpace(const std::string& colorSpace)
{
    return puntoexe::imebra::transforms::colorTransforms::colorTransformsFactory::normalizeColorSpace(colorSpace);
}

bool ColorTransformsFactory::isMonochrome(const std::string& colorSpace)
{
    return puntoexe::imebra::transforms::colorTransforms::colorTransformsFactory::isMonochrome(colorSpace);
}

bool ColorTransformsFactory::isSubsampledX(const std::string& colorSpace)
{
    return puntoexe::imebra::transforms::colorTransforms::colorTransformsFactory::isSubsampledX(colorSpace);
}

bool ColorTransformsFactory::isSubsampledY(const std::string& colorSpace)
{
    return puntoexe::imebra::transforms::colorTransforms::colorTransformsFactory::isSubsampledY(colorSpace);
}

bool ColorTransformsFactory::canSubsample(const std::string& colorSpace)
{
    return puntoexe::imebra::transforms::colorTransforms::colorTransformsFactory::canSubsample(colorSpace);
}

std::string ColorTransformsFactory::makeSubsampled(const std::string& colorSpace, bool bSubsampleX, bool bSubsampleY)
{
    return puntoexe::imebra::transforms::colorTransforms::colorTransformsFactory::makeSubsampled(colorSpace, bSubsampleX, bSubsampleY);
}

int ColorTransformsFactory::getNumberOfChannels(const std::string& colorSpace)
{
    return (int)puntoexe::imebra::transforms::colorTransforms::colorTransformsFactory::getNumberOfChannels(colorSpace);
}

Transform ColorTransformsFactory::getTransform(const std::string& startColorSpace, const std::string& endColorSpace)
{
    std::shared_ptr<puntoexe::imebra::transforms::colorTransforms::colorTransformsFactory> factory(puntoexe::imebra::transforms::colorTransforms::colorTransformsFactory::getColorTransformsFactory());
    Transform transform(factory->getTransform(startColorSpace, endColorSpace));
    if(transform.m_pTransform == 0)
    {
        throw colorTransformsFactoryExceptionNoTransform("There is no color transform that can convert between the specified color spaces");
    }
    return transform;
}

}
