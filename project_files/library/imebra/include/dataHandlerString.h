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
	virtual bool pointerIsValid(const imbxUint32 index) const;

	// Get the data element as a signed long
	///////////////////////////////////////////////////////////
	virtual imbxInt32 getSignedLong(const imbxUint32 index) const;

	// Get the data element as an unsigned long
	///////////////////////////////////////////////////////////
	virtual imbxUint32 getUnsignedLong(const imbxUint32 index) const;
	
	// Get the data element as a double
	///////////////////////////////////////////////////////////
	virtual double getDouble(const imbxUint32 index) const;

	// Get the data element as a string
	///////////////////////////////////////////////////////////
	virtual std::string getString(const imbxUint32 index) const;

	// Get the data element as an unicode string
	///////////////////////////////////////////////////////////
	virtual std::wstring getUnicodeString(const imbxUint32 index) const;

	// Retrieve the data element as a string
	///////////////////////////////////////////////////////////
	virtual imbxUint32 getSize() const;
	
	// Set the data element as a signed long
	///////////////////////////////////////////////////////////
	virtual void setSignedLong(const imbxUint32 index, const imbxInt32 value);
	
	// Set the data element as an unsigned long
	///////////////////////////////////////////////////////////
	virtual void setUnsignedLong(const imbxUint32 index, const imbxUint32 value);
	
	// Set the data element as a double
	///////////////////////////////////////////////////////////
	virtual void setDouble(const imbxUint32 index, const double value);
	
	// Set the data element as a string
	///////////////////////////////////////////////////////////
	virtual void setString(const imbxUint32 index, const std::string& value);

	// Set the data element as an unicode string
	///////////////////////////////////////////////////////////
	virtual void setUnicodeString(const imbxUint32 index, const std::wstring& value);
	
	// Set the buffer's size, in data elements
	///////////////////////////////////////////////////////////
	virtual void setSize(const imbxUint32 elementsNumber);

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
	virtual imbxUint32 maxSize() const;

	// Return the separator
	///////////////////////////////////////////////////////////
	virtual wchar_t getSeparator() const;

	imbxUint32 m_elementNumber;

	std::vector<std::wstring> m_strings;

};


} // namespace handlers

} // namespace imebra

} // namespace puntoexe

#endif // !defined(imebraDataHandlerString_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
