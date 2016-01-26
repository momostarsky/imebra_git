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

namespace puntoexe
{

namespace imebra
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
std::string PALETTECOLORToRGB::getInitialColorSpace()
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
std::string PALETTECOLORToRGB::getFinalColorSpace()
{
    return "RGB";
}

std::shared_ptr<colorTransform> PALETTECOLORToRGB::createColorTransform()
{
    return std::shared_ptr<colorTransform>(std::make_shared<PALETTECOLORToRGB>());
}

} // namespace colorTransforms

} // namespace transforms

} // namespace imebra

} // namespace puntoexe


