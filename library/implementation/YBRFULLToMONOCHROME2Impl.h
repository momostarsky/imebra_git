/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement 
 that your application must also be GPL), you may purchase a commercial 
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

/*! \file YBRFULLToMONOCHROME2.h
    \brief Declaration of the class YBRFULLToMONOCHROME2.

*/

#if !defined(imebraYBRFULLToMONOCHROME2_E27C63E7_A907_4899_9BD3_8026AD7D110C__INCLUDED_)
#define imebraYBRFULLToMONOCHROME2_E27C63E7_A907_4899_9BD3_8026AD7D110C__INCLUDED_

#include "colorTransformImpl.h"


namespace dicomhero
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
    virtual std::string getInitialColorSpace() const override;
    virtual std::string getFinalColorSpace() const override;

    DEFINE_RUN_TEMPLATE_TRANSFORM;

    template <class inputType, class outputType>
    void templateTransform(
            const inputType* inputHandlerData,
            outputType* outputHandlerData,
            bitDepth_t /* inputDepth */, std::uint32_t inputHandlerWidth, const std::string& inputHandlerColorSpace,
            std::shared_ptr<palette> /* inputPalette */,
            std::uint32_t inputHighBit,
            std::uint32_t inputTopLeftX, std::uint32_t inputTopLeftY, std::uint32_t inputWidth, std::uint32_t inputHeight,
            bitDepth_t /* outputDepth */, std::uint32_t outputHandlerWidth, const std::string& outputHandlerColorSpace,
            std::shared_ptr<palette> /* outputPalette */,
            std::uint32_t outputHighBit,
            std::uint32_t outputTopLeftX, std::uint32_t outputTopLeftY) const

    {
        DICOMHERO_FUNCTION_START();

        checkColorSpaces(inputHandlerColorSpace, outputHandlerColorSpace);
        checkHighBit(inputHighBit, outputHighBit);

        const inputType* pInputMemory(inputHandlerData);
        outputType* pOutputMemory(outputHandlerData);

        pInputMemory += (inputTopLeftY * inputHandlerWidth + inputTopLeftX) * 3;
        pOutputMemory += outputTopLeftY * outputHandlerWidth + outputTopLeftX;

        std::int64_t inputHandlerMinValue = getMinValue<inputType>(inputHighBit);
        std::int64_t outputHandlerMinValue = getMinValue<outputType>(outputHighBit);

        for(; inputHeight != 0; --inputHeight)
        {
            for(std::uint32_t scanPixels(inputWidth); scanPixels != 0; --scanPixels)
            {
                *(pOutputMemory++) = (outputType)(outputHandlerMinValue + (std::int64_t)*pInputMemory - inputHandlerMinValue);
                pInputMemory += 3;
            }
            pInputMemory += (inputHandlerWidth - inputWidth) * 3;
            pOutputMemory += (outputHandlerWidth - inputWidth);
        }

        DICOMHERO_FUNCTION_END();
    }
};


///////////////////////////////////////////////////////////
/// \brief Transforms an image from the colorspace
///         YBR_ICT into the color space MONOCHROME2.
///
/// The input image has to have the colorspace YBR_ICT,
///  while the output image is created by the transform
///  and will have the colorspace MONOCHROME2.
///
///////////////////////////////////////////////////////////
class YBRICTToMONOCHROME2: public YBRFULLToMONOCHROME2
{
public:
    virtual std::string getInitialColorSpace() const override;

};

/// @}

} // namespace colorTransforms

} // namespace transforms

} // namespace implementation

} // namespace dicomhero

#endif // !defined(imebraYBRFULLToMONOCHROME2_E27C63E7_A907_4899_9BD3_8026AD7D110C__INCLUDED_)
