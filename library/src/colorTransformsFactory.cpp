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

std::wstring ColorTransformsFactory::normalizeColorSpace(const std::wstring& colorSpace)
{
    return puntoexe::imebra::transforms::colorTransforms::colorTransformsFactory::normalizeColorSpace(colorSpace);
}

bool ColorTransformsFactory::isMonochrome(const std::wstring& colorSpace)
{
    return puntoexe::imebra::transforms::colorTransforms::colorTransformsFactory::isMonochrome(colorSpace);
}

bool ColorTransformsFactory::isSubsampledX(const std::wstring& colorSpace)
{
    return puntoexe::imebra::transforms::colorTransforms::colorTransformsFactory::isSubsampledX(colorSpace);
}

bool ColorTransformsFactory::isSubsampledY(const std::wstring& colorSpace)
{
    return puntoexe::imebra::transforms::colorTransforms::colorTransformsFactory::isSubsampledY(colorSpace);
}

bool ColorTransformsFactory::canSubsample(const std::wstring& colorSpace)
{
    return puntoexe::imebra::transforms::colorTransforms::colorTransformsFactory::canSubsample(colorSpace);
}

std::wstring ColorTransformsFactory::makeSubsampled(const std::wstring& colorSpace, bool bSubsampleX, bool bSubsampleY)
{
    return puntoexe::imebra::transforms::colorTransforms::colorTransformsFactory::makeSubsampled(colorSpace, bSubsampleX, bSubsampleY);
}

int ColorTransformsFactory::getNumberOfChannels(const std::wstring& colorSpace)
{
    return (int)puntoexe::imebra::transforms::colorTransforms::colorTransformsFactory::getNumberOfChannels(colorSpace);
}

Transform ColorTransformsFactory::getTransform(const std::wstring& startColorSpace, const std::wstring& endColorSpace)
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
