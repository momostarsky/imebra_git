/*
$fileHeader$
*/

/*! \file baseStreamInput.cpp
    \brief Implementation of the the base class for the input streams (memory, file, ...).
*/

#include "../include/imebra/baseStreamInput.h"
#include "../implementation/baseStreamImpl.h"
#include "../implementation/exceptionImpl.h"

namespace imebra
{

BaseStreamInput::BaseStreamInput(std::shared_ptr<implementation::baseStreamInput> pStream): m_pStream(pStream)
{
}

BaseStreamInput::~BaseStreamInput()
{
}

}
