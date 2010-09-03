/*
$fileHeader$
*/

/*! \file dataHandlerStringUT.cpp
    \brief Implementation of the class dataHandlerStringUT.

*/

#include "../include/dataHandlerStringUT.h"

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
// dataHandlerStringUT
//
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

imbxUint8 dataHandlerStringUT::getPaddingByte() const
{
	return 0x20;
}

imbxUint32 dataHandlerStringUT::getUnitSize() const
{
	return 0;
}

imbxUint32 dataHandlerStringUT::maxSize() const
{
	return 0;
}

wchar_t dataHandlerStringUT::getSeparator() const
{
	return 0;
}

} // namespace handlers

} // namespace imebra

} // namespace puntoexe
