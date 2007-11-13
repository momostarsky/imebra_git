/*
$fileHeader$
*/

/*! \file VOILUT.cpp
    \brief Implementation of the class VOILUT.

*/

#include "../../base/include/exception.h"
#include "../include/VOILUT.h"
#include "../include/dataSet.h"
#include "../include/LUT.h"


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
	ptr<dataSet> lutDataSet=getDataSet();
	if(lutDataSet == 0)
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
		windowCenter=lutDataSet->getSignedLong(0x0028, 0, 0x1050, scanWindow);
		windowWidth =lutDataSet->getSignedLong(0x0028, 0, 0x1051, scanWindow);
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
		ptr<dataSet> voiLut=lutDataSet->getSequenceItem(0x0028, 0, 0x3010, VOILUTNumber);
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
	ptr<dataSet> lutDataSet=getDataSet();
	if(lutDataSet == 0)
	{
		return VOILUTDescription;
	}

	imbxUint32 VOILUTNumber=VOILUTId & 0x0000ffff;

	// Window's center/width
	///////////////////////////////////////////////////////////
	if((VOILUTId & 0x00200000))
	{
		VOILUTDescription = lutDataSet->getUnicodeString(0x0028, 0, 0x1052, VOILUTNumber);
	}

	// LUT
	///////////////////////////////////////////////////////////
	if((VOILUTId & 0x00100000))
	{
		ptr<lut> voiLut = lutDataSet->getLut(0x0028, 0x3010, VOILUTNumber);
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
	ptr<dataSet> lutDataSet = getDataSet();
	if(lutDataSet == 0)
		return;

	imbxUint32 VOILUTNumber=VOILUTId & 0x0000ffff;

	// Window's center/width
	///////////////////////////////////////////////////////////
	if((VOILUTId & 0x00200000))
	{
		setCenterWidth(
			lutDataSet->getSignedLong(0x0028, 0, 0x1050, VOILUTNumber),
			lutDataSet->getSignedLong(0x0028, 0, 0x1051, VOILUTNumber));
		return;
	}

	// LUT
	///////////////////////////////////////////////////////////
	if((VOILUTId & 0x00100000))
	{
		setLUT(lutDataSet->getLut(0x0028, 0x3010, VOILUTNumber));
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
// VOILUT transformation
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void VOILUT::doTransformBuffers(
		imbxUint32 /* sizeX */,
		imbxUint32 /* sizeY */,
		imbxUint32 /* inputChannelsNumber */,
		std::wstring /* inputColorSpace */,
		image::bitDepth /* inputDepth */,
		imbxUint32 /* inputHighBit */,
		imbxInt32* /* pInputBuffer */,
		imbxInt32* pOutputBuffer,
		imbxUint32 buffersSize,
		image::bitDepth* pOutputDepth,
		imbxUint32* pOutputHighBit)
{
	PUNTOEXE_FUNCTION_START(L"VOILUT::doTransformBuffers");

	//
	// LUT found
	//
	///////////////////////////////////////////////////////////
	if(m_pLUT != 0 && m_pLUT->getSize())
	{
		lut* pLUT = m_pLUT.get();
		imbxUint8 bits = pLUT->getBits();

		*pOutputDepth = image::depthU8;
		if(bits>8)
		{
			*pOutputDepth = image::depthU16;
		}
		*pOutputHighBit = bits-1;

		while(buffersSize--)
		{
			*pOutputBuffer=pLUT->mappedValue(*pOutputBuffer);
			++pOutputBuffer;
		}

		return;
	}

	//
	// LUT not found.
	// Use the window's center/width
	//
	///////////////////////////////////////////////////////////

	// The output is always positive
	if(*pOutputDepth==image::depthS8)
		*pOutputDepth=image::depthU8;
	if(*pOutputDepth==image::depthS16)
		*pOutputDepth=image::depthU16;

	imbxInt32 finalRange=((imbxInt32)1)<<(*pOutputHighBit + 1);

	imbxInt32 minValue=m_windowCenter-(m_windowWidth/2);
	imbxInt32 maxValue=m_windowCenter+(m_windowWidth/2);
	float multFactor=(float)finalRange/(float)(maxValue-minValue);
	if(m_windowWidth <= 0)
	{
		return;
	}

	while(buffersSize--)
	{
		if(*pOutputBuffer  <= minValue)
		{
			*pOutputBuffer++ = 0;
			continue;
		}
		if(*pOutputBuffer >=maxValue)
		{
			*pOutputBuffer++ = finalRange-1;
			continue;
		}
		*pOutputBuffer = (imbxInt32)((float)(*pOutputBuffer - minValue)*multFactor+0.5);
		if(*pOutputBuffer < 0)
			*pOutputBuffer = 0;
		if(*pOutputBuffer >= finalRange)
			*pOutputBuffer = finalRange-1;
		++pOutputBuffer;
	}
	return;

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Inverse VOILUT transformation
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void VOILUTInverse::doTransformBuffers(
		imbxUint32 /* sizeX */, 
		imbxUint32 /* sizeY */,
		imbxUint32 /* inputChannelsNumber */,
		std::wstring /* inputColorSpace */,
		image::bitDepth /* inputDepth */,
		imbxUint32 inputHighBit,
		imbxInt32* /* pInputBuffer */,
		imbxInt32* pOutputBuffer,
		imbxUint32 buffersSize,
		image::bitDepth* pOutputDepth,
		imbxUint32* pOutputHighBit)
{
	PUNTOEXE_FUNCTION_START(L"VOILUTInverse::doTransformBuffers");

	//
	// LUT found
	//
	///////////////////////////////////////////////////////////
	if(m_pLUT != 0 && m_pLUT->getSize())
	{
		*pOutputDepth=image::depthUnknown;
		*pOutputHighBit = 0;
		while(buffersSize--)
		{
			*pOutputBuffer = m_pLUT->mappedValueRev(*pOutputBuffer);
			++pOutputBuffer;
		}

		return;
	}

	//
	// LUT not found.
	// Use the window's center/width
	//
	///////////////////////////////////////////////////////////
	imbxInt32 initialRange = ((imbxInt32)1)<<(inputHighBit+1);

	imbxInt32 minValue = m_windowCenter-(m_windowWidth/2);
	imbxInt32 maxValue = m_windowCenter+(m_windowWidth/2);
	double multFactor = (double)(maxValue-minValue)/(double)initialRange;
	if(m_windowWidth <= 0)
	{
		return;
	}

	*pOutputDepth=image::depthUnknown;
	*pOutputHighBit = 0;
	while(buffersSize--)
	{
		*pOutputBuffer = (imbxInt32)((double)*pOutputBuffer*multFactor+0.5+minValue);
		++pOutputBuffer;
	}

	return;

	PUNTOEXE_FUNCTION_END();
}

} // namespace transforms

} // namespace imebra

} // namespace puntoexe
