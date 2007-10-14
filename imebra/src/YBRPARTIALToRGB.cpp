/*
$fileHeader$
*/

/*! \file YBRPARTIALToRGB.cpp
    \brief Implementation of the class YBRPARTIALToRGB.

*/

#include "../../base/include/exception.h"
#include "../include/YBRPARTIALToRGB.h"
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

static registerColorTransform m_registerTransform(ptr<colorTransform>(new YBRPARTIALToRGB));

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Return the initial color space
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::wstring YBRPARTIALToRGB::getInitialColorSpace()
{
	return L"YBR_PARTIAL";
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
std::wstring YBRPARTIALToRGB::getFinalColorSpace()
{
	return L"RGB";
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Create a new YBRPARTIALToRGB object
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
ptr<colorTransform> YBRPARTIALToRGB::createColorTransform()
{
	return ptr<colorTransform>(new YBRPARTIALToRGB);
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// RGB to YBR_PARTIAL transformation
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void YBRPARTIALToRGB::doColorTransform(imbxInt32* pSourceMem, imbxInt32* pDestMem, imbxUint32 pixelsNumber, imbxInt32 inputMinValue, imbxInt32 inputMaxValue, imbxInt32 outputMinValue, imbxInt32 outputMaxValue)
{
	imbxInt32 sourcePixelY;
	imbxInt32 sourcePixelB;
	imbxInt32 sourcePixelR;
	imbxInt32 destPixelR;
	imbxInt32 destPixelG;
	imbxInt32 destPixelB;
	imbxInt32 middleValue=(inputMaxValue-inputMinValue+1)>>1;
	while(pixelsNumber--)
	{
		sourcePixelY = *pSourceMem++ - (middleValue >> 3);
		sourcePixelB = *pSourceMem++ - middleValue;
		sourcePixelR = *pSourceMem++ - middleValue;

		///////////////////////////////////////////////////////////
		// Conversion
		///////////////////////////////////////////////////////////
		imbxInt32 Y1164 = (imbxInt32)4768* sourcePixelY;
		destPixelR =  (Y1164 + (imbxInt32)6427 * sourcePixelR) >> 12;
		destPixelG =  (Y1164 - (imbxInt32)1602 * sourcePixelB - (imbxInt32)3330 * sourcePixelR)>>12;
		destPixelB =  (Y1164 + (imbxInt32)8266 * sourcePixelB) >> 12;

		if(destPixelR<outputMinValue)
			destPixelR=outputMinValue;
		if(destPixelR>outputMaxValue)
			destPixelR=outputMaxValue;
		if(destPixelG<outputMinValue)
			destPixelG=outputMinValue;
		if(destPixelG>outputMaxValue)
			destPixelG=outputMaxValue;
		if(destPixelB<outputMinValue)
			destPixelB=outputMinValue;
		if(destPixelB>outputMaxValue)
			destPixelB=outputMaxValue;

		*pDestMem++ = destPixelR;
		*pDestMem++ = destPixelG;
		*pDestMem++ = destPixelB;
	}
}

} // namespace colorTransforms

} // namespace transforms

} // namespace imebra

} // namespace puntoexe

