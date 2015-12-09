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
   symbol PUNTOEXE_WINDOWS


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

Once the dataSet has been created or loaded, your application can read or write
 values from/to the dataSet's tags.

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

The dataSet provides two functions that can decompress an image embedded into a dataSet:

- puntoexe::imebra::dataSet::getImage()
- puntoexe::imebra::dataSet::getModalityImage()

puntoexe::imebra::dataSet::getImage() retrieves the original images stored in the dataset, while
 puntoexe::imebra::dataSet::getModalityImage() retrieves the images after the modality VOI/LUT has been
 applied (if a modality VOI/LUT is available).

The following example reads the first image embedded into a dataSet:
\code
ptr<imebra::image> firstImage = testDataSet->getModalityImage(0);
\endcode

Further processing may be required to convert firstImage into an image
 suitable for the presentation on the screen. The VOILUT transform applies the
 contrast suggested by the dataSet to the image. For instance:
\code
ptr<imebra::transforms::transform> myVoiLut(
	new imebra::transforms::VOILUT(testDataSet));

// Apply the first VOI or LUT
std::uint32_t lutId = myVoiLut->getVOILUTId(0);
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

Now the variable presentationImage contains an RGB image.


\section quick_tour_image_pixels How to access the image's pixels

In order to access to the image's pixels you have to retrieve a data handler:
\code
std::uint32_t rowSize, channelPixelSize, channelsNumber;
ptr<imebra::handlers::dataHandlerNumericBase> myHandler = presentationImage->getDataHandler(false, &rowSize, &channelPixelSize, &channelsNumber);

// Retrieve the image's size in pixels
std::uint32_t sizeX, sizeY;
presentationImage->getSize(&sizeX, &sizeY);

