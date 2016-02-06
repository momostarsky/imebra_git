/*
$fileHeader$
*/

/*! \file modalityVOILUT.cpp
    \brief Implementation of the class modalityVOILUT.

*/

#define NOMINMAX

#include "exceptionImpl.h"
#include "modalityVOILUTImpl.h"
#include "dataSetImpl.h"
#include "colorTransformsFactoryImpl.h"
#include <math.h>
#include <limits>

namespace imebra
{

namespace implementation
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
modalityVOILUT::modalityVOILUT(std::shared_ptr<const dataSet> pDataSet):
        m_pDataSet(pDataSet), m_voiLut(0), m_rescaleIntercept(pDataSet->getDouble(0x0028, 0, 0x1052, 0, 0, 0)), m_rescaleSlope(1.0), m_bEmpty(true)

{


	// Only monochrome images can have the modality voi-lut
	///////////////////////////////////////////////////////
    const std::string colorSpace(pDataSet->getStringThrow(0x0028, 0x0, 0x0004, 0, 0));

	if(!colorTransforms::colorTransformsFactory::isMonochrome(colorSpace))
	{
		return;
	}

    try
    {
        std::shared_ptr<handlers::readingDataHandler> rescaleHandler(m_pDataSet->getReadingDataHandlerThrow(0x0028, 0, 0x1053, 0x0));
        m_rescaleSlope = rescaleHandler->getDouble(0);
        m_bEmpty = false;
    }
    catch(const MissingDataElementError&)
    {
        try
        {
            m_voiLut = pDataSet->getLutThrow(0x0028, 0x3000, 0);
            m_bEmpty = m_voiLut->getSize() != 0;
        }
        catch(const MissingDataElementError&)
        {
            // Nothing to do. Transformis empty
        }

    }
}

bool modalityVOILUT::isEmpty() const
{
	return m_bEmpty;
}


std::shared_ptr<image> modalityVOILUT::allocateOutputImage(
        image::bitDepth inputDepth,
        const std::string& inputColorSpace,
        std::uint32_t inputHighBit,
        std::shared_ptr<palette> /* inputPalette */,
        std::uint32_t outputWidth, std::uint32_t outputHeight) const
{
	if(isEmpty())
	{
        std::shared_ptr<image> newImage(std::make_shared<image>());
        newImage->create(outputWidth, outputHeight, inputDepth, inputColorSpace, inputHighBit);
		return newImage;
	}

	// LUT
	///////////////////////////////////////////////////////////
	if(m_voiLut != 0 && m_voiLut->getSize() != 0 && m_voiLut->checkValidDataRange())
	{
		std::uint8_t bits(m_voiLut->getBits());

		// Look for negative outputs
		bool bNegative(false);
        for(std::int32_t index(m_voiLut->getFirstMapped()), size((std::int32_t)m_voiLut->getSize()); !bNegative && size != 0; --size, ++index)
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
        std::shared_ptr<image> returnImage(std::make_shared<image>());
        returnImage->create(outputWidth, outputHeight, depth, inputColorSpace, bits - 1);
		return returnImage;
	}

	// Rescale
	///////////////////////////////////////////////////////////
    if(fabs(m_rescaleSlope) <= std::numeric_limits<double>::denorm_min())
	{
        std::shared_ptr<image> returnImage(std::make_shared<image>());
        returnImage->create(outputWidth, outputHeight, inputDepth, inputColorSpace, inputHighBit);
		return returnImage;
	}

	std::int32_t value0 = 0;
    std::int32_t value1 = ((std::int32_t)1 << (inputHighBit + 1)) - 1;
	if(inputDepth == image::depthS16 || inputDepth == image::depthS8)
	{
        value0 = ((std::int32_t)(-1) << inputHighBit);
        value1 = ((std::int32_t)1 << inputHighBit);
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

    std::shared_ptr<image> returnImage(std::make_shared<image>());
	if(minValue >= 0 && maxValue <= 255)
	{
        returnImage->create(outputWidth, outputHeight, image::depthU8, inputColorSpace, 7);
		return returnImage;
	}
	if(minValue >= -128 && maxValue <= 127)
	{
        returnImage->create(outputWidth, outputHeight, image::depthS8, inputColorSpace, 7);
		return returnImage;
	}
	if(minValue >= 0 && maxValue <= 65535)
	{
        returnImage->create(outputWidth, outputHeight, image::depthU16, inputColorSpace, 15);
		return returnImage;
	}
	if(minValue >= -32768 && maxValue <= 32767)
	{
        returnImage->create(outputWidth, outputHeight, image::depthS16, inputColorSpace, 15);
		return returnImage;
	}
    returnImage->create(outputWidth, outputHeight, image::depthS32, inputColorSpace, 31);
	return returnImage;
}



} // namespace transforms

} // namespace implementation

} // namespace imebra
