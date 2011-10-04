/*
$fileHeader$
*/

/*! \file codecFactory_swig.cpp
	\brief Implementation of the class used to retrieve the codec able to
	        handle the requested transfer syntax.

*/

#include "../include/codecFactory_swig.h"

imebraDataSet imebraCodecFactory::load(imebraStreamReader reader, unsigned long maxSizeBufferLoad)
{
	puntoexe::ptr<puntoexe::imebra::codecs::codecFactory> factory(puntoexe::imebra::codecs::codecFactory::getCodecFactory());
	return imebraDataSet(factory->load(reader.m_pReader, maxSizeBufferLoad));
}
