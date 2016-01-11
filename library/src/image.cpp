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

Image::Image(): m_pImage(std::make_shared<puntoexe::imebra::image>())
{
}

Image::Image(const Image& right): m_pImage(right.m_pImage)
{}

Image::Image(std::shared_ptr<puntoexe::imebra::image> pImage): m_pImage(pImage)
{}

Image& Image::operator=(const Image& right)
{
    m_pImage = right.m_pImage;
    return *this;
}

WritingDataHandler Image::create(
        const size_t sizeX,
        const size_t sizeY,
		const bitDepth depth,
        const std::string& colorSpace,
        const unsigned int highBit)
{
    return WritingDataHandler(m_pImage->create((std::uint32_t)sizeX, (std::uint32_t)sizeY, (puntoexe::imebra::image::bitDepth)depth, colorSpace, (std::uint8_t)highBit));
}

void Image::setHighBit(unsigned int highBit)
{
    m_pImage->setHighBit((std::uint8_t)highBit);
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

size_t Image::getSizeX() const
{
    std::uint32_t sizeX, sizeY;
    m_pImage->getSize(&sizeX, &sizeY);
    return (size_t)sizeX;
}

size_t Image::getSizeY() const
{
    std::uint32_t sizeX, sizeY;
    m_pImage->getSize(&sizeX, &sizeY);
    return (size_t)sizeY;
}

ReadingDataHandler Image::getReadingDataHandler() const
{
    return ReadingDataHandler(m_pImage->getReadingDataHandler());
}


std::string Image::getColorSpace() const
{
    return m_pImage->getColorSpace();
}

int Image::getChannelsNumber() const
{
    return m_pImage->getChannelsNumber();
}

Image::bitDepth Image::getDepth() const
{
    return (bitDepth)(m_pImage->getDepth());
}

int Image::getHighBit() const
{
    return (int)(m_pImage->getHighBit());
}

}
