/*
$fileHeader$
*/

/*! \file dataSet.cpp
    \brief Implementation of the class dataSet.

*/

#include "exceptionImpl.h"
#include "streamReaderImpl.h"
#include "streamWriterImpl.h"
#include "memoryStreamImpl.h"
#include "dataSetImpl.h"
#include "dataHandlerNumericImpl.h"
#include "dicomDictImpl.h"
#include "codecFactoryImpl.h"
#include "codecImpl.h"
#include "imageImpl.h"
#include "LUTImpl.h"
#include "waveformImpl.h"
#include "colorTransformsFactoryImpl.h"
#include "transformsChainImpl.h"
#include "transformHighBitImpl.h"
#include "modalityVOILUTImpl.h"
#include <iostream>
#include <string.h>


namespace puntoexe
{

namespace imebra
{

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
//
// dataSet
//
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Retrieve the requested tag
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::shared_ptr<data> dataSet::getTag(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId) const
{
	PUNTOEXE_FUNCTION_START(L"dataSet::getTag");

    tGroups::const_iterator findGroup(m_groups.find(groupId));
    if(findGroup == m_groups.end())
    {
        return std::shared_ptr<data>(0);
    }

    if(findGroup->second.size() <= order)
    {
        return std::shared_ptr<data>(0);
    }

    const tTags& tagsMap = findGroup->second.at(order);
    tTags::const_iterator findTag(tagsMap.find(tagId));
    if(findTag == tagsMap.end())
    {
        return std::shared_ptr<data>(0);
    }
    return findTag->second;

	PUNTOEXE_FUNCTION_END();
}


std::shared_ptr<data> dataSet::getTagCreate(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId)
{
    PUNTOEXE_FUNCTION_START(L"dataSet::getTag");

    if(m_groups[groupId].size() <= order)
    {
        m_groups[groupId].resize(order + 1);
    }

    if(m_groups[groupId][order][tagId] == 0)
    {
        m_groups[groupId][order][tagId] = std::make_shared<data>();
    }

    return m_groups[groupId][order][tagId];

    PUNTOEXE_FUNCTION_END();
}

bool dataSet::bufferExists(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, std::uint32_t bufferId)
{
    std::shared_ptr<data> tag(getTag(groupId, order, tagId));
    return tag != 0 && tag->bufferExists(bufferId);
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Retrieve the image from the structure
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::shared_ptr<image> dataSet::getImage(std::uint32_t frameNumber) const
{
	PUNTOEXE_FUNCTION_START(L"dataSet::getImage");

	// Retrieve the transfer syntax
	///////////////////////////////////////////////////////////
    std::wstring transferSyntax = getUnicodeString(0x0002, 0x0, 0x0010, 0, 0);

	// Get the right codec
	///////////////////////////////////////////////////////////
    std::shared_ptr<codecs::codec> pCodec=codecs::codecFactory::getCodec(transferSyntax);

	// Return if the codec has not been found
	///////////////////////////////////////////////////////////
	if(pCodec == 0)
	{
        PUNTOEXE_THROW(::imebra::dataSetExceptionUnknownTransferSyntax, "None of the codecs support the specified transfer syntax");
	}

    std::shared_ptr<imebra::data> imageTag = getTag(0x7fe0, 0x0, 0x0010);
	if(imageTag == 0)
	{
        PUNTOEXE_THROW(::imebra::dataSetImageDoesntExist, "The requested image doesn't exist");
	}
	std::string imageStreamDataType = imageTag->getDataType();

	// Get the number of frames
	///////////////////////////////////////////////////////////
	std::uint32_t numberOfFrames = 1;
	if(!getDataType(0x0028, 0, 0x0008).empty())
	{
        numberOfFrames = getUnsignedLong(0x0028, 0, 0x0008, 0, 0);
	}

	if(frameNumber >= numberOfFrames)
	{
        PUNTOEXE_THROW(::imebra::dataSetImageDoesntExist, "The requested image doesn't exist");
	}

	// Placeholder for the stream containing the image
	///////////////////////////////////////////////////////////
    std::shared_ptr<streamReader> imageStream;

	// Retrieve the second item in the image's tag.
	// If the second item is present, then a multiframe
	//  image is present.
	///////////////////////////////////////////////////////////
	bool bDontNeedImagesPositions = false;
	{
		if(imageTag->getBufferSize(1) != 0)
		{
			std::uint32_t firstBufferId(0), endBufferId(0), totalLength(0);
			if(imageTag->getBufferSize(0) == 0 && numberOfFrames + 1 == imageTag->getBuffersCount())
			{
				firstBufferId = frameNumber + 1;
				endBufferId = firstBufferId + 1;
				totalLength = imageTag->getBufferSize(firstBufferId);
			}
			else
			{
				totalLength = getFrameBufferIds(frameNumber, &firstBufferId, &endBufferId);
			}
			if(firstBufferId == endBufferId - 1)
			{
				imageStream = imageTag->getStreamReader(firstBufferId);
				if(imageStream == 0)
				{
                    PUNTOEXE_THROW(::imebra::dataSetImageDoesntExist, "The requested image doesn't exist");
				}
			}
			else
			{
                std::shared_ptr<memory> temporaryMemory(memoryPool::getMemoryPool()->getMemory(totalLength));
				const std::uint8_t* pDest = temporaryMemory->data();
				for(std::uint32_t scanBuffers = firstBufferId; scanBuffers != endBufferId; ++scanBuffers)
				{
                    std::shared_ptr<handlers::readingDataHandlerRaw> bufferHandler = imageTag->getReadingDataHandlerRaw(scanBuffers);
                    const std::uint8_t* pSource = bufferHandler->getMemoryBuffer();
					::memcpy((void*)pDest, (void*)pSource, bufferHandler->getSize());
					pDest += bufferHandler->getSize();
				}
                std::shared_ptr<baseStreamReader> compositeStream(new memoryStreamReader(temporaryMemory));
                imageStream = std::shared_ptr<streamReader>(new streamReader(compositeStream));
			}
			bDontNeedImagesPositions = true;
		}
	}

	// If the image cannot be found, then probably we are
	//  handling an old dicom format.
	// Then try to read the image from the next group with
	//  id=0x7fe
	///////////////////////////////////////////////////////////
	if(imageStream == 0)
	{
		imageStream = getStreamReader(0x7fe0, (std::uint16_t)frameNumber, 0x0010, 0x0);
		bDontNeedImagesPositions = true;
	}

	// We are dealing with an old dicom format that doesn't
	//  include the image offsets and stores all the images
	//  in one buffer
	///////////////////////////////////////////////////////////
	if(imageStream == 0)
	{
		imageStream = imageTag->getStreamReader(0x0);
		if(imageStream == 0)
		{
            PUNTOEXE_THROW(::imebra::dataSetImageDoesntExist, "The requested image doesn't exist");
		}

		// Reset an internal array that keeps track of the
		//  images position
		///////////////////////////////////////////////////////////
		if(m_imagesPositions.size() != numberOfFrames)
		{
			m_imagesPositions.resize(numberOfFrames);

			for(std::uint32_t resetImagesPositions = 0; resetImagesPositions < numberOfFrames; m_imagesPositions[resetImagesPositions++] = 0)
			{}// empty loop

		}

		// Read all the images before the desidered one so we set
		//  reading position in the stream
		///////////////////////////////////////////////////////////
		for(std::uint32_t readImages = 0; readImages < frameNumber; readImages++)
		{
			std::uint32_t offsetPosition = m_imagesPositions[readImages];
			if(offsetPosition == 0)
			{
                pCodec->getImage(*this, imageStream, imageStreamDataType);
				m_imagesPositions[readImages] = imageStream->position();
				continue;
			}
			if((m_imagesPositions[readImages + 1] == 0) || (readImages == (frameNumber - 1)))
			{
				imageStream->seek(offsetPosition);
			}
		}
	}

    double pixelDistanceX = getDouble(0x0028, 0x0, 0x0030, 0, 0);
    double pixelDistanceY = getDouble(0x0028, 0x0, 0x0030, 0, 1);

    std::shared_ptr<image> pImage;
    pImage = pCodec->getImage(*this, imageStream, imageStreamDataType);

	if(!bDontNeedImagesPositions && m_imagesPositions.size() > frameNumber)
	{
		m_imagesPositions[frameNumber] = imageStream->position();
	}

	// If the image has been returned correctly, then set
	//  the image's size
	///////////////////////////////////////////////////////////
	if(pImage != 0)
	{
		std::uint32_t sizeX, sizeY;
		pImage->getSize(&sizeX, &sizeY);
		pImage->setSizeMm(pixelDistanceX*(double)sizeX, pixelDistanceY*(double)sizeY);
	}

	if(pImage->getColorSpace() == L"PALETTE COLOR")
	{
        std::shared_ptr<lut> red(new lut), green(new lut), blue(new lut);
        red->setLut(getReadingDataHandler(0x0028, 0x0, 0x1101, 0), getReadingDataHandler(0x0028, 0x0, 0x1201, 0), L"");
        green->setLut(getReadingDataHandler(0x0028, 0x0, 0x1102, 0), getReadingDataHandler(0x0028, 0x0, 0x1202, 0), L"");
        blue->setLut(getReadingDataHandler(0x0028, 0x0, 0x1103, 0), getReadingDataHandler(0x0028, 0x0, 0x1203, 0), L"");
        std::shared_ptr<palette> imagePalette(new palette(red, green, blue));
		pImage->setPalette(imagePalette);
	}

	return pImage;

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Get an image from the dataset and apply the modality
//  transform.
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::shared_ptr<image> dataSet::getModalityImage(std::uint32_t frameNumber)
{
    PUNTOEXE_FUNCTION_START(L"dataSet::getImage");

    std::shared_ptr<image> originalImage = getImage(frameNumber);

    std::shared_ptr<transforms::colorTransforms::colorTransformsFactory> colorFactory(transforms::colorTransforms::colorTransformsFactory::getColorTransformsFactory());
    if(originalImage == 0 || !colorFactory->isMonochrome(originalImage->getColorSpace()))
    {
        return originalImage;
    }

    std::shared_ptr<transforms::modalityVOILUT> modalityVOILUT(new transforms::modalityVOILUT(std::static_pointer_cast<dataSet>(shared_from_this())));

    // Convert to MONOCHROME2 if a modality transform is not present
    ////////////////////////////////////////////////////////////////
    if(modalityVOILUT->isEmpty())
    {
        std::shared_ptr<transforms::transform> monochromeColorTransform(colorFactory->getTransform(originalImage->getColorSpace(), L"MONOCHROME2"));
        if(monochromeColorTransform != 0)
        {
            std::uint32_t width, height;
            originalImage->getSize(&width, &height);
            std::shared_ptr<image> outputImage = monochromeColorTransform->allocateOutputImage(originalImage, width, height);
            monochromeColorTransform->runTransform(originalImage, 0, 0, width, height, outputImage, 0, 0);
            return outputImage;
        }

        return originalImage;
    }

    // Apply the modality VOI/LUT transform
    ///////////////////////////////////////
    std::uint32_t width, height;
    originalImage->getSize(&width, &height);
    std::shared_ptr<image> outputImage = modalityVOILUT->allocateOutputImage(originalImage, width, height);
    modalityVOILUT->runTransform(originalImage, 0, 0, width, height, outputImage, 0, 0);
    return outputImage;

    PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Insert an image into the dataset
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void dataSet::setImage(std::uint32_t frameNumber, std::shared_ptr<image> pImage, const std::wstring& transferSyntax, codecs::codec::quality quality)
{
	PUNTOEXE_FUNCTION_START(L"dataSet::setImage");

	// The group, order, tag and buffer where the image must
	//  be stored
	///////////////////////////////////////////////////////////
	std::uint16_t groupId(0x7fe0), orderId(0), tagId(0x0010);
    std::uint32_t firstBufferId(0);

	// bDontChangeAttributes is true if some images already
	//  exist in the dataset and we must save the new image
	//  using the attributes already stored
	///////////////////////////////////////////////////////////
    std::uint32_t numberOfFrames = getUnsignedLong(0x0028, 0, 0x0008, 0, 0);
	if(frameNumber != numberOfFrames)
	{
        PUNTOEXE_THROW(::imebra::dataSetExceptionWrongFrame, "The frames must be inserted in sequence");
	}
	bool bDontChangeAttributes = (numberOfFrames != 0);
	if(bDontChangeAttributes)
	{
        if(transferSyntax != getUnicodeString(0x0002, 0x0, 0x0010, 0, 0))
        {
            PUNTOEXE_THROW(::imebra::dataSetExceptionDifferentFormat, "Previous images had a different transfer syntax");
        }
	}

	// Select the right codec
	///////////////////////////////////////////////////////////
    std::shared_ptr<codecs::codec> saveCodec(codecs::codecFactory::getCodec(transferSyntax));
	if(saveCodec == 0L)
	{
        PUNTOEXE_THROW(::imebra::dataSetExceptionUnknownTransferSyntax, "None of the codec support the requested transfer syntax");
	}

	// Do we have to save the basic offset table?
	///////////////////////////////////////////////////////////
	bool bEncapsulated = saveCodec->encapsulated(transferSyntax) ||
                         (getReadingDataHandlerRaw(groupId, 0x0, tagId, 0x1) != 0);

	// Check if we are dealing with an old Dicom format...
	///////////////////////////////////////////////////////////
	std::string dataHandlerType = getDataType(0x7fe0, 0x1, 0x0010);
	if(!dataHandlerType.empty())
	{
		orderId = (std::uint16_t)frameNumber;
		bEncapsulated = false;
	}


	// Set the subsampling flags
	///////////////////////////////////////////////////////////
	bool bSubSampledX = quality > codecs::codec::high;
	bool bSubSampledY = quality > codecs::codec::medium;
	if( !transforms::colorTransforms::colorTransformsFactory::canSubsample(pImage->getColorSpace()) )
	{
		bSubSampledX = bSubSampledY = false;
	}

    image::bitDepth depth = pImage->getDepth();
    bool b2complement = (depth == image::depthS32 || depth == image::depthS16 || depth == image::depthS8);
    std::uint32_t channelsNumber = pImage->getChannelsNumber();
    std::uint8_t allocatedBits = (std::uint8_t)(saveCodec->suggestAllocatedBits(transferSyntax, pImage->getHighBit()));
    bool bInterleaved(false);
    if(getDataType(0x0028, 0, 0x0006).empty())
    {
        if(channelsNumber > 1)
        {
            bInterleaved = true;
            setUnsignedLong(0x0028, 0, 0x0006, 0, 0, 0, "US");
        }
    }
    else
    {
        bInterleaved = (getUnsignedLong(0x0028, 0x0, 0x0006, 0, 0) == 0x0);
    }

	// If the attributes cannot be changed, then check the
	//  attributes already stored in the dataset
	///////////////////////////////////////////////////////////
	if(bDontChangeAttributes)
	{
		pImage = convertImageForDataSet(pImage);
        std::wstring currentColorSpace = getUnicodeString(0x0028, 0x0, 0x0004, 0, 0);
		bSubSampledX = transforms::colorTransforms::colorTransformsFactory::isSubsampledX(currentColorSpace);
		bSubSampledY = transforms::colorTransforms::colorTransformsFactory::isSubsampledY(currentColorSpace);
        b2complement = (getUnsignedLong(0x0028, 0, 0x0103, 0, 0) != 0);
        allocatedBits = (std::uint8_t)getUnsignedLong(0x0028, 0x0, 0x0100, 0, 0);
        channelsNumber = getUnsignedLong(0x0028, 0x0, 0x0002, 0, 0);
	}

	// Select the data type OB if not already set in the
	//  dataset
	///////////////////////////////////////////////////////////
	if(dataHandlerType.empty())
	{
		if(transferSyntax == L"1.2.840.10008.1.2")
		{
			dataHandlerType = getDefaultDataType(0x7FE0, 0x0010);
		}
		else
		{
			dataHandlerType = (bEncapsulated || allocatedBits <= 8) ? "OB" : "OW";
		}
	}

	// Encapsulated mode. Check if we have the offsets table
	///////////////////////////////////////////////////////////
	if(bEncapsulated)
	{
		// We have to add the offsets buffer
		///////////////////////////////////////////////////////////
        std::shared_ptr<handlers::readingDataHandlerRaw> imageHandler0 = getReadingDataHandlerRaw(groupId, 0x0, tagId, 0x0);
        std::shared_ptr<handlers::readingDataHandlerRaw> imageHandler1 = getReadingDataHandlerRaw(groupId, 0x0, tagId, 0x1);
		if(imageHandler0 != 0L && imageHandler0->getSize() != 0 && imageHandler1 == 0L)
		{
			// The first image must be moved forward, in order to
			//  make some room for the offset table
			///////////////////////////////////////////////////////////
			dataHandlerType = imageHandler0->getDataType();
            std::shared_ptr<handlers::writingDataHandlerRaw> moveFirstImage = getWritingDataHandlerRaw(groupId, 0x0, tagId, 0x1, dataHandlerType);

			if(moveFirstImage == 0L)
			{
                PUNTOEXE_THROW(::imebra::dataSetExceptionOldFormat, "Cannot move the first image");
			}
            size_t bufferSize=imageHandler0->getSize();
			moveFirstImage->setSize(bufferSize);
			::memcpy(moveFirstImage->getMemoryBuffer(), imageHandler0->getMemoryBuffer(), bufferSize);
		}

		// An image in the first buffer already exists.
		///////////////////////////////////////////////////////////
		if(imageHandler1 != 0)
		{
			dataHandlerType = imageHandler1->getDataType();
		}

		firstBufferId = getFirstAvailFrameBufferId();
	}

	// Get a stream to save the image
	///////////////////////////////////////////////////////////
    std::shared_ptr<streamWriter> outputStream;
    std::shared_ptr<memory> uncompressedImage(new memory);
	if(bEncapsulated || frameNumber == 0)
	{
		outputStream = getStreamWriter(groupId, orderId, tagId, firstBufferId, dataHandlerType);
	}
	else
	{
        std::shared_ptr<puntoexe::memoryStreamWriter> memStream(new memoryStreamWriter(uncompressedImage));
        outputStream = std::make_shared<streamWriter>(memStream);
	}

	// Save the image in the stream
	///////////////////////////////////////////////////////////
	saveCodec->setImage(
		outputStream,
		pImage,
		transferSyntax,
		quality,
		dataHandlerType,
		allocatedBits,
		bSubSampledX, bSubSampledY,
		bInterleaved,
		b2complement);
	outputStream->flushDataBuffer();

	if(!bEncapsulated && frameNumber != 0)
	{
        std::shared_ptr<handlers::writingDataHandlerRaw> copyUncompressed(getWritingDataHandlerRaw(groupId, orderId, tagId, firstBufferId));
		copyUncompressed->setSize((frameNumber + 1) * uncompressedImage->size());
		std::uint8_t* pSource = uncompressedImage->data();
		std::uint8_t* pDest = copyUncompressed->getMemoryBuffer() + (frameNumber * uncompressedImage->size());
		::memcpy(pDest, pSource, uncompressedImage->size());
	}

	// The images' positions calculated by getImage are not
	//  valid now. They must be recalculated.
	///////////////////////////////////////////////////////////
	m_imagesPositions.clear();

	// Write the attributes in the dataset
	///////////////////////////////////////////////////////////
	if(!bDontChangeAttributes)
	{
        std::shared_ptr<handlers::writingDataHandler> dataHandlerTransferSyntax = getWritingDataHandler(0x0002, 0x0, 0x0010, 0x0);
		dataHandlerTransferSyntax->setUnicodeString(0, transferSyntax);

		std::wstring colorSpace = pImage->getColorSpace();
        setUnicodeString(0x0028, 0x0, 0x0004, 0, 0, transforms::colorTransforms::colorTransformsFactory::makeSubsampled(colorSpace, bSubSampledX, bSubSampledY));
        setUnsignedLong(0x0028, 0x0, 0x0006, 0, 0, bInterleaved ? 0 : 1);
        setUnsignedLong(0x0028, 0x0, 0x0100, 0, 0, allocatedBits);            // allocated bits
        setUnsignedLong(0x0028, 0x0, 0x0101, 0, 0, pImage->getHighBit() + 1); // stored bits
        setUnsignedLong(0x0028, 0x0, 0x0102, 0, 0, pImage->getHighBit());     // high bit
        setUnsignedLong(0x0028, 0x0, 0x0103, 0, 0, b2complement ? 1 : 0);
        setUnsignedLong(0x0028, 0x0, 0x0002, 0, 0, channelsNumber);
		std::uint32_t imageSizeX, imageSizeY;
		pImage->getSize(&imageSizeX, &imageSizeY);
        setUnsignedLong(0x0028, 0x0, 0x0011, 0, 0, imageSizeX);
        setUnsignedLong(0x0028, 0x0, 0x0010, 0, 0, imageSizeY);

		if(colorSpace == L"PALETTECOLOR")
		{
            std::shared_ptr<palette> imagePalette(pImage->getPalette());
			if(imagePalette != 0)
			{
                imagePalette->getRed()->fillHandlers(getWritingDataHandler(0x0028, 0x0, 0x1101, 0), getWritingDataHandler(0x0028, 0x0, 0x1201, 0));
                imagePalette->getGreen()->fillHandlers(getWritingDataHandler(0x0028, 0x0, 0x1102, 0), getWritingDataHandler(0x0028, 0x0, 0x1202, 0));
                imagePalette->getBlue()->fillHandlers(getWritingDataHandler(0x0028, 0x0, 0x1103, 0), getWritingDataHandler(0x0028, 0x0, 0x1203, 0));
			}

		}

		double imageSizeMmX, imageSizeMmY;
		pImage->getSizeMm(&imageSizeMmX, &imageSizeMmY);

	}

	// Update the number of frames
	///////////////////////////////////////////////////////////
	numberOfFrames = frameNumber + 1;
    setUnsignedLong(0x0028, 0, 0x0008, 0, 0, numberOfFrames );

	// Update the offsets tag with the image's offsets
	///////////////////////////////////////////////////////////
	if(!bEncapsulated)
	{
		return;
	}

	std::uint32_t calculatePosition(0);
    std::shared_ptr<data> tag(getTagCreate(groupId, 0, tagId));
	for(std::uint32_t scanBuffers = 1; scanBuffers != firstBufferId; ++scanBuffers)
	{
		calculatePosition += tag->getBufferSize(scanBuffers);
		calculatePosition += 8;
	}
    std::shared_ptr<handlers::writingDataHandlerRaw> offsetHandler(getWritingDataHandlerRaw(groupId, 0, tagId, 0, dataHandlerType));
	offsetHandler->setSize(4 * (frameNumber + 1));
	std::uint8_t* pOffsetFrame(offsetHandler->getMemoryBuffer() + (frameNumber * 4));
	*( (std::uint32_t*)pOffsetFrame  ) = calculatePosition;
	streamController::adjustEndian(pOffsetFrame, 4, streamController::lowByteEndian, 1);

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
// Get the offset, in bytes, of the specified frame
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::uint32_t dataSet::getFrameOffset(std::uint32_t frameNumber) const
{
	// Retrieve the buffer containing the offsets
	///////////////////////////////////////////////////////////
    std::shared_ptr<handlers::readingDataHandlerRaw> framesPointer = getReadingDataHandlerRaw(0x7fe0, 0x0, 0x0010, 0);
	if(framesPointer == 0)
	{
		return 0xffffffff;
	}

	// Get the offset table's size, in number of offsets
	///////////////////////////////////////////////////////////
	std::uint32_t offsetsCount = framesPointer->getSize() / sizeof(std::uint32_t);

	// If the requested frame doesn't exist then return
	//  0xffffffff (the maximum value)
	///////////////////////////////////////////////////////////
	if(frameNumber >= offsetsCount && frameNumber != 0)
	{
		return 0xffffffff;
	}

	// Return the requested offset. If the requested frame is
	//  the first and is offset is not specified, then return
	//  0 (the first position)
	///////////////////////////////////////////////////////////
    if(frameNumber < offsetsCount)
    {
        std::uint32_t* pOffsets = (std::uint32_t*)(framesPointer->getMemoryBuffer());
        std::uint32_t returnOffset(pOffsets[frameNumber]);
        streamController::adjustEndian((std::uint8_t*)&returnOffset, 4, streamController::lowByteEndian);
        return returnOffset;
	}
	return 0;
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
// Return the buffer that starts at the specified offset
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::uint32_t dataSet::getFrameBufferId(std::uint32_t offset, std::uint32_t* pLengthToBuffer) const
{
	PUNTOEXE_FUNCTION_START(L"dataSet::getFrameBufferId");

	*pLengthToBuffer = 0;

    std::shared_ptr<data> imageTag = getTag(0x7fe0, 0, 0x0010);
	if(imageTag == 0)
	{
		return 0;
	}

	// Start from the buffer n. 1 (the buffer 0 contains
	//  the offset table
	///////////////////////////////////////////////////////////
	std::uint32_t scanBuffers(1);

	if(offset == 0xffffffff)
	{
		while(imageTag->bufferExists(scanBuffers))
		{
			++scanBuffers;
		}
		return scanBuffers;
	}

	while(offset != 0)
	{
		// If the handler isn't connected to any buffer, then
		//  the buffer doesn't exist: return
		///////////////////////////////////////////////////////////
		if(!imageTag->bufferExists(scanBuffers))
		{
			break;
		}

		// Calculate the total size of the buffer, including
		//  its descriptor (tag group and id and length)
		///////////////////////////////////////////////////////////
		std::uint32_t bufferSize = imageTag->getBufferSize(scanBuffers);;
		(*pLengthToBuffer) += bufferSize; // Increase the total size
		bufferSize += 4; // one WORD for the group id, one WORD for the tag id
		bufferSize += 4; // one DWORD for the tag length
		if(bufferSize > offset)
		{
            PUNTOEXE_THROW(::imebra::dataSetImageDoesntExist, "Image not in the offset table");
		}
		offset -= bufferSize;
		++scanBuffers;
	}

	if(offset != 0)
	{
        PUNTOEXE_THROW(::imebra::dataSetCorruptedOffsetTable, "The basic offset table is corrupted");
	}

	return scanBuffers;

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Get the first buffer and the end buffer occupied by an
//  image
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::uint32_t dataSet::getFrameBufferIds(std::uint32_t frameNumber, std::uint32_t* pFirstBuffer, std::uint32_t* pEndBuffer) const
{
	PUNTOEXE_FUNCTION_START(L"dataSet::getFrameBufferIds");

	std::uint32_t startOffset = getFrameOffset(frameNumber);
	std::uint32_t endOffset = getFrameOffset(frameNumber + 1);

	if(startOffset == 0xffffffff)
	{
        PUNTOEXE_THROW(::imebra::dataSetImageDoesntExist, "Image not in the table offset");
	}

	std::uint32_t startLength, endLength;
	*pFirstBuffer = getFrameBufferId(startOffset, &startLength);
	*pEndBuffer = getFrameBufferId(endOffset, &endLength);

    std::shared_ptr<data> imageTag = getTag(0x7fe0, 0, 0x0010);
	if(imageTag == 0)
	{
		return 0;
	}
	std::uint32_t totalSize(0);
	for(std::uint32_t scanBuffers(*pFirstBuffer); scanBuffers != *pEndBuffer; ++scanBuffers)
	{
		totalSize += imageTag->getBufferSize(scanBuffers);
	}
	return totalSize;

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Return the id of the first available buffer that can
//  be used to store a new frame
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::uint32_t dataSet::getFirstAvailFrameBufferId() const
{
	PUNTOEXE_FUNCTION_START(L"dataSet::getFirstAvailFrameBufferId");

    std::shared_ptr<data> imageTag = getTag(0x7fe0, 0, 0x0010);
	if(imageTag == 0)
	{
		return 1;
	}

	std::uint32_t availableId(1);
	while(imageTag->bufferExists(availableId))
	{
		++availableId;
	}

	return availableId;

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Converts an image using the attributes specified in
//  the dataset.
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::shared_ptr<image> dataSet::convertImageForDataSet(std::shared_ptr<image> sourceImage)
{
	PUNTOEXE_FUNCTION_START(L"dataSet::convertImageForDataSet");

	std::uint32_t imageWidth, imageHeight;
	sourceImage->getSize(&imageWidth, &imageHeight);

	std::wstring colorSpace = sourceImage->getColorSpace();
	std::uint32_t highBit = sourceImage->getHighBit();

    std::uint32_t currentWidth  = getUnsignedLong(0x0028, 0x0, 0x0011, 0, 0);
    std::uint32_t currentHeight = getUnsignedLong(0x0028, 0x0, 0x0010, 0, 0);
    std::uint32_t currentHighBit = getUnsignedLong(0x0028, 0x0, 0x0102, 0, 0);





    std::wstring currentColorSpace = transforms::colorTransforms::colorTransformsFactory::normalizeColorSpace(getUnicodeString(0x0028, 0x0, 0x0004, 0, 0));

	if(currentWidth != imageWidth || currentHeight != imageHeight)
	{
        PUNTOEXE_THROW(::imebra::dataSetExceptionDifferentFormat, "The dataset already contains an image with a different size");
	}

	if(currentHighBit < highBit)
	{
        PUNTOEXE_THROW(::imebra::dataSetExceptionDifferentFormat, "The high bit in the dataset is smaller than the requested one");
	}

	if( !transforms::colorTransforms::colorTransformsFactory::isMonochrome(colorSpace) && colorSpace != currentColorSpace)
	{
        PUNTOEXE_THROW(::imebra::dataSetExceptionDifferentFormat, "The requested color space doesn't match the one already stored in the dataset");
	}

    std::shared_ptr<transforms::transformsChain> chain(new transforms::transformsChain);
	if(colorSpace != currentColorSpace)
	{
        std::shared_ptr<transforms::colorTransforms::colorTransformsFactory> pColorFactory(transforms::colorTransforms::colorTransformsFactory::getColorTransformsFactory());
        std::shared_ptr<transforms::transform> colorChain = pColorFactory->getTransform(colorSpace, currentColorSpace);
		if(colorChain->isEmpty())
		{
            PUNTOEXE_THROW(::imebra::dataSetExceptionDifferentFormat, "The image color space cannot be converted to the dataset color space");
		}
		chain->addTransform(colorChain);
	}

	if(currentHighBit != highBit)
	{
        chain->addTransform(std::make_shared<transforms::transformHighBit>());
	}

	if(chain->isEmpty())
	{
		return sourceImage;
	}

    std::shared_ptr<image> destImage(new image);
    bool b2Complement(getUnsignedLong(0x0028, 0x0, 0x0103, 0, 0)!=0x0);
	image::bitDepth depth;
	if(b2Complement)
		depth=highBit>=8 ? image::depthS16 : image::depthS8;
	else
		depth=highBit>=8 ? image::depthU16 : image::depthU8;
	destImage->create(currentWidth, currentHeight, depth, currentColorSpace, currentHighBit);

	chain->runTransform(sourceImage, 0, 0, imageWidth, imageHeight, destImage, 0, 0);

	return destImage;

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Retrieve a sequence item as a dataset
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::shared_ptr<dataSet> dataSet::getSequenceItem(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t itemId)
{
	PUNTOEXE_FUNCTION_START(L"dataSet::getSequenceItem");

    std::shared_ptr<data> tag = getTag(groupId, order, tagId);
    std::shared_ptr<dataSet> pDataSet;
	if(tag != 0)
	{
		pDataSet = tag->getDataSet(itemId);
	}

	return pDataSet;

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Retrieve a LUT from the data set
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::shared_ptr<lut> dataSet::getLut(std::uint16_t groupId, std::uint16_t tagId, std::uint32_t lutId)
{
	PUNTOEXE_FUNCTION_START(L"dataSet::getLut");

    std::shared_ptr<lut> pLUT;
    std::shared_ptr<dataSet> embeddedLUT = getSequenceItem(groupId, 0, tagId, lutId);
	std::string tagType = getDataType(groupId, 0, tagId);
	if(embeddedLUT != 0)
	{
        std::shared_ptr<lut> tempLut(new lut);
		pLUT = tempLut;
        std::shared_ptr<handlers::readingDataHandler> descriptorHandle = embeddedLUT->getReadingDataHandler(0x0028, 0x0, 0x3002, 0x0);
        std::shared_ptr<handlers::readingDataHandler> dataHandle = embeddedLUT->getReadingDataHandler(0x0028, 0x0, 0x3006, 0x0);

		pLUT->setLut(
			descriptorHandle,
			dataHandle,
            embeddedLUT->getUnicodeString(0x0028, 0x0, 0x3003, 0, 0));
	}
	return pLUT;

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Retrieve a waveform
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::shared_ptr<waveform> dataSet::getWaveform(std::uint32_t waveformId)
{
	PUNTOEXE_FUNCTION_START(L"dataSet::getWaveform");

    std::shared_ptr<dataSet> embeddedWaveform(getSequenceItem(0x5400, 0, 0x0100, waveformId));
	if(embeddedWaveform == 0)
	{
		return 0;
	}

    return std::make_shared<waveform>(embeddedWaveform);

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Get a tag as a signed long
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::int32_t dataSet::getSignedLong(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber) const
{
	PUNTOEXE_FUNCTION_START(L"dataSet::getSignedLong");

    std::shared_ptr<handlers::readingDataHandler> dataHandler = getReadingDataHandler(groupId, order, tagId, bufferId);
	if(dataHandler == 0)
	{
		return 0;
	}

    return dataHandler->getSignedLong(elementNumber);

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Set a tag as a signed long
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void dataSet::setSignedLong(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber, std::int32_t newValue, const std::string& defaultType /* = "" */)
{
	PUNTOEXE_FUNCTION_START(L"dataSet::setSignedLong");

    std::shared_ptr<handlers::writingDataHandler> dataHandler = getWritingDataHandler(groupId, order, tagId, bufferId, defaultType);
	if(dataHandler != 0)
	{
        if(dataHandler->getSize() <= elementNumber)
		{
			dataHandler->setSize(elementNumber + 1);
		}
		dataHandler->setSignedLong(elementNumber, newValue);
	}

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Get the requested tag as an unsigned long
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::uint32_t dataSet::getUnsignedLong(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber) const
{
	PUNTOEXE_FUNCTION_START(L"dataSet::getUnignedLong");

    std::shared_ptr<handlers::readingDataHandler> dataHandler = getReadingDataHandler(groupId, order, tagId, bufferId);
	if(dataHandler == 0)
	{
		return 0;
	}

    return dataHandler->getUnsignedLong(elementNumber);

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Set the requested tag as an unsigned long
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void dataSet::setUnsignedLong(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber, std::uint32_t newValue, const std::string& defaultType /* = "" */)
{
	PUNTOEXE_FUNCTION_START(L"dataSet::setUnsignedLong");

    std::shared_ptr<handlers::writingDataHandler> dataHandler = getWritingDataHandler(groupId, order, tagId, bufferId, defaultType);
	if(dataHandler != 0)
	{
		if(dataHandler->getSize() <= elementNumber)
		{
			dataHandler->setSize(elementNumber + 1);
		}
		dataHandler->setUnsignedLong(elementNumber, newValue);
	}

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Get the requested tag as a double
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
double dataSet::getDouble(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber) const
{
	PUNTOEXE_FUNCTION_START(L"dataSet::getDouble");

    std::shared_ptr<handlers::readingDataHandler> dataHandler = getReadingDataHandler(groupId, order, tagId, bufferId);
	if(dataHandler == 0)
	{
		return 0.0;
	}

    return dataHandler->getDouble(elementNumber);

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Set the requested tag as a double
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void dataSet::setDouble(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber, double newValue, const std::string& defaultType /* = "" */)
{
	PUNTOEXE_FUNCTION_START(L"dataSet::setDouble");

    std::shared_ptr<handlers::writingDataHandler> dataHandler = getWritingDataHandler(groupId, order, tagId, bufferId, defaultType);
	if(dataHandler != 0)
	{
		if(dataHandler->getSize() <= elementNumber)
		{
			dataHandler->setSize(elementNumber + 1);
		}
		dataHandler->setDouble(elementNumber, newValue);
	}

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Get the requested tag as a string
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::string dataSet::getString(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber) const
{
	PUNTOEXE_FUNCTION_START(L"dataSet::getString");

    std::shared_ptr<handlers::readingDataHandler> dataHandler = getReadingDataHandler(groupId, order, tagId, bufferId);
	std::string returnValue;
	if(dataHandler != 0)
	{
        returnValue = dataHandler->getString(elementNumber);
	}

	return returnValue;

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Get the requested tag as an unicode string
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::wstring dataSet::getUnicodeString(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber) const
{
	PUNTOEXE_FUNCTION_START(L"dataSet::getUnicodeString");

    std::shared_ptr<handlers::readingDataHandler> dataHandler = getReadingDataHandler(groupId, order, tagId, bufferId);
	std::wstring returnValue;
	if(dataHandler != 0)
	{
        returnValue = dataHandler->getUnicodeString(elementNumber);
    }

	return returnValue;

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Set the requested tag as a string
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void dataSet::setString(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber, const std::string& newString, const std::string& defaultType /* = "" */)
{
	PUNTOEXE_FUNCTION_START(L"dataSet::setString");

    std::shared_ptr<handlers::writingDataHandler> dataHandler = getWritingDataHandler(groupId, order, tagId, bufferId, defaultType);
	if(dataHandler != 0)
	{
		if(dataHandler->getSize() <= elementNumber)
		{
			dataHandler->setSize(elementNumber + 1);
		}
		dataHandler->setString(elementNumber, newString);
	}

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Set the requested tag as a string
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void dataSet::setUnicodeString(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber, const std::wstring& newString, const std::string& defaultType /* = "" */)
{
	PUNTOEXE_FUNCTION_START(L"dataSet::setUnicodeString");

    std::shared_ptr<handlers::writingDataHandler> dataHandler = getWritingDataHandler(groupId, order, tagId, bufferId, defaultType);
	if(dataHandler != 0)
	{
		if(dataHandler->getSize() <= elementNumber)
		{
			dataHandler->setSize(elementNumber + 1);
		}
		dataHandler->setUnicodeString(elementNumber, newString);
	}

	PUNTOEXE_FUNCTION_END();
}

void dataSet::setAge(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber, int age, ::imebra::ageUnit_t units, const std::string& defaultType /* = "" */)
{
    PUNTOEXE_FUNCTION_START(L"dataSet::setAge");

    std::shared_ptr<handlers::writingDataHandler> dataHandler = getWritingDataHandler(groupId, order, tagId, bufferId, defaultType);
    if(dataHandler != 0)
    {
        if(dataHandler->getSize() <= elementNumber)
        {
            dataHandler->setSize(elementNumber + 1);
        }
        dataHandler->setAge(elementNumber, age, units);
    }

    PUNTOEXE_FUNCTION_END();
}

int dataSet::getAge(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber, ::imebra::ageUnit_t* pUnits) const
{
    PUNTOEXE_FUNCTION_START(L"dataSet::getAge");

    std::shared_ptr<handlers::readingDataHandler> dataHandler = getReadingDataHandler(groupId, order, tagId, bufferId);
    if(dataHandler != 0)
    {
        return dataHandler->getAge(elementNumber, pUnits);
    }

    *pUnits = ::imebra::ageUnit_t::years;
    return 0;

    PUNTOEXE_FUNCTION_END();

}



///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Get a data handler for the requested tag
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::shared_ptr<handlers::readingDataHandler> dataSet::getReadingDataHandler(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId) const
{
	PUNTOEXE_FUNCTION_START(L"dataSet::getDataHandler");

    std::shared_ptr<data> tag(getTag(groupId, order, tagId));

    if(tag == 0)
	{
        std::shared_ptr<handlers::readingDataHandler> pDataHandler;
        return pDataHandler;
	}

    return tag->getReadingDataHandler(bufferId);

	PUNTOEXE_FUNCTION_END();
}


std::shared_ptr<handlers::writingDataHandler> dataSet::getWritingDataHandler(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, const std::string& defaultType /* ="" */)
{
    PUNTOEXE_FUNCTION_START(L"dataSet::getDataHandler");

    std::shared_ptr<data> tag(getTagCreate(groupId, order, tagId));

    if(defaultType.length()!=2L)
    {
        return tag->getWritingDataHandler(bufferId, getDefaultDataType(groupId, tagId), m_charsetsList);
    }

    return tag->getWritingDataHandler(bufferId, defaultType, m_charsetsList);

    PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Get a stream reader that works on the specified tag
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::shared_ptr<streamReader> dataSet::getStreamReader(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId) const
{
	PUNTOEXE_FUNCTION_START(L"dataSet::getStream");

    std::shared_ptr<data> tag (getTag(groupId, order, tagId));

    return tag->getStreamReader(bufferId);

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Retrieve a stream writer for the specified tag
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::shared_ptr<streamWriter> dataSet::getStreamWriter(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, const std::string& dataType /* = "" */)
{
	PUNTOEXE_FUNCTION_START(L"dataSet::getStream");

    std::shared_ptr<data> tag = getTagCreate(groupId, order, tagId);

    std::shared_ptr<streamWriter> returnStream;

    if(tag != 0)
	{
        returnStream = tag->getStreamWriter(bufferId, dataType);
	}

	return returnStream;

	PUNTOEXE_FUNCTION_END();
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Get a raw data handler for the requested tag
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::shared_ptr<handlers::readingDataHandlerRaw> dataSet::getReadingDataHandlerRaw(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId) const
{
	PUNTOEXE_FUNCTION_START(L"dataSet::getDataHandlerRaw");

    std::shared_ptr<data> tag = getTag(groupId, order, tagId);

    if(tag == 0)
	{
        std::shared_ptr<handlers::readingDataHandlerRaw> emptyDataHandler;
		return emptyDataHandler;
	}

    return tag->getReadingDataHandlerRaw(bufferId);

	PUNTOEXE_FUNCTION_END();
}


std::shared_ptr<handlers::writingDataHandlerRaw> dataSet::getWritingDataHandlerRaw(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, const std::string& defaultType /* ="" */)
{
    PUNTOEXE_FUNCTION_START(L"dataSet::getDataHandlerRaw");

    std::shared_ptr<data> tag = getTagCreate(groupId, order, tagId);

    if(defaultType.length()!=2)
    {
        return tag->getWritingDataHandlerRaw(bufferId, getDefaultDataType(groupId, tagId), m_charsetsList);
    }

    return tag->getWritingDataHandlerRaw(bufferId, defaultType, m_charsetsList);

    PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Retrieve the requested tag's default data type
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::string dataSet::getDefaultDataType(std::uint16_t groupId, std::uint16_t tagId) const
{
	PUNTOEXE_FUNCTION_START(L"dataSet::getDefaultDataType");

	return dicomDictionary::getDicomDictionary()->getTagType(groupId, tagId);

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Get the data type of a tag
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::string dataSet::getDataType(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId) const
{
	PUNTOEXE_FUNCTION_START(L"dataSet::getDataType");

	std::string bufferType;

    std::shared_ptr<data> tag = getTag(groupId, order, tagId);
	if(tag != 0)
	{
		bufferType = tag->getDataType();
	}
	return bufferType;

	PUNTOEXE_FUNCTION_END();
}

void dataSet::updateCharsetTag()
{
	charsetsList::tCharsetsList charsets;
	getCharsetsList(&charsets);
    std::shared_ptr<handlers::writingDataHandler> charsetHandler(getWritingDataHandler(0x0008, 0, 0x0005, 0));
	charsetHandler->setSize((std::uint32_t)(charsets.size()));
	std::uint32_t pointer(0);
	for(charsetsList::tCharsetsList::iterator scanCharsets = charsets.begin(); scanCharsets != charsets.end(); ++scanCharsets)
	{
        charsetHandler->setString(pointer++, *scanCharsets);
	}
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Update the list of the used charsets
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void dataSet::updateTagsCharset()
{
	charsetsList::tCharsetsList charsets;
    std::shared_ptr<handlers::readingDataHandler> charsetHandler(getReadingDataHandler(0x0008, 0, 0x0005, 0));
	if(charsetHandler != 0)
	{
        for(std::uint32_t pointer(0); pointer != charsetHandler->getSize(); ++pointer)
		{
            charsets.push_back(charsetHandler->getString(pointer));
		}
	}
    setCharsetsList(charsets);
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Set the item's position in the stream
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void dataSet::setItemOffset(std::uint32_t offset)
{
	m_itemOffset = offset;
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Get the item's position in the stream
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::uint32_t dataSet::getItemOffset() const
{
	return m_itemOffset;
}

void dataSet::getCharsetsList(charsetsList::tCharsetsList* pCharsetsList) const
{
    for(tGroups::const_iterator scanGroups(m_groups.begin()), endGroups(m_groups.end()); scanGroups != endGroups; ++scanGroups)
    {
        for(tGroupsList::const_iterator scanGroupsList(scanGroups->second.begin()), endGroupsList(scanGroups->second.end()); scanGroupsList != endGroupsList; ++scanGroupsList)
        {
            for(tTags::const_iterator scanTags((*scanGroupsList).begin()), endTags((*scanGroupsList).end()); scanTags != endTags; ++scanTags)
            {
                charsetsList::tCharsetsList charsets;
                scanTags->second->getCharsetsList(&charsets);
                charsetsList::updateCharsets(&charsets, pCharsetsList);

            }
        }
    }
}

dataSet::tGroupsIds dataSet::getGroups() const
{
    dataSet::tGroupsIds groups;

    for(tGroups::const_iterator scanGroups(m_groups.begin()), endGroups(m_groups.end()); scanGroups != endGroups; ++scanGroups)
    {
        groups.insert(scanGroups->first);
    }

    return groups;
}

size_t dataSet::getGroupsNumber(uint16_t groupId) const
{
    dataSet::tGroups::const_iterator findGroup(m_groups.find(groupId));

    if(findGroup == m_groups.end())
    {
        return 0;
    }

    return findGroup->second.size();

}

const dataSet::tTags& dataSet::getGroupTags(std::uint16_t groupId, size_t groupOrder) const
{
    static const dataSet::tTags emptyTags;

    tGroups::const_iterator findGroup(m_groups.find(groupId));
    if(findGroup == m_groups.end() || findGroup->second.size() <= groupOrder)
    {
        return emptyTags;
    }

    return findGroup->second.at(groupOrder);

}

void dataSet::setCharsetsList(const charsetsList::tCharsetsList& charsetsList)
{
    m_charsetsList = charsetsList;
    for(tGroups::iterator scanGroups(m_groups.begin()), endGroups(m_groups.end()); scanGroups != endGroups; ++scanGroups)
    {
        for(tGroupsList::iterator scanGroupsList(scanGroups->second.begin()), endGroupsList(scanGroups->second.end()); scanGroupsList != endGroupsList; ++scanGroupsList)
        {
            for(tTags::iterator scanTags((*scanGroupsList).begin()), endTags((*scanGroupsList).end()); scanTags != endTags; ++scanTags)
            {
                scanTags->second->setCharsetsList(charsetsList);
            }
        }
    }
}

} // namespace imebra

} // namespace puntoexe
