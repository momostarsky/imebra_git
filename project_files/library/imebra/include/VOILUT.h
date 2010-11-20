/*
$fileHeader$
*/

/*! \file VOILUT.h
    \brief Declaration of the class VOILUT.

*/

#if !defined(imebraVOILUT_8347C70F_1FC8_4df8_A887_8DE9E968B2CF__INCLUDED_)
#define imebraVOILUT_8347C70F_1FC8_4df8_A887_8DE9E968B2CF__INCLUDED_

#include "image.h"
#include "LUT.h"
#include "transform.h"



///////////////////////////////////////////////////////////
//
// Everything is in the namespace puntoexe::imebra
//
///////////////////////////////////////////////////////////
namespace puntoexe
{

namespace imebra
{

class lut;

namespace transforms
{

///////////////////////////////////////////////////////////
/// \brief Transform the value of the input image's pixels
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
	VOILUT(ptr<dataSet> pDataSet): m_pDataSet(pDataSet), m_windowCenter(0), m_windowWidth(0){}

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
	imbxUint32 getVOILUTId(imbxUint32 VOILUTNumber);

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
	std::wstring getVOILUTDescription(imbxUint32 VOILUTId);

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
	void setVOILUT(imbxUint32 VOILUTId);

	/// \brief Define the LUT to use for the transformation.
	///
	/// @param pLut the lut that will be used for the
	///              transformation
	///
	///////////////////////////////////////////////////////////
	void setLUT(ptr<lut> pLut);

	/// \brief Define the VOI width/center to use for the
	///         transformation.
	///
	/// @param center   the center value of the VOI
	/// @param width    the width value of the VOI
	///
	///////////////////////////////////////////////////////////
	void setCenterWidth(imbxInt32 center, imbxInt32 width);

	/// \brief Returns the VOI width/center used for the
	///         transformation.
	///
	/// @param pCenter  pointer to the recipient for the VOI
	///                  center
	/// @param pWidth    pointer to the recipient for the VOI
	///                  width
	///
	///////////////////////////////////////////////////////////
	void getCenterWidth(imbxInt32* pCenter, imbxInt32* pWidth);

        DEFINE_RUN_TEMPLATE_TRANSFORM;

        template <class inputType, class outputType>
        void templateTransform(
            inputType* inputHandlerData, size_t /* inputHandlerSize */, imbxUint32 inputHandlerWidth, const std::wstring& /* inputHandlerColorSpace */,
            ptr<palette> /* inputPalette */,
            imbxInt32 inputHandlerMinValue, imbxUint32 inputHandlerNumValues,
            imbxInt32 inputTopLeftX, imbxInt32 inputTopLeftY, imbxInt32 inputWidth, imbxInt32 inputHeight,
            outputType* outputHandlerData, size_t /* outputHandlerSize */, imbxInt32 outputHandlerWidth, const std::wstring& /* outputHandlerColorSpace */,
            ptr<palette> /* outputPalette */,
            imbxInt32 outputHandlerMinValue, imbxUint32 outputHandlerNumValues,
            imbxInt32 outputTopLeftX, imbxInt32 outputTopLeftY)

        {
            inputType* pInputMemory(inputHandlerData);
            outputType* pOutputMemory(outputHandlerData);

            pInputMemory += inputTopLeftY * inputHandlerWidth + inputTopLeftX;
            pOutputMemory += outputTopLeftY * outputHandlerWidth + outputTopLeftX;

            //
            // LUT found
            //
            ///////////////////////////////////////////////////////////
            if(m_pLUT != 0 && m_pLUT->getSize())
            {
                    lut* pLUT = m_pLUT.get();
                    inputHandlerNumValues = ((imbxUint32)1) << pLUT->getBits();
                    inputHandlerMinValue = 0;

                    if(inputHandlerNumValues == outputHandlerNumValues)
                    {
                        for(; inputHeight != 0; --inputHeight)
                        {
                            for(int scanPixels(inputWidth); scanPixels != 0; --scanPixels)
                            {
                                *(pOutputMemory++) = (outputType)( outputHandlerMinValue + pLUT->mappedValue((imbxInt32) (*(pInputMemory++))) );
                            }
                            pInputMemory += (inputHandlerWidth - inputWidth);
                            pOutputMemory += (outputHandlerWidth - inputWidth);
                        }
                    }
                    else
                    {
                        for(; inputHeight != 0; --inputHeight)
                        {
                            for(int scanPixels(inputWidth); scanPixels != 0; --scanPixels)
                            {
                                *(pOutputMemory++) = (outputType)( outputHandlerMinValue + (pLUT->mappedValue((imbxInt32) (*(pInputMemory++)) ) * outputHandlerNumValues ) / inputHandlerNumValues );
                            }
                            pInputMemory += (inputHandlerWidth - inputWidth);
                            pOutputMemory += (outputHandlerWidth - inputWidth);
                        }
                    }

                    return;
            }

            //
            // LUT not found.
            // Use the window's center/width
            //
            ///////////////////////////////////////////////////////////
            if(m_windowWidth <= 1)
            {
                    return;
            }

            imbxInt32 minValue = m_windowCenter-(m_windowWidth/2);
            imbxInt32 maxValue = m_windowCenter+(m_windowWidth/2);
            inputHandlerNumValues = maxValue - minValue;

            imbxInt32 value;
            for(; inputHeight != 0; --inputHeight)
            {

                for(int scanPixels(inputWidth); scanPixels != 0; --scanPixels)
                {
                    value = (imbxInt32) *(pInputMemory++);
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
                    *(pOutputMemory++) = (outputType)( (value - minValue) * outputHandlerNumValues / inputHandlerNumValues + outputHandlerMinValue );
                }
                pInputMemory += (inputHandlerWidth - inputWidth);
                pOutputMemory += (outputHandlerWidth - inputWidth);
            }
        }

        virtual ptr<image> allocateOutputImage(ptr<image> pInputImage, imbxUint32 width, imbxUint32 height);

protected:
        ptr<dataSet> m_pDataSet;
	ptr<lut> m_pLUT;
	imbxInt32 m_windowCenter;
	imbxInt32 m_windowWidth;
};



} // namespace transforms

} // namespace imebra

} // namespace puntoexe

#endif // !defined(imebraVOILUT_8347C70F_1FC8_4df8_A887_8DE9E968B2CF__INCLUDED_)
