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

DataSet::DataSet(): m_pDataSet(new puntoexe::imebra::dataSet)
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

Image DataSet::getImage(int frameNumber)
{
    return Image(m_pDataSet->getImage((imbxUint32)frameNumber));
}

void DataSet::setImage(int frameNumber, Image image, const std::wstring& transferSyntax, imageQuality quality)
{
	m_pDataSet->setImage(frameNumber, image.m_pImage, transferSyntax, (puntoexe::imebra::codecs::codec::quality)quality);
}

DataSet DataSet::getSequenceItem(int groupId, int order, int tagId, int itemId)
{
	return DataSet(m_pDataSet->getSequenceItem(groupId, order, tagId, itemId));
}

int DataSet::getSignedLong(int groupId, int order, int tagId, int elementNumber) const
{
	return m_pDataSet->getSignedLong(groupId, order, tagId, elementNumber);
}

void DataSet::setSignedLong(int groupId, int order, int tagId, int elementNumber, int newValue, const std::string& defaultType)
{
	m_pDataSet->setSignedLong(groupId, order, tagId, elementNumber, newValue, defaultType);
}

int DataSet::getUnsignedLong(int groupId, int order, int tagId, int elementNumber) const
{
	return m_pDataSet->getUnsignedLong(groupId, order, tagId, elementNumber);
}

void DataSet::setUnsignedLong(int groupId, int order, int tagId, int elementNumber, int newValue, const std::string& defaultType)
{
	m_pDataSet->setUnsignedLong(groupId, order, tagId, elementNumber, newValue, defaultType);
}

double DataSet::getDouble(int groupId, int order, int tagId, int elementNumber) const
{
	return m_pDataSet->getDouble(groupId, order, tagId, elementNumber);
}

void DataSet::setDouble(int groupId, int order, int tagId, int elementNumber, double newValue, const std::string& defaultType)
{
	m_pDataSet->setDouble(groupId, order, tagId, elementNumber, newValue, defaultType);
}

std::wstring DataSet::getString(int groupId, int order, int tagId, int elementNumber) const
{
	return m_pDataSet->getUnicodeString(groupId, order, tagId, elementNumber);
}

void DataSet::setString(int groupId, int order, int tagId, int elementNumber, const std::wstring& newString, const std::string& defaultType)
{
	m_pDataSet->setUnicodeString(groupId, order, tagId, elementNumber, newString, defaultType);
}

size_t DataSet::getRawData(int groupId, int order, int tagId, int bufferId, char* buffer, size_t bufferSize) const
{
    std::shared_ptr<puntoexe::imebra::handlers::dataHandlerRaw> dataHandlerRaw = m_pDataSet->getDataHandlerRaw(groupId, order, tagId, bufferId, false);
    if(dataHandlerRaw->getSize() > bufferSize)
    {
        return dataHandlerRaw->getSize();
    }
    dataHandlerRaw->copyTo((std::int8_t*)buffer, dataHandlerRaw->getSize());
    return dataHandlerRaw->getSize();
}

void DataSet::setRawData(int groupId, int order, int tagId, int bufferId, char* buffer, size_t bufferSize, const std::string& defaultType)
{
    std::shared_ptr<puntoexe::imebra::handlers::dataHandlerRaw> dataHandlerRaw = m_pDataSet->getDataHandlerRaw(groupId, order, tagId, bufferId, true);
    dataHandlerRaw->copyFrom((std::int8_t*)buffer, bufferSize);
}


std::string DataSet::getDefaultDataType(int groupId, int order, int tagId) const
{
	return m_pDataSet->getDataType(groupId, order, tagId);
}

std::string DataSet::getDataType(int groupId, int order, int tagId) const
{
	return m_pDataSet->getDataType(groupId, order, tagId);
}

}
