/*
$fileHeader$
*/

/*! \file transform_swig.cpp
    \brief Implementation of the transform class for SWIG.

*/

#include "../include/imebra/transform.h"
#include "../implementation/transformImpl.h"

namespace imebra
{

Transform::Transform(const Transform& right): m_pTransform(right.m_pTransform)
{}

Transform& Transform::operator=(const Transform& right)
{
    m_pTransform = right.m_pTransform;
    return *this;
}

Transform::Transform(std::shared_ptr<imebra::implementation::transforms::transform> pTransform): m_pTransform(pTransform)
{}

bool Transform::isEmpty() const
{
    return m_pTransform == 0 || m_pTransform->isEmpty();
}

Image Transform::allocateOutputImage(Image& inputImage, unsigned int width, unsigned int height)
{
    return Image(m_pTransform->allocateOutputImage(inputImage.m_pImage, (std::uint32_t)width, (std::uint32_t)height));
}

void Transform::runTransform(
            const Image& inputImage,
            unsigned int inputTopLeftX, unsigned int inputTopLeftY, unsigned int inputWidth, unsigned int inputHeight,
            Image& outputImage,
            unsigned int outputTopLeftX, unsigned int outputTopLeftY)
{
    m_pTransform->runTransform(inputImage.m_pImage,
        (std::uint32_t) inputTopLeftX,
        (std::uint32_t) inputTopLeftY,
        (std::uint32_t) inputWidth,
        (std::uint32_t) inputHeight,
        outputImage.m_pImage,
        (std::uint32_t) outputTopLeftX,
        (std::uint32_t) outputTopLeftY);
}

}
