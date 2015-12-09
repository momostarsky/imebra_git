/*
$fileHeader$
*/

/*! \file dataHandlerStringDS.h
    \brief Declaration of the class dataHandlerStringDS.

*/

#if !defined(imebraDataHandlerStringDS_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
#define imebraDataHandlerStringDS_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_

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
/// \brief Handles the Dicom type "DS" (decimal string)
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class dataHandlerStringDS : public dataHandlerString
{
public:
	// Overwritten to use getDouble()
	///////////////////////////////////////////////////////////
	virtual std::int32_t getSignedLong(const std::uint32_t index) const;

	// Overwritten to use getDouble()
	///////////////////////////////////////////////////////////
	virtual std::uint32_t getUnsignedLong(const std::uint32_t index) const;

	// Overwritten to use setDouble()
	///////////////////////////////////////////////////////////
	virtual void setSignedLong(const std::uint32_t index, const std::int32_t value);

	// Overwritten to use setDouble()
	///////////////////////////////////////////////////////////
	virtual void setUnsignedLong(const std::uint32_t index, const std::uint32_t value);

	// Overwritten to use the exponential form if needed
	///////////////////////////////////////////////////////////
	virtual void setDouble(const std::uint32_t index, const double value);

	// Get the padding byte
	///////////////////////////////////////////////////////////
	virtual std::uint8_t getPaddingByte() const;

	// Get the element size
	///////////////////////////////////////////////////////////
	virtual std::uint32_t getUnitSize() const;

protected:
	// Return the maximum string's length
	///////////////////////////////////////////////////////////
	virtual std::uint32_t maxSize() const;

};

} // namespace handlers

} // namespace imebra

} // namespace puntoexe

#endif // !defined(imebraDataHandlerStringDS_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
