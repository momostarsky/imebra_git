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

namespace puntoexe
{
namespace imebra
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
    Transform(std::shared_ptr<puntoexe::imebra::transforms::transform> pTransform);
#endif


    bool isEmpty() const;

    Image allocateOutputImage(Image& pInputImage, unsigned int width, unsigned int height);

	void runTransform(
            const Image& inputImage,
            unsigned int inputTopLeftX, unsigned int inputTopLeftY, unsigned int inputWidth, unsigned int inputHeight,
            Image& outputImage,
            unsigned int outputTopLeftX, unsigned int outputTopLeftY);

#ifndef SWIG
    std::shared_ptr<puntoexe::imebra::transforms::transform> m_pTransform;
#endif
};

}

#endif // imebraTransform_SWIG_F6221390_BC44_4B83_B5BB_3485222FF1DD__INCLUDED_
