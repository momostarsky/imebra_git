/*
$fileHeader$
*/

/*! \file configuration.h
    \brief Declaration of the basic data types and of the platform flags
	        (Posix or Windows)

*/


/// This type represents a 1 byte unsigned integer.
typedef unsigned char  imbxUint8;

/// This type represents a 2 bytes unsigned integer.
typedef unsigned short imbxUint16;

/// This type represents a 4 bytes unsigned integer.
typedef unsigned int  imbxUint32;

/// This type represents an 1 byte signed integer.
typedef signed char    imbxInt8;

/// This type represents a 2 bytes signed integer.
typedef signed short   imbxInt16;

/// This type represents a 4 bytes signed integer.
typedef signed int    imbxInt32;


#if !defined(PUNTOEXE_WINDOWS) && !defined(PUNTOEXE_POSIX)

#ifdef WIN32
#define PUNTOEXE_WINDOWS 1
#endif

#ifndef PUNTOEXE_WINDOWS
#define PUNTOEXE_POSIX 1
#endif

#endif



