/*
$fileHeader$
*/

/*! \file colorTransformsFactory_swig.cpp
    \brief Implementation of the class ColorTransformsFactory for SWIG.
*/

#include "../include/imebra/colorTransformsFactory.h"
#include "../implementation/colorTransformsFactoryImpl.h"

std::wstring ColorTransformsFactory::normalizeColorSpace(std::wstring colorSpace)
{
    return puntoexe::imebra::transforms::colorTransforms::colorTransformsFactory::normalizeColorSpace(colorSpace);

}

bool ColorTransformsFactory::isMonochrome(std::wstring colorSpace)
{
    return puntoexe::imebra::transforms::colorTransforms::colorTransformsFactory::isMonochrome(colorSpace);
}

bool ColorTransformsFactory::isSubsampledX(std::wstring colorSpace)
{
    return puntoexe::imebra::transforms::colorTransforms::colorTransformsFactory::isSubsampledX(colorSpace);
}

bool ColorTransformsFactory::isSubsampledY(std::wstring colorSpace)
{
    return puntoexe::imebra::transforms::colorTransforms::colorTransformsFactory::isSubsampledY(colorSpace);
}

bool ColorTransformsFactory::canSubsample(std::wstring colorSpace)
{
    return puntoexe::imebra::transforms::colorTransforms::colorTransformsFactory::canSubsample(colorSpace);
}

std::wstring ColorTransformsFactory::makeSubsampled(std::wstring colorSpace, bool bSubsampleX, bool bSubsampleY)
{
    return puntoexe::imebra::transforms::colorTransforms::colorTransformsFactory::makeSubsampled(colorSpace, bSubsampleX, bSubsampleY);
}

int ColorTransformsFactory::getNumberOfChannels(std::wstring colorSpace)
{
    return (int)puntoexe::imebra::transforms::colorTransforms::colorTransformsFactory::getNumberOfChannels(colorSpace);
}

Transform ColorTransformsFactory::getTransform(std::wstring startColorSpace, std::wstring endColorSpace)
{
    puntoexe::ptr<puntoexe::imebra::transforms::colorTransforms::colorTransformsFactory> factory(puntoexe::imebra::transforms::colorTransforms::colorTransformsFactory::getColorTransformsFactory());
    Transform transform(factory->getTransform(startColorSpace, endColorSpace));
    if(transform.m_pTransform == 0)
    {
        throw puntoexe::imebra::transforms::colorTransforms::colorTransformsFactoryExceptionNoTransform("There is no color transform that can convert between the specified color spaces");
    }
    return transform;
}
