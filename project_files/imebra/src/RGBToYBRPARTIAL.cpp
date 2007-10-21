/*
$fileHeader$
*/

/*! \file RGBToYBRPARTIAL.cpp
    \brief Implementation of the class RGBToYBRPARTIAL.

*/

#include "../../base/include/exception.h"
#include "../include/RGBToYBRPARTIAL.h"
#include "../include/dataHandler.h"
#include "../include/dataSet.h"
#include "../include/image.h"

namespace puntoexe
{

namespace imebra
{

namespace transforms
{

namespace colorTransforms
{

static registerColorTransform m_registerTransform(ptr<colorTransform>(new RGBToYBRPARTIAL));


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Return the initial color space
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::wstring RGBToYBRPARTIAL::getInitialColorSpace()
{
	return L"RGB";
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Return the final color space
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::wstring RGBToYBRPARTIAL::getFinalColorSpace()
{
	return L"YBR_PARTIAL";
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Create a RGBToYBRPARTIAL object
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
ptr<colorTransform> RGBToYBRPARTIAL::createColorTransform()
{
	return ptr<colorTransform>(new RGBToYBRPARTIAL);
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// RGB to YBR_FULL transformation
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void RGBToYBRPARTIAL::doColorTransform(imbxInt32* pSourceMem, imbxInt32* pDestMem, imbxUint32 pixelsNumber, imbxInt32 /* inputMinValue */, imbxInt32 /* inputMaxValue */, imbxInt32 outputMinValue, imbxInt32 outputMaxValue)
{
	imbxInt32 sourcePixelR;
	imbxInt32 sourcePixelG;
	imbxInt32 sourcePixelB;
	imbxInt32 destPixelY;
	imbxInt32 destPixelB;
	imbxInt32 destPixelR;
	imbxInt32 middleValue=(outputMaxValue-outputMinValue+1)>>1;
	while(pixelsNumber--)
	{
		sourcePixelR=*pSourceMem++;
		sourcePixelG=*pSourceMem++;
		sourcePixelB=*pSourceMem++;

		///////////////////////////////////////////////////////////
		// Conversion
		///////////////////////////////////////////////////////////
		destPixelY=(middleValue>>3)+(((imbxInt32)1052*sourcePixelR+(imbxInt32)2065*sourcePixelG+(imbxInt32)401*sourcePixelB)>>12);
		destPixelB=middleValue+(((imbxInt32)1799*sourcePixelB-(imbxInt32)607*sourcePixelR-(imbxInt32)1192*sourcePixelG)>>12);
		destPixelR=middleValue+(((imbxInt32)1799*sourcePixelR-(imbxInt32)1507*sourcePixelG-(imbxInt32)292*sourcePixelB)>>12);

		if(destPixelY<outputMinValue)
			destPixelY=outputMinValue;
		if(destPixelY>outputMaxValue)
			destPixelY=outputMaxValue;
		if(destPixelB<outputMinValue)
			destPixelB=outputMinValue;
		if(destPixelB>outputMaxValue)
			destPixelB=outputMaxValue;
		if(destPixelR<outputMinValue)
			destPixelR=outputMinValue;
		if(destPixelR>outputMaxValue)
			destPixelR=outputMaxValue;

		*pDestMem++ = destPixelY;
		*pDestMem++ = destPixelB;
		*pDestMem++ = destPixelR;
	}
}

} // namespace colorTransforms

} // namespace transforms

} // namespace imebra

} // namespace puntoexe


