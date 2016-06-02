/*
$fileHeader$
*/

/*! \file dataHandlerStringLT.cpp
    \brief Implementation of the class dataHandlerStringLT.

*/

#include "dataHandlerStringLTImpl.h"

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
// dataHandlerStringLT
//
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

readingDataHandlerStringLT::readingDataHandlerStringLT(const memory& parseMemory, const charsetsList::tCharsetsList& initialCharsetsList):
    readingDataHandlerStringUnicode(parseMemory, initialCharsetsList, tagVR_t::LT, L'\\', 0x20)
{
}

writingDataHandlerStringLT::writingDataHandlerStringLT(const std::shared_ptr<buffer> &pBuffer, const charsetsList::tCharsetsList &charsets):
    writingDataHandlerStringUnicode(pBuffer, charsets, tagVR_t::LT, 0, 0, 10240, 0x20)
{
}

} // namespace handlers

} // namespace implementation

} // namespace imebra
