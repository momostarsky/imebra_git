/*
$fileHeader$
*/

/*! \file image.cpp
    \brief Implementation of the class image.

*/

#include "exceptionImpl.h"
#include "imageImpl.h"
#include "colorTransformsFactoryImpl.h"
#include "bufferImpl.h"
#include "../include/imebra/exceptions.h"

namespace imebra
{

namespace implementation
{

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
//
// image
//
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Create an image with the specified size, colorspace and
//  bit depth
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::shared_ptr<handlers::writingDataHandlerNumericBase> image::create(
						const std::uint32_t sizeX, 
						const std::uint32_t sizeY, 
						const bitDepth depth, 
                        const std::string& inputColorSpace,
                        const std::uint32_t highBit)
{
    IMEBRA_FUNCTION_START();

	if(sizeX == 0 || sizeY == 0)
	{
        IMEBRA_THROW(ImageInvalidSizeError, "An invalid image's size has been specified");
	}

	// Normalize the color space (remove _420 & _422 and
	//  make it uppercase).
	///////////////////////////////////////////////////////////
	m_colorSpace=transforms::colorTransforms::colorTransformsFactory::normalizeColorSpace(inputColorSpace);

	// Find the number of channels to allocate
	///////////////////////////////////////////////////////////
	m_channelsNumber = transforms::colorTransforms::colorTransformsFactory::getNumberOfChannels(inputColorSpace);
	if(m_channelsNumber == 0)
	{
        IMEBRA_THROW(ImageUnknownColorSpaceError, "Cannot recognize the specified color space");
	}

	// Find the datatype to use to allocate the
	//  buffer (datatypes are in Dicom standard, plus SB
	//  for signed bytes).
	///////////////////////////////////////////////////////////
	std::uint8_t defaultHighBit = 0;

	std::string bufferDataType;

	switch(depth)
	{
	case depthU8:
		bufferDataType = "OB";
		defaultHighBit=7;
		break;
	case depthS8:
		bufferDataType = "SB";
		defaultHighBit=7;
        break;
	case depthU16:
		bufferDataType = "US";
		defaultHighBit=15;
        break;
	case depthS16:
		bufferDataType = "SS";
		defaultHighBit=15;
        break;
	case depthU32:
		bufferDataType = "UL";
		defaultHighBit=31;
        break;
	case depthS32:
		bufferDataType = "SL";
		defaultHighBit=31;
        break;
	default:
        IMEBRA_THROW(ImageUnknownDepthError, "Unknown depth");
	}

	// Adjust the high bit value
	///////////////////////////////////////////////////////////
	if(highBit == 0 || highBit>defaultHighBit)
		m_highBit=defaultHighBit;
	else
		m_highBit=highBit;

	// If a valid buffer with the same data type is already
	//  allocated then use it.
	///////////////////////////////////////////////////////////
    if(m_buffer.get() == 0 || !(m_buffer.unique()) )
	{
        m_buffer = std::make_shared<buffer>(bufferDataType);
	}

	m_sizeX = m_sizeY = 0;
	
    std::shared_ptr<handlers::writingDataHandler> imageHandler(m_buffer->getWritingDataHandler(sizeX * sizeY * (std::uint32_t)m_channelsNumber) );

    imageHandler->setSize(m_channelsNumber * sizeX * sizeY);

    // Set the attributes
    ///////////////////////////////////////////////////////////
    m_imageDepth=depth;
    m_sizeX=sizeX;
    m_sizeY=sizeY;

    return std::static_pointer_cast<handlers::writingDataHandlerNumericBase>(imageHandler);

	IMEBRA_FUNCTION_END();
}


void image::setPalette(std::shared_ptr<palette> imagePalette)
{
	m_palette = imagePalette;
}



///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Retrieve an handler to the image's buffer.
// The image's components are interleaved.
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::shared_ptr<handlers::readingDataHandlerNumericBase> image::getReadingDataHandler() const
{
    IMEBRA_FUNCTION_START();

	if(m_buffer == 0)
	{
        return std::shared_ptr<handlers::readingDataHandlerNumericBase>(0);
	}

    std::shared_ptr<handlers::readingDataHandler> imageHandler(m_buffer->getReadingDataHandler());

    return std::dynamic_pointer_cast<handlers::readingDataHandlerNumericBase>(imageHandler);

	IMEBRA_FUNCTION_END();
}

std::shared_ptr<handlers::writingDataHandlerNumericBase> image::getWritingDataHandler()
{
    IMEBRA_FUNCTION_START();

    if(m_buffer == 0)
    {
        return std::shared_ptr<handlers::writingDataHandlerNumericBase>(0);
    }

    std::shared_ptr<handlers::writingDataHandler> imageHandler(m_buffer->getWritingDataHandler(m_sizeX * m_sizeY * m_channelsNumber));

    return std::dynamic_pointer_cast<handlers::writingDataHandlerNumericBase>(imageHandler);

    IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Return the bit depth
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
image::bitDepth image::getDepth() const
{
	return m_imageDepth;
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Return the high bit
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::uint32_t image::getHighBit() const
{
	return m_highBit;
}

std::shared_ptr<palette> image::getPalette() const
{
	return m_palette;
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Returns the colorspace
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::string image::getColorSpace() const
{
	return m_colorSpace;
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Returns the numbero of allocated channels
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::uint32_t image::getChannelsNumber() const
{
	return m_channelsNumber;
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Returns the image's size in pixels
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void image::getSize(std::uint32_t* pSizeX, std::uint32_t* pSizeY) const
{
	if(pSizeX)
        *pSizeX = m_sizeX;

	if(pSizeY)
        *pSizeY = m_sizeY;
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Returns the image's size in millimeters
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void image::getSizeMm(double* pSizeMmX, double* pSizeMmY) const
{
    IMEBRA_FUNCTION_START();

	if(pSizeMmX)
        *pSizeMmX = m_sizeMmX;

	if(pSizeMmY)
        *pSizeMmY = m_sizeMmY;

	IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Set the image's size in millimeters
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void image::setSizeMm(const double sizeMmX, const double sizeMmY)
{
    IMEBRA_FUNCTION_START();

    m_sizeMmX = sizeMmX;
    m_sizeMmY = sizeMmY;

	IMEBRA_FUNCTION_END();
}

} // namespace implementation

} // namespace imebra
