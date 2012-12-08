/*
$fileHeader$
*/

/*! \file codecFactory_swig.cpp
	\brief Implementation of the class used to retrieve the codec able to
		handle the requested transfer syntax (SWIG).

*/

#include "../include/exceptions_swig.h"
#include "../include/codecFactory_swig.h"

dataSet codecFactory::load(streamReader reader, unsigned long maxSizeBufferLoad)
{
	try
	{
		puntoexe::ptr<puntoexe::imebra::codecs::codecFactory> factory(puntoexe::imebra::codecs::codecFactory::getCodecFactory());
		return dataSet(factory->load(reader.m_pReader, maxSizeBufferLoad));
	}
	CATCH_IMEBRA_EXCEPTIONS;
}
