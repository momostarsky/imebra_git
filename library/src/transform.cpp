/*
$fileHeader$
*/

/*! \file transform_swig.cpp
    \brief Implementation of the transform class for SWIG.

*/

#include "../include/imebra/transform.h"
#include "../implementation/transformImpl.h"

Transform::Transform(const Transform& right): m_pTransform(right.m_pTransform)
{}

Transform& Transform::operator=(const Transform& right)
{
    m_pTransform = right.m_pTransform;
    return *this;
}

Transform::Transform(puntoexe::ptr<puntoexe::imebra::transforms::transform> pTransform): m_pTransform(pTransform)
{}

bool Transform::isEmpty()
{
    return m_pTransform == 0 || m_pTransform->isEmpty();
}

Image Transform::allocateOutputImage(Image& inputImage, int width, int height)
{
    return Image(m_pTransform->allocateOutputImage(inputImage.m_pImage, (imbxUint32)width, (imbxUint32)height));
}

void Transform::runTransform(
            const Image& inputImage,
            int inputTopLeftX, int inputTopLeftY, int inputWidth, int inputHeight,
            Image& outputImage,
			int outputTopLeftX, int outputTopLeftY)
{
    m_pTransform->runTransform(inputImage.m_pImage,
        (imbxUint32) inputTopLeftX,
        (imbxUint32) inputTopLeftY,
        (imbxUint32) inputWidth,
        (imbxUint32) inputHeight,
        outputImage.m_pImage,
        (imbxUint32) outputTopLeftX,
        (imbxUint32) outputTopLeftY);
}

