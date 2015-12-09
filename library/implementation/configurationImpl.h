/*
$fileHeader$
*/

/*! \file configuration.h
    \brief Declaration of the basic data types and of the platform flags
	        (Posix or Windows)

*/

#include <cstdint>

/// \addtogroup group_baseclasses
///
/// @{

/// @deprecated Use std::uint8_t instead
///
/// This type represents a 1 byte unsigned integer.
///
typedef std::uint8_t imbxUint8;

/// @deprecated Use std::uint16_t instead
///
/// This type represents a 2 bytes unsigned integer.
///
typedef std::uint16_t imbxUint16;

/// @deprecated Use std::uint32_t instead
///
/// This type represents a 4 bytes unsigned integer.
///
typedef std::uint32_t  imbxUint32;

/// @deprecated Use std::int8_t instead
///
/// This type represents an 1 byte signed integer.
///
typedef std::int8_t    imbxInt8;

/// @deprecated Use std::int16_t instead
///
/// This type represents a 2 bytes signed integer.
///
typedef std::int16_t   imbxInt16;

/// @deprecated Use std::int32_t instead
///
/// This type represents a 8 bytes signed integer.
///
typedef std::int32_t    imbxInt32;

typedef std::int64_t imbxInt64;

typedef std::uint64_t imbxUint64;

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

///@}
