/*
$fileHeader$
*/

/*! \file baseStream_swig.h
    \brief Declaration of the the base class for the streams (memory, file, ...)
            for SWIG.
*/

#if !defined(imebraDefinitions_SWIG_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_)
#define imebraDefinitions_SWIG_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_

// Generic helper definitions for shared library support
#if defined _WIN32 || defined __CYGWIN__
  #define IMEBRA_HELPER_DLL_IMPORT __declspec(dllimport)
  #define IMEBRA_HELPER_DLL_EXPORT __declspec(dllexport)
#else
  #if __GNUC__ >= 4
    #define IMEBRA_HELPER_DLL_IMPORT __attribute__ ((visibility ("default")))
    #define IMEBRA_HELPER_DLL_EXPORT __attribute__ ((visibility ("default")))
  #else
    #define IMEBRA_HELPER_DLL_IMPORT
    #define IMEBRA_HELPER_DLL_EXPORT
  #endif
#endif


// IMEBRA_API is used for the public API symbols
// IMEBRA_LOCAL is used for non-api symbols

#ifdef IMEBRA_DLL // defined if Imebra is compiled as a DLL
  #ifdef IMEBRA_DLL_EXPORTS // defined if we are building the Imebra DLL (instead of using it)
    #define IMEBRA_API IMEBRA_HELPER_DLL_EXPORT
  #else
    #define IMEBRA_API IMEBRA_HELPER_DLL_IMPORT
  #endif // IMEBRA_DLL_EXPORTS
#else // IMEBRA_DLL is not defined: this means Imebra is a static lib.
  #define IMEBRA_API
#endif // IMEBRA_DLL






namespace imebra
{

/// \brief Used by setAge() and getAge() to specify the
///         unit of the age value.
///
///////////////////////////////////////////////////////////
enum class ageUnit_t: char
{
    days = L'D',   ///< the age value is in days
    weeks = L'W',  ///< the age value is in weeks
    months = L'M', ///< the age value is in months
    years = L'Y'   ///< the age value is in years
};


}

#endif // imebraDefinitions_SWIG_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_
