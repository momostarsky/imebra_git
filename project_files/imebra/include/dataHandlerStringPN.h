/*
$fileHeader$
*/

/*! \file dataHandlerStringPN.h
    \brief Declaration of the class dataHandlerStringPN.

*/

#if !defined(imebraDataHandlerStringPN_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
#define imebraDataHandlerStringPN_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_

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
/// \brief Handles the Dicom type "PN" (patient name).
///
/// This class separates the components of the name.
///
/// This means that to read or set all the patient name
///  you have to move the pointer to the internal element
///  by using setPointer(), incPointer() or skip().
///
/// For instance, to set the name "Brandoli^Paolo" you
///  have to use the following code:
///
/// - myDataSet->getDataHandler(group, 0, tag, 0, true, "PN");
/// - myDataSet->setSize(2);
/// - myDataSet->setUnicodeString(L"Brandoli");
/// - myDataSet->incPointer();
/// - myDataSet->setUnicodeString(L"Paolo");
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class dataHandlerStringPN : public dataHandlerStringUnicode
{
public:
	virtual imbxUint8 getPaddingByte();

	virtual imbxUint32 getUnitSize();

protected:
	// Return the maximum string's length
	///////////////////////////////////////////////////////////
	virtual imbxUint32 maxSize();

	// Returns the separator ^
	///////////////////////////////////////////////////////////
	virtual wchar_t getSeparator();
};

} // namespace handlers

} // namespace imebra

} // namespace puntoexe

#endif // !defined(imebraDataHandlerStringPN_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
