/*
$fileHeader$
*/

/*! \file charsetConversionICU.h
    \brief Declaration of the class used to convert a string between different
            charsets using the ICU library.

The class hides the platform specific implementations and supplies a common
 interface for the charsets translations.

*/

#if !defined(imebraCharsetConversionICU_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_)
#define imebraCharsetConversionICU_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_

#if defined(IMEBRA_USE_ICU)

#include "charsetConversionBaseImpl.h"

#include <unicode/coll.h>
#include <unicode/ucnv.h>

///////////////////////////////////////////////////////////
//
// Everything is in the namespace puntoexe
//
///////////////////////////////////////////////////////////
namespace puntoexe
{

class charsetConversionICU: public charsetConversionBase
{
public:
    charsetConversionICU(const std::string& dicomName);
    virtual ~charsetConversionICU();

    virtual std::string fromUnicode(const std::wstring& unicodeString) const;

    virtual std::wstring toUnicode(const std::string& asciiString) const;

protected:
    UConverter* m_pIcuConverter;
};

typedef charsetConversionICU defaultCharsetConversion;

} // namespace puntoexe

#endif // defined(IMEBRA_USE_ICU)

#endif // !defined(imebraCharsetConversionICU_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_)
