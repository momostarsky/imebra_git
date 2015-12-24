/*
$fileHeader$
*/

/*! \file dataHandlerStringUI.cpp
    \brief Implementation of the class dataHandlerStringUI.

*/

#include "dataHandlerStringUIImpl.h"

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
// dataHandlerStringUI
//
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

dataHandlerStringUI::dataHandlerStringUI(): dataHandlerString("UI", 0x0, 0x0)
{
}

std::uint32_t dataHandlerStringUI::getUnitSize() const
{
	return 0;
}

std::uint32_t dataHandlerStringUI::maxSize() const
{
	return 64;
}

} // namespace handlers

} // namespace imebra

} // namespace puntoexe
