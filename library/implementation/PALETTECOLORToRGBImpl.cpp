/*
$fileHeader$
*/

/*! \file PALETTECOLORToRGB.cpp
    \brief Implementation of the class PALETTECOLORToRGB.

*/

#include "exceptionImpl.h"
#include "PALETTECOLORToRGBImpl.h"
#include "dataSetImpl.h"
#include "dataHandlerImpl.h"
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

std::shared_ptr<colorTransform> PALETTECOLORToRGB::createColorTransform()
{
    return std::shared_ptr<colorTransform>(new PALETTECOLORToRGB);
}

} // namespace colorTransforms

} // namespace transforms

} // namespace imebra

} // namespace puntoexe


