/*
$fileHeader$
*/

/*! \file baseStream_swig.cpp
    \brief Implementation of the the base class for the streams (memory, file, ...)
			for SWIG.
*/

#include "../include/baseStream_swig.h"

baseStream::baseStream()
{}

baseStream::baseStream(puntoexe::ptr<puntoexe::baseStream> pStream): m_pStream(pStream)
{
}

baseStream::baseStream(const baseStream& right): m_pStream(right.m_pStream)
{
}

baseStream& baseStream::operator=(const baseStream& right)
{
	m_pStream = right.m_pStream;
	return *this;
}


