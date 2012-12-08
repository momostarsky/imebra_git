/*
$fileHeader$
*/

/*! \file stream_swig.cpp
    \brief Implementation of the stream class for SWIG.

*/

#include "../include/stream_swig.h"
#include "../include/exceptions_swig.h"

stream::stream(): baseStream(new puntoexe::stream)
{
}

stream::stream(const stream& right): baseStream(right.m_pStream)
{
}

stream& stream::operator=(const stream& right)
{
	m_pStream = right.m_pStream;
	return *this;
}

void stream::openFile(const std::wstring& name, const int mode)
{
	try
	{
		(dynamic_cast<puntoexe::stream*>(m_pStream.get()))->openFile(name, mode);
	}
	CATCH_IMEBRA_EXCEPTIONS;
}


