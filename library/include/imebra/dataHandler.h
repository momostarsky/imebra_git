/*
$fileHeader$
*/

/// \file dataHandler.h
/// \brief Declaration of the classes ReadingDataHandler and
///        WritingDataHandler.
///
///////////////////////////////////////////////////////////////////////////////

#if !defined(imebraDataHandler__INCLUDED_)
#define imebraDataHandler__INCLUDED_

#include <string>
#include <memory>
#include "definitions.h"
#include "memory.h"

#ifndef SWIG

namespace imebra
{
namespace implementation
{
namespace handlers
{
class readingDataHandler;
class readingDataHandlerNumericBase;
class writingDataHandler;
class writingDataHandlerNumericBase;
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
    size_t data(char* buffer, const size_t bufferSize) const;

    ///
    /// \brief Returns a pointer to the raw representation of the handled data.
    ///
    /// \param dataSize
    /// \return
    ///
    ///////////////////////////////////////////////////////////////////////////////
    const char* data(size_t* pDataSize) const;

    /// \brief If ReadingDataHandler is handling a numeric tag's content then it
    ///        returns the number of bytes occupied by each number.
    ///
    /// \return the number of bytes occupied by each number stored in the tag
    ///
    ///////////////////////////////////////////////////////////////////////////////
    size_t getUnitSize() const;

    bool isSigned() const;
};

class IMEBRA_API WritingDataHandler
{
#ifndef SWIG
    friend class DataSet;
    friend class TagContent;
    friend class WritingDataHandlerNumeric;

private:
    WritingDataHandler(std::shared_ptr<imebra::implementation::handlers::writingDataHandler> pDataHandler);
#endif

public:
    // Costructor
    ///////////////////////////////////////////////////////////
    WritingDataHandler(const WritingDataHandler& right);

    virtual ~WritingDataHandler();

    WritingDataHandler& operator=(const WritingDataHandler& right);

    void close();

    void setSize(const size_t elementsNumber);

    size_t getSize() const;

    std::string getDataType() const;

    WritingDataHandler& setDate(const size_t index, const Date& date);

    WritingDataHandler& setAge(const size_t index, const Age& age);

    WritingDataHandler& setSignedLong(const size_t index, const std::int32_t value);

    WritingDataHandler& setUnsignedLong(const size_t index, const std::uint32_t value);

    WritingDataHandler& setDouble(const size_t index, const double value);

    WritingDataHandler& setString(const size_t index, const std::string& value);

    WritingDataHandler& setUnicodeString(const size_t index, const std::wstring& value);

#ifndef SWIG
protected:
    std::shared_ptr<imebra::implementation::handlers::writingDataHandler> m_pDataHandler;
#endif
};

class IMEBRA_API WritingDataHandlerNumeric: public WritingDataHandler
{
#ifndef SWIG
    friend class Image;
    friend class DataSet;
    friend class TagContent;
private:
    WritingDataHandlerNumeric(std::shared_ptr<imebra::implementation::handlers::writingDataHandlerNumericBase> pDataHandler);
#endif

public:
    // Costructor
    ///////////////////////////////////////////////////////////
    WritingDataHandlerNumeric(const WritingDataHandlerNumeric& right);

    WritingDataHandlerNumeric& operator=(const WritingDataHandlerNumeric& right);

    ReadWriteMemory getMemory() const;

    void assign(const char* buffer, const size_t bufferSize);

    char* data(size_t* pDataSize) const;

    size_t getUnitSize() const;

    bool isSigned() const;
};

}

#endif // !defined(imebraDataHandler__INCLUDED_)
