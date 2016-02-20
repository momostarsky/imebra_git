/*
$fileHeader$
*/

/*! \file dataHandlerString.cpp
    \brief Implementation of the base class for the string handlers.

*/

#include <sstream>
#include <iomanip>

#include "exceptionImpl.h"
#include "dataHandlerStringImpl.h"
#include "memoryImpl.h"
#include "bufferImpl.h"

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
// dataHandlerString
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


readingDataHandlerString::readingDataHandlerString(const memory &parseMemory, const std::string &dataType, const char separator, const uint8_t paddingByte):
    readingDataHandler(dataType)
{
    IMEBRA_FUNCTION_START();

    std::string parseString((const char*)parseMemory.data(), parseMemory.size());
    while(!parseString.empty() && parseString.back() == (char)paddingByte)
    {
        parseString.pop_back();
    }

    if(separator == 0)
    {
        m_strings.push_back(parseString);
        return;
    }

    for(size_t firstPosition(0); ;)
    {
        size_t nextPosition = parseString.find(separator, firstPosition);
        if(nextPosition == std::string::npos)
        {
            m_strings.push_back(parseString.substr(firstPosition));
            return;
        }
        m_strings.push_back(parseString.substr(firstPosition, nextPosition - firstPosition));
        firstPosition = ++nextPosition;
    }

    IMEBRA_FUNCTION_END();
}

// Get the data element as a signed long
///////////////////////////////////////////////////////////
std::int32_t readingDataHandlerString::getSignedLong(const size_t index) const
{
    IMEBRA_FUNCTION_START();

    std::istringstream conversion(m_strings.at(index));
    std::int32_t value;
    if(!(conversion >> value))
    {
        IMEBRA_THROW(DataHandlerConversionError, "Cannot convert " << m_strings.at(index) << " to a number");
    }
    return value;

    IMEBRA_FUNCTION_END();
}

// Get the data element as an unsigned long
///////////////////////////////////////////////////////////
std::uint32_t readingDataHandlerString::getUnsignedLong(const size_t index) const
{
    IMEBRA_FUNCTION_START();

    std::istringstream conversion(m_strings.at(index));
    std::uint32_t value;
    if(!(conversion >> value))
    {
        IMEBRA_THROW(DataHandlerConversionError, "Cannot convert " << m_strings.at(index) << " to a number");
    }
    return value;

    IMEBRA_FUNCTION_END();
}

// Get the data element as a double
///////////////////////////////////////////////////////////
double readingDataHandlerString::getDouble(const size_t index) const
{
    IMEBRA_FUNCTION_START();

    std::istringstream conversion(m_strings.at(index));
    double value;
    if(!(conversion >> value))
    {
        IMEBRA_THROW(DataHandlerConversionError, "Cannot convert " << m_strings.at(index) << " to a number");
    }
    return value;

    IMEBRA_FUNCTION_END();
}

// Get the data element as a string
///////////////////////////////////////////////////////////
std::string readingDataHandlerString::getString(const size_t index) const
{
    IMEBRA_FUNCTION_START();

    return m_strings.at(index);

    IMEBRA_FUNCTION_END();
}

// Get the data element as an unicode string
///////////////////////////////////////////////////////////
std::wstring readingDataHandlerString::getUnicodeString(const size_t index) const
{
    IMEBRA_FUNCTION_START();

    charsetsList::tCharsetsList charsets;
    charsets.push_back("ISO 2022 IR 6");
    return dicomConversion::convertToUnicode(getString(index), charsets);

    IMEBRA_FUNCTION_END();
}

// Retrieve the data element as a string
///////////////////////////////////////////////////////////
size_t readingDataHandlerString::getSize() const
{
    IMEBRA_FUNCTION_START();

    return m_strings.size();

    IMEBRA_FUNCTION_END();
}

writingDataHandlerString::writingDataHandlerString(const std::shared_ptr<buffer> &pBuffer, const std::string &dataType, const char separator, const size_t unitSize, const size_t maxSize, const uint8_t paddingByte):
    writingDataHandler(pBuffer, dataType, paddingByte), m_separator(separator), m_unitSize(unitSize), m_maxSize(maxSize)
{
}

writingDataHandlerString::~writingDataHandlerString()
{
    std::string completeString;
    for(size_t stringsIterator(0); stringsIterator != m_strings.size(); ++stringsIterator)
    {
        if(stringsIterator != 0)
        {
            completeString += m_separator;
        }
        completeString += m_strings.at(stringsIterator);
    }

    std::shared_ptr<memory> commitMemory = std::make_shared<memory>(completeString.size());
    commitMemory->assign((std::uint8_t*)completeString.data(), completeString.size());

    // The buffer's size must be an even number
    ///////////////////////////////////////////////////////////
    size_t memorySize = commitMemory->size();
    if((memorySize & 0x1) != 0)
    {
        commitMemory->resize(++memorySize);
        *(commitMemory->data() + (memorySize - 1)) = m_paddingByte;
    }

    m_buffer->commit(commitMemory, m_dataType);
}

// Set the data element as a signed long
///////////////////////////////////////////////////////////
void writingDataHandlerString::setSignedLong(const size_t index, const std::int32_t value)
{
    IMEBRA_FUNCTION_START();

    std::ostringstream conversion;
    conversion << value;
    setString(index, conversion.str());

    IMEBRA_FUNCTION_END();
}

// Set the data element as an unsigned long
///////////////////////////////////////////////////////////
void writingDataHandlerString::setUnsignedLong(const size_t index, const std::uint32_t value)
{
    IMEBRA_FUNCTION_START();

    std::ostringstream conversion;
    conversion << value;
    setString(index, conversion.str());

    IMEBRA_FUNCTION_END();
}

// Set the data element as a double
///////////////////////////////////////////////////////////
void writingDataHandlerString::setDouble(const size_t index, const double value)
{
    IMEBRA_FUNCTION_START();

    std::ostringstream conversion;
    conversion << value;
    setString(index, conversion.str());

    IMEBRA_FUNCTION_END();
}

// Set the buffer's size, in data elements
///////////////////////////////////////////////////////////
void writingDataHandlerString::setSize(const size_t elementsNumber)
{
    IMEBRA_FUNCTION_START();

    m_strings.resize(elementsNumber);

    IMEBRA_FUNCTION_END();
}

size_t writingDataHandlerString::getSize() const
{
    IMEBRA_FUNCTION_START();

    return m_strings.size();

    IMEBRA_FUNCTION_END();
}

void writingDataHandlerString::setString(const size_t index, const std::string& value)
{
    IMEBRA_FUNCTION_START();

    if(m_maxSize != 0 && value.size() > m_maxSize)
    {
        throw;
    }

    if(m_unitSize != 0 && value.size() > m_unitSize)
    {
        throw;
    }

    if(index >= getSize())
    {
        setSize(index + 1);
    }
    m_strings[index] = value;

    IMEBRA_FUNCTION_END();
}

void writingDataHandlerString::setUnicodeString(const size_t index, const std::wstring& value)
{
    IMEBRA_FUNCTION_START();

    charsetsList::tCharsetsList charsets;
    charsets.push_back("ISO_IR 6");
    setString(index, dicomConversion::convertFromUnicode(value, &charsets));

    IMEBRA_FUNCTION_END();
}


} // namespace handlers

} // namespace implementation

} // namespace imebra
