/*
$fileHeader$
*/

/*! \file dataHandlerStringSH.h
    \brief Declaration of the class dataHandlerStringSH.

*/

#if !defined(imebraDataHandlerStringSH_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
#define imebraDataHandlerStringSH_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_

#include "dataHandlerStringUnicodeImpl.h"


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
// dataHandlerStringSH
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class dataHandlerStringSH : public dataHandlerStringUnicode
{
public:
	virtual std::uint8_t getPaddingByte() const;

	virtual std::uint32_t getUnitSize() const;

protected:
	// Return the maximum string's length
	///////////////////////////////////////////////////////////
	virtual std::uint32_t maxSize() const;

};

} // namespace handlers

} // namespace imebra

} // namespace puntoexe

#endif // !defined(imebraDataHandlerStringSH_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
