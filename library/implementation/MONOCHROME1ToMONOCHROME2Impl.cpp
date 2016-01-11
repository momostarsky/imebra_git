/*
$fileHeader$
*/

/*! \file MONOCHROME1ToMONOCHROME2.cpp
    \brief Implementation of the classes for conversion between 2 monochrome color spaces.

*/

#include "exceptionImpl.h"
#include "MONOCHROME1ToMONOCHROME2Impl.h"
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


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Return the initial color space
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::string MONOCHROME1ToMONOCHROME2::getInitialColorSpace()
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
std::string MONOCHROME1ToMONOCHROME2::getFinalColorSpace()
{
    return "MONOCHROME2";
}

std::shared_ptr<colorTransform> MONOCHROME1ToMONOCHROME2::createColorTransform()
{
    return std::shared_ptr<colorTransform> (std::make_shared<MONOCHROME1ToMONOCHROME2>());
}




///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Return the initial color space
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::string MONOCHROME2ToMONOCHROME1::getInitialColorSpace()
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
std::string MONOCHROME2ToMONOCHROME1::getFinalColorSpace()
{
    return "MONOCHROME1";
}

std::shared_ptr<colorTransform> MONOCHROME2ToMONOCHROME1::createColorTransform()
{
    return std::shared_ptr<colorTransform> (std::make_shared<MONOCHROME2ToMONOCHROME1>());
}



} // namespace colorTransforms

} // namespace transforms

} // namespace imebra

} // namespace puntoexe

