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

/*!
\brief Handles the Dicom type "PN" (person name).

This class separates the component groups of the name.

The person name can be formed by three groups:
 one or more groups can be absent.
- the first components group contains a character
  representation of the person name
- the second components group contains an ideographic
  representation of the person name
- the third components group contains a phonetic
  representation of the patient name

Inside a components group, the name components
 (first name, middle name, surname, etc) must be
 separated by a ^.

This class doesn't insert or parse the ^ separator
 which must be inserted and handled by the calling
 application, but handles the = separator which
 separates the components groups.\n
This means that to read or set all the patient name
 you have to move the pointer to the internal element
 by using setPointer(), incPointer() or skip().

For instance, to set the name "Left^Arrow" both
 with a character and an ideographic representation you
 have to use the following code:

\code
myDataSet->getDataHandler(group, 0, tag, 0, true, "PN");
myDataSet->setSize(2);
myDataSet->setUnicodeString(L"Left^Arrow");
myDataSet->incPointer();
myDataSet->setUnicodeString(L"<-"); // :-)
\endcode

*/
class dataHandlerStringPN : public dataHandlerStringUnicode
{
public:
	virtual imbxUint8 getPaddingByte();

	virtual imbxUint32 getUnitSize();

protected:
	// Return the maximum string's length
	///////////////////////////////////////////////////////////
	virtual imbxUint32 maxSize();

	// Returns the separator =
	///////////////////////////////////////////////////////////
	virtual wchar_t getSeparator();
};

} // namespace handlers

} // namespace imebra

} // namespace puntoexe

#endif // !defined(imebraDataHandlerStringPN_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
