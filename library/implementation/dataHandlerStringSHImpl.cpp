/*
$fileHeader$
*/

/*! \file dataHandlerStringSH.cpp
    \brief Implementation of the class dataHandlerStringSH.

*/

#include "dataHandlerStringSHImpl.h"

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
// dataHandlerStringSH
//
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

readingDataHandlerStringSH::readingDataHandlerStringSH(const memory& parseMemory, const charsetsList::tCharsetsList& charsets):
    readingDataHandlerStringUnicode(parseMemory, charsets, tagVR_t::SH, L'\\', 0x20)
{
}

writingDataHandlerStringSH::writingDataHandlerStringSH(const std::shared_ptr<buffer> &pBuffer, const charsetsList::tCharsetsList &charsets):
    writingDataHandlerStringUnicode(pBuffer, charsets, tagVR_t::SH, L'\\', 0, 16, 0x20)
{
}

} // namespace handlers

} // namespace implementation

} // namespace imebra
