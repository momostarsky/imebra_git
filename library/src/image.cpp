/*
$fileHeader$
*/

/*! \file image_swig.h
    \brief Implementation of the class Image for SWIG.

*/

#include "../include/imebra/image.h"
#include "../implementation/imageImpl.h"
#include "../implementation/dataHandlerImpl.h"
#include "../implementation/dataHandlerNumericImpl.h"

namespace imebra
{

Image::Image()
{
    std::string colorSpace("MONOCHROME2");
    m_pImage = std::make_shared<implementation::image>((std::uint32_t)1, (std::uint32_t)1, bitDepth::depthU8, colorSpace, (std::uint32_t)7);
}

Image::Image(
        std::uint32_t sizeX,
        std::uint32_t sizeY,
        bitDepth depth,
        const std::string& colorSpace,
        std::uint32_t highBit):
    m_pImage(std::make_shared<implementation::image>(sizeX, sizeY, depth, colorSpace, highBit))
{
}

Image::Image(const Image& right): m_pImage(right.m_pImage)
{}

Image::Image(std::shared_ptr<implementation::image> pImage): m_pImage(pImage)
{}

Image& Image::operator=(const Image& right)
{
    m_pImage = right.m_pImage;
    return *this;
}

double Image::getSizeMmX() const
{
    double sizeX, sizeY;
    m_pImage->getSizeMm(&sizeX, &sizeY);
    return sizeX;
}

double Image::getSizeMmY() const
{
    double sizeX, sizeY;
    m_pImage->getSizeMm(&sizeX, &sizeY);
    return sizeY;
}

void Image::setSizeMm(const double sizeX, const double sizeY)
{
    m_pImage->setSizeMm(sizeX, sizeY);
}

std::uint32_t Image::getSizeX() const
{
    std::uint32_t sizeX, sizeY;
    m_pImage->getSize(&sizeX, &sizeY);
    return sizeX;
}

std::uint32_t Image::getSizeY() const
{
    std::uint32_t sizeX, sizeY;
    m_pImage->getSize(&sizeX, &sizeY);
    return sizeY;
}

ReadingDataHandler Image::getReadingDataHandler() const
{
    return ReadingDataHandler(m_pImage->getReadingDataHandler());
}

WritingDataHandler Image::getWritingDataHandler()
{
    return WritingDataHandler(m_pImage->getWritingDataHandler());
}

std::string Image::getColorSpace() const
{
    return m_pImage->getColorSpace();
}

std::uint32_t Image::getChannelsNumber() const
{
    return m_pImage->getChannelsNumber();
}

bitDepth Image::getDepth() const
{
    return m_pImage->getDepth();
}

std::uint32_t Image::getHighBit() const
{
    return m_pImage->getHighBit();
}

}
