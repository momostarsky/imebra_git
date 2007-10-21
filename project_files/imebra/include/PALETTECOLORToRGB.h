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
	virtual void declareDataSet(ptr<dataSet> pDataSet);

	/// \brief Specify the palette to use for the conversion.
	///
	/// If the application doesn't call this function before
	///  calling doTransform(), then the transform uses the
	///  palette declared in the dataSet.
	///
	/// @param red    the lut that stores the red components 
	///                of the mapped values
	/// @param green  the lut that stores the green components 
	///                of the mapped values
	/// @param blue   the lut that stores the blue components 
	///                of the mapped values
	///
	///////////////////////////////////////////////////////////
	virtual void setLut(ptr<lut> red, ptr<lut> green, ptr<lut> blue);

	virtual void doTransform();

	virtual std::wstring getInitialColorSpace();
	virtual std::wstring getFinalColorSpace();
	virtual ptr<colorTransform> createColorTransform();

protected:
	virtual void doColorTransform(imbxInt32* pSourceMem, imbxInt32* pDestMem, imbxUint32 pixelsNumber, imbxInt32 inputMinValue, imbxInt32 inputMaxValue, imbxInt32 outputMinValue, imbxInt32 outputMaxValue);

	// Color palette
	///////////////////////////////////////////////////////////
protected:
	ptr<lut> m_redPalette;
	ptr<lut> m_greenPalette;
	ptr<lut> m_bluePalette;

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
