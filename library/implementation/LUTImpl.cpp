/*
$fileHeader$
*/

/*! \file LUT.cpp
    \brief Implementation of the class lut.

*/

#include "exceptionImpl.h"
#include "LUTImpl.h"
#include "dataHandlerNumericImpl.h"
#include "bufferImpl.h"
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
// Create a LUT from a data handler
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
lut::lut(std::shared_ptr<handlers::readingDataHandlerNumericBase> pDescriptor, std::shared_ptr<handlers::readingDataHandlerNumericBase> pData, const std::wstring& description, bool signedData):
    m_size(0),
      m_firstMapped(0),
      m_bits(0)

{
    IMEBRA_FUNCTION_START();

    if(pDescriptor->getSize() < 3)
    {
        IMEBRA_THROW(LutCorruptedError, "The LUT is corrupted");
    }

    m_size = descriptorSignedToUnsigned(pDescriptor->getSignedLong(0));

    if(signedData)
    {
        m_firstMapped = pDescriptor->getSignedLong(1);
    }
    else
    {
        m_firstMapped = pDescriptor->getUnsignedLong(1);
    }

    m_bits = pDescriptor->getUnsignedLong(2);
    if(m_bits > 16)
    {
        IMEBRA_THROW(LutCorruptedError, "The LUT items cannot be more than 16 bit wide");
    }

    if(m_size != pData->getSize())
    {
        IMEBRA_THROW(LutCorruptedError, "The LUT is corrupted");
    }

    m_pDataHandler = pData;

    m_description = description;


    IMEBRA_FUNCTION_END();
}


std::shared_ptr<handlers::readingDataHandlerNumericBase> lut::getReadingDataHandler() const
{
    return m_pDataHandler;
}


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
    IMEBRA_FUNCTION_START();

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
// Retrieve the first mapped index
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::int32_t lut::getFirstMapped() const
{
	return m_firstMapped;
}


std::int32_t lut::getMappedValue(std::int32_t index) const
{
    IMEBRA_FUNCTION_START();

    if(index < m_firstMapped)
    {
        index = m_firstMapped;
    }

    std::uint32_t correctedIndex = (std::uint32_t)(index - m_firstMapped);
    if(correctedIndex >= m_size)
    {
        correctedIndex = m_size - 1;
    }
    return m_pDataHandler->getSignedLong(correctedIndex);

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


palette::palette(std::shared_ptr<lut> red, std::shared_ptr<lut> green, std::shared_ptr<lut> blue):
m_redLut(red), m_greenLut(green), m_blueLut(blue)
{}

void palette::setLuts(std::shared_ptr<lut> red, std::shared_ptr<lut> green, std::shared_ptr<lut> blue)
{
    IMEBRA_FUNCTION_START();

    m_redLut = red;
	m_greenLut = green;
	m_blueLut = blue;

    IMEBRA_FUNCTION_END();
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
