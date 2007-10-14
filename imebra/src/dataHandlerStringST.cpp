/*
$fileHeader$
*/

/*! \file dataHandlerStringST.cpp
    \brief Implementation of the class dataHandlerStringST.

*/

#include "../include/dataHandlerStringST.h"

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
// imebraDataHandlerStringST
//
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

imbxUint8 dataHandlerStringST::getPaddingByte()
{
	return 0x20;
}

imbxUint32 dataHandlerStringST::getUnitSize()
{
	return 0;
}

imbxUint32 dataHandlerStringST::maxSize()
{
	return 1024L;
}

wchar_t dataHandlerStringST::getSeparator()
{
	return 0;
}

} // namespace handlers

} // namespace imebra

} // namespace puntoexe
