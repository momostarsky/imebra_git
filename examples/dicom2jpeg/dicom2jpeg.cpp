/*
$fileHeader$
*/

#include <iostream>


#include <imebra/imebra.h>
#include <sstream>

#ifdef IMEBRA_WINDOWS
#include <process.h>
#else
#include <spawn.h>
#include <sys/wait.h>
#endif

#include <memory>
#include <list>

using namespace imebra;

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


void outputDatasetTags(const DataSet& dataset, const std::wstring& prefix)
{
    imebra::groups_t groups = dataset.getGroups();

    // Output all the tags
    for(imebra::groups_t::const_iterator scanGroups(groups.begin()), endGroups(groups.end());
        scanGroups != endGroups;
        ++scanGroups)
    {
        size_t numGroups = dataset.getGroupsNumber(*scanGroups);

        for(size_t groupNumber(0); groupNumber != numGroups; ++groupNumber)
        {
            tags_t tags = dataset.getGroupTags(*scanGroups, groupNumber);

            for(tags_t::const_iterator scanTags(tags.begin()), endTags(tags.end());
                scanTags != endTags;
                ++scanTags)
            {
                std::wstring tagName = DicomDictionary::getUnicodeTagName(*scanGroups, scanTags->first);
                std::wcout << prefix << L"Tag " << *scanGroups << L"," << scanTags->first << L" (" << tagName << L")" << std::endl;

                for(size_t itemId(0); ; ++itemId)
                {
                    try
                    {
                        DataSet sequence = scanTags->second.getSequenceItemThrow(itemId);
                        std::wcout << prefix << L"  SEQUENCE " << itemId << std::endl;
                        outputDatasetTags(sequence, prefix + L"    ");
                    }
                    catch(const MissingItemError&)
                    {
                        break;
                    }
                }
                for(size_t bufferId(0); bufferId != scanTags->second.getBuffersCount(); ++bufferId)
                {
                    ReadingDataHandler handler = scanTags->second.getReadingDataHandlerRawThrow(bufferId);
                    if(handler.getDataType() != "OW" && handler.getDataType() != "OB")
                    {
                        for(size_t scanHandler(0); scanHandler != handler.getSize(); ++scanHandler)
                        {
                            std::wcout << prefix << L"  buffer " << bufferId << L", position "<< scanHandler << ":" << handler.getUnicodeString(scanHandler) << std::endl;
                        }
                    }
                    else
                    {
                        std::wcout << prefix << L"  Not shown: size " << handler.getSize() << " elements" << std::endl;
                    }

                }


            }


        }

    }
}


