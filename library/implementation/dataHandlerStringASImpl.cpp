/*
$fileHeader$
*/

/*! \file dataHandlerStringAS.cpp
    \brief Implementation of the class dataHandlerStringAS.

*/

#include <sstream>
#include <iomanip>

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
	IMEBRA_FUNCTION_START(L"dataHandlerStringAS::getAge");

    std::string ageString = getString(index);
    if(ageString.size() != 4)
    {
        throw;
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
        throw;
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
	IMEBRA_FUNCTION_START(L"dataHandlerStringAS::getSignedLong");

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
	IMEBRA_FUNCTION_START(L"dataHandlerStringAS::getUnsignedLong");

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
	IMEBRA_FUNCTION_START(L"dataHandlerStringAS::getDouble");

    ageUnit_t ageUnit;
	double age = (double)getAge(index, &ageUnit);

    switch (ageUnit)
    {
    case ageUnit_t::days:
        return age / (double)365;

    case ageUnit_t::weeks:
        return age / 52.14;

    case ageUnit_t::months:
        return age / (double)12;

    case ageUnit_t::years:
        return age;

    default:
        throw;
    }

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
    IMEBRA_FUNCTION_START(L"dataHandlerStringAS::setAge");

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
	IMEBRA_FUNCTION_START(L"dataHandlerStringAS::setSignedLong");

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
	IMEBRA_FUNCTION_START(L"dataHandlerStringAS::setUnsignedLong");

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
	IMEBRA_FUNCTION_START(L"dataHandlerStringAS::setDouble");

	if(value < 0)
	{
        setAge(index, 0, ageUnit_t::days);
	}
	if(value < 0.08)
	{
        setAge(index, (std::uint32_t)(value * 365), ageUnit_t::days);
		return;
	}
	if(value < 0.5)
	{
        setAge(index, (std::uint32_t)(value * 52.14), ageUnit_t::weeks);
		return;
	}
	if(value < 2)
	{
        setAge(index, (std::uint32_t)(value * 12), ageUnit_t::months);
		return;
	}
    setAge(index, (std::uint32_t)value, ageUnit_t::years);

	IMEBRA_FUNCTION_END();
}


} // namespace handlers

} // namespace implementation

} // namespace imebra
