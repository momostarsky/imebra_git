/*
$fileHeader$
*/

/*! \file MONOCHROME1ToRGB.cpp
    \brief Implementation of the class MONOCHROME1ToRGB.

*/

#include "exceptionImpl.h"
#include "MONOCHROME1ToRGBImpl.h"
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


static registerColorTransform m_registerTransform(std::shared_ptr<colorTransform>(new MONOCHROME1ToRGB));


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

std::shared_ptr<colorTransform> MONOCHROME1ToRGB::createColorTransform()
{
	return std::shared_ptr<colorTransform>(new MONOCHROME1ToRGB);
}

} // namespace colorTransforms

} // namespace transforms

} // namespace imebra

} // namespace puntoexe

