/*
$fileHeader$
*/

/*! \file baseStreamOutput.cpp
    \brief Implementation of the the base class for the streams (memory, file, ...).
*/

#include "../include/imebra/baseStreamOutput.h"
#include "../implementation/baseStreamImpl.h"
#include "../implementation/exceptionImpl.h"

namespace imebra
{

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

}
