/*
$fileHeader$
*/

/*! \file dataSet.cpp
    \brief Implementation of the class dataSet.

*/
#define NOMINMAX

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


namespace imebra
{

namespace implementation
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
std::shared_ptr<data> dataSet::getTagThrow(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId) const
{
    IMEBRA_FUNCTION_START();

    tGroups::const_iterator findGroup(m_groups.find(groupId));
    if(findGroup == m_groups.end())
    {
        throw MissingGroupError("The requested group is missing");
    }

    if(findGroup->second.size() <= order)
    {
        throw MissingGroupError("The requested group is missing");
    }

    const tTags& tagsMap = findGroup->second.at(order);
    tTags::const_iterator findTag(tagsMap.find(tagId));
    if(findTag == tagsMap.end())
    {
        throw MissingGroupError("The requested tag is missing");
    }
    return findTag->second;

	IMEBRA_FUNCTION_END();
}


std::shared_ptr<data> dataSet::getTagCreate(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId)
{
    IMEBRA_FUNCTION_START();

    if(m_groups[groupId].size() <= order)
    {
        m_groups[groupId].resize(order + 1);
    }

    if(m_groups[groupId][order][tagId] == 0)
    {
        m_groups[groupId][order][tagId] = std::make_shared<data>();
    }

    return m_groups[groupId][order][tagId];

    IMEBRA_FUNCTION_END();
}

bool dataSet::bufferExists(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId) const
{
    try
    {
        std::shared_ptr<data> tag(getTagThrow(groupId, order, tagId));
        return tag != 0 && tag->bufferExists(bufferId);
    }
    catch(const MissingDataElementError&)
    {
        return false;
    }
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
    IMEBRA_FUNCTION_START();

	// Retrieve the transfer syntax
	///////////////////////////////////////////////////////////
    std::string transferSyntax = getStringThrow(0x0002, 0x0, 0x0010, 0, 0);

	// Get the right codec
	///////////////////////////////////////////////////////////
    std::shared_ptr<codecs::codec> pCodec=codecs::codecFactory::getCodec(transferSyntax);

    try
    {
        std::shared_ptr<implementation::data> imageTag = getTagThrow(0x7fe0, 0x0, 0x0010);

        const std::string imageStreamDataType(imageTag->getDataTypeThrow(0));

        // Get the number of frames
        ///////////////////////////////////////////////////////////
        std::uint32_t numberOfFrames = getUnsignedLong(0x0028, 0, 0x0008, 0, 0, 1);

        if(frameNumber >= numberOfFrames)
        {
            IMEBRA_THROW(DataSetImageDoesntExistError, "The requested image doesn't exist");
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
            if(imageTag->bufferExists(1))
            {
                std::uint32_t firstBufferId(0), endBufferId(0);
                size_t totalLength(0);
                if(imageTag->getBufferSizeThrow(0) == 0 && numberOfFrames + 1 == imageTag->getBuffersCount())
                {
                    firstBufferId = frameNumber + 1;
                    endBufferId = firstBufferId + 1;
                    totalLength = imageTag->getBufferSizeThrow(firstBufferId);
                }
                else
                {
                    totalLength = getFrameBufferIds(frameNumber, &firstBufferId, &endBufferId);
                }
                if(firstBufferId == endBufferId - 1)
                {
                    imageStream = imageTag->getStreamReaderThrow(firstBufferId);
                }
                else
                {
                    std::shared_ptr<memory> temporaryMemory(memoryPool::getMemoryPool()->getMemory(totalLength));
                    const std::uint8_t* pDest = temporaryMemory->data();
                    for(std::uint32_t scanBuffers = firstBufferId; scanBuffers != endBufferId; ++scanBuffers)
                    {
                        std::shared_ptr<handlers::readingDataHandlerRaw> bufferHandler = imageTag->getReadingDataHandlerRawThrow(scanBuffers);
                        const std::uint8_t* pSource = bufferHandler->getMemoryBuffer();
                        ::memcpy((void*)pDest, (void*)pSource, bufferHandler->getSize());
                        pDest += bufferHandler->getSize();
                    }
                    std::shared_ptr<baseStreamInput> compositeStream(std::make_shared<memoryStreamInput>(temporaryMemory));
                    imageStream = std::make_shared<streamReader>(compositeStream);
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
            try
            {
                imageStream = getStreamReaderThrow(0x7fe0, (std::uint16_t)frameNumber, 0x0010, 0x0);
                bDontNeedImagesPositions = true;
            }
            catch(const MissingDataElementError&)
            {
                // Nothing to do
            }
        }

        // We are dealing with an old dicom format that doesn't
        //  include the image offsets and stores all the images
        //  in one buffer
        ///////////////////////////////////////////////////////////
        if(imageStream == 0)
        {
            imageStream = imageTag->getStreamReaderThrow(0x0);

            // Reset an internal array that keeps track of the
            //  images position
            ///////////////////////////////////////////////////////////
            if(m_imagesPositions.size() != numberOfFrames)
            {
                m_imagesPositions.resize(numberOfFrames);

                for(std::uint32_t resetImagesPositions = 0; resetImagesPositions != numberOfFrames; ++resetImagesPositions)
                {
                    m_imagesPositions[resetImagesPositions] = 0;
                }

            }

            // Read all the images before the desidered one so we set
            //  reading position in the stream
            ///////////////////////////////////////////////////////////
            for(std::uint32_t readImages = 0; readImages < frameNumber; readImages++)
            {
                size_t offsetPosition = m_imagesPositions[readImages];
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

        double pixelDistanceX = getDouble(0x0028, 0x0, 0x0030, 0, 0, 1);
        double pixelDistanceY = getDouble(0x0028, 0x0, 0x0030, 0, 1, 1);

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

        if(pImage->getColorSpace() == "PALETTE COLOR")
        {
            std::shared_ptr<lut> red(std::make_shared<lut>()), green(std::make_shared<lut>()), blue(std::make_shared<lut>());
            red->setLut(getReadingDataHandlerThrow(0x0028, 0x0, 0x1101, 0), getReadingDataHandlerThrow(0x0028, 0x0, 0x1201, 0), L"");
            green->setLut(getReadingDataHandlerThrow(0x0028, 0x0, 0x1102, 0), getReadingDataHandlerThrow(0x0028, 0x0, 0x1202, 0), L"");
            blue->setLut(getReadingDataHandlerThrow(0x0028, 0x0, 0x1103, 0), getReadingDataHandlerThrow(0x0028, 0x0, 0x1203, 0), L"");
            std::shared_ptr<palette> imagePalette(std::make_shared<palette>(red, green, blue));
            pImage->setPalette(imagePalette);
        }

        return pImage;
    }
    catch(const MissingDataElementError&)
    {
        IMEBRA_THROW(DataSetImageDoesntExistError, "The requested image doesn't exist");
    }

	IMEBRA_FUNCTION_END();
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
std::shared_ptr<image> dataSet::getModalityImage(std::uint32_t frameNumber) const
{
    IMEBRA_FUNCTION_START();

    std::shared_ptr<image> originalImage = getImage(frameNumber);

    std::shared_ptr<transforms::colorTransforms::colorTransformsFactory> colorFactory(transforms::colorTransforms::colorTransformsFactory::getColorTransformsFactory());
    if(originalImage == 0 || !colorFactory->isMonochrome(originalImage->getColorSpace()))
    {
        return originalImage;
    }

    std::shared_ptr<transforms::modalityVOILUT> modalityVOILUT(std::make_shared<transforms::modalityVOILUT>(std::static_pointer_cast<const dataSet>(shared_from_this())));

    // Convert to MONOCHROME2 if a modality transform is not present
    ////////////////////////////////////////////////////////////////
    if(modalityVOILUT->isEmpty())
    {
        std::shared_ptr<transforms::transform> monochromeColorTransform(colorFactory->getTransform(originalImage->getColorSpace(), "MONOCHROME2"));
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

    IMEBRA_FUNCTION_END();
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
void dataSet::setImage(std::uint32_t frameNumber, std::shared_ptr<image> pImage, const std::string& transferSyntax, codecs::codec::quality quality)
{
    IMEBRA_FUNCTION_START();

	// The group, order, tag and buffer where the image must
	//  be stored
	///////////////////////////////////////////////////////////
    std::uint16_t groupId(0x7fe0), tagId(0x0010);
    std::uint32_t firstBufferId(0);

	// bDontChangeAttributes is true if some images already
	//  exist in the dataset and we must save the new image
	//  using the attributes already stored
	///////////////////////////////////////////////////////////
    std::uint32_t numberOfFrames = getUnsignedLong(0x0028, 0, 0x0008, 0, 0, 0);
	if(frameNumber != numberOfFrames)
	{
        IMEBRA_THROW(DataSetWrongFrameError, "The frames must be inserted in sequence");
	}
	bool bDontChangeAttributes = (numberOfFrames != 0);
	if(bDontChangeAttributes)
	{
        if(transferSyntax != getStringThrow(0x0002, 0x0, 0x0010, 0, 0))
        {
            IMEBRA_THROW(DataSetDifferentFormatError, "Previous images had a different transfer syntax");
        }
	}

	// Select the right codec
	///////////////////////////////////////////////////////////
    std::shared_ptr<codecs::codec> saveCodec(codecs::codecFactory::getCodec(transferSyntax));

	// Do we have to save the basic offset table?
	///////////////////////////////////////////////////////////
    bool bEncapsulated = saveCodec->encapsulated(transferSyntax) || bufferExists(groupId, 0x0, tagId, 0x1);

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
    bool bInterleaved = (getUnsignedLong(0x0028, 0x0, 0x0006, 0, 0, channelsNumber > 1 ? 0 : 1) == 0x0);
    setUnsignedLong(0x0028, 0, 0x0006, 0, 0, bInterleaved ? 0 : 1);

	// If the attributes cannot be changed, then check the
	//  attributes already stored in the dataset
	///////////////////////////////////////////////////////////
	if(bDontChangeAttributes)
	{
        std::string currentColorSpace = getStringThrow(0x0028, 0x0, 0x0004, 0, 0);
        if(
                transforms::colorTransforms::colorTransformsFactory::normalizeColorSpace(pImage->getColorSpace()) !=
                    transforms::colorTransforms::colorTransformsFactory::normalizeColorSpace(currentColorSpace) ||
                bSubSampledX != transforms::colorTransforms::colorTransformsFactory::isSubsampledX(currentColorSpace) ||
                bSubSampledY != transforms::colorTransforms::colorTransformsFactory::isSubsampledY(currentColorSpace) ||
                b2complement != (getUnsignedLongThrow(0x0028, 0, 0x0103, 0, 0) != 0) ||
                allocatedBits != (std::uint8_t)getUnsignedLongThrow(0x0028, 0x0, 0x0100, 0, 0) ||
                channelsNumber != getUnsignedLongThrow(0x0028, 0x0, 0x0002, 0, 0))
        {
            IMEBRA_THROW(DataSetDifferentFormatError, "An image already exists in the dataset and has different attributes");
        }
	}

	// Select the data type OB if not already set in the
	//  dataset
	///////////////////////////////////////////////////////////
    std::string dataHandlerType;
    if(transferSyntax == "1.2.840.10008.1.2")
    {
        dataHandlerType = getDefaultDataType(0x7FE0, 0x0010);
    }
    else
    {
        dataHandlerType = (bEncapsulated || allocatedBits <= 8) ? "OB" : "OW";
    }

	// Encapsulated mode. Check if we have the offsets table
	///////////////////////////////////////////////////////////
	if(bEncapsulated)
	{
        try
        {
            if(bufferExists(groupId, 0x0, tagId, 0x1))
            {
                dataHandlerType = getDataTypeThrow(groupId, 0x0, tagId, 0x1);
            }
            else
            {
                std::shared_ptr<handlers::readingDataHandlerRaw> imageHandler0 = getReadingDataHandlerRawThrow(groupId, 0x0, tagId, 0x0);
                size_t bufferSize(imageHandler0->getSize());

                if(bufferSize != 0 && !bufferExists(groupId, 0x0, tagId, 0x1))
                {
                    // The first image must be moved forward, in order to
                    //  make some room for the offset table
                    ///////////////////////////////////////////////////////////
                    dataHandlerType = imageHandler0->getDataType();
                    std::shared_ptr<handlers::writingDataHandlerRaw> moveFirstImage = getWritingDataHandlerRaw(groupId, 0x0, tagId, 0x1, dataHandlerType);
                    moveFirstImage->setSize(bufferSize);
                    ::memcpy(moveFirstImage->getMemoryBuffer(), imageHandler0->getMemoryBuffer(), bufferSize);
                }
            }
        }
        catch(const MissingDataElementError&)
        {
            // Nothing to do. No image has been stored yet
        }

		firstBufferId = getFirstAvailFrameBufferId();
	}

	// Get a stream to save the image
	///////////////////////////////////////////////////////////
    std::shared_ptr<streamWriter> outputStream;
    std::shared_ptr<memory> uncompressedImage(std::make_shared<memory>());
	if(bEncapsulated || frameNumber == 0)
	{
        outputStream = getStreamWriter(groupId, 0, tagId, firstBufferId, dataHandlerType);
	}
	else
	{
        std::shared_ptr<memoryStreamOutput> memStream(std::make_shared<memoryStreamOutput>(uncompressedImage));
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
        std::shared_ptr<handlers::writingDataHandlerRaw> copyUncompressed(getWritingDataHandlerRaw(groupId, 0, tagId, firstBufferId));
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
        dataHandlerTransferSyntax->setString(0, transferSyntax);

        std::string colorSpace = pImage->getColorSpace();
        setString(0x0028, 0x0, 0x0004, 0, 0, transforms::colorTransforms::colorTransformsFactory::makeSubsampled(colorSpace, bSubSampledX, bSubSampledY));
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

        if(colorSpace == "PALETTECOLOR")
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
    for(std::uint32_t scanBuffers = 1; scanBuffers < firstBufferId; ++scanBuffers)
	{
        calculatePosition += (std::uint32_t)tag->getBufferSizeThrow(scanBuffers);
		calculatePosition += 8;
	}
    std::shared_ptr<handlers::writingDataHandlerRaw> offsetHandler(getWritingDataHandlerRaw(groupId, 0, tagId, 0, dataHandlerType));
	offsetHandler->setSize(4 * (frameNumber + 1));
	std::uint8_t* pOffsetFrame(offsetHandler->getMemoryBuffer() + (frameNumber * 4));
	*( (std::uint32_t*)pOffsetFrame  ) = calculatePosition;
	streamController::adjustEndian(pOffsetFrame, 4, streamController::lowByteEndian, 1);

	IMEBRA_FUNCTION_END();
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
    try
    {
        // Retrieve the buffer containing the offsets
        ///////////////////////////////////////////////////////////
        std::shared_ptr<handlers::readingDataHandlerRaw> framesPointer = getReadingDataHandlerRawThrow(0x7fe0, 0x0, 0x0010, 0);

        // Get the offset table's size, in number of offsets
        ///////////////////////////////////////////////////////////
        std::uint32_t offsetsCount = (std::uint32_t)(framesPointer->getSize() / sizeof(std::uint32_t));

        // If the requested frame doesn't exist then return
        //  0xffffffff (the maximum value)
        ///////////////////////////////////////////////////////////
        if(frameNumber >= offsetsCount && frameNumber != 0)
        {
            return std::numeric_limits<std::uint32_t>::max();
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
    catch(const MissingDataElementError&)
    {
        return 0xffffffff;
    }
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
// Return the buffer that starts at the specified offset
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::uint32_t dataSet::getFrameBufferId(std::uint32_t offset) const
{
    IMEBRA_FUNCTION_START();

    std::shared_ptr<data> imageTag = getTagThrow(0x7fe0, 0, 0x0010);

    // Start from the buffer n. 1 (the buffer 0 contains
    //  the offset table
    ///////////////////////////////////////////////////////////
    std::uint32_t scanBuffers(1);

    if(offset == std::numeric_limits<std::uint32_t>::max())
    {
        while(imageTag->bufferExists(scanBuffers))
        {
            ++scanBuffers;
        }
        return scanBuffers;
    }

    while(offset != 0)
    {
        // Calculate the total size of the buffer, including
        //  its descriptor (tag group and id and length)
        ///////////////////////////////////////////////////////////
        std::uint32_t bufferSize = (std::uint32_t)imageTag->getBufferSizeThrow(scanBuffers);;
        bufferSize += 4; // one WORD for the group id, one WORD for the tag id
        bufferSize += 4; // one DWORD for the tag length
        if(bufferSize > offset)
        {
            IMEBRA_THROW(DataSetImageDoesntExistError, "Image not in the offset table");
        }
        offset -= bufferSize;
        ++scanBuffers;
    }

    return scanBuffers;

	IMEBRA_FUNCTION_END();
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
size_t dataSet::getFrameBufferIds(std::uint32_t frameNumber, std::uint32_t* pFirstBuffer, std::uint32_t* pEndBuffer) const
{
    IMEBRA_FUNCTION_START();

    try
    {
        std::uint32_t startOffset = getFrameOffset(frameNumber);
        std::uint32_t endOffset = getFrameOffset(frameNumber + 1);

        if(startOffset == std::numeric_limits<std::int32_t>::max())
        {
            IMEBRA_THROW(DataSetImageDoesntExistError, "Image not in the table offset");
        }

        *pFirstBuffer = getFrameBufferId(startOffset);
        *pEndBuffer = getFrameBufferId(endOffset);

        std::shared_ptr<data> imageTag = getTagThrow(0x7fe0, 0, 0x0010);
        if(imageTag == 0)
        {
            return 0;
        }
        size_t totalSize(0);
        for(std::uint32_t scanBuffers(*pFirstBuffer); scanBuffers != *pEndBuffer; ++scanBuffers)
        {
            totalSize += imageTag->getBufferSizeThrow(scanBuffers);
        }
        return totalSize;
    }
    catch(const MissingDataElementError&)
    {
        IMEBRA_THROW(DataSetCorruptedOffsetTableError, "The basic offset table is corrupted");
    }

	IMEBRA_FUNCTION_END();
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
    IMEBRA_FUNCTION_START();

    std::uint32_t availableId(0);
    while(bufferExists(0x7fe0, 0, 0x0010, availableId))
    {
        ++availableId;
    }

	return availableId;

	IMEBRA_FUNCTION_END();
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
std::shared_ptr<dataSet> dataSet::getSequenceItemThrow(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t itemId) const
{
    IMEBRA_FUNCTION_START();

    return getTagThrow(groupId, order, tagId)->getDataSetThrow(itemId);

	IMEBRA_FUNCTION_END();
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
std::shared_ptr<lut> dataSet::getLutThrow(std::uint16_t groupId, std::uint16_t tagId, std::uint32_t lutId) const
{
    IMEBRA_FUNCTION_START();

    std::shared_ptr<dataSet> embeddedLUT = getSequenceItemThrow(groupId, 0, tagId, lutId);
    std::shared_ptr<handlers::readingDataHandler> descriptorHandle = embeddedLUT->getReadingDataHandlerThrow(0x0028, 0x0, 0x3002, 0x0);
    std::shared_ptr<handlers::readingDataHandler> dataHandle = embeddedLUT->getReadingDataHandlerThrow(0x0028, 0x0, 0x3006, 0x0);

    std::shared_ptr<lut> pLUT = std::make_shared<lut>();
    pLUT->setLut(
        descriptorHandle,
        dataHandle,
        embeddedLUT->getUnicodeStringThrow(0x0028, 0x0, 0x3003, 0, 0));
	return pLUT;

	IMEBRA_FUNCTION_END();
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
std::shared_ptr<waveform> dataSet::getWaveformThrow(std::uint32_t waveformId)
{
    IMEBRA_FUNCTION_START();

    std::shared_ptr<dataSet> embeddedWaveform(getSequenceItemThrow(0x5400, 0, 0x0100, waveformId));
    return std::make_shared<waveform>(embeddedWaveform);

	IMEBRA_FUNCTION_END();
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
std::int32_t dataSet::getSignedLongThrow(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber) const
{
    IMEBRA_FUNCTION_START();

    return getReadingDataHandlerThrow(groupId, order, tagId, bufferId)->getSignedLong(elementNumber);

	IMEBRA_FUNCTION_END();
}

std::int32_t dataSet::getSignedLong(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber, std::int32_t defaultValue) const
{
    try
    {
        return getSignedLongThrow(groupId, order, tagId, bufferId, elementNumber);
    }
    catch(const MissingDataElementError&)
    {
        return defaultValue;
    }
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
    IMEBRA_FUNCTION_START();

    std::shared_ptr<handlers::writingDataHandler> dataHandler = getWritingDataHandler(groupId, order, tagId, bufferId, defaultType);
    if(dataHandler->getSize() <= elementNumber)
    {
        dataHandler->setSize(elementNumber + 1);
    }
    dataHandler->setSignedLong(elementNumber, newValue);

	IMEBRA_FUNCTION_END();
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
std::uint32_t dataSet::getUnsignedLongThrow(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber) const
{
    IMEBRA_FUNCTION_START();

    return getReadingDataHandlerThrow(groupId, order, tagId, bufferId)->getUnsignedLong(elementNumber);

	IMEBRA_FUNCTION_END();
}

std::uint32_t dataSet::getUnsignedLong(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber, std::uint32_t defaultValue) const
{
    try
    {
        return getUnsignedLongThrow(groupId, order, tagId, bufferId, elementNumber);
    }
    catch(const MissingDataElementError&)
    {
        return defaultValue;
    }
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
    IMEBRA_FUNCTION_START();

    std::shared_ptr<handlers::writingDataHandler> dataHandler = getWritingDataHandler(groupId, order, tagId, bufferId, defaultType);
    if(dataHandler->getSize() <= elementNumber)
    {
        dataHandler->setSize(elementNumber + 1);
    }
    dataHandler->setUnsignedLong(elementNumber, newValue);

	IMEBRA_FUNCTION_END();
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
double dataSet::getDoubleThrow(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber) const
{
    IMEBRA_FUNCTION_START();

    return getReadingDataHandlerThrow(groupId, order, tagId, bufferId)->getDouble(elementNumber);

	IMEBRA_FUNCTION_END();
}

double dataSet::getDouble(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber, double defaultValue) const
{
    try
    {
        return getDoubleThrow(groupId, order, tagId, bufferId, elementNumber);
    }
    catch(const MissingDataElementError&)
    {
        return defaultValue;
    }
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
    IMEBRA_FUNCTION_START();

    std::shared_ptr<handlers::writingDataHandler> dataHandler = getWritingDataHandler(groupId, order, tagId, bufferId, defaultType);
    if(dataHandler->getSize() <= elementNumber)
    {
        dataHandler->setSize(elementNumber + 1);
    }
    dataHandler->setDouble(elementNumber, newValue);

	IMEBRA_FUNCTION_END();
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
std::string dataSet::getStringThrow(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber) const
{
    IMEBRA_FUNCTION_START();

    return getReadingDataHandlerThrow(groupId, order, tagId, bufferId)->getString(elementNumber);

	IMEBRA_FUNCTION_END();
}

std::string dataSet::getString(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber, const std::string& defaultValue) const
{
    try
    {
        return getStringThrow(groupId, order, tagId, bufferId, elementNumber);
    }
    catch(const MissingDataElementError&)
    {
        return defaultValue;
    }
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
std::wstring dataSet::getUnicodeStringThrow(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber) const
{
    IMEBRA_FUNCTION_START();

    return getReadingDataHandlerThrow(groupId, order, tagId, bufferId)->getUnicodeString(elementNumber);

	IMEBRA_FUNCTION_END();
}

std::wstring dataSet::getUnicodeString(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber, const std::wstring& defaultValue) const
{
    try
    {
        return getUnicodeStringThrow(groupId, order, tagId, bufferId, elementNumber);
    }
    catch(const MissingDataElementError&)
    {
        return defaultValue;
    }
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
    IMEBRA_FUNCTION_START();

    std::shared_ptr<handlers::writingDataHandler> dataHandler = getWritingDataHandler(groupId, order, tagId, bufferId, defaultType);
    if(dataHandler->getSize() <= elementNumber)
    {
        dataHandler->setSize(elementNumber + 1);
    }
    dataHandler->setString(elementNumber, newString);

	IMEBRA_FUNCTION_END();
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
    IMEBRA_FUNCTION_START();

    std::shared_ptr<handlers::writingDataHandler> dataHandler = getWritingDataHandler(groupId, order, tagId, bufferId, defaultType);
    if(dataHandler->getSize() <= elementNumber)
    {
        dataHandler->setSize(elementNumber + 1);
    }
    dataHandler->setUnicodeString(elementNumber, newString);

	IMEBRA_FUNCTION_END();
}

void dataSet::setAge(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber, std::uint32_t age, ageUnit_t units, const std::string& defaultType /* = "" */)
{
    IMEBRA_FUNCTION_START();

    std::shared_ptr<handlers::writingDataHandler> dataHandler = getWritingDataHandler(groupId, order, tagId, bufferId, defaultType);
    if(dataHandler->getSize() <= elementNumber)
    {
        dataHandler->setSize(elementNumber + 1);
    }
    dataHandler->setAge(elementNumber, age, units);

    IMEBRA_FUNCTION_END();
}

std::uint32_t dataSet::getAgeThrow(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber, ageUnit_t* pUnits) const
{
    IMEBRA_FUNCTION_START();

    return getReadingDataHandlerThrow(groupId, order, tagId, bufferId)->getAge(elementNumber, pUnits);

    IMEBRA_FUNCTION_END();
}

std::uint32_t dataSet::getAge(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId,
                              size_t elementNumber, ageUnit_t* pUnits,
                              std::uint32_t defaultAge, ageUnit_t defaultUnits) const
{
    IMEBRA_FUNCTION_START();

    try
    {
        return getAgeThrow(groupId, order, tagId, bufferId, elementNumber, pUnits);
    }
    catch(const MissingDataElementError&)
    {
        *pUnits = defaultUnits;
        return defaultAge;
    }

    IMEBRA_FUNCTION_END();

}


void dataSet::setDate(uint16_t groupId, uint16_t order, uint16_t tagId, size_t bufferId, size_t elementNumber, uint32_t year, uint32_t month, uint32_t day, uint32_t hour, uint32_t minutes, uint32_t seconds, uint32_t nanoseconds, int32_t offsetHours, int32_t offsetMinutes, const std::string& defaultType /* = "" */)
{
    IMEBRA_FUNCTION_START();

    std::shared_ptr<handlers::writingDataHandler> dataHandler = getWritingDataHandler(groupId, order, tagId, bufferId, defaultType);
    if(dataHandler->getSize() <= elementNumber)
    {
        dataHandler->setSize(elementNumber + 1);
    }
    dataHandler->setDate(elementNumber, year, month, day, hour, minutes, seconds, nanoseconds, offsetHours, offsetMinutes);

    IMEBRA_FUNCTION_END();
}

void dataSet::getDateThrow(uint16_t groupId, uint16_t order, uint16_t tagId, size_t bufferId, size_t elementNumber, uint32_t *pYear, uint32_t *pMonth, uint32_t *pDay, uint32_t *pHour, uint32_t *pMinutes, uint32_t *pSeconds, uint32_t *pNanoseconds, int32_t *pOffsetHours, int32_t *pOffsetMinutes) const
{
    IMEBRA_FUNCTION_START();

    return getReadingDataHandlerThrow(groupId, order, tagId, bufferId)->getDate(elementNumber, pYear, pMonth, pDay, pHour, pMinutes, pSeconds, pNanoseconds, pOffsetHours, pOffsetMinutes);

    IMEBRA_FUNCTION_END();
}

void dataSet::getDate(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber,
    std::uint32_t* pYear,
    std::uint32_t* pMonth,
    std::uint32_t* pDay,
    std::uint32_t* pHour,
    std::uint32_t* pMinutes,
    std::uint32_t* pSeconds,
    std::uint32_t* pNanoseconds,
    std::int32_t* pOffsetHours,
    std::int32_t* pOffsetMinutes,
    std::uint32_t defaultYear,
    std::uint32_t defaultMonth,
    std::uint32_t defaultDay,
    std::uint32_t defaultHour,
    std::uint32_t defaultMinutes,
    std::uint32_t defaultSeconds,
    std::uint32_t defaultNanoseconds,
    std::int32_t defaultOffsetHours,
    std::int32_t defaultOffsetMinutes) const
{
    try
    {
        return getDateThrow(groupId, order, tagId, bufferId, elementNumber,
                            pYear, pMonth, pDay, pHour, pMinutes, pSeconds, pNanoseconds, pOffsetHours, pOffsetMinutes);
    }
    catch(const MissingDataElementError&)
    {
        *pYear = defaultYear;
        *pMonth = defaultMonth;
        *pDay = defaultDay;
        *pHour = defaultHour;
        *pMinutes = defaultMinutes;
        *pSeconds = defaultSeconds;
        *pNanoseconds = defaultNanoseconds;
        *pOffsetHours = defaultOffsetHours;
        *pOffsetMinutes = defaultOffsetMinutes;
    }
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
std::shared_ptr<handlers::readingDataHandler> dataSet::getReadingDataHandlerThrow(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId) const
{
    IMEBRA_FUNCTION_START();

    return getTagThrow(groupId, order, tagId)->getReadingDataHandlerThrow(bufferId);

	IMEBRA_FUNCTION_END();
}


std::shared_ptr<handlers::writingDataHandler> dataSet::getWritingDataHandler(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, const std::string& defaultType /* ="" */)
{
    IMEBRA_FUNCTION_START();

    std::shared_ptr<data> tag(getTagCreate(groupId, order, tagId));

    if(defaultType.length()!=2L)
    {
        return tag->getWritingDataHandler(bufferId, getDefaultDataType(groupId, tagId), m_charsetsList);
    }

    return tag->getWritingDataHandler(bufferId, defaultType, m_charsetsList);

    IMEBRA_FUNCTION_END();
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
std::shared_ptr<streamReader> dataSet::getStreamReaderThrow(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId) const
{
    IMEBRA_FUNCTION_START();

    return getTagThrow(groupId, order, tagId)->getStreamReaderThrow(bufferId);

	IMEBRA_FUNCTION_END();
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
    IMEBRA_FUNCTION_START();

    return getTagCreate(groupId, order, tagId)->getStreamWriter(bufferId, dataType);

	IMEBRA_FUNCTION_END();
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
std::shared_ptr<handlers::readingDataHandlerRaw> dataSet::getReadingDataHandlerRawThrow(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId) const
{
    IMEBRA_FUNCTION_START();

    return getTagThrow(groupId, order, tagId)->getReadingDataHandlerRawThrow(bufferId);

	IMEBRA_FUNCTION_END();
}


std::shared_ptr<handlers::writingDataHandlerRaw> dataSet::getWritingDataHandlerRaw(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, const std::string& defaultType /* ="" */)
{
    IMEBRA_FUNCTION_START();

    std::shared_ptr<data> tag = getTagCreate(groupId, order, tagId);

    if(defaultType.length()!=2)
    {
        return tag->getWritingDataHandlerRaw(bufferId, getDefaultDataType(groupId, tagId), m_charsetsList);
    }

    return tag->getWritingDataHandlerRaw(bufferId, defaultType, m_charsetsList);

    IMEBRA_FUNCTION_END();
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
    IMEBRA_FUNCTION_START();

	return dicomDictionary::getDicomDictionary()->getTagType(groupId, tagId);

	IMEBRA_FUNCTION_END();
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
std::string dataSet::getDataTypeThrow(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId) const
{
    IMEBRA_FUNCTION_START();

    return getTagThrow(groupId, order, tagId)->getDataTypeThrow(bufferId);

	IMEBRA_FUNCTION_END();
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
    try
    {
        std::shared_ptr<handlers::readingDataHandler> charsetHandler(getReadingDataHandlerThrow(0x0008, 0, 0x0005, 0));
        for(std::uint32_t pointer(0); pointer != charsetHandler->getSize(); ++pointer)
		{
            charsets.push_back(charsetHandler->getString(pointer));
		}
	}
    catch(const MissingDataElementError&)
    {
        // TODO
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

} // namespace implementation

} // namespace imebra
