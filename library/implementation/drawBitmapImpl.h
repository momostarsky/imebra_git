/*
$fileHeader$
*/

/*! \file drawBitmap.h
    \brief Declaration of the a class that draw an image into a bitmap.

This file is not included automatically by implementation.h

*/

#if !defined(imebraDrawBitmap_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_)
#define imebraDrawBitmap_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_

#include "memoryImpl.h"
#include "transformsChainImpl.h"
#include "../include/imebra/exceptions.h"


#include <memory>
#include <string.h>

namespace imebra
{

	namespace implementation
	{

		/// \addtogroup group_helpers Helpers
		///
		/// @{

        ///////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////
        /// \brief Defines the output type of
        ///         getBitmap().
        ///
        ///////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////
        enum tDrawBitmapType
		{
            drawBitmapRGB  = 0, ///< Generates a BMP image where each pixel contains 3 bytes (R, G and B)
            drawBitmapBGR  = 1, ///< Generates a BMP image where each pixel contains 3 bytes (B, G and R)
            drawBitmapRGBA = 2, ///< Generates a BMP image where each pixel contains 4 bytes (R, G, B and A)
            drawBitmapBGRA = 3  ///< Generates a BMP image where each pixel contains 4 bytes (B, G, R and A)
		};

		///////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////
		/// \brief This class takes an image as an input and
		///         returns an 8 bit RGB bitmap of the requested
		///         image's area.
		///
		///////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////
        class drawBitmap
		{
		public:
			/// \brief Constructor.
			///
			/// @param sourceImage  the input image that has to be
			///                      rendered
			/// @param transformsChain the list of transforms to be
			///                      applied to the image before it
			///                      is rendered. Can be null.
			///                     The transformation to RGB and
			///                      high bit shift are applied
			///                      automatically by this class
			///
			///////////////////////////////////////////////////////////
			drawBitmap(std::shared_ptr<image> sourceImage, std::shared_ptr<transforms::transformsChain> transformsChain);

			/// \brief Renders the image specified in the constructor
			///         into an RGB or BGR buffer.
			///
			/// The caller can pass to the function a memory object
			///  that will be used to store the RGB/BGR buffer,
			///  otherwise the function will allocate a new one.
			///
			/// Each row of pixels in the RGB/BGR buffer will be
			///  aligned according to the template parameter
			///  rowAlignBytes
			///
			/// \image html drawbitmap.png "drawbitmap"
			/// \image latex drawbitmap.png "drawbitmap" width=15cm
			///
			/// The figure illustrates how the getBitmap() method
			///  works:
			/// -# the image is resized according to the parameters
			///        totalWidthPixels and totalHeightPixels
			/// -# the area specified by visibleTopLeftX,
			///    visibleTopLeftY - visibleBottomRightX,
			///    visibleBottomRightY is rendered into the buffer
			///
			/// Please note that the rendering algorithm achieves the
			///  described results without actually resizing the image.
			///
			/// @tparam drawBitmapType The RGB order. Must be
			///                         drawBitmapBGR for BMP images
			/// @tparam rowAlignBytes  the boundary alignment of each
			///                         row. Must be 4 for BMP images
			/// @param reuseMemory      a pointer to a memory object
			///                          that must be used to store the
			///                          output buffer. Can be null
			/// @return the memory object in which the output buffer
			///          is stored. Is the same object specified in
			///          reuseMemory or a new object if reuseMemory
			///          is null
			///
			///////////////////////////////////////////////////////////
			template <tDrawBitmapType drawBitmapType, int rowAlignBytes>
                    std::shared_ptr<memory> getBitmap(std::shared_ptr<memory> reuseMemory)
			{
				IMEBRA_FUNCTION_START(L"drawBitmap::getBitmap");

                size_t memorySize(getBitmap<drawBitmapType, rowAlignBytes>(0, 0));

				if(reuseMemory == 0)
				{
                    reuseMemory.reset(memoryPool::getMemoryPool()->getMemory(memorySize));
				}
				else
				{
					reuseMemory->resize(memorySize);
				}

				// Retrieve the final bitmap's buffer
				///////////////////////////////////////////////////////////
				std::uint8_t* pFinalBuffer = (std::uint8_t*)(reuseMemory->data());

                getBitmap<drawBitmapType, rowAlignBytes>(pFinalBuffer, memorySize);

				return reuseMemory;

				IMEBRA_FUNCTION_END();

			}

