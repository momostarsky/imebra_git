/*
$fileHeader$
*/

/*! \file VOILUT.cpp
    \brief Implementation of the class VOILUT.

*/

#include "../../base/include/exception.h"
#include "../include/VOILUT.h"
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
// Retrieve an ID for a VOI LUT module.
// Returns NULL if the requested VOI LUT module doesn't
//  exist
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
imbxUint32 VOILUT::getVOILUTId(imbxUint32 VOILUTNumber)
{
	PUNTOEXE_FUNCTION_START(L"VOILUT::getVOILUTId");

	// reset the LUT's ID
	///////////////////////////////////////////////////////////
	imbxUint32 VOILUTId = 0;

	// If the dataset has not been set, then return NULL
	///////////////////////////////////////////////////////////
	if(m_pDataSet == 0)
	{
		return 0;
	}

	// Reset the window's center and width
	///////////////////////////////////////////////////////////
	imbxInt32 windowWidth = 0;
	imbxInt32 windowCenter = 0;

	// Scan all the window's centers and widths.
	///////////////////////////////////////////////////////////
	imbxUint32 scanWindow;
	for(scanWindow=VOILUTNumber; (windowWidth == 0) && (scanWindow!=0xffffffff); --scanWindow)
	{
		windowCenter = m_pDataSet->getSignedLong(0x0028, 0, 0x1050, scanWindow);
		windowWidth  = m_pDataSet->getSignedLong(0x0028, 0, 0x1051, scanWindow);
	}
	++scanWindow;

	// If the window's center/width has not been found or it
	//  is not inside the VOILUTNumber parameter, then
	//  look in the LUTs
	///////////////////////////////////////////////////////////
	if(windowWidth == 0 || scanWindow != VOILUTNumber)
	{
		// Find the LUT's ID
		///////////////////////////////////////////////////////////
		VOILUTNumber-=scanWindow;
		ptr<dataSet> voiLut = m_pDataSet->getSequenceItem(0x0028, 0, 0x3010, VOILUTNumber);
		if(voiLut != 0)
		{
			// Set the VOILUTId
			///////////////////////////////////////////////////////////
			VOILUTId=VOILUTNumber | 0x00100000;
		}
	}

	// The window's center/width has been found
	///////////////////////////////////////////////////////////
	else
	{
		// Set the VOILUTId
		///////////////////////////////////////////////////////////
		VOILUTId=VOILUTNumber | 0x00200000;
	}

	// Return the VOILUT's ID
	///////////////////////////////////////////////////////////
	return VOILUTId;

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Returns the VOILUT description
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::wstring VOILUT::getVOILUTDescription(imbxUint32 VOILUTId)
{
	PUNTOEXE_FUNCTION_START(L"VOILUT::getVOILUTDescription");

	std::wstring VOILUTDescription;

	// If the dataset has not been, then return NULL
	///////////////////////////////////////////////////////////
	if(m_pDataSet == 0)
	{
		return VOILUTDescription;
	}

	imbxUint32 VOILUTNumber=VOILUTId & 0x0000ffff;

	// Window's center/width
	///////////////////////////////////////////////////////////
	if((VOILUTId & 0x00200000))
	{
		VOILUTDescription = m_pDataSet->getUnicodeString(0x0028, 0, 0x1055, VOILUTNumber);
	}

	// LUT
	///////////////////////////////////////////////////////////
	if((VOILUTId & 0x00100000))
	{
		ptr<lut> voiLut = m_pDataSet->getLut(0x0028, 0x3010, VOILUTNumber);
		if(voiLut != 0)
		{
			VOILUTDescription=voiLut->getDescription();
		}
	}

	return VOILUTDescription;

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Set the VOI/LUT module to use for the transformation.
// You can retrieve the VOILUTId using the function
//  GetVOILUTId().
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void VOILUT::setVOILUT(imbxUint32 VOILUTId)
{
	PUNTOEXE_FUNCTION_START(L"VOILUT::setVOILUT");

	// If the dataset has not been set, then return NULL
	///////////////////////////////////////////////////////////
	if(m_pDataSet == 0)
	{
		return;
	}

	imbxUint32 VOILUTNumber=VOILUTId & 0x0000ffff;

	// Window's center/width
	///////////////////////////////////////////////////////////
	if((VOILUTId & 0x00200000))
	{
		setCenterWidth(
			m_pDataSet->getSignedLong(0x0028, 0, 0x1050, VOILUTNumber),
			m_pDataSet->getSignedLong(0x0028, 0, 0x1051, VOILUTNumber));
		return;
	}

	// LUT
	///////////////////////////////////////////////////////////
	if((VOILUTId & 0x00100000))
	{
		setLUT(m_pDataSet->getLut(0x0028, 0x3010, VOILUTNumber));
		return;
	}

	setCenterWidth(0, 0);

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Set the lut
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void VOILUT::setLUT(ptr<lut> pLut)
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
void VOILUT::setCenterWidth(imbxInt32 center, imbxInt32 width)
{
	m_windowCenter = center;
	m_windowWidth = width;
	m_pLUT.release();
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
void VOILUT::getCenterWidth(imbxInt32* pCenter, imbxInt32* pWidth)
{
	*pCenter = m_windowCenter;
	*pWidth = m_windowWidth;
}


bool VOILUT::isEmpty()
{
	return m_windowWidth <= 1 && m_pLUT == 0;
}

ptr<image> VOILUT::allocateOutputImage(ptr<image> pInputImage, imbxUint32 width, imbxUint32 height)
{
	ptr<image> outputImage(new image);

	image::bitDepth depth = pInputImage->getDepth();
	if(m_pLUT != 0 && m_pLUT->getSize())
	{
		imbxUint8 bits = m_pLUT->getBits();

		bool bNegative(false);
		for(imbxInt32 index(m_pLUT->getFirstMapped()), size(m_pLUT->getSize()); !bNegative && size != 0; --size, ++index)
		{
			bNegative = (m_pLUT->mappedValue(index) < 0);
		}

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

	//
	// LUT not found.
	// Use the window's center/width
	//
	///////////////////////////////////////////////////////////
	if(m_windowWidth <= 1)
	{
		outputImage->create(width, height, depth, pInputImage->getColorSpace(), pInputImage->getHighBit());
		return outputImage;
	}

	if(depth == image::depthS8)
		depth = image::depthU8;
	if(depth == image::depthS16 || depth == image::depthU32 || depth == image::depthS32)
		depth = image::depthU16;

	outputImage->create(width, height, depth, L"MONOCHROME2", pInputImage->getHighBit());

	return outputImage;
}




} // namespace transforms

} // namespace imebra

} // namespace puntoexe
