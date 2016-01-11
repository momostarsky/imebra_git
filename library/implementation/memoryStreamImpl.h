/*
$fileHeader$
*/

/*! \file memoryStream.h
    \brief Declaration of the memoryStream class.

*/

#if !defined(imebraMemoryStream_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_)
#define imebraMemoryStream_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_

#include "baseStreamImpl.h"
#include "memoryImpl.h"

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
///         class and implements a memory stream.
///
/// This class can be used to read/write on the allocated
///  memory.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class memoryStreamInput : public baseStreamInput
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
    memoryStreamInput(std::shared_ptr<const memory> memoryStream);

	///////////////////////////////////////////////////////////
	//
	// Virtual stream's functions
	//
	///////////////////////////////////////////////////////////
	virtual std::uint32_t read(std::uint32_t startPosition, std::uint8_t* pBuffer, std::uint32_t bufferLength);

protected:
    std::shared_ptr<const memory> m_memory;
};

class memoryStreamOutput : public baseStreamOutput
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
    memoryStreamOutput(std::shared_ptr<memory> memoryStream);

    ///////////////////////////////////////////////////////////
    //
    // Virtual stream's functions
    //
    ///////////////////////////////////////////////////////////
    virtual void write(std::uint32_t startPosition, const std::uint8_t* pBuffer, std::uint32_t bufferLength);

protected:
    std::shared_ptr<memory> m_memory;
};


///@}

} // namespace puntoexe

#endif // !defined(imebraMemoryStream_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_)
