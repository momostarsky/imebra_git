/*
$fileHeader$
*/

/*! \file streamReader.cpp
    \brief Implementation of the the class used to read the streams.

*/

#include "../include/imebra/streamReader.h"
#include "../include/imebra/baseStreamInput.h"
#include "../implementation/streamReaderImpl.h"

namespace imebra
{

StreamReader::StreamReader(std::shared_ptr<implementation::streamReader> pReader): m_pReader(pReader)
{
}

StreamReader::StreamReader(const BaseStreamInput& stream): m_pReader(std::make_shared<implementation::streamReader>(stream.m_pStream))
{
}


StreamReader::StreamReader(const BaseStreamInput& stream, size_t virtualStart, size_t virtualLength): m_pReader(std::make_shared<implementation::streamReader>(stream.m_pStream, virtualStart, virtualLength))
{
}

StreamReader::StreamReader(const StreamReader& right): m_pReader(right.m_pReader)
{
}

StreamReader::~StreamReader()
{
}

StreamReader& StreamReader::operator=(const StreamReader& right)
{
    m_pReader = right.m_pReader;
    return *this;
}

}
