/*
$fileHeader$
*/

/*! \file applyLUT.h
    \brief Declaration of the class applyLUT.

*/

#if !defined(imebraApplyLUT_8347C70F_1FC8_4df8_A887_8DE9E968B2CF__INCLUDED_)
#define imebraApplyLUT_8347C70F_1FC8_4df8_A887_8DE9E968B2CF__INCLUDED_

#include "transform.h"
#include "image.h"
#include "dataSet.h"
#include "LUT.h"
#include "colorTransformsFactory.h"


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

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This exception is thrown by modalityVOILUT
///         when the images passed to the transform are
///         not monochromatic.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class applyLUTException: public transformException
{
public:
    applyLUTException(const std::string& message): transformException(message){}
};


/// \addtogroup group_transforms
///
/// @{

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This class applies a LUT to an image.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class applyLUT: public transformHandlers
{
public:
	/// \brief Constructor.
	///
    /// @param pLUT the LUT to apply to the image
	///
	///////////////////////////////////////////////////////////
    applyLUT(ptr<lut> pLUT);

	DEFINE_RUN_TEMPLATE_TRANSFORM;

	template <class inputType, class outputType>
			void templateTransform(
					inputType* inputHandlerData, size_t /* inputHandlerSize */, std::uint32_t inputHandlerWidth, const std::wstring& inputHandlerColorSpace,
					ptr<palette> /* inputPalette */,
                    std::int32_t /* inputHandlerMinValue */, std::uint32_t /* inputHighBit */,
					std::int32_t inputTopLeftX, std::int32_t inputTopLeftY, std::int32_t inputWidth, std::int32_t inputHeight,
					outputType* outputHandlerData, size_t /* outputHandlerSize */, std::int32_t outputHandlerWidth, const std::wstring& outputHandlerColorSpace,
					ptr<palette> /* outputPalette */,
                    std::int32_t /* outputHandlerMinValue */, std::uint32_t /* outputHighBit */,
					std::int32_t outputTopLeftX, std::int32_t outputTopLeftY)
	{
        PUNTOEXE_FUNCTION_START(L"applyLUT::templateTransform");
		if(!colorTransforms::colorTransformsFactory::isMonochrome(inputHandlerColorSpace) || !colorTransforms::colorTransformsFactory::isMonochrome(outputHandlerColorSpace))
		{
            PUNTOEXE_THROW(applyLUTException, "applyLUT can process only monochromatic images");
		}
		inputType* pInputMemory(inputHandlerData);
		outputType* pOutputMemory(outputHandlerData);

		pInputMemory += inputTopLeftY * inputHandlerWidth + inputTopLeftX;
		pOutputMemory += outputTopLeftY * outputHandlerWidth + outputTopLeftX;

        for(; inputHeight != 0; --inputHeight)
        {
            for(int scanPixels(inputWidth); scanPixels != 0; --scanPixels)
            {
                *(pOutputMemory++) = (outputType) ( m_lut->mappedValue((std::int32_t) *(pInputMemory++)) );
            }
            pInputMemory += (inputHandlerWidth - inputWidth);
            pOutputMemory += (outputHandlerWidth - inputWidth);
        }

		PUNTOEXE_FUNCTION_END();
	}

	virtual bool isEmpty();

	virtual ptr<image> allocateOutputImage(ptr<image> pInputImage, std::uint32_t width, std::uint32_t height);

private:
    ptr<lut> m_lut;
};


/// @}

} // namespace transforms

} // namespace imebra

} // namespace puntoexe

#endif // !defined(imebraApplyLUT_8347C70F_1FC8_4df8_A887_8DE9E968B2CF__INCLUDED_)
