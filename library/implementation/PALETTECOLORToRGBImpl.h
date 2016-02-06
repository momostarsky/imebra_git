/*
$fileHeader$
*/

/*! \file PALETTECOLORToRGB.h
    \brief Declaration of the class PALETTECOLORToRGB.

*/

#if !defined(imebraPALETTECOLORToRGB_E27C63E7_A907_4899_9BD3_8026AD7D110C__INCLUDED_)
#define imebraPALETTECOLORToRGB_E27C63E7_A907_4899_9BD3_8026AD7D110C__INCLUDED_

#include "colorTransformImpl.h"
#include "LUTImpl.h"
#include "dataSetImpl.h"

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
    virtual std::string getInitialColorSpace() const;
    virtual std::string getFinalColorSpace() const;
    virtual std::shared_ptr<colorTransform> createColorTransform();

        DEFINE_RUN_TEMPLATE_TRANSFORM;

        template <class inputType, class outputType>
        void templateTransform(
            const inputType* inputHandlerData,
            outputType* outputHandlerData,
            image::bitDepth /* inputDepth */, std::uint32_t inputHandlerWidth, const std::string& inputHandlerColorSpace,
            std::shared_ptr<palette> inputPalette,
            std::uint32_t /* inputHighBit */,
            std::uint32_t inputTopLeftX, std::uint32_t inputTopLeftY, std::uint32_t inputWidth, std::uint32_t inputHeight,
            image::bitDepth /* outputDepth */, std::uint32_t outputHandlerWidth, const std::string& outputHandlerColorSpace,
            std::shared_ptr<palette> /* outputPalette */,
            std::uint32_t outputHighBit,
            std::uint32_t outputTopLeftX, std::uint32_t outputTopLeftY) const

        {
            checkColorSpaces(inputHandlerColorSpace, outputHandlerColorSpace);
            std::uint32_t inputHighBit = inputPalette->getRed()->getBits();
            checkHighBit(inputHighBit, outputHighBit);

            const inputType* pInputMemory(inputHandlerData);
            outputType* pOutputMemory(outputHandlerData);

            lut* pRed = inputPalette->getRed().get();
            lut* pGreen = inputPalette->getGreen().get();
            lut* pBlue = inputPalette->getBlue().get();

            pInputMemory += inputTopLeftY * inputHandlerWidth + inputTopLeftX;
            pOutputMemory += (outputTopLeftY * outputHandlerWidth + outputTopLeftX) * 3;

            std::int64_t outputHandlerMinValue = getMinValue<outputType>(outputHighBit);

            std::int32_t paletteValue;
            for(; inputHeight != 0; --inputHeight)
            {
                for(std::uint32_t scanPixels(inputWidth); scanPixels != 0; --scanPixels)
                {
                    paletteValue = (std::int32_t) (*pInputMemory++);
                    *pOutputMemory++ = (outputType)(pRed->mappedValue(paletteValue) + outputHandlerMinValue);
                    *pOutputMemory++ = (outputType)(pGreen->mappedValue(paletteValue) + outputHandlerMinValue);
                    *pOutputMemory++ = (outputType)(pBlue->mappedValue(paletteValue) + outputHandlerMinValue);
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

#endif // !defined(imebraPALETTECOLORToRGB_E27C63E7_A907_4899_9BD3_8026AD7D110C__INCLUDED_)
