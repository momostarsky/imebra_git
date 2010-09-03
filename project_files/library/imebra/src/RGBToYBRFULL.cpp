/*
$fileHeader$
*/

/*! \file RGBToYBRFULL.cpp
    \brief Implementation of the class RGBToYBRFULL.

*/

#include "../../base/include/exception.h"
#include "../include/RGBToYBRFULL.h"
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

static registerColorTransform m_registerTransform(ptr<colorTransform>(new RGBToYBRFULL));

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


ptr<colorTransform> RGBToYBRFULL::createColorTransform()
{
	return ptr<colorTransform>(new RGBToYBRFULL);
}


} // namespace colorTransforms

} // namespace transforms

} // namespace imebra

} // namespace puntoexe

