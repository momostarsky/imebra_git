/*
$fileHeader$
*/

/*! \file dataHandlerStringLO.cpp
    \brief Implementation of the class dataHandlerStringLO.

*/

#include "dataHandlerStringLOImpl.h"

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
// dataHandlerStringLO
//
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

readingDataHandlerStringLO::readingDataHandlerStringLO(const memory &parseMemory, const charsetsList::tCharsetsList &charsets):
    readingDataHandlerStringUnicode(parseMemory, charsets, tagVR_t::LO, L'\\', 0x20)
{
}

writingDataHandlerStringLO::writingDataHandlerStringLO(const std::shared_ptr<buffer> &pBuffer, const charsetsList::tCharsetsList &charsets):
    writingDataHandlerStringUnicode(pBuffer, charsets, tagVR_t::LO, L'\\', 0, 64, 0x20)
{
}

} // namespace handlers

} // namespace implementation

} // namespace imebra
