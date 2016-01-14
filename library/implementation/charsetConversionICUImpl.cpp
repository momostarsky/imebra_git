/*
$fileHeader$
*/

/*! \file charsetConversionICU.cpp
    \brief Implementation of the charsetConversion class using the ICU library.

*/

#include "configurationImpl.h"

#if defined(IMEBRA_USE_ICU)

#include "exceptionImpl.h"
#include "charsetConversionICUImpl.h"
#include "../include/imebra/exceptions.h"
#include <memory>

namespace puntoexe
{

///////////////////////////////////////////////////////////
//
// Constructor
//
///////////////////////////////////////////////////////////
charsetConversionICU::charsetConversionICU(const std::string& dicomName)
{
    PUNTOEXE_FUNCTION_START(L"charsetConversionICU::charsetConversionICU");

    UErrorCode errorCode(U_ZERO_ERROR);
    const charsetInformation& info = getDictionary().getCharsetInformation(dicomName);

    m_pIcuConverter = ucnv_open(info.m_isoRegistration.c_str(), &errorCode);
    if(U_FAILURE(errorCode))
    {
        std::ostringstream buildErrorString;
        buildErrorString << "ICU library returned error " << errorCode << " for table " << dicomName;
        PUNTOEXE_THROW(::imebra::charsetConversionExceptionNoSupportedTable, buildErrorString.str());
    }

    PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
//
// Destructor
//
///////////////////////////////////////////////////////////
charsetConversionICU::~charsetConversionICU()
{
    ucnv_close(m_pIcuConverter);
}



///////////////////////////////////////////////////////////
//
// Convert a string from unicode to multibyte
//
///////////////////////////////////////////////////////////
std::string charsetConversionICU::fromUnicode(const std::wstring& unicodeString) const
{
    PUNTOEXE_FUNCTION_START(L"charsetConversionICU::fromUnicode");

	if(unicodeString.empty())
	{
		return std::string();
	}

    UnicodeString unicodeStringConversion;
    switch(sizeof(wchar_t))
    {
    case 2:
        unicodeStringConversion = UnicodeString((UChar*)&(unicodeString[0]), unicodeString.size());
        break;
    case 4:
        unicodeStringConversion = UnicodeString::fromUTF32((UChar32*)&(unicodeString[0]), unicodeString.size());
        break;
    default:
        PUNTOEXE_THROW(::imebra::charsetConversionExceptionUtfSizeNotSupported, "The system utf size is not supported");
    }
    UErrorCode errorCode(U_ZERO_ERROR);
    int32_t conversionLength = unicodeStringConversion.extract(0, 0, m_pIcuConverter, errorCode);
    errorCode = U_ZERO_ERROR;
    std::string returnString((size_t)conversionLength, char(0));
    unicodeStringConversion.extract(&(returnString[0]), conversionLength, m_pIcuConverter, errorCode);
    if(U_FAILURE(errorCode))
    {
        std::ostringstream buildErrorString;
        buildErrorString << "ICU library returned error " << errorCode;
        PUNTOEXE_THROW(::imebra::charsetConversionException, buildErrorString.str());
    }
    if(returnString == "\x1a")
    {
        return "";
    }
    return returnString;

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
//
// Convert a string from multibyte to unicode
//
///////////////////////////////////////////////////////////
std::wstring charsetConversionICU::toUnicode(const std::string& asciiString) const
{
    PUNTOEXE_FUNCTION_START(L"charsetConversionICU::toUnicode");

	if(asciiString.empty())
	{
		return std::wstring();
	}

    UErrorCode errorCode(U_ZERO_ERROR);
    UnicodeString unicodeString(&(asciiString[0]), asciiString.size(), m_pIcuConverter, errorCode);
    switch(sizeof(wchar_t))
    {
    case 2:
    {
        std::wstring returnString(unicodeString.length(), wchar_t(0));
        unicodeString.extract((UChar*)&(returnString[0]), unicodeString.length(), errorCode);
        return returnString;
    }
    case 4:
    {
        int32_t conversionLength = unicodeString.toUTF32((UChar32*)0, (int32_t)0, errorCode);
        errorCode = U_ZERO_ERROR;
        std::wstring returnString(conversionLength, wchar_t(0));
        unicodeString.toUTF32((UChar32*)&(returnString[0]), conversionLength, errorCode);
        return returnString;
    }
    default:
        PUNTOEXE_THROW(::imebra::charsetConversionExceptionUtfSizeNotSupported, "The system utf size is not supported");
    }

	PUNTOEXE_FUNCTION_END();
}



} // namespace puntoexe



#endif
