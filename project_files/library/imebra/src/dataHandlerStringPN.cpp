/*
$fileHeader$
*/

/*! \file dataHandlerStringPN.cpp
    \brief Implementation of the class dataHandlerStringPN.

*/

#include "../include/dataHandlerStringPN.h"

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

std::uint8_t dataHandlerStringPN::getPaddingByte() const
{
	return 0x20;
}

std::uint32_t dataHandlerStringPN::getUnitSize() const
{
	return 0;
}

std::uint32_t dataHandlerStringPN::maxSize() const
{
	return 64;
}

wchar_t dataHandlerStringPN::getSeparator() const
{
	return L'=';
}

} // namespace handlers

} // namespace imebra

} // namespace puntoexe