int main(int argc, char* argv[])
{
    std::wstring version(L"1.0.0.1");
    std::wcout << L"dicom2jpeg version " << version << std::endl;

    try
    {

        if(argc < 2)
        {
            std::wcout << L"Usage: dicom2jpeg dicomFileName jpegFileName [-ffmpeg FFMPEGPATH FFMPEGOPT]" << std::endl;
            std::wcout << L"dicomFileName        = name of the dicom file" << std::endl;
            std::wcout << L"jpegFileName         = name of the output jpeg file" << std::endl;
            std::wcout << L"-ffmpeg FFMPEGPATH   = launches FFMPEG after generating the jpeg images." << std::endl;
            std::wcout << L" FFMPEGPATH is the path to FFMPEG" << std::endl;
            std::wcout << L" FFMPEGOPT are the options for ffmpeg" << std::endl;
            std::wcout << L" The input images and the frame rate are added automatically to the options" << std::endl;
            return 1;
        }


        // Check for the -ffmpeg flag
        int ffmpegFlag(findArgument("-ffmpeg", argc, argv));
        size_t framesCount(0);

        DataSet loadedDataSet = CodecFactory::load(argv[1], 2048);

        outputDatasetTags(loadedDataSet, L"");

        if(argc < 3)
        {
            return 0;
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

        try
        {
            // Get the first image. We use it in case there isn't any presentation VOI/LUT
            //  and we have to calculate the optimal one
            //////////////////////////////////////////////////////////////////////////////
            Image dataSetImage(loadedDataSet.getImage(0));
            std::uint32_t width = dataSetImage.getSizeX();
            std::uint32_t height = dataSetImage.getSizeY();

            // Build the transforms chain
            /////////////////////////////
            TransformsChain chain;

            chain.addTransform(ModalityVOILUT(loadedDataSet));

            if(ColorTransformsFactory::isMonochrome(dataSetImage.getColorSpace()))
            {
                VOILUT presentationVOILUT(loadedDataSet);
                std::uint32_t firstVOILUTID(presentationVOILUT.getVOILUTId(0));
                if(firstVOILUTID != 0)
                {
                    presentationVOILUT.setVOILUT(firstVOILUTID);
                }
                else
                {
                    // Now find the optimal VOILUT
                    //////////////////////////////
                    presentationVOILUT.applyOptimalVOI(dataSetImage, 0, 0, width, height);
                }
                chain.addTransform(presentationVOILUT);
            }

            // Get the colorspace of the transformation output
            //////////////////////////////////////////////////
            std::string initialColorSpace;
            if(chain.isEmpty())
            {
                initialColorSpace = dataSetImage.getColorSpace();
            }
            else
            {
                Image startImage(chain.allocateOutputImage(dataSetImage, 1, 1));
                initialColorSpace = startImage.getColorSpace();
            }

            /*
            Transform bw = ColorTransformsFactory::getTransform("YBR_FULL", "MONOCHROME2");
            Image bwImage = bw.allocateOutputImage(dataSetImage, width, height);
            bw.runTransform(dataSetImage, 0, 0, width, height, bwImage, 0, 0);
            dataSetImage = bwImage;
            initialColorSpace = "MONOCHROME2";
            */

            // Color transform to YCrCb
            ///////////////////////////
            if(initialColorSpace != "YBR_FULL")
            {
                Transform colorTransform(ColorTransformsFactory::getTransform(initialColorSpace, "YBR_FULL"));
                if(!colorTransform.isEmpty())
                {
                    chain.addTransform((colorTransform));
                }
            }

            Image finalImage;
            finalImage.create(width, height, Image::bitDepth::depthU8, "YBR_FULL", 7);

            // Scan through the frames
            //////////////////////////
            for(std::uint32_t frameNumber(0); ; ++frameNumber)
            {
                if(frameNumber != 0)
                {
                    dataSetImage = loadedDataSet.getImageApplyModalityTransform(frameNumber);
                }

                if(frameNumber == 0 && (dataSetImage.getDepth() != finalImage.getDepth() || dataSetImage.getHighBit() != finalImage.getHighBit()))
                {
                    chain.addTransform(TransformHighBit());
                }

                if(!chain.isEmpty())
                {
                    chain.runTransform(dataSetImage, 0, 0, width, height, finalImage, 0, 0);
                }
                else
                {
                    finalImage = dataSetImage;
                }

                // Open a stream for the jpeg
                const std::string jpegTransferSyntax("1.2.840.10008.1.2.4.50");
                std::ostringstream jpegFileName;
                jpegFileName << outputFileName;
                if(frameNumber != 0 || ffmpegFlag >= 0)
                {
                    jpegFileName << "_" << frameNumber;
                }
                jpegFileName << extension;

                FileStreamOutput writeJpeg;
                writeJpeg.openFile(jpegFileName.str());
                StreamWriter writer(writeJpeg);
                CodecFactory::saveImage(writer, finalImage, jpegTransferSyntax, imageQuality_t::high, "OB", 8, false, false, true, false);

                ++framesCount;
            }



        }
        catch(DataSetImageDoesntExistError)
        {
            // Ignore this exception. It is thrown when we reach the
            //  end of the images list
            //exceptionsManager::getMessage();
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
            double frameTime(loadedDataSet.getDouble(0x0018, 0, 0x1063, 0, 0, 0));
            if(frameTime > 0.1)
            {
                framesPerSecond = 1000 / frameTime;
            }
            if(framesPerSecond < 0.1)
            {
                framesPerSecond = loadedDataSet.getUnsignedLong(0x0018, 0x0, 0x0040, 0x0, 0, 0);
            }
            if(framesPerSecond < 0.1)
            {
                framesPerSecond = loadedDataSet.getUnsignedLong(0x0008, 0x0, 0x2144, 0x0, 0, 0);
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
        //std::wcout << exceptionsManager::getMessage();
        return 1;
    }
}

