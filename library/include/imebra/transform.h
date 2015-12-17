/*
$fileHeader$
*/

/*! \file transform_swig.h
	\brief Declaration of the base class for transforms for SWIG.

*/

#if !defined(imebraTransform_SWIG_F6221390_BC44_4B83_B5BB_3485222FF1DD__INCLUDED_)
#define imebraTransform_SWIG_F6221390_BC44_4B83_B5BB_3485222FF1DD__INCLUDED_

#ifndef SWIG

#include "../../implementation/baseObjectImpl.h"

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


#include "image.h"

namespace imebra
{

class Transform
{

public:
    Transform(const Transform& right);
    Transform& operator=(const Transform& right);
    virtual ~Transform(){}

#ifndef SWIG
    Transform(puntoexe::ptr<puntoexe::imebra::transforms::transform> pTransform);
#endif


    bool isEmpty() const;

	Image allocateOutputImage(Image& pInputImage, int width, int height);

	void runTransform(
            const Image& inputImage,
            int inputTopLeftX, int inputTopLeftY, int inputWidth, int inputHeight,
            Image& outputImage,
			int outputTopLeftX, int outputTopLeftY);

#ifndef SWIG
    puntoexe::ptr<puntoexe::imebra::transforms::transform> m_pTransform;
#endif
};

}

#endif // imebraTransform_SWIG_F6221390_BC44_4B83_B5BB_3485222FF1DD__INCLUDED_
