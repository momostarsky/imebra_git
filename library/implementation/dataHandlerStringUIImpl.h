/*
$fileHeader$
*/

/*! \file dataHandlerStringUI.h
    \brief Declaration of the class dataHandlerStringUI.

*/

#if !defined(imebraDataHandlerStringUI_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
#define imebraDataHandlerStringUI_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_

#include "dataHandlerStringImpl.h"


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
// dataHandlerStringUI
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class readingDataHandlerStringUI : public readingDataHandlerString
{
public:
    readingDataHandlerStringUI(const memory& parseMemory);
};

class writingDataHandlerStringUI: public writingDataHandlerString
{
public:
    writingDataHandlerStringUI(const std::shared_ptr<buffer>& pBuffer);
};

} // namespace handlers

} // namespace implementation

} // namespace imebra

#endif // !defined(imebraDataHandlerStringUI_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
