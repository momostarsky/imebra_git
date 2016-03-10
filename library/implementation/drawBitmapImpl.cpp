/*
$fileHeader$
*/

/*! \file drawBitmap.cpp
    \brief Implementation of the transform drawBitmap.

*/

#include "drawBitmapImpl.h"
#include "imageImpl.h"
#include "colorTransformsFactoryImpl.h"
#include "transformHighBitImpl.h"

namespace imebra
{

namespace implementation
{


drawBitmap::drawBitmap(std::shared_ptr<transforms::transformsChain> transformsChain):
    m_userTransforms(transformsChain)
{
}


std::shared_ptr<memory> drawBitmap::getBitmap(const std::shared_ptr<const image>& sourceImage, drawBitmapType_t drawBitmapType, std::uint32_t rowAlignBytes)
{
    IMEBRA_FUNCTION_START();

    size_t memorySize(getBitmap(sourceImage, drawBitmapType, rowAlignBytes, 0, 0));

    std::shared_ptr<memory> bitmapMemory = std::make_shared<memory>(memorySize);

    // Retrieve the final bitmap's buffer
    ///////////////////////////////////////////////////////////
    std::uint8_t* pFinalBuffer = (std::uint8_t*)(bitmapMemory->data());

    getBitmap(sourceImage, drawBitmapType, rowAlignBytes, pFinalBuffer, memorySize);

    return bitmapMemory;

    IMEBRA_FUNCTION_END();

}

size_t drawBitmap::getBitmap(const std::shared_ptr<const image>& sourceImage, drawBitmapType_t drawBitmapType, std::uint32_t rowAlignBytes, std::uint8_t* pBuffer, size_t bufferSize)
{
    IMEBRA_FUNCTION_START();

    // This chain contains all the necessary transforms, including color transforms
    //  and high bit shift
    ///////////////////////////////////////////////////////////////////////////////
    transforms::transformsChain chain;

    if(m_userTransforms != 0 && !m_userTransforms->isEmpty())
    {
        chain.addTransform(m_userTransforms);
    }

    // Allocate the transforms that obtain an RGB24 image
    ///////////////////////////////////////////////////////////////////////////////
    std::string initialColorSpace;
    std::uint32_t highBit = 7;
    bitDepth_t depth = bitDepth_t::depthU8;
    if(chain.isEmpty())
    {
        initialColorSpace = sourceImage->getColorSpace();
        highBit = sourceImage->getHighBit();
        depth = sourceImage->getDepth();
    }
    else
    {
        std::shared_ptr<image> startImage(chain.allocateOutputImage(sourceImage->getDepth(),
                                                                                 sourceImage->getColorSpace(),
                                                                                 sourceImage->getHighBit(),
                                                                                 sourceImage->getPalette(),
                                                                                 1, 1));
        initialColorSpace = startImage->getColorSpace();
    }
    std::shared_ptr<transforms::colorTransforms::colorTransformsFactory> pColorTransformsFactory(transforms::colorTransforms::colorTransformsFactory::getColorTransformsFactory());
    std::shared_ptr<transforms::transform> rgbColorTransform(pColorTransformsFactory->getTransform(initialColorSpace, "RGB"));
    chain.addTransform(rgbColorTransform);

    if(highBit != 7 || depth != bitDepth_t::depthU8)
    {
        std::shared_ptr<transforms::transformHighBit> highBitTransform(std::make_shared<transforms::transformHighBit>());
        chain.addTransform(highBitTransform);
    }

    std::uint32_t width, height;
    sourceImage->getSize(&width, &height);
    std::uint32_t destPixelSize((drawBitmapType == drawBitmapType_t::drawBitmapRGBA || drawBitmapType == drawBitmapType_t::drawBitmapBGRA) ? 4 : 3);

    // Calculate the row' size, in bytes
    ///////////////////////////////////////////////////////////
    std::uint32_t rowSizeBytes = (width * destPixelSize + rowAlignBytes - 1) / rowAlignBytes;
    rowSizeBytes *= rowAlignBytes;

    // Allocate the memory for the final bitmap
    ///////////////////////////////////////////////////////////
    std::uint32_t memorySize(rowSizeBytes * height);
    if(memorySize > bufferSize)
    {
        return memorySize;
    }

    // If a transform chain is active then allocate a temporary
    //  output image
    ///////////////////////////////////////////////////////////
    std::shared_ptr<handlers::readingDataHandlerNumericBase> imageHandler;

    if(chain.isEmpty())
    {
        imageHandler = sourceImage->getReadingDataHandler();
    }
    else
    {
        std::shared_ptr<image> outputImage = chain.allocateOutputImage(sourceImage->getDepth(),
                                                                       sourceImage->getColorSpace(),
                                                                       sourceImage->getHighBit(),
                                                                       sourceImage->getPalette(),
                                                                       width, height);

        chain.runTransform(sourceImage, 0, 0, width, height, outputImage, 0, 0);
        imageHandler = outputImage->getReadingDataHandler();
    }

    const std::uint8_t* pImagePointer = imageHandler->getMemoryBuffer();

    std::uint32_t nextRowGap = rowSizeBytes - width * 3;

    // Scan all the final bitmap's rows
    ///////////////////////////////////////////////////////////
    switch(drawBitmapType)
    {
    case drawBitmapType_t::drawBitmapRGB:
    {
        for(std::uint32_t scanY(height); scanY != 0; --scanY)
        {
            for(std::uint32_t scanX(width); scanX != 0; --scanX)
            {
                *pBuffer++ = *pImagePointer++;
                *pBuffer++ = *pImagePointer++;
                *pBuffer++ = *pImagePointer++;
            }
            pBuffer += nextRowGap;
        }
        break;
    }
    case drawBitmapType_t::drawBitmapBGR:
    {
        std::uint8_t r, g;
        for(std::uint32_t scanY(height); scanY != 0; --scanY)
        {
            for(std::uint32_t scanX(width); scanX != 0; --scanX)
            {
                r = *pImagePointer++;
                g = *pImagePointer++;
                *pBuffer++ = *pImagePointer++;
                *pBuffer++ = g;
                *pBuffer++ = r;
            }
            pBuffer += nextRowGap;
        }
        break;
    }
    case drawBitmapType_t::drawBitmapRGBA:
    {
        for(std::uint32_t scanY(height); scanY != 0; --scanY)
        {
            for(std::uint32_t scanX(width); scanX != 0; --scanX)
            {
                *pBuffer++ = *pImagePointer++;
                *pBuffer++ = *pImagePointer++;
                *pBuffer++ = *pImagePointer++;
                *pBuffer++ = 0xff;
            }
            pBuffer += nextRowGap;
        }
        break;
    }
    default:
    {
        std::uint8_t r, g;
        for(std::uint32_t scanY(height); scanY != 0; --scanY)
        {
            for(std::uint32_t scanX(width); scanX != 0; --scanX)
            {
                r = *pImagePointer++;
                g = *pImagePointer++;
                *pBuffer++ = *pImagePointer++;
                *pBuffer++ = g;
                *pBuffer++ = r;
                *pBuffer++ = 0xff;
            }
            pBuffer += nextRowGap;
        }
        break;
    }
    }

    return memorySize;

    IMEBRA_FUNCTION_END();
}



} // namespace implementation

} // namespace imebra
