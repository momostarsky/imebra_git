/*
$fileHeader$
*/

/*! \file transformHighBit.cpp
    \brief Implementation of the class transformHighBit.

*/

#include "../../base/include/exception.h"
#include "../include/transformHighBit.h"
#include "../include/dataSet.h"


namespace puntoexe
{

namespace imebra
{

namespace transforms
{

ptr<image> transformHighBit::allocateOutputImage(ptr<image> pInputImage, std::uint32_t width, std::uint32_t height)
{
    ptr<image> newImage(new image());
	newImage->create(width, height, pInputImage->getDepth(), pInputImage->getColorSpace(), pInputImage->getHighBit());
	return newImage;
}

} // namespace transforms

} // namespace imebra

} // namespace puntoexe
