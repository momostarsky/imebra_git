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

StreamWriter::StreamWriter(const BaseStreamOutput& stream, int virtualStart, int virtualLength): m_pWriter(std::make_shared<puntoexe::streamWriter>(stream.m_pStream, virtualStart, virtualLength))
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
