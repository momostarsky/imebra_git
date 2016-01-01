/*
$fileHeader$
*/

/*! \file stream_swig.cpp
    \brief Implementation of the stream class for SWIG.

*/

#include "../include/imebra/stream.h"
#include "../implementation/streamImpl.h"

namespace imebra
{

FileStreamWriter::FileStreamWriter(): BaseStreamWriter(std::make_shared<puntoexe::fileStreamWriter>())
{
}

FileStreamWriter::FileStreamWriter(const FileStreamWriter& right): BaseStreamWriter(right.m_pStream)
{
}

FileStreamWriter& FileStreamWriter::operator=(const FileStreamWriter& right)
{
	m_pStream = right.m_pStream;
	return *this;
}

void FileStreamWriter::openFile(const std::wstring& name)
{
    (dynamic_cast<puntoexe::fileStreamWriter*>(m_pStream.get()))->openFile(name);
}

void FileStreamWriter::openFile(const std::string& name)
{
    (dynamic_cast<puntoexe::fileStreamWriter*>(m_pStream.get()))->openFile(name);
}

void FileStreamWriter::close()
{
    static_cast<puntoexe::fileStreamWriter*>(m_pStream.get())->close();
}


FileStreamReader::FileStreamReader(): BaseStreamReader(std::make_shared<puntoexe::fileStreamReader>())
{
}

FileStreamReader::FileStreamReader(const FileStreamReader& right): BaseStreamReader(right.m_pStream)
{
}

FileStreamReader& FileStreamReader::operator=(const FileStreamReader& right)
{
    m_pStream = right.m_pStream;
    return *this;
}

void FileStreamReader::openFile(const std::wstring& name)
{
    (dynamic_cast<puntoexe::fileStreamReader*>(m_pStream.get()))->openFile(name);
}

void FileStreamReader::openFile(const std::string& name)
{
    (dynamic_cast<puntoexe::fileStreamReader*>(m_pStream.get()))->openFile(name);
}

void FileStreamReader::close()
{
    static_cast<puntoexe::fileStreamReader*>(m_pStream.get())->close();
}


}
