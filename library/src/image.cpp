/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
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

Image::Image(const std::shared_ptr<implementation::image>& pImage): m_pImage(pImage)
{
}

Image::Image(const Image &source): m_pImage(getImageImplementation(source))
{
}

Image& Image::operator=(const Image& source)
{
    m_pImage = getImageImplementation(source);
    return *this;
}

const std::shared_ptr<implementation::image>& getImageImplementation(const Image& source)
{
    return source.m_pImage;
}

Image::~Image()
{
}

double Image::getWidthMm() const
{
    double width, height;
    m_pImage->getSizeMm(&width, &height);
    return width;
}

double Image::getHeightMm() const
{
    double width, height;
    m_pImage->getSizeMm(&width, &height);
    return height;
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

MutableImage::MutableImage(
        std::uint32_t width,
        std::uint32_t height,
        bitDepth_t depth,
        const std::string& colorSpace,
        std::uint32_t highBit):
    Image(std::make_shared<implementation::image>(width, height, depth, colorSpace, highBit))
{
}

MutableImage::MutableImage(std::shared_ptr<imebra::implementation::image> pImage):
    Image(pImage)
{
}

MutableImage::MutableImage(const MutableImage& source): Image(source)
{
}

MutableImage& MutableImage::operator=(const MutableImage& source)
{
    Image::operator =(source);
    return *this;
}


void MutableImage::setSizeMm(double width, double height)
{
    getImageImplementation(*this)->setSizeMm(width, height);
}

WritingDataHandlerNumeric MutableImage::getWritingDataHandler()
{
    IMEBRA_FUNCTION_START();

    return WritingDataHandlerNumeric(getImageImplementation(*this)->getWritingDataHandler());

    IMEBRA_FUNCTION_END_LOG();
}

}
