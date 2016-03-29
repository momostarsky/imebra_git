/*
$fileHeader$
*/

/*! \file dicomDictionary.cpp
    \brief Implementation of the class DicomDictionary class.

*/

#include "../include/imebra/dicomDictionary.h"
#include "../include/imebra/definitions.h"
#include "../include/imebra/tagId.h"
#include "../implementation/dicomDictImpl.h"
#include "../implementation/charsetConversionImpl.h"
#include <memory>

namespace imebra
{

std::wstring DicomDictionary::getUnicodeTagName(const TagId& id)
{
    return implementation::dicomDictionary::getDicomDictionary()->getTagName(id.getGroupId(), id.getTagId());
}

std::string DicomDictionary::getTagName(const TagId& id)
{
    std::wstring name = implementation::dicomDictionary::getDicomDictionary()->getTagName(id.getGroupId(), id.getTagId());
    implementation::charsetsList::tCharsetsList charsets;
    charsets.push_back("ISO 2022 IR 6");
    return implementation::dicomConversion::convertFromUnicode(name, &charsets);
}

tagVR_t DicomDictionary::getTagType(const TagId& id)
{
    return implementation::dicomDictionary::getDicomDictionary()->getTagType(id.getGroupId(), id.getTagId());
}


std::uint32_t DicomDictionary::getWordSize(tagVR_t dataType)
{
    return implementation::dicomDictionary::getDicomDictionary()->getWordSize(dataType);
}

std::uint32_t DicomDictionary::getMaxSize(tagVR_t dataType)
{
    return implementation::dicomDictionary::getDicomDictionary()->getMaxSize(dataType);
}

}

