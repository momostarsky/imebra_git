/*
$fileHeader$
*/

/*! \file transformsChain.cpp
    \brief Implementation of the class transformsChain.

*/

#include "exceptionImpl.h"
#include "transformsChainImpl.h"
#include "imageImpl.h"
#include "dataSetImpl.h"
#include "transformHighBitImpl.h"

namespace puntoexe
{

namespace imebra
{

namespace transforms
{



transformsChain::transformsChain():
        m_inputWidth(0),
        m_inputHeight(0),
	m_inputDepth(image::endOfDepths),
	m_inputHighBit(0),
	m_outputDepth(image::endOfDepths),
	m_outputHighBit(0)
{}

///////////////////////////////////////////////////////////
//
// Add a new transform to the chain
//
///////////////////////////////////////////////////////////
void transformsChain::addTransform(std::shared_ptr<transform> pTransform)
{
	PUNTOEXE_FUNCTION_START(L"transformsChain::addTransform");

        if(pTransform != 0 && !pTransform->isEmpty())
        {
            // Store the transform in the chain.
            ///////////////////////////////////////////////////////////
            m_transformsList.push_back(pTransform);
        }

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
//
// Returns true if no transform has been defined
//
///////////////////////////////////////////////////////////
bool transformsChain::isEmpty()
{
	return m_transformsList.empty();
}


void transformsChain::runTransform(
            const std::shared_ptr<image>& inputImage,
            std::uint32_t inputTopLeftX, std::uint32_t inputTopLeftY, std::uint32_t inputWidth, std::uint32_t inputHeight,
            const std::shared_ptr<image>& outputImage,
            std::uint32_t outputTopLeftX, std::uint32_t outputTopLeftY)
{
	if(isEmpty())
	{
		std::shared_ptr<transformHighBit> highBit(new transformHighBit);
		highBit->runTransform(inputImage, inputTopLeftX, inputTopLeftY, inputWidth, inputHeight, outputImage, outputTopLeftX, outputTopLeftY);
		return;
	}

	if(m_transformsList.size() == 1)
	{
		m_transformsList.front()->runTransform(inputImage, inputTopLeftX, inputTopLeftY, inputWidth, inputHeight,
			outputImage, outputTopLeftX, outputTopLeftY);
		return;
	}

	// Get the position of the last transform
	///////////////////////////////////////////////////////////
	tTransformsList::iterator lastTransform(m_transformsList.end());
	--lastTransform;

    std::string inputColorSpace(inputImage->getColorSpace());
	image::bitDepth inputDepth(inputImage->getDepth());
	std::uint32_t inputHighBit(inputImage->getHighBit());
    std::string outputColorSpace(outputImage->getColorSpace());
	image::bitDepth outputDepth(outputImage->getDepth());
	std::uint32_t outputHighBit(outputImage->getHighBit());
	std::uint32_t allocateRows = 65536 / inputWidth;
	if(allocateRows < 1)
	{
		allocateRows = 1;
	}
	if(allocateRows > inputHeight)
	{
		allocateRows = inputHeight;
	}

	// Allocate temporary images
	///////////////////////////////////////////////////////////
	if(
		m_inputWidth != inputWidth ||
		m_inputHeight != inputHeight ||
		m_inputColorSpace != inputColorSpace ||
		m_inputDepth != inputDepth ||
		m_inputHighBit != inputHighBit ||
		m_outputColorSpace != outputColorSpace ||
		m_outputDepth != outputDepth ||
		m_outputHighBit != outputHighBit)
	{
		m_inputWidth = inputWidth;
		m_inputHeight = inputHeight;
		m_inputColorSpace = inputColorSpace;
		m_inputDepth = inputDepth;
		m_inputHighBit = inputHighBit;
		m_outputColorSpace = outputColorSpace;
		m_outputDepth = outputDepth;
		m_outputHighBit = outputHighBit;

		m_temporaryImages.clear();
		tTransformsList::iterator scanTransforms(m_transformsList.begin());
		m_temporaryImages.push_back((*scanTransforms)->allocateOutputImage(inputImage, inputWidth, allocateRows));
		while(++scanTransforms != lastTransform)
		{
			m_temporaryImages.push_back((*scanTransforms)->allocateOutputImage(m_temporaryImages.back(), inputWidth, allocateRows));
		}
	}

	// Run all the transforms. Split the images into several
	//  parts
	///////////////////////////////////////////////////////////
	while(inputHeight != 0)
	{
		std::uint32_t rows = allocateRows;
		if(rows > inputHeight)
		{
			rows = inputHeight;
		}
		inputHeight -= rows;
		
		tTransformsList::iterator scanTransforms(m_transformsList.begin());
		tTemporaryImagesList::iterator scanTemporaryImages(m_temporaryImages.begin());
		
		(*scanTransforms)->runTransform(inputImage, inputTopLeftX, inputTopLeftY, inputWidth, rows, *scanTemporaryImages, 0, 0);
		inputTopLeftY += rows;

		while(++scanTransforms != lastTransform)
		{
			std::shared_ptr<image> temporaryInput(*(scanTemporaryImages++));
			std::shared_ptr<image> temporaryOutput(*scanTemporaryImages);

			(*scanTransforms)->runTransform(temporaryInput, 0, 0, inputWidth, rows, temporaryOutput, 0, 0);
		}

		m_transformsList.back()->runTransform(*scanTemporaryImages, 0, 0, inputWidth, rows, outputImage, outputTopLeftX, outputTopLeftY);
		outputTopLeftY += rows;
	}
}


std::shared_ptr<image> transformsChain::allocateOutputImage(std::shared_ptr<image> pInputImage, std::uint32_t width, std::uint32_t height)
{
	if(isEmpty())
	{
        std::shared_ptr<image> newImage(new image());
		newImage->create(width, height, pInputImage->getDepth(), pInputImage->getColorSpace(), pInputImage->getHighBit());
		return newImage;
	}

	if(m_transformsList.size() == 1)
	{
		return m_transformsList.front()->allocateOutputImage(pInputImage, width, height);
	}

	// Get the position of the last transform
	///////////////////////////////////////////////////////////
	tTransformsList::iterator lastTransform(m_transformsList.end());
	--lastTransform;

	std::shared_ptr<image> temporaryImage;

	for(tTransformsList::iterator scanTransforms(m_transformsList.begin()); scanTransforms != lastTransform; ++scanTransforms)
	{
		if(scanTransforms == m_transformsList.begin())
		{
			temporaryImage = (*scanTransforms)->allocateOutputImage(pInputImage, 1, 1);
		}
		else
		{
			std::shared_ptr <image> newImage( (*scanTransforms)->allocateOutputImage(temporaryImage, 1, 1) );
			temporaryImage = newImage;
		}
	}
	return (*lastTransform)->allocateOutputImage(temporaryImage, width, height);


}


} // namespace transforms

} // namespace imebra

} // namespace puntoexe
