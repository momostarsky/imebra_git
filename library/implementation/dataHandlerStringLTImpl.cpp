/*
$fileHeader$
*/

/*! \file dataHandlerStringLT.cpp
    \brief Implementation of the class dataHandlerStringLT.

*/

#include "dataHandlerStringLTImpl.h"

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
// dataHandlerStringLT
//
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

dataHandlerStringLT::dataHandlerStringLT(const charsetsList::tCharsetsList& initialCharsetsList): dataHandlerStringUnicode("LT", 0x0, 0x20, initialCharsetsList)
{
}

std::uint32_t dataHandlerStringLT::getUnitSize() const
{
	return 0;
}

std::uint32_t dataHandlerStringLT::maxSize() const
{
	return 10240L;
}

} // namespace handlers

} // namespace imebra

} // namespace puntoexe
