/*
$fileHeader$
*/

/*! \file RGBToYBRFULL.h
    \brief Declaration of the class RGBToYBRFULL.

*/

#if !defined(imebraRGBToYBRFULL_E27C63E7_A907_4899_9BD3_8026AD7D110C__INCLUDED_)
#define imebraRGBToYBRFULL_E27C63E7_A907_4899_9BD3_8026AD7D110C__INCLUDED_

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
///         RGB into the color space YBR_FULL.
///
/// The input image has to have the colorspace RGB,
///  while the output image is created by the transform
///  and will have the colorspace YBR_FULL.
///
///////////////////////////////////////////////////////////
class RGBToYBRFULL: public colorTransform
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
            std::int32_t inputHandlerMinValue, std::uint32_t inputHighBit,
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
            pOutputMemory += (outputTopLeftY * outputHandlerWidth + outputTopLeftX) * 3;

            std::int32_t outputMiddleValue(outputHandlerMinValue + ((std::int32_t)1 << outputHighBit));

            std::int32_t sourceR, sourceG, sourceB;
            if(inputHighBit > outputHighBit)
            {
                std::int32_t division = ((std::int32_t)1 << (inputHighBit - outputHighBit)) * 16384;
                for(; inputHeight != 0; --inputHeight)
                {
                    for(int scanPixels(inputWidth); scanPixels != 0; --scanPixels)
                    {
                        sourceR = (std::int32_t) (*(pInputMemory++)) - inputHandlerMinValue;
                        sourceG = (std::int32_t) (*(pInputMemory++)) - inputHandlerMinValue;
                        sourceB = (std::int32_t) (*(pInputMemory++)) - inputHandlerMinValue;
                        *(pOutputMemory++) = (outputType) ( (((std::int32_t)4899 * sourceR+(std::int32_t)9617 * sourceG+(std::int32_t)1868 * sourceB) / division) + outputHandlerMinValue );
                        *(pOutputMemory++) = (outputType) ( outputMiddleValue + (((std::int32_t)8192 * sourceB - (std::int32_t)2764 * sourceR - (std::int32_t)5428 * sourceG + (std::int32_t)8192) / division));
                        *(pOutputMemory++) = (outputType) ( outputMiddleValue + (((std::int32_t)8192 * sourceR - (std::int32_t)6860 * sourceG - (std::int32_t)1332 * sourceB + (std::int32_t)8192) / division));
                    }
                    pInputMemory += (inputHandlerWidth - inputWidth) * 3;
                    pOutputMemory += (outputHandlerWidth - inputWidth) * 3;
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
                        *(pOutputMemory++) = (outputType) ( ((((std::int32_t)4899 * sourceR+(std::int32_t)9617 * sourceG+(std::int32_t)1868 * sourceB) / 16384) << leftShift) + outputHandlerMinValue );
                        *(pOutputMemory++) = (outputType) ( outputMiddleValue + ((((std::int32_t)8192 * sourceB - (std::int32_t)2764 * sourceR - (std::int32_t)5428 * sourceG + (std::int32_t)8192) / 16384) << leftShift));
                        *(pOutputMemory++) = (outputType) ( outputMiddleValue + ((((std::int32_t)8192 * sourceR - (std::int32_t)6860 * sourceG - (std::int32_t)1332 * sourceB + (std::int32_t)8192) / 16384) << leftShift));
                    }
                    pInputMemory += (inputHandlerWidth - inputWidth) * 3;
                    pOutputMemory += (outputHandlerWidth - inputWidth) * 3;
                }
            }
        }
};

/// @}

} // namespace colorTransforms

} // namespace transforms

} // namespace imebra

} // namespace puntoexe

#endif // !defined(imebraRGBToYBRFULL_E27C63E7_A907_4899_9BD3_8026AD7D110C__INCLUDED_)
