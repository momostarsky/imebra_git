/*
$fileHeader$
*/

/*! \file dicomDir_swig.cpp
    \brief Implementation of the classes that parse/create a DICOMDIR
		structure (dicomDir and directoryRecord) for SWIG.

*/

#include "../include/dicomDir_swig.h"
#include "../include/dataSet_swig.h"
#include "../include/exceptions_swig.h"

directoryRecord::directoryRecord(){}

directoryRecord::directoryRecord(const directoryRecord& right): m_pDirectoryRecord(right.m_pDirectoryRecord)
{
}

directoryRecord::directoryRecord(puntoexe::ptr<puntoexe::imebra::directoryRecord> pDirectoryRecord): m_pDirectoryRecord(pDirectoryRecord)
{
}

directoryRecord& directoryRecord::operator=(const directoryRecord& right)
{
	m_pDirectoryRecord = right.m_pDirectoryRecord;
	return *this;
}

dataSet directoryRecord::getRecordDataSet()
{
	if(m_pDirectoryRecord == 0) throw dicomDirNullRecord("Null directoryRecord");
	try
	{
		return dataSet(m_pDirectoryRecord->getRecordDataSet());
	}
	CATCH_IMEBRA_EXCEPTIONS;
}

directoryRecord directoryRecord::getNextRecord()
{
	if(m_pDirectoryRecord == 0) throw dicomDirNullRecord("Null directoryRecord");
	try
	{
		return directoryRecord(m_pDirectoryRecord->getNextRecord());
	}
	CATCH_IMEBRA_EXCEPTIONS;
}

directoryRecord directoryRecord::getFirstChildRecord()
{
	if(m_pDirectoryRecord == 0) throw dicomDirNullRecord("Null directoryRecord");
	try
	{
		return directoryRecord(m_pDirectoryRecord->getFirstChildRecord());
	}
	CATCH_IMEBRA_EXCEPTIONS;
}
	
directoryRecord directoryRecord::getReferencedRecord()
{
	if(m_pDirectoryRecord == 0) throw dicomDirNullRecord("Null directoryRecord");
	try
	{
		return directoryRecord(m_pDirectoryRecord->getReferencedRecord());
	}
	CATCH_IMEBRA_EXCEPTIONS;
}

void directoryRecord::setNextRecord(const directoryRecord& nextRecord)
{
	if(m_pDirectoryRecord == 0) throw dicomDirNullRecord("Null directoryRecord");
	try
	{
		m_pDirectoryRecord->setNextRecord(nextRecord.m_pDirectoryRecord);
	}
	CATCH_IMEBRA_EXCEPTIONS;
}

void directoryRecord::setFirstChildRecord(const directoryRecord& firstChildRecord)
{
	if(m_pDirectoryRecord == 0) throw dicomDirNullRecord("Null directoryRecord");
	try
	{
		m_pDirectoryRecord->setFirstChildRecord(firstChildRecord.m_pDirectoryRecord);
	}
	CATCH_IMEBRA_EXCEPTIONS;
}

void directoryRecord::setReferencedRecord(const directoryRecord& referencedRecord)
{
	if(m_pDirectoryRecord == 0) throw dicomDirNullRecord("Null directoryRecord");
	try
	{
		m_pDirectoryRecord->setReferencedRecord(referencedRecord.m_pDirectoryRecord);
	}
	CATCH_IMEBRA_EXCEPTIONS;
}
	
std::wstring directoryRecord::getFilePart(unsigned int part)
{
	if(m_pDirectoryRecord == 0) throw dicomDirNullRecord("Null directoryRecord");
	try
	{
		return m_pDirectoryRecord->getFilePart(part);
	}
	CATCH_IMEBRA_EXCEPTIONS;
}

void directoryRecord::setFilePart(unsigned int part, const std::wstring& partName)
{
	if(m_pDirectoryRecord == 0) throw dicomDirNullRecord("Null directoryRecord");
	try
	{
		m_pDirectoryRecord->setFilePart(part, partName);
	}
	CATCH_IMEBRA_EXCEPTIONS;
}

std::wstring directoryRecord::getTypeString()
{
	if(m_pDirectoryRecord == 0) throw dicomDirNullRecord("Null directoryRecord");
	try
	{
		return m_pDirectoryRecord->getTypeString();
	}
	CATCH_IMEBRA_EXCEPTIONS;
}

void directoryRecord::setTypeString(const std::wstring& recordType)
{
	if(m_pDirectoryRecord == 0) throw dicomDirNullRecord("Null directoryRecord");
	try
	{
		m_pDirectoryRecord->setTypeString(recordType);
	}
	CATCH_IMEBRA_EXCEPTIONS;
}

bool directoryRecord::isNull()
{
	return m_pDirectoryRecord == 0;
}


dicomDir::dicomDir(dataSet fromDataSet): m_pDicomDir(new puntoexe::imebra::dicomDir(fromDataSet.m_pDataSet))
{}

dataSet dicomDir::getDirectoryDataSet()
{
	try
	{
		return dataSet(m_pDicomDir->getDirectoryDataSet());
	}
	CATCH_IMEBRA_EXCEPTIONS;
}

directoryRecord dicomDir::getNewRecord()
{
	try
	{
		return directoryRecord(m_pDicomDir->getNewRecord());
	}
	CATCH_IMEBRA_EXCEPTIONS;
}

directoryRecord dicomDir::getFirstRootRecord()
{
	try
	{
		return directoryRecord(m_pDicomDir->getFirstRootRecord());
	}
	CATCH_IMEBRA_EXCEPTIONS;
}

void dicomDir::setFirstRootRecord(directoryRecord firstRootRecord)
{
	if(firstRootRecord.m_pDirectoryRecord == 0) throw dicomDirNullRecord("Null directoryRecord");
	try
	{
		m_pDicomDir->setFirstRootRecord(firstRootRecord.m_pDirectoryRecord);
	}
	CATCH_IMEBRA_EXCEPTIONS;
}

dataSet dicomDir::buildDataSet()
{
	try
	{
		return dataSet(m_pDicomDir->buildDataSet());
	}
	CATCH_IMEBRA_EXCEPTIONS;
}
