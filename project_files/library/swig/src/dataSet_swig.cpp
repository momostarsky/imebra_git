/*
$fileHeader$
*/

/*! \file dataSet_swig.cpp
    \brief Implementation of the class dataSet for SWIG.
*/

#include "../include/dataSet_swig.h"
#include "../include/exceptions_swig.h"

dataSet::dataSet(): m_pDataSet(new puntoexe::imebra::dataSet)
{
}

dataSet::dataSet(const dataSet& right): m_pDataSet(right.m_pDataSet)
{
}

#ifndef SWIG
dataSet::dataSet(puntoexe::ptr<puntoexe::imebra::dataSet> pDataSet): m_pDataSet(pDataSet)
{
}

#endif

dataSet& dataSet::operator=(const dataSet& right)
{
	m_pDataSet = right.m_pDataSet;
	return *this;
}


dataSet dataSet::getSequenceItem(unsigned int groupId, unsigned int order, unsigned int tagId, unsigned long itemId)
{
	try
	{
		return dataSet(m_pDataSet->getSequenceItem(groupId, order, tagId, itemId));
	}
	CATCH_IMEBRA_EXCEPTIONS;
}

long dataSet::getSignedLong(unsigned int groupId, unsigned int order, unsigned int tagId, unsigned long elementNumber)
{
	try
	{
		return m_pDataSet->getSignedLong(groupId, order, tagId, elementNumber);
	}
	CATCH_IMEBRA_EXCEPTIONS;
}

void dataSet::setSignedLong(unsigned int groupId, unsigned int order, unsigned int tagId, unsigned long elementNumber, long newValue, std::string defaultType)
{
	try
	{
		m_pDataSet->setSignedLong(groupId, order, tagId, elementNumber, newValue, defaultType);
	}
	CATCH_IMEBRA_EXCEPTIONS;
}

unsigned long dataSet::getUnsignedLong(unsigned int groupId, unsigned int order, unsigned int tagId, unsigned long elementNumber)
{
	try
	{
		return m_pDataSet->getUnsignedLong(groupId, order, tagId, elementNumber);
	}
	CATCH_IMEBRA_EXCEPTIONS;
}

void dataSet::setUnsignedLong(unsigned int groupId, unsigned int order, unsigned int tagId, unsigned long elementNumber, unsigned long newValue, std::string defaultType)
{
	try
	{
		m_pDataSet->setUnsignedLong(groupId, order, tagId, elementNumber, newValue, defaultType);
	}
	CATCH_IMEBRA_EXCEPTIONS;
}

double dataSet::getDouble(unsigned int groupId, unsigned int order, unsigned int tagId, unsigned long elementNumber)
{
	try
	{
		return m_pDataSet->getDouble(groupId, order, tagId, elementNumber);
	}
	CATCH_IMEBRA_EXCEPTIONS;
}

void dataSet::setDouble(unsigned int groupId, unsigned int order, unsigned int tagId, unsigned long elementNumber, double newValue, std::string defaultType)
{
	try
	{
		m_pDataSet->setDouble(groupId, order, tagId, elementNumber, newValue, defaultType);
	}
	CATCH_IMEBRA_EXCEPTIONS;
}

std::wstring dataSet::getString(unsigned int groupId, unsigned int order, unsigned int tagId, unsigned long elementNumber)
{
	try
	{
		return m_pDataSet->getUnicodeString(groupId, order, tagId, elementNumber);
	}
	CATCH_IMEBRA_EXCEPTIONS;
}

void dataSet::setString(unsigned int groupId, unsigned int order, unsigned int tagId, unsigned long elementNumber, std::wstring newString, std::string defaultType)
{
	try
	{
		m_pDataSet->setUnicodeString(groupId, order, tagId, elementNumber, newString, defaultType);
	}
	CATCH_IMEBRA_EXCEPTIONS;
}

std::string dataSet::getDefaultDataType(unsigned int groupId, unsigned int order, unsigned int tagId)
{
	try
	{
		return m_pDataSet->getDataType(groupId, order, tagId);
	}
	CATCH_IMEBRA_EXCEPTIONS;
}

std::string dataSet::getDataType(unsigned int groupId, unsigned int order, unsigned int tagId)
{
	try
	{
		return m_pDataSet->getDataType(groupId, order, tagId);
	}
	CATCH_IMEBRA_EXCEPTIONS;
}




