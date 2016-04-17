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

FileStreamInput::~FileStreamInput()
{
}

FileStreamInput::FileStreamInput(const std::wstring& name): BaseStreamInput(std::make_shared<implementation::fileStreamInput>(name))
{
}

FileStreamInput::FileStreamInput(const std::string& name): BaseStreamInput(std::make_shared<implementation::fileStreamInput>(name))
{
}

}
