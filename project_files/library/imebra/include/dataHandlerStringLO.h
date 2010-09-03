/*
$fileHeader$
*/

/*! \file dataHandlerStringLO.h
    \brief Declaration of the class dataHandlerStringLO.

*/

#if !defined(imebraDataHandlerStringLO_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
#define imebraDataHandlerStringLO_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_

#include "dataHandlerStringUnicode.h"


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
//
//
// dataHandlerStringLO
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class dataHandlerStringLO : public dataHandlerStringUnicode
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

#endif // !defined(imebraDataHandlerStringLO_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
