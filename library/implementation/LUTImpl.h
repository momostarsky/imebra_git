/*
$fileHeader$
*/

/*! \file LUT.h
    \brief Declaration of the class lut.

*/

#if !defined(imebraLUT_C2D59748_5D38_4b12_BA16_5EC22DA7C0E7__INCLUDED_)
#define imebraLUT_C2D59748_5D38_4b12_BA16_5EC22DA7C0E7__INCLUDED_

#include <map>
#include <memory>


///////////////////////////////////////////////////////////
//
// Everything is in the namespace puntoexe::imebra
//
///////////////////////////////////////////////////////////
namespace puntoexe
{

namespace imebra
{

namespace handlers
{
    class readingDataHandler;
    class writingDataHandler;
}

/// \addtogroup group_image
///
/// @{

///////////////////////////////////////////////////////////
/// \brief Represents a Lookup table (LUT).
///
/// The lookup table maps a value stored into an image
///  into another value that must be used for the
///  visualization or for the analysis of the image.
///
/// 3 lookups tables can be joined together to form a
///  color palette.
///
///////////////////////////////////////////////////////////
class lut
{
public:
	// Constructor
	///////////////////////////////////////////////////////////
	lut():
	  m_size(0),
		m_firstMapped(0),
		m_bits(0),
		m_bChecked(false),
		m_bValid(false),
		m_pMappedValues(0){}

    // Destructor
    ///////////////////////////////////////////////////////////
    virtual ~lut();


	/// \brief Initializes the lut with the values stored in
	///         three data handlers, usually retrieved from
	///         a dataset.
	///
	/// @param pDescriptor   the handler that manages the
	///                       lut descriptor (size, first
	///                       mapped value and number of bits)
	/// @param pData         the handler that manages the
	///                       lut data
	/// @param description   a string that describes the
	///                       lut
	///
	///////////////////////////////////////////////////////////
    void setLut(std::shared_ptr<handlers::readingDataHandler> pDescriptor, std::shared_ptr<handlers::readingDataHandler> pData, const std::wstring& description);

	/// \brief Create an empty lut.
	///
	/// Subsequent calls to setLutValue() must be made in
	///  order to fill the lut with the data.
	///
	/// @param size          the number of mapped values that
	///                       will be set by setLutValue()
	/// @param firstMapped   the id of the first mapped value
	/// @param bits          the number of bits to use to
	///                       store the mapped values
	/// @param description   a string that describes the lut
	///
	///////////////////////////////////////////////////////////
    void create(std::uint32_t size, std::int32_t firstMapped, std::uint8_t bits, const std::wstring& description);

	/// \brief Store a mapped value in the lut.
	///
	/// This function has to be called if the lut has been
	///  created by create().
	///
	/// Call this function for every mapped value that must be
	///  stored in the lut.
	///
	/// @param startValue   the id of the mapped value
	/// @param lutValue     the mapped value
	///
	///////////////////////////////////////////////////////////
	void setLutValue(std::int32_t startValue, std::int32_t lutValue);

	/// \brief Fill the data handlers with the lut's descriptor
	///         and the lut's data.
	///
	/// This function is usually called when a lut has to be
	///  written in a dataSet.
	///
	/// @param pDescriptor   the data handler that manages the
	///                       buffer that will store the lut
	///                       descriptor
	/// @param pData         the data handler that manages the
	///                       buffer that will store the lut
	///                       data
	///
	///////////////////////////////////////////////////////////
    void fillHandlers(std::shared_ptr<handlers::writingDataHandler> pDescriptor, std::shared_ptr<handlers::writingDataHandler> pData);

	/// \brief Return the lut's description.
	///
	/// @return the lut description
	///
	///////////////////////////////////////////////////////////
	std::wstring getDescription();

	/// \brief Return the number of bits used to store a mapped
	///         value.
	///
	/// @return the number of bits used to store a mapped value
	///
	///////////////////////////////////////////////////////////
	std::uint8_t getBits();

	/// \brief Return the lut's size.
	///
	/// @return the number of mapped value stored in the lut
	///
	///////////////////////////////////////////////////////////
	size_t getSize();

	/// \brief Checks if the data in the LUT is consistent
	///         with the number of bits specified in number
	///         of bits.
	///
	/// @return true if the data is correct, false otherwise
	///
	///////////////////////////////////////////////////////////
	bool checkValidDataRange();

