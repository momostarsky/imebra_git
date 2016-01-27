/*
$fileHeader$
*/

/*! \file charsetConversionWindows.h
    \brief Declaration of the class used to convert a string between different
            charsets in Windows.

*/

#if !defined(imebraCharsetConversionWindows_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_)
#define imebraCharsetConversionWindows_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_

#if defined(IMEBRA_USE_WINDOWS_CHARSET)

#include "charsetConversionBaseImpl.h"
#include <windows.h>

///////////////////////////////////////////////////////////
//
// Everything is in the namespace imebra
//
///////////////////////////////////////////////////////////
namespace imebra
{
class charsetConversionWindows: public charsetConversionBase
{
public:
    charsetConversionWindows(const std::string& dicomName);

    virtual std::string fromUnicode(const std::wstring& unicodeString) const;

    virtual std::wstring toUnicode(const std::string& asciiString) const;

protected:
	unsigned long m_codePage;
	bool m_bZeroFlag;
};

typedef charsetConversionWindows defaultCharsetConversion;

} // namespace imebra

#endif // defined(IMEBRA_USE_WINDOWS_CHARSET)

#endif // !defined(imebraCharsetConversionWindows_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_)
