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
            inputType* inputHandlerData, size_t /* inputHandlerSize */, imbxUint32 inputHandlerWidth, const std::wstring& inputHandlerColorSpace,
            ptr<palette> /* inputPalette */,
            imbxInt32 inputHandlerMinValue, imbxUint32 inputHandlerNumValues,
            imbxInt32 inputTopLeftX, imbxInt32 inputTopLeftY, imbxInt32 inputWidth, imbxInt32 inputHeight,
            outputType* outputHandlerData, size_t /* outputHandlerSize */, imbxInt32 outputHandlerWidth, const std::wstring& outputHandlerColorSpace,
            ptr<palette> /* outputPalette */,
            imbxInt32 outputHandlerMinValue, imbxUint32 outputHandlerNumValues,
            imbxInt32 outputTopLeftX, imbxInt32 outputTopLeftY)

        {
            checkColorSpaces(inputHandlerColorSpace, outputHandlerColorSpace);

            inputType* pInputMemory(inputHandlerData);
            outputType* pOutputMemory(outputHandlerData);

            pInputMemory += (inputTopLeftY * inputHandlerWidth + inputTopLeftX) * 3;
            pOutputMemory += (outputTopLeftY * outputHandlerWidth + outputTopLeftX) * 3;

            imbxInt32 minY(outputHandlerMinValue + outputHandlerNumValues / 16);
            imbxInt32 outputMiddleValue(outputHandlerMinValue + outputHandlerNumValues / 2);

            imbxInt32 sourceR, sourceG, sourceB;
            if(inputHandlerNumValues == outputHandlerNumValues)
            {
                for(; inputHeight != 0; --inputHeight)
                {
                    for(int scanPixels(inputWidth); scanPixels != 0; --scanPixels)
                    {
                        sourceR = *(pInputMemory++) - inputHandlerMinValue;
                        sourceG = *(pInputMemory++) - inputHandlerMinValue;
                        sourceB = *(pInputMemory++) - inputHandlerMinValue;
        		*(pOutputMemory++) = minY + (((imbxInt32)4207 * sourceR+(imbxInt32)8259 * sourceG+(imbxInt32)1604 * sourceB) >> 14);
                        *(pOutputMemory++) = outputMiddleValue + (((imbxInt32)7196 * sourceB - (imbxInt32)2428 * sourceR - (imbxInt32)4768 * sourceG + (imbxInt32)8192) >> 14);
                        *(pOutputMemory++) = outputMiddleValue + (((imbxInt32)7196 * sourceR - (imbxInt32)6026 * sourceG - (imbxInt32)1170 * sourceB + (imbxInt32)8192) >> 14);
                    }
                    pInputMemory += (inputHandlerWidth - inputWidth) * 3;
                    pOutputMemory += (outputHandlerWidth - inputWidth) * 3;
                }
            }
            else
            {
                for(; inputHeight != 0; --inputHeight)
                {
                    for(int scanPixels(inputWidth); scanPixels != 0; --scanPixels)
                    {
                        sourceR = *(pInputMemory++) - inputHandlerMinValue;
                        sourceG = *(pInputMemory++) - inputHandlerMinValue;
                        sourceB = *(pInputMemory++) - inputHandlerMinValue;
        		*(pOutputMemory++) = minY + ((((imbxInt32)4207 * sourceR+(imbxInt32)8259 * sourceG+(imbxInt32)1604 * sourceB) >> 14)  * outputHandlerNumValues) / inputHandlerNumValues;
                        *(pOutputMemory++) = outputMiddleValue + ((((imbxInt32)7196 * sourceB - (imbxInt32)2428 * sourceR - (imbxInt32)4768 * sourceG + (imbxInt32)8192) >> 14) * outputHandlerNumValues) / inputHandlerNumValues;
                        *(pOutputMemory++) = outputMiddleValue + ((((imbxInt32)7196 * sourceR - (imbxInt32)6026 * sourceG - (imbxInt32)1170 * sourceB + (imbxInt32)8192) >> 14) * outputHandlerNumValues) / inputHandlerNumValues;
                    }
                    pInputMemory += (inputHandlerWidth - inputWidth) * 3;
                    pOutputMemory += (outputHandlerWidth - inputWidth) * 3;
                }
            }
        }
};

} // namespace colorTransforms

} // namespace transforms

} // namespace imebra

} // namespace puntoexe

#endif // !defined(imebraRGBToYBRPARTIAL_E27C63E7_A907_4899_9BD3_8026AD7D110C__INCLUDED_)
