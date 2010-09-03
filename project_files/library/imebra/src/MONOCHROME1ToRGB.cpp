/*
$fileHeader$
*/

/*! \file MONOCHROME1ToRGB.cpp
    \brief Implementation of the class MONOCHROME1ToRGB.

*/

#include "../../base/include/exception.h"
#include "../include/MONOCHROME1ToRGB.h"
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


static registerColorTransform m_registerTransform(ptr<colorTransform>(new MONOCHROME1ToRGB));


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

ptr<colorTransform> MONOCHROME1ToRGB::createColorTransform()
{
	return ptr<colorTransform>(new MONOCHROME1ToRGB);
}

} // namespace colorTransforms

} // namespace transforms

} // namespace imebra

} // namespace puntoexe

