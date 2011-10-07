/*
$fileHeader$
*/

/*! \file streamReader_swig.h
	\brief Declaration of the the class used to read the streams for SWIG.

*/

#if !defined(imebraStreamReader_SWIG_F6221390_BC44_4B83_B5BB_3485222FF1DD__INCLUDED_)
#define imebraStreamReader_SWIG_F6221390_BC44_4B83_B5BB_3485222FF1DD__INCLUDED_

#ifndef SWIG
#include "../../base/include/streamReader.h"
#include "baseStream.h"
#endif

class codecFactory;

class streamReader
{
	friend class codecFactory;
public:
	streamReader(const baseStream& stream, unsigned long virtualStart = 0, unsigned long virtualLength = 0);

#ifndef SWIG
protected:
	puntoexe::ptr<puntoexe::streamReader> m_pReader;
#endif
};

#endif // !defined(imebraStreamReader_SWIG_F6221390_BC44_4B83_B5BB_3485222FF1DD__INCLUDED_)
