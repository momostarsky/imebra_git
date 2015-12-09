/*
$fileHeader$
*/

/*! \file modalityVOILUT.cpp
    \brief Implementation of the class modalityVOILUT.

*/

#include "exceptionImpl.h"
#include "modalityVOILUTImpl.h"
#include "dataSetImpl.h"
#include "colorTransformsFactoryImpl.h"

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
modalityVOILUT::modalityVOILUT(ptr<dataSet> pDataSet):
		m_pDataSet(pDataSet), m_voiLut(pDataSet->getLut(0x0028, 0x3000, 0)), m_rescaleIntercept(pDataSet->getDouble(0x0028, 0, 0x1052, 0x0)), m_rescaleSlope(1.0), m_bEmpty(true)

{
	// Only monochrome images can have the modality voi-lut
	///////////////////////////////////////////////////////
	std::wstring colorSpace(pDataSet->getUnicodeString(0x0028, 0x0, 0x0004, 0x0));
	if(!colorTransforms::colorTransformsFactory::isMonochrome(colorSpace))
	{
		return;
	}

	ptr<handlers::dataHandler> rescaleHandler(m_pDataSet->getDataHandler(0x0028, 0, 0x1053, 0x0, false));
	if(rescaleHandler != 0)
	{
		m_rescaleSlope = rescaleHandler->getDouble(0);
		m_bEmpty = false;
	}
	if(m_voiLut != 0 && m_voiLut->getSize() != 0)
	{
		m_bEmpty = false;
	}

}

bool modalityVOILUT::isEmpty()
{
	return m_bEmpty;
}


ptr<image> modalityVOILUT::allocateOutputImage(ptr<image> pInputImage, std::uint32_t width, std::uint32_t height)
{
	if(isEmpty())
	{
        ptr<image> newImage(new image());
		newImage->create(width, height, pInputImage->getDepth(), pInputImage->getColorSpace(), pInputImage->getHighBit());
		return newImage;
	}

	// LUT
	///////////////////////////////////////////////////////////
	if(m_voiLut != 0 && m_voiLut->getSize() != 0 && m_voiLut->checkValidDataRange())
	{
		std::uint8_t bits(m_voiLut->getBits());

		// Look for negative outputs
		bool bNegative(false);
		for(std::int32_t index(m_voiLut->getFirstMapped()), size(m_voiLut->getSize()); !bNegative && size != 0; --size, ++index)
		{
			bNegative = (m_voiLut->mappedValue(index) < 0);
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

	// Rescale
	///////////////////////////////////////////////////////////
	if(m_rescaleSlope == 0)
	{
		ptr<image> returnImage(new image);
		returnImage->create(width, height, pInputImage->getDepth(), L"MONOCHROME2", pInputImage->getHighBit());
		return returnImage;
	}

	image::bitDepth inputDepth(pInputImage->getDepth());
	std::uint32_t highBit(pInputImage->getHighBit());

	std::int32_t value0 = 0;
	std::int32_t value1 = ((std::int32_t)1 << (highBit + 1)) - 1;
	if(inputDepth == image::depthS16 || inputDepth == image::depthS8)
	{
		value0 = ((std::int32_t)(-1) << highBit);
		value1 = ((std::int32_t)1 << highBit);
	}
	std::int32_t finalValue0((std::int32_t) ((double)value0 * m_rescaleSlope + m_rescaleIntercept + 0.5) );
	std::int32_t finalValue1((std::int32_t) ((double)value1 * m_rescaleSlope + m_rescaleIntercept + 0.5) );

	std::int32_t minValue, maxValue;
	if(finalValue0 < finalValue1)
	{
		minValue = finalValue0;
		maxValue = finalValue1;
	}
	else
	{
		minValue = finalValue1;
		maxValue = finalValue0;
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
