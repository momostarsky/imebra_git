/*
$fileHeader$
*/

/*! \file memoryStream.h
    \brief Declaration of the memoryStream class.

*/

#if !defined(imebraMemoryStream_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_)
#define imebraMemoryStream_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_

#include "baseStream.h"
#include "memory.h"

/// \addtogroup group_baseclasses
///
/// @{

///////////////////////////////////////////////////////////
//
// Everything is in the namespace puntoexe
//
///////////////////////////////////////////////////////////
namespace puntoexe
{

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This class derives from the baseStream 
///         class and implements a memory stream.
///
/// This class can be used to read/write on the allocated
///  memory.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class memoryStream : public baseStream
{

public:
	/// \brief Construct a memoryStream object and attach a
	///         memory object to it.
	///
	/// The attached memory object will be resized if new data
	///  is written and its size is too small.
	///
	/// @param memoryStream the memory object to be used by
	///                      the memoryStream object.
	///
	///////////////////////////////////////////////////////////
	memoryStream(ptr<memory> memoryStream);

	///////////////////////////////////////////////////////////
	//
	// Virtual stream's functions
	//
	///////////////////////////////////////////////////////////
	virtual void write(imbxUint32 startPosition, const imbxUint8* pBuffer, imbxUint32 bufferLength);
	virtual imbxUint32 read(imbxUint32 startPosition, imbxUint8* pBuffer, imbxUint32 bufferLength);

protected:
	ptr<memory> m_memory;
};

} // namespace puntoexe

///@}

#endif // !defined(imebraMemoryStream_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_)
