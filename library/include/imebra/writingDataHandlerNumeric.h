/*
$fileHeader$
*/

/// \file writingDataHandlerNumeric.h
/// \brief Declaration of the class WritingDataHandlerNumeric.
///
///////////////////////////////////////////////////////////////////////////////

#if !defined(imebraWritingDataHandlerNumeric__INCLUDED_)
#define imebraWritingDataHandlerNumeric__INCLUDED_

#include <string>
#include <memory>
#include "definitions.h"
#include "readWriteMemory.h"
#include "writingDataHandler.h"

#ifndef SWIG

namespace imebra
{
namespace implementation
{
namespace handlers
{
class writingDataHandlerNumericBase;
}
}
}

#endif


namespace imebra
{

///
/// \brief Specialized WritingDataHandler for numeric data types.
///
/// Includes few methods that allow to access the raw memory containing the
/// buffer's data.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API WritingDataHandlerNumeric: public WritingDataHandler
{
#ifndef SWIG
    friend class Image;
    friend class DataSet;
    friend class Tag;
private:
    WritingDataHandlerNumeric(std::shared_ptr<imebra::implementation::handlers::writingDataHandlerNumericBase> pDataHandler);
#endif

public:
    /// \brief Copy constructor.
    ///
    /// The new WritingDataHandlerNumeric will handle the same content
    /// handled by the source WritingDataHandlerNumeric.
    ///
    /// \param right the source WritingDataHandlerNumeric
    ///
    ///////////////////////////////////////////////////////////////////////////////
    WritingDataHandlerNumeric(const WritingDataHandlerNumeric& right);

    /// \brief Copy operator.
    ///
    /// The WritingDataHandlerNumeric object will handle the same content
    /// handled by the source WritingDataHandlerNumeric.
    ///
    /// \param right the source WritingDataHandlerNumeric
    /// \return a reference to this object
    ///
    ///////////////////////////////////////////////////////////////////////////////
    WritingDataHandlerNumeric& operator=(const WritingDataHandlerNumeric& right);

    /// \brief Return a ReadWriteMemory object referencing the raw buffer's data.
    ///
    /// \return a ReadWriteMemory object referencing the raw buffer's data
    ///
    ///////////////////////////////////////////////////////////////////////////////
    ReadWriteMemory getMemory() const;

    /// \brief Copy the content of the specified buffer into the content managed
    ///        by data handler.
    ///
    /// \param source     a pointer to the source memory buffer
    /// \param sourceSize the number of bytes to copy and the new memory size
    ///
    ///////////////////////////////////////////////////////////////////////////////
    void assign(const char* source, size_t sourceSize);

#ifndef SWIG
    /// \brief Returns a pointer to the buffer's raw memory content.
    ///
    /// \param pDataSize a variable that will contain the raw memory's size in
    ///                  bytes
    /// \return a pointer to the buffer's raw memory
    ///
    ///////////////////////////////////////////////////////////////////////////////
    char* data(size_t* pDataSize) const;
#endif

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

    /// \brief Returns the number of bytes occupied by the numbers handled by the
    ///        data handler
    ///
    /// \return the number of bytes occupied by the numbers handled by the data
    ///         handler
    ///
    ///////////////////////////////////////////////////////////////////////////////
    size_t getUnitSize() const;

    /// \brief Returns true if the numbers handled by the data handler are signed,
    ///        false otherwise.
    ///
    /// \return true if the numbers handled by the data handler are signed, false
    ///         otherwise
    ///
    ///////////////////////////////////////////////////////////////////////////////
    bool isSigned() const;
};

}

#endif // !defined(imebraWritingDataHandlerNumeric__INCLUDED_)
