/*
$fileHeader$
*/

/*! \file dataHandlerStringCS.cpp
    \brief Implementation of the class dataHandlerStringCS.

*/

#include "dataHandlerStringCSImpl.h"

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
// dataHandlerStringCS
//
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

readingDataHandlerStringCS::readingDataHandlerStringCS(const memory &parseMemory):
    readingDataHandlerString(parseMemory, tagVR_t::CS, '\\', 0x20)
{
}

writingDataHandlerStringCS::writingDataHandlerStringCS(const std::shared_ptr<buffer> pBuffer):
    writingDataHandlerString(pBuffer, tagVR_t::CS, '\\', 0, 16, 0x20)
{
}

} // namespace handlers

} // namespace implementation

} // namespace imebra
