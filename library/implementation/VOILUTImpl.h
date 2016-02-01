/*
$fileHeader$
*/

/*! \file VOILUT.h
    \brief Declaration of the class VOILUT.

*/

#if !defined(imebraVOILUT_8347C70F_1FC8_4df8_A887_8DE9E968B2CF__INCLUDED_)
#define imebraVOILUT_8347C70F_1FC8_4df8_A887_8DE9E968B2CF__INCLUDED_

#include "imageImpl.h"
#include "LUTImpl.h"
#include "transformImpl.h"



///////////////////////////////////////////////////////////
//
// Everything is in the namespace imebra::implementation
//
///////////////////////////////////////////////////////////
namespace imebra
{

namespace implementation
{

class lut;

namespace transforms
{

/// \addtogroup group_transforms
///
/// @{

///////////////////////////////////////////////////////////
/// \brief Transforms the value of the input image's pixels
///         by using the presentation VOI/LUT defined in
///         the dataSet.
///
/// The dataSet could define more than one VOI/LUT: by
///  default the transform uses the first VOI or LUT
///  defined in the dataset.
///
/// To control which VOI/LUT is used for the
///  transformation the application must use the functions
///  getVOILUTId(), getVOILUTDescription(), setVOILUT() or
///  set the VOI or the LUT directly by calling
///  setCenterWidth() or setLUT().
///
///////////////////////////////////////////////////////////
class VOILUT: public transforms::transformHandlers
{
public:
    /// \brief Constructor.
    ///
    /// @param pDataSet the dataset from which the input image
    ///        comes from
    ///
    ///////////////////////////////////////////////////////////
	VOILUT(std::shared_ptr<dataSet> pDataSet): m_pDataSet(pDataSet), m_windowCenter(0), m_windowWidth(0){}

	/// \brief Retrieve an ID for a VOI or a LUT.
	///
	/// The returned ID can be used with the functions
	///  getVOILUTDescription() and setVOILUT().
	///
	/// The function returns 0 when the requested VOI/LUT
	///  doesn't exist.
	///
	/// The parameter VOILUTNumber is a zero based index used
	///  to scan all the available VOIs first and then all the
	///  LUTs.
	/// For instance, if VOILUTNumber is 3 and the dataSet
	///  contains 2 VOIs and 3 LUTs, then the function will
	///  return the ID for the second LUT.
	///
	/// @param VOILUTNumber  a number that identifies the
	///                       VOI or the LUT for which the
	///                       ID is requested.
	///                      The value 0 refers to the first
	///                       VOI in the dataSet or to the
	///                       first LUT if there isn't any
	///                       defined VOI. Bigger values refer
	///                       to the following VOIs or LUTs
	///                       when all the VOIs have been
	///                       scanned
	/// @return an ID that can be used with
	///          getVOILUTDescription() and setVOILUT(), or 0
	///                       if the requested VOI/LUT doesn't
	///                       exist
	///
	///////////////////////////////////////////////////////////
	std::uint32_t getVOILUTId(std::uint32_t VOILUTNumber);

    /// \brief List of ids of the VOIs and LUTs defined in
    ///        the dataset.
    ///
    /// The list is returned by getVOILUTIds() and each id can
    ///  be used with getVOILUTDescription() and setVOILUT().
    ///
    ///////////////////////////////////////////////////////////
    typedef std::list<std::uint32_t> voilutIds_t;

    /// \brief Return a list of ids of the VOIs and LUTs
    ///        defined in the database.
    ///
    /// @return a list of ids of the available VOI/LUTs
    ///
    ///////////////////////////////////////////////////////////
    voilutIds_t getVOILUTIds();

	/// \brief Return a description for the VOI or LUT with
	///         the specified ID.
	///
	/// The VOI/LUT ID can be obtained by calling
	///  getVOILUTId().
	///
	/// @param VOILUTId the id of the VOI/LUT for which the
	///                  description is required
	/// @return         the VOI/LUT description
	///
	///////////////////////////////////////////////////////////
	std::wstring getVOILUTDescription(std::uint32_t VOILUTId);

	/// \brief Define the VOI/LUT to use for the
	///         transformation.
	///
	/// The VOI/LUT ID can be obtained by calling
	///  getVOILUTId().
	///
	/// Disable the VOI/LUT transform if the parameter is 0.
	///
	/// @param VOILUTId the ID of the VOI/LUT to use for the
	///                  transformation, or 0 to disable the
	///                  transformation
	///
	///////////////////////////////////////////////////////////
	void setVOILUT(std::uint32_t VOILUTId);

