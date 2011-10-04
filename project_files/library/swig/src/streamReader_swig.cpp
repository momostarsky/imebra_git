/*
$fileHeader$
*/

/*! \file streamReader_swig.cpp
    \brief Implementation of the the class used to read the streams for SWIG.

*/

#include "../include/streamReader_swig.h"

imebraStreamReader::imebraStreamReader(const imebraBaseStream& stream, unsigned long virtualStart, unsigned long virtualLength): m_pReader(new puntoexe::streamReader(stream.m_pStream, virtualStart, virtualLength))
{
}
