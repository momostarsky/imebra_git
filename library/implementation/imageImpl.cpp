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

namespace puntoexe
{

namespace imebra
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
std::shared_ptr<handlers::dataHandlerNumericBase> image::create(
						const std::uint32_t sizeX, 
						const std::uint32_t sizeY, 
						const bitDepth depth, 
						std::wstring inputColorSpace, 
						const std::uint8_t highBit)
{
	PUNTOEXE_FUNCTION_START(L"image::create");

	if(sizeX == 0 || sizeY == 0)
	{
		PUNTOEXE_THROW(imageExceptionInvalidSize, "An invalid image's size has been specified");
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
		PUNTOEXE_THROW(imageExceptionUnknownColorSpace, "Cannot recognize the specified color space");
	}

	// Find the datatype to use to allocate the
	//  buffer (datatypes are in Dicom standard, plus SB
	//  for signed bytes).
	///////////////////////////////////////////////////////////
	m_channelPixelSize = 0;
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
		PUNTOEXE_THROW(imageExceptionUnknownDepth, "Unknown depth");
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
	
	std::shared_ptr<handlers::dataHandler> imageHandler(m_buffer->getDataHandler(true, sizeX * sizeY * (std::uint32_t)m_channelsNumber) );
	if(imageHandler != 0)
	{
		m_rowLength = m_channelsNumber*sizeX;
		
		imageHandler->setSize(m_rowLength*sizeY);
		m_channelPixelSize = imageHandler->getUnitSize();

		// Set the attributes
		///////////////////////////////////////////////////////////
		m_imageDepth=depth;
		m_sizeX=sizeX;
		m_sizeY=sizeY;
	}

    return std::static_pointer_cast<handlers::dataHandlerNumericBase>(imageHandler);

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Set the depth
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void image::setHighBit(std::uint32_t highBit)
{
	m_highBit = highBit;
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
std::shared_ptr<handlers::dataHandlerNumericBase> image::getDataHandler(const bool bWrite, std::uint32_t* pRowSize, std::uint32_t* pChannelPixelSize, std::uint32_t* pChannelsNumber)
{
	PUNTOEXE_FUNCTION_START(L"image::getDataHandler");

	if(m_buffer == 0)
	{
		return std::shared_ptr<handlers::dataHandlerNumericBase>(0);
	}

	*pRowSize=m_rowLength;
	*pChannelPixelSize=m_channelPixelSize;
	*pChannelsNumber=m_channelsNumber;

	std::shared_ptr<handlers::dataHandler> imageHandler(m_buffer->getDataHandler(bWrite, m_sizeX * m_sizeY * m_channelsNumber));

    return std::static_pointer_cast<handlers::dataHandlerNumericBase>(imageHandler);

	PUNTOEXE_FUNCTION_END();
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
image::bitDepth image::getDepth()
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
std::uint32_t image::getHighBit()
{
	return m_highBit;
}

std::shared_ptr<palette> image::getPalette()
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
std::wstring image::getColorSpace()
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
std::uint32_t image::getChannelsNumber()
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
void image::getSize(std::uint32_t* pSizeX, std::uint32_t* pSizeY)
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
void image::getSizeMm(double* pSizeMmX, double* pSizeMmY)
{
	PUNTOEXE_FUNCTION_START(L"image::getSizeMm");

	if(pSizeMmX)
		*pSizeMmX=m_sizeMmX;

	if(pSizeMmY)
		*pSizeMmY=m_sizeMmY;

	PUNTOEXE_FUNCTION_END();
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
	PUNTOEXE_FUNCTION_START(L"image::setSizeMm");

	if(sizeMmX)
		m_sizeMmX=sizeMmX;

	if(sizeMmY)
		m_sizeMmY=sizeMmY;

	PUNTOEXE_FUNCTION_END();
}

} // namespace imebra

} // namespace puntoexe
