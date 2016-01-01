/*
$fileHeader$
*/

/*! \file dataHandlerString.h
    \brief Declaration of the base class used by the string handlers.

*/

#if !defined(imebraDataHandlerString_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
#define imebraDataHandlerString_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_

#include "dataHandlerImpl.h"
#include <vector>
#include <string>


///////////////////////////////////////////////////////////
//
// Everything is in the namespace puntoexe::imebra
//
///////////////////////////////////////////////////////////
namespace puntoexe
{

namespace imebra
{

namespace handlers
{

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This is the base class for all the data handlers
///         that manage strings.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class readingDataHandlerString : public readingDataHandler
{
public:
    readingDataHandlerString(const memory& parseMemory, const std::string& dataType, const char separator, const std::uint8_t paddingByte);

    // Get the data element as a signed long
    ///////////////////////////////////////////////////////////
    virtual std::int32_t getSignedLong(const size_t index) const;

    // Get the data element as an unsigned long
    ///////////////////////////////////////////////////////////
    virtual std::uint32_t getUnsignedLong(const size_t index) const;

    // Get the data element as a double
    ///////////////////////////////////////////////////////////
    virtual double getDouble(const size_t index) const;

    // Get the data element as a string
    ///////////////////////////////////////////////////////////
    virtual std::string getString(const size_t index) const;

    // Get the data element as an unicode string
    ///////////////////////////////////////////////////////////
    virtual std::wstring getUnicodeString(const size_t index) const;

    // Retrieve the data element as a string
    ///////////////////////////////////////////////////////////
    virtual size_t getSize() const;

protected:

    std::vector<std::string> m_strings;    
};


class writingDataHandlerString : public writingDataHandler
{
public:
    writingDataHandlerString(const std::shared_ptr<buffer>& pBuffer, const std::string& dataType, const char separator, const size_t unitSize, const size_t maxSize, const std::uint8_t paddingByte);

    ~writingDataHandlerString();

    // Set the data element as a signed long
    ///////////////////////////////////////////////////////////
    virtual void setSignedLong(const size_t index, const std::int32_t value);

    // Set the data element as an unsigned long
    ///////////////////////////////////////////////////////////
    virtual void setUnsignedLong(const size_t index, const std::uint32_t value);

    // Set the data element as a double
    ///////////////////////////////////////////////////////////
    virtual void setDouble(const size_t index, const double value);

    // Set the buffer's size, in data elements
    ///////////////////////////////////////////////////////////
    virtual void setSize(const size_t elementsNumber);

    virtual size_t getSize() const;

    virtual void setString(const size_t index, const std::string& value);

    virtual void setUnicodeString(const size_t index, const std::wstring& value);

protected:

    std::vector<std::string> m_strings;

    char m_separator;
    size_t m_unitSize;
    size_t m_maxSize;


};


} // namespace handlers

} // namespace imebra

} // namespace puntoexe

#endif // !defined(imebraDataHandlerString_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