	/// \brief Define the LUT to use for the transformation.
	///
	/// @param pLut the lut that will be used for the
	///              transformation
	///
	///////////////////////////////////////////////////////////
	void setLUT(std::shared_ptr<lut> pLut);

	/// \brief Define the VOI width/center to use for the
	///         transformation.
	///
	/// @param center   the center value of the VOI
	/// @param width    the width value of the VOI
	///
	///////////////////////////////////////////////////////////
    void setCenterWidth(double center, double width);

	/// \brief Returns the VOI width/center used for the
	///         transformation.
	///
	/// @param pCenter  pointer to the recipient for the VOI
	///                  center
	/// @param pWidth    pointer to the recipient for the VOI
	///                  width
	///
	///////////////////////////////////////////////////////////
    void getCenterWidth(double* pCenter, double* pWidth);

    /// \brief Finds and apply the optimal VOI values.
    ///
    /// @param inputImage    the image for which the optimal
    ///                      VOI must be found
    /// @param inputTopLeftX the horizontal coordinate of the
    ///                       top-left corner of the area for
    ///                       which the optimal VOI must be
    ///                       found
    /// @param inputTopLeftY the vertical coordinate of the
    ///                       top-left corner of the area for
    ///                       which the optimal VOI must be
    ///                       found
    /// @param inputWidth    the width of the area for which
    ///                       the optimal VOI must be found
    /// @param inputHeight   the height of the area for which
    ///                       the optimal VOI must be found
    ///
    ///////////////////////////////////////////////////////////
    void applyOptimalVOI(const std::shared_ptr<imebra::implementation::image>& inputImage, std::uint32_t inputTopLeftX, std::uint32_t inputTopLeftY, std::uint32_t inputWidth, std::uint32_t inputHeight);


	DEFINE_RUN_TEMPLATE_TRANSFORM;

    // The actual transformation is done here
    //
    ///////////////////////////////////////////////////////////
	template <class inputType, class outputType>
			void templateTransform(
                    const inputType* inputHandlerData,
                    outputType* outputHandlerData,
                    std::uint32_t inputHandlerWidth, const std::string& /* inputHandlerColorSpace */,
					std::shared_ptr<palette> /* inputPalette */,
                    std::uint32_t inputHighBit,
                    std::uint32_t inputTopLeftX, std::uint32_t inputTopLeftY, std::uint32_t inputWidth, std::uint32_t inputHeight,
                    std::uint32_t outputHandlerWidth, const std::string& /* outputHandlerColorSpace */,
					std::shared_ptr<palette> /* outputPalette */,
                    std::uint32_t outputHighBit,
                    std::uint32_t outputTopLeftX, std::uint32_t outputTopLeftY)

