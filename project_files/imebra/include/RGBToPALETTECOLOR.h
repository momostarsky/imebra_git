/*
$fileHeader$
*/

/*! \file RGBToPALETTECOLOR.h
    \brief Declaration of the class RGBToPALETTECOLOR.

*/

#if !defined(imebraRGBToPALETTECOLOR_E27C63E7_A907_4899_9BD3_8026AD7D110C__INCLUDED_)
#define imebraRGBToPALETTECOLOR_E27C63E7_A907_4899_9BD3_8026AD7D110C__INCLUDED_

#include <memory>
#include "PALETTECOLORToRGB.h"

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
///         RGB into the color space PALETTE COLOR.
///
/// The input image has to have the colorspace RGB,
///  while the output image is created by the transform
///  and will have the colorspace PALETTE COLOR.
///
/// If a palette has been defined by calling setLut() or
///  declareDataSet(), then the specified lut will be
///  used for the conversion.
///
/// If the declared dataset doesn't contain a palette,
///  or the dataSet nor the palette have been defined then
///  the function calculate a new palette and stores it
///  in the declared dataSet (if any).
/// The calculated lut will also be used for the
///  conversion.
///
/// When multiple image have been declared as input
///  parameters, then the palette will be shared by all the
///  images.
///
///////////////////////////////////////////////////////////
class RGBToPALETTECOLOR: public PALETTECOLORToRGB
{
public:
	RGBToPALETTECOLOR(): m_octreeBits(8), m_octreeMask(0x0080), m_leavesCount(0) {}

	virtual void declareDataSet(ptr<dataSet> pDataSet);
	virtual void setLut(ptr<lut> red, ptr<lut> green, ptr<lut> blue);

	virtual void doTransform();

	virtual std::wstring getInitialColorSpace();
	virtual std::wstring getFinalColorSpace();
	virtual ptr<colorTransform> createColorTransform();

protected:
	virtual void doColorTransform(imbxInt32* pSourceMem, imbxInt32* pDestMem, imbxUint32 pixelsNumber, imbxInt32 inputMinValue, imbxInt32 inputMaxValue, imbxInt32 outputMinValue, imbxInt32 outputMaxValue);

	void findPalette();

	class octreeNode
	{
	public:
		octreeNode (): m_reference(0), m_red(0), m_green(0), m_blue(0), m_childrenCount(0), m_index(0){}

		void findNodeToReduce(imbxUint32* pMinReferenceCount, octreeNode** pReduceNode);

		void assignColors(lut* pRed, lut* pGreen, lut* pBlue, imbxUint32* pIndex);

		imbxUint32 m_reference;
		imbxInt32 m_red;
		imbxInt32 m_green;
		imbxInt32 m_blue;
		std::auto_ptr<octreeNode> m_children[8];
		char m_childrenCount;

		imbxUint32 m_index;
	} m_rootNode;
	char m_octreeBits;
	imbxInt32 m_octreeMask;

	imbxUint32 m_leavesCount;

	void resetOctree(char bits);
	void insertOctreeColor(imbxInt32 red, imbxInt32 green, imbxUint32 blue, imbxInt32 index);
	void reduceOctreeColor(imbxUint32 size);
	void findNodeToReduce(octreeNode* pParentNode, imbxUint32* pMinReferenceCount, octreeNode** pReduceNode);
	void generatePaletteFromOctree();
	imbxUint32 getOctreeIndex(imbxInt32 red, imbxInt32 green, imbxInt32 blue);

};

class RGBToPALETTECOLORException: public colorTransformException
{
public:
	RGBToPALETTECOLORException(const std::string& message): colorTransformException(message){}
};


} // namespace colorTransforms

} // namespace transforms

} // namespace imebra

} // namespace puntoexe

#endif // !defined(imebraRGBToPALETTECOLOR_E27C63E7_A907_4899_9BD3_8026AD7D110C__INCLUDED_)
