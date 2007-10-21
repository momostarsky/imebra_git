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

imbxUint8 dataHandlerStringPN::getPaddingByte()
{
	return 0x20;
}

imbxUint32 dataHandlerStringPN::getUnitSize()
{
	return 0;
}

imbxUint32 dataHandlerStringPN::maxSize()
{
	return 64;
}

wchar_t dataHandlerStringPN::getSeparator()
{
	return L'=';
}

} // namespace handlers

} // namespace imebra

} // namespace puntoexe
