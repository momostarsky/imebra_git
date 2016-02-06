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
std::string RGBToYBRFULL::getInitialColorSpace() const
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
std::string RGBToYBRFULL::getFinalColorSpace() const
{
    return "YBR_FULL";
}


std::shared_ptr<colorTransform> RGBToYBRFULL::createColorTransform()
{
    return std::shared_ptr<colorTransform>(std::make_shared<RGBToYBRFULL>());
}


} // namespace colorTransforms

} // namespace transforms

} // namespace implementation

} // namespace imebra

