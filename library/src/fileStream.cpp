/*
$fileHeader$
*/

/*! \file stream_swig.cpp
    \brief Implementation of the stream class for SWIG.

*/

#include "../include/imebra/fileStream.h"
#include "../implementation/fileStreamImpl.h"

namespace imebra
{

FileStreamOutput::FileStreamOutput(): BaseStreamOutput(std::make_shared<implementation::fileStreamOutput>())
{
}

FileStreamOutput::FileStreamOutput(const FileStreamOutput& right): BaseStreamOutput(right.m_pStream)
{
}

FileStreamOutput& FileStreamOutput::operator=(const FileStreamOutput& right)
{
	m_pStream = right.m_pStream;
	return *this;
}

void FileStreamOutput::openFile(const std::wstring& name)
{
    (dynamic_cast<implementation::fileStreamOutput*>(m_pStream.get()))->openFile(name);
}

void FileStreamOutput::openFile(const std::string& name)
{
    (dynamic_cast<implementation::fileStreamOutput*>(m_pStream.get()))->openFile(name);
}

void FileStreamOutput::close()
{
    static_cast<implementation::fileStreamOutput*>(m_pStream.get())->close();
}


FileStreamInput::FileStreamInput(): BaseStreamInput(std::make_shared<implementation::fileStreamInput>())
{
}

FileStreamInput::FileStreamInput(const FileStreamInput& right): BaseStreamInput(right.m_pStream)
{
}

FileStreamInput& FileStreamInput::operator=(const FileStreamInput& right)
{
    m_pStream = right.m_pStream;
    return *this;
}

void FileStreamInput::openFile(const std::wstring& name)
{
    (dynamic_cast<implementation::fileStreamInput*>(m_pStream.get()))->openFile(name);
}

void FileStreamInput::openFile(const std::string& name)
{
    (dynamic_cast<implementation::fileStreamInput*>(m_pStream.get()))->openFile(name);
}

void FileStreamInput::close()
{
    static_cast<implementation::fileStreamInput*>(m_pStream.get())->close();
}


}
