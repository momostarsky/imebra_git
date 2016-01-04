/*
$fileHeader$
*/

/*! \file codecFactory_swig.cpp
	\brief Implementation of the class used to retrieve the codec able to
		handle the requested transfer syntax (SWIG).

*/

#include <imebra/codecFactory.h>
#include <imebra/stream.h>

#include "../implementation/dicomCodecImpl.h"
#include "../implementation/jpegCodecImpl.h"
#include "../implementation/codecFactoryImpl.h"

namespace imebra
{

DataSet CodecFactory::load(StreamReader& reader, size_t maxSizeBufferLoad)
{
    std::shared_ptr<puntoexe::imebra::codecs::codecFactory> factory(puntoexe::imebra::codecs::codecFactory::getCodecFactory());
    return DataSet(factory->load(reader.m_pReader, maxSizeBufferLoad));
}

DataSet CodecFactory::load(const std::wstring& fileName, size_t maxSizeBufferLoad)
{
    FileStreamReader file;
    file.openFile(fileName);

    StreamReader reader(file);
    return load(reader, maxSizeBufferLoad);
}

DataSet CodecFactory::load(const std::string& fileName, size_t maxSizeBufferLoad)
{
    FileStreamReader file;
    file.openFile(fileName);

    StreamReader reader(file);
    return load(reader, maxSizeBufferLoad);
}


void CodecFactory::save(const DataSet& dataSet, StreamWriter& writer, codecType codecType)
{
    std::shared_ptr<puntoexe::imebra::codecs::codec> codec;

    switch(codecType)
    {
    case jpeg:
        codec = std::make_shared<puntoexe::imebra::codecs::jpegCodec>();
        break;
    default:
        codec = std::make_shared<puntoexe::imebra::codecs::dicomCodec>();
        break;
    }

    codec->write(writer.m_pWriter, dataSet.m_pDataSet);
}

void CodecFactory::save(const DataSet &dataSet, const std::wstring& fileName, codecType codecType)
{
    FileStreamWriter file;
    file.openFile(fileName);

    StreamWriter writer(file);
    CodecFactory::save(dataSet, writer, codecType);
}

void CodecFactory::save(const DataSet &dataSet, const std::string& fileName, codecType codecType)
{
    FileStreamWriter file;
    file.openFile(fileName);

    StreamWriter writer(file);
    CodecFactory::save(dataSet, writer, codecType);
}


}
