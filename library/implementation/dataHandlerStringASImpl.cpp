/*
$fileHeader$
*/

/*! \file dataHandlerStringAS.cpp
    \brief Implementation of the class dataHandlerStringAS.

*/

#include <sstream>
#include <iomanip>
#include "../include/imebra/exceptions.h"
#include "exceptionImpl.h"
#include "dataHandlerStringASImpl.h"

namespace imebra
{

namespace implementation
{

namespace handlers
{

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
//
// dataHandlerStringAS
//
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Constructor
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
readingDataHandlerStringAS::readingDataHandlerStringAS(const memory& parseMemory): readingDataHandlerString(parseMemory, "AS", '\\', 0x20)
{
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Retrieve the age
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::uint32_t readingDataHandlerStringAS::getAge(const size_t index, ageUnit_t* pUnit) const
{
    IMEBRA_FUNCTION_START();

    std::string ageString = getString(index);
    if(ageString.size() != 4)
    {
        IMEBRA_THROW(DataHandlerCorruptedBufferError, "The AGE string should be 4 bytes long but it is "<< ageString.size() << " bytes long");
    }
    std::istringstream ageStream(ageString);
	std::uint32_t age;
	ageStream >> age;
    char unit = ageString[3];
    if(
            unit != (char)ageUnit_t::days &&
            unit != (char)ageUnit_t::weeks &&
            unit == (char)ageUnit_t::months &&
            unit == (char)ageUnit_t::years)
    {
        IMEBRA_THROW(DataHandlerCorruptedBufferError, "The AGE unit should be D, W, M or Y but is ascii code "<< (int)unit);
    }
    *pUnit = (ageUnit_t)unit;
    return age;

	IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Retrieve the age in years as a signed long
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::int32_t readingDataHandlerStringAS::getSignedLong(const size_t index) const
{
    IMEBRA_FUNCTION_START();

	return (std::int32_t)getDouble(index);

	IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Retrieve the age in years as an unsigned long
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::uint32_t readingDataHandlerStringAS::getUnsignedLong(const size_t index) const
{
    IMEBRA_FUNCTION_START();

	return (std::int32_t)getDouble(index);

	IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Retrieve the age in years as a double
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
double readingDataHandlerStringAS::getDouble(const size_t index) const
{
    IMEBRA_FUNCTION_START();

    IMEBRA_THROW(DataHandlerDeniedConversionError, "Cannot convert an Age to a number")

	IMEBRA_FUNCTION_END();
}


writingDataHandlerStringAS::writingDataHandlerStringAS(const std::shared_ptr<buffer> &pBuffer):
    writingDataHandlerString(pBuffer, "AS", '\\', 4, 4, 0x20)
{
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Set the age
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void writingDataHandlerStringAS::setAge(const size_t index, const std::uint32_t age, const ageUnit_t unit)
{
    IMEBRA_FUNCTION_START();

    if(index >= getSize())
    {
        setSize(index + 1);
    }

    std::ostringstream ageStream;
    ageStream << std::setfill('0');
    ageStream << std::setw(3) << age;
    ageStream << std::setw(1) << (char)unit;

    setString(index, ageStream.str());

    IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Set the age in years as a signed long
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void writingDataHandlerStringAS::setSignedLong(const size_t index, const std::int32_t value)
{
    IMEBRA_FUNCTION_START();

	setDouble(index, (double)value);

	IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Set the age in years as an unsigned long
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void writingDataHandlerStringAS::setUnsignedLong(const size_t index, const std::uint32_t value)
{
    IMEBRA_FUNCTION_START();

	setDouble(index, (double)value);

	IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Set the age in years as a double
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void writingDataHandlerStringAS::setDouble(const size_t index, const double value)
{
    IMEBRA_FUNCTION_START();

    IMEBRA_THROW(DataHandlerDeniedConversionError, "Cannot convert VR AS to double");

	IMEBRA_FUNCTION_END();
}


} // namespace handlers

} // namespace implementation

} // namespace imebra