			template <tDrawBitmapType drawBitmapType, int rowAlignBytes>
                    size_t getBitmap(std::uint8_t* pBuffer, size_t bufferSize)
			{
				IMEBRA_FUNCTION_START(L"drawBitmap::getBitmapRaw");

                std::uint32_t destPixelSize((drawBitmapType == drawBitmapRGBA || drawBitmapType == drawBitmapBGRA) ? 4 : 3);

                std::uint32_t imageSizeX, imageSizeY;
                m_image->getSize(&imageSizeX, &imageSizeY);

                // Calculate the row' size, in bytes
				///////////////////////////////////////////////////////////
                std::uint32_t rowSizeBytes = (imageSizeX * destPixelSize + rowAlignBytes - 1) / rowAlignBytes;
				rowSizeBytes *= rowAlignBytes;

				// Allocate the memory for the final bitmap
				///////////////////////////////////////////////////////////
                std::uint32_t memorySize(rowSizeBytes * imageSizeY);
				if(memorySize > bufferSize)
				{
				    return memorySize;
				}

				// If a transform chain is active then allocate a temporary
				//  output image
				///////////////////////////////////////////////////////////
				std::shared_ptr<image> sourceImage(m_image);

                std::shared_ptr<handlers::readingDataHandlerNumericBase> imageHandler;

                if(m_transformsChain->isEmpty())
                {
                    imageHandler = sourceImage->getReadingDataHandler();
                }
                else
                {
                    m_transformsChain->allocateOutputImage(m_image, imageSizeX, imageSizeY);
                    imageHandler = sourceImage->getReadingDataHandler();
                }
                const std::uint8_t* pImagePointer = imageHandler->getMemoryBuffer();

                std::uint32_t nextRowGap = rowSizeBytes - imageSizeX * 3;

				// Scan all the final bitmap's rows
				///////////////////////////////////////////////////////////
                if(drawBitmapType == drawBitmapRGB)
                {
                    for(std::uint32_t scanY(imageSizeY); scanY != 0; --scanY)
                    {
                        for(std::uint32_t scanX(imageSizeX); scanX != 0; --scanX)
                        {
                            *pBuffer++ = *pImagePointer++;
                            *pBuffer++ = *pImagePointer++;
                            *pBuffer++ = *pImagePointer++;
                        }
                        pBuffer += nextRowGap;
                    }
                }
                else if(drawBitmapType == drawBitmapBGR)
                {
                    std::uint8_t r, g;
                    for(std::uint32_t scanY(imageSizeY); scanY != 0; --scanY)
                    {
                        for(std::uint32_t scanX(imageSizeX); scanX != 0; --scanX)
                        {
                            r = *pImagePointer++;
                            g = *pImagePointer++;
                            *pBuffer++ = *pImagePointer++;
                            *pBuffer++ = g;
                            *pBuffer++ = r;
                        }
                        pBuffer += nextRowGap;
                    }
                }
                else if(drawBitmapType == drawBitmapRGBA)
                {
                    for(std::uint32_t scanY(imageSizeY); scanY != 0; --scanY)
                    {
                        for(std::uint32_t scanX(imageSizeX); scanX != 0; --scanX)
                        {
                            *pBuffer++ = *pImagePointer++;
                            *pBuffer++ = *pImagePointer++;
                            *pBuffer++ = *pImagePointer++;
                            *pBuffer++ = 0xff;
                        }
                        pBuffer += nextRowGap;
                    }
                }
                else
                {
                    std::uint8_t r, g;
                    for(std::uint32_t scanY(imageSizeY); scanY != 0; --scanY)
                    {
                        for(std::uint32_t scanX(imageSizeX); scanX != 0; --scanX)
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

                }

				return memorySize;

				IMEBRA_FUNCTION_END();
			}

		protected:
			std::shared_ptr<image> m_image;

			std::shared_ptr<image> m_finalImage;

			// Transform that calculates an 8 bit per channel RGB image
			std::shared_ptr<transforms::transformsChain> m_transformsChain;
		};

		/// @}

	} // namespace implementation

} // namespace imebra

#endif // !defined(imebraDrawBitmap_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_)
