/*
$fileHeader$
*/

/// \file readingDataHandlerNumeric.h
/// \brief Declaration of the class ReadingDataHandler and
///        WritingDataHandler.
///
///////////////////////////////////////////////////////////////////////////////

#if !defined(imebraReadingDataHandlerNumeric__INCLUDED_)
#define imebraReadingDataHandlerNumeric__INCLUDED_

#include <string>
#include <memory>
#include "definitions.h"
#include "readMemory.h"
#include "readingDataHandler.h"

#ifndef SWIG

namespace imebra
{
namespace implementation
{
namespace handlers
{
class readingDataHandlerNumericBase;
}
}
}

#endif


namespace imebra
{

///
/// \brief Specialized ReadingDataHandler for numeric data types.
///
/// Includes few methods that allow to access the raw memory containing the
/// buffer's data.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API ReadingDataHandlerNumeric: public ReadingDataHandler
{
    ReadingDataHandlerNumeric(const ReadingDataHandlerNumeric&) = delete;
    ReadingDataHandlerNumeric& operator=(const ReadingDataHandlerNumeric&) = delete;

public:
#ifndef SWIG
    friend class Image;
    friend class DataSet;
    friend class Tag;

private:
    ReadingDataHandlerNumeric(std::shared_ptr<imebra::implementation::handlers::readingDataHandlerNumericBase> pDataHandler);
#endif

public:

    /// \brief Return a ReadMemory object referencing the raw buffer's data.
    ///
    /// \return a ReadMemory object referencing the raw buffer's data
    ///
    ///////////////////////////////////////////////////////////////////////////////
    const ReadMemory* getMemory() const;

    /// \brief Copies the buffer's raw memory content into the specified buffer.
    ///
    /// If the allocated buffer is not large enough then the method doesn't
    ///  copy any data and just returns the required buffer' size.
    ///
    /// \param destination     a pointer to the allocated buffer
    /// \param destinationSize the size of the allocated buffer
    /// \return the number of bytes to be copied into the pre-allocated buffer
    ///
    ///////////////////////////////////////////////////////////////////////////////
    size_t data(char* destination, size_t destinationSize) const;

#ifndef SWIG
    /// \brief Returns a pointer to the buffer's raw memory content.
    ///
    /// \param pDataSize a variable that will contain the raw memory's size in
    ///                  bytes
    /// \return a pointer to the buffer's raw memory
    ///
    ///////////////////////////////////////////////////////////////////////////////
    const char* data(size_t* pDataSize) const;
#endif

    /// \brief Returns the number of bytes occupied by the numbers handled by the
    ///        data handler
    ///
    /// \return the number of bytes occupied by the numbers handled by the data
    ///         handler
    ///
    ///////////////////////////////////////////////////////////////////////////////
    size_t getUnitSize() const;

    /// \brief Returns true if the numbers stored in the buffer are signed, false
    ///        otherwise.
    ///
    /// \return true if the numbers stored in the buffer are signed, false
    ///         otherwise
    ///
    ///////////////////////////////////////////////////////////////////////////////
    bool isSigned() const;
};

}

#endif // !defined(imebraReadingDataHandlerNumeric__INCLUDED_)
