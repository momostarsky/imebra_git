/*
$fileHeader$
*/

/*! \file dataHandlerString.h
    \brief Declaration of the base class used by the string handlers.

*/

#if !defined(imebraDataHandlerStringBase_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
#define imebraDataHandlerStringBase_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_

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
class dataHandlerStringBase : public dataHandler
{
public:
    dataHandlerStringBase(const std::string& dataType, const wchar_t separator, const std::uint8_t paddingByte);

    virtual void parseBuffer(const std::shared_ptr<memory>& memoryBuffer);

    // Get the data element as a signed long
    ///////////////////////////////////////////////////////////
    virtual std::int32_t getSignedLong(const std::uint32_t index) const;

    // Get the data element as an unsigned long
    ///////////////////////////////////////////////////////////
    virtual std::uint32_t getUnsignedLong(const std::uint32_t index) const;

    // Get the data element as a double
    ///////////////////////////////////////////////////////////
    virtual double getDouble(const std::uint32_t index) const;

    // Get the data element as a string
    ///////////////////////////////////////////////////////////
    virtual std::string getString(const std::uint32_t index) const;

    // Get the data element as an unicode string
    ///////////////////////////////////////////////////////////
    virtual std::wstring getUnicodeString(const std::uint32_t index) const;

    // Retrieve the data element as a string
    ///////////////////////////////////////////////////////////
    virtual std::uint32_t getSize() const;

    // Set the data element as a signed long
    ///////////////////////////////////////////////////////////
    virtual void setSignedLong(const std::uint32_t index, const std::int32_t value);

    // Set the data element as an unsigned long
    ///////////////////////////////////////////////////////////
    virtual void setUnsignedLong(const std::uint32_t index, const std::uint32_t value);

    // Set the data element as a double
    ///////////////////////////////////////////////////////////
    virtual void setDouble(const std::uint32_t index, const double value);

    // Set the data element as a string
    ///////////////////////////////////////////////////////////
    virtual void setString(const std::uint32_t index, const std::string& value);

    // Set the data element as an unicode string
    ///////////////////////////////////////////////////////////
    virtual void setUnicodeString(const std::uint32_t index, const std::wstring& value);

    // Set the buffer's size, in data elements
    ///////////////////////////////////////////////////////////
    virtual void setSize(const std::uint32_t elementsNumber);

protected:
    // Convert a string to unicode, without using the dicom
    //  charsets
    ///////////////////////////////////////////////////////////
    virtual std::wstring convertToUnicode(const std::string& value) const = 0;

    // Convert a string from unicode, without using the dicom
    //  charsets
    ///////////////////////////////////////////////////////////
    virtual std::string convertFromUnicode(const std::wstring& value, charsetsList::tCharsetsList* pCharsetsList) const = 0;

    // Return the maximum string's length
    ///////////////////////////////////////////////////////////
    virtual std::uint32_t maxSize() const;

    // Return the separator
    ///////////////////////////////////////////////////////////
    wchar_t getSeparator() const;

protected:
    const wchar_t m_separator;

	std::vector<std::wstring> m_strings;

};


} // namespace handlers

} // namespace imebra

} // namespace puntoexe

#endif // !defined(imebraDataHandlerStringBase_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
