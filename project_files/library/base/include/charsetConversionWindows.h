/*
$fileHeader$
*/

/*! \file charsetConversionWindows.h
    \brief Declaration of the class used to convert a string between different
            charsets in Windows.

*/

#if !defined(imebraCharsetConversionWindows_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_)
#define imebraCharsetConversionWindows_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_

#include "charsetConversion.h"
#include <windows.h>

///////////////////////////////////////////////////////////
//
// Everything is in the namespace puntoexe
//
///////////////////////////////////////////////////////////
namespace puntoexe
{
class charsetConversionWindows: public charsetConversion
{
public:
    charsetConversionWindows();
    virtual ~charsetConversionWindows();

    virtual void initialize(const int requestedTable);

    virtual std::string fromUnicode(const std::wstring& unicodeString) const;

    virtual std::wstring toUnicode(const std::string& asciiString) const;

protected:
    virtual void close();

	unsigned long m_codePage;
	bool m_bZeroFlag;
};

} // namespace puntoexe

#endif // !defined(imebraCharsetConversionWindows_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_)
