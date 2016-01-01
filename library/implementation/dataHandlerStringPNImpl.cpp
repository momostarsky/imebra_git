/*
$fileHeader$
*/

/*! \file dataHandlerStringPN.cpp
    \brief Implementation of the class dataHandlerStringPN.

*/

#include "dataHandlerStringPNImpl.h"

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
// dataHandlerStringPN
//
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

readingDataHandlerStringPN::readingDataHandlerStringPN(const memory& parseMemory, const charsetsList::tCharsetsList& charsets):
    readingDataHandlerStringUnicode(parseMemory, charsets, "PN", L'=', 0x20)
{
}

writingDataHandlerStringPN::writingDataHandlerStringPN(const std::shared_ptr<buffer>& pBuffer, const charsetsList::tCharsetsList& charsets):
    writingDataHandlerStringUnicode(pBuffer, charsets, "PN", L'=', 0, 64, 0x20)
{
}

} // namespace handlers

} // namespace imebra

} // namespace puntoexe
