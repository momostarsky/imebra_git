/*
$fileHeader$
*/

/*! \file dataHandlerStringLO.cpp
    \brief Implementation of the class dataHandlerStringLO.

*/

#include "dataHandlerStringLOImpl.h"

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
// dataHandlerStringLO
//
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

dataHandlerStringLO::dataHandlerStringLO(const charsetsList::tCharsetsList& initialCharsetsList): dataHandlerStringUnicode("LO", L'\\', 0x20, initialCharsetsList)
{
}

std::uint32_t dataHandlerStringLO::getUnitSize() const
{
	return 0;
}

std::uint32_t dataHandlerStringLO::maxSize() const
{
	return 64;
}

} // namespace handlers

} // namespace imebra

} // namespace puntoexe
