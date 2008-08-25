/*
$fileHeader$
*/

/*! \file transformHighBit.cpp
    \brief Implementation of the class transformHighBit.

*/

#include "../../base/include/exception.h"
#include "../include/transformHighBit.h"
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
// Modify the high bit of an image
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void transformHighBit::doTransformBuffersInPlace(
	imbxUint32 /* sizeX */,
	imbxUint32 /* sizeY */,
	imbxUint32 /* inputChannelsNumber */,
	std::wstring /* inputColorSpace */,
	image::bitDepth /* inputDepth */,
	imbxUint32 inputHighBit,
	imbxInt32* pOutputBuffer,
	imbxUint32 buffersSize,
	image::bitDepth* /* pOutputDepth */,
	imbxUint32* pOutputHighBit
	)
{
	PUNTOEXE_FUNCTION_START(L"transformHighBit::doTransformBuffers");

	if(inputHighBit == *pOutputHighBit)
	{
		return;
	}

	if(inputHighBit < *pOutputHighBit)
	{
		imbxUint32 leftShift = *pOutputHighBit - inputHighBit;
		while(buffersSize--)
		{
			*(pOutputBuffer++) <<= leftShift;
		}
		return;
	}

	imbxUint32 rightShift = inputHighBit - *pOutputHighBit;
	while(buffersSize--)
	{
		*(pOutputBuffer++) >>= rightShift;
	}
	return;

	PUNTOEXE_FUNCTION_END();
}

} // namespace transforms

} // namespace imebra

} // namespace puntoexe
