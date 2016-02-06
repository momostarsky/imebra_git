/*
$fileHeader$
*/

/*! \file dataHandlerStringUnicode.cpp
    \brief Implementation of the base class used by the string handlers that need
	        to handle several charsets.

*/

#include "exceptionImpl.h"
#include "dataHandlerStringUnicodeImpl.h"
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
// dataHandlerStringUnicode
//
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

readingDataHandlerStringUnicode::readingDataHandlerStringUnicode(const memory& parseMemory, const charsetsList::tCharsetsList& charsets, const std::string& dataType, const wchar_t separator, const std::uint8_t paddingByte):
    readingDataHandler(dataType)
{
    IMEBRA_FUNCTION_START();

    std::string asciiString((const char*)parseMemory.data(), parseMemory.size());
    std::wstring parseString(dicomConversion::convertToUnicode(asciiString, charsets));

    while(!parseString.empty() && parseString.back() == (wchar_t)paddingByte)
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

    IMEBRA_FUNCTION_END();

}

// Get the data element as a signed long
///////////////////////////////////////////////////////////
std::int32_t readingDataHandlerStringUnicode::getSignedLong(const size_t index) const
{
    IMEBRA_FUNCTION_START();

    std::wistringstream conversion(m_strings.at(index));
    std::int32_t value;
    if(!(conversion >> value))
    {
        IMEBRA_THROW(DataHandlerConversionError, "The string is not a number");
    }
    return value;

    IMEBRA_FUNCTION_END();
}

// Get the data element as an unsigned long
///////////////////////////////////////////////////////////
std::uint32_t readingDataHandlerStringUnicode::getUnsignedLong(const size_t index) const
{
    IMEBRA_FUNCTION_START();

    std::wistringstream conversion(m_strings.at(index));
    std::uint32_t value;
    if(!(conversion >> value))
    {
        IMEBRA_THROW(DataHandlerConversionError, "The string is not a number");
    }
    return value;

    IMEBRA_FUNCTION_END();
}

// Get the data element as a double
///////////////////////////////////////////////////////////
double readingDataHandlerStringUnicode::getDouble(const size_t index) const
{
    IMEBRA_FUNCTION_START();

    std::wistringstream conversion(m_strings.at(index));
    double value;
    if(!(conversion >> value))
    {
        IMEBRA_THROW(DataHandlerConversionError, "The string is not a number");
    }
    return value;

    IMEBRA_FUNCTION_END();
}

// Get the data element as a string
///////////////////////////////////////////////////////////
std::string readingDataHandlerStringUnicode::getString(const size_t index) const
{
    IMEBRA_FUNCTION_START();

    charsetsList::tCharsetsList charsets;
    charsets.push_back("ISO 2022 IR 6");
    return dicomConversion::convertFromUnicode(m_strings.at(index), &charsets);

    IMEBRA_FUNCTION_END();
}

// Get the data element as an unicode string
///////////////////////////////////////////////////////////
std::wstring readingDataHandlerStringUnicode::getUnicodeString(const size_t index) const
{
    IMEBRA_FUNCTION_START();

    return m_strings.at(index);

    IMEBRA_FUNCTION_END();
}

// Retrieve the data element as a string
///////////////////////////////////////////////////////////
size_t readingDataHandlerStringUnicode::getSize() const
{
    IMEBRA_FUNCTION_START();

    return m_strings.size();

    IMEBRA_FUNCTION_END();
}

writingDataHandlerStringUnicode::writingDataHandlerStringUnicode(const std::shared_ptr<buffer> &pBuffer, const charsetsList::tCharsetsList& charsets, const std::string &dataType, const wchar_t separator, const size_t unitSize, const size_t maxSize, const uint8_t paddingByte):
    writingDataHandler(pBuffer, dataType, paddingByte), m_charsets(charsets), m_separator(separator), m_unitSize(unitSize), m_maxSize(maxSize)
{

}

writingDataHandlerStringUnicode::~writingDataHandlerStringUnicode()
{
    IMEBRA_FUNCTION_START();

    std::wstring completeString;
    for(size_t stringsIterator(0); stringsIterator != m_strings.size(); ++stringsIterator)
    {
        if(stringsIterator != 0)
        {
            completeString += m_separator;
        }
        completeString += m_strings.at(stringsIterator);
    }

    std::string asciiString = dicomConversion::convertFromUnicode(completeString, &m_charsets);

    std::shared_ptr<memory> commitMemory = std::make_shared<memory>(asciiString.size());
    commitMemory->assign((std::uint8_t*)asciiString.data(), asciiString.size());

    // The buffer's size must be an even number
    ///////////////////////////////////////////////////////////
    size_t memorySize = commitMemory->size();
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

    IMEBRA_FUNCTION_END();
}

// Set the data element as a signed long
///////////////////////////////////////////////////////////
void writingDataHandlerStringUnicode::setSignedLong(const size_t index, const std::int32_t value)
{
    IMEBRA_FUNCTION_START();

    std::wostringstream conversion;
    conversion << value;
    setUnicodeString(index, conversion.str());

    IMEBRA_FUNCTION_END();
}

// Set the data element as an unsigned long
///////////////////////////////////////////////////////////
void writingDataHandlerStringUnicode::setUnsignedLong(const size_t index, const std::uint32_t value)
{
    IMEBRA_FUNCTION_START();

    std::wostringstream conversion;
    conversion << value;
    setUnicodeString(index, conversion.str());

    IMEBRA_FUNCTION_END();
}

// Set the data element as a double
///////////////////////////////////////////////////////////
void writingDataHandlerStringUnicode::setDouble(const size_t index, const double value)
{
    IMEBRA_FUNCTION_START();

    std::wostringstream conversion;
    conversion << value;
    setUnicodeString(index, conversion.str());

    IMEBRA_FUNCTION_END();
}

// Set the buffer's size, in data elements
///////////////////////////////////////////////////////////
void writingDataHandlerStringUnicode::setSize(const size_t elementsNumber)
{
    IMEBRA_FUNCTION_START();

    m_strings.resize(elementsNumber);

    IMEBRA_FUNCTION_END();
}

size_t writingDataHandlerStringUnicode::getSize() const
{
    IMEBRA_FUNCTION_START();

    return m_strings.size();

    IMEBRA_FUNCTION_END();
}

void writingDataHandlerStringUnicode::setString(const size_t index, const std::string& value)
{
    IMEBRA_FUNCTION_START();

    charsetsList::tCharsetsList charsets;
    charsets.push_back("ISO 2022 IR 6");
    setUnicodeString(index, dicomConversion::convertToUnicode(value, charsets));

    IMEBRA_FUNCTION_END();
}

void writingDataHandlerStringUnicode::setUnicodeString(const size_t index, const std::wstring& value)
{
    IMEBRA_FUNCTION_START();

    if(index >= getSize())
    {
        setSize(index + 1);
    }
    m_strings[index] = value;

    IMEBRA_FUNCTION_END();
}


} // namespace handlers

} // namespace implementation

} // namespace imebra
