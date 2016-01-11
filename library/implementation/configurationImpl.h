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

#if !defined(PUNTOEXE_WINDOWS) && !defined(PUNTOEXE_POSIX)

#if defined(WIN32) || defined(WIN64)
#define PUNTOEXE_WINDOWS 1
#endif

#ifndef PUNTOEXE_WINDOWS
#define PUNTOEXE_POSIX 1
#endif

#endif

#if !defined(PUNTOEXE_USE_ICONV) && !defined(PUNTOEXE_USE_ICU) && !defined(PUNTOEXE_USE_WINDOWS_CHARSET) && !defined(PUNTOEXE_USE_JAVA)

#if defined(PUNTOEXE_WINDOWS)
    #define PUNTOEXE_USE_WINDOWS_CHARSET
#else
    #define PUNTOEXE_USE_ICONV
#endif
#endif

