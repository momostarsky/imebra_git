/*
$fileHeader$
*/

#include <iostream>


#include "../../imebra/include/imebra.h"
#include <sstream>
#include <process.h>
#include <memory>
#include <list>

using namespace puntoexe;
using namespace puntoexe::imebra;

int findArgument(const char* argument, int argc, char* argv[])
{
	for(int scanArg(0); scanArg != argc; ++scanArg)
	{
		if(std::string(argv[scanArg]) == argument)
		{
			return scanArg;
		}
	}
	return -1;
}



int main(int argc, char* argv[])
{
	try
	{

	if(argc < 3)
	{
		std::wcout << 
L"\
Usage: dicom2jpeg dicomFileName jpegFileName [-presentation] [-ffmpeg FFMPEGPATH FFMPEGOPT]\n\
\n\
dicomFileName        = name of the dicom file\n\
jpegFileName         = name of the final jpeg file\n\
-presentation        = if present then the presentation VOI/LUT are\n\
                       applied\n\
                       The modality VOI/LUT is always applied\n\
-ffmpeg FFMPEGPATH   = launches FFMPEG after generating the jpeg images.\n\
                       FFMPEGPATH is the path to FFMPEG and FFMPEGOPT\n\
                       are the options for ffmpeg.n\
                       The input images and the frame rate are\n\
                       added automatically to the options\
";
		return 1;
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
	
	// Check for the -presentation flag
	int presentationFlag(findArgument("-presentation", argc, argv));
	int ffmpegFlag(findArgument("-ffmpeg", argc, argv));

	size_t framesCount(0);

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
			if(presentationFlag >= 0)
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


			// Open a stream for the jpeg
			const std::wstring jpegTransferSyntax(L"1.2.840.10008.1.2.4.50");
			std::ostringstream jpegFileName;
			jpegFileName << outputFileName;
			if(frameNumber != 0 || ffmpegFlag >= 0)
			{
				jpegFileName << "_" << frameNumber;
			}
			jpegFileName << extension;
			ptr<puntoexe::stream> jpegStream(new puntoexe::stream);
			jpegStream->openFile(jpegFileName.str(), std::ios_base::out | std::ios_base::trunc);
			ptr<puntoexe::streamWriter> jpegWriter(new streamWriter(jpegStream));
			ptr<codecs::codec> outputCodec(codecsFactory->getCodec(jpegTransferSyntax));
			outputCodec->setImage(jpegWriter, finalImage, jpegTransferSyntax, codecs::codec::veryHigh,
				"OB", 8, false, false, false, false);
			++framesCount;
		}

	}
	catch(dataSetImageDoesntExist&)
	{
		// Ignore this exception. It is thrown when we reach the
		//  end of the images list
		exceptionsManager::getMessage(); 
	}

		// All the images have been generated.
		// Should we launch FFMPEG?
		if(ffmpegFlag >= 0 && framesCount != 0)
		{
			typedef std::list<std::string> tOptionsList;
			tOptionsList options;

			options.push_back(argv[ffmpegFlag + 1]);

			imbxUint32 framesPerSecond(loadedDataSet->getUnsignedLong(0x0018, 0x0, 0x0040, 0x0));
			if(framesPerSecond != 0)
			{
				options.push_back("-r");
				std::ostringstream frameRate;
				frameRate << framesPerSecond;
				options.push_back(frameRate.str());
			}

			options.push_back("-i");
			options.push_back(outputFileName + "_%d" + extension);

			options.push_back("-dframes");

			std::ostringstream frameCount;
			frameCount << (unsigned long)framesCount;
			options.push_back(frameCount.str());

			for(int copyArguments(ffmpegFlag + 2); copyArguments < argc; ++copyArguments)
			{
				options.push_back(argv[copyArguments]);
			}

			std::auto_ptr<const char*> ffArgv(new const char*[options.size() + 1]);
			size_t insertPosition(0);
			for(tOptionsList::iterator scanOptions(options.begin()); scanOptions != options.end(); ++scanOptions, ++insertPosition)
			{
				ffArgv.get()[insertPosition] = (*scanOptions).c_str();
			}
			ffArgv.get()[options.size()] = 0;

			// Launch ffmpeg
			return (int)_spawnvp(_P_WAIT , argv[ffmpegFlag + 1], ffArgv.get());

		}

		return 0;

	}
	catch(...)
	{
		std::wcout << exceptionsManager::getMessage();
		return 1;
	}
}