	/// \brief Return the id of the first mapped value
	///
	/// @return the id of the first mapped value
	///
	///////////////////////////////////////////////////////////
	std::int32_t getFirstMapped();

	/// \brief Retrieve the value mapped by the specified id.
	///
	/// @param  id the id to look for
	/// @return the value mapped by the specified id
	///
	///////////////////////////////////////////////////////////
	std::int32_t mappedValue(std::int32_t id);

	/// \brief Retrieve tha id that maps the specified value.
	///
	/// @param  lutValue the value to look for in the lut
	/// @return the id that maps the specified value
	///
	///////////////////////////////////////////////////////////
	std::int32_t mappedValueRev(std::int32_t lutValue);

	/// \brief Copy the lut's data into an std::int32_t array.
	///
	/// @param pDestination a pointer to the first element of
	///                      the std::int32_t array
	/// @param destSize     the size of the array, in elements
	/// @param pFirstMapped a pointer to a variable that this
	///                      function will fill with the id
	///                      of the first mapped element
	///
	///////////////////////////////////////////////////////////
	void copyToInt32(std::int32_t* pDestination, std::uint32_t destSize, std::int32_t* pFirstMapped);

    size_t m_size;
	std::int32_t m_firstMapped;
	std::uint8_t m_bits;

	bool m_bChecked;
	bool m_bValid;

	std::wstring m_description;

	std::int32_t* m_pMappedValues;
	std::map<std::int32_t, std::int32_t> m_mappedValuesRev;
};


/// \brief Represents an RGB color palette.
///
/// A color palette uses 3 lut objects to represent the
///  colors.
///
///////////////////////////////////////////////////////////
class palette
{
public:
    /// \brief Construct the color palette.
    ///
    /// @param red   the lut containing the red components
    /// @param green the lut containing the green components
    /// @param blue  the lut containing the blue components
    ///
    ///////////////////////////////////////////////////////////
    palette(std::shared_ptr<lut> red, std::shared_ptr<lut> green, std::shared_ptr<lut> blue);

    /// \brief Set the luts that form the color palette.
    ///
    /// @param red   the lut containing the red components
    /// @param green the lut containing the green components
    /// @param blue  the lut containing the blue components
    ///
    ///////////////////////////////////////////////////////////
    void setLuts(std::shared_ptr<lut> red, std::shared_ptr<lut> green, std::shared_ptr<lut> blue);

    /// \brief Retrieve the lut containing the red components.
    ///
    /// @return the lut containing the red components
    ///
    ///////////////////////////////////////////////////////////
    std::shared_ptr<lut> getRed();

    /// \brief Retrieve the lut containing the green components.
    ///
    /// @return the lut containing the green components
    ///
    ///////////////////////////////////////////////////////////
    std::shared_ptr<lut> getGreen();

    /// \brief Retrieve the lut containing the blue components.
    ///
    /// @return the lut containing the blue components
    ///
    ///////////////////////////////////////////////////////////
    std::shared_ptr<lut> getBlue();

protected:
    std::shared_ptr<lut> m_redLut;
    std::shared_ptr<lut> m_greenLut;
    std::shared_ptr<lut> m_blueLut;
};


///////////////////////////////////////////////////////////
/// \brief This is the base class for the exceptions thrown
///         by the lut class
///
///////////////////////////////////////////////////////////
class lutException: public std::runtime_error
{
public:
	lutException(const std::string& message): std::runtime_error(message){}
};


///////////////////////////////////////////////////////////
/// \brief This exception is thrown by the lut class when
///         the wrong index or id is specified as a
///         parameter.
///
///////////////////////////////////////////////////////////
class lutExceptionWrongIndex: public lutException
{
public:
	lutExceptionWrongIndex(const std::string& message): lutException(message){}
};


///////////////////////////////////////////////////////////
/// \brief This exception is thrown by the lut class when
///         the the LUT information is corrupted.
///
///////////////////////////////////////////////////////////
class lutExceptionCorrupted: public lutException
{
public:
	lutExceptionCorrupted(const std::string& message): lutException(message){}
};

/// @}


} // namespace imebra

} // namespace puntoexe

#endif // !defined(imebraLUT_C2D59748_5D38_4b12_BA16_5EC22DA7C0E7__INCLUDED_)
