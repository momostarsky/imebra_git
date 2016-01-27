/*
$fileHeader$
*/

/*! \file RGBToMONOCHROME2.h
    \brief Declaration of the class RGBToMONOCHROME2.

*/

#if !defined(imebraRGBToMONOCHROME2_E27C63E7_A907_4899_9BD3_8026AD7D110C__INCLUDED_)
#define imebraRGBToMONOCHROME2_E27C63E7_A907_4899_9BD3_8026AD7D110C__INCLUDED_

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
///         RGB into the color space MONOCHROME2.
///
/// The input image has to have the colorspace RGB,
///  while the output image is created by the transform
///  and will have the colorspace MONOCHROME2.
///
///////////////////////////////////////////////////////////
class RGBToMONOCHROME2: public colorTransform
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
            std::int32_t inputHandlerMinValue, std::uint32_t inputHighBit,
            std::int32_t inputTopLeftX, std::int32_t inputTopLeftY, std::int32_t inputWidth, std::int32_t inputHeight,
            std::int32_t outputHandlerWidth, const std::string& outputHandlerColorSpace,
            std::shared_ptr<palette> /* outputPalette */,
            std::int32_t outputHandlerMinValue, std::uint32_t outputHighBit,
            std::int32_t outputTopLeftX, std::int32_t outputTopLeftY)

        {
            checkColorSpaces(inputHandlerColorSpace, outputHandlerColorSpace);

            const inputType* pInputMemory(inputHandlerData);
            outputType* pOutputMemory(outputHandlerData);

            pInputMemory += (inputTopLeftY * inputHandlerWidth + inputTopLeftX) * 3;
            pOutputMemory += outputTopLeftY * outputHandlerWidth + outputTopLeftX;

            std::int32_t sourceR, sourceG, sourceB;
            if(inputHighBit > outputHighBit)
            {
                std::uint32_t rightShift = inputHighBit - outputHighBit;
                for(; inputHeight != 0; --inputHeight)
                {
                    for(int scanPixels(inputWidth); scanPixels != 0; --scanPixels)
                    {
                        sourceR = (std::int32_t) (*(pInputMemory++)) - inputHandlerMinValue;
                        sourceG = (std::int32_t) (*(pInputMemory++)) - inputHandlerMinValue;
                        sourceB = (std::int32_t) (*(pInputMemory++)) - inputHandlerMinValue;
                        *(pOutputMemory++) = (outputType) ( ((((std::int32_t)4899 * sourceR+(std::int32_t)9617 * sourceG+(std::int32_t)1868 * sourceB) >> 14) >> rightShift) + outputHandlerMinValue );
                    }
                    pInputMemory += (inputHandlerWidth - inputWidth) * 3;
                    pOutputMemory += outputHandlerWidth - inputWidth;
                }
            }
            else
            {
                std::uint32_t leftShift = outputHighBit - inputHighBit;
                for(; inputHeight != 0; --inputHeight)
                {
                    for(int scanPixels(inputWidth); scanPixels != 0; --scanPixels)
                    {
                        sourceR = (std::int32_t) (*(pInputMemory++)) - inputHandlerMinValue;
                        sourceG = (std::int32_t) (*(pInputMemory++)) - inputHandlerMinValue;
                        sourceB = (std::int32_t) (*(pInputMemory++)) - inputHandlerMinValue;
                        *(pOutputMemory++) = (outputType) ( ((((std::int32_t)4899 * sourceR+(std::int32_t)9617 * sourceG+(std::int32_t)1868 * sourceB) >> 14) << leftShift) + outputHandlerMinValue );
                    }
                    pInputMemory += (inputHandlerWidth - inputWidth) * 3;
                    pOutputMemory += outputHandlerWidth - inputWidth;
                }
            }
        }
};

/// @}

} // namespace colorTransforms

} // namespace transforms

} // namespace implementation

} // namespace imebra

#endif // !defined(imebraRGBToMONOCHROME2_E27C63E7_A907_4899_9BD3_8026AD7D110C__INCLUDED_)
