/*
$fileHeader$
*/

#include "../include/imebra/dataSet.h"
#include "../implementation/dataSetImpl.h"
#include "../implementation/dataHandlerNumericImpl.h"

namespace imebra
{

DataSet::DataSet(): m_pDataSet(std::make_shared<imebra::implementation::dataSet>())
{
}

DataSet::DataSet(const DataSet& right): m_pDataSet(right.m_pDataSet)
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

Image DataSet::getImage(size_t frameNumber)
{
    return Image(m_pDataSet->getImage((std::uint32_t)frameNumber));
}

Image DataSet::getImageApplyModalityTransform(size_t frameNumber)
{
    return Image(m_pDataSet->getModalityImage((std::uint32_t)frameNumber));
}

void DataSet::setImage(size_t frameNumber, Image image, const std::string& transferSyntax, imageQuality quality)
{
    m_pDataSet->setImage((std::uint32_t)frameNumber, image.m_pImage, transferSyntax, (imebra::implementation::codecs::codec::quality)quality);
}

DataSet DataSet::getSequenceItem(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t itemId)
{
    return DataSet(m_pDataSet->getSequenceItemThrow(groupId, order, tagId, itemId));
}

ReadingDataHandler DataSet::getReadingDataHandler(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId) const
{
    return ReadingDataHandler(m_pDataSet->getReadingDataHandlerThrow(groupId, order, tagId, bufferId));
}

WritingDataHandler DataSet::getWritingDataHandler(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, const std::string& defaultDataType)
{
    return WritingDataHandler(m_pDataSet->getWritingDataHandler(groupId, order, tagId, bufferId, defaultDataType));
}

bool DataSet::bufferExists(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId)
{
    return m_pDataSet->bufferExists(groupId, order, tagId, bufferId);
}

std::int32_t DataSet::getSignedLongThrow(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber) const
{
    return m_pDataSet->getSignedLongThrow(groupId, order, tagId, bufferId, elementNumber);
}

std::int32_t DataSet::getSignedLong(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber, std::int32_t defaultValue) const
{
    return m_pDataSet->getSignedLong(groupId, order, tagId, bufferId, elementNumber, defaultValue);
}

void DataSet::setSignedLong(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber, std::int32_t newValue, const std::string& defaultType)
{
    m_pDataSet->setSignedLong(groupId, order, tagId, bufferId, elementNumber, newValue, defaultType);
}

std::uint32_t DataSet::getUnsignedLongThrow(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber) const
{
    return m_pDataSet->getUnsignedLongThrow(groupId, order, tagId, bufferId, elementNumber);
}

std::uint32_t DataSet::getUnsignedLong(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber, std::uint32_t defaultValue) const
{
    return m_pDataSet->getUnsignedLong(groupId, order, tagId, bufferId, elementNumber, defaultValue);
}

void DataSet::setUnsignedLong(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber, std::uint32_t newValue, const std::string& defaultType)
{
    m_pDataSet->setUnsignedLong(groupId, order, tagId, bufferId, elementNumber, newValue, defaultType);
}

double DataSet::getDoubleThrow(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber) const
{
    return m_pDataSet->getDoubleThrow(groupId, order, tagId, bufferId, elementNumber);
}

double DataSet::getDouble(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber, double defaultValue) const
{
    return m_pDataSet->getDouble(groupId, order, tagId, bufferId, elementNumber, defaultValue);
}

void DataSet::setDouble(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber, double newValue, const std::string& defaultType)
{
    m_pDataSet->setDouble(groupId, order, tagId, bufferId, elementNumber, newValue, defaultType);
}

std::string DataSet::getStringThrow(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber) const
{
    return m_pDataSet->getStringThrow(groupId, order, tagId, bufferId, elementNumber);
}

std::string DataSet::getString(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber, const std::string& defaultValue) const
{
    return m_pDataSet->getString(groupId, order, tagId, bufferId, elementNumber, defaultValue);
}

std::wstring DataSet::getUnicodeStringThrow(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber) const
{
    return m_pDataSet->getUnicodeStringThrow(groupId, order, tagId, bufferId, elementNumber);
}

std::wstring DataSet::getUnicodeString(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber, const std::wstring& defaultValue) const
{
    return m_pDataSet->getUnicodeString(groupId, order, tagId, bufferId, elementNumber, defaultValue);
}

void DataSet::setString(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber, const std::string& newString, const std::string& defaultType)
{
    m_pDataSet->setString(groupId, order, tagId, bufferId, elementNumber, newString, defaultType);
}

void DataSet::setUnicodeString(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber, const std::wstring& newString, const std::string& defaultType)
{
    m_pDataSet->setUnicodeString(groupId, order, tagId, bufferId, elementNumber, newString, defaultType);
}

void DataSet::setAge(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber, const Age& age, const std::string& defaultType)
{
    m_pDataSet->setAge(groupId, order, tagId, bufferId, elementNumber, age.age, age.units, defaultType);
}

Age DataSet::getAgeThrow(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber) const
{
    imebra::ageUnit_t units;
    std::uint32_t age = m_pDataSet->getAgeThrow(groupId, order, tagId, bufferId, elementNumber, &units);
    return Age(age, units);
}

Age DataSet::getAge(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber, const Age& defaultValue) const
{
    imebra::ageUnit_t units;
    std::uint32_t age = m_pDataSet->getAge(groupId, order, tagId, bufferId, elementNumber, &units, defaultValue.age, defaultValue.units);
    return Age(age, units);
}

void DataSet::setDate(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber, const Date& date, const std::string& defaultType)
{
    m_pDataSet->setDate(groupId, order, tagId, bufferId, elementNumber,
                        (std::uint32_t) date.year,
                        (std::uint32_t) date.month,
                        (std::uint32_t) date.day,
                        (std::uint32_t) date.hour,
                        (std::uint32_t) date.minutes,
                        (std::uint32_t) date.seconds,
                        (std::uint32_t) date.nanoseconds,
                        (std::int32_t) date.offsetHours,
                        (std::int32_t) date.offsetMinutes, defaultType);
}

Date DataSet::getDateThrow(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber) const
{
    std::uint32_t year, month, day, hour, minutes, seconds, nanoseconds;
    std::int32_t offsetHours, offsetMinutes;
    m_pDataSet->getDateThrow(groupId, order, tagId, bufferId, elementNumber,
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

Date DataSet::getDate(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber, const Date& defaultValue) const
{
    std::uint32_t year, month, day, hour, minutes, seconds, nanoseconds;
    std::int32_t offsetHours, offsetMinutes;
    m_pDataSet->getDate(groupId, order, tagId, bufferId, elementNumber,
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


size_t DataSet::getRawDataThrow(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, char* buffer, size_t bufferSize) const
{
    std::shared_ptr<imebra::implementation::handlers::readingDataHandlerRaw> dataHandlerRaw = m_pDataSet->getReadingDataHandlerRawThrow(groupId, order, tagId, bufferId);
    if(dataHandlerRaw->getSize() > bufferSize)
    {
        return dataHandlerRaw->getSize();
    }
    dataHandlerRaw->copyTo((std::int8_t*)buffer, dataHandlerRaw->getSize());
    return dataHandlerRaw->getSize();
}

void DataSet::setRawData(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, char* buffer, size_t bufferSize, const std::string& defaultType)
{
    std::shared_ptr<imebra::implementation::handlers::writingDataHandlerRaw> dataHandlerRaw = m_pDataSet->getWritingDataHandlerRaw(groupId, order, tagId, bufferId, defaultType);
    dataHandlerRaw->copyFrom((std::int8_t*)buffer, bufferSize);
}


std::string DataSet::getDefaultDataType(std::uint16_t groupId, std::uint16_t tagId) const
{
    return m_pDataSet->getDefaultDataType(groupId, tagId);
}

std::string DataSet::getDataTypeThrow(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId) const
{
    return m_pDataSet->getDataTypeThrow(groupId, order, tagId, 0);
}

}
