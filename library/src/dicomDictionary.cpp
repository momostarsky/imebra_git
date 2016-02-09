/*
$fileHeader$
*/

/*! \file dicomDictionary.cpp
    \brief Implementation of the class DicomDictionary class.

*/

#include "../include/imebra/dicomDictionary.h"
#include "../include/imebra/definitions.h"
#include "../implementation/dicomDictImpl.h"
#include "../implementation/charsetConversionImpl.h"
#include <memory>

namespace imebra
{

std::wstring DicomDictionary::getUnicodeTagName(std::uint16_t groupId, std::uint16_t tagId)
{
    return implementation::dicomDictionary::getDicomDictionary()->getTagName(groupId, tagId);
}

std::string DicomDictionary::getTagName(std::uint16_t groupId, std::uint16_t tagId)
{
    std::wstring name = implementation::dicomDictionary::getDicomDictionary()->getTagName(groupId, tagId);
    implementation::charsetsList::tCharsetsList charsets;
    charsets.push_back("ISO 2022 IR 6");
    return implementation::dicomConversion::convertFromUnicode(name, &charsets);
}

std::string DicomDictionary::getTagType(std::uint16_t groupId, std::uint16_t tagId)
{
    return implementation::dicomDictionary::getDicomDictionary()->getTagType(groupId, tagId);
}


std::uint32_t DicomDictionary::getWordSize(const std::string& dataType)
{
    return implementation::dicomDictionary::getDicomDictionary()->getWordSize(dataType);
}

std::uint32_t DicomDictionary::getMaxSize(const std::string& dataType)
{
    return implementation::dicomDictionary::getDicomDictionary()->getMaxSize(dataType);
}

}

