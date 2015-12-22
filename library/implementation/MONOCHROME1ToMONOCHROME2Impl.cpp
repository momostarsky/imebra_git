/*
$fileHeader$
*/

/*! \file MONOCHROME1ToMONOCHROME2.cpp
    \brief Implementation of the classes for conversion between 2 monochrome color spaces.

*/

#include "exceptionImpl.h"
#include "MONOCHROME1ToMONOCHROME2Impl.h"
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

static registerColorTransform m_registerTransform0(std::shared_ptr<colorTransform>(std::make_shared<MONOCHROME1ToMONOCHROME2>()));
static registerColorTransform m_registerTransform1(std::shared_ptr<colorTransform>(std::make_shared<MONOCHROME2ToMONOCHROME1>()));

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

std::shared_ptr<colorTransform> MONOCHROME1ToMONOCHROME2::createColorTransform()
{
    return std::shared_ptr<colorTransform> (std::make_shared<MONOCHROME1ToMONOCHROME2>());
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

std::shared_ptr<colorTransform> MONOCHROME2ToMONOCHROME1::createColorTransform()
{
    return std::shared_ptr<colorTransform> (std::make_shared<MONOCHROME2ToMONOCHROME1>());
}



} // namespace colorTransforms

} // namespace transforms

} // namespace imebra

} // namespace puntoexe

