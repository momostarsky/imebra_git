/*
$fileHeader$
*/

/*! \file dataHandlerStringIS.h
    \brief Declaration of the class dataHandlerStringIS.

*/

#if !defined(imebraDataHandlerStringIS_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
#define imebraDataHandlerStringIS_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_

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
/// \brief Handles the Dicom type "IS" (integer string)
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class dataHandlerStringIS : public dataHandlerString
{
public:
	// Overwritten to use getSignedLong()
	///////////////////////////////////////////////////////////
	virtual double getDouble();

	// Overwritten to use setSignedLong()
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

#endif // !defined(imebraDataHandlerStringIS_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
