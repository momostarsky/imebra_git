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
dataHandlerString::dataHandlerString(const wchar_t separator, const std::uint8_t paddingByte): dataHandlerStringBase(separator, paddingByte)
{
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Rebuild the buffer
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
dataHandlerString::~dataHandlerString()
{
    if(m_buffer != 0)
    {
        std::wstring completeString;
        for(size_t stringsIterator = 0; stringsIterator < m_strings.size(); ++stringsIterator)
        {
            if(stringsIterator)
            {
                completeString += m_separator;
            }
            completeString += m_strings[stringsIterator];
        }

        std::string asciiString = convertFromUnicode(completeString, &m_charsetsList);

        m_commitMemory = std::make_shared<memory>((std::uint32_t)asciiString.size());
        m_commitMemory->assign((std::uint8_t*)asciiString.data(), (std::uint32_t)asciiString.size());
    }
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Convert a string to unicode, without using the dicom
//  charsets
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::wstring dataHandlerString::convertToUnicode(const std::string& value) const
{
	size_t stringLength = value.size();
	std::wstring returnString;
	returnString.resize(stringLength, 0);
	for(size_t copyString = 0; copyString < stringLength; ++copyString)
	{
		returnString[copyString]=(wchar_t)value[copyString];
	}
	return returnString;
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Convert a string from unicode, without using the dicom 
//  charsets
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::string dataHandlerString::convertFromUnicode(const std::wstring& value, charsetsList::tCharsetsList* /* pCharsetsList */) const
{
	size_t stringLength = value.size();
	std::string returnString;
	returnString.resize(stringLength);
	for(size_t copyString = 0; copyString < stringLength; ++copyString)
	{
		returnString[copyString]=(char)value[copyString];
	}
	return returnString;
}


} // namespace handlers

} // namespace imebra

} // namespace puntoexe
