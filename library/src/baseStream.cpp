/*
$fileHeader$
*/

/*! \file baseStream_swig.cpp
    \brief Implementation of the the base class for the streams (memory, file, ...)
			for SWIG.
*/

#include "../include/imebra/baseStream.h"
#include "../implementation/baseStreamImpl.h"

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

BaseStreamOutput& BaseStreamOutput::operator=(const BaseStreamOutput& right)
{
	m_pStream = right.m_pStream;
	return *this;
}


BaseStreamInput::BaseStreamInput()
{}

BaseStreamInput::BaseStreamInput(std::shared_ptr<implementation::baseStreamInput> pStream): m_pStream(pStream)
{
}

BaseStreamInput::BaseStreamInput(const BaseStreamInput& right): m_pStream(right.m_pStream)
{
}

BaseStreamInput& BaseStreamInput::operator=(const BaseStreamInput& right)
{
    m_pStream = right.m_pStream;
    return *this;
}

}
