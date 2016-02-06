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

Image Transform::allocateOutputImage(Image& inputImage, std::uint32_t width, std::uint32_t height) const
{
    return Image(m_pTransform->allocateOutputImage(inputImage.m_pImage->getDepth(),
                                                   inputImage.m_pImage->getColorSpace(),
                                                   inputImage.m_pImage->getHighBit(),
                                                   inputImage.m_pImage->getPalette(),
                                                   width, height));
}

void Transform::runTransform(
            const Image& inputImage,
            std::uint32_t inputTopLeftX, std::uint32_t inputTopLeftY, std::uint32_t inputWidth, std::uint32_t inputHeight,
            Image& outputImage,
            std::uint32_t outputTopLeftX, std::uint32_t outputTopLeftY) const
{
    m_pTransform->runTransform(inputImage.m_pImage,
        inputTopLeftX,
        inputTopLeftY,
        inputWidth,
        inputHeight,
        outputImage.m_pImage,
        outputTopLeftX,
        outputTopLeftY);
}

}
