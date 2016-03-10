/*
$fileHeader$
*/

/*! \file fileStreamInput.cpp
    \brief Implementation of the file input stream class.

*/

#include "../include/imebra/fileStreamInput.h"
#include "../implementation/fileStreamImpl.h"

namespace imebra
{

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
