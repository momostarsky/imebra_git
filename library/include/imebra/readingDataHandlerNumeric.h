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

class IMEBRA_API ReadingDataHandlerNumeric: public ReadingDataHandler
{
public:
#ifndef SWIG
    friend class Image;
    friend class DataSet;
    friend class TagContent;

private:
    ReadingDataHandlerNumeric(std::shared_ptr<imebra::implementation::handlers::readingDataHandlerNumericBase> pDataHandler);
#endif

public:

    /// \brief Copy constructor.
    ///
    /// The new ReadingDataHandlerNumeric will handle the same tag's content
    /// handler by the source ReadingDataHandlerNumeric.
    ///
    /// \param right the source ReadingDataHandlerNumeric
    ///
    ///////////////////////////////////////////////////////////////////////////////
    ReadingDataHandlerNumeric(const ReadingDataHandlerNumeric& right);

    /// \brief Copy operator.
    ///
    /// The ReadingDataHandler object will drop the handled tag's content
    /// and will handle the same tag's content as the source ReadingDataHandler.
    ///
    /// \param right the source ReadingDataHandler
    ///
    ///////////////////////////////////////////////////////////////////////////////
    ReadingDataHandlerNumeric& operator=(const ReadingDataHandlerNumeric& right);

    const ReadMemory getMemory() const;

    ///
    /// \brief Copies the raw representation of the handled data into
    ///        a pre-allocated buffer.
    ///
    /// If the allocated buffer is not large enough then the method doesn't
    ///  copy any data and just returns the required buffer' size.
    ///
    /// \param buffer     a pointer to the allocated buffer
    /// \param bufferSize the size of the allocated buffer
    /// \return the number of bytes to be copied into the pre-allocated buffer
    ///
    ///////////////////////////////////////////////////////////////////////////////
    size_t data(char* destination, size_t destinationSize) const;

#ifndef SWIG
    ///
    /// \brief Returns a pointer to the raw representation of the handled data.
    ///
    /// \param dataSize
    /// \return
    ///
    ///////////////////////////////////////////////////////////////////////////////
    const char* data(size_t* pDataSize) const;
#endif

    /// \brief If ReadingDataHandler is handling a numeric tag's content then it
    ///        returns the number of bytes occupied by each number.
    ///
    /// \return the number of bytes occupied by each number stored in the tag
    ///
    ///////////////////////////////////////////////////////////////////////////////
    size_t getUnitSize() const;

    bool isSigned() const;
};

}

#endif // !defined(imebraReadingDataHandlerNumeric__INCLUDED_)
