/*
$fileHeader$
*/

/*! \file definitions.h
    \brief Declaration of the enumeration classes and custom types.
*/

#if !defined(imebraDefinitions__INCLUDED_)
#define imebraDefinitions__INCLUDED_

#include <cstdint>
#include <vector>
#include <string>

#ifndef SWIG

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

#ifdef IMEBRA_DLL // defined if Imebra is compiled as a DLL
  #ifdef IMEBRA_DLL_EXPORTS // defined if we are building the Imebra DLL (instead of using it)
    #define IMEBRA_API IMEBRA_HELPER_DLL_EXPORT
  #else
    #define IMEBRA_API IMEBRA_HELPER_DLL_IMPORT
  #endif // IMEBRA_DLL_EXPORTS
#else // IMEBRA_DLL is not defined: this means Imebra is a static lib.
  #define IMEBRA_API
#endif // IMEBRA_DLL

#endif // SWIG

namespace imebra
{

///
/// \brief Used by setAge() and getAge() to specify the unit of the age value.
///
///////////////////////////////////////////////////////////////////////////////
enum class ageUnit_t: char
{
    days = 'D',   ///< the age value is in days
    weeks = 'W',  ///< the age value is in weeks
    months = 'M', ///< the age value is in months
    years = 'Y'   ///< the age value is in years
};


///
///
/// \brief This enumeration specifies the quality of the compressed image
///        when a lossy compression format is used.
///
///////////////////////////////////////////////////////////////////////////////
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


///
/// \brief Defines the size (in bytes) of the memory allocated for each
///        pixel's color component and its representation (signed/unsigned).
///
/// This enumeration does not specify the highest bit used:
/// in order to retrieve the highest used bit call Image::getHighBit().
///
///////////////////////////////////////////////////////////////////////////////
enum class bitDepth_t: std::uint32_t
{
    depthU8 = 0,    ///< Unsigned byte
    depthS8 = 1,    ///< Signed byte
    depthU16 = 2,   ///< Unsigned word (2 bytes)
    depthS16 = 3,   ///< Signed word (2 bytes)
    depthU32 = 4,   ///< Unsigned double word (4 bytes)
    depthS32 = 5    ///< Signed double word (4 bytes)
};


///
/// \brief Specifies the directory item's type.
///
///////////////////////////////////////////////////////////////////////////////
enum class directoryRecordType_t: std::uint32_t
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


///
/// \brief Defines the data stream & images codec.
///
///////////////////////////////////////////////////////////////////////////////
enum class codecType_t: std::uint32_t
{
    dicom,
    jpeg
};

#define MAKE_VR_ENUM(string) ((((std::uint16_t)string[0]) << 8) | (std::uint16_t)string[1])

enum class tagVR_t: std::uint32_t
{
    AE = MAKE_VR_ENUM("AE"), ///< Application Entity
    AS = MAKE_VR_ENUM("AS"),
    AT = MAKE_VR_ENUM("AT"),
    CS = MAKE_VR_ENUM("CS"),
    DA = MAKE_VR_ENUM("DA"),
    DS = MAKE_VR_ENUM("DS"),
    DT = MAKE_VR_ENUM("DT"),
    FL = MAKE_VR_ENUM("FL"),
    FD = MAKE_VR_ENUM("FD"),
    IS = MAKE_VR_ENUM("IS"),
    LO = MAKE_VR_ENUM("LO"),
    LT = MAKE_VR_ENUM("LT"),
    OB = MAKE_VR_ENUM("OB"),
    SB = MAKE_VR_ENUM("SB"), // Non standard. Used internally for signed bytes
    OD = MAKE_VR_ENUM("OD"),
    OF = MAKE_VR_ENUM("OF"),
    OL = MAKE_VR_ENUM("OL"),
    OW = MAKE_VR_ENUM("OW"),
    PN = MAKE_VR_ENUM("PN"),
    SH = MAKE_VR_ENUM("SH"),
    SL = MAKE_VR_ENUM("SL"),
    SQ = MAKE_VR_ENUM("SQ"),
    SS = MAKE_VR_ENUM("SS"),
    ST = MAKE_VR_ENUM("ST"),
    TM = MAKE_VR_ENUM("TM"),
    UC = MAKE_VR_ENUM("UC"),
    UI = MAKE_VR_ENUM("UI"),
    UL = MAKE_VR_ENUM("UL"),
    UN = MAKE_VR_ENUM("UN"),
    UR = MAKE_VR_ENUM("UR"),
    US = MAKE_VR_ENUM("US"),
    UT = MAKE_VR_ENUM("UT")
};




typedef std::vector<std::string> fileParts_t;


///
/// \brief Defines the type of the bitmap generated by DrawBitmap.
///
///////////////////////////////////////////////////////////////////////////////
enum class drawBitmapType_t: std::uint32_t
{
    drawBitmapRGB  = 0, ///< Generates a BMP image where each pixel contains 3 bytes (R, G and B)
    drawBitmapBGR  = 1, ///< Generates a BMP image where each pixel contains 3 bytes (B, G and R)
    drawBitmapRGBA = 2, ///< Generates a BMP image where each pixel contains 4 bytes (R, G, B and A)
    drawBitmapBGRA = 3  ///< Generates a BMP image where each pixel contains 4 bytes (B, G, R and A)
};


///
/// \brief Specifies an age, in days, weeks, months or years.
///
///////////////////////////////////////////////////////////////////////////////
struct IMEBRA_API Age
{
    /// \brief Constructor.
    ///
    /// \param initialAge the initial age to assign to the object, in days, weeks,
    ///                   months or years, depending on the parameter initialUnits
    /// \param initialUnits the units of the value in initialAge
    ///
    ///////////////////////////////////////////////////////////////////////////////
    Age(std::uint32_t initialAge, ageUnit_t initialUnits);

