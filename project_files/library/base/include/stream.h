/*
$fileHeader$
*/

/*! \file stream.h
    \brief Declaration of the stream class.

*/

#if !defined(imebraStream_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_)
#define imebraStream_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_

#include "baseStream.h"

#include <ios>
#include <stdio.h>

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
///         class and implements a file stream.
///
/// This class can be used to read/write on physical files
///  in the mass storage.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class stream : public baseStream
{
protected:
	// Destructor
	///////////////////////////////////////////////////////////
	virtual ~stream();

public:
	// Constructor
	///////////////////////////////////////////////////////////
	stream(): m_openFile(0){}

	/// \brief Open a file.
	///
	/// The function uses the standard library function
	///  fopen to open the specified file.
	///
	/// The created file object will be automatically
	///  closed and destroyed when one of the following events
	///  will occur:
	/// - the stream class will be destroyed
	/// - this function will be called again
	///
	/// @param fileName the name of the file to be opened
	/// @param mode     the opening mode.
	///                 Can be the combination of one or
	///                 more of the following values:
	///                 - ios_base::in the file will be opened
	///                   for reading operations
	///                 - ios_base::out the file will be
	///                   opened for writing operations
	///                 - ios_base::app the writing operations
	///                   will append data to the existing file
	///                 - ios_base::trunc the existing file
	///                   will be truncated to zero length
	///                 - ios_base::binary the file will be
	///                   opened in binary mode. Please note
	///                   that this flag is useless, since all
	///                   the files ARE OPENED IN BINARY MODE.
	///
	///////////////////////////////////////////////////////////
	void openFile(const std::string& fileName, const int mode);

	void openFile(const std::wstring& fileName, const int mode);

	///////////////////////////////////////////////////////////
	//
	// Virtual stream's functions
	//
	///////////////////////////////////////////////////////////
	virtual void write(imbxUint32 startPosition, const imbxUint8* pBuffer, imbxUint32 bufferLength);
	virtual imbxUint32 read(imbxUint32 startPosition, imbxUint8* pBuffer, imbxUint32 bufferLength);

protected:
	FILE* m_openFile;
};

///@}

} // namespace puntoexe


#endif // !defined(imebraStream_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_)
