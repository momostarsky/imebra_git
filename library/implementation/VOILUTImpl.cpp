/*
$fileHeader$
*/

/*! \file VOILUT.cpp
    \brief Implementation of the class VOILUT.

*/

#include "exceptionImpl.h"
#include "VOILUTImpl.h"
#include "dataSetImpl.h"
#include "../include/imebra/exceptions.h"

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
// Set the lut
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void VOILUT::setLUT(std::shared_ptr<lut> pLut)
{
	m_pLUT = pLut;
	m_windowCenter = 0;
	m_windowWidth = 0;
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Set the center/width
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void VOILUT::setCenterWidth(double center, double width)
{
	m_windowCenter = center;
	m_windowWidth = width;
    m_pLUT.reset();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Get the center/width
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void VOILUT::getCenterWidth(double* pCenter, double* pWidth)
{
	*pCenter = m_windowCenter;
	*pWidth = m_windowWidth;
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Returns true if the transform is empty
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
bool VOILUT::isEmpty() const
{
	return m_windowWidth <= 1 && (m_pLUT == 0 || m_pLUT->getSize() == 0);
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Allocate the output image
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::shared_ptr<image> VOILUT::allocateOutputImage(
        bitDepth_t inputDepth,
        const std::string& inputColorSpace,
        std::uint32_t inputHighBit,
        std::shared_ptr<palette> /* inputPalette */,
        std::uint32_t outputWidth, std::uint32_t outputHeight) const
{
    IMEBRA_FUNCTION_START();

    if(isEmpty())
	{
        return std::make_shared<image>(outputWidth, outputHeight, inputDepth, inputColorSpace, inputHighBit);
	}

	if(m_pLUT != 0 && m_pLUT->getSize() != 0)
	{
		std::uint8_t bits = m_pLUT->getBits();

		bool bNegative(false);
        for(std::int32_t index(m_pLUT->getFirstMapped()), size((std::int32_t)m_pLUT->getSize()); !bNegative && size != 0; --size, ++index)
		{
			bNegative = (m_pLUT->mappedValue(index) < 0);
		}

		if(bNegative)
		{
            inputDepth = bits > 8 ? bitDepth_t::depthS16 : bitDepth_t::depthS8;
		}
		else
		{
            inputDepth = bits > 8 ? bitDepth_t::depthU16 : bitDepth_t::depthU8;
		}
        return std::make_shared<image>(outputWidth, outputHeight, inputDepth, inputColorSpace, bits - 1);
	}

	//
	// LUT not found.
	// Use the window's center/width
	//
	///////////////////////////////////////////////////////////
	if(m_windowWidth <= 1)
	{
        return std::make_shared<image>(outputWidth, outputHeight, inputDepth, inputColorSpace, inputHighBit);
	}

    if(inputDepth == bitDepth_t::depthS8)
        inputDepth = bitDepth_t::depthU8;
    if(inputDepth == bitDepth_t::depthS16 || inputDepth == bitDepth_t::depthU32 || inputDepth == bitDepth_t::depthS32)
        inputDepth = bitDepth_t::depthU16;

    return std::make_shared<image>(outputWidth, outputHeight, inputDepth, inputColorSpace, inputHighBit);

    IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Finds and applies the optimal VOI.
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void VOILUT::applyOptimalVOI(const std::shared_ptr<imebra::implementation::image>& inputImage, std::uint32_t inputTopLeftX, std::uint32_t inputTopLeftY, std::uint32_t inputWidth, std::uint32_t inputHeight)
{
    IMEBRA_FUNCTION_START();

    std::uint32_t width, height;
    inputImage->getSize(&width, &height);

    if(inputTopLeftX + inputWidth > width || inputTopLeftY + inputHeight > height)
    {
        IMEBRA_THROW(TransformInvalidAreaError, "The input and/or output areas are invalid");
    }

    std::shared_ptr<handlers::readingDataHandlerNumericBase> handler(inputImage->getReadingDataHandler());
    HANDLER_CALL_TEMPLATE_FUNCTION_WITH_PARAMS(templateFindOptimalVOI, handler, width, inputTopLeftX, inputTopLeftY, inputWidth, inputHeight);

    IMEBRA_FUNCTION_END();
}




} // namespace transforms

} // namespace implementation

} // namespace imebra
