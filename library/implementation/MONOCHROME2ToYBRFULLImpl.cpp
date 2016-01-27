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
std::string MONOCHROME2ToYBRFULL::getInitialColorSpace()
{
    return "MONOCHROME2";
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
std::string MONOCHROME2ToYBRFULL::getFinalColorSpace()
{
    return "YBR_FULL";
}


std::shared_ptr<colorTransform> MONOCHROME2ToYBRFULL::createColorTransform()
{
    return std::shared_ptr<colorTransform>(std::make_shared<MONOCHROME2ToYBRFULL>());
}


} // namespace colorTransforms

} // namespace transforms

} // namespace implementation

} // namespace imebra
