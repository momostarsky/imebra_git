/*
$fileHeader$
*/

/*! \file YBRFULLToRGB.cpp
    \brief Implementation of the class YBRFULLToRGB.

*/

#include "exceptionImpl.h"
#include "YBRFULLToRGBImpl.h"
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
std::string YBRFULLToRGB::getInitialColorSpace() const
{
    return "YBR_FULL";
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
std::string YBRFULLToRGB::getFinalColorSpace() const
{
    return "RGB";
}


} // namespace colorTransforms

} // namespace transforms

} // namespace implementation

} // namespace imebra

