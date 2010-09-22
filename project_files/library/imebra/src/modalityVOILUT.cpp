/*
$fileHeader$
*/

/*! \file modalityVOILUT.cpp
    \brief Implementation of the class modalityVOILUT.

*/

#include "../../base/include/exception.h"
#include "../include/modalityVOILUT.h"
#include "../include/dataSet.h"

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
// Modality VOILUT transform
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
modalityVOILUT::modalityVOILUT(ptr<dataSet> pDataSet): m_pDataSet(pDataSet)
{
	m_voiLut = m_pDataSet->getLut(0x0028, 0x3000, 0);

	m_rescaleIntercept = m_pDataSet->getDouble(0x0028, 0, 0x1052, 0x0);
	m_rescaleSlope = m_pDataSet->getDouble(0x0028, 0, 0x1053, 0x0);
	if(m_rescaleSlope == 0.0)
	    m_rescaleSlope = 1.0;

}

ptr<image> modalityVOILUT::allocateOutputImage(ptr<image> pInputImage, imbxUint32 width, imbxUint32 height)
{
	// LUT
	///////////////////////////////////////////////////////////
	if(m_voiLut != 0 && m_voiLut->getSize() != 0 && m_voiLut->checkValidDataRange())
	{
		imbxUint8 bits(m_voiLut->getBits());

		// Look for negative outputs
		bool bNegative(false);
		for(imbxInt32 index(m_voiLut->getFirstMapped()), size(m_voiLut->getSize()); !bNegative && size != 0; --size, ++index)
		{
			bNegative = (m_voiLut->mappedValue(index) < 0);
		}

		image::bitDepth depth;
		if(bNegative)
		{
			depth = bits > 8 ? image::depthS16 : image::depthS8;
		}
		else
		{
			depth = bits > 8 ? image::depthU16 : image::depthU8;
		}
		ptr<image> returnImage(new image);
		returnImage->create(width, height, depth, L"MONOCHROME2", bits - 1);
		return returnImage;
	}

	// Rescale
	///////////////////////////////////////////////////////////
	if(m_rescaleSlope == 0)
	{
		ptr<image> returnImage(new image);
		returnImage->create(width, height, pInputImage->getDepth(), L"MONOCHROME2", pInputImage->getHighBit());
		return returnImage;
	}

	image::bitDepth inputDepth(pInputImage->getDepth());
	imbxUint32 highBit(pInputImage->getHighBit());

	imbxInt32 value0 = 0;
	imbxInt32 value1 = ((imbxInt32)1 << (highBit + 1)) - 1;
	if(inputDepth == image::depthS16 || inputDepth == image::depthS8)
	{
		value0 = ((imbxInt32)(-1) << highBit) + m_rescaleIntercept;
		value1 = ((imbxInt32)1 << highBit) + m_rescaleIntercept;
	}
	value0 *= m_rescaleSlope;
	value0 += m_rescaleIntercept;
	value1 *= m_rescaleSlope;
	value1 += m_rescaleIntercept;

	imbxInt32 minValue, maxValue;
	if(value0 < value1)
	{
		minValue = value0;
		maxValue = value1;
	}
	else
	{
		minValue = value1;
		maxValue = value0;
	}

	ptr<image> returnImage(new image);
	if(minValue >= 0 && maxValue <= 255)
	{
		returnImage->create(width, height, image::depthU8, L"MONOCHROME2", 7);
		return returnImage;
	}
	if(minValue >= -128 && maxValue <= 127)
	{
		returnImage->create(width, height, image::depthS8, L"MONOCHROME2", 7);
		return returnImage;
	}
	if(minValue >= 0 && maxValue <= 65535)
	{
		returnImage->create(width, height, image::depthU16, L"MONOCHROME2", 15);
		return returnImage;
	}
	if(minValue >= -32768 && maxValue <= 32767)
	{
		returnImage->create(width, height, image::depthS16, L"MONOCHROME2", 15);
		return returnImage;
	}
	returnImage->create(width, height, image::depthS32, L"MONOCHROME2", 31);
	return returnImage;
}



} // namespace transforms

} // namespace imebra

} // namespace puntoexe
