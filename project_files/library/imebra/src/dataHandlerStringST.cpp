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

imbxUint8 dataHandlerStringST::getPaddingByte() const
{
	return 0x20;
}

imbxUint32 dataHandlerStringST::getUnitSize() const
{
	return 0;
}

imbxUint32 dataHandlerStringST::maxSize() const
{
	return 1024L;
}

wchar_t dataHandlerStringST::getSeparator() const
{
	return 0;
}

} // namespace handlers

} // namespace imebra

} // namespace puntoexe
