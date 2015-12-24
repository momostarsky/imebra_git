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

dataHandlerStringPN::dataHandlerStringPN(const charsetsList::tCharsetsList& initialCharsetsList): dataHandlerStringUnicode("PN", L'=', 0x20, initialCharsetsList)
{
}

std::uint32_t dataHandlerStringPN::getUnitSize() const
{
	return 0;
}

std::uint32_t dataHandlerStringPN::maxSize() const
{
	return 64;
}

} // namespace handlers

} // namespace imebra

} // namespace puntoexe
