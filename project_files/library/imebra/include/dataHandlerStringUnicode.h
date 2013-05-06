/*
$fileHeader$
*/

/*! \file dataHandlerStringUnicode.h
    \brief Declaration of the base class used by the string handlers that need to work
	        with different charsets.

*/

#if !defined(imebraDataHandlerStringUnicode_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
#define imebraDataHandlerStringUnicode_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_

#include "../../base/include/charsetConversion.h"
#include "dataHandlerString.h"
#include "charsetsList.h"



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

struct dicomCharsetInformation
{
	dicomCharsetInformation(const wchar_t* dicomName, const char* escapeSequence, const char* isoRegistration):
		m_dicomName(dicomName), m_escapeSequence(escapeSequence), m_isoRegistration(isoRegistration){}
	const wchar_t* m_dicomName;
	std::string m_escapeSequence;
	std::string m_isoRegistration;
};

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This is the base class for all the data handlers
///         that manage strings that need to be converted
///         from different unicode charsets
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class dataHandlerStringUnicode : public dataHandlerString
{
public:

    dataHandlerStringUnicode();

	/// \internal
	/// \brief Defines the charset used by the strings encoded
	///         in the tag.
	///
	/// @param pCharsetsList the list of dicom charsets used by
	///                      the string
	/// 
	///////////////////////////////////////////////////////////
	virtual void setCharsetsList(charsetsList::tCharsetsList* pCharsetsList);
	
	/// \internal
	/// \brief Retrieve the charset used in the encoded string
	///
	/// @param pCharsetsList a list that will be filled with the
	///                      dicom charsets used in the string
	///
	///////////////////////////////////////////////////////////
	virtual void getCharsetsList(charsetsList::tCharsetsList* pCharsetsList) const;

protected:
	// Convert a string to unicode, using the dicom charsets
	///////////////////////////////////////////////////////////
	virtual std::wstring convertToUnicode(const std::string& value) const;

	// Convert a string from unicode, using the dicom charsets
	///////////////////////////////////////////////////////////
	virtual std::string convertFromUnicode(const std::wstring& value, charsetsList::tCharsetsList* pCharsetsList) const;

    std::auto_ptr<charsetConversion> m_charsetConversion;
    std::auto_ptr<charsetConversion> m_localeCharsetConversion;

	dicomCharsetInformation* getCharsetInfo(const std::wstring& dicomName) const;
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
