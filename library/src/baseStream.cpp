/*
$fileHeader$
*/

/*! \file baseStream.cpp
    \brief Implementation of the the base class for the streams (memory, file, ...).
*/

#include "../include/imebra/baseStream.h"
#include "../implementation/baseStreamImpl.h"
#include "../implementation/exceptionImpl.h"

namespace imebra
{

BaseStreamOutput::BaseStreamOutput()
{}

BaseStreamOutput::BaseStreamOutput(std::shared_ptr<implementation::baseStreamOutput> pStream): m_pStream(pStream)
{
}

BaseStreamOutput::BaseStreamOutput(const BaseStreamOutput& right): m_pStream(right.m_pStream)
{
}

BaseStreamOutput::~BaseStreamOutput()
{
}

BaseStreamOutput& BaseStreamOutput::operator=(const BaseStreamOutput& right)
{
    IMEBRA_FUNCTION_START();

	m_pStream = right.m_pStream;
	return *this;

    IMEBRA_FUNCTION_END();
}


BaseStreamInput::BaseStreamInput()
{}

BaseStreamInput::BaseStreamInput(std::shared_ptr<implementation::baseStreamInput> pStream): m_pStream(pStream)
{
}

BaseStreamInput::BaseStreamInput(const BaseStreamInput& right): m_pStream(right.m_pStream)
{
}

BaseStreamInput::~BaseStreamInput()
{
}

BaseStreamInput& BaseStreamInput::operator=(const BaseStreamInput& right)
{
    IMEBRA_FUNCTION_START();

    m_pStream = right.m_pStream;
    return *this;

    IMEBRA_FUNCTION_END();
}

}
