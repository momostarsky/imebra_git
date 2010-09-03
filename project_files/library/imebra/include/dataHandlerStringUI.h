/*
$fileHeader$
*/

/*! \file dataHandlerStringUI.h
    \brief Declaration of the class dataHandlerStringUI.

*/

#if !defined(imebraDataHandlerStringUI_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
#define imebraDataHandlerStringUI_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_

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
//
//
// dataHandlerStringUI
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class dataHandlerStringUI : public dataHandlerString
{
public:
	virtual imbxUint8 getPaddingByte() const;

	virtual imbxUint32 getUnitSize() const;

protected:
	// Return the maximum string's length
	///////////////////////////////////////////////////////////
	virtual imbxUint32 maxSize() const;

	// Returns the separator
	///////////////////////////////////////////////////////////
	virtual wchar_t getSeparator() const;
};

} // namespace handlers

} // namespace imebra

} // namespace puntoexe

#endif // !defined(imebraDataHandlerStringUI_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
