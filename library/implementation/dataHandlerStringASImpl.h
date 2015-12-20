/*
$fileHeader$
*/

/*! \file dataHandlerStringAS.h
    \brief Declaration of the class dataHandlerStringAS.

*/

#if !defined(imebraDataHandlerStringAS_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
#define imebraDataHandlerStringAS_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_

#include "dataHandlerStringImpl.h"


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


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief Handles the Dicom data type "AS" (age string)
///
/// The handler supplies two additional functions designed
///  to set/get the age (setAge() and getAge()) and 
///  overwrite the functions getSignedLong(), 
///  getUnsignedLong(), getDouble(), setSignedLong(),
///  setUnsignedLong(), setDouble() to make them work with
///  the years.
///
/// setDouble() and getDouble() work also with fraction
///  of a year, setting the age unit correctly (days, 
///  weeks, months or years).
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class dataHandlerStringAS : public dataHandlerString
{
public:
    dataHandlerStringAS();

	/// \brief Used by setAge() and getAge() to specify the
	///         unit of the age value.
	///
	///////////////////////////////////////////////////////////
	enum tAgeUnit
	{
		days = L'D',   ///< the age value is in days
		weeks = L'W',  ///< the age value is in weeks
		months = L'M', ///< the age value is in months
		years = L'Y'   ///< the age value is in years
	};
	
	/// \brief Set the value of the age string and specify
	///         its unit.
	///
	/// @param index the zero based index of the age value to
	///               read
	/// @param age   the age to be written in the buffer
	/// @param unit  the units used for the parameter age
	///
	///////////////////////////////////////////////////////////
	virtual void setAge(const std::uint32_t index, const std::uint32_t age, const tAgeUnit unit);

	/// \brief Retrieve the age value and its unit from the
	///         buffer handled by this handler.
	///
	/// @param index the zero based index of the age value to
	///               modify
	/// @param pUnit a pointer to a tAgeUnit that will be
	///               filled with the unit information related
	///               to the returned value
	/// @return the age, expressed in the unit written in the
	///               location referenced by the parameter 
	///               pUnit
	///
	///////////////////////////////////////////////////////////
	virtual std::uint32_t getAge(const std::uint32_t index, tAgeUnit* pUnit) const;

	/// \brief Retrieve the age from the handled buffer.
	///
	/// The returned value is always expressed in years.
	///
	/// @param index the zero based index of the age value to
	///               read
	/// @return the age contained in the buffer converted into
	///          years
	///
	///////////////////////////////////////////////////////////
	virtual std::int32_t getSignedLong(const std::uint32_t index) const;

	/// \brief Retrieve the age from the handled buffer.
	///
	/// The returned value is always expressed in years.
	///
	/// @param index the zero based index of the age value to
	///               read
	/// @return the age contained in the buffer converted into
	///          years
	///
	///////////////////////////////////////////////////////////
	virtual std::uint32_t getUnsignedLong(const std::uint32_t index) const;

	/// \brief Retrieve the age from the handled buffer.
	///
	/// The returned value is always expressed in years.
	/// The function can return fraction of a year if the
	///  age contained in the buffer is expressed in days,
	///  weeks or months.
	///
	/// @param index the zero based index of the age value to
	///               read
	/// @return the age contained in the buffer converted into
	///          years
	///
	///////////////////////////////////////////////////////////
	virtual double getDouble(const std::uint32_t index) const;

	/// \brief Write the specified age into the handled buffer.
	///
	/// @param index the zero based index of the age value to
	///               modify
	/// @param value the age to be written, in years
	///
	///////////////////////////////////////////////////////////
	virtual void setSignedLong(const std::uint32_t index, const std::int32_t value);

	/// \brief Write the specified age into the handled buffer.
	///
	/// @param index the zero based index of the age value to
	///               modify
	/// @param value the age to be written, in years
	///
	///////////////////////////////////////////////////////////
	virtual void setUnsignedLong(const std::uint32_t index, const std::uint32_t value);

	/// \brief Write the specified age into the handled buffer.
	///
	/// If a fraction of a year is specified, then the function
	///  set the age in days, weeks or months according to
	///  the value of the fraction.
	///
	/// @param index the zero based index of the age value to
	///               modify
	/// @param value the age to be written, in years
	///
	///////////////////////////////////////////////////////////
	virtual void setDouble(const std::uint32_t index, const double value);

	virtual std::uint32_t getUnitSize() const;

protected:
	// Return the maximum string's length
	///////////////////////////////////////////////////////////
	virtual std::uint32_t maxSize() const;
};

} // namespace handlers

} // namespace imebra

} // namespace puntoexe

#endif // !defined(imebraDataHandlerStringAS_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
