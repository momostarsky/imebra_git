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
/// \brief This class takes an image as an input and
///         returns an 8 bit RGB bitmap of the requested
///         image's area; the image's area is expanded or
///         reduced to fit into the destination bitmap's
///         size.
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
        PUNTOEXE_FUNCTION_START(L"drawBitmap::getBitmap");

		// Just return if there is nothing to show
		///////////////////////////////////////////////////////////
		if(visibleTopLeftX == visibleBottomRightX || visibleTopLeftY == visibleBottomRightY)
		{
			if(reuseMemory != 0)
			{
				reuseMemory->resize(0);
			}
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

		// Calculate the row' size, in bytes
		///////////////////////////////////////////////////////////
		imbxUint32 rowSizeBytes = ((visibleBottomRightX - visibleTopLeftX) * 3 + rowAlignBytes - 1) / rowAlignBytes;
		rowSizeBytes *= rowAlignBytes;

		// Allocate the memory for the final bitmap
		///////////////////////////////////////////////////////////
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

		imbxUint8 leftShiftX(0), leftShiftY(0);
		imbxUint32 maskX(0), maskY(0);
		while( (imageSizeX << leftShiftX) < (imbxUint32)totalWidthPixels)
		{
			++leftShiftX;
			maskX <<= 1;
			++maskX;
		}
		while( (imageSizeY << leftShiftY) < (imbxUint32)totalHeightPixels)
		{
			++leftShiftY;
			maskY <<= 1;
			++maskY;
		}

		// Allocate an horizontal buffer that stores the pixels
		//  average colors and a buffer that indicates the pixels
		//  in the source image mapped to the final bitmap
		///////////////////////////////////////////////////////////
		imbxUint32 destBitmapWidth(visibleBottomRightX - visibleTopLeftX);
		std::auto_ptr<imbxInt32> averagePixels(new imbxInt32[destBitmapWidth * 4]);
		std::auto_ptr<imbxUint32> sourcePixelIndex(new imbxUint32[destBitmapWidth + 1]);
		for(imbxInt32 scanPixelsX = visibleTopLeftX; scanPixelsX != visibleBottomRightX + 1; ++scanPixelsX)
		{
			sourcePixelIndex.get()[scanPixelsX - visibleTopLeftX] = scanPixelsX * (imageSizeX << leftShiftX) / totalWidthPixels;
		}

		// Get the index of the first and last+1 pixel to be ž
		//  displayed
		///////////////////////////////////////////////////////////
		imbxInt32 firstPixelX(sourcePixelIndex.get()[0]);
		imbxInt32 lastPixelX(sourcePixelIndex.get()[visibleBottomRightX - visibleTopLeftX]);

		// If a transform chain is active then allocate a temporary
		//  output image
		///////////////////////////////////////////////////////////
		imbxUint32 rowSize, channelSize, channelsNumber;
		ptr<image> sourceImage(m_image);
		imbxUint32 sourceHeight;
		if(m_transformsChain->isEmpty())
		{
			sourceHeight = imageSizeY;
		}
		else
		{
			sourceHeight = 65536 / (lastPixelX - firstPixelX) * 3;
			if(sourceHeight < 1)
			{
				sourceHeight = 1;
			}
			if(sourceHeight > imageSizeY)
			{
				sourceHeight = imageSizeY;
			}
			sourceImage = new image;
			sourceImage->create(lastPixelX - firstPixelX, sourceHeight, image::depthU8, L"RGB", 7);
		}

		// Retrieve the final bitmap's buffer
		///////////////////////////////////////////////////////////
		imbxUint8* pFinalBuffer = (imbxUint8*)(reuseMemory->data());
		imbxInt32 nextRowGap = rowSizeBytes - destBitmapWidth * 3;

		// First Y pixel not transformed by the transforms chain
		///////////////////////////////////////////////////////////
		imbxUint32 transformChainStartY(0); 

		imbxInt32 firstImagePixelY = visibleTopLeftY * (imageSizeY << leftShiftY) / totalHeightPixels;
		imbxInt32 lastImagePixelY = visibleBottomRightY * (imageSizeY << leftShiftY) / totalHeightPixels;

		// Scan all the final bitmap's rows
		///////////////////////////////////////////////////////////
		for(imbxInt32 scanY = visibleTopLeftY; scanY != visibleBottomRightY; ++scanY)
		{
			::memset(averagePixels.get(), 0, destBitmapWidth * 4 * sizeof(averagePixels.get()[0]));

			// Scan all the image's rows that go in the bitmap's row
			///////////////////////////////////////////////////////////
			imbxInt32 firstPixelY = scanY * (imageSizeY << leftShiftY) / totalHeightPixels;
			imbxInt32 lastPixelY = (scanY + 1) * (imageSizeY << leftShiftY) / totalHeightPixels;
			for(imbxInt32 scanImageY = firstPixelY; scanImageY != lastPixelY; /* increased in the loop */)
			{
				imbxInt32* pAveragePointer = averagePixels.get();
				imbxUint32* pNextSourceXIndex = sourcePixelIndex.get();

				imbxUint8* pImagePointer(0);
				imbxUint8* imageMemory(0);

				ptr<handlers::dataHandlerNumericBase> imageHandler;
				if(m_transformsChain->isEmpty())
				{
					imageHandler = sourceImage->getDataHandler(false, &rowSize, &channelSize, &channelsNumber);
					pImagePointer = &(imageMemory[(scanImageY >> leftShiftY) * imageSizeX * 3 + ((*pNextSourceXIndex) >> leftShiftX) * 3]);
					imageMemory = imageHandler->getMemoryBuffer();
				}
				else
				{
					imbxInt32 currentImageY = (scanImageY >> leftShiftY);
					if((currentImageY - firstImagePixelY) % sourceHeight == 0 || scanImageY == firstImagePixelY)
					{
						imbxInt32 lastTransformY(currentImageY + sourceHeight);
						if(lastTransformY > lastImagePixelY)
						{
							lastTransformY = lastImagePixelY;
						}
						m_transformsChain->runTransform(m_image, firstPixelX, currentImageY, lastPixelX - firstPixelX, lastTransformY - currentImageY, sourceImage, 0, 0);
						transformChainStartY = currentImageY;
					}
					imageHandler = sourceImage->getDataHandler(false, &rowSize, &channelSize, &channelsNumber);
					imageMemory = imageHandler->getMemoryBuffer();
					
					pImagePointer = &(imageMemory[(currentImageY - transformChainStartY) * (lastPixelX - firstPixelX) * 3]);
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

			if(drawBitmapType == drawBitmapRGB)
			{
				for(imbxInt32 scanX (destBitmapWidth); scanX != 0; --scanX)
				{
					counter = (imbxUint32)*(pAveragePointer++);
					*(pFinalBuffer++) = (imbxUint8) (((imbxUint32)*(pAveragePointer++) / counter) & 0xff);
					*(pFinalBuffer++) = (imbxUint8) (((imbxUint32)*(pAveragePointer++) / counter) & 0xff);
					*(pFinalBuffer++) = (imbxUint8) (((imbxUint32)*(pAveragePointer++) / counter) & 0xff);
				}
			}
			else
			{
				for(imbxInt32 scanX (destBitmapWidth); scanX != 0; --scanX)
				{
					counter = (imbxUint32)*(pAveragePointer++);
					imbxUint32 r = (imbxUint8) (((imbxUint32)*(pAveragePointer++) / counter) & 0xff);
					imbxUint32 g = (imbxUint8) (((imbxUint32)*(pAveragePointer++) / counter) & 0xff);
					imbxUint32 b = (imbxUint8) (((imbxUint32)*(pAveragePointer++) / counter) & 0xff);
					*(pFinalBuffer++) = (imbxUint8)b;
					*(pFinalBuffer++) = (imbxUint8)g;
					*(pFinalBuffer++) = (imbxUint8)r;
				}
			}
			pFinalBuffer += nextRowGap;
		}

        return reuseMemory;

		PUNTOEXE_FUNCTION_END();

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

