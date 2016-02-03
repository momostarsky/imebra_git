/*
$fileHeader$
*/

/*! \file dataHandlerStringLT.h
    \brief Declaration of the class dataHandlerStringLT.

*/

#if !defined(imebraDataHandlerStringLT_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
#define imebraDataHandlerStringLT_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_

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
// dataHandlerStringLT
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class readingDataHandlerStringLT : public readingDataHandlerStringUnicode
{
public:
    readingDataHandlerStringLT(const memory& parseMemory, const charsetsList::tCharsetsList& charsets);
};

class writingDataHandlerStringLT: public writingDataHandlerStringUnicode
{
public:
    writingDataHandlerStringLT(const std::shared_ptr<buffer>& pBuffer, const charsetsList::tCharsetsList& charsets);
};

} // namespace handlers

} // namespace implementation

} // namespace imebra

#endif // !defined(imebraDataHandlerStringLT_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
