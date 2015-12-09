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

#ifndef SWIG

#include <jni.h>
#include "../imebra/project_files/library/base/include/charsetConversionImpl.h"


///////////////////////////////////////////////////////////
//
// Everything is in the namespace puntoexe
//
///////////////////////////////////////////////////////////
namespace puntoexe
{

class charsetConversionJava: public charsetConversion
{
public:
    charsetConversionJava();
    virtual ~charsetConversionJava();

    virtual void initialize(const int requestedTable);

    virtual std::string fromUnicode(const std::wstring& unicodeString) const;

    virtual std::wstring toUnicode(const std::string& asciiString) const;

protected:
    virtual void close();

    static jstring getNativeJavaString(JNIEnv *env, const std::string& str, const char* tableName);
    static std::string getBytesFromString(JNIEnv *env, jstring jstr, const char* tableName);

    static JNIEnv* getJavaEnv(bool* bDetach);

    const char* m_tableName;


};

} // namespace puntoexe

#endif // SWIG

#endif // !defined(imebraCharsetConversionICU_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_)
