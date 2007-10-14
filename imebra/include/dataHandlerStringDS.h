/*
$fileHeader$
*/

/*! \file dataHandlerStringDS.h
    \brief Declaration of the class dataHandlerStringDS.

*/

#if !defined(imebraDataHandlerStringDS_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
#define imebraDataHandlerStringDS_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_

#include "dataHandlerString.h"


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
	virtual imbxInt32 getSignedLong();

	// Overwritten to use getDouble()
	///////////////////////////////////////////////////////////
	virtual imbxUint32 getUnsignedLong();

	// Overwritten to use setDouble()
	///////////////////////////////////////////////////////////
	virtual void setSignedLong(imbxInt32 value);

	// Overwritten to use setDouble()
	///////////////////////////////////////////////////////////
	virtual void setUnsignedLong(imbxUint32 value);

	// Overwritten to use the exponential form if needed
	///////////////////////////////////////////////////////////
	virtual void setDouble(double value);

	// Get the padding byte
	///////////////////////////////////////////////////////////
	virtual imbxUint8 getPaddingByte();

	// Get the element size
	///////////////////////////////////////////////////////////
	virtual imbxUint32 getUnitSize();

protected:
	// Return the maximum string's length
	///////////////////////////////////////////////////////////
	virtual imbxUint32 maxSize();

};

} // namespace handlers

} // namespace imebra

} // namespace puntoexe

#endif // !defined(imebraDataHandlerStringDS_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
