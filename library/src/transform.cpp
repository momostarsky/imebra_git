/*
$fileHeader$
*/

/*! \file transform.cpp
    \brief Implementation of the Transform class.

*/

#include "../include/imebra/transform.h"
#include "../include/imebra/image.h"
#include "../implementation/transformImpl.h"

namespace imebra
{

Transform::~Transform()
{
}

Transform::Transform(std::shared_ptr<imebra::implementation::transforms::transform> pTransform): m_pTransform(pTransform)
{}

bool Transform::isEmpty() const
{
    return m_pTransform == 0 || m_pTransform->isEmpty();
}

Image* Transform::allocateOutputImage(const Image& inputImage, std::uint32_t width, std::uint32_t height) const
{
    return new Image(m_pTransform->allocateOutputImage(inputImage.m_pImage->getDepth(),
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
