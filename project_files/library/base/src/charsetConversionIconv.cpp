/*
$fileHeader$
*/

/*! \file charsetConversionIconv.cpp
    \brief Implementation of the charsetConversion class using Iconv.

*/

#include "../include/configuration.h"

#if defined(PUNTOEXE_USE_ICONV)

#include "../include/exception.h"
#include "../include/charsetConversionIconv.h"
#include <memory>

namespace puntoexe
{

///////////////////////////////////////////////////////////
//
// Constructor
//
///////////////////////////////////////////////////////////
charsetConversionIconv::charsetConversionIconv(const std::string& dicomName)
{
    PUNTOEXE_FUNCTION_START(L"charsetConversion::charsetConversionIconv");

    const charsetInformation& info(getDictionary().getCharsetInformation(dicomName));

    std::string toCodeIgnore(info.m_isoRegistration);
    toCodeIgnore += "//IGNORE";

    // Check little endian/big endian
    ///////////////////////////////////////////////////////////
    static std::uint16_t m_endianCheck=0x00ff;
    const char* utfCode;
    switch(sizeof(wchar_t))
    {
    case 2:
        utfCode = (*((std::uint8_t*)&m_endianCheck) == 0xff) ? "UTF-16LE" : "UTF-16BE";
        break;
    case 4:
        utfCode = (*((std::uint8_t*)&m_endianCheck) == 0xff) ? "UTF-32LE" : "UTF-32BE";
        break;
    default:
        PUNTOEXE_THROW(charsetConversionExceptionUtfSizeNotSupported, "The system utf size is not supported");
    }

    m_iconvToUnicode = iconv_open(utfCode, info.m_isoRegistration.c_str());
    m_iconvFromUnicode = iconv_open(toCodeIgnore.c_str(), utfCode);
    if(m_iconvToUnicode == (iconv_t)-1 || m_iconvFromUnicode == (iconv_t)-1)
    {
        std::ostringstream buildErrorString;
        buildErrorString << "Table " << dicomName << " not supported by the system";
        PUNTOEXE_THROW(charsetConversionExceptionNoSupportedTable, buildErrorString.str());
    }

    PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
//
// Destructor
//
///////////////////////////////////////////////////////////
charsetConversionIconv::~charsetConversionIconv()
{
    iconv_close(m_iconvToUnicode);
    iconv_close(m_iconvFromUnicode);
}

///////////////////////////////////////////////////////////
//
// Convert a string from unicode to multibyte
//
///////////////////////////////////////////////////////////
std::string charsetConversionIconv::fromUnicode(const std::wstring& unicodeString) const
{
    PUNTOEXE_FUNCTION_START(L"charsetConversionIconv::fromUnicode");

	if(unicodeString.empty())
	{
		return std::string();
	}

	return myIconv(m_iconvFromUnicode, (char*)unicodeString.c_str(), unicodeString.length() * sizeof(wchar_t));

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
//
// Convert a string from multibyte to unicode
//
///////////////////////////////////////////////////////////
std::wstring charsetConversionIconv::toUnicode(const std::string& asciiString) const
{
    PUNTOEXE_FUNCTION_START(L"charsetConversionIconv::toUnicode");

	if(asciiString.empty())
	{
		return std::wstring();
	}

	std::string convertedString(myIconv(m_iconvToUnicode, (char*)asciiString.c_str(), asciiString.length()));
	std::wstring returnString((wchar_t*)convertedString.c_str(), convertedString.size() / sizeof(wchar_t));

    return returnString;

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
//
// In Posix systems executes an iconv
//
///////////////////////////////////////////////////////////
#if defined(PUNTOEXE_WINDOWS)
std::string charsetConversionIconv::myIconv(iconv_t context, const char* inputString, size_t inputStringLengthBytes) const
#else
std::string charsetConversionIconv::myIconv(iconv_t context, char* inputString, size_t inputStringLengthBytes) const
#endif
{
	PUNTOEXE_FUNCTION_START(L"charsetConversion::myIconv");

	std::string finalString;

	// Reset the state
	///////////////////////////////////////////////////////////
	iconv(context, 0, 0, 0, 0);

	// Buffer for the conversion
	///////////////////////////////////////////////////////////
	char conversionBuffer[1024];

	// Convert the string
	///////////////////////////////////////////////////////////
	for(size_t iconvReturn = (size_t)-1; iconvReturn == (size_t)-1;)
	{
		// Executes the conversion
		///////////////////////////////////////////////////////////
		size_t progressiveOutputBufferSize = sizeof(conversionBuffer);
		char* progressiveOutputBuffer(conversionBuffer);
		iconvReturn = iconv(context, &inputString, &inputStringLengthBytes, &progressiveOutputBuffer, &progressiveOutputBufferSize);

		// Update buffer's size
		///////////////////////////////////////////////////////////
		size_t outputLengthBytes = sizeof(conversionBuffer) - progressiveOutputBufferSize;

		finalString.append(conversionBuffer, outputLengthBytes);

		// Throw if an invalid sequence is found
		///////////////////////////////////////////////////////////
		if(iconvReturn == (size_t)-1 && errno != E2BIG)
		{
		    return std::string();
		}
	}

	return finalString;

	PUNTOEXE_FUNCTION_END();
}

} // namespace puntoexe

#endif
