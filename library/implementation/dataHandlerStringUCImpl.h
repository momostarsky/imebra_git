/*
$fileHeader$
*/

/*! \file dataHandlerStringUC.h
    \brief Declaration of the class dataHandlerStringUC.

*/

#if !defined(imebraDataHandlerStringUC_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
#define imebraDataHandlerStringUC_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_

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
// dataHandlerStringUC
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class readingDataHandlerStringUC : public readingDataHandlerStringUnicode
{
public:
    readingDataHandlerStringUC(const memory& parseMemory, const charsetsList::tCharsetsList& charsets);
};

class writingDataHandlerStringUC: public writingDataHandlerStringUnicode
{
public:
    writingDataHandlerStringUC(const std::shared_ptr<buffer>& pBuffer, const charsetsList::tCharsetsList& charsets);
};

} // namespace handlers

} // namespace implementation

} // namespace imebra

#endif // !defined(imebraDataHandlerStringUC_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
