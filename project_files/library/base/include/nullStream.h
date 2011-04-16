/*
$fileHeader$
*/

/*! \file nullStream.h
    \brief Declaration of the nullStream class.

*/

#if !defined(imebraNullStream_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_)
#define imebraNullStream_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_

#include "baseStream.h"

///////////////////////////////////////////////////////////
//
// Everything is in the namespace puntoexe
//
///////////////////////////////////////////////////////////
namespace puntoexe
{

/// \addtogroup group_baseclasses
///
/// @{

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This class derives from the baseStream 
///         class and implements a null stream.
///
/// The null stream doesn't write or read anything: it's
///  just used to update the position counter.
/// The null stream can be used to calculate the tags
///  offsets before they are written to the definitive
///  stream.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class nullStream : public baseStream
{

public:
	///////////////////////////////////////////////////////////
	//
	// Virtual stream's functions
	//
	///////////////////////////////////////////////////////////
	virtual void write(imbxUint32, const imbxUint8*, imbxUint32){}
	virtual imbxUint32 read(imbxUint32 , imbxUint8* , imbxUint32 ){return 0;}
};

///@}

} // namespace puntoexe

#endif // !defined(imebraNullStream_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_)
