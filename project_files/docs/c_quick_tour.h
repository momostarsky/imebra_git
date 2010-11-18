/*
$fileHeader$
*/

/*!

\page quick_tour Getting started

\section quick_tour_project Adding the Imebra library to your project

You should read \ref add_to_project to learn how to include Imebra to your
 project.

For the impatients:
 - Add all the files in the directories library/base and 
   library/imebra to your project
 - Disable the use of the precompiled header for all the Imebra source files (.cpp)
 - Include the file "library/imebra/include/imebra.h" in all the
   files that use the Imebra classes, or include it in the precompiled headers
 - If you are compiling the application on Windows, then define the preprocessor
   symbol WIN32 and _WIN32_WINNT=0x0500 or higher


\section quick_tour_dataSet Let's read a dataSet

A dataSet can be created by reading a Dicom stream or a Jpeg stream; Imebra
 detects the stream format automatically.

The first operation to perform is the creation of a stream; this can be a file or a
 memory buffer.

In this example we use a file stream. The following code creates a file stream
 and open the file "d:\test.dcm" in read mode:
\code
using namespace puntoexe;
ptr<stream> readStream(new stream);
readStream->openFile("d:\\test.dcm", std::ios::in);
\endcode

In the previous code the application used a smart pointer (see puntoexe::ptr)
 that tracks the usage of a stream object; when the smart pointer (the variable
 readStream) goes out of scope then the reference counter of the stream is
 decreased. Eventually the stream is deleted when the reference counter
 reaches 0.

With the following code we parse the content of the file managed by the stream
 and we create a dataSet structure that contains the dicom tags defined in the
 file. We create a streamReader object, which accesses the stream and gets data
 from it. Several streamReader objects can share a single baseStream, even in
 multithread environments.
\code
ptr<streamReader> reader(new streamReader(readStream));
ptr<imebra::dataSet> testDataSet = 
	imebra::codecs::codecFactory::getCodecFactory()->load(reader);
\endcode

The previous code gets the pointer to the \ref puntoexe::imebra::codecs::codecFactory, 
 which in turn loads the data from the specified stream. The codecs factory automatically
 detects the data format (dicom or jpeg). There is only one instance of the codec
 factory allocated by the library.


\section quick_tour_tag Let's read or set a tag in the dataSet

Once the dataSet has been created or loaded, your application can load or write
 values into the dataSet's tags.

In the following example we read the patient's name.
A person name can have up to 5 components (last name, middle name, first name,...)
 separated by ^ and can be represented in 3 different ways (character representation,
 ideographic representation or phonetic representation) separated by a =.

Refer to the Dicom standard for more informations regarding the person name.

The Person Name handler in Imebra automatically separates the name's representation,
 while the name's components have to be separated by the application.
\code
std::string patientNameCharacter = testDataSet->getString(0x0010, 0, 0x0010, 0);
std::string patientNameIdeographic = testDataSet->getString(0x0010, 0, 0x0010, 1);
\endcode


\section quick_tour_image Let's read an image

The dataSet provides a function that can decompress an image embedded into a dataSet.

The following example reads the first image embedded into a dataSet:
\code
ptr<imebra::image> firstImage = testDataSet->getImage(0);
\endcode

Note that an image should be processed by the modalityVOILUT transform to convert
 its pixel values into meaningful values.

The following example apply the modalityVOILUT transform to the image:
\code
ptr<imebra::transforms::transform> modVOILUT(
	new imebra::transforms::modalityVOILUT);
imbxUint32 width, height;
firstImage->getSize(&width, &height);
ptr<imebra::image> convertedImage(modVOILUT->allocateOutputImage(firstImage, width, height);
modVOILUT->runTransform(firstImage, 0, 0, width, height, convertedImage, 0, 0);
\endcode

Further processing may be required to convert the convertedImage into an image
 suitable for the presentation on the screen. The VOILUT transform applies the
 contrast suggested by the dataSet to the image. For instance:
\code
ptr<imebra::transforms::transform> myVoiLut(
	new imebra::transforms::VOILUT(testDataSet));

// Apply the first VOI or LUT
imbxUint32 lutId = myVoiLut->getVOILUTId(0);
myVoiLut->setVOILUT(lutId);

ptr<imebra::image> presentationImage(myVoiLut->allocateOutputImage(convertedImage, width, height));
myVoiLut->runTransform(convertedImage, 0, 0 width, height, presentationImage, 0, 0);
\endcode

And do you need the image in an RGB format? Here you go:
\code
using namespace puntoexe::imebra;
transforms::colorTransforms::colorTransformsFactory* pFactory = transforms::colorTransforms::colorTransformsFactory::getColorTransformsFactory();
ptr<transforms::transform> myColorTransform = pFactory->getTransform(presentationImage->getColorSpace(), L"RGB");
if(myColorTransform != 0) // color transform not needed if the factory returns 0
{
	ptr<image> rgbImage(myColorTransform->allocateOutputImage(presentationImage, width, height));
	myColorTransform->runTransform(presentationImage, 0, 0, width, height, rgbImage, 0, 0);
	presentationImage = rgbImage;
}
\endcode

Now the variable presentationImage contains an RGB image ready to be displayed.


\section quick_tour_image_pixels How to access the image's pixels

In order to access to the image's pixels you have to retrieve a data handler:
\code
imbxUint32 rowSize, channelPixelSize, channelsNumber;
ptr<imebra::handlers::dataHandlerNumericBase> myHandler = presentationImage->getDataHandler(false, &rowSize, &channelPixelSize, &channelsNumber);

// Retrieve the image's size in pixels
imbxUint32 sizeX, sizeY;
presentationImage->getSize(&sizeX, &sizeY);

// Scan all the rows
for(imbxUint32 scanY = 0; scanY < sizeY; ++scanY)
{
	// Scan all the columns
	for(imbxUint32 scanX = 0; scanX < sizeX; ++scanX)
	{
		// Scan all the channels
		for(imbxUint32 scanChannel = 0; scanChannel < channelsNumber; ++scanChannel)
		{
			imbxInt32 channelValue = myHandler->getSignedLongIncPointer();
			
			// Do something with the channel's value
			//--------------------------------------
		}
	}
}
\endcode

The data handler provides also a pointer to the image's data, which allows to access the pixels' values in a faster way.\n
Use the method puntoexe::imebra::handlers::dataHandlerNumericBase::getMemoryBuffer() to retrieve a pointer to the first
 pixel channel. Note that the values may be 1, 2 or 4 bytes wide, signed or unsigned, according to the image's bit depth
 and signed/unsigned attribute. You can use the functions puntoexe::imebra::handlers::dataHandler::getUnitSize() and
 puntoexe::imebra::handlers::dataHandlerNumericBase::isSigned() to retrieve the values width in bytes and the signed/unsigned
 attribute.

\code
imbxUint32 rowSize, channelPixelSize, channelsNumber;
ptr<imebra::handlers::dataHandlerNumericBase> myHandler = presentationImage->getDataHandler(false, &rowSize, &channelPixelSize, &channelsNumber);
imbxInt32* pBuffer = myHandler->getMemoryBuffer();

// Retrieve the image's size in pixels
imbxUint32 sizeX, sizeY;
presentationImage->getSize(&sizeX, &sizeY);

// Scan all the rows. We assume that the pixels are 32 bits wide and signed
if(myHandler->getUnitSize() == sizeof(imbxInt32) && myHandler->isSigned())
{
	for(imbxUint32 scanY = 0; scanY < sizeY; ++scanY)
	{
	// Scan all the columns
	for(imbxUint32 scanX = 0; scanX < sizeX; ++scanX)
	{
		// Scan all the channels
		for(imbxUint32 scanChannel = 0; scanChannel < channelsNumber; ++scanChannel)
		{
			imbxInt32 channelValue = *(pBuffer++);
			
			// Do something with the channel's value
			//--------------------------------------
		}
	}
	}
}
\endcode
*/
