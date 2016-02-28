/*
$fileHeader$
*/

/*! \file dataHandler_swig.h
    \brief Declaration of the class DataHandler for SWIG.

*/

#if !defined(imebraDataHandler_SWIG_93F684BF_0024_4bf3_89BA_D98E82A1F44C__INCLUDED_)
#define imebraDataHandler_SWIG_93F684BF_0024_4bf3_89BA_D98E82A1F44C__INCLUDED_

#ifndef SWIG

#include <string>
#include <memory>
#include "definitions.h"

namespace imebra
{
namespace implementation
{
namespace handlers
{
class readingDataHandler;
class writingDataHandler;
}
}
}

#endif

#include "memory.h"

namespace imebra
{

///
/// \brief The ReadingDataHandler class allows to read the content
///        of a Dicom tag.
///
/// ReadingDataHandler is able to return the tag's content as a string,
/// a number, a date/time or an age.
///
/// When ReadingDataHandler handles numeric tags then it can also return a
/// pointer to the raw memory that stores the numeric values.
///
/// In order to obtain a ReadingDataHandler for a specific tag stored
/// in a DataSet, call DataSet::getReadingDataHandler().
///
/// \warning ReadingDataHandler is NOT thread safe.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API ReadingDataHandler
{
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

#ifndef SWIG
    ReadingDataHandler(std::shared_ptr<imebra::implementation::handlers::readingDataHandler> pDataHandler);
#endif

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

    /// \brief If ReadingDataHandler is handling a numeric tag's content then it
    ///        returns the number of bytes occupied by each number.
    ///
    /// \return the number of bytes occupied by each number stored in the tag
    ///
    ///////////////////////////////////////////////////////////////////////////////
    size_t getUnitSize() const;

    bool isSigned() const;

	std::string getDataType() const;

    std::int32_t getSignedLong(size_t index) const;

    std::uint32_t getUnsignedLong(size_t index) const;

    double getDouble(size_t index) const;

    std::string getString(size_t index) const;

    std::wstring getUnicodeString(size_t index) const;

    Date getDate(size_t index) const;

    Age getAge(const size_t index) const;

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
    size_t data(char* buffer, const size_t bufferSize) const;

    ///
    /// \brief Returns a pointer to the raw representation of the handled data.
    /// \param dataSize
    /// \return
    ///
    const char* data(size_t* pDataSize) const;


#ifndef SWIG
protected:
    std::shared_ptr<imebra::implementation::handlers::readingDataHandler> m_pDataHandler;
#endif
};

class IMEBRA_API WritingDataHandler
{
public:
    // Costructor
    ///////////////////////////////////////////////////////////
    WritingDataHandler(const WritingDataHandler& right);

    WritingDataHandler& operator=(const WritingDataHandler& right);

#ifndef SWIG
    WritingDataHandler(std::shared_ptr<imebra::implementation::handlers::writingDataHandler> pDataHandler);
#endif

    void close();

    void setSize(const size_t elementsNumber);

    size_t getSize() const;

    size_t getUnitSize() const;

    bool isSigned() const;

    std::string getDataType() const;

    WritingDataHandler& setDate(const size_t index, const Date& date);

    WritingDataHandler& setAge(const size_t index, const Age& age);

    WritingDataHandler& setSignedLong(const size_t index, const std::int32_t value);

    WritingDataHandler& setUnsignedLong(const size_t index, const std::uint32_t value);

    WritingDataHandler& setDouble(const size_t index, const double value);

    WritingDataHandler& setString(const size_t index, const std::string& value);

    WritingDataHandler& setUnicodeString(const size_t index, const std::wstring& value);

    void assign(const char* buffer, const size_t bufferSize);

    char* data(size_t* pDataSize) const;

#ifndef SWIG
protected:
    std::shared_ptr<imebra::implementation::handlers::writingDataHandler> m_pDataHandler;
#endif
};

}

#endif // !defined(imebraDataHandler_SWIG_93F684BF_0024_4bf3_89BA_D98E82A1F44C__INCLUDED_)
