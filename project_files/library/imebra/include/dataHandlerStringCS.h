/*
$fileHeader$
*/

/*! \file dataHandlerStringCS.h
    \brief Declaration of the class dataHandlerStringCS.

*/

#if !defined(imebraDataHandlerStringCS_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
#define imebraDataHandlerStringCS_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_

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
/// \brief Handles the Dicom data type "CS" (code string)
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class dataHandlerStringCS : public dataHandlerString
{
public:
	virtual imbxUint8 getPaddingByte() const;

	virtual imbxUint32 getUnitSize() const;

protected:
	// Return the maximum string's length
	///////////////////////////////////////////////////////////
	virtual imbxUint32 maxSize() const;
};

} // namespace handlers

} // namespace imebra

} // namespace puntoexe

#endif // !defined(imebraDataHandlerStringCS_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
