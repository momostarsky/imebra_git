/*
$fileHeader$
*/

/*! \file YBRFULLToRGB.cpp
    \brief Implementation of the class YBRFULLToRGB.

*/

#include "../../base/include/exception.h"
#include "../include/YBRFULLToRGB.h"
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

static registerColorTransform m_registerTransform(ptr<colorTransform>(new YBRFULLToRGB));

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Return the initial color space
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::wstring YBRFULLToRGB::getInitialColorSpace()
{
	return L"YBR_FULL";
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
std::wstring YBRFULLToRGB::getFinalColorSpace()
{
	return L"RGB";
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Create a new YBRFULLToRGB object
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
ptr<colorTransform> YBRFULLToRGB::createColorTransform()
{
	return ptr<colorTransform>(new YBRFULLToRGB);
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
void YBRFULLToRGB::doColorTransform(imbxInt32* pSourceMem, imbxInt32* pDestMem, imbxUint32 pixelsNumber, imbxInt32 inputMinValue, imbxInt32 inputMaxValue, imbxInt32 outputMinValue, imbxInt32 outputMaxValue)
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
		sourcePixelY = *pSourceMem++;
		sourcePixelB = *pSourceMem++ - middleValue;
		sourcePixelR = *pSourceMem++ - middleValue;

		///////////////////////////////////////////////////////////
		// Conversion
		///////////////////////////////////////////////////////////
		destPixelR = sourcePixelY + ( ( (imbxInt32)5743 * sourcePixelR) >> 12);
		destPixelG = sourcePixelY - ( ( (imbxInt32)1410 * sourcePixelB + (imbxInt32)2925 * sourcePixelR)>>12);
		destPixelB = sourcePixelY + ( ( (imbxInt32)7258 * sourcePixelB) >> 12);

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

