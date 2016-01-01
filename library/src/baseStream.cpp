/*
$fileHeader$
*/

/*! \file baseStream_swig.cpp
    \brief Implementation of the the base class for the streams (memory, file, ...)
			for SWIG.
*/

#include "../include/imebra/baseStream.h"
#include "../implementation/baseStreamImpl.h"

namespace imebra
{

BaseStreamWriter::BaseStreamWriter()
{}

BaseStreamWriter::BaseStreamWriter(std::shared_ptr<puntoexe::baseStreamWriter> pStream): m_pStream(pStream)
{
}

BaseStreamWriter::BaseStreamWriter(const BaseStreamWriter& right): m_pStream(right.m_pStream)
{
}

BaseStreamWriter& BaseStreamWriter::operator=(const BaseStreamWriter& right)
{
	m_pStream = right.m_pStream;
	return *this;
}


BaseStreamReader::BaseStreamReader()
{}

BaseStreamReader::BaseStreamReader(std::shared_ptr<puntoexe::baseStreamReader> pStream): m_pStream(pStream)
{
}

BaseStreamReader::BaseStreamReader(const BaseStreamReader& right): m_pStream(right.m_pStream)
{
}

BaseStreamReader& BaseStreamReader::operator=(const BaseStreamReader& right)
{
    m_pStream = right.m_pStream;
    return *this;
}

}
