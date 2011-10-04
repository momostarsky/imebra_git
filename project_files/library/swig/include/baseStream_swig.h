/*
$fileHeader$
*/

/*! \file baseStream_swig.h
    \brief Declaration of the the base class for the streams (memory, file, ...)
			for SWIG.
*/

#if !defined(imebraBaseStream_SWIG_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_)
#define imebraBaseStream_SWIG_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_

#ifndef SWIG
#include "../../base/include/baseStream.h"
#endif

class imebraBaseStream
{
#ifndef SWIG
	friend class imebraStreamReader;
	friend class imebraStreamWriter;
public:
	imebraBaseStream(puntoexe::ptr<puntoexe::baseStream> pStream);
	imebraBaseStream(const imebraBaseStream& right);
	imebraBaseStream& operator=(const imebraBaseStream& right);
protected:
	puntoexe::ptr<puntoexe::baseStream> m_pStream;
#endif
public:
	imebraBaseStream();
};




#endif // !defined(imebraBaseStream_SWIG_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_)
