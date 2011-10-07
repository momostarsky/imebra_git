#include "../include/dataSet.h"

dataSet::dataSet(): m_pDataSet(new puntoexe::imebra::dataSet)
{
}

dataSet::imebraDataSet(const dataSet& right): m_pDataSet(right.m_pDataSet)
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

std::wstring dataSet::getUnicodeString(unsigned int groupId, unsigned int order, unsigned int tagId, unsigned long elementNumber)
{
	return m_pDataSet->getUnicodeString(groupId, order, tagId, elementNumber);
}

