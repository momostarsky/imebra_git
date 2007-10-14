/*
$fileHeader$
*/

/*! \file transformBuffers.h
    \brief Declaration of the class transformBuffers.

*/

#if !defined(imebraTransformBuffers_5DB89BFD_F105_45e7_B9D9_3756AC93C821__INCLUDED_)
#define imebraTransformBuffers_5DB89BFD_F105_45e7_B9D9_3756AC93C821__INCLUDED_

#include "transform.h"
#include "image.h"


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
/// \brief This class is used as a base class by some
///         transforms that work on the image's pixels.
///
/// The class takes the input image and automatically
///  allocate an output image if it hasn't been declared.
/// Two temporary buffer are automatically allocated
///  (one for the input image and one for the output one)
///  and both of them are defined as signed long
///  (imbxInt32).
///
/// Then the virtual function doTransformBuffers() is 
///  called.
/// This function can change the output buffer's content.
///
/// doTransformBuffers() can modify the bit depth and
///  the high bit of the output buffer.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class transformBuffers : public transform
{

public:
	/// \brief This function takes care of allocating
	///         the temporary buffers and calling the 
	///         doTransformBuffers() function.
	///
	///////////////////////////////////////////////////////////
	virtual void doTransform();
	
	/// \brief This function, implemented in the derived 
	///         classes, modifies the content of the output
	///         buffer and sets its attributes.
	///
	/// @param sizeX      the width of the image in pixels
	/// @param sizeY      the height of the image in pixels
	/// @param inputChannelsNumber the number of color 
	///                    channels stored in the input buffer
	/// @param inputColorSpace the color space used by the
	///                    input buffer
	/// @param inputDepth the depth of the input buffer
	/// @param inputHighBit the high bit of the input buffer
	/// @param pInputBuffer a pointer to the first element of
	///                    the input buffer
	/// @param pOutputBuffer a pointer to the first element of
	///                    the output buffer
	/// @param buffersSize the size of the buffers, in pixels
	///                     (a pixel may include more than one
	///                     color channel)
	/// @param pOutputDepth a pointer to a variable that this
	///                     function fills with the output
	///                     buffer's bit depth.
	/// @param pOutputHighBit a pointer to a variable that 
	///                     this function fills with the
	///                     output buffer's high bit
	///
	///////////////////////////////////////////////////////////
	virtual void doTransformBuffers(
		imbxUint32 sizeX, 
		imbxUint32 sizeY,
		imbxUint32 inputChannelsNumber,
		std::wstring inputColorSpace,
		image::bitDepth inputDepth,
		imbxUint32 inputHighBit,
		imbxInt32* pInputBuffer,
		imbxInt32* pOutputBuffer,
		imbxUint32 buffersSize,
		image::bitDepth* pOutputDepth,
		imbxUint32* pOutputHighBit
		)=0;
};

} // namespace transforms

} // namespace imebra

} // namespace puntoexe

#endif // !defined(imebraTransformBuffers_5DB89BFD_F105_45e7_B9D9_3756AC93C821__INCLUDED_)
