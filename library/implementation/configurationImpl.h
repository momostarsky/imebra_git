/*
$fileHeader$
*/

/*! \file configuration.h
    \brief Declaration of the basic data types and of the platform flags
	        (Posix or Windows)

*/

#include <cstdint>

#ifndef MAXIMUM_IMAGE_WIDTH
    #define MAXIMUM_IMAGE_WIDTH 4096
#endif
#ifndef MAXIMUM_IMAGE_HEIGHT
    #define MAXIMUM_IMAGE_HEIGHT 4096
#endif

#if !defined(IMEBRA_WINDOWS) && !defined(IMEBRA_POSIX)

#if defined(_WIN32)
#define IMEBRA_WINDOWS 1
#endif

#ifndef IMEBRA_WINDOWS
#define IMEBRA_POSIX 1
#endif

#endif

#if !defined(IMEBRA_USE_ICONV) && !defined(IMEBRA_USE_ICU) && !defined(IMEBRA_USE_WINDOWS_CHARSET) && !defined(IMEBRA_USE_JAVA)

#if defined(IMEBRA_WINDOWS)
    #define IMEBRA_USE_WINDOWS_CHARSET
#else
    #define IMEBRA_USE_ICONV
#endif
#endif

