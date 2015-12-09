/*
$fileHeader$
*/

/*! \file MONOCHROME2ToYBRFULL.cpp
    \brief Implementation of the class MONOCHROMEToYBRFULL.

*/

#include "exceptionImpl.h"
#include "MONOCHROME2ToYBRFULLImpl.h"
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

static registerColorTransform m_registerTransform(ptr<colorTransform>(new MONOCHROME2ToYBRFULL));

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Return the initial color space
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::wstring MONOCHROME2ToYBRFULL::getInitialColorSpace()
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
std::wstring MONOCHROME2ToYBRFULL::getFinalColorSpace()
{
	return L"YBR_FULL";
}


ptr<colorTransform> MONOCHROME2ToYBRFULL::createColorTransform()
{
	return ptr<colorTransform>(new MONOCHROME2ToYBRFULL);
}


} // namespace colorTransforms

} // namespace transforms

} // namespace imebra

} // namespace puntoexe
