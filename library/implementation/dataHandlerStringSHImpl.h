/*
$fileHeader$
*/

/*! \file dataHandlerStringSH.h
    \brief Declaration of the class dataHandlerStringSH.

*/

#if !defined(imebraDataHandlerStringSH_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
#define imebraDataHandlerStringSH_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_

#include "dataHandlerStringUnicodeImpl.h"


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
// dataHandlerStringSH
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class readingDataHandlerStringSH : public readingDataHandlerStringUnicode
{
public:
    readingDataHandlerStringSH(const memory& parseMemory, const charsetsList::tCharsetsList& charsets);
};

class writingDataHandlerStringSH: public writingDataHandlerStringUnicode
{
public:
    writingDataHandlerStringSH(const std::shared_ptr<buffer>& pBuffer, const charsetsList::tCharsetsList& charsets);
};

} // namespace handlers

} // namespace implementation

} // namespace imebra

#endif // !defined(imebraDataHandlerStringSH_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
