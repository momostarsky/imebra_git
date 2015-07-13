/*
$fileHeader$
*/

/*! \file dataHandlerString.h
    \brief Declaration of the base class used by the string handlers.

*/

#if !defined(imebraDataHandlerString_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
#define imebraDataHandlerString_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_

#include "dataHandler.h"
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
class dataHandlerString : public dataHandler
{
public:
	// Returns true if the pointer is valid
	///////////////////////////////////////////////////////////
	virtual bool pointerIsValid(const std::uint32_t index) const;

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

	// Parse the buffer
	///////////////////////////////////////////////////////////
	virtual void parseBuffer(const ptr<memory>& memoryBuffer);

	// Build the buffer
	///////////////////////////////////////////////////////////
	virtual void buildBuffer(const ptr<memory>& memoryBuffer);

protected:
	// Convert a string to unicode, without using the dicom 
	//  charsets
	///////////////////////////////////////////////////////////
	virtual std::wstring convertToUnicode(const std::string& value) const;

	// Convert a string from unicode, without using the dicom 
	//  charsets
	///////////////////////////////////////////////////////////
	virtual std::string convertFromUnicode(const std::wstring& value, charsetsList::tCharsetsList* pCharsetsList) const;

	// Return the maximum string's length
	///////////////////////////////////////////////////////////
	virtual std::uint32_t maxSize() const;

	// Return the separator
	///////////////////////////////////////////////////////////
	virtual wchar_t getSeparator() const;

	std::uint32_t m_elementNumber;

	std::vector<std::wstring> m_strings;

};


} // namespace handlers

} // namespace imebra

} // namespace puntoexe

#endif // !defined(imebraDataHandlerString_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
