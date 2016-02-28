/*
$fileHeader$
*/

/*! \file dicomDict.cpp
    \brief Implementation of the class dicomDict.

*/


#include "exceptionImpl.h"
#include "dicomDictImpl.h"
#include "tagsDescription.h"
#include "../include/imebra/exceptions.h"

namespace imebra
{

namespace implementation
{

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
//
// dicomDictionary
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
// Constructor. Register all the known tags and VRs
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
dicomDictionary::dicomDictionary()
{
    IMEBRA_FUNCTION_START();

	registerVR("AE", false, 0, 16);
	registerVR("AS", false, 0, 0);
	registerVR("AT", false, 2, 0);
	registerVR("CS", false, 0, 16);
	registerVR("DA", false, 0, 0);
	registerVR("DS", false, 0, 16);
	registerVR("DT", false, 0, 26);
    registerVR("FL", false, 4, 0);
    registerVR("FD", false, 8, 0);
    registerVR("IS", false, 0, 12);
	registerVR("LO", false, 0, 64);
	registerVR("LT", false, 0, 10240);
	registerVR("OB", true,  0, 0);
    registerVR("SB", true,  0, 0); // Non standard. Used internally for signed bytes
    registerVR("OF", true,  4, 0);
    registerVR("OD", true,  8, 0);
	registerVR("OW", true,  2, 0);
	registerVR("PN", false, 0, 64);
	registerVR("SH", false, 0, 16);
	registerVR("SL", false, 4, 0);
	registerVR("SQ", true,  0, 0);
	registerVR("SS", false, 2, 0);
	registerVR("ST", false, 0, 1024);
	registerVR("TM", false, 0, 16);
	registerVR("UI", false, 0, 64);
	registerVR("UL", false, 4, 0);
	registerVR("UN", true,  0, 0);
	registerVR("US", false, 2, 0);
	registerVR("UT", true, 0, 0);
	registerVR("IS", false, 0, 0);
	
    for(size_t scanDescriptions(0); m_tagsDescription[scanDescriptions].m_tagId != 0; ++scanDescriptions)
    {
        registerTag(m_tagsDescription[scanDescriptions].m_tagId,
                    m_tagsDescription[scanDescriptions].m_tagDescription,
                    m_tagsDescription[scanDescriptions].m_vr);

    }

	IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Register a tag
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void dicomDictionary::registerTag(std::uint32_t tagId, const wchar_t* tagName, const char* tagType)
{
    IMEBRA_FUNCTION_START();

	if(m_dicomDict.find(tagId) != m_dicomDict.end())
	{
		return;
	}
	imageDataDictionaryElement newElement;

	newElement.m_tagName = tagName;
    newElement.m_tagType = tagType;

	m_dicomDict[tagId] = newElement;

	IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Register a VR
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void dicomDictionary::registerVR(const std::string& vr, bool bLongLength, std::uint32_t wordSize, std::uint32_t maxLength)
{
    IMEBRA_FUNCTION_START();

	if(m_vrDict.find(vr) != m_vrDict.end())
	{
		return;
	}
	validDataTypesStruct newElement;
	newElement.m_longLength = bLongLength;
	newElement.m_wordLength = wordSize;
	newElement.m_maxLength = maxLength;

	m_vrDict[vr] = newElement;

	IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Return an human readable name for the tag
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::wstring dicomDictionary::getTagName(std::uint16_t groupId, std::uint16_t tagId) const
{
    IMEBRA_FUNCTION_START();

	std::uint32_t tagDWordId=(((std::uint32_t)groupId)<<16) | (std::uint32_t)tagId;

	tDicomDictionary::const_iterator findIterator = m_dicomDict.find(tagDWordId);
	if(findIterator == m_dicomDict.end())
	{
        IMEBRA_THROW(DictionaryUnknownTagError, "Unknown tag " << std::hex << groupId << ", " << std::hex << tagId);
	}
	
	return findIterator->second.m_tagName;

	IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Return the default type for the specified tag
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::string dicomDictionary::getTagType(std::uint16_t groupId, std::uint16_t tagId) const
{
    IMEBRA_FUNCTION_START();

	std::uint32_t tagDWordId=(((std::uint32_t)groupId)<<16) | (std::uint32_t)tagId;

	tDicomDictionary::const_iterator findIterator = m_dicomDict.find(tagDWordId);
    if(findIterator == m_dicomDict.end())
	{
        IMEBRA_THROW(DictionaryUnknownTagError, "Unknown tag " << std::hex << groupId << ", " << std::hex << tagId);
    }

    if(findIterator->second.m_tagType.empty())
    {
        IMEBRA_THROW(DictionaryUnknownDefaultTypeError, "Unknown default data type for " << std::hex << groupId << ", " << std::hex << tagId);
    }

	return findIterator->second.m_tagType;

	IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Return true if the specified data type is valid
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
bool dicomDictionary::isDataTypeValid(const std::string& dataType) const
{
	tVRDictionary::const_iterator findIterator = m_vrDict.find(dataType);

	return (findIterator != m_vrDict.end());
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Return true if the specified data type must use a 
//  long length descriptor
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
bool dicomDictionary::getLongLength(const std::string& dataType) const
{
    IMEBRA_FUNCTION_START();

	tVRDictionary::const_iterator findIterator = m_vrDict.find(dataType);

	if(findIterator == m_vrDict.end())
	{
		return false;
	}

	return findIterator->second.m_longLength;

	IMEBRA_FUNCTION_END();
	
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Return the word size for the specified data type
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::uint32_t dicomDictionary::getWordSize(const std::string& dataType) const
{
    IMEBRA_FUNCTION_START();

	tVRDictionary::const_iterator findIterator = m_vrDict.find(dataType);

	if(findIterator == m_vrDict.end())
	{
        IMEBRA_THROW(DictionaryUnknownDataTypeError, "Unknown data type " << dataType);
    }

	return findIterator->second.m_wordLength;

	IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Return the max size in bytes for the specified data
//  type
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::uint32_t dicomDictionary::getMaxSize(const std::string& dataType) const
{
    IMEBRA_FUNCTION_START();

	tVRDictionary::const_iterator findIterator = m_vrDict.find(dataType);

	if(findIterator == m_vrDict.end())
	{
        IMEBRA_THROW(DictionaryUnknownDataTypeError, "Unknown data type " << dataType);
    }

	return findIterator->second.m_maxLength;

	IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Return a pointer to the unique instance of
//  dicomDictionary
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
dicomDictionary* dicomDictionary::getDicomDictionary()
{
    IMEBRA_FUNCTION_START();

    static dicomDictionary m_imbxDicomDictionary;
	return &m_imbxDicomDictionary;

    IMEBRA_FUNCTION_END();
}


} // namespace implementation

} // namespace imebra
