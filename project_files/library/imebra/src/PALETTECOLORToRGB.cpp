/*
$fileHeader$
*/

/*! \file PALETTECOLORToRGB.cpp
    \brief Implementation of the class PALETTECOLORToRGB.

*/

#include "../../base/include/exception.h"
#include "../include/PALETTECOLORToRGB.h"
#include "../include/dataSet.h"
#include "../include/dataHandler.h"
#include "../include/image.h"

namespace puntoexe
{

namespace imebra
{

namespace transforms
{

namespace colorTransforms
{

static registerColorTransform m_registerTransform(ptr<colorTransform>(new PALETTECOLORToRGB));

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Return the initial color space
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::wstring PALETTECOLORToRGB::getInitialColorSpace()
{
	return L"PALETTE COLOR";
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
std::wstring PALETTECOLORToRGB::getFinalColorSpace()
{
	return L"RGB";
}

ptr<colorTransform> PALETTECOLORToRGB::createColorTransform()
{
	return ptr<colorTransform>(new PALETTECOLORToRGB);
}

} // namespace colorTransforms

} // namespace transforms

} // namespace imebra

} // namespace puntoexe


