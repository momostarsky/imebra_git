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

imbxUint8 dataHandlerStringPN::getPaddingByte() const
{
	return 0x20;
}

imbxUint32 dataHandlerStringPN::getUnitSize() const
{
	return 0;
}

imbxUint32 dataHandlerStringPN::maxSize() const
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
