/*
$fileHeader$
*/

/*! \file MONOCHROME1ToRGB.h
    \brief Declaration of the class MONOCHROME1ToRGB.

*/

#if !defined(imebraMONOCHROME1ToRGB_E27C63E7_A907_4899_9BD3_8026AD7D110C__INCLUDED_)
#define imebraMONOCHROME1ToRGB_E27C63E7_A907_4899_9BD3_8026AD7D110C__INCLUDED_

#include "colorTransformImpl.h"


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
///         MONOCHROME1 into the color space RGB.
///
/// The input image has to have the colorspace MONOCHROME1,
///  while the output image is created by the transform
///  and will have the colorspace RGB.
///
///////////////////////////////////////////////////////////
class MONOCHROME1ToRGB: public colorTransform
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
            std::uint32_t inputHighBit,
            std::uint32_t inputTopLeftX, std::uint32_t inputTopLeftY, std::uint32_t inputWidth, std::uint32_t inputHeight,
            std::uint32_t outputHandlerWidth, const std::string& outputHandlerColorSpace,
            std::shared_ptr<palette> /* outputPalette */,
            std::uint32_t outputHighBit,
            std::uint32_t outputTopLeftX, std::uint32_t outputTopLeftY)

        {
            checkColorSpaces(inputHandlerColorSpace, outputHandlerColorSpace);
            checkHighBit(inputHighBit, outputHighBit);

            const inputType* pInputMemory(inputHandlerData);
            outputType* pOutputMemory(outputHandlerData);

            pInputMemory += inputTopLeftY * inputHandlerWidth + inputTopLeftX;
            pOutputMemory += (outputTopLeftY * outputHandlerWidth + outputTopLeftX) * 3;

            std::int64_t inputHandlerMinValue = getMinValue<inputType>(inputHighBit);
            std::int64_t outputHandlerMinValue = getMinValue<outputType>(outputHighBit);
            std::int64_t inputHandlerNumValuesMinusOne = ((std::int64_t)1 << (inputHighBit + 1)) - 1;

            outputType outputValue;

            for(; inputHeight != 0; --inputHeight)
            {
                for(std::uint32_t scanPixels(inputWidth); scanPixels != 0; --scanPixels)
                {
                    outputValue = (outputType)(outputHandlerMinValue + inputHandlerNumValuesMinusOne - (std::int64_t)pInputMemory++ + inputHandlerMinValue);
                    *pOutputMemory = outputValue;
                    *++pOutputMemory = outputValue;
                    *++pOutputMemory = outputValue;
                    ++pOutputMemory;
                }
                pInputMemory += inputHandlerWidth - inputWidth;
                pOutputMemory += (outputHandlerWidth - inputWidth) * 3;
            }
        }

};

/// @}

} // namespace colorTransforms

} // namespace transforms

} // namespace implementation

} // namespace imebra

#endif // !defined(imebraMONOCHROME1ToRGB_E27C63E7_A907_4899_9BD3_8026AD7D110C__INCLUDED_)
