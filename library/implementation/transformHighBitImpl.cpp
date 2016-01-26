/*
$fileHeader$
*/

/*! \file transformHighBit.cpp
    \brief Implementation of the class transformHighBit.

*/

#include "exceptionImpl.h"
#include "transformHighBitImpl.h"
#include "dataSetImpl.h"


namespace puntoexe
{

namespace imebra
{

namespace transforms
{

std::shared_ptr<image> transformHighBit::allocateOutputImage(std::shared_ptr<image> pInputImage, std::uint32_t width, std::uint32_t height)
{
    std::shared_ptr<image> newImage(std::make_shared<image>());
	newImage->create(width, height, pInputImage->getDepth(), pInputImage->getColorSpace(), pInputImage->getHighBit());
	return newImage;
}

} // namespace transforms

} // namespace imebra

} // namespace puntoexe
