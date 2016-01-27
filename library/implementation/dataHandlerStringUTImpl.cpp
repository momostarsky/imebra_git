/*
$fileHeader$
*/

/*! \file dataHandlerStringUT.cpp
    \brief Implementation of the class dataHandlerStringUT.

*/

#include "dataHandlerStringUTImpl.h"

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
// dataHandlerStringUT
//
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

readingDataHandlerStringUT::readingDataHandlerStringUT(const memory& parseMemory, const charsetsList::tCharsetsList& charsets):
    readingDataHandlerStringUnicode(parseMemory, charsets, "UT", 0x0, 0x20)
{
}

writingDataHandlerStringUT::writingDataHandlerStringUT(const std::shared_ptr<buffer> &pBuffer, const charsetsList::tCharsetsList &charsets):
    writingDataHandlerStringUnicode(pBuffer, charsets, "UT", 0x0, 0, 0, 0x20)
{
}

} // namespace handlers

} // namespace implementation

} // namespace imebra
