/*
$fileHeader$
*/

/*! \file dataHandlerStringCS.cpp
    \brief Implementation of the class dataHandlerStringCS.

*/

#include "dataHandlerStringCSImpl.h"

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

dataHandlerStringCS::dataHandlerStringCS(): dataHandlerString(L'\\', 0x20)
{
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
