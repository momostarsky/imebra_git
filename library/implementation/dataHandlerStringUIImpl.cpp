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

std::uint8_t dataHandlerStringUI::getPaddingByte() const
{
	return 0x0;
}

std::uint32_t dataHandlerStringUI::getUnitSize() const
{
	return 0;
}

std::uint32_t dataHandlerStringUI::maxSize() const
{
	return 64;
}

wchar_t dataHandlerStringUI::getSeparator() const
{
	return 0;
}

} // namespace handlers

} // namespace imebra

} // namespace puntoexe
