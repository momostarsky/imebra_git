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

dataHandlerStringST::dataHandlerStringST(): dataHandlerStringUnicode(0x0, 0x20)
{
}

std::uint32_t dataHandlerStringST::getUnitSize() const
{
	return 0;
}

std::uint32_t dataHandlerStringST::maxSize() const
{
	return 1024L;
}

} // namespace handlers

} // namespace imebra

} // namespace puntoexe
