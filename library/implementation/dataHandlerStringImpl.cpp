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
    PUNTOEXE_FUNCTION_START(L"readingDataHandlerString::readingDataHandlerString");

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

    for(size_t firstPosition(0); firstPosition != parseString.size(); )
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

    PUNTOEXE_FUNCTION_END();
}

// Get the data element as a signed long
///////////////////////////////////////////////////////////
std::int32_t readingDataHandlerString::getSignedLong(const size_t index) const
{
    std::istringstream conversion(m_strings.at(index));
    std::int32_t value;
    conversion >> value;
    return value;
}

// Get the data element as an unsigned long
///////////////////////////////////////////////////////////
std::uint32_t readingDataHandlerString::getUnsignedLong(const size_t index) const
{
    std::istringstream conversion(m_strings.at(index));
    std::uint32_t value;
    conversion >> value;
    return value;
}

// Get the data element as a double
///////////////////////////////////////////////////////////
double readingDataHandlerString::getDouble(const size_t index) const
{
    std::istringstream conversion(m_strings.at(index));
    double value;
    conversion >> value;
    return value;

}

// Get the data element as a string
///////////////////////////////////////////////////////////
std::string readingDataHandlerString::getString(const size_t index) const
{
    return m_strings.at(index);
}

// Get the data element as an unicode string
///////////////////////////////////////////////////////////
std::wstring readingDataHandlerString::getUnicodeString(const size_t index) const
{
    charsetsList::tCharsetsList charsets;
    charsets.push_back("ISO 2022 IR 6");
    return dicomConversion::convertToUnicode(getString(index), charsets);
}

// Retrieve the data element as a string
///////////////////////////////////////////////////////////
size_t readingDataHandlerString::getSize() const
{
    return m_strings.size();
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

    std::shared_ptr<memory> commitMemory = std::make_shared<memory>((std::uint32_t)completeString.size());
    commitMemory->assign((std::uint8_t*)completeString.data(), (std::uint32_t)completeString.size());

    // The buffer's size must be an even number
    ///////////////////////////////////////////////////////////
    std::uint32_t memorySize = commitMemory->size();
    if((memorySize & 0x1) != 0)
    {
        commitMemory->resize(++memorySize);
        *(commitMemory->data() + (memorySize - 1)) = m_paddingByte;
    }

    if(m_maxSize != 0 && commitMemory->size() > m_maxSize)
    {
        throw;
    }

    if(m_unitSize != 0 && commitMemory->size() > m_unitSize)
    {
        throw;
    }

    m_buffer->commit(commitMemory, m_dataType);
}

// Set the data element as a signed long
///////////////////////////////////////////////////////////
void writingDataHandlerString::setSignedLong(const size_t index, const std::int32_t value)
{
    std::ostringstream conversion;
    conversion << value;
    setString(index, conversion.str());
}

// Set the data element as an unsigned long
///////////////////////////////////////////////////////////
void writingDataHandlerString::setUnsignedLong(const size_t index, const std::uint32_t value)
{
    std::ostringstream conversion;
    conversion << value;
    setString(index, conversion.str());
}

// Set the data element as a double
///////////////////////////////////////////////////////////
void writingDataHandlerString::setDouble(const size_t index, const double value)
{
    std::ostringstream conversion;
    conversion << value;
    setString(index, conversion.str());
}

// Set the buffer's size, in data elements
///////////////////////////////////////////////////////////
void writingDataHandlerString::setSize(const size_t elementsNumber)
{
    m_strings.resize(elementsNumber);
}

size_t writingDataHandlerString::getSize() const
{
    return m_strings.size();
}

void writingDataHandlerString::setString(const size_t index, const std::string& value)
{
    m_strings[index] = value;
}

void writingDataHandlerString::setUnicodeString(const size_t index, const std::wstring& value)
{
    charsetsList::tCharsetsList charsets;
    charsets.push_back("ISO_IR 6");
    setString(index, dicomConversion::convertFromUnicode(value, &charsets));
}


} // namespace handlers

} // namespace imebra

} // namespace puntoexe
