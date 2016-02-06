/*
$fileHeader$
*/

/*! \file MONOCHROME1ToRGB.cpp
    \brief Implementation of the class MONOCHROME1ToRGB.

*/

#include "exceptionImpl.h"
#include "MONOCHROME1ToRGBImpl.h"
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
std::string MONOCHROME1ToRGB::getInitialColorSpace() const
{
    return "MONOCHROME1";
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
std::string MONOCHROME1ToRGB::getFinalColorSpace() const
{
    return "RGB";
}

std::shared_ptr<colorTransform> MONOCHROME1ToRGB::createColorTransform()
{
    return std::shared_ptr<colorTransform>(std::make_shared<MONOCHROME1ToRGB>());
}

} // namespace colorTransforms

} // namespace transforms

} // namespace implementation

} // namespace imebra

