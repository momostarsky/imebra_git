/*
$fileHeader$
*/

/*! \file transformHighBit.h
    \brief Declaration of the class transformHighBit.

*/

#if !defined(imebraTransformHighBit_8347C70F_1FC8_4df8_A887_8DE9E968B2CF__INCLUDED_)
#define imebraTransformHighBit_8347C70F_1FC8_4df8_A887_8DE9E968B2CF__INCLUDED_

#include "transformImpl.h"
#include "colorTransformsFactoryImpl.h"
#include "../include/imebra/exceptions.h"

namespace imebra
{

namespace implementation
{

namespace transforms
{

/// \addtogroup group_transforms
///
/// @{


///////////////////////////////////////////////////////////
/// \brief Shift the image's content to adapt it to the
///         specified high bit.
///
/// In order to use this transform, both the input and
///  the output image must be defined by calling
///  declareInputImage() and declareOutputImage().
///
/// The input image is copied into the output image but
///  all the values are shifted to be fitted in the
///  output image's high bit settings.
///
///////////////////////////////////////////////////////////
class transformHighBit: public transformHandlers
{
public:
        virtual std::shared_ptr<image> allocateOutputImage(std::shared_ptr<image> pInputImage, std::uint32_t width, std::uint32_t height);

        DEFINE_RUN_TEMPLATE_TRANSFORM;

        template <class inputType, class outputType>
        void templateTransform(
            const inputType* inputHandlerData,
            outputType* outputHandlerData,
            std::uint32_t inputHandlerWidth, const std::string& inputHandlerColorSpace,
            std::shared_ptr<palette> /* inputPalette */,
            std::int32_t inputHandlerMinValue, std::uint32_t inputHighBit,
            std::int32_t inputTopLeftX, std::int32_t inputTopLeftY, std::int32_t inputWidth, std::int32_t inputHeight,
            std::int32_t outputHandlerWidth, const std::string& outputHandlerColorSpace,
            std::shared_ptr<palette> /* outputPalette */,
            std::int32_t outputHandlerMinValue, std::uint32_t outputHighBit,
            std::int32_t outputTopLeftX, std::int32_t outputTopLeftY)

        {
            if(colorTransforms::colorTransformsFactory::normalizeColorSpace(inputHandlerColorSpace) !=
               colorTransforms::colorTransformsFactory::normalizeColorSpace(outputHandlerColorSpace))
            {
                throw transformHighBitDifferentColorSpaces("The input and output image must have the same color space");
            }

            std::int32_t numChannels(colorTransforms::colorTransformsFactory::getNumberOfChannels(inputHandlerColorSpace));

            const inputType* pInputMemory(inputHandlerData);
            outputType* pOutputMemory(outputHandlerData);

            pInputMemory += (inputTopLeftY * inputHandlerWidth + inputTopLeftX) * numChannels;
            pOutputMemory += (outputTopLeftY * outputHandlerWidth + outputTopLeftX) * numChannels;

            if(inputHighBit > outputHighBit)
            {
                std::uint32_t rightShift = inputHighBit - outputHighBit;
                for(; inputHeight != 0; --inputHeight)
                {
                    for(int scanPixels(inputWidth * numChannels); scanPixels != 0; --scanPixels)
                    {
                        *pOutputMemory++ = (outputType)((((std::int32_t)*(pInputMemory++) - inputHandlerMinValue) >> rightShift) + outputHandlerMinValue);
                    }
                    pInputMemory += (inputHandlerWidth - inputWidth) * numChannels;
                    pOutputMemory += (outputHandlerWidth - inputWidth) * numChannels;
                }
            }
            else
            {
                std::uint32_t leftShift = outputHighBit - inputHighBit;
                for(; inputHeight != 0; --inputHeight)
                {
                    for(int scanPixels(inputWidth * numChannels); scanPixels != 0; --scanPixels)
                    {
                        *pOutputMemory++ = (outputType)((((std::int32_t)*(pInputMemory++) - inputHandlerMinValue) << leftShift) + outputHandlerMinValue);
                    }
                    pInputMemory += (inputHandlerWidth - inputWidth) * numChannels;
                    pOutputMemory += (outputHandlerWidth - inputWidth) * numChannels;
                }
            }
        }

};

/// @}

} // namespace transforms

} // namespace implementation

} // namespace imebra

#endif // !defined(imebraTransformHighBit_8347C70F_1FC8_4df8_A887_8DE9E968B2CF__INCLUDED_)
