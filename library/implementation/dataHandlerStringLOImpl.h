/*
$fileHeader$
*/

/*! \file dataHandlerStringLO.h
    \brief Declaration of the class dataHandlerStringLO.

*/

#if !defined(imebraDataHandlerStringLO_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
#define imebraDataHandlerStringLO_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_

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
// dataHandlerStringLO
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class readingDataHandlerStringLO : public readingDataHandlerStringUnicode
{
public:
    readingDataHandlerStringLO(const memory& parseMemory, const charsetsList::tCharsetsList& charsets);
};

class writingDataHandlerStringLO: public writingDataHandlerStringUnicode
{
public:
    writingDataHandlerStringLO(const std::shared_ptr<buffer>& pBuffer, const charsetsList::tCharsetsList& charsets);
};

} // namespace handlers

} // namespace implementation

} // namespace imebra

#endif // !defined(imebraDataHandlerStringLO_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
