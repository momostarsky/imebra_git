/*
$fileHeader$
*/

#include "../include/imebra/dataSet.h"
#include "../implementation/dataSetImpl.h"
#include "../implementation/dataHandlerNumericImpl.h"
#include "../implementation/charsetConversionBaseImpl.h"
#include <typeinfo>
#include <memory>

namespace imebra
{

DataSet::DataSet(): m_pDataSet(std::make_shared<imebra::implementation::dataSet>())
{
    implementation::charsetsList::tCharsetsList list;
    list.push_back("ISO 2022 IR 6");
    m_pDataSet->setCharsetsList(list);
}

DataSet::DataSet(const DataSet& right): m_pDataSet(right.m_pDataSet)
{
}

DataSet::~DataSet()
{
}

#ifndef SWIG
DataSet::DataSet(std::shared_ptr<imebra::implementation::dataSet> pDataSet): m_pDataSet(pDataSet)
{
    if(pDataSet == 0)
    {
        m_pDataSet = std::make_shared<imebra::implementation::dataSet>();
    }
}

#endif

DataSet& DataSet::operator=(const DataSet& right)
{
	m_pDataSet = right.m_pDataSet;
	return *this;
}

tagsIds_t DataSet::getTags() const
{
    tagsIds_t returnTags;

    implementation::dataSet::tGroupsIds groups = m_pDataSet->getGroups();
    for(implementation::dataSet::tGroupsIds::const_iterator scanGroups(groups.begin()), endGroups(groups.end());
        scanGroups != endGroups;
        ++scanGroups)
    {
        std::uint32_t orders = m_pDataSet->getGroupsNumber(*scanGroups);
        for(std::uint32_t scanOrders(0); scanOrders != orders; ++scanOrders)
        {
            const implementation::dataSet::tTags tags = m_pDataSet->getGroupTags(*scanGroups, scanOrders);
            for(implementation::dataSet::tTags::const_iterator scanTags(tags.begin()), endTags(tags.end());
                scanTags != endTags;
                ++scanTags)
            {
                returnTags.push_back(TagId(*scanGroups, orders, scanTags->first));
            }
        }
    }

    return returnTags;
}

Tag DataSet::getTagContent(const TagId& tagId) const
{
    return Tag(m_pDataSet->getTag(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId()));
}

Image DataSet::getImage(size_t frameNumber)
{
    return Image(m_pDataSet->getImage((std::uint32_t)frameNumber));
}

Image DataSet::getImageApplyModalityTransform(size_t frameNumber)
{
    return Image(m_pDataSet->getModalityImage((std::uint32_t)frameNumber));
}

void DataSet::setImage(size_t frameNumber, Image image, const std::string& transferSyntax, imageQuality_t quality)
{
    m_pDataSet->setImage((std::uint32_t)frameNumber, image.m_pImage, transferSyntax, quality);
}

DataSet DataSet::getSequenceItem(const TagId& tagId, size_t itemId)
{
    return DataSet(m_pDataSet->getSequenceItem(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), itemId));
}

ReadingDataHandler DataSet::getReadingDataHandler(const TagId& tagId, size_t bufferId) const
{
    return ReadingDataHandler(m_pDataSet->getReadingDataHandler(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), bufferId));
}

WritingDataHandler DataSet::getWritingDataHandler(const TagId& tagId, size_t bufferId, const std::string& defaultDataType)
{
    return WritingDataHandler(m_pDataSet->getWritingDataHandler(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), bufferId, defaultDataType));
}

ReadingDataHandlerNumeric DataSet::getReadingDataHandlerNumeric(const TagId& tagId, size_t bufferId) const
{
    std::shared_ptr<implementation::handlers::readingDataHandlerNumericBase> numericHandler =
            std::dynamic_pointer_cast<implementation::handlers::readingDataHandlerNumericBase>(m_pDataSet->getReadingDataHandler(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), bufferId));
    if(numericHandler.get() == 0)
    {
        throw std::bad_cast();
    }
    return ReadingDataHandlerNumeric(numericHandler);
}

