/*
$fileHeader$
*/

/*! \file transformHighBit.cpp
    \brief Implementation of the class transformHighBit.

*/

#include "exceptionImpl.h"
#include "transformHighBitImpl.h"
#include "dataSetImpl.h"


namespace imebra
{

namespace implementation
{

namespace transforms
{

std::shared_ptr<image> transformHighBit::allocateOutputImage(
        image::bitDepth inputDepth,
        const std::string& inputColorSpace,
        std::uint32_t inputHighBit,
        std::shared_ptr<palette> /* inputPalette */,
        std::uint32_t outputWidth, std::uint32_t outputHeight) const
{
    std::shared_ptr<image> newImage(std::make_shared<image>());
    newImage->create(outputWidth, outputHeight, inputDepth, inputColorSpace, inputHighBit);
	return newImage;
}

} // namespace transforms

} // namespace implementation

} // namespace imebra
