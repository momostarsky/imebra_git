/*
$fileHeader$
*/

/*! \file RGBToYBRFULL.cpp
    \brief Implementation of the class RGBToYBRFULL.

*/

#include "exceptionImpl.h"
#include "RGBToYBRFULLImpl.h"
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
std::wstring RGBToYBRFULL::getInitialColorSpace()
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
std::wstring RGBToYBRFULL::getFinalColorSpace()
{
	return L"YBR_FULL";
}


std::shared_ptr<colorTransform> RGBToYBRFULL::createColorTransform()
{
	return std::shared_ptr<colorTransform>(new RGBToYBRFULL);
}


} // namespace colorTransforms

} // namespace transforms

} // namespace imebra

} // namespace puntoexe

