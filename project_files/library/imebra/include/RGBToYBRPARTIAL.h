/*
$fileHeader$
*/

/*! \file RGBToYBRPARTIAL.h
    \brief Declaration of the class RGBToYBRPARTIAL.

*/

#if !defined(imebraRGBToYBRPARTIAL_E27C63E7_A907_4899_9BD3_8026AD7D110C__INCLUDED_)
#define imebraRGBToYBRPARTIAL_E27C63E7_A907_4899_9BD3_8026AD7D110C__INCLUDED_

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
///         RGB into the color space YBR_PARTIAL.
///
/// The input image has to have the colorspace RGB,
///  while the output image is created by the transform
///  and will have the colorspace YBR_PARTIAL.
///
///////////////////////////////////////////////////////////
class RGBToYBRPARTIAL: public colorTransform
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

            std::int32_t minY(outputHandlerMinValue + ((std::int32_t)1 << (outputHighBit - 3)));
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
                        *(pOutputMemory++) = (outputType) ( minY + (((std::int32_t)4207 * sourceR+(std::int32_t)8259 * sourceG+(std::int32_t)1604 * sourceB) / division));
                        *(pOutputMemory++) = (outputType) ( outputMiddleValue + (((std::int32_t)7196 * sourceB - (std::int32_t)2428 * sourceR - (std::int32_t)4768 * sourceG + (std::int32_t)8192) / division) );
                        *(pOutputMemory++) = (outputType) ( outputMiddleValue + (((std::int32_t)7196 * sourceR - (std::int32_t)6026 * sourceG - (std::int32_t)1170 * sourceB + (std::int32_t)8192) / division) );
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
                        *(pOutputMemory++) = (outputType) ( minY + ((((std::int32_t)4207 * sourceR+(std::int32_t)8259 * sourceG+(std::int32_t)1604 * sourceB) / 16384)  << leftShift));
                        *(pOutputMemory++) = (outputType) ( outputMiddleValue + ((((std::int32_t)7196 * sourceB - (std::int32_t)2428 * sourceR - (std::int32_t)4768 * sourceG + (std::int32_t)8192) / 16384) << leftShift) );
                        *(pOutputMemory++) = (outputType) ( outputMiddleValue + ((((std::int32_t)7196 * sourceR - (std::int32_t)6026 * sourceG - (std::int32_t)1170 * sourceB + (std::int32_t)8192) / 16384) << leftShift) );
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

#endif // !defined(imebraRGBToYBRPARTIAL_E27C63E7_A907_4899_9BD3_8026AD7D110C__INCLUDED_)
