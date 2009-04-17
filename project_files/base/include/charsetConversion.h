/*
$fileHeader$
*/

/*! \file charsetConversion.h
    \brief Declaration of the class used to convert a string between different
	        charsets.

The class hides the platform specific implementations and supplies a common
 interface for the charsets translations.

*/

#if !defined(imebraCharsetConversion_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_)
#define imebraCharsetConversion_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_

#include "configuration.h"
#include "baseObject.h"
#include <string>
#include <stdexcept>

#if PUNTOEXE_POSIX
#define PUNTOEXE_USEICONV 1
#endif

#if defined(PUNTOEXE_USEICONV)
#include <iconv.h>
#include <errno.h>
#else
#include "windows.h"
#endif


///////////////////////////////////////////////////////////
//
// Everything is in the namespace puntoexe
//
///////////////////////////////////////////////////////////
namespace puntoexe
{

///////////////////////////////////////////////////////////
/// \internal
/// \brief Stores the information related to a single
///         charset.
///
///////////////////////////////////////////////////////////
struct charsetInformation
{
	const char* m_isoRegistration;   ///< ISO name for the charset
	const char* m_iconvName;         ///< Name used by the iconv function
	unsigned long m_codePage;  ///< codePage used by Windows
	bool m_bZeroFlag;          ///< needs flags=0 in Windows
};

///////////////////////////////////////////////////////////
/// \internal
/// \brief This class converts a string from multibyte to
///         unicode and viceversa.
///
/// The class uses the function iconv on Posix systems and
///  the functions MultiByteToWideChars and
///  WideCharsToMultiByte on Windows systems.
///
///////////////////////////////////////////////////////////
class charsetConversion
{
public:
	charsetConversion();
	virtual ~charsetConversion();

	/// \brief Initialize the charsetConversion object.
	///
	/// This function must be called before any other
	///  function's method can be called.
	///
	/// @param tableName the ISO name of the charset that will
	///                   be used for the conversion
	///
	///////////////////////////////////////////////////////////
	void initialize(std::string tableName);

	/// \brief Retrieve the ISO name of the charset currently
	///         used for the conversion.
	///
	/// @return the ISO name of the active charset
	///
	///////////////////////////////////////////////////////////
	std::string getIsoCharset();

	/// \brief Transform a multibyte string into an unicode
	///         string using the charset declared with the
	///         method initialize().
	///
	/// initialize() must have been called before calling this
	///  method.
	///
	/// @param unicodeStr
	///
	///////////////////////////////////////////////////////////
	std::string fromUnicode(std::wstring unicodeString);

	/// \brief Transform a multibyte string into an unicode
	///         string using the charset declared with the
	///         method initialize().
	///
	/// initialize() must have been called before calling this
	///  method.
	///
	/// @param asciiString the multibyte string that will be
	///                     converted to unicode
	/// @return            the converted unicode string
	///
	///////////////////////////////////////////////////////////
	std::wstring toUnicode(std::string asciiString);

protected:
	void close();

	int findTable(std::string tableName);

	std::string m_isoCharset;

#if defined(PUNTOEXE_USEICONV)

#if defined(WIN32)
	std::string myIconv(iconv_t context, const char* inputString, size_t inputStringLengthBytes);
#else
	std::string myIconv(iconv_t context, char* inputString, size_t inputStringLengthBytes);
#endif
	iconv_t m_iconvToUnicode;
	iconv_t m_iconvFromUnicode;
#else
	unsigned long m_codePage;
	bool m_bZeroFlag;
#endif
};


///////////////////////////////////////////////////////////
/// \internal
/// \brief
///
/// Save the state of a charsetConversion object.
/// The saved state is restored by the destructor of the
///  class.
///
///////////////////////////////////////////////////////////
class saveCharsetConversionState
{
public:
	/// \brief Constructor. Save the state of the
	///         charsetConversion object specified in the
	///         parameter.
	///
	/// @param pConversion a pointer to the charsetConversion
	///                     object that need to be saved
	///
	///////////////////////////////////////////////////////////
	saveCharsetConversionState(charsetConversion* pConversion)
	{
		m_pConversion = pConversion;
		m_savedState = pConversion->getIsoCharset();
	}

	/// \brief Destructor. Restore the saved state to the
	///         charsetConversion object specified during
	///         the construction.
	///
	///////////////////////////////////////////////////////////
	virtual ~saveCharsetConversionState()
	{
		m_pConversion->initialize(m_savedState);
	}

protected:
	std::string m_savedState;
	charsetConversion* m_pConversion;
};


///////////////////////////////////////////////////////////
/// \brief Base class for the exceptions thrown by
///         charsetConversion.
///
///////////////////////////////////////////////////////////
class charsetConversionException: public std::runtime_error
{
public:
	charsetConversionException(std::string message): std::runtime_error(message){}
};


///////////////////////////////////////////////////////////
/// \brief Exception thrown when the requested charset
///         is not supported by the DICOM standard.
///
///////////////////////////////////////////////////////////
class charsetConversionExceptionNoTable: public charsetConversionException
{
public:
	charsetConversionExceptionNoTable(std::string message): charsetConversionException(message){}
};


///////////////////////////////////////////////////////////
/// \brief Exception thrown when the requested charset
///         is not supported by the system.
///
///////////////////////////////////////////////////////////
class charsetConversionExceptionNoSupportedTable: public charsetConversionException
{
public:
	charsetConversionExceptionNoSupportedTable(std::string message): charsetConversionException(message){}
};


///////////////////////////////////////////////////////////
/// \brief Exception thrown when the system doesn't have
///         a supported size for wchar_t
///
///////////////////////////////////////////////////////////
class charsetConversionExceptionUtfSizeNotSupported: public charsetConversionException
{
public:
	charsetConversionExceptionUtfSizeNotSupported(std::string message): charsetConversionException(message){}
};


} // namespace puntoexe


#endif // !defined(imebraCharsetConversion_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_)
