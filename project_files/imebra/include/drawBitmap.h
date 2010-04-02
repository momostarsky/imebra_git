/*
$fileHeader$
*/

/*! \file drawBitmap.h
    \brief Declaration of the a class that draw an image into a bitmap.

This file is not included automatically by imebra.h

*/

#if !defined(imebraDrawBitmap_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_)
#define imebraDrawBitmap_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_

#include "../../base/include/memory.h"
#include "transformsChain.h"
#include <memory>
#include <string.h>

namespace puntoexe
{

namespace imebra
{


    ///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief Base class used for the exceptions thrown by
///         drawBitmap.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class drawBitmapException: public std::runtime_error
{
public:
	drawBitmapException(const std::string& message): std::runtime_error(message){}
};

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This exception is thrown by
///         declareInputImage() if the dataSet hasn't been
///         declared yet.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class drawBitmapExceptionDataSetNotDeclared: public drawBitmapException
{
public:
	drawBitmapExceptionDataSetNotDeclared(const std::string& message): drawBitmapException(message){}
};


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This exception is thrown by
///         doTransform() if the image hasn't been declared
///         yet.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class drawBitmapExceptionImageNotDeclared: public drawBitmapException
{
public:
	drawBitmapExceptionImageNotDeclared(const std::string& message): drawBitmapException(message){}
};


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This exception is thrown by
///         declareBitmapType() if the image's area that
///         has to be generated is not valid.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class drawBitmapExceptionInvalidArea: public drawBitmapException
{
public:
	drawBitmapExceptionInvalidArea(const std::string& message): drawBitmapException(message){}
};


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This exception is thrown by
///         declareBitmapType() if the align byte is
///         illegal (1, 2 and 4 are the typical values).
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class drawBitmapExceptionInvalidAlignByte: public drawBitmapException
{
public:
	drawBitmapExceptionInvalidAlignByte(const std::string& message): drawBitmapException(message){}
};


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This transform takes an image as an input and
///         returns an 8 bit RGB bitmap of the requested
///         image's area; the image's area is expanded or
///         reduced to fit into the destination bitmap's
///         size.
///
/// The transform processes only the first declared image.
/// A requirement of this transform is that the dataSet has
///  to be declared before the input image; this means
///  that declareDataSet() has to be called before
///  declareInputImage().
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
enum tDrawBitmapType
    {
        drawBitmapRGB,
        drawBitmapBGR
    };

class drawBitmap: public baseObject
{
public:
    drawBitmap(ptr<image> sourceImage, ptr<transforms::transformsChain> transformsChain);

