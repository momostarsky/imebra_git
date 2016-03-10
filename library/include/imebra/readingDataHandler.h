/*
$fileHeader$
*/

/// \file readingDataHandler.h
/// \brief Declaration of the class ReadingDataHandler.
///
///////////////////////////////////////////////////////////////////////////////

#if !defined(imebraReadingDataHandler__INCLUDED_)
#define imebraReadingDataHandler__INCLUDED_

#include <string>
#include <memory>
#include "definitions.h"
#include "readMemory.h"

#ifndef SWIG

namespace imebra
{
namespace implementation
{
namespace handlers
{
class readingDataHandler;
}
}
}

#endif


namespace imebra
{

///
/// \brief The ReadingDataHandler class allows to read the content
///        of a Dicom tag.
///
/// ReadingDataHandler is able to return the tag's content as a string,
/// a number, a date/time or an age.
///
/// When a ReadingDataHandler object handles a numeric tag then it can also
/// return a pointer to the raw memory that stores the numeric values.
///
/// In order to obtain a ReadingDataHandler object for a specific tag stored
/// in a DataSet, call DataSet::getReadingDataHandler().
///
/// \warning ReadingDataHandler is NOT thread safe.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API ReadingDataHandler
{
#ifndef SWIG
    friend class DataSet;
    friend class TagContent;
    friend class ReadingDataHandlerNumeric;

private:
    ReadingDataHandler(std::shared_ptr<imebra::implementation::handlers::readingDataHandler> pDataHandler);
#endif

public:

    /// \brief Copy constructor.
    ///
    /// The new ReadingDataHandler will handle the same tag's content handled
    /// by the source ReadingDataHandler.
    ///
    /// \param right the source ReadingDataHandler
    ///
    ///////////////////////////////////////////////////////////////////////////////
    ReadingDataHandler(const ReadingDataHandler& right);

    virtual ~ReadingDataHandler();

    /// \brief Copy operator.
    ///
    /// The ReadingDataHandler object will drop the handled tag's content
    /// and will handle the same tag's content as the source ReadingDataHandler.
    ///
    /// \param right the source ReadingDataHandler
    ///
    ///////////////////////////////////////////////////////////////////////////////
    ReadingDataHandler& operator=(const ReadingDataHandler& right);

    /// \brief Returns the number of elements in the Dicom tag handled by the data
    ///        handler.
    ///
    /// If the ReadingDataHandler object is related to a tag that contains strings,
    /// then it returns the number of strings stored in the tag. Multiple strings
    /// in a string tag are separated by a separator char.
    ///
    /// \return the number of elements stored in the handled Dicom tag
    ///
    ///////////////////////////////////////////////////////////////////////////////
    size_t getSize() const;

	std::string getDataType() const;

    std::int32_t getSignedLong(size_t index) const;

    std::uint32_t getUnsignedLong(size_t index) const;

    double getDouble(size_t index) const;

    std::string getString(size_t index) const;

    std::wstring getUnicodeString(size_t index) const;

    Date getDate(size_t index) const;

    Age getAge(const size_t index) const;

#ifndef SWIG
protected:
    std::shared_ptr<imebra::implementation::handlers::readingDataHandler> m_pDataHandler;
#endif
};

}

#endif // !defined(imebraReadingDataHandler__INCLUDED_)
