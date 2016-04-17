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

FileStreamOutput::FileStreamOutput(const std::wstring& name): BaseStreamOutput(std::make_shared<implementation::fileStreamOutput>(name))
{
}

FileStreamOutput::FileStreamOutput(const std::string& name): BaseStreamOutput(std::make_shared<implementation::fileStreamOutput>(name))
{
}

FileStreamOutput::~FileStreamOutput()
{
}

}
