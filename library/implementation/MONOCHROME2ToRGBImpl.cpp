/*
$fileHeader$
*/

/*! \file MONOCHROME2ToRGB.cpp
    \brief Implementation of the class MONOCHROME2ToRGB.

*/

#include "exceptionImpl.h"
#include "MONOCHROME2ToRGBImpl.h"
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
std::string MONOCHROME2ToRGB::getInitialColorSpace()
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
std::string MONOCHROME2ToRGB::getFinalColorSpace()
{
    return "RGB";
}


std::shared_ptr<colorTransform> MONOCHROME2ToRGB::createColorTransform()
{
    return std::shared_ptr<colorTransform>(std::make_shared<MONOCHROME2ToRGB>());
}



} // namespace colorTransforms

} // namespace transforms

} // namespace implementation

} // namespace imebra

