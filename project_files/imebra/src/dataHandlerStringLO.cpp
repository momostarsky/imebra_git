/*
$fileHeader$
*/

/*! \file dataHandlerStringLO.cpp
    \brief Implementation of the class dataHandlerStringLO.

*/

#include "../include/dataHandlerStringLO.h"

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

imbxUint8 dataHandlerStringLO::getPaddingByte()
{
	return 0x20;
}

imbxUint32 dataHandlerStringLO::getUnitSize()
{
	return 0;
}

imbxUint32 dataHandlerStringLO::maxSize()
{
	return 64;
}

} // namespace handlers

} // namespace imebra

} // namespace puntoexe
