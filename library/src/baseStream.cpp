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

BaseStream::BaseStream()
{}

BaseStream::BaseStream(std::shared_ptr<puntoexe::baseStream> pStream): m_pStream(pStream)
{
}

BaseStream::BaseStream(const BaseStream& right): m_pStream(right.m_pStream)
{
}

BaseStream& BaseStream::operator=(const BaseStream& right)
{
	m_pStream = right.m_pStream;
	return *this;
}

}
