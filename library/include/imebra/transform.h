/*
$fileHeader$
*/

/*! \file transform.h
    \brief Declaration of the base class for transforms.

*/

#if !defined(imebraTransform__INCLUDED_)
#define imebraTransform__INCLUDED_

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

#ifndef SWIG
    friend class TransformsChain;
    friend class DrawBitmap;
    friend class ColorTransformsFactory;
    friend class TransformHighBit;
    friend class ModalityVOILUT;
    friend class VOILUT;

private:
    Transform(std::shared_ptr<imebra::implementation::transforms::transform> pTransform);
#endif


public:
    Transform(const Transform& right);
    virtual ~Transform();

    Transform& operator=(const Transform& right);


    bool isEmpty() const;

    Image allocateOutputImage(const Image& pInputImage, std::uint32_t width, std::uint32_t height) const;

	void runTransform(
            const Image& inputImage,
            std::uint32_t inputTopLeftX, std::uint32_t inputTopLeftY, std::uint32_t inputWidth, std::uint32_t inputHeight,
            Image& outputImage,
            std::uint32_t outputTopLeftX, std::uint32_t outputTopLeftY) const;

#ifndef SWIG
protected:
    std::shared_ptr<imebra::implementation::transforms::transform> m_pTransform;
#endif
};

}

#endif // imebraTransform__INCLUDED_
