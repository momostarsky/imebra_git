/*
$fileHeader$
*/

/*! \file RGBToMONOCHROME2.cpp
    \brief Implementation of the class RGBToMONOCHROME2.

*/

#include "exceptionImpl.h"
#include "RGBToMONOCHROME2Impl.h"
#include "dataHandlerImpl.h"
#include "dataSetImpl.h"
#include "imageImpl.h"

namespace imebra
{

namespace implementation
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
std::string RGBToMONOCHROME2::getInitialColorSpace() const
{
    return "RGB";
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
std::string RGBToMONOCHROME2::getFinalColorSpace() const
{
    return "MONOCHROME2";
}

std::shared_ptr<colorTransform> RGBToMONOCHROME2::createColorTransform()
{
    return std::shared_ptr<colorTransform>(std::make_shared<RGBToMONOCHROME2>());
}

} // namespace colorTransforms

} // namespace transforms

} // namespace implementation

} // namespace imebra

