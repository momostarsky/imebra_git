/*
$fileHeader$
*/

/*! \file RGBToMONOCHROME2.cpp
    \brief Implementation of the class RGBToMONOCHROME2.

*/

#include "exceptionImpl.h"
#include "RGBToMONOCHROME2Impl.h"
#include "dataHandlerImpl.h"
#include "dataSetImpl.h"
#include "imageImpl.h"

namespace puntoexe
{

namespace imebra
{

namespace transforms
{

namespace colorTransforms
{

static registerColorTransform m_registerTransform(std::shared_ptr<colorTransform>(new RGBToMONOCHROME2));

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

std::shared_ptr<colorTransform> RGBToMONOCHROME2::createColorTransform()
{
	return std::shared_ptr<colorTransform>(new RGBToMONOCHROME2);
}

} // namespace colorTransforms

} // namespace transforms

} // namespace imebra

} // namespace puntoexe

