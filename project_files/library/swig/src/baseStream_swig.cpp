/*
$fileHeader$
*/

/*! \file baseStream_swig.cpp
    \brief Implementation of the the base class for the streams (memory, file, ...)
			for SWIG.
*/

#include "../include/baseStream_swig.h"

imebraBaseStream::imebraBaseStream()
{}

imebraBaseStream::imebraBaseStream(puntoexe::ptr<puntoexe::baseStream> pStream): m_pStream(pStream)
{
}

imebraBaseStream::imebraBaseStream(const imebraBaseStream& right): m_pStream(right.m_pStream)
{
}

imebraBaseStream& imebraBaseStream::operator=(const imebraBaseStream& right)
{
	m_pStream = right.m_pStream;
	return *this;
}


