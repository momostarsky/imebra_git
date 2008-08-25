/*
$fileHeader$
*/

/*! \file transformHighBit.h
    \brief Declaration of the class transformHighBit.

*/

#if !defined(imebraTransformHighBit_8347C70F_1FC8_4df8_A887_8DE9E968B2CF__INCLUDED_)
#define imebraTransformHighBit_8347C70F_1FC8_4df8_A887_8DE9E968B2CF__INCLUDED_

#include "transformBuffers.h"

namespace puntoexe
{

namespace imebra
{

namespace transforms
{

///////////////////////////////////////////////////////////
/// \brief Shift the image's content to adapt it to the
///         specified high bit.
///
/// In order to use this transform, both the input and
///  the output image must be defined by calling
///  declareInputImage() and declareOutputImage().
///
/// The input image is copied into the output image but
///  all the values are shifted to be fitted in the
///  output image's high bit settings.
///
///////////////////////////////////////////////////////////
class transformHighBit: public transformBuffersInPlace
{
public:
	virtual void doTransformBuffersInPlace(
		imbxUint32 sizeX,
		imbxUint32 sizeY,
		imbxUint32 inputChannelsNumber,
		std::wstring inputColorSpace,
		image::bitDepth inputDepth,
		imbxUint32 inputHighBit,
		imbxInt32* pOutputBuffer,
		imbxUint32 buffersSize,
		image::bitDepth* pOutputDepth,
		imbxUint32* pOutputHighBit
		);
};

} // namespace transforms

} // namespace imebra

} // namespace puntoexe

#endif // !defined(imebraTransformHighBit_8347C70F_1FC8_4df8_A887_8DE9E968B2CF__INCLUDED_)
