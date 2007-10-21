/*
$fileHeader$
*/

/*! \file dataHandlerStringUI.cpp
    \brief Implementation of the class dataHandlerStringUI.

*/

#include "../include/dataHandlerStringUI.h"

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

imbxUint8 dataHandlerStringUI::getPaddingByte()
{
	return 0x0;
}

imbxUint32 dataHandlerStringUI::getUnitSize()
{
	return 0;
}

imbxUint32 dataHandlerStringUI::maxSize()
{
	return 64;
}

wchar_t dataHandlerStringUI::getSeparator()
{
	return 0;
}

} // namespace handlers

} // namespace imebra

} // namespace puntoexe