ReadingDataHandlerNumeric DataSet::getReadingDataHandlerRaw(const TagId& tagId, size_t bufferId) const
{
    std::shared_ptr<implementation::handlers::readingDataHandlerNumericBase> numericHandler = m_pDataSet->getReadingDataHandlerRaw(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), bufferId);
    return ReadingDataHandlerNumeric(numericHandler);
}

WritingDataHandlerNumeric DataSet::getWritingDataHandlerNumeric(const TagId& tagId, size_t bufferId, const std::string& defaultDataType)
{
    std::shared_ptr<implementation::handlers::writingDataHandlerNumericBase> numericHandler =
            std::dynamic_pointer_cast<implementation::handlers::writingDataHandlerNumericBase>(m_pDataSet->getWritingDataHandler(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), bufferId, defaultDataType));
    if(numericHandler.get() == 0)
    {
        throw std::bad_cast();
    }
    return WritingDataHandlerNumeric(numericHandler);
}

WritingDataHandlerNumeric DataSet::getWritingDataHandlerRaw(const TagId& tagId, size_t bufferId, const std::string& defaultDataType)
{
    std::shared_ptr<implementation::handlers::writingDataHandlerNumericBase> numericHandler = m_pDataSet->getWritingDataHandlerRaw(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), bufferId, defaultDataType);
    return WritingDataHandlerNumeric(numericHandler);
}

bool DataSet::bufferExists(const TagId& tagId, size_t bufferId)
{
    return m_pDataSet->bufferExists(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), bufferId);
}

std::int32_t DataSet::getSignedLong(const TagId& tagId, size_t bufferId, size_t elementNumber) const
{
    return m_pDataSet->getSignedLong(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), bufferId, elementNumber);
}

std::int32_t DataSet::getSignedLong(const TagId& tagId, size_t bufferId, size_t elementNumber, std::int32_t defaultValue) const
{
    return m_pDataSet->getSignedLong(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), bufferId, elementNumber, defaultValue);
}

void DataSet::setSignedLong(const TagId& tagId, size_t bufferId, std::int32_t newValue, const std::string& tagVR)
{
    m_pDataSet->setSignedLong(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), bufferId, newValue, tagVR);
}

std::uint32_t DataSet::getUnsignedLong(const TagId& tagId, size_t bufferId, size_t elementNumber) const
{
    return m_pDataSet->getUnsignedLong(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), bufferId, elementNumber);
}

std::uint32_t DataSet::getUnsignedLong(const TagId& tagId, size_t bufferId, size_t elementNumber, std::uint32_t defaultValue) const
{
    return m_pDataSet->getUnsignedLong(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), bufferId, elementNumber, defaultValue);
}

void DataSet::setUnsignedLong(const TagId& tagId, size_t bufferId, std::uint32_t newValue, const std::string& tagVR)
{
    m_pDataSet->setUnsignedLong(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), bufferId, newValue, tagVR);
}

double DataSet::getDouble(const TagId& tagId, size_t bufferId, size_t elementNumber) const
{
    return m_pDataSet->getDouble(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), bufferId, elementNumber);
}

double DataSet::getDouble(const TagId& tagId, size_t bufferId, size_t elementNumber, double defaultValue) const
{
    return m_pDataSet->getDouble(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), bufferId, elementNumber, defaultValue);
}

void DataSet::setDouble(const TagId& tagId, size_t bufferId, double newValue, const std::string& tagVR)
{
    m_pDataSet->setDouble(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), bufferId, newValue, tagVR);
}

std::string DataSet::getString(const TagId& tagId, size_t bufferId, size_t elementNumber) const
{
    return m_pDataSet->getString(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), bufferId, elementNumber);
}

std::string DataSet::getString(const TagId& tagId, size_t bufferId, size_t elementNumber, const std::string& defaultValue) const
{
    return m_pDataSet->getString(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), bufferId, elementNumber, defaultValue);
}

std::wstring DataSet::getUnicodeString(const TagId& tagId, size_t bufferId, size_t elementNumber) const
{
    return m_pDataSet->getUnicodeString(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), bufferId, elementNumber);
}

