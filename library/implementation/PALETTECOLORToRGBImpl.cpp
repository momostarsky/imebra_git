/*
$fileHeader$
*/

/*! \file PALETTECOLORToRGB.cpp
    \brief Implementation of the class PALETTECOLORToRGB.

*/

#include "exceptionImpl.h"
#include "PALETTECOLORToRGBImpl.h"
#include "dataSetImpl.h"
#include "dataHandlerImpl.h"
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
std::string PALETTECOLORToRGB::getInitialColorSpace() const
{
    return "PALETTE COLOR";
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
std::string PALETTECOLORToRGB::getFinalColorSpace() const
{
    return "RGB";
}

std::shared_ptr<colorTransform> PALETTECOLORToRGB::createColorTransform()
{
    return std::shared_ptr<colorTransform>(std::make_shared<PALETTECOLORToRGB>());
}

} // namespace colorTransforms

} // namespace transforms

} // namespace implementation

} // namespace imebra


