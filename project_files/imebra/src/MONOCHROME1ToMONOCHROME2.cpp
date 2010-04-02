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

