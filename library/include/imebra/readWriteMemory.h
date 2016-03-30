/*
$fileHeader$
*/

/*! \file readWriteMemory.h
    \brief Declaration of the class ReadWriteMemory.

*/

#if !defined(imebraReadWriteMemory__INCLUDED_)
#define imebraReadWriteMemory__INCLUDED_

#include <memory>
#include <string>
#include "definitions.h"
#include "readMemory.h"

#ifndef SWIG

namespace imebra
{
namespace implementation
{
class memory;
}
}
#endif

namespace imebra
{


///
/// \brief Manages a writable buffer of memory.
///
/// The buffer of memory is usually associated with a Tag buffer content.
///
/// ReadMemory and ReadWriteMemory are managed by MemoryPool.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API ReadWriteMemory: public ReadMemory
{

#ifndef SWIG
    friend class MemoryStreamOutput;
    friend class DrawBitmap;
    friend class WritingDataHandlerNumeric;
private:
    ReadWriteMemory(std::shared_ptr<implementation::memory> pMemory);
#endif

public:

    /// \brief Construct an empty buffer of memory.
    ///
    /// The memory can be resized later with resize().
    ///
    ///////////////////////////////////////////////////////////////////////////////
    ReadWriteMemory();

    /// \brief Construct a buffer of memory of the specified size.
    ///
    /// The memory can be resized later with resize().
    ///
    /// \param initialSize the initial memory's size, in bytes
    ///
    ///////////////////////////////////////////////////////////////////////////////
    ReadWriteMemory(size_t initialSize);

    /// \brief Construct a buffer of memory and copy the specified content into it.
    ///
    /// \param buffer      a pointer to the source data
    /// \param bufferSize  the amount of data to copy into the allocated memory
    ///
    ///////////////////////////////////////////////////////////////////////////////
    ReadWriteMemory(const char* buffer, size_t bufferSize);

    /// \brief Copy constructor.
    ///
    /// References the same memory area referenced in the source object
    ///
    /// \param right the source memory object
    ///
    ///////////////////////////////////////////////////////////////////////////////
    ReadWriteMemory(const ReadWriteMemory& right);

    /// \brief Copy operator.
    ///
    /// References the same memory area referenced in the source object.
    ///
    /// \param right the source memory object
    /// \return a reference to this object
    ///
    ///////////////////////////////////////////////////////////////////////////////
    ReadWriteMemory& operator=(const ReadWriteMemory& right);

    /// \brief Copy the content from another memory object.
    ///
    /// \param sourceMemory the source memory object
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void copyFrom(const ReadMemory& sourceMemory);

    /// \brief Resize the memory to zero bytes.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void clear();

    /// \brief Resize the memory.
    ///
    /// \param newSize the new memory size, in bytes
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void resize(size_t newSize);

    /// \brief Reserve the specified amount of bytes, without changing the memory
    ///        size
    ///
    /// \param reserveSize the number of bytes to reserve
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void reserve(size_t reserveSize);

#ifndef SWIG
    /// \brief Return a pointer to the referenced memory.
    ///
    /// \param pDataSize pointer to a variable that will be filled with the
    ///        memory size, in bytes
    /// \return a pointer to the referenced memory
    ///
    ///////////////////////////////////////////////////////////////////////////////
    char* data(size_t* pDataSize) const;
#endif

    /// \brief Copy the content of the specified buffer into the ReadWriteMemory
    ///        object.
    ///
    /// \param source     a pointer to the source memory buffer
    /// \param sourceSize the number of bytes to copy and the new memory size
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void assign(const char* source, size_t sourceSize);
};

}

#endif // !defined(imebraReadWriteMemory__INCLUDED_)
