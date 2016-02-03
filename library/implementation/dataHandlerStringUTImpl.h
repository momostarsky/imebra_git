/*
$fileHeader$
*/

/*! \file dataHandlerStringUT.h
    \brief Declaration of the class dataHandlerStringUT.

*/

#if !defined(imebraDataHandlerStringUT_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
#define imebraDataHandlerStringUT_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_

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
// dataHandlerStringUT
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class readingDataHandlerStringUT : public readingDataHandlerStringUnicode
{
public:
    readingDataHandlerStringUT(const memory& parseMemory, const charsetsList::tCharsetsList& charsets);
};

class writingDataHandlerStringUT: public writingDataHandlerStringUnicode
{
public:
    writingDataHandlerStringUT(const std::shared_ptr<buffer>& pBuffer, const charsetsList::tCharsetsList& charsets);
};

} // namespace handlers

} // namespace implementation

} // namespace imebra

#endif // !defined(imebraDataHandlerStringUT_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
