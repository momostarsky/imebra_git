/*
$fileHeader$
*/

/*! \file streamWriter.cpp
    \brief Implementation of the the class used to write the streams.

*/

#include "../include/imebra/streamWriter.h"
#include "../include/imebra/baseStreamOutput.h"

#include "../implementation/streamWriterImpl.h"

namespace imebra
{

StreamWriter::StreamWriter(std::shared_ptr<implementation::streamWriter> pWriter): m_pWriter(pWriter)
{
}

StreamWriter::StreamWriter(const BaseStreamOutput& stream): m_pWriter(std::make_shared<implementation::streamWriter>(stream.m_pStream))
{
}

StreamWriter::StreamWriter(const BaseStreamOutput& stream, size_t virtualStart, size_t virtualLength): m_pWriter(std::make_shared<implementation::streamWriter>(stream.m_pStream, virtualStart, virtualLength))
{
}

}
