/*
$fileHeader$
*/

/*! \file MONOCHROME2ToRGB.cpp
    \brief Implementation of the class MONOCHROME2ToRGB.

*/

#include "exceptionImpl.h"
#include "MONOCHROME2ToRGBImpl.h"
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

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Return the initial color space
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::wstring MONOCHROME2ToRGB::getInitialColorSpace()
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
std::wstring MONOCHROME2ToRGB::getFinalColorSpace()
{
	return L"RGB";
}


std::shared_ptr<colorTransform> MONOCHROME2ToRGB::createColorTransform()
{
	return std::shared_ptr<colorTransform>(new MONOCHROME2ToRGB);
}



} // namespace colorTransforms

} // namespace transforms

} // namespace imebra

} // namespace puntoexe

