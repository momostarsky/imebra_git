/*
$fileHeader$
*/

/*! \file stream_swig.h
    \brief Implementation of the stream class for SWIG.

*/

#include "../include/stream_swig.h"

imebraStream::imebraStream(): imebraBaseStream(new puntoexe::stream)
{
}

imebraStream::imebraStream(const imebraStream& right): imebraBaseStream(right.m_pStream)
{
}

imebraStream& imebraStream::operator=(const imebraStream& right)
{
	m_pStream = right.m_pStream;
	return *this;
}

void imebraStream::openFile(const std::wstring& name, const int mode)
{
	(dynamic_cast<puntoexe::stream*>(m_pStream.get()))->openFile(name, mode);
}


