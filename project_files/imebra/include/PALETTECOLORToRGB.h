/*
$fileHeader$
*/

/*! \file PALETTECOLORToRGB.h
    \brief Declaration of the class PALETTECOLORToRGB.

*/

#if !defined(imebraPALETTECOLORToRGB_E27C63E7_A907_4899_9BD3_8026AD7D110C__INCLUDED_)
#define imebraPALETTECOLORToRGB_E27C63E7_A907_4899_9BD3_8026AD7D110C__INCLUDED_

#include "colorTransform.h"
#include "LUT.h"
#include "dataSet.h"

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
///         PALETTE COLOR into the color space RGB.
///
/// The input image has to have the colorspace
///  PALETTE COLOR, while the output image is created by 
///  the transform and will have the colorspace RGB.
///
/// The transform needs a dataSet or a palette in order
///  to perform the conversion.
/// Use declareDataSet() to declare the dataSet or setLut()
///  to declare the palette.
///
///////////////////////////////////////////////////////////
class PALETTECOLORToRGB: public colorTransform
{
public:
	virtual std::wstring getInitialColorSpace();
	virtual std::wstring getFinalColorSpace();
	virtual ptr<colorTransform> createColorTransform();

        DEFINE_RUN_TEMPLATE_TRANSFORM;

        template <class inputType, class outputType>
        void templateTransform(
            inputType* inputHandlerData, size_t inputHandlerSize, imbxUint32 inputHandlerWidth, const std::wstring& inputHandlerColorSpace,
            ptr<palette> inputPalette,
            imbxInt32 inputHandlerMinValue, imbxUint32 inputHandlerNumValues,
            imbxInt32 inputTopLeftX, imbxInt32 inputTopLeftY, imbxInt32 inputWidth, imbxInt32 inputHeight,
            outputType* outputHandlerData, size_t outputHandlerSize, imbxInt32 outputHandlerWidth, const std::wstring& outputHandlerColorSpace,
            ptr<palette> /* outputPalette */,
            imbxInt32 outputHandlerMinValue, imbxUint32 outputHandlerNumValues,
            imbxInt32 outputTopLeftX, imbxInt32 outputTopLeftY)

        {
            checkColorSpaces(inputHandlerColorSpace, outputHandlerColorSpace);

            inputType* pInputMemory(inputHandlerData);
            outputType* pOutputMemory(outputHandlerData);

            lut* pRed = inputPalette->getRed().get();
            lut* pGreen = inputPalette->getGreen().get();
            lut* pBlue = inputPalette->getBlue().get();

            inputHandlerMinValue = 0;
            inputHandlerNumValues = (imbxUint32)1 << (pRed->getBits());

            pInputMemory += inputTopLeftY * inputHandlerWidth + inputTopLeftX;
            pOutputMemory += (outputTopLeftY * outputHandlerWidth + outputTopLeftX) * 3;

            imbxInt32 paletteValue;
            if(inputHandlerNumValues == outputHandlerNumValues)
            {
                for(; inputHeight != 0; --inputHeight)
                {
                    for(int scanPixels(inputWidth); scanPixels != 0; --scanPixels)
                    {
                        paletteValue = *pInputMemory++;
                        *pOutputMemory++ = (outputType)(pRed->mappedValue(paletteValue) + outputHandlerMinValue);
                        *pOutputMemory++ = (outputType)(pGreen->mappedValue(paletteValue) + outputHandlerMinValue);
                        *pOutputMemory++ = (outputType)(pBlue->mappedValue(paletteValue) + outputHandlerMinValue);
                    }
                    pInputMemory += inputHandlerWidth - inputWidth;
                    pOutputMemory += (outputHandlerWidth - inputWidth) * 3;
                }
            }
            else
            {
                for(; inputHeight != 0; --inputHeight)
                {
                    for(int scanPixels(inputWidth); scanPixels != 0; --scanPixels)
                    {
                        paletteValue = *pInputMemory++;
                        *pOutputMemory++ = (outputType)((pRed->mappedValue(paletteValue) * outputHandlerNumValues) / inputHandlerNumValues + outputHandlerMinValue);
                        *pOutputMemory++ = (outputType)((pGreen->mappedValue(paletteValue) * outputHandlerNumValues) / inputHandlerNumValues + outputHandlerMinValue);
                        *pOutputMemory++ = (outputType)((pBlue->mappedValue(paletteValue) * outputHandlerNumValues) / inputHandlerNumValues + outputHandlerMinValue);
                    }
                    pInputMemory += inputHandlerWidth - inputWidth;
                    pOutputMemory += (outputHandlerWidth - inputWidth) * 3;
                }
            }

        }


};

class PALETTECOLORToRGBException: public colorTransformException
{
public:
	PALETTECOLORToRGBException(const std::string& message): colorTransformException(message){}
};

class PALETTECOLORToRGBExceptionWhoToldYouSo: public PALETTECOLORToRGBException
{
public:
	PALETTECOLORToRGBExceptionWhoToldYouSo(const std::string& message): PALETTECOLORToRGBException(message){}
};


} // namespace colorTransforms

} // namespace transforms

} // namespace imebra

} // namespace puntoexe

#endif // !defined(imebraPALETTECOLORToRGB_E27C63E7_A907_4899_9BD3_8026AD7D110C__INCLUDED_)
