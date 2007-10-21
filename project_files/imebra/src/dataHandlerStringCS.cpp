/*
$fileHeader$
*/

/*! \file dataHandlerStringCS.cpp
    \brief Implementation of the class dataHandlerStringCS.

*/

#include "../include/dataHandlerStringCS.h"

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

imbxUint8 dataHandlerStringCS::getPaddingByte()
{
	return 0x20;
}

imbxUint32 dataHandlerStringCS::getUnitSize()
{
	return 0;
}

imbxUint32 dataHandlerStringCS::maxSize()
{
	return 16;
}

} // namespace handlers

} // namespace imebra

} // namespace puntoexe
