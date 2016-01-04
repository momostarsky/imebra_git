/*
$fileHeader$
*/

/*! \file transformsChain.h
    \brief Declaration of the class transformsChain.

*/

#if !defined(imebraTransformsChain_5DB89BFD_F105_45e7_B9D9_3756AC93C821__INCLUDED_)
#define imebraTransformsChain_5DB89BFD_F105_45e7_B9D9_3756AC93C821__INCLUDED_

#include <list>
#include "transformImpl.h"

namespace puntoexe
{

namespace imebra
{

namespace transforms
{

/// \addtogroup group_transforms
///
/// @{

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief Executes a sequence of transforms.
///
/// Before calling runTransform() specify the sequence
///  by calling addTransform().
/// Each specified transforms take the output of the 
///  previous transform as input.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class transformsChain: public transform
{
public:
	transformsChain();

	/// \brief Add a transform to the transforms chain.
	///
	/// The added transform will take the output of the 
	///  previously added transform as an input image and will
	///  supply its output to the next added transform or as
	///  an output of the transformsChain if it is the
	///  last added transform.
	///
	/// @param pTransform the transform to be added to
	///                    transformsChain
	///
	///////////////////////////////////////////////////////////
	void addTransform(std::shared_ptr<transform> pTransform);

	virtual void runTransform(
            const std::shared_ptr<image>& inputImage,
            std::uint32_t inputTopLeftX, std::uint32_t inputTopLeftY, std::uint32_t inputWidth, std::uint32_t inputHeight,
            const std::shared_ptr<image>& outputImage,
            std::uint32_t outputTopLeftX, std::uint32_t outputTopLeftY);

	/// \brief Returns true if the transform doesn't do
	///         anything.
	///
	/// @return false if the transform does something, or true
	///          if the transform doesn't do anything (e.g. an
	///          empty transformsChain object).
	///
	///////////////////////////////////////////////////////////
	virtual bool isEmpty();

	virtual std::shared_ptr<image> allocateOutputImage(std::shared_ptr<image> pInputImage, std::uint32_t width, std::uint32_t height);

protected:
	std::uint32_t m_inputWidth;
	std::uint32_t m_inputHeight;
	std::wstring m_inputColorSpace;
	image::bitDepth m_inputDepth;
	std::uint32_t m_inputHighBit;
	std::wstring m_outputColorSpace;
	image::bitDepth m_outputDepth;
	std::uint32_t m_outputHighBit;

	typedef std::list<std::shared_ptr<transform> > tTransformsList;
	tTransformsList m_transformsList;

	typedef std::list<std::shared_ptr<image> > tTemporaryImagesList;
	tTemporaryImagesList m_temporaryImages;

};

/// @}

} // namespace transforms

} // namespace imebra

} // namespace puntoexe

#endif // !defined(imebraTransformsChain_5DB89BFD_F105_45e7_B9D9_3756AC93C821__INCLUDED_)
