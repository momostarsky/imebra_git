/*
$fileHeader$
*/

/*! \file YBRFULLToMONOCHROME2.h
    \brief Declaration of the class YBRFULLToMONOCHROME2.

*/

#if !defined(imebraYBRFULLToMONOCHROME2_E27C63E7_A907_4899_9BD3_8026AD7D110C__INCLUDED_)
#define imebraYBRFULLToMONOCHROME2_E27C63E7_A907_4899_9BD3_8026AD7D110C__INCLUDED_

#include "colorTransformImpl.h"


///////////////////////////////////////////////////////////
//
// Everything is in the namespace imebra::implementation
//
///////////////////////////////////////////////////////////
namespace imebra
{

namespace implementation
{

namespace transforms
{

namespace colorTransforms
{

/// \addtogroup group_transforms
///
/// @{

///////////////////////////////////////////////////////////
/// \brief Transforms an image from the colorspace 
///         YBR_FULL into the color space MONOCHROME2.
///
/// The input image has to have the colorspace YBR_FULL,
///  while the output image is created by the transform
///  and will have the colorspace MONOCHROME2.
///
///////////////////////////////////////////////////////////
class YBRFULLToMONOCHROME2: public colorTransform
{
public:
    virtual std::string getInitialColorSpace();
    virtual std::string getFinalColorSpace();
	virtual std::shared_ptr<colorTransform> createColorTransform();

        DEFINE_RUN_TEMPLATE_TRANSFORM;

        template <class inputType, class outputType>
        void templateTransform(
            const inputType* inputHandlerData,
            outputType* outputHandlerData,
            std::uint32_t inputHandlerWidth, const std::string& inputHandlerColorSpace,
            std::shared_ptr<palette> /* inputPalette */,
            std::int32_t /* inputHandlerMinValue */, std::uint32_t inputHighBit,
            std::uint32_t inputTopLeftX, std::uint32_t inputTopLeftY, std::uint32_t inputWidth, std::uint32_t inputHeight,
            std::uint32_t outputHandlerWidth, const std::string& outputHandlerColorSpace,
            std::shared_ptr<palette> /* outputPalette */,
            std::int32_t outputHandlerMinValue, std::uint32_t outputHighBit,
            std::uint32_t outputTopLeftX, std::uint32_t outputTopLeftY)

        {
            checkColorSpaces(inputHandlerColorSpace, outputHandlerColorSpace);

            const inputType* pInputMemory(inputHandlerData);
            outputType* pOutputMemory(outputHandlerData);

            pInputMemory += (inputTopLeftY * inputHandlerWidth + inputTopLeftX) * 3;
            pOutputMemory += outputTopLeftY * outputHandlerWidth + outputTopLeftX;

            if(inputHighBit > outputHighBit)
            {
                std::uint32_t rightShift = inputHighBit - outputHighBit;
                for(; inputHeight != 0; --inputHeight)
                {
                    for(std::uint32_t scanPixels(inputWidth); scanPixels != 0; --scanPixels)
                    {
                        *(pOutputMemory++) = (outputType)( outputHandlerMinValue + ((*pInputMemory - outputHandlerMinValue) >> rightShift) );
                        pInputMemory += 3;
                    }
                    pInputMemory += (inputHandlerWidth - inputWidth) * 3;
                    pOutputMemory += (outputHandlerWidth - inputWidth);
                }
            }
            else
            {
                std::uint32_t leftShift = outputHighBit - inputHighBit;
                for(; inputHeight != 0; --inputHeight)
                {
                    for(std::uint32_t scanPixels(inputWidth); scanPixels != 0; --scanPixels)
                    {
                        *(pOutputMemory++) = (outputType)( outputHandlerMinValue + ((*pInputMemory - outputHandlerMinValue) << leftShift) );
                        pInputMemory += 3;
                    }
                    pInputMemory += (inputHandlerWidth - inputWidth) * 3;
                    pOutputMemory += (outputHandlerWidth - inputWidth);
                }
            }
        }
};

/// @}

} // namespace colorTransforms

} // namespace transforms

} // namespace implementation

} // namespace imebra

#endif // !defined(imebraYBRFULLToMONOCHROME2_E27C63E7_A907_4899_9BD3_8026AD7D110C__INCLUDED_)
