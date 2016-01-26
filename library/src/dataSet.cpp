/*
$fileHeader$
*/

/*! \file dataSet_swig.cpp
    \brief Implementation of the class dataSet for SWIG.
*/

#include "../include/imebra/dataSet.h"
#include "../implementation/dataSetImpl.h"
#include "../implementation/dataHandlerNumericImpl.h"

namespace imebra
{

DataSet::DataSet(): m_pDataSet(std::make_shared<puntoexe::imebra::dataSet>())
{
}

DataSet::DataSet(const DataSet& right): m_pDataSet(right.m_pDataSet)
{
}

#ifndef SWIG
DataSet::DataSet(std::shared_ptr<puntoexe::imebra::dataSet> pDataSet): m_pDataSet(pDataSet)
{
    if(pDataSet == 0)
    {
        m_pDataSet = std::make_shared<puntoexe::imebra::dataSet>();
    }
}

#endif

DataSet& DataSet::operator=(const DataSet& right)
{
	m_pDataSet = right.m_pDataSet;
	return *this;
}

Image DataSet::getImage(std::uint32_t frameNumber)
{
    return Image(m_pDataSet->getImage((std::uint32_t)frameNumber));
}

Image DataSet::getImageApplyModalityTransform(std::uint32_t frameNumber)
{
    return Image(m_pDataSet->getModalityImage((std::uint32_t)frameNumber));
}

void DataSet::setImage(std::uint32_t frameNumber, Image image, const std::string& transferSyntax, imageQuality quality)
{
	m_pDataSet->setImage(frameNumber, image.m_pImage, transferSyntax, (puntoexe::imebra::codecs::codec::quality)quality);
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

int DataSet::getSignedLong(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber) const
{
    return m_pDataSet->getSignedLongThrow(groupId, order, tagId, bufferId, elementNumber);
}

void DataSet::setSignedLong(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber, int newValue, const std::string& defaultType)
{
    m_pDataSet->setSignedLong(groupId, order, tagId, bufferId, elementNumber, newValue, defaultType);
}

unsigned int DataSet::getUnsignedLong(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber) const
{
    return m_pDataSet->getUnsignedLongThrow(groupId, order, tagId, bufferId, elementNumber);
}

void DataSet::setUnsignedLong(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber, unsigned int newValue, const std::string& defaultType)
{
    m_pDataSet->setUnsignedLong(groupId, order, tagId, bufferId, elementNumber, newValue, defaultType);
}

double DataSet::getDouble(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber) const
{
    return m_pDataSet->getDoubleThrow(groupId, order, tagId, bufferId, elementNumber);
}

void DataSet::setDouble(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber, double newValue, const std::string& defaultType)
{
    m_pDataSet->setDouble(groupId, order, tagId, bufferId, elementNumber, newValue, defaultType);
}

std::wstring DataSet::getString(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber) const
{
    return m_pDataSet->getUnicodeStringThrow(groupId, order, tagId, bufferId, elementNumber);
}

void DataSet::setString(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber, const std::wstring& newString, const std::string& defaultType)
{
    m_pDataSet->setUnicodeString(groupId, order, tagId, bufferId, elementNumber, newString, defaultType);
}

void DataSet::setAge(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber, int age, imebra::ageUnit_t units, const std::string& defaultType)
{
    m_pDataSet->setAge(groupId, order, tagId, bufferId, elementNumber, age, units, defaultType);
}

int DataSet::getAge(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber, imebra::ageUnit_t* pUnits) const
{
    return m_pDataSet->getAgeThrow(groupId, order, tagId, bufferId, elementNumber, pUnits);
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

Date DataSet::getDate(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber) const
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



size_t DataSet::getRawData(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, char* buffer, size_t bufferSize) const
{
    std::shared_ptr<puntoexe::imebra::handlers::readingDataHandlerRaw> dataHandlerRaw = m_pDataSet->getReadingDataHandlerRawThrow(groupId, order, tagId, bufferId);
    if(dataHandlerRaw->getSize() > bufferSize)
    {
        return dataHandlerRaw->getSize();
    }
    dataHandlerRaw->copyTo((std::int8_t*)buffer, dataHandlerRaw->getSize());
    return dataHandlerRaw->getSize();
}

void DataSet::setRawData(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, char* buffer, size_t bufferSize, const std::string& defaultType)
{
    std::shared_ptr<puntoexe::imebra::handlers::writingDataHandlerRaw> dataHandlerRaw = m_pDataSet->getWritingDataHandlerRaw(groupId, order, tagId, bufferId, defaultType);
    dataHandlerRaw->copyFrom((std::int8_t*)buffer, bufferSize);
}


std::string DataSet::getDefaultDataType(std::uint16_t groupId, std::uint16_t tagId) const
{
    return m_pDataSet->getDefaultDataType(groupId, tagId);
}

std::string DataSet::getDataType(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId) const
{
    return m_pDataSet->getDataTypeThrow(groupId, order, tagId, 0);
}

}
