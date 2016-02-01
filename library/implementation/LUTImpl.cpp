/*
$fileHeader$
*/

/*! \file LUT.cpp
    \brief Implementation of the class lut.

*/

#include "exceptionImpl.h"
#include "LUTImpl.h"
#include "dataHandlerNumericImpl.h"
#include "../include/imebra/exceptions.h"

#include <string.h>

namespace imebra
{

namespace implementation
{

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Destructor
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
lut::~lut()
{
	if(m_pMappedValues)
	{
        delete[] m_pMappedValues;
	}
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Create a LUT from a data handler
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void lut::setLut(std::shared_ptr<handlers::readingDataHandler> pDescriptor, std::shared_ptr<handlers::readingDataHandler> pData, const std::wstring& description)
{
    IMEBRA_FUNCTION_START();

	if(pDescriptor->getSize() < 3)
	{
        IMEBRA_THROW(LutCorruptedError, "The LUT is corrupted");
	}
    std::uint32_t lutSize(descriptorSignedToUnsigned(pDescriptor->getSignedLong(0)));

    std::int32_t lutFirstMapped = pDescriptor->getSignedLong(1);

    std::uint32_t lutBits = pDescriptor->getUnsignedLong(2);

	if((size_t)lutSize != pData->getSize())
	{
        IMEBRA_THROW(LutCorruptedError, "The LUT is corrupted");
	}

	create(lutSize, lutFirstMapped, (std::uint8_t)lutBits, description);

    std::dynamic_pointer_cast<handlers::readingDataHandlerNumericBase>(pData)->copyTo(m_pMappedValues, lutSize);

    IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Convert a signed value in the lut descriptor into an
//  unsigned value
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::uint32_t lut::descriptorSignedToUnsigned(std::int32_t signedValue)
{
    if(signedValue == 0)
    {
        return 0x010000;
    }
    else if(signedValue < 0)
    {
        return (signedValue & 0x0FFFF);
    }
    else
    {
        return (std::uint32_t)signedValue;
    }
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Create a LUT
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void lut::create(std::uint32_t size, std::int32_t firstMapped, std::uint8_t bits, const std::wstring& description)
{
    IMEBRA_FUNCTION_START();

	// If some values were previously allocated, then remove
	//  them
	///////////////////////////////////////////////////////////
	if(m_pMappedValues)
	{
		delete m_pMappedValues;
		m_pMappedValues= 0;
	}

	m_size = 0;

	m_description = description;

    if(size != 0)
	{
        m_size = size;
        m_firstMapped = firstMapped;
        m_bits = bits;
        m_pMappedValues = new std::int32_t[m_size];
	}

    IMEBRA_FUNCTION_END();
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Fill the data handlers in a dataset with the lut
//  information
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void lut::fillHandlers(std::shared_ptr<handlers::writingDataHandler> pDescriptor, std::shared_ptr<handlers::writingDataHandler> pData) const
{
    IMEBRA_FUNCTION_START();

	pDescriptor->setSize(3);
    std::uint32_t lutSize = (std::uint32_t)getSize();
	if(lutSize == 0x00010000)
	{
		pDescriptor->setSignedLong(0, 0);
	}
	else
	{
		pDescriptor->setUnsignedLong(0, lutSize);
	}

    std::int32_t lutFirstMapped = getFirstMapped();
	pDescriptor->setSignedLong(1, lutFirstMapped);

	std::uint8_t bits = getBits();
	pDescriptor->setUnsignedLong(2, bits);

	pData->setSize(lutSize);
    std::dynamic_pointer_cast<handlers::writingDataHandlerNumericBase>(pData)->copyFrom(m_pMappedValues, lutSize);

    IMEBRA_FUNCTION_END();
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Retrieve the number of values stored into the LUT
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::uint32_t lut::getSize() const
{
	return m_size;
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Check the validity of the data in the LUT
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
bool lut::checkValidDataRange() const
{
    std::int32_t maxValue(65535);
    std::int32_t minValue(-32768);
    if(m_bits == 8)
    {
        maxValue = 255;
        minValue = -128;
    }
    const std::int32_t* pScanValues(m_pMappedValues);
    for(std::uint32_t checkData(0); checkData != m_size; ++checkData)
    {
        if(*pScanValues < minValue || *pScanValues > maxValue)
        {
            return false;
        }
        ++pScanValues;
    }
    return true;
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Retrieve the first mapped index
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::int32_t lut::getFirstMapped() const
{
	return m_firstMapped;
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Insert a new value into the LUT
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void lut::setLutValue(std::int32_t startValue, std::int32_t lutValue)
{
    IMEBRA_FUNCTION_START();

    if(startValue < m_firstMapped)
	{
        IMEBRA_THROW(LutWrongIndexError, "The start index is below the first mapped index");
	}
    startValue -= m_firstMapped;
    if(startValue < (std::int32_t)m_size)
	{
		m_pMappedValues[startValue]=lutValue;
	}

    IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Retrieve the lut's description.
// The returned value must be removed by the client
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::wstring lut::getDescription() const
{
	return m_description;
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Return the lut's bits
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::uint8_t lut::getBits() const
{
	return m_bits;
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Lookup the requested value
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::int32_t lut::mappedValue(std::int32_t id) const
{
	// The LUT's size is zero, return
	///////////////////////////////////////////////////////////
	if(m_size == 0)
	{
		return 0;
	}

	// Subtract the first mapped value
	///////////////////////////////////////////////////////////
    if(m_firstMapped > id)
    {
        return m_pMappedValues[0];
    }

    id -= m_firstMapped;
    if(id < (std::int32_t)m_size)
	{
        return m_pMappedValues[(std::uint32_t)id];
	}
	return m_pMappedValues[m_size-1];
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Copy the palette's data to an array of std::int32_t
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void lut::copyToInt32(std::int32_t* pDestination, size_t destSize, std::int32_t* pFirstMapped) const
{
	if(destSize > m_size)
	{
		destSize = m_size;
	}
    ::memcpy(pDestination, m_pMappedValues, destSize * sizeof(std::int32_t));
	*pFirstMapped = m_firstMapped;
}


palette::palette(std::shared_ptr<lut> red, std::shared_ptr<lut> green, std::shared_ptr<lut> blue):
m_redLut(red), m_greenLut(green), m_blueLut(blue)
{}

void palette::setLuts(std::shared_ptr<lut> red, std::shared_ptr<lut> green, std::shared_ptr<lut> blue)
{
	m_redLut = red;
	m_greenLut = green;
	m_blueLut = blue;
}

std::shared_ptr<lut> palette::getRed() const
{
	return m_redLut;
}

std::shared_ptr<lut> palette::getGreen() const
{
	return m_greenLut;
}

std::shared_ptr<lut> palette::getBlue() const
{
	return m_blueLut;
}

} // namespace implementation

} // namespace imebra
