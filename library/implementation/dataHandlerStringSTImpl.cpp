/*
$fileHeader$
*/

/*! \file dataHandlerStringST.cpp
    \brief Implementation of the class dataHandlerStringST.

*/

#include "dataHandlerStringSTImpl.h"

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
// imebraDataHandlerStringST
//
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

readingDataHandlerStringST::readingDataHandlerStringST(const memory& parseMemory, const charsetsList::tCharsetsList& charsets):
    readingDataHandlerStringUnicode(parseMemory, charsets, tagVR_t::ST, 0x0, 0x20)
{
}

writingDataHandlerStringST::writingDataHandlerStringST(const std::shared_ptr<buffer> &pBuffer, const charsetsList::tCharsetsList &charsets):
    writingDataHandlerStringUnicode(pBuffer, charsets, tagVR_t::ST, 0x0, 0, 1024, 0x20)
{
}


} // namespace handlers

} // namespace implementation

} // namespace imebra