std::wstring DataSet::getUnicodeString(const TagId& tagId, size_t bufferId, size_t elementNumber, const std::wstring& defaultValue) const
{
    return m_pDataSet->getUnicodeString(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), bufferId, elementNumber, defaultValue);
}

void DataSet::setString(const TagId& tagId, size_t bufferId, const std::string& newString, const std::string& tagVR)
{
    m_pDataSet->setString(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), bufferId, newString, tagVR);
}

void DataSet::setUnicodeString(const TagId& tagId, size_t bufferId, const std::wstring& newString, const std::string& tagVR)
{
    m_pDataSet->setUnicodeString(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), bufferId, newString, tagVR);
}

void DataSet::setAge(const TagId& tagId, size_t bufferId, const Age& age, const std::string& tagVR)
{
    m_pDataSet->setAge(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), bufferId, age.age, age.units, tagVR);
}

Age DataSet::getAge(const TagId& tagId, size_t bufferId, size_t elementNumber) const
{
    imebra::ageUnit_t units;
    std::uint32_t age = m_pDataSet->getAge(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), bufferId, elementNumber, &units);
    return Age(age, units);
}

Age DataSet::getAge(const TagId& tagId, size_t bufferId, size_t elementNumber, const Age& defaultValue) const
{
    imebra::ageUnit_t units;
    std::uint32_t age = m_pDataSet->getAge(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), bufferId, elementNumber, &units, defaultValue.age, defaultValue.units);
    return Age(age, units);
}

void DataSet::setDate(const TagId& tagId, size_t bufferId, const Date& date, const std::string& tagVR)
{
    m_pDataSet->setDate(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), bufferId,
                        (std::uint32_t) date.year,
                        (std::uint32_t) date.month,
                        (std::uint32_t) date.day,
                        (std::uint32_t) date.hour,
                        (std::uint32_t) date.minutes,
                        (std::uint32_t) date.seconds,
                        (std::uint32_t) date.nanoseconds,
                        (std::int32_t) date.offsetHours,
                        (std::int32_t) date.offsetMinutes, tagVR);
}

Date DataSet::getDate(const TagId& tagId, size_t bufferId, size_t elementNumber) const
{
    std::uint32_t year, month, day, hour, minutes, seconds, nanoseconds;
    std::int32_t offsetHours, offsetMinutes;
    m_pDataSet->getDate(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), bufferId, elementNumber,
                        &year, &month, &day, &hour, &minutes, &seconds, &nanoseconds, &offsetHours, &offsetMinutes);

    return Date(
                (unsigned int)year,
                (unsigned int)month,
                (unsigned int)day,
                (unsigned int)hour,
                (unsigned int)minutes,
                (unsigned int)seconds,
                (unsigned int)nanoseconds,
                (int)offsetHours,
                (int)offsetMinutes);
}

Date DataSet::getDate(const TagId& tagId, size_t bufferId, size_t elementNumber, const Date& defaultValue) const
{
    std::uint32_t year, month, day, hour, minutes, seconds, nanoseconds;
    std::int32_t offsetHours, offsetMinutes;
    m_pDataSet->getDate(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), bufferId, elementNumber,
                        &year, &month, &day, &hour, &minutes, &seconds, &nanoseconds, &offsetHours, &offsetMinutes,
                        defaultValue.year, defaultValue.month, defaultValue.day,
                        defaultValue.hour, defaultValue.minutes, defaultValue.seconds, defaultValue.nanoseconds,
                        defaultValue.offsetHours, defaultValue.offsetMinutes);

    return Date(
                (unsigned int)year,
                (unsigned int)month,
                (unsigned int)day,
                (unsigned int)hour,
                (unsigned int)minutes,
                (unsigned int)seconds,
                (unsigned int)nanoseconds,
                (int)offsetHours,
                (int)offsetMinutes);
}


std::string DataSet::getDataType(const TagId& tagId) const
{
    return m_pDataSet->getDataType(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0);
}

}
