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

imbxUint8 dataHandlerStringLT::getPaddingByte() const
{
	return 0x20;
}

imbxUint32 dataHandlerStringLT::getUnitSize() const
{
	return 0;
}

imbxUint32 dataHandlerStringLT::maxSize() const
{
	return 10240L;
}

wchar_t dataHandlerStringLT::getSeparator() const
{
	return 0;
}

} // namespace handlers

} // namespace imebra

} // namespace puntoexe
