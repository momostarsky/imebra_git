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

static registerColorTransform m_registerTransform(ptr<colorTransform>(new MONOCHROME2ToRGB));

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


ptr<colorTransform> MONOCHROME2ToRGB::createColorTransform()
{
	return ptr<colorTransform>(new MONOCHROME2ToRGB);
}



} // namespace colorTransforms

} // namespace transforms

} // namespace imebra

} // namespace puntoexe

