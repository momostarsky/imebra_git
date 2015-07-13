/*
$fileHeader$
*/

/*! \file dataHandlerStringUT.cpp
    \brief Implementation of the class dataHandlerStringUT.

*/

#include "../include/dataHandlerStringUT.h"

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
// dataHandlerStringUT
//
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

std::uint8_t dataHandlerStringUT::getPaddingByte() const
{
	return 0x20;
}

std::uint32_t dataHandlerStringUT::getUnitSize() const
{
	return 0;
}

std::uint32_t dataHandlerStringUT::maxSize() const
{
	return 0;
}

wchar_t dataHandlerStringUT::getSeparator() const
{
	return 0;
}

} // namespace handlers

} // namespace imebra

} // namespace puntoexe
