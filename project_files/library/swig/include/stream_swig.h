/*
$fileHeader$
*/

/*! \file stream_swig.h
	\brief Declaration of the stream class for SWIG.

*/

#if !defined(imebraStream_SWIG_146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_)
#define imebraStream_SWIG_146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_

#ifndef SWIG
#include "../../base/include/stream.h"
#endif

#include "../include/baseStream_swig.h"

class imebraStream : public imebraBaseStream
{
public:
	imebraStream();
	imebraStream(const imebraStream& right);
	imebraStream& operator=(const imebraStream& right);

	void openFile(const std::wstring& name, const int mode);

};


#endif // !defined(imebraStream_SWIG_146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_)
