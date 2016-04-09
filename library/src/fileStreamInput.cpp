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
