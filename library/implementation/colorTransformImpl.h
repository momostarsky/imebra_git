/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement 
 that your application must also be GPL), you may purchase a commercial 
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

/*! \file colorTransform.h
    \brief Declaration of the base class used by all the color transforms.

*/


#if !defined(imebraColorTransform_E27C63E7_A907_4899_9BD3_8026AD7D110C__INCLUDED_)
#define imebraColorTransform_E27C63E7_A907_4899_9BD3_8026AD7D110C__INCLUDED_

#include "transformImpl.h"


namespace dicomhero
{

namespace implementation
{

namespace transforms
{

/// \namespace colorTransforms
/// \brief This namespace contains all the classes
///         involved in the transformation between several
///         color spaces.
///
/// The color transformation is performed on images (see
///  dicomhero::implementation::image).
///
///////////////////////////////////////////////////////////
namespace colorTransforms
{

/// \addtogroup group_transforms
///
/// @{

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This is the base class used by the color
///         transforms classes.
///
/// Each color transform class can handle a color space
///  conversion from one color space to another.
///
/// The class colorTransformsFactory can select the
///  right transform automatically when queried with
///  the initial and the final color spaces as parameters.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class colorTransform: public transform
{
public:
	/// \brief Return the name of the color space that this 
	///         colorTransform can convert.
	///
	/// @return a string with the name of the color space that
	///          can be converted by the colorTransform
	///
	///////////////////////////////////////////////////////////
    virtual std::string getInitialColorSpace() const = 0;

	/// \brief Return the name of the color space that this
	///         colorTransform can generate.
	///
	/// @return a string with the name of the color space that
	///          can be generated by the colorTransform
	///
	///////////////////////////////////////////////////////////
    virtual std::string getFinalColorSpace() const = 0;

    virtual std::shared_ptr<image> allocateOutputImage(
            bitDepth_t inputDepth,
            const std::string& inputColorSpace,
            std::uint32_t inputHighBit,
            std::shared_ptr<palette> inputPalette,
            std::uint32_t outputWidth, std::uint32_t outputHeight) const override;

protected:
    // Check the color space of the input and output images
	///////////////////////////////////////////////////////////
    void checkColorSpaces(const std::string& inputHandlerColorSpace, const std::string& outputHandlerColorSpace) const;

    virtual void checkHighBit(std::uint32_t inputHighBit, std::uint32_t outputHighBit) const;

};

/// @}

} // namespace colorTransforms

} // namespace transforms

} // namespace implementation

} // namespace dicomhero


#endif // !defined(imebraColorTransform_E27C63E7_A907_4899_9BD3_8026AD7D110C__INCLUDED_)
