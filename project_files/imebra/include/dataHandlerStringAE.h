/*
$fileHeader$
*/

/*! \file dataHandlerStringAE.h
    \brief Declaration of the class dataHandlerStringAE.

*/

#if !defined(imebraDataHandlerStringAE_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
#define imebraDataHandlerStringAE_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_

#include "dataHandlerString.h"
#include <map>
#include <string>


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
/// \brief Handles the Dicom data type "AE" (application
///         entity
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class dataHandlerStringAE : public dataHandlerString
{
public:
	virtual imbxUint8 getPaddingByte();

	virtual imbxUint32 getUnitSize();

protected:
	// Return the maximum string's length
	///////////////////////////////////////////////////////////
	virtual imbxUint32 maxSize();
};

} // namespace handlers

} // namespace imebra

} // namespace puntoexe

#endif // !defined(imebraDataHandlerStringAE_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