    template <tDrawBitmapType drawBitmapType, int rowAlignBytes>
    ptr<memory> getBitmap(imbxInt32 totalWidthPixels, imbxInt32 totalHeightPixels,
		imbxInt32 visibleTopLeftX, imbxInt32 visibleTopLeftY, imbxInt32 visibleBottomRightX, imbxInt32 visibleBottomRightY,
                ptr<memory> reuseMemory)
    {
        PUNTOEXE_FUNCTION_START("drawBitmap::getBitmap");

	if(visibleTopLeftX == visibleBottomRightX || visibleTopLeftY == visibleBottomRightY)
	{
		return reuseMemory;
	}

	// Check if the image is visible in the specified area
	///////////////////////////////////////////////////////////
	if(
		visibleBottomRightX > totalWidthPixels ||
		visibleBottomRightY > totalHeightPixels ||
		visibleTopLeftX < 0 ||
		visibleTopLeftY < 0 ||
		visibleTopLeftX > visibleBottomRightX ||
		visibleTopLeftY > visibleBottomRightY
		)
	{
		PUNTOEXE_THROW(drawBitmapExceptionInvalidArea, "Destination area not valid");
	}

	imbxUint32 rowSizeBytes = ((visibleBottomRightX - visibleTopLeftX) * 3 + rowAlignBytes - 1) / rowAlignBytes;
	rowSizeBytes *= rowAlignBytes;

	imbxUint32 memorySize(rowSizeBytes * (visibleBottomRightY - visibleTopLeftY));
	if(reuseMemory == 0)
	{
		reuseMemory = memoryPool::getMemoryPool()->getMemory(memorySize);
	}
	else
	{
		reuseMemory->resize(memorySize);
	}

	// Find the multiplier that make the image bigger than
	//  the rendering area
	///////////////////////////////////////////////////////////
	imbxUint32 imageSizeX, imageSizeY;
	m_image->getSize(&imageSizeX, &imageSizeY);

	imbxUint8 leftShiftX(0);
	imbxUint32 maskX(0);
	while( (imageSizeX << leftShiftX) < (imbxUint32)totalWidthPixels)
	{
		++leftShiftX;
		maskX <<= 1;
		++maskX;
	}

	imbxUint8 leftShiftY(0);
	imbxUint32 maskY(0);
	while( (imageSizeY << leftShiftY) < (imbxUint32)totalHeightPixels)
	{
		++leftShiftY;
		maskY <<= 1;
		++maskY;
	}

	// Allocate an horizontal buffer that stores the pixels
	//  average colors
	///////////////////////////////////////////////////////////
	imbxUint32 destBitmapWidth(visibleBottomRightX - visibleTopLeftX);
	std::auto_ptr<imbxInt32> averagePixels(new imbxInt32[destBitmapWidth * 4]);
	std::auto_ptr<imbxUint32> sourcePixelIndex(new imbxUint32[destBitmapWidth + 1]);

	for(imbxInt32 scanPixelsX = visibleTopLeftX; scanPixelsX != visibleBottomRightX + 1; ++scanPixelsX)
	{
		sourcePixelIndex.get()[scanPixelsX - visibleTopLeftX] = scanPixelsX * (imageSizeX << leftShiftX) / totalWidthPixels;
	}

	imbxInt32 firstPixelX(sourcePixelIndex.get()[0]);
	imbxInt32 lastPixelX(sourcePixelIndex.get()[visibleBottomRightX - visibleTopLeftX]);

	ptr<handlers::dataHandlerNumericBase> imageHandler;
	imbxUint32 rowSize, channelSize, channelsNumber;
	ptr<image> rgbImage(new image);
	if(m_transformsChain->isEmpty())
	{
		imageHandler = m_image->getDataHandler(false, &rowSize, &channelSize, &channelsNumber);
	}
	else
	{
		rgbImage->create(lastPixelX - firstPixelX, 1, image::depthU8, L"RGB", 7);
		imageHandler = rgbImage->getDataHandler(false, &rowSize, &channelSize, &channelsNumber);
	}
	imbxUint8* imageMemory = imageHandler->getMemoryBuffer();

	// Retrieve the image's buffer
	///////////////////////////////////////////////////////////


	imbxUint8* pFinalBuffer = (imbxUint8*)(reuseMemory->data());
	imbxInt32 nextRowGap = rowSizeBytes - destBitmapWidth * 3;

	for(imbxInt32 scanY = visibleTopLeftY; scanY != visibleBottomRightY; ++scanY)
	{
		::memset(averagePixels.get(), 0, destBitmapWidth * 4 * sizeof(averagePixels.get()[0]));

		imbxInt32 firstPixelY = scanY * (imageSizeY << leftShiftY) / totalHeightPixels;
		imbxInt32 lastPixelY = (scanY + 1) * (imageSizeY << leftShiftY) / totalHeightPixels;
		for(imbxInt32 scanImageY = firstPixelY; scanImageY != lastPixelY; /* increased in the loop */)
		{
			imbxInt32* pAveragePointer = averagePixels.get();
			imbxUint32* pNextSourceXIndex = sourcePixelIndex.get();

                        imbxInt32* pImagePointer(0);
			if(m_transformsChain->isEmpty())
			{
				pImagePointer = &(imageMemory[(scanImageY >> leftShiftY) * imageSizeX * 3 + ((*pNextSourceXIndex) >> leftShiftX) * 3]);
			}
			else
			{
				m_transformsChain->runTransform(m_image, (*pNextSourceXIndex) >> leftShiftX, scanImageY >> leftShiftY, lastPixelX - firstPixelX, 1, rgbImage, 0, 0);
			}

                        imbxInt32 scanYBlock ( (scanImageY & (~maskY)) + ((imbxInt32)1 << leftShiftY) );
                        if(scanYBlock > lastPixelY)
                        {
                            scanYBlock = lastPixelY;
                        }
                        imbxInt32 numRows(scanYBlock - scanImageY);
                        scanImageY += numRows;

                        if(numRows == 1)
                        {
                            for(imbxInt32 scanX (destBitmapWidth); scanX != 0; --scanX)
                            {
                                for(imbxUint32 scanImageX = *(pNextSourceXIndex++); scanImageX != *pNextSourceXIndex; ++scanImageX)
                                {
                                        ++(*pAveragePointer);
                                        *(++pAveragePointer) += *pImagePointer;
                                        *(++pAveragePointer) += *(++pImagePointer);
                                        *(++pAveragePointer) += *(++pImagePointer);
                                        pAveragePointer -= 3;
                                        if( (scanImageX & maskX) != 0)
                                        {
                                                pImagePointer -= 2;
                                                continue;
                                        }
                                        ++pImagePointer;
                                }
                                pAveragePointer += 4;
                            }
                        }
                        else
                        {
                            for(imbxInt32 scanX (destBitmapWidth); scanX != 0; --scanX)
                            {
				    for(imbxUint32 scanImageX = *(pNextSourceXIndex++); scanImageX != *pNextSourceXIndex; ++scanImageX)
				    {
					    *pAveragePointer += numRows;
					    *(++pAveragePointer) += *pImagePointer  * numRows;
					    *(++pAveragePointer) += *(++pImagePointer)  * numRows;
					    *(++pAveragePointer) += *(++pImagePointer)  * numRows;
					    pAveragePointer -= 3;
					    if( (scanImageX & maskX) != 0)
					    {
						    pImagePointer -= 2;
						    continue;
					    }
					    ++pImagePointer;
				    }
				    pAveragePointer += 4;
                            }
                        }
		}

		// Copy the average to the bitmap
		imbxInt32* pAveragePointer = averagePixels.get();
		imbxUint32 counter;

		imbxUint32 r, g;
		for(imbxInt32 scanX (destBitmapWidth); scanX != 0; --scanX)
		{
			counter = (imbxUint32)*(pAveragePointer++);
			r = (imbxUint8) (((imbxUint32)*(pAveragePointer++) / counter) & 0xff);
			g = (imbxUint8) (((imbxUint32)*(pAveragePointer++) / counter) & 0xff);
			*(pFinalBuffer++) = (imbxUint8) (((imbxUint32)*(pAveragePointer++) / counter) & 0xff);
			*(pFinalBuffer++) = (imbxUint8)g;
			*(pFinalBuffer++) = (imbxUint8)r;
		}
		pFinalBuffer += nextRowGap;
	}
        PUNTOEXE_FUNCTION_END();

        return reuseMemory;

    }

protected:
    ptr<image> m_image;

    ptr<image> m_finalImage;

    // Transform that calculates an 8 bit per channel RGB image
    ptr<transforms::transformsChain> m_transformsChain;
};





} // namespace imebra

} // namespace puntoexe

#endif // !defined(imebraDrawBitmap_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_)

