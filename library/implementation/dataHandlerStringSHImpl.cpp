/*
$fileHeader$
*/

/*! \file dataHandlerStringSH.cpp
    \brief Implementation of the class dataHandlerStringSH.

*/

#include "dataHandlerStringSHImpl.h"

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

dataHandlerStringSH::dataHandlerStringSH(const charsetsList::tCharsetsList& initialCharsetsList): dataHandlerStringUnicode("SH", L'\\', 0x20, initialCharsetsList)
{
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
