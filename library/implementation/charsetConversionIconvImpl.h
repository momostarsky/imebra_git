/*
$fileHeader$
*/

/*! \file charsetConversionIconv.h
    \brief Declaration of the class used to convert a string between different
            charsets using the Iconv library.

The class hides the platform specific implementations and supplies a common
 interface for the charsets translations.

*/

#if !defined(imebraCharsetConversionIconv_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_)
#define imebraCharsetConversionIconv_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_

#if defined(IMEBRA_USE_ICONV)

#include "charsetConversionBaseImpl.h"

#include <iconv.h>
#include <errno.h>

///////////////////////////////////////////////////////////
//
// Everything is in the namespace imebra
//
///////////////////////////////////////////////////////////
namespace imebra
{

class charsetConversionIconv: public charsetConversionBase
{
public:
    charsetConversionIconv(const std::string& dicomName);
    virtual ~charsetConversionIconv();

    virtual std::string fromUnicode(const std::wstring& unicodeString) const;

    virtual std::wstring toUnicode(const std::string& asciiString) const;

protected:

#if defined(IMEBRA_WINDOWS)
    std::string myIconv(iconv_t context, const char* inputString, size_t inputStringLengthBytes) const;
#else
    std::string myIconv(iconv_t context, char* inputString, size_t inputStringLengthBytes) const;
#endif
    iconv_t m_iconvToUnicode;
	iconv_t m_iconvFromUnicode;
};

typedef charsetConversionIconv defaultCharsetConversion;

} // namespace imebra

#endif // defined(IMEBRA_USE_ICONV)

#endif // !defined(imebraCharsetConversionIconv_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_)
