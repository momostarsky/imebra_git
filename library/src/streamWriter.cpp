/*
$fileHeader$
*/

/*! \file streamWriter_swig.cpp
    \brief Implementation of the the class used to write the streams for SWIG.

*/

#include "../include/imebra/streamWriter.h"
#include "../include/imebra/baseStream.h"

#include "../implementation/streamWriterImpl.h"

namespace imebra
{

StreamWriter::StreamWriter(std::shared_ptr<implementation::streamWriter> pWriter): m_pWriter(pWriter)
{
}

StreamWriter::StreamWriter(const BaseStreamOutput& stream, size_t virtualStart, size_t virtualLength): m_pWriter(std::make_shared<implementation::streamWriter>(stream.m_pStream, virtualStart, virtualLength))
{
}

StreamWriter::StreamWriter(const StreamWriter& right): m_pWriter(right.m_pWriter)
{
}

StreamWriter& StreamWriter::operator=(const StreamWriter& right)
{
    m_pWriter = right.m_pWriter;
    return *this;
}

}
