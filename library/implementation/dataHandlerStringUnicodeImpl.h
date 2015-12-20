/*
$fileHeader$
*/

/*! \file dataHandlerStringUnicode.h
    \brief Declaration of the base class used by the string handlers that need to work
	        with different charsets.

*/

#if !defined(imebraDataHandlerStringUnicode_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
#define imebraDataHandlerStringUnicode_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_

#include "charsetConversionImpl.h"
#include "dataHandlerStringBaseImpl.h"
#include "charsetsListImpl.h"
#include <memory>


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
///         that manage strings that need to be converted
///         from different unicode charsets
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class dataHandlerStringUnicode : public dataHandlerStringBase
{
public:

    dataHandlerStringUnicode(const wchar_t separator, const std::uint8_t paddingByte);

    ~dataHandlerStringUnicode();

	/// \internal
	/// \brief Defines the charset used by the strings encoded
	///         in the tag.
	///
	/// @param pCharsetsList the list of dicom charsets used by
	///                      the string
	/// 
	///////////////////////////////////////////////////////////
	virtual void setCharsetsList(charsetsList::tCharsetsList* pCharsetsList);
	
protected:
	// Convert a string to unicode, using the dicom charsets
	///////////////////////////////////////////////////////////
	virtual std::wstring convertToUnicode(const std::string& value) const;

	// Convert a string from unicode, using the dicom charsets
	///////////////////////////////////////////////////////////
	virtual std::string convertFromUnicode(const std::wstring& value, charsetsList::tCharsetsList* pCharsetsList) const;

};

class dataHandlerStringUnicodeException: public std::runtime_error
{
public:
	dataHandlerStringUnicodeException(const std::string& message): std::runtime_error(message){}
};

class dataHandlerStringUnicodeExceptionUnknownCharset: public dataHandlerStringUnicodeException
{
public:
	dataHandlerStringUnicodeExceptionUnknownCharset(const std::string& message): dataHandlerStringUnicodeException(message){}
};

} // namespace handlers

} // namespace imebra

} // namespace puntoexe

#endif // !defined(imebraDataHandlerStringUnicode_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
