/*
$fileHeader$
*/

/*! \file RGBToYBRFULL.cpp
    \brief Implementation of the class RGBToYBRFULL.

*/

#include "../../base/include/exception.h"
#include "../include/RGBToYBRFULL.h"
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

static registerColorTransform m_registerTransform(ptr<colorTransform>(new RGBToYBRFULL));

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Return the initial color space
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::wstring RGBToYBRFULL::getInitialColorSpace()
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
std::wstring RGBToYBRFULL::getFinalColorSpace()
{
	return L"YBR_FULL";
}


ptr<colorTransform> RGBToYBRFULL::createColorTransform()
{
	return ptr<colorTransform>(new RGBToYBRFULL);
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
void RGBToYBRFULL::doColorTransform(imbxInt32* pSourceMem, imbxInt32* pDestMem, imbxUint32 pixelsNumber, imbxInt32 /* inputMinValue */, imbxInt32 /* inputMaxValue */, imbxInt32 outputMinValue, imbxInt32 outputMaxValue)
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
		destPixelY=((imbxInt32)1225*sourcePixelR+(imbxInt32)2404*sourcePixelG+(imbxInt32)581*sourcePixelB)>>12;
		destPixelB=middleValue+(((imbxInt32)2048*sourcePixelB-(imbxInt32)691*sourcePixelR-(imbxInt32)1357*sourcePixelG)>>12);
		destPixelR=middleValue+(((imbxInt32)2048*sourcePixelR-(imbxInt32)1715*sourcePixelG-(imbxInt32)333*sourcePixelB)>>12);

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

