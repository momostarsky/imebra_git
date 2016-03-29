/*
$fileHeader$
*/

/*! \file dataHandlerStringUI.cpp
    \brief Implementation of the class dataHandlerStringUI.

*/

#include "dataHandlerStringUIImpl.h"

namespace imebra
{

namespace implementation
{

namespace handlers
{

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
//
// dataHandlerStringUI
//
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

readingDataHandlerStringUI::readingDataHandlerStringUI(const memory& parseMemory):
    readingDataHandlerString(parseMemory, tagVR_t::UI, 0x0, 0x0)
{
}

writingDataHandlerStringUI::writingDataHandlerStringUI(const std::shared_ptr<buffer> &pBuffer):
    writingDataHandlerString(pBuffer, tagVR_t::UI, 0x0, 0, 64, 0x0)
{
}

} // namespace handlers

} // namespace implementation

} // namespace imebra