    /// \brief Return the age in years.
    ///
    /// \return the stored age converted to years.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    double years() const;

    std::uint32_t age;   ///< The age, in days, weeks, months or years according to units
    ageUnit_t     units; ///< The units of the value in age

};


///
/// \brief Stores a Date, Time or Date/Time value.
///
///////////////////////////////////////////////////////////////////////////////
struct IMEBRA_API Date
{
    /// \brief Constructor.
    ///
    /// Initialize the Date structure with the specified values.
    ///
    /// \param initialYear    year (0 = unused)
    /// \param initialMonth   month (1...12, 0 = unused)
    /// \param initialDay     day of the month (1...31, 0 = unused)
    /// \param initialHour    hour (0...23)
    /// \param initialMinutes minutes (0...59)
    /// \param initialSeconds seconds (0...59)
    /// \param initialNanoseconds nanoseconds
    /// \param initialOffseHours    hours offset from UTC
    /// \param initialOffsetMinutes minutes offset from UTC
    ///////////////////////////////////////////////////////////////////////////////
    Date(const std::uint32_t initialYear,
         const std::uint32_t initialMonth,
         const std::uint32_t initialDay,
         const std::uint32_t initialHour,
         const std::uint32_t initialMinutes,
         const std::uint32_t initialSeconds,
         const std::uint32_t initialNanoseconds,
         const std::int32_t initialOffsetHours,
         const std::int32_t initialOffsetMinutes);

    std::uint32_t year;         ///< Year (0 = unused)
    std::uint32_t month;        ///< Month (1...12, 0 = unused)
    std::uint32_t day;          ///< Day (1...12, 0 = unused)
    std::uint32_t hour;         ///< Hours
    std::uint32_t minutes;      ///< Minutes
    std::uint32_t seconds;      ///< Seconds
    std::uint32_t nanoseconds;  ///< Nanoseconds
    std::int32_t offsetHours;   ///< Offset hours from UTC
    std::int32_t offsetMinutes; ///< Offset minutes from UTC

};


typedef std::vector<std::uint16_t> groups_t;

} // namespace imebra

#endif // imebraDefinitions__INCLUDED_
