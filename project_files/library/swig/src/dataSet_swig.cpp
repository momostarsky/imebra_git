#include "../include/dataSet_swig.h"

imebraDataSet::imebraDataSet(): m_pDataSet(new puntoexe::imebra::dataSet)
{
}

imebraDataSet::imebraDataSet(const imebraDataSet& right): m_pDataSet(right.m_pDataSet)
{
}

#ifndef SWIG
imebraDataSet::imebraDataSet(puntoexe::ptr<puntoexe::imebra::dataSet> pDataSet): m_pDataSet(pDataSet)
{
}

#endif

imebraDataSet& imebraDataSet::operator=(const imebraDataSet& right)
{
	m_pDataSet = right.m_pDataSet;
	return *this;
}

std::wstring imebraDataSet::getUnicodeString(unsigned int groupId, unsigned int order, unsigned int tagId, unsigned long elementNumber)
{
	return m_pDataSet->getUnicodeString(groupId, order, tagId, elementNumber);
}

