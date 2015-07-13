/*
$fileHeader$
*/

/*! \file YBRFULLToMONOCHROME2.h
    \brief Declaration of the class YBRFULLToMONOCHROME2.

*/

#if !defined(imebraYBRFULLToMONOCHROME2_E27C63E7_A907_4899_9BD3_8026AD7D110C__INCLUDED_)
#define imebraYBRFULLToMONOCHROME2_E27C63E7_A907_4899_9BD3_8026AD7D110C__INCLUDED_

#include "colorTransform.h"


///////////////////////////////////////////////////////////
//
// Everything is in the namespace puntoexe::imebra
//
///////////////////////////////////////////////////////////
namespace puntoexe
{

namespace imebra
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
	virtual std::wstring getInitialColorSpace();
	virtual std::wstring getFinalColorSpace();
	virtual ptr<colorTransform> createColorTransform();

        DEFINE_RUN_TEMPLATE_TRANSFORM;

        template <class inputType, class outputType>
        void templateTransform(
            inputType* inputHandlerData, size_t /* inputHandlerSize */, std::uint32_t inputHandlerWidth, const std::wstring& inputHandlerColorSpace,
            ptr<palette> /* inputPalette */,
            std::int32_t /* inputHandlerMinValue */, std::uint32_t inputHighBit,
            std::int32_t inputTopLeftX, std::int32_t inputTopLeftY, std::int32_t inputWidth, std::int32_t inputHeight,
            outputType* outputHandlerData, size_t /* outputHandlerSize */, std::int32_t outputHandlerWidth, const std::wstring& outputHandlerColorSpace,
            ptr<palette> /* outputPalette */,
            std::int32_t outputHandlerMinValue, std::uint32_t outputHighBit,
            std::int32_t outputTopLeftX, std::int32_t outputTopLeftY)

        {
            checkColorSpaces(inputHandlerColorSpace, outputHandlerColorSpace);

            inputType* pInputMemory(inputHandlerData);
            outputType* pOutputMemory(outputHandlerData);

            pInputMemory += (inputTopLeftY * inputHandlerWidth + inputTopLeftX) * 3;
            pOutputMemory += outputTopLeftY * outputHandlerWidth + outputTopLeftX;

            if(inputHighBit > outputHighBit)
            {
                std::uint32_t rightShift = inputHighBit - outputHighBit;
                for(; inputHeight != 0; --inputHeight)
                {
                    for(int scanPixels(inputWidth); scanPixels != 0; --scanPixels)
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
                    for(int scanPixels(inputWidth); scanPixels != 0; --scanPixels)
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

} // namespace imebra

} // namespace puntoexe

#endif // !defined(imebraYBRFULLToMONOCHROME2_E27C63E7_A907_4899_9BD3_8026AD7D110C__INCLUDED_)
