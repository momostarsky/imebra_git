/*
$fileHeader$
*/

/*! \file dataHandlerString.cpp
    \brief Implementation of the base class for the string handlers.

*/

#include <sstream>
#include <iomanip>

#include "exceptionImpl.h"
#include "dataHandlerStringBaseImpl.h"


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
dataHandlerStringBase::dataHandlerStringBase(const wchar_t separator, const std::uint8_t paddingByte): dataHandler(paddingByte), m_separator(separator)
{
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Parse the buffer
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void dataHandlerStringBase::parseBuffer(const ptr<memory>& memoryBuffer)
{
    PUNTOEXE_FUNCTION_START(L"dataHandlerStringBase::parseBuffer");

	m_strings.clear();

	// Convert the string to unicode
	///////////////////////////////////////////////////////////
	std::wstring tempBufferUnicode;
	std::uint32_t tempBufferSize(memoryBuffer->size());
	if(tempBufferSize != 0)
	{
		tempBufferUnicode = convertToUnicode(std::string((char*)(memoryBuffer->data()), tempBufferSize));
	}

	// Remove the extra spaces and zero bytes
	///////////////////////////////////////////////////////////
	size_t removeTrail;
	for(removeTrail = tempBufferUnicode.size(); removeTrail != 0 && (tempBufferUnicode[removeTrail - 1] == 0x20 || tempBufferUnicode[removeTrail - 1] == 0x0); --removeTrail){};
	tempBufferUnicode.resize(removeTrail);

	if( getSeparator() == 0)
	{
		m_strings.push_back(tempBufferUnicode);
		return;
	}

	size_t nextPosition;
	std::uint32_t unitSize=getUnitSize();
	for(size_t firstPosition = 0; firstPosition<tempBufferUnicode.size(); firstPosition = nextPosition)
	{
		nextPosition = tempBufferUnicode.find(getSeparator(), firstPosition);
		bool bSepFound=(nextPosition != tempBufferUnicode.npos);
		if(!bSepFound)
			nextPosition = tempBufferUnicode.size();

		if(unitSize && (nextPosition-firstPosition) > (size_t)unitSize)
			nextPosition=firstPosition+unitSize;

		m_strings.push_back(tempBufferUnicode.substr(firstPosition, nextPosition-firstPosition));

		if(bSepFound)
		{
			++nextPosition;
		}
	}

	PUNTOEXE_FUNCTION_END();
}



///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Returns TRUE if the pointer is valid
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
bool dataHandlerStringBase::pointerIsValid(const std::uint32_t index) const
{
    PUNTOEXE_FUNCTION_START(L"dataHandlerStringBase::pointerIsValid");

	return index < m_strings.size();

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Get data element as a signed long
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::int32_t dataHandlerStringBase::getSignedLong(const std::uint32_t index) const
{
    PUNTOEXE_FUNCTION_START(L"dataHandlerStringBase::getSignedLong");

	std::wstring tempString = getUnicodeString(index);
	std::wistringstream convStream(tempString);
	std::int32_t value;
	convStream >> value;
	return value;

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Get data element as an unsigned long
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::uint32_t dataHandlerStringBase::getUnsignedLong(const std::uint32_t index) const
{
    PUNTOEXE_FUNCTION_START(L"dataHandlerStringBase::getUnsignedLong");

	std::wstring tempString = getUnicodeString(index);
	std::wistringstream convStream(tempString);
	std::uint32_t value;
	convStream >> value;
	return value;

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Get data element as a double
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
double dataHandlerStringBase::getDouble(const std::uint32_t index) const
{
    PUNTOEXE_FUNCTION_START(L"dataHandlerStringBase::getDouble");

	std::wstring tempString = getUnicodeString(index);
	std::wistringstream convStream(tempString);
	double value;
	convStream >> value;
	return value;

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Get data element as a string
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::string dataHandlerStringBase::getString(const std::uint32_t index) const
{
    PUNTOEXE_FUNCTION_START(L"dataHandlerStringBase::getString");

    charsetsList::tCharsetsList localCharsetsList(m_charsetsList);
	return convertFromUnicode(getUnicodeString(index), &localCharsetsList);

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Get data element as an unicode string
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::wstring dataHandlerStringBase::getUnicodeString(const std::uint32_t index) const
{
    PUNTOEXE_FUNCTION_START(L"dataHandlerStringBase::getUnicodeString");

	if(index >= m_strings.size())
	{
		return L"";
	}
	return m_strings[index];

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Set data element as a signed long
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void dataHandlerStringBase::setSignedLong(const std::uint32_t index, const std::int32_t value)
{
    PUNTOEXE_FUNCTION_START(L"dataHandlerStringBase::setSignedLong");

	std::wostringstream convStream;
	convStream << value;
	setUnicodeString(index, convStream.str());

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Set data element as an unsigned long
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void dataHandlerStringBase::setUnsignedLong(const std::uint32_t index, const std::uint32_t value)
{
    PUNTOEXE_FUNCTION_START(L"dataHandlerStringBase::setUnsignedLong");

	std::wostringstream convStream;
	convStream << value;
	setUnicodeString(index, convStream.str());

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Set data element as a double
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void dataHandlerStringBase::setDouble(const std::uint32_t index, const double value)
{
    PUNTOEXE_FUNCTION_START(L"dataHandlerStringBase::setDouble");

	std::wostringstream convStream;
	convStream << std::fixed << value;
	setUnicodeString(index, convStream.str());

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Set data element as a string
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void dataHandlerStringBase::setString(const std::uint32_t index, const std::string& value)
{
    PUNTOEXE_FUNCTION_START(L"dataHandlerStringBase::setString");

	setUnicodeString(index, convertToUnicode(value));

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Set data element as an string
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void dataHandlerStringBase::setUnicodeString(const std::uint32_t index, const std::wstring& value)
{
    PUNTOEXE_FUNCTION_START(L"dataHandlerStringBase::setUnicodeString");

	if(index >= m_strings.size())
        {
            return;
        }
        std::uint32_t stringMaxSize(maxSize());

        if(stringMaxSize > 0 && value.size() > stringMaxSize)
        {
            m_strings[index] = value.substr(0, stringMaxSize);
            return;
        }
        m_strings[index] = value;

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Set the buffer's size (in data elements)
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void dataHandlerStringBase::setSize(const std::uint32_t elementsNumber)
{
    PUNTOEXE_FUNCTION_START(L"dataHandlerStringBase::setSize");

	if(getSeparator() == 0)
	{
		m_strings.resize(1, L"");
                return;
	}

	m_strings.resize(elementsNumber, L"");

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Get the size in strings
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::uint32_t dataHandlerStringBase::getSize() const
{
    PUNTOEXE_FUNCTION_START(L"dataHandlerStringBase::getSize");

	return (std::uint32_t)m_strings.size();

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Get the max size of a string
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::uint32_t dataHandlerStringBase::maxSize() const
{
	return 0;
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Get the separator
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
wchar_t dataHandlerStringBase::getSeparator() const
{
    return m_separator;
}


} // namespace handlers

} // namespace imebra

} // namespace puntoexe
