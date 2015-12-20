/*
$fileHeader$
*/

/*! \file dataHandlerStringUT.cpp
    \brief Implementation of the class dataHandlerStringUT.

*/

#include "dataHandlerStringUTImpl.h"

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

dataHandlerStringUT::dataHandlerStringUT(): dataHandlerStringUnicode(0x0, 0x20)
{
}

std::uint32_t dataHandlerStringUT::getUnitSize() const
{
	return 0;
}

std::uint32_t dataHandlerStringUT::maxSize() const
{
	return 0;
}

} // namespace handlers

} // namespace imebra

} // namespace puntoexe
