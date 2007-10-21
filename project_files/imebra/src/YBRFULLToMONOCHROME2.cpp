/*
$fileHeader$
*/

/*! \file YBRFULLToMONOCHROME2.cpp
    \brief Implementation of the class YBRFULLToMONOCHROME2.

*/

#include "../../base/include/exception.h"
#include "../include/YBRFULLToMONOCHROME2.h"
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

static registerColorTransform m_registerTransform(ptr<colorTransform>(new YBRFULLToMONOCHROME2));

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Return the initial color space
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::wstring YBRFULLToMONOCHROME2::getInitialColorSpace()
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
std::wstring YBRFULLToMONOCHROME2::getFinalColorSpace()
{
	return L"MONOCHROME2";
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Create a new YBRFULLToMONOCHROME2 object
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
ptr<colorTransform> YBRFULLToMONOCHROME2::createColorTransform()
{
	return ptr<colorTransform>(new YBRFULLToMONOCHROME2);
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// YBR_FULL to MONOCHROME2 transformation
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void YBRFULLToMONOCHROME2::doColorTransform(imbxInt32* pSourceMem, imbxInt32* pDestMem, imbxUint32 pixelsNumber, imbxInt32 inputMinValue, imbxInt32 /* inputMaxValue */, imbxInt32 outputMinValue, imbxInt32 outputMaxValue)
{
	imbxInt32 sourcePixelY;
	while(pixelsNumber--)
	{
		sourcePixelY= *pSourceMem++ - inputMinValue + outputMinValue;
		++pSourceMem;
		++pSourceMem;

		if(sourcePixelY<outputMinValue)
			sourcePixelY=outputMinValue;
		if(sourcePixelY>outputMaxValue)
			sourcePixelY=outputMaxValue;

		*pDestMem++ = sourcePixelY;
	}
}

} // namespace colorTransforms

} // namespace transforms

} // namespace imebra

} // namespace puntoexe

