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
    m_pImage = std::make_shared<implementation::image>((std::uint32_t)1, (std::uint32_t)1, bitDepth_t::depthU8, colorSpace, (std::uint32_t)7);
}

Image::Image(
        std::uint32_t width,
        std::uint32_t height,
        bitDepth_t depth,
        const std::string& colorSpace,
        std::uint32_t highBit):
    m_pImage(std::make_shared<implementation::image>(width, height, depth, colorSpace, highBit))
{
}

Image::Image(const Image& right): m_pImage(right.m_pImage)
{
}

Image::Image(std::shared_ptr<implementation::image> pImage): m_pImage(pImage)
{
}

Image::~Image()
{
}

Image& Image::operator=(const Image& right)
{
    m_pImage = right.m_pImage;
    return *this;
}

double Image::getSizeMmX() const
{
    double width, height;
    m_pImage->getSizeMm(&width, &height);
    return width;
}

double Image::getSizeMmY() const
{
    double width, height;
    m_pImage->getSizeMm(&width, &height);
    return height;
}

void Image::setSizeMm(const double width, const double height)
{
    m_pImage->setSizeMm(width, height);
}

std::uint32_t Image::getWidth() const
{
    std::uint32_t width, height;
    m_pImage->getSize(&width, &height);
    return width;
}

std::uint32_t Image::getHeight() const
{
    std::uint32_t width, height;
    m_pImage->getSize(&width, &height);
    return height;
}

ReadingDataHandlerNumeric Image::getReadingDataHandler() const
{
    return ReadingDataHandlerNumeric(m_pImage->getReadingDataHandler());
}

WritingDataHandlerNumeric Image::getWritingDataHandler()
{
    return WritingDataHandlerNumeric(m_pImage->getWritingDataHandler());
}

std::string Image::getColorSpace() const
{
    return m_pImage->getColorSpace();
}

std::uint32_t Image::getChannelsNumber() const
{
    return m_pImage->getChannelsNumber();
}

bitDepth_t Image::getDepth() const
{
    return m_pImage->getDepth();
}

std::uint32_t Image::getHighBit() const
{
    return m_pImage->getHighBit();
}

}
