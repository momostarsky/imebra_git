/*
$fileHeader$
*/

/*! \file dataHandlerStringDS.cpp
    \brief Implementation of the class dataHandlerStringDS.

*/

#include <sstream>
#include <iomanip>

#include "exceptionImpl.h"
#include "dataHandlerStringDSImpl.h"

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
// dataHandlerStringDS
//
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

readingDataHandlerStringDS::readingDataHandlerStringDS(const memory& parseMemory): readingDataHandlerString(parseMemory, "DS", '\\', 0x20)
{
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Get the value as a signed long.
// Overwritten to use getDouble()
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::int32_t readingDataHandlerStringDS::getSignedLong(const size_t index) const
{
	IMEBRA_FUNCTION_START(L"dataHandlerStringDS::getSignedLong");

	return (std::int32_t)getDouble(index);

	IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Get the value as an unsigned long.
// Overwritten to use getDouble()
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::uint32_t readingDataHandlerStringDS::getUnsignedLong(const size_t index) const
{
	IMEBRA_FUNCTION_START(L"dataHandlerStringDS::getUnsignedLong");

    return (std::uint32_t)getDouble(index);

	IMEBRA_FUNCTION_END();
}


writingDataHandlerStringDS::writingDataHandlerStringDS(const std::shared_ptr<buffer> pBuffer):
    writingDataHandlerString(pBuffer, "DS", '\\', 0, 16, 0x20)
{

}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Set the value as a signed long.
// Overwritten to use setDouble()
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void writingDataHandlerStringDS::setSignedLong(const size_t index, const std::int32_t value)
{
	IMEBRA_FUNCTION_START(L"dataHandlerStringDS::setSignedLong");

	setDouble(index, (double)value);

	IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Set the value as an unsigned long.
// Overwritten to use setDouble()
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void writingDataHandlerStringDS::setUnsignedLong(const size_t index, const std::uint32_t value)
{
	IMEBRA_FUNCTION_START(L"dataHandlerStringDS::setUnsignedLong");

	setDouble(index, (double)value);

	IMEBRA_FUNCTION_END();
}

} // namespace handlers

} // namespace imebra

} // namespace puntoexe
