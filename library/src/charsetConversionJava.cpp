/*
$fileHeader$
*/

/*! \file charsetConversionICU.cpp
    \brief Implementation of the charsetConversion class using the ICU library.

*/

#if defined(IMEBRA_USE_JAVA)

#include "../implementation/configurationImpl.h"
#include "../imebra/project_files/library/base/include/streamControllerImpl.h"

#include "onloadImpl.h"
#include "../implementation/exceptionImpl.h"
#include "./charsetConversionJavaImpl.h"
#include <memory>

namespace puntoexe
{

///////////////////////////////////////////////////////////
//
// Constructor
//
///////////////////////////////////////////////////////////
charsetConversionJava::charsetConversionJava()
{
}


///////////////////////////////////////////////////////////
//
// Destructor
//
///////////////////////////////////////////////////////////
charsetConversionJava::~charsetConversionJava()
{
	close();
}


///////////////////////////////////////////////////////////
//
// Initialize the charsetConversion object
//
///////////////////////////////////////////////////////////
void charsetConversionJava::initialize(const int requestedTable)
{
    PUNTOEXE_FUNCTION_START(L"charsetConversionJava::initialize");

    m_tableName = m_charsetTable[requestedTable].m_iconvName;

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
//
// Uninitialize the charsetConversion object
//
///////////////////////////////////////////////////////////
void charsetConversionJava::close()
{
    PUNTOEXE_FUNCTION_START(L"charsetConversionJava::close");

    charsetConversion::close();

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
//
// Convert a string from unicode to multibyte
//
///////////////////////////////////////////////////////////
std::string charsetConversionJava::fromUnicode(const std::wstring& unicodeString) const
{
    PUNTOEXE_FUNCTION_START(L"charsetConversionJava::fromUnicode");

	if(unicodeString.empty())
	{
		return std::string();
	}

	bool bDetach(false);
	JNIEnv* env = getJavaEnv(&bDetach);

	std::string bytes;
	bytes.resize(unicodeString.length() * sizeof(wchar_t));
	::memcpy(&bytes[0], &(unicodeString[0]), bytes.size());
	puntoexe::streamController::adjustEndian((imbxUint8*)&(bytes[0]), sizeof(wchar_t), puntoexe::streamController::highByteEndian, unicodeString.size());
	jstring javaString = getNativeJavaString(env, bytes, sizeof(wchar_t) == 2 ? "UTF-16BE" : "UTF-32BE");

	std::string returnValue;

	if(javaString != 0)
	{
	    returnValue = getBytesFromString(env, javaString, m_tableName);
	    env->DeleteLocalRef(javaString);
	}

    if(bDetach)
    {
        get_imebra_javaVM()->DetachCurrentThread();
    }

    return returnValue;

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
//
// Convert a string from multibyte to unicode
//
///////////////////////////////////////////////////////////
std::wstring charsetConversionJava::toUnicode(const std::string& asciiString) const
{
    PUNTOEXE_FUNCTION_START(L"charsetConversionJava::toUnicode");

	if(asciiString.empty())
	{
		return std::wstring();
	}

	bool bDetach(false);
	JNIEnv* env = getJavaEnv(&bDetach);

    std::wstring returnValue;
    jstring javaString = getNativeJavaString(env, asciiString, m_tableName);
    if(javaString != 0)
    {
        std::string bytes = getBytesFromString(env, javaString, sizeof(wchar_t) == 2 ? "UTF-16BE" : "UTF-32BE");
        if(bytes.size() != 0)
        {
            returnValue.resize(bytes.size() / sizeof(wchar_t));
            ::memcpy(&(returnValue[0]), &(bytes[0]), bytes.size());
            puntoexe::streamController::adjustEndian((imbxUint8*)&(returnValue[0]), sizeof(wchar_t), puntoexe::streamController::highByteEndian, returnValue.size());
        }
        env->DeleteLocalRef(javaString);
    }

    if(bDetach)
    {
        get_imebra_javaVM()->DetachCurrentThread();
    }

    return returnValue;

	PUNTOEXE_FUNCTION_END();
}

charsetConversion* allocateCharsetConversion()
{
    return new charsetConversionJava();
}


/**
 The function creates a byte array, copies the native C string into the byte array,
 and finally invokes the String(byte[] bytes) constructor to create the resulting jstring object.
 Class_java_lang_String is a global reference to the java.lang.String class, and MID_String_init
 is the method ID of the string constructor.
 Because this is a utility function, we make sure to delete the local reference to the byte array
  created temporarily to store the characters.
*/
jstring charsetConversionJava::getNativeJavaString(JNIEnv *env, const std::string& str, const char* tableName)
{
    jclass Class_java_lang_String = env->FindClass("java/lang/String");
    jmethodID MID_String_init = env->GetMethodID(Class_java_lang_String, "<init>", "([BLjava/lang/String;)V");

    if (env->EnsureLocalCapacity(2) < 0)
    {
        return 0;
    }

    size_t len = str.size();
    jbyteArray bytes = env->NewByteArray(len);
    if (bytes != 0)
    {
        jstring jTableName = env->NewStringUTF(tableName);
        if(jTableName != 0)
        {
            env->SetByteArrayRegion(bytes, 0, len, (jbyte *)&(str[0]));
            jstring result = (jstring)env->NewObject(Class_java_lang_String, MID_String_init, bytes, jTableName);
            env->DeleteLocalRef(jTableName);
            env->DeleteLocalRef(bytes);
            return result;
        }
        env->DeleteLocalRef(bytes);
    }

    return 0;
}





/**
 Use the String.getBytes method to convert a jstring to the appropriate native encoding.
 The following utility function translates a jstring to a locale-specific native C string
*/
std::string charsetConversionJava::getBytesFromString(JNIEnv *env, jstring jstr, const char* tableName)
{
    std::string result;
    jclass Class_java_lang_String = env->FindClass("java/lang/String");
    jmethodID MID_String_getBytes = env->GetMethodID(Class_java_lang_String, "getBytes", "(Ljava/lang/String;)[B");

    jbyteArray bytes = 0;
    jthrowable exc;
    if (env->EnsureLocalCapacity(2) < 0)
    {
        return ""; /* out of memory error */
    }

    jstring jTableName = env->NewStringUTF(tableName);
    if(jTableName != 0)
    {
        bytes = (jbyteArray)env->CallObjectMethod(jstr, MID_String_getBytes, jTableName);
        exc = env->ExceptionOccurred();
        if (!exc && bytes != 0)
        {
            jint len = env->GetArrayLength(bytes);
            if(len != 0)
            {
                result.resize(len);
                env->GetByteArrayRegion(bytes, 0, len, (jbyte *)&(result[0]));
            }
        }
        else
        {
            env->DeleteLocalRef(exc);
        }
        if(bytes != 0)
        {
            env->DeleteLocalRef(bytes);
        }
        env->DeleteLocalRef(jTableName);
    }
    return result;
}


JNIEnv* charsetConversionJava::getJavaEnv(bool* bDetach)
{
    JavaVM* javaVM = get_imebra_javaVM();
    JNIEnv* env;

    // double check it's all ok
    int getEnvStat = javaVM->GetEnv((void **)&env, JNI_VERSION_1_6);
    if (getEnvStat == JNI_EDETACHED)
    {
        if (javaVM->AttachCurrentThread(&env, 0) == 0)
        {
            *bDetach = true;
            return env;
        }
    }
    else if (getEnvStat == JNI_OK)
    {
        *bDetach = false;
        return env;
    }
    return 0;
}


} // namespace puntoexe



#endif
