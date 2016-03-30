/*
$fileHeader$
*/

/*! \file readMemory.h
    \brief Declaration of the class ReadMemory.

*/

#if !defined(imebraReadMemory__INCLUDED_)
#define imebraReadMemory__INCLUDED_

#include <memory>
#include <string>
#include "definitions.h"

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
/// \brief Manages a read-only buffer of memory.
///
/// The buffer of memory is usually associated with a Tag buffer content.
///
/// ReadMemory and ReadWriteMemory are managed by MemoryPool.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API ReadMemory
{

#ifndef SWIG
    friend class MemoryStreamInput;
    friend class ReadWriteMemory;
    friend class ReadingDataHandlerNumeric;
private:
    ReadMemory(std::shared_ptr<const implementation::memory> pMemory);
#endif


public:
    /// \brief Construct an empty buffer of memory.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    ReadMemory();

    /// \brief Construct a buffer of memory and copy the specified content into it.
    ///
    /// \param buffer      a pointer to the source data
    /// \param bufferSize  the amount of data to copy into the allocated memory
    ///
    ///////////////////////////////////////////////////////////////////////////////
    ReadMemory(const char* buffer, size_t bufferSize);

    /// \brief Copy constructor.
    ///
    /// References the same memory area referenced in the source object
    ///
    /// \param right the source memory object
    ///
    ///////////////////////////////////////////////////////////////////////////////
    ReadMemory(const ReadMemory& right);

    virtual ~ReadMemory();

    /// \brief Copy operator.
    ///
    /// References the same memory area referenced in the source object.
    ///
    /// \param right the source memory object
    /// \return a reference to this object
    ///
    ///////////////////////////////////////////////////////////////////////////////
    ReadMemory& operator=(const ReadMemory& right);

    /// \brief Return the memory size, in bytes.
    ///
    /// \return the memory size in bytes
    ///
    ///////////////////////////////////////////////////////////////////////////////
    size_t size() const;

    /// \brief Copies the raw memory content into the specified buffer.
    ///
    /// If the allocated buffer is not large enough then the method doesn't
    ///  copy any data and just returns the required buffer' size.
    ///
    /// \param destination     a pointer to the allocated buffer
    /// \param destinationSize the size of the allocated buffer, in bytes
    /// \return the number of bytes to be copied into the pre-allocated buffer
    ///
    ///////////////////////////////////////////////////////////////////////////////
    size_t data(char* destination, size_t destinationSize) const;

#ifndef SWIG
    /// \brief Return a pointer to the constant referenced memory.
    ///
    /// \param pDataSize pointer to a variable that will be filled with the
    ///        memory size, in bytes
    /// \return a pointer to the referenced memory
    ///
    ///////////////////////////////////////////////////////////////////////////////
    const char* data(size_t* pDataSize) const;
#endif

    /// \brief Return true if the referenced memory is zero bytes long or hasn't
    ///        been allocated yet.
    ///
    /// \true if the referenced memory does not exist or is empty
    ///
    ///////////////////////////////////////////////////////////////////////////////
    bool empty() const;

#ifndef SWIG
protected:
    std::shared_ptr<const implementation::memory> m_pMemory;
#endif
};

}

#endif // !defined(imebraReadMemory__INCLUDED_)
