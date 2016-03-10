/*
$fileHeader$
*/

/*! \file definitions.h
    \brief Declaration of the enumeration classes and custom types.
*/

#if !defined(imebraDefinitions__INCLUDED_)
#define imebraDefinitions__INCLUDED_

#include <set>
#include <cstdint>
#include <list>
#include <string>

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

/// \brief All the Imebra interfaces are defined in the imebra namespace.
///
///
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

///
/// \brief This enumeration specifies the quality of the
///        compressed image when a lossy compression format
///        is used.
///
///////////////////////////////////////////////////////////
enum class imageQuality_t: std::uint32_t
{
    veryHigh = 0,      ///< the image is saved with very high quality. No subsampling is performed and no quantization
    high = 100,        ///< the image is saved with high quality. No subsampling is performed. Quantization ratios are low
    aboveMedium = 200, ///< the image is saved in medium quality. Horizontal subsampling is applied. Quantization ratios are low
    medium = 300,      ///< the image is saved in medium quality. Horizontal subsampling is applied. Quantization ratios are medium
    belowMedium = 400, ///< the image is saved in medium quality. Horizontal and vertical subsampling are applied. Quantization ratios are medium
    low = 500,         ///< the image is saved in low quality. Horizontal and vertical subsampling are applied. Quantization ratios are higher than the ratios used in the belowMedium quality
    veryLow = 600	   ///< the image is saved in low quality. Horizontal and vertical subsampling are applied. Quantization ratios are high
};

/// \brief Defines the size (in bytes) of the memory
///        allocated for each pixel's color component and
///        its representation (signed/unsigned).
///
/// This enumeration does not specify the highest bit used:
/// in order to retrieve the highest used bit call
/// getHighBit().
///////////////////////////////////////////////////////////
enum class bitDepth_t
{
    depthU8 = 0,    ///< Unsigned byte
    depthS8 = 1,    ///< Signed byte
    depthU16 = 2,   ///< Unsigned word (2 bytes)
    depthS16 = 3,   ///< Signed word (2 bytes)
    depthU32 = 4,   ///< Unsigned double word (4 bytes)
    depthS32 = 5    ///< Signed double word (4 bytes)
};

/// \brief Specifies the item's type.
///
///////////////////////////////////////////////////////////
enum class directoryRecordType_t
{
    patient,
    study,
    series,
    image,
    overlay,
    modality_lut,
    voi_lut,
    curve,
    topic,
    visit,
    results,
    interpretation,
    study_component,
    stored_print,
    rt_dose,
    rt_structure_set,
    rt_plan,
    rt_treat_record,
    presentation,
    waveform,
    sr_document,
    key_object_doc,
    spectroscopy,
    raw_data,
    registration,
    fiducial,
    mrdr,
    endOfDirectoryRecordTypes
};

enum class codecType_t
{
    dicom,
    jpeg
};



typedef std::list<std::string> fileParts_t;

/// \brief Defines the output type of
///         getBitmap().
///
///////////////////////////////////////////////////////////
enum class drawBitmapType_t
{
    drawBitmapRGB  = 0, ///< Generates a BMP image where each pixel contains 3 bytes (R, G and B)
    drawBitmapBGR  = 1, ///< Generates a BMP image where each pixel contains 3 bytes (B, G and R)
    drawBitmapRGBA = 2, ///< Generates a BMP image where each pixel contains 4 bytes (R, G, B and A)
    drawBitmapBGRA = 3  ///< Generates a BMP image where each pixel contains 4 bytes (B, G, R and A)
};

struct IMEBRA_API Age
{
    Age(std::uint32_t initialAge, ageUnit_t initialUnits);
    std::uint32_t age;
    ageUnit_t     units;
    double years();
};

struct IMEBRA_API Date
{
    Date(const std::uint32_t initialYear,
         const std::uint32_t initialMonth,
         const std::uint32_t initialDay,
         const std::uint32_t initialHour,
         const std::uint32_t initialMinutes,
         const std::uint32_t initialSeconds,
         const std::uint32_t initialNanoseconds,
         const std::int32_t initialOffsetHours,
         const std::int32_t initialOffsetMinutes);

    std::uint32_t year;
    std::uint32_t month;
    std::uint32_t day;
    std::uint32_t hour;
    std::uint32_t minutes;
    std::uint32_t seconds;
    std::uint32_t nanoseconds;
    std::int32_t offsetHours;
    std::int32_t offsetMinutes;

};


typedef std::set<std::uint16_t> groups_t;

} // namespace imebra

#endif // imebraDefinitions__INCLUDED_
