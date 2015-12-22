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

DataHandler Image::create(
        const size_t sizeX,
        const size_t sizeY,
		const bitDepth depth,
		std::wstring colorSpace,
		const int highBit)
{
    return DataHandler(m_pImage->create((imbxUint32)sizeX, (imbxUint32)sizeY, (puntoexe::imebra::image::bitDepth)depth, colorSpace, (imbxUint8)highBit));
}

void Image::setHighBit(int highBit)
{
    m_pImage->setHighBit((imbxUint8)highBit);
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
    imbxUint32 sizeX, sizeY;
    m_pImage->getSize(&sizeX, &sizeY);
    return (size_t)sizeX;
}

size_t Image::getSizeY() const
{
    imbxUint32 sizeX, sizeY;
    m_pImage->getSize(&sizeX, &sizeY);
    return (size_t)sizeY;
}

DataHandler Image::getDataHandler(const bool bWrite)
{
    imbxUint32 rowSize, channelPixelSize, channelsNumber;
    return DataHandler(m_pImage->getDataHandler(bWrite, &rowSize, &channelPixelSize, &channelsNumber));
}


std::wstring Image::getColorSpace() const
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
