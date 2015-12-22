/*
$fileHeader$
*/

/*! \file codecFactory_swig.cpp
	\brief Implementation of the class used to retrieve the codec able to
		handle the requested transfer syntax (SWIG).

*/

#include "../include/imebra/codecFactory.h"

#include "../implementation/dicomCodecImpl.h"
#include "../implementation/jpegCodecImpl.h"
#include "../implementation/codecFactoryImpl.h"

namespace imebra
{

DataSet CodecFactory::load(StreamReader reader, size_t maxSizeBufferLoad)
{
    std::shared_ptr<puntoexe::imebra::codecs::codecFactory> factory(puntoexe::imebra::codecs::codecFactory::getCodecFactory());
    return DataSet(factory->load(reader.m_pReader, maxSizeBufferLoad));
}

void CodecFactory::save(DataSet dataSet, StreamWriter writer, codecType codecType)
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

}
