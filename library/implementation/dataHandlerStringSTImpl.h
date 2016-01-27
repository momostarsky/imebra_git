/*
$fileHeader$
*/

/*! \file dataHandlerStringST.h
    \brief Declaration of the class dataHandlerStringST.

*/

#if !defined(imebraDataHandlerStringST_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
#define imebraDataHandlerStringST_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_

#include "dataHandlerStringUnicodeImpl.h"


///////////////////////////////////////////////////////////
//
// Everything is in the namespace imebra::implementation
//
///////////////////////////////////////////////////////////
namespace imebra
{

namespace implementation
{

namespace handlers
{

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// dataHandlerStringST
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class readingDataHandlerStringST : public readingDataHandlerStringUnicode
{
public:
    readingDataHandlerStringST(const memory& parseMemory, const charsetsList::tCharsetsList& charsets);
};

class writingDataHandlerStringST: public writingDataHandlerStringUnicode
{
public:
    writingDataHandlerStringST(const std::shared_ptr<buffer>& pBuffer, const charsetsList::tCharsetsList& charsets);
};

} // namespace handlers

} // namespace implementation

} // namespace imebra

#endif // !defined(imebraDataHandlerStringST_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
