/*
$fileHeader$
*/

/*! \file transform.cpp
    \brief Implementation of the base class used by the transforms.

*/

#include "../../base/include/exception.h"
#include "../include/transform.h"
#include "../include/image.h"


namespace puntoexe
{

namespace imebra
{

namespace transforms
{

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Declare an input parameter
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void transform::declareInputImage(long imageNumber, ptr<image> pInputImage)
{
	PUNTOEXE_FUNCTION_START(L"transform::declareInputImage");

	lockObject lockAccess(this);

	// Add the new parameter
	///////////////////////////////////////////////////////////
	m_inputImages[imageNumber]=pInputImage;

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Delare an output parameter
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void transform::declareOutputImage(long imageNumber, ptr<image> pOutputImage)
{
	PUNTOEXE_FUNCTION_START(L"transform::declareOutputImage");

	lockObject lockAccess(this);

	// Add the new parameter
	///////////////////////////////////////////////////////////
	m_outputImages[imageNumber]=pOutputImage;

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Retrieve an output parameter
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
ptr<image> transform::getOutputImage(long imageNumber)
{
	PUNTOEXE_FUNCTION_START(L"transform::getOutputImage");

	lockObject lockAccess(this);

	tImagesMap::iterator findImage = m_outputImages.find(imageNumber);
	if(findImage != m_outputImages.end())
	{
		return findImage->second;
	}
	
	ptr<image> pImage;
	return pImage;

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Retrieve an input parameter
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
ptr<image> transform::getInputImage(long imageNumber)
{
	PUNTOEXE_FUNCTION_START(L"transform::getInputImage");

	lockObject lockAccess(this);
	
	tImagesMap::iterator findImage = m_inputImages.find(imageNumber);
	if(findImage != m_inputImages.end())
	{
		return findImage->second;
	}

	ptr<image> pImage;
	return pImage;

	PUNTOEXE_FUNCTION_END();
}


void transform::doTransform()
{
	PUNTOEXE_FUNCTION_START(L"transform::doTransform")

	for(int scanImages = 0; ; ++scanImages)
	{
		// Get the input image
		///////////////////////////////////////////////////////////
		ptr<image> pInputImage (getInputImage(scanImages));
		ptr<image> pOutputImage (getOutputImage(scanImages));

		// If the input image doesn't exist, then exit
		///////////////////////////////////////////////////////////
		if(pInputImage == 0 && pOutputImage == 0)
		{
			break;
		}

		if(pInputImage == 0)
		{
			pInputImage = pOutputImage;
		}

		imbxUint32 imageWidth(0), imageHeight(0);
		pInputImage->getSize(&imageWidth, &imageHeight);

		if(pOutputImage == 0)
		{
			pOutputImage = allocateOutputImage(pInputImage, imageWidth, imageHeight);
		}


		runTransform(pInputImage, 0, 0, imageWidth, imageHeight, pOutputImage, 0, 0);

	}

	PUNTOEXE_FUNCTION_END();

}


} // namespace transforms

} // namespace imebra

} // namespace puntoexe
