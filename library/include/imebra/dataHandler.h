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

class IMEBRA_API ReadingDataHandler
{
public:
	// Costructor
	///////////////////////////////////////////////////////////
    ReadingDataHandler(const ReadingDataHandler& right);

    ReadingDataHandler& operator=(const ReadingDataHandler& right);

#ifndef SWIG
    ReadingDataHandler(std::shared_ptr<imebra::implementation::handlers::readingDataHandler> pDataHandler);
#endif

	void close();

    size_t getSize() const;

    size_t getUnitSize() const;

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

    std::string getDataType() const;

    void setDate(const size_t index, const Date& date);

    void setAge(const size_t index, const Age& age);

    void setSignedLong(const size_t index, const std::int32_t value);

    void setUnsignedLong(const size_t index, const std::uint32_t value);

    void setDouble(const size_t index, const double value);

    void setString(const size_t index, const std::wstring& value);

    void assign(const char* buffer, const size_t bufferSize);

    char* data(size_t* pDataSize) const;


#ifndef SWIG
protected:
    std::shared_ptr<imebra::implementation::handlers::writingDataHandler> m_pDataHandler;
#endif
};

}

#endif // !defined(imebraDataHandler_SWIG_93F684BF_0024_4bf3_89BA_D98E82A1F44C__INCLUDED_)