// Scan all the rows
std::uint32_t index(0);
for(std::uint32_t scanY = 0; scanY < sizeY; ++scanY)
{
	// Scan all the columns
	for(std::uint32_t scanX = 0; scanX < sizeX; ++scanX)
	{
		// Scan all the channels
		for(std::uint32_t scanChannel = 0; scanChannel < channelsNumber; ++scanChannel)
		{
            std::int32_t channelValue = myHandler->getSignedLong(index++);
			
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
std::uint32_t rowSize, channelPixelSize, channelsNumber;
ptr<imebra::handlers::dataHandlerNumericBase> myHandler = presentationImage->getDataHandler(false, &rowSize, &channelPixelSize, &channelsNumber);
std::int32_t* pBuffer = myHandler->getMemoryBuffer();

// Retrieve the image's size in pixels
std::uint32_t sizeX, sizeY;
presentationImage->getSize(&sizeX, &sizeY);

// Scan all the rows. We assume that the pixels are 32 bits wide and signed
if(myHandler->getUnitSize() == sizeof(std::int32_t) && myHandler->isSigned())
{
	for(std::uint32_t scanY = 0; scanY < sizeY; ++scanY)
	{
	// Scan all the columns
	for(std::uint32_t scanX = 0; scanX < sizeX; ++scanX)
	{
		// Scan all the channels
		for(std::uint32_t scanChannel = 0; scanChannel < channelsNumber; ++scanChannel)
		{
			std::int32_t channelValue = *(pBuffer++);
			
			// Do something with the channel's value
			//--------------------------------------
		}
	}
	}
}
\endcode


\section quick_tour_image_display Displaying an image.

The class puntoexe::imebra::drawBitmap takes an image as an input and returns an 8 bit RGB bitmap of the requested
 image's area.

Each bitmap's row can be aligned to specific bytes boundaries and can store the pixels in the followig formats:

- puntoexe::imebra::drawBitmap::drawBitmapRGB: each pixel is formed by 3 bytes (R, G and B)
- puntoexe::imebra::drawBitmap::drawBitmapBGR: each pixel is formed by (B, G and R). Suitable for Windows systems
- puntoexe::imebra::drawBitmap::drawBitmapRGBA: each pixel is formed by 4 bytes (R, G, B and A). Suitable for Android & Mac (OSX, iOS)
- puntoexe::imebra::drawBitmap::drawBitmapBGRA: each pixel is formed by 4 bytes (B, G, R and A). Suitable for Windows systems

drawBitmap takes care of converting the color format to RGB if necessary, and also shifts the values to obtain 8 bit per color component.

If you used puntoexe::imebra::dataSet::getModalityImage() to retrieve the image then the modality transform has already
 been applied to the image, otherwise it must be applied by your application (see puntoexe::imebra::transforms::modalityVOILUT)
Sometimes the image must be processed with a presentation VOI/LUT transformations before it can be displayed.\n
A dataSet may contain several presentation VOI/LUTs and each one of them may highlight different parts of the image by
 applying different predefined contrasts or lookup tables.\n
The class puntoexe::imebra::transforms::VOILUT is responsible for retrieving the list of available presentation VOIs/LUTs,
 applying the selected VOI/LUT or finding the ideal LUT if none is specified in the dataSet.

The constructor of the puntoexe::imebra::transforms::VOILUT class takes a dataset as parameter in the constructor: then it uses
 the dataset to retrieve the available VOI or LUTs.


\subsection quick_tour_image_display_list_voilut Listing the presentation VOIs/LUTs defined in the dataset

The method puntoexe::imebra::transforms::VOILUT::getVOILUTIds() retrieves a list of IDs representing each VOI/LUT defined
 in the dataset.

Each ID may represent a VOI (Value of interest) or a LUT defined in the dataset: use puntoexe::imebra::transforms::VOILUT::getVOILUTDescription()
 to retrieve the description for a particular VOI or LUT.

\code
// Construct a VOILUT from a dataset
////////////////////////////////////
ptr<imebra::transforms::VOILUT> pVOILUT = new imebra::transforms::VOILUT(testDataSet);

// Get the list of defined VOIs and LUTs
////////////////////////////////////////
imebra::transforms::VOILUT::voilutIds_t availableIds = pVOILUT->getVOILUTIds();


\subsection quick_tour_image_display_select_voilut Selecting the presentation VOI/LUT

// Print out the description for the available VOI/LUTs
///////////////////////////////////////////////////////
for(imebra::transforms::VOILUT::voilutIds_t::iterator scan(availableIds.begin()), end(availableIds.end()); scan != end; ++scan)
{
    std::cout << pVOILUT->getVOILUTDescription(*scan);
}
\endcode

To select the VOI or LUT to apply to the image, pass the proper VOILUT id to the method puntoexe::imebra::transforms::VOILUT::setVOILUT().

\code
pVOILUT->setVOILUT(availableIds.front());
\endcode

The application may also apply a VOI not defined in the dataset by using puntoexe::imebra::transforms::VOILUT::setCenterWidth()
or puntoexe::imebra::transforms::VOILUT::applyOptimalVOI() which analyzes the image and selects the proper VOI.


\subsection quick_tour_image_display_drawbitmap Drawing the image

After the VOI or LUT has been selected, pass the transform class to the drawBitmap constructor which will apply it to the input
 image before calculating the output bytes.

\code

// Initialize the drawBitmap object
///////////////////////////////////
ptr<imebra::drawBitmap> draw = new imebra::drawBitmap(presentationImage, pVOILUT);

// Fill the puntoexe::memory object with the image in RGBA format
/////////////////////////////////////////////////////////////////
ptr<memory> memory = draw->getBitmap<imebra::drawBitmap::drawBitmapRGBA, 4>
                        (width, height, 0, 0, width, height, 0);

std::uint8_t* pRawData = memory->data(); // Data ready to be displayed in RGBA format
\endcode


\subsection quick_tour_image_display_mac Using drawBitmap on OS-X or iOS.

Please read also the previous sections, since they contain important information relevant to understand this section.

A special helper method called getImage() is available for OS-X and iOS (add the files in the folder objectivec to
 your project, see \ref add_to_project_files_mac).

This method uses puntoexe::imebra::drawBitmap to produce an UIImage or NSImage that can be used directly.

The method accepts the same parameters as drawBitmap's constructor but instead of a raw buffer it returns an UIImage
 or NSImage object that can be used directly by your application.





*/
