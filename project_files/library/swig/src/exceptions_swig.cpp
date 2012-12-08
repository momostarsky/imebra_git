/*
$fileHeader$
*/

/*! \file exceptions_swig.cpp
    \brief Implementation of the the exception classes for SWIG.
*/

#include "../include/exceptions_swig.h"

imebraException::imebraException(const std::string& message): m_what(message), m_stack(puntoexe::exceptionsManager::getMessage())
{
}

std::string imebraException::what()
{
	return m_what;
}

std::wstring imebraException::stack()
{
	return m_stack;
}

