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
dataHandlerString::dataHandlerString(const std::string& dataType, const wchar_t separator, const std::uint8_t paddingByte):
    dataHandlerStringBase(dataType, separator, paddingByte)
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

        charsetsList::tCharsetsList localCharsetsList;
        localCharsetsList.push_back("ISO_IR 6");
        std::string asciiString = convertFromUnicode(completeString, &localCharsetsList);

        std::shared_ptr<memory> commitMemory = std::make_shared<memory>((std::uint32_t)asciiString.size());
        commitMemory->assign((std::uint8_t*)asciiString.data(), (std::uint32_t)asciiString.size());

        // The buffer's size must be an even number
        ///////////////////////////////////////////////////////////
        std::uint32_t memorySize = commitMemory->size();
        if((memorySize & 0x1) != 0)
        {
            commitMemory->resize(++memorySize);
            *(commitMemory->data() + (memorySize - 1)) = m_paddingByte;
        }

        m_buffer->commit(commitMemory, m_bufferType);
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
