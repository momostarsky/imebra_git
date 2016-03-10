/*
$fileHeader$
*/

/*! \file drawBitmap.cpp
    \brief Implementation of the class DrawBitmap.

*/

#include "../include/imebra/drawBitmap.h"
#include "../implementation/drawBitmapImpl.h"
#include "../include/imebra/image.h"
#include "../include/imebra/transformsChain.h"

namespace imebra
{

DrawBitmap::DrawBitmap():
    m_pDrawBitmap(std::make_shared<implementation::drawBitmap>(std::shared_ptr<implementation::transforms::transformsChain>()))
{
}

DrawBitmap::DrawBitmap(const DrawBitmap& right): m_pDrawBitmap(right.m_pDrawBitmap)
{
}

DrawBitmap::DrawBitmap(const TransformsChain& transformsChain):
    m_pDrawBitmap(std::make_shared<implementation::drawBitmap>(std::dynamic_pointer_cast<implementation::transforms::transformsChain>(transformsChain.m_pTransform)))
{
}

DrawBitmap::~DrawBitmap()
{
}

size_t DrawBitmap::getBitmap(const Image& image, drawBitmapType_t drawBitmapType, std::uint32_t rowAlignBytes, char* buffer, size_t bufferSize)
{
    return m_pDrawBitmap->getBitmap(image.m_pImage, drawBitmapType, rowAlignBytes, (std::uint8_t*)buffer, bufferSize);
}

ReadWriteMemory DrawBitmap::getBitmap(const Image& image, drawBitmapType_t drawBitmapType, std::uint32_t rowAlignBytes)
{
    return ReadWriteMemory(m_pDrawBitmap->getBitmap(image.m_pImage, drawBitmapType, rowAlignBytes));
}

}
