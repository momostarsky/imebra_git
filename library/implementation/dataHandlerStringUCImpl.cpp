/*
$fileHeader$
*/

/*! \file dataHandlerStringUC.cpp
    \brief Implementation of the class dataHandlerStringUC.

*/

#include "dataHandlerStringUCImpl.h"

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
// dataHandlerStringUC
//
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

readingDataHandlerStringUC::readingDataHandlerStringUC(const memory &parseMemory, const charsetsList::tCharsetsList &charsets):
    readingDataHandlerStringUnicode(parseMemory, charsets, tagVR_t::UC, L'\\', 0x20)
{
}

writingDataHandlerStringUC::writingDataHandlerStringUC(const std::shared_ptr<buffer> &pBuffer, const charsetsList::tCharsetsList &charsets):
    writingDataHandlerStringUnicode(pBuffer, charsets, tagVR_t::UC, L'\\', 0, 4294967294, 0x20)
{
}

} // namespace handlers

} // namespace implementation

} // namespace imebra
