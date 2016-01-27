/*
$fileHeader$
*/

/*! \file transform_swig.h
	\brief Declaration of the base class for transforms for SWIG.

*/

#if !defined(imebraTransform_SWIG_F6221390_BC44_4B83_B5BB_3485222FF1DD__INCLUDED_)
#define imebraTransform_SWIG_F6221390_BC44_4B83_B5BB_3485222FF1DD__INCLUDED_

#ifndef SWIG

#include <memory>
#include "definitions.h"
#include "image.h"

namespace imebra
{
namespace implementation
{
namespace transforms
{
class transform;
}
}
}
#endif

namespace imebra
{

class IMEBRA_API Transform
{

public:
    Transform(const Transform& right);
    Transform& operator=(const Transform& right);
    virtual ~Transform(){}

#ifndef SWIG
    Transform(std::shared_ptr<imebra::implementation::transforms::transform> pTransform);
#endif


    bool isEmpty() const;

    Image allocateOutputImage(Image& pInputImage, std::uint32_t width, std::uint32_t height);

	void runTransform(
            const Image& inputImage,
            std::uint32_t inputTopLeftX, std::uint32_t inputTopLeftY, std::uint32_t inputWidth, std::uint32_t inputHeight,
            Image& outputImage,
            std::uint32_t outputTopLeftX, std::uint32_t outputTopLeftY);

#ifndef SWIG
    std::shared_ptr<imebra::implementation::transforms::transform> m_pTransform;
#endif
};

}

#endif // imebraTransform_SWIG_F6221390_BC44_4B83_B5BB_3485222FF1DD__INCLUDED_
