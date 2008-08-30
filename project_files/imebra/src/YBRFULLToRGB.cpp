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
	static const int precisionBits(14);
	static const double multiplier((double)((imbxInt32)1 << precisionBits));
	static const imbxInt32 multiplier0_5((imbxUint32)1 << (precisionBits - 1));
	static const imbxInt32 multiplier1_4020((imbxInt32)(1.402f * multiplier + 0.5));
	static const imbxInt32 multiplier0_34414((imbxInt32)(0.34414f * multiplier + 0.5));
	static const imbxInt32 multiplier0_71414((imbxInt32)(0.71414f * multiplier + 0.5));
	static const imbxInt32 multiplier1_772((imbxInt32)(1.772f * multiplier + 0.5));

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
		destPixelR = sourcePixelY + ( ( multiplier1_4020 * sourcePixelR + multiplier0_5) >> precisionBits);
		destPixelG = sourcePixelY - ( ( multiplier0_34414 * sourcePixelB + multiplier0_71414 * sourcePixelR + multiplier0_5) >> precisionBits);
		destPixelB = sourcePixelY + ( ( multiplier1_772 * sourcePixelB + multiplier0_5) >> precisionBits);

		if(destPixelR<outputMinValue)
		{
			destPixelR=outputMinValue;
		}
		else if(destPixelR>outputMaxValue)
		{
			destPixelR=outputMaxValue;
		}

		if(destPixelG<outputMinValue)
		{
			destPixelG=outputMinValue;
		}
		else if(destPixelG>outputMaxValue)
		{
			destPixelG=outputMaxValue;
		}

		if(destPixelB<outputMinValue)
		{
			destPixelB=outputMinValue;
		}
		else if(destPixelB>outputMaxValue)
		{
			destPixelB=outputMaxValue;
		}

		*pDestMem++ = destPixelR;
		*pDestMem++ = destPixelG;
		*pDestMem++ = destPixelB;
	}
}

} // namespace colorTransforms

} // namespace transforms

} // namespace imebra

} // namespace puntoexe

