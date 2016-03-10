/*
$fileHeader$
*/

/*! \file fileStreamOutput.cpp
    \brief Implementation of the file output stream class.

*/

#include "../include/imebra/fileStreamOutput.h"
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
    std::dynamic_pointer_cast<implementation::fileStreamOutput>(m_pStream)->openFile(name);
}

void FileStreamOutput::openFile(const std::string& name)
{
    std::dynamic_pointer_cast<implementation::fileStreamOutput>(m_pStream)->openFile(name);
}

void FileStreamOutput::close()
{
    static_cast<implementation::fileStreamOutput*>(m_pStream.get())->close();
}

}
