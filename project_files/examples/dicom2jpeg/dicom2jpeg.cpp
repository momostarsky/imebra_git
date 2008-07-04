// dicom2jpeg.cpp : Defines the entry point for the console application.
//

#include <iostream>


#include "../../imebra/include/imebra.h"
#include <sstream>

using namespace puntoexe;
using namespace puntoexe::imebra;
int main(int argc, char* argv[])
{
	try
	{

	if(argc < 3)
	{
		std::wcout << L"Usage: dicom2jpeg dicomFileName jpegFileName [-presentation]\r\n";
		std::wcout << L" dicomFileName = name of the dicom file\r\n";
		std::wcout << L" jpegFileName  = name of the final jpeg file\r\n";
		std::wcout << L" -presentation = if present then the presentation VOI/LUT are applied\r\n";
		std::wcout << L"                 The modality VOI/LUT is always applied\r\n";
	}

	// Separate the extension from the file name
	std::string outputFileName(argv[2]);
	std::string extension;
	size_t dotPos(outputFileName.rfind('.'));
	if(dotPos != outputFileName.npos)
	{
		extension = outputFileName.substr(dotPos);
		outputFileName.erase(dotPos);
	}
	else
	{
		extension = ".jpg";
	}

	// Open the file containing the dicom dataset
	ptr<puntoexe::stream> inputStream(new puntoexe::stream);
	inputStream->openFile(argv[1], std::ios_base::in);

	// Connect a stream reader to the dicom stream. Several stream reader
	//  can share the same stream
	ptr<puntoexe::streamReader> reader(new streamReader(inputStream));

	// Get a codec factory and let it use the right codec to create a dataset
	//  from the input stream
	ptr<codecs::codecFactory> codecsFactory(codecs::codecFactory::getCodecFactory());
	ptr<dataSet> loadedDataSet(codecsFactory->load(reader, 2048));
	
	try
	{
		for(imbxUint32 frameNumber(0); ; ++frameNumber)
		{
			// Apply the modality VOI/LUT
			ptr<transforms::modalityVOILUT> modVOILUT(new transforms::modalityVOILUT);
			modVOILUT->declareDataSet(loadedDataSet);
			modVOILUT->declareInputImage(0, loadedDataSet->getImage(frameNumber));
			modVOILUT->doTransform();
			ptr<image> finalImage(modVOILUT->getOutputImage(0));

			// Apply the presentation VOI/LUT
			if(argc == 4 && std::string(argv[3]) == "-presentation")
			{
				ptr<transforms::VOILUT> presentationVOILUT(new transforms::VOILUT);
				presentationVOILUT->declareDataSet(loadedDataSet);
				imbxUint32 firstVOILUTID(presentationVOILUT->getVOILUTId(0));
				if(firstVOILUTID != 0)
				{
					presentationVOILUT->setVOILUT(firstVOILUTID);
					presentationVOILUT->declareInputImage(0, finalImage);
					presentationVOILUT->doTransform();
					finalImage = presentationVOILUT->getOutputImage(0);
				}
			}

			// Color transform to YCrCb
			ptr<transforms::colorTransforms::colorTransformsFactory> colorFactory(transforms::colorTransforms::colorTransformsFactory::getColorTransformsFactory());
			ptr<transforms::transform> colorTransform(colorFactory->getTransform(finalImage->getColorSpace(), L"YBR_FULL"));
			if(colorTransform != 0)
			{
				colorTransform->declareDataSet(loadedDataSet);
				colorTransform->declareInputImage(0, finalImage);
				colorTransform->doTransform();
				finalImage = colorTransform->getOutputImage(0);
			}

			// Adjust high bit
			if(finalImage->getHighBit() != 7)
			{
				ptr<image> eightBitImage(new image);
				imbxUint32 width, height;
				finalImage->getSize(&width, &height);
				eightBitImage->create(width, height, image::depthU8, L"YBR_FULL", 7);
				ptr<transforms::transformHighBit> modifyHighBit(new transforms::transformHighBit);
				modifyHighBit->declareDataSet(loadedDataSet);
				modifyHighBit->declareInputImage(0, finalImage);
				modifyHighBit->declareOutputImage(0, eightBitImage);
				modifyHighBit->doTransform();
				finalImage = eightBitImage;
			}

			// Create a jpeg dataset
			std::wstring jpegTransferSyntax(L"1.2.840.10008.1.2.4.50");
			ptr<dataSet> jpegDataSet(new dataSet);
			jpegDataSet->setImage(0, finalImage, jpegTransferSyntax, codecs::codec::veryHigh);

			// Open a stream for the jpeg
			std::ostringstream jpegFileName;
			jpegFileName << outputFileName;
			if(frameNumber != 0)
			{
				jpegFileName << "_" << frameNumber;
			}
			jpegFileName << extension;
			ptr<puntoexe::stream> jpegStream(new puntoexe::stream);
			jpegStream->openFile(jpegFileName.str(), std::ios_base::out | std::ios_base::trunc);
			ptr<puntoexe::streamWriter> jpegWriter(new streamWriter(jpegStream));
			ptr<codecs::codec> outputCodec(codecsFactory->getCodec(jpegTransferSyntax));
			outputCodec->write(jpegWriter, jpegDataSet);
		}
	}
	catch(dataSetImageDoesntExist&)
	{
		// Ignore this exception. It is thrown when we reach the
		//  end of the images list
		exceptionsManager::getMessage(); 
	}
	return 0;

	}
	catch(...)
	{
		std::wcout << exceptionsManager::getMessage();
		return 1;
	}
}

