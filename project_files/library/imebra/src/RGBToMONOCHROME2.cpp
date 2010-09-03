/*
$fileHeader$
*/

/*! \file RGBToMONOCHROME2.cpp
    \brief Implementation of the class RGBToMONOCHROME2.

*/

#include "../../base/include/exception.h"
#include "../include/RGBToMONOCHROME2.h"
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

static registerColorTransform m_registerTransform(ptr<colorTransform>(new RGBToMONOCHROME2));

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Return the initial color space
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::wstring RGBToMONOCHROME2::getInitialColorSpace()
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
std::wstring RGBToMONOCHROME2::getFinalColorSpace()
{
	return L"MONOCHROME2";
}

ptr<colorTransform> RGBToMONOCHROME2::createColorTransform()
{
	return ptr<colorTransform>(new RGBToMONOCHROME2);
}

} // namespace colorTransforms

} // namespace transforms

} // namespace imebra

} // namespace puntoexe

