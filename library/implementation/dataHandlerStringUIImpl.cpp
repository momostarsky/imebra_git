/*
$fileHeader$
*/

/*! \file dataHandlerStringUI.cpp
    \brief Implementation of the class dataHandlerStringUI.

*/

#include "dataHandlerStringUIImpl.h"

namespace puntoexe
{

namespace imebra
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
    readingDataHandlerString(parseMemory, "UI", 0x0, 0x0)
{
}

writingDataHandlerStringUI::writingDataHandlerStringUI(const std::shared_ptr<buffer> &pBuffer):
    writingDataHandlerString(pBuffer, "UI", 0x0, 0, 64, 0x0)
{
}

} // namespace handlers

} // namespace imebra

} // namespace puntoexe
