/*
$fileHeader$
*/

/*! \file transformHighBit.cpp
    \brief Implementation of the class transformHighBit.

*/

#include "exceptionImpl.h"
#include "transformHighBitImpl.h"
#include "dataSetImpl.h"
#include "imageImpl.h"


namespace imebra
{

namespace implementation
{

namespace transforms
{

std::shared_ptr<image> transformHighBit::allocateOutputImage(
        bitDepth_t inputDepth,
        const std::string& inputColorSpace,
        std::uint32_t inputHighBit,
        std::shared_ptr<palette> /* inputPalette */,
        std::uint32_t outputWidth, std::uint32_t outputHeight) const
{
    IMEBRA_FUNCTION_START();

    return std::make_shared<image>(outputWidth, outputHeight, inputDepth, inputColorSpace, inputHighBit);

    IMEBRA_FUNCTION_END();
}

} // namespace transforms

} // namespace implementation

} // namespace imebra
