/*
$fileHeader$
*/

/*! \file dataHandlerStringST.cpp
    \brief Implementation of the class dataHandlerStringST.

*/

#include "dataHandlerStringSTImpl.h"

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

std::uint8_t dataHandlerStringST::getPaddingByte() const
{
	return 0x20;
}

std::uint32_t dataHandlerStringST::getUnitSize() const
{
	return 0;
}

std::uint32_t dataHandlerStringST::maxSize() const
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
