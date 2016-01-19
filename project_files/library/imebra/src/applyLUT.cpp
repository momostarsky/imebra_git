/*
$fileHeader$
*/

/*! \file applyLUT.cpp
    \brief Implementation of the class applyLUT.

*/

#include "../../base/include/exception.h"
#include "../include/applyLUT.h"
#include "../include/colorTransformsFactory.h"

namespace puntoexe
{

namespace imebra
{

namespace transforms
{


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Apply a LUT to an image
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
applyLUT::applyLUT(ptr<lut> pLUT):
        m_lut(pLUT)

{
}

bool applyLUT::isEmpty()
{
    return m_lut == 0 || m_lut->getSize() == 0 || !m_lut->checkValidDataRange();
}


ptr<image> applyLUT::allocateOutputImage(ptr<image> pInputImage, std::uint32_t width, std::uint32_t height)
{
	if(isEmpty())
	{
        ptr<image> newImage(new image());
		newImage->create(width, height, pInputImage->getDepth(), pInputImage->getColorSpace(), pInputImage->getHighBit());
		return newImage;
	}

	// LUT
	///////////////////////////////////////////////////////////
    std::uint8_t bits(m_lut->getBits());

    // Look for negative outputs
    bool bNegative(false);
    for(std::int32_t index(m_lut->getFirstMapped()), size(m_lut->getSize()); !bNegative && size != 0; --size, ++index)
    {
        bNegative = (m_lut->mappedValue(index) < 0);
    }

    image::bitDepth depth;
    if(bNegative)
    {
        if(bits > 16)
        {
            depth = image::depthS32;
        }
        else if(bits > 8)
        {
            depth = image::depthS16;
        }
        else
        {
            depth = image::depthS8;
        }
    }
    else
    {
        if(bits > 16)
        {
            depth = image::depthU32;
        }
        else if(bits > 8)
        {
            depth = image::depthU16;
        }
        else
        {
            depth = image::depthU8;
        }
    }
    ptr<image> returnImage(new image);
    returnImage->create(width, height, depth, L"MONOCHROME2", bits - 1);
    return returnImage;
}



} // namespace transforms

} // namespace imebra

} // namespace puntoexe
