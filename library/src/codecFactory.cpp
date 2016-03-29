/*
$fileHeader$
*/

/*! \file codecFactory.cpp
	\brief Implementation of the class used to retrieve the codec able to
        handle the requested transfer syntax.

*/

#include "../include/imebra/fileStreamInput.h"
#include "../include/imebra/fileStreamOutput.h"
#include "../include/imebra/codecFactory.h"
#include "../include/imebra/definitions.h"

#include "../implementation/dicomCodecImpl.h"
#include "../implementation/jpegCodecImpl.h"
#include "../implementation/codecFactoryImpl.h"
#include "../implementation/codecImpl.h"
#include "../implementation/exceptionImpl.h"

namespace imebra
{

DataSet CodecFactory::load(StreamReader& reader, size_t maxSizeBufferLoad /*  = std::numeric_limits<size_t>::max()) */)
{
    IMEBRA_FUNCTION_START();

    std::shared_ptr<imebra::implementation::codecs::codecFactory> factory(imebra::implementation::codecs::codecFactory::getCodecFactory());
    return DataSet(factory->load(reader.m_pReader, (std::uint32_t)maxSizeBufferLoad));

    IMEBRA_FUNCTION_END();
}

DataSet CodecFactory::load(const std::wstring& fileName, size_t maxSizeBufferLoad)
{
    IMEBRA_FUNCTION_START();

    FileStreamInput file;
    file.openFile(fileName);

    StreamReader reader(file);
    return load(reader, maxSizeBufferLoad);

    IMEBRA_FUNCTION_END();
}

DataSet CodecFactory::load(const std::string& fileName, size_t maxSizeBufferLoad)
{
    IMEBRA_FUNCTION_START();

    FileStreamInput file;
    file.openFile(fileName);

    StreamReader reader(file);
    return load(reader, maxSizeBufferLoad);

    IMEBRA_FUNCTION_END();
}

void CodecFactory::saveImage(
        StreamWriter& destStream,
        const Image& sourceImage,
        const std::string& transferSyntax,
        imageQuality_t imageQuality,
        tagVR_t dataType,
        std::uint32_t allocatedBits,
        bool bSubSampledX,
        bool bSubSampledY,
        bool bInterleaved,
        bool b2Complement)
{
    IMEBRA_FUNCTION_START();

    std::shared_ptr<imebra::implementation::codecs::codecFactory> factory(imebra::implementation::codecs::codecFactory::getCodecFactory());
    std::shared_ptr<implementation::codecs::codec> pCodec = factory->getCodec(transferSyntax);
    pCodec->setImage(destStream.m_pWriter, sourceImage.m_pImage, transferSyntax, imageQuality, dataType, allocatedBits, bSubSampledX, bSubSampledY, bInterleaved, b2Complement);

    IMEBRA_FUNCTION_END();
}


void CodecFactory::save(const DataSet& dataSet, StreamWriter& writer, codecType_t codecType)
{
    IMEBRA_FUNCTION_START();

    std::shared_ptr<imebra::implementation::codecs::codec> codec;

    switch(codecType)
    {
    case codecType_t::jpeg:
        codec = std::make_shared<imebra::implementation::codecs::jpegCodec>();
        break;
    default:
        codec = std::make_shared<imebra::implementation::codecs::dicomCodec>();
        break;
    }

    codec->write(writer.m_pWriter, dataSet.m_pDataSet);

    IMEBRA_FUNCTION_END();
}

void CodecFactory::save(const DataSet &dataSet, const std::wstring& fileName, codecType_t codecType)
{
    IMEBRA_FUNCTION_START();

    FileStreamOutput file;
    file.openFile(fileName);

    StreamWriter writer(file);
    CodecFactory::save(dataSet, writer, codecType);

    IMEBRA_FUNCTION_END();
}

void CodecFactory::save(const DataSet &dataSet, const std::string& fileName, codecType_t codecType)
{
    IMEBRA_FUNCTION_START();

    FileStreamOutput file;
    file.openFile(fileName);

    StreamWriter writer(file);
    CodecFactory::save(dataSet, writer, codecType);

    IMEBRA_FUNCTION_END();
}


}
