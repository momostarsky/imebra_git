/*
$fileHeader$
*/

/*! \file modalityVOILUT.cpp
    \brief Implementation of the class modalityVOILUT.

*/

#include "../../base/include/exception.h"
#include "../include/modalityVOILUT.h"
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
// Modality VOILUT transform
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void modalityVOILUT::doTransformBuffers(
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
	PUNTOEXE_FUNCTION_START(L"modalityVOILUT::doTransformBuffers");

	ptr<dataSet> voiDataSet = getDataSet();
	if(voiDataSet == 0)
	{
		PUNTOEXE_THROW(transformExceptionDataSetNotDefined, "VOI dataset missed");
	}

	// Get the modality LUT
	///////////////////////////////////////////////////////////
	ptr<lut> voiLut=voiDataSet->getLut(0x0028, 0x3000, 0);
	
	//
	// Modality LUT found
	//
	///////////////////////////////////////////////////////////
	if(voiLut != 0 && voiLut->getSize())
	{
		imbxUint8 bits=voiLut->getBits();

		*pOutputDepth=image::depthU8;
		if(bits>8)
			*pOutputDepth=image::depthU16;
		*pOutputHighBit=bits-1;

		while(buffersSize--)
		{
			*pOutputBuffer=voiLut->mappedValue(*pOutputBuffer);
			++pOutputBuffer;
		}

		return;
	}

	//
	// Modality LUT not found
	//
	///////////////////////////////////////////////////////////

	// Retrieve the intercept/scale pair
	///////////////////////////////////////////////////////////
	double rescaleIntercept=voiDataSet->getDouble(0x0028, 0, 0x1052, 0x0);
	double rescaleSlope=voiDataSet->getDouble(0x0028, 0, 0x1053, 0x0);
	if(rescaleSlope==0.0)
		rescaleSlope=1.0;

	// Scale/Intercept 
	///////////////////////////////////////////////////////////
	if(rescaleSlope==1.0 && rescaleIntercept==0.0)
	{
		return;
	}

	*pOutputDepth=image::depthUnknown;
	*pOutputHighBit = 0;

	while(buffersSize--)
	{
		*pOutputBuffer=(imbxInt32)((double)(*pOutputBuffer)*rescaleSlope+rescaleIntercept+0.5);
		++pOutputBuffer;
	}
	return;

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Inverse Modality VOILUT transform
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void modalityVOILUTInverse::doTransformBuffers(
		imbxUint32 /* sizeX */, 
		imbxUint32 /* sizeY */,
		imbxUint32 /* inputChannelsNumber */,
		std::wstring /* inputColorSpace */,
		image::bitDepth /* inputDepth */,
		imbxUint32 /* inputHighBit */,
		imbxInt32* /* pInputBuffer */,
		imbxInt32* pOutputBuffer,
		imbxUint32 buffersSize,
		image::bitDepth* /* pOutputDepth */,
		imbxUint32* /* pOutputHighBit */)
{
	PUNTOEXE_FUNCTION_START(L"modalityVOILUTInverse::doTransformBuffers");

	ptr<dataSet> voiDataSet=getDataSet();
	if(voiDataSet == 0)
	{
		PUNTOEXE_THROW(transformExceptionDataSetNotDefined, "VOI dataset missed");
	}

	// Get the modality LUT
	///////////////////////////////////////////////////////////
	ptr<lut> voiLut=voiDataSet->getLut(0x0028, 0x3000, 0);
	
	//
	// Modality LUT found
	//
	///////////////////////////////////////////////////////////
	if(voiLut != 0 && voiLut->getSize())
	{
		while(buffersSize--)
		{
			*pOutputBuffer = voiLut->mappedValueRev(*pOutputBuffer);
			++pOutputBuffer;
		}

		return;
	}

	//
	// Modality LUT not found
	//
	///////////////////////////////////////////////////////////

	// Retrieve the intercept/scale pair
	///////////////////////////////////////////////////////////
	double rescaleIntercept=voiDataSet->getDouble(0x0028, 0, 0x1052, 0x0);
	double rescaleSlope=voiDataSet->getDouble(0x0028, 0, 0x1053, 0x0);
	if(rescaleSlope==0.0)
		rescaleSlope=1.0;

	// Scale/Intercept 
	///////////////////////////////////////////////////////////
	if(rescaleSlope==1.0 && rescaleIntercept==0.0)
	{
		return;
	}

	while(buffersSize--)
	{
		*pOutputBuffer = (imbxInt32)(((double)(*pOutputBuffer) - rescaleIntercept)/rescaleSlope+0.5);
		++pOutputBuffer;
	}

	PUNTOEXE_FUNCTION_END();
}


} // namespace transforms

} // namespace imebra

} // namespace puntoexe
