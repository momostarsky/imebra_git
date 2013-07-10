/*
$fileHeader$
*/

/*! \file charsetConversionWindows.cpp
    \brief Implementation of the charsetConversion class on Windows.

*/

#include "../include/configuration.h"

#if defined(PUNTOEXE_USE_WINDOWS_CHARSET)

#include "../include/exception.h"
#include "../include/charsetConversionWindows.h"
#include <memory>

namespace puntoexe
{

///////////////////////////////////////////////////////////
//
// Constructor
//
///////////////////////////////////////////////////////////
charsetConversionWindows::charsetConversionWindows()
{

	m_codePage = 0;
	m_bZeroFlag = false;
}


///////////////////////////////////////////////////////////
//
// Destructor
//
///////////////////////////////////////////////////////////
charsetConversionWindows::~charsetConversionWindows()
{
}


///////////////////////////////////////////////////////////
//
// Initialize the charsetConversion object
//
///////////////////////////////////////////////////////////
void charsetConversionWindows::initialize(const int requestedTable)
{
    PUNTOEXE_FUNCTION_START(L"charsetConversionWindows::initialize");

	m_codePage = m_charsetTable[requestedTable].m_codePage;
	m_bZeroFlag = m_charsetTable[requestedTable].m_bZeroFlag;

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
//
// Uninitialize the charsetConversion object
//
///////////////////////////////////////////////////////////
void charsetConversionWindows::close()
{
    PUNTOEXE_FUNCTION_START(L"charsetConversionWindows::close");

    charsetConversion::close();
	m_codePage = 0;
	m_bZeroFlag = false;

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
//
// Convert a string from unicode to multibyte
//
///////////////////////////////////////////////////////////
std::string charsetConversionWindows::fromUnicode(const std::wstring& unicodeString) const
{
    PUNTOEXE_FUNCTION_START(L"charsetConversionWindows::fromUnicode");

	if(unicodeString.empty())
	{
		return std::string();
	}


	BOOL bUsedDefault = false;
	int requiredChars = ::WideCharToMultiByte(m_codePage, m_bZeroFlag ? 0 : WC_NO_BEST_FIT_CHARS | WC_COMPOSITECHECK | WC_DEFAULTCHAR, unicodeString.c_str(), (int)(unicodeString.length()), 0, 0, 0, m_bZeroFlag ? 0 : &bUsedDefault);
	std::auto_ptr<char> convertedString(new char[requiredChars]);
	::WideCharToMultiByte(m_codePage, m_bZeroFlag ? 0 : WC_NO_BEST_FIT_CHARS | WC_COMPOSITECHECK | WC_DEFAULTCHAR, unicodeString.c_str(), (int)(unicodeString.length()), convertedString.get(), requiredChars, 0, m_bZeroFlag ? 0 : &bUsedDefault);
	if(bUsedDefault)
	{
		return std::string();
	}
	std::string returnString(convertedString.get(), requiredChars);
	return returnString;

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
//
// Convert a string from multibyte to unicode
//
///////////////////////////////////////////////////////////
std::wstring charsetConversionWindows::toUnicode(const std::string& asciiString) const
{
    PUNTOEXE_FUNCTION_START(L"charsetConversionWindows::toUnicode");

	if(asciiString.empty())
	{
		return std::wstring();
	}

	int requiredWChars = ::MultiByteToWideChar(m_codePage, 0, asciiString.c_str(), (int)(asciiString.length()), 0, 0);
	std::auto_ptr<wchar_t> convertedString(new wchar_t[requiredWChars]);
	::MultiByteToWideChar(m_codePage, 0, asciiString.c_str(), (int)(asciiString.length()), convertedString.get(), requiredWChars);
	std::wstring returnString(convertedString.get(), requiredWChars);

    return returnString;

	PUNTOEXE_FUNCTION_END();
}

charsetConversion* allocateCharsetConversion()
{
    return new charsetConversionWindows();
}

} // namespace puntoexe

#endif
