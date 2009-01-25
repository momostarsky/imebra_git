/*
$fileHeader$
*/

#include <iostream>


#include "../../imebra/include/imebra.h"
#include <sstream>

#ifdef PUNTOEXE_WINDOWS
#include <process.h>
#else
#include <spawn.h>
#include <sys/wait.h>
#endif

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
	std::wstring version(L"1.0.0.1");
	std::wcout << L"dicom2jpeg version " << version << L"\n";

	try
	{

		if(argc < 3)
		{
			std::wcout <<
L"\
Usage: dicom2jpeg dicomFileName jpegFileName [-ffmpeg FFMPEGPATH FFMPEGOPT]\n\
\n\
dicomFileName        = name of the dicom file\n\
jpegFileName         = name of the final jpeg file\n\
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

		// Check for the -ffmpeg flag
		int ffmpegFlag(findArgument("-ffmpeg", argc, argv));

		size_t framesCount(0);

		try
		{
			// Scan through the frames
			for(imbxUint32 frameNumber(0); ; ++frameNumber)
			{
				// Apply the modality VOI/LUT
				ptr<transforms::modalityVOILUT> modVOILUT(new transforms::modalityVOILUT);
				modVOILUT->declareDataSet(loadedDataSet);
				modVOILUT->declareInputImage(0, loadedDataSet->getImage(frameNumber));
				modVOILUT->doTransform();
				ptr<image> finalImage(modVOILUT->getOutputImage(0));

				// Apply the presentation VOI/LUT
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

				// Write the jpeg image to the stream
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
			// List of arguments to be passed to ffmpeg
			typedef std::list<std::string> tOptionsList;
			tOptionsList options;

			// The first argument is the application's name
			options.push_back(argv[ffmpegFlag + 1]);

			// Calculate the frames per second from the available tags
			double framesPerSecond(0);
			double frameTime(loadedDataSet->getDouble(0x0018, 0, 0x1063, 0));
			if(frameTime > 0.1)
			{
				framesPerSecond = 1000 / frameTime;
			}
			if(framesPerSecond < 0.1)
			{
				framesPerSecond = loadedDataSet->getUnsignedLong(0x0018, 0x0, 0x0040, 0x0);
			}
			if(framesPerSecond < 0.1)
			{
				framesPerSecond = loadedDataSet->getUnsignedLong(0x0008, 0x0, 0x2144, 0x0);
			}

			// Add the ffmpeg argument for the frames per second
			if(framesPerSecond > 0.1)
			{
				options.push_back("-r");
				std::ostringstream frameRate;
				frameRate << framesPerSecond;
				options.push_back(frameRate.str());
			}

			// Add the ffmpeg argument for the input files
			options.push_back("-i");
			options.push_back(outputFileName + "_%d" + extension);

			// Add the ffmpeg argument for the number of frames
			options.push_back("-dframes");
			std::ostringstream frameCount;
			frameCount << (unsigned long)framesCount;
			options.push_back(frameCount.str());

			// Add the arguments specified when dicom2jpeg was launched
			for(int copyArguments(ffmpegFlag + 2); copyArguments < argc; ++copyArguments)
			{
				options.push_back(argv[copyArguments]);
			}

			// Build the arguments array
			std::auto_ptr<const char*> ffArgv(new const char*[options.size() + 1]);
			size_t insertPosition(0);
			for(tOptionsList::iterator scanOptions(options.begin()); scanOptions != options.end(); ++scanOptions, ++insertPosition)
			{
				ffArgv.get()[insertPosition] = (*scanOptions).c_str();
			}
			ffArgv.get()[options.size()] = 0;

			// Launch ffmpeg
#ifdef PUNTOEXE_WINDOWS
            return (int)_spawnvp(_P_WAIT , argv[ffmpegFlag + 1], ffArgv.get());
#else
            char *environment[] = {0};

            pid_t process_id;
            posix_spawnp (&process_id, argv[ffmpegFlag + 1],
                            0, 0, (char* const*)ffArgv.get(), (char* const*)environment);
            wait(0);
#endif

		}

		return 0;

	}
	catch(...)
	{
		std::wcout << exceptionsManager::getMessage();
		return 1;
	}
}

