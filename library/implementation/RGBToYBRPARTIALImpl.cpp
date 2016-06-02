/*
$fileHeader$
*/

/*! \file RGBToYBRPARTIAL.cpp
    \brief Implementation of the class RGBToYBRPARTIAL.

*/

#include "exceptionImpl.h"
#include "RGBToYBRPARTIALImpl.h"
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
std::string RGBToYBRPARTIAL::getInitialColorSpace() const
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
std::string RGBToYBRPARTIAL::getFinalColorSpace() const
{
    return "YBR_PARTIAL";
}


} // namespace colorTransforms

} // namespace transforms

} // namespace implementation

} // namespace imebra


