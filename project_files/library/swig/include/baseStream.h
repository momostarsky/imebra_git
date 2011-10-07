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

class baseStream
{
#ifndef SWIG
	friend class streamReader;
	friend class streamWriter;
public:
	baseStream(puntoexe::ptr<puntoexe::baseStream> pStream);
	baseStream(const baseStream& right);
	baseStream& operator=(const baseStream& right);
protected:
	puntoexe::ptr<puntoexe::baseStream> m_pStream;
#endif

public:
	baseStream();
};




#endif // !defined(imebraBaseStream_SWIG_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_)
