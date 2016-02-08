/*
$fileHeader$
*/

/*! \file codecFactory_swig.cpp
	\brief Implementation of the class used to retrieve the codec able to
		handle the requested transfer syntax (SWIG).

*/

#include <imebra/codecFactory.h>
#include <imebra/fileStream.h>
#include <imebra/definitions.h>

#include "../implementation/dicomCodecImpl.h"
#include "../implementation/jpegCodecImpl.h"
#include "../implementation/codecFactoryImpl.h"
#include "../implementation/codecImpl.h"

namespace imebra
{

DataSet CodecFactory::load(StreamReader& reader, size_t maxSizeBufferLoad)
{
    std::shared_ptr<imebra::implementation::codecs::codecFactory> factory(imebra::implementation::codecs::codecFactory::getCodecFactory());
    return DataSet(factory->load(reader.m_pReader, (std::uint32_t)maxSizeBufferLoad));
}

DataSet CodecFactory::load(const std::wstring& fileName, size_t maxSizeBufferLoad)
{
    FileStreamInput file;
    file.openFile(fileName);

    StreamReader reader(file);
    return load(reader, maxSizeBufferLoad);
}

DataSet CodecFactory::load(const std::string& fileName, size_t maxSizeBufferLoad)
{
    FileStreamInput file;
    file.openFile(fileName);

    StreamReader reader(file);
    return load(reader, maxSizeBufferLoad);
}

void CodecFactory::saveImage(
        StreamWriter& destStream,
        const Image& sourceImage,
        const std::string& transferSyntax,
        imageQuality_t imageQuality,
        const std::string& dataType,
        std::uint32_t allocatedBits,
        bool bSubSampledX,
        bool bSubSampledY,
        bool bInterleaved,
        bool b2Complement)
{
    std::shared_ptr<imebra::implementation::codecs::codecFactory> factory(imebra::implementation::codecs::codecFactory::getCodecFactory());
    std::shared_ptr<implementation::codecs::codec> pCodec = factory->getCodec(transferSyntax);
    pCodec->setImage(destStream.m_pWriter, sourceImage.m_pImage, transferSyntax, (imebra::implementation::codecs::codec::quality)imageQuality, dataType, allocatedBits, bSubSampledX, bSubSampledY, bInterleaved, b2Complement);

}


void CodecFactory::save(const DataSet& dataSet, StreamWriter& writer, codecType codecType)
{
    std::shared_ptr<imebra::implementation::codecs::codec> codec;

    switch(codecType)
    {
    case jpeg:
        codec = std::make_shared<imebra::implementation::codecs::jpegCodec>();
        break;
    default:
        codec = std::make_shared<imebra::implementation::codecs::dicomCodec>();
        break;
    }

    codec->write(writer.m_pWriter, dataSet.m_pDataSet);
}

void CodecFactory::save(const DataSet &dataSet, const std::wstring& fileName, codecType codecType)
{
    FileStreamOutput file;
    file.openFile(fileName);

    StreamWriter writer(file);
    CodecFactory::save(dataSet, writer, codecType);
}

void CodecFactory::save(const DataSet &dataSet, const std::string& fileName, codecType codecType)
{
    FileStreamOutput file;
    file.openFile(fileName);

    StreamWriter writer(file);
    CodecFactory::save(dataSet, writer, codecType);
}


}