	{
        const inputType* pInputMemory(inputHandlerData);
		outputType* pOutputMemory(outputHandlerData);

		pInputMemory += inputTopLeftY * inputHandlerWidth + inputTopLeftX;
		pOutputMemory += outputTopLeftY * outputHandlerWidth + outputTopLeftX;

        std::int64_t inputHandlerMinValue = getMinValue<inputType>(inputHighBit);
        std::int64_t outputHandlerMinValue = getMinValue<outputType>(outputHighBit);

		//
		// LUT found
		//
		///////////////////////////////////////////////////////////
		if(m_pLUT != 0 && m_pLUT->getSize() != 0)
		{
            for(; inputHeight != 0; --inputHeight)
            {
                for(std::uint32_t scanPixels(inputWidth); scanPixels != 0; --scanPixels)
                {
                    *(pOutputMemory++) = (outputType)( outputHandlerMinValue + m_pLUT->mappedValue((std::int32_t)*pInputMemory++ ));
                }
                pInputMemory += (inputHandlerWidth - inputWidth);
                pOutputMemory += (outputHandlerWidth - inputWidth);
            }
			return;
		}

		//
		// LUT not found.
		// Use the window's center/width
		//
        ///////////////////////////////////////////////////////////
        std::int64_t inputHandlerNumValues = (std::int64_t)1 << (inputHighBit + 1);
        std::int64_t outputHandlerNumValues = (std::int64_t)1 << (outputHighBit + 1);
        std::int64_t minValue = (std::int64_t)(m_windowCenter - m_windowWidth/2);
        std::int64_t maxValue = (std::int64_t)(m_windowCenter + m_windowWidth/2);
		if(m_windowWidth <= 1)
		{
			minValue = inputHandlerMinValue ;
			maxValue = inputHandlerMinValue + inputHandlerNumValues;
		}
		else
		{
			inputHandlerNumValues = maxValue - minValue;
		}

        std::int64_t value;

        if(inputHandlerNumValues > outputHandlerNumValues)
        {
            std::int32_t ratio = (std::int32_t)(inputHandlerNumValues / outputHandlerNumValues);
            for(; inputHeight != 0; --inputHeight)
            {

                for(std::uint32_t scanPixels(inputWidth); scanPixels != 0; --scanPixels)
                {
                    value = (std::int64_t) *(pInputMemory++);
                    if(value <= minValue)
                    {
                        *(pOutputMemory++) = (outputType)outputHandlerMinValue;
                        continue;
                    }
                    if(value >= maxValue)
                    {
                        *(pOutputMemory++) = (outputType)( outputHandlerMinValue + outputHandlerNumValues - 1 );
                        continue;
                    }
                    *(pOutputMemory++) = (outputType)( (value - minValue) / ratio + outputHandlerMinValue );
                }
                pInputMemory += (inputHandlerWidth - inputWidth);
                pOutputMemory += (outputHandlerWidth - inputWidth);
            }
        }
        else
        {
            std::int32_t ratio = (std::int32_t)(outputHandlerNumValues / inputHandlerNumValues);
            for(; inputHeight != 0; --inputHeight)
            {

                for(std::uint32_t scanPixels(inputWidth); scanPixels != 0; --scanPixels)
                {
                    value = (std::int64_t) *(pInputMemory++);
                    if(value <= minValue)
                    {
                        *(pOutputMemory++) = (outputType)outputHandlerMinValue;
                        continue;
                    }
                    if(value >= maxValue)
                    {
                        *(pOutputMemory++) = (outputType)( outputHandlerMinValue + outputHandlerNumValues - 1 );
                        continue;
                    }
                    *(pOutputMemory++) = (outputType)( (value - minValue) * ratio + outputHandlerMinValue );
                }
                pInputMemory += (inputHandlerWidth - inputWidth);
                pOutputMemory += (outputHandlerWidth - inputWidth);
            }
        }
	}


	virtual bool isEmpty();

	virtual std::shared_ptr<image> allocateOutputImage(std::shared_ptr<image> pInputImage, std::uint32_t width, std::uint32_t height);

protected:

    // Find the optimal VOI
    //
    ///////////////////////////////////////////////////////////
    template <class inputType>
            void templateFindOptimalVOI(
                    inputType* inputHandlerData, size_t /* inputHandlerSize */, std::uint32_t inputHandlerWidth,
                    std::uint32_t inputTopLeftX, std::uint32_t inputTopLeftY, std::uint32_t inputWidth, std::uint32_t inputHeight)
    {
        inputType* pInputMemory(inputHandlerData + inputHandlerWidth * inputTopLeftY + inputTopLeftX);
        inputType minValue(*pInputMemory);
        inputType maxValue(minValue);
        inputType value;
        for(std::uint32_t scanY(inputHeight); scanY != 0; --scanY)
        {
            for(std::uint32_t scanX(inputWidth); scanX != 0; --scanX)
            {
                value = *(pInputMemory++);
                if(value < minValue)
                {
                    minValue = value;
                }
                else if(value > maxValue)
                {
                    maxValue = value;
                }
            }
            pInputMemory += inputHandlerWidth - inputWidth;
        }
        double center = (std::int32_t)(((std::int64_t)maxValue - (std::int64_t)minValue) / 2 + (std::int64_t)minValue);
        double width = (std::int64_t)maxValue - (std::int64_t)minValue;
        setCenterWidth(center, width);
    }

    std::shared_ptr<dataSet> m_pDataSet;
	std::shared_ptr<lut> m_pLUT;
    double m_windowCenter;
    double m_windowWidth;
};

/// @}

} // namespace transforms

} // namespace implementation

} // namespace imebra

#endif // !defined(imebraVOILUT_8347C70F_1FC8_4df8_A887_8DE9E968B2CF__INCLUDED_)
