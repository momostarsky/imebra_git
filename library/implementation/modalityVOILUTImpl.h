/*
$fileHeader$
*/

/*! \file modalityVOILUT.h
    \brief Declaration of the class modalityVOILUT.

*/

#if !defined(imebraModalityVOILUT_8347C70F_1FC8_4df8_A887_8DE9E968B2CF__INCLUDED_)
#define imebraModalityVOILUT_8347C70F_1FC8_4df8_A887_8DE9E968B2CF__INCLUDED_

#include "transformImpl.h"
#include "imageImpl.h"
#include "dataSetImpl.h"
#include "LUTImpl.h"
#include "colorTransformsFactoryImpl.h"


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
class modalityVOILUTException: public transformException
{
public:
    modalityVOILUTException(const std::string& message): transformException(message){}
};


/// \addtogroup group_transforms
///
/// @{

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This class transforms the pixel values of the
///         image retrieved from the dataset into values
///         that are meaningful to th application.
///
/// For instance, the original pixel values could store
///  a device specific value that has a meaning only when
///  used by the device that generated it: this transform
///  uses the modality VOI/LUT defined in the dataset to
///  convert the original values into optical density
///  or other known measure units.
///
/// If the dataset doesn't define any modality VOI/LUT
///  transformation, then the input image is simply copied
///  into the output image.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class modalityVOILUT: public transformHandlers
{
public:
	/// \brief Constructor.
	///
	/// @param pDataSet the dataSet from which the input
	///         images come from
	///
	///////////////////////////////////////////////////////////
    modalityVOILUT(ptr<dataSet> pDataSet);

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
		PUNTOEXE_FUNCTION_START(L"modalityVOILUT::templateTransform");
		if(!colorTransforms::colorTransformsFactory::isMonochrome(inputHandlerColorSpace) || !colorTransforms::colorTransformsFactory::isMonochrome(outputHandlerColorSpace))
		{
			PUNTOEXE_THROW(modalityVOILUTException, "modalityVOILUT can process only monochromatic images");
		}
		inputType* pInputMemory(inputHandlerData);
		outputType* pOutputMemory(outputHandlerData);

		pInputMemory += inputTopLeftY * inputHandlerWidth + inputTopLeftX;
		pOutputMemory += outputTopLeftY * outputHandlerWidth + outputTopLeftX;

		//
		// Modality LUT found
		//
		///////////////////////////////////////////////////////////
		if(m_voiLut != 0 && m_voiLut->getSize() != 0 && m_voiLut->checkValidDataRange())
		{
			for(; inputHeight != 0; --inputHeight)
			{
				for(int scanPixels(inputWidth); scanPixels != 0; --scanPixels)
				{
					*(pOutputMemory++) = (outputType) ( m_voiLut->mappedValue((std::int32_t) *(pInputMemory++)) );
				}
				pInputMemory += (inputHandlerWidth - inputWidth);
				pOutputMemory += (outputHandlerWidth - inputWidth);
			}
			return;
		}

		//
		// Modality LUT not found
		//
		///////////////////////////////////////////////////////////

		// Retrieve the intercept/scale pair
		///////////////////////////////////////////////////////////
		for(; inputHeight != 0; --inputHeight)
		{
			for(int scanPixels(inputWidth); scanPixels != 0; --scanPixels)
			{
				*(pOutputMemory++) = (outputType)((double)(*(pInputMemory++)) * m_rescaleSlope + m_rescaleIntercept + 0.5);
			}
			pInputMemory += (inputHandlerWidth - inputWidth);
			pOutputMemory += (outputHandlerWidth - inputWidth);
		}
		PUNTOEXE_FUNCTION_END();
	}

	virtual bool isEmpty();

	virtual ptr<image> allocateOutputImage(ptr<image> pInputImage, std::uint32_t width, std::uint32_t height);

private:
    ptr<dataSet> m_pDataSet;
    ptr<lut> m_voiLut;
    double m_rescaleIntercept;
    double m_rescaleSlope;
	bool m_bEmpty;
};


/// @}

} // namespace transforms

} // namespace imebra

} // namespace puntoexe

#endif // !defined(imebraModalityVOILUT_8347C70F_1FC8_4df8_A887_8DE9E968B2CF__INCLUDED_)
