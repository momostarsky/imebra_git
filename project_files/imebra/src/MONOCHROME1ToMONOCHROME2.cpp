/*
$fileHeader$
*/

/*! \file MONOCHROME1ToMONOCHROME2.cpp
    \brief Implementation of the classes for conversion between 2 monochrome color spaces.

*/

#include "../../base/include/exception.h"
#include "../include/MONOCHROME1ToMONOCHROME2.h"
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

static registerColorTransform m_registerTransform0(ptr<colorTransform>(new MONOCHROME1ToMONOCHROME2));
static registerColorTransform m_registerTransform1(ptr<colorTransform>(new MONOCHROME2ToMONOCHROME1));

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Return the initial color space
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::wstring MONOCHROME1ToMONOCHROME2::getInitialColorSpace()
{
	return L"MONOCHROME1";
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
std::wstring MONOCHROME1ToMONOCHROME2::getFinalColorSpace()
{
	return L"MONOCHROME2";
}

ptr<colorTransform> MONOCHROME1ToMONOCHROME2::createColorTransform()
{
	return ptr<colorTransform> (new MONOCHROME1ToMONOCHROME2);
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// MONOCHROME1 to MONOCHROME2 transformation
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void MONOCHROME1ToMONOCHROME2::doColorTransform(imbxInt32* pSourceMem, imbxInt32* pDestMem, imbxUint32 pixelsNumber, imbxInt32 /* inputMinValue */, imbxInt32 inputMaxValue, imbxInt32 outputMinValue, imbxInt32 outputMaxValue)
{
	imbxInt32 destPixel;
	imbxInt32 offset=inputMaxValue+outputMinValue;
	while(pixelsNumber--)
	{
		///////////////////////////////////////////////////////////
		// Conversion
		///////////////////////////////////////////////////////////
		destPixel=offset - *pSourceMem++;

		if(destPixel<outputMinValue)
			destPixel=outputMinValue;
		if(destPixel>outputMaxValue)
			destPixel=outputMaxValue;

		*pDestMem++ = destPixel;
	}
}



///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Return the initial color space
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::wstring MONOCHROME2ToMONOCHROME1::getInitialColorSpace()
{
	return L"MONOCHROME2";
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
std::wstring MONOCHROME2ToMONOCHROME1::getFinalColorSpace()
{
	return L"MONOCHROME1";
}

ptr<colorTransform> MONOCHROME2ToMONOCHROME1::createColorTransform()
{
	return ptr<colorTransform> (new MONOCHROME2ToMONOCHROME1);
}

} // namespace colorTransforms

} // namespace transforms

} // namespace imebra

} // namespace puntoexe

