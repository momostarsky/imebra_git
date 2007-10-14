/*
$fileHeader$
*/

/*! \file dataHandlerStringLT.cpp
    \brief Implementation of the class dataHandlerStringLT.

*/

#include "../include/dataHandlerStringLT.h"

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
// dataHandlerStringLT
//
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

imbxUint8 dataHandlerStringLT::getPaddingByte()
{
	return 0x20;
}

imbxUint32 dataHandlerStringLT::getUnitSize()
{
	return 0;
}

imbxUint32 dataHandlerStringLT::maxSize()
{
	return 10240L;
}

wchar_t dataHandlerStringLT::getSeparator()
{
	return 0;
}

} // namespace handlers

} // namespace imebra

} // namespace puntoexe
