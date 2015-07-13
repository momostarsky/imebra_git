/*
$fileHeader$
*/

/*! \file dataHandlerStringLT.cpp
    \brief Implementation of the class dataHandlerStringLT.

*/

#include "../include/dataHandlerStringLT.h"

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

std::uint8_t dataHandlerStringLT::getPaddingByte() const
{
	return 0x20;
}

std::uint32_t dataHandlerStringLT::getUnitSize() const
{
	return 0;
}

std::uint32_t dataHandlerStringLT::maxSize() const
{
	return 10240L;
}

wchar_t dataHandlerStringLT::getSeparator() const
{
	return 0;
}

} // namespace handlers

} // namespace imebra

} // namespace puntoexe
