/*
$fileHeader$
*/

/*! \file dataHandlerStringCS.cpp
    \brief Implementation of the class dataHandlerStringCS.

*/

#include "../include/dataHandlerStringCS.h"

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
// dataHandlerStringCS
//
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

std::uint8_t dataHandlerStringCS::getPaddingByte() const
{
	return 0x20;
}

std::uint32_t dataHandlerStringCS::getUnitSize() const
{
	return 0;
}

std::uint32_t dataHandlerStringCS::maxSize() const
{
	return 16;
}

} // namespace handlers

} // namespace imebra

} // namespace puntoexe
