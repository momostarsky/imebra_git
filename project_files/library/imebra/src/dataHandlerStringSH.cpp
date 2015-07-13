/*
$fileHeader$
*/

/*! \file dataHandlerStringSH.cpp
    \brief Implementation of the class dataHandlerStringSH.

*/

#include "../include/dataHandlerStringSH.h"

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
// dataHandlerStringSH
//
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

std::uint8_t dataHandlerStringSH::getPaddingByte() const
{
	return 0x20;
}

std::uint32_t dataHandlerStringSH::getUnitSize() const
{
	return 0;
}

std::uint32_t dataHandlerStringSH::maxSize() const
{
	return 16;
}

} // namespace handlers

} // namespace imebra

} // namespace puntoexe
