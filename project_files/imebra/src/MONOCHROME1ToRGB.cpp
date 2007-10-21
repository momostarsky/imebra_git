/*
$fileHeader$
*/

/*! \file MONOCHROME1ToRGB.cpp
    \brief Implementation of the class MONOCHROME1ToRGB.

*/

#include "../../base/include/exception.h"
#include "../include/MONOCHROME1ToRGB.h"
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


static registerColorTransform m_registerTransform(ptr<colorTransform>(new MONOCHROME1ToRGB));


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Return the initial color space
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::wstring MONOCHROME1ToRGB::getInitialColorSpace()
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
std::wstring MONOCHROME1ToRGB::getFinalColorSpace()
{
	return L"RGB";
}

ptr<colorTransform> MONOCHROME1ToRGB::createColorTransform()
{
	return ptr<colorTransform>(new MONOCHROME1ToRGB);
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// MONOCHROME1 to RGB transformation
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void MONOCHROME1ToRGB::doColorTransform(imbxInt32* pSourceMem, imbxInt32* pDestMem, imbxUint32 pixelsNumber, imbxInt32 /* inputMinValue */, imbxInt32 inputMaxValue, imbxInt32 outputMinValue, imbxInt32 outputMaxValue)
{
	imbxInt32 sourcePixel;
	imbxInt32 offset=inputMaxValue+outputMinValue;

	while(pixelsNumber--)
	{
		sourcePixel=offset - *pSourceMem++;

		if(sourcePixel<outputMinValue)
			sourcePixel=outputMinValue;
		if(sourcePixel>outputMaxValue)
			sourcePixel=outputMaxValue;

		*pDestMem++ = sourcePixel;
		*pDestMem++ = sourcePixel;
		*pDestMem++ = sourcePixel;
	}
}

} // namespace colorTransforms

} // namespace transforms

} // namespace imebra

} // namespace puntoexe

