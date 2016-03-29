/*
$fileHeader$
*/

/*! \file dicomDir.cpp
    \brief Implementation of the classes that parse/create a DICOMDIR
        structure (DicomDir and DicomDirEntry).

*/

#include "../include/imebra/dicomDirEntry.h"
#include "../include/imebra/dataSet.h"
#include "../implementation/dicomDirImpl.h"

namespace imebra
{

DicomDirEntry::DicomDirEntry(const DataSet& fromDataSet):
    m_pDirectoryRecord(std::make_shared<imebra::implementation::directoryRecord>(fromDataSet.m_pDataSet))
{}

DicomDirEntry::DicomDirEntry(const DicomDirEntry& right): m_pDirectoryRecord(right.m_pDirectoryRecord)
{
}

DicomDirEntry::DicomDirEntry(std::shared_ptr<imebra::implementation::directoryRecord> pDirectoryRecord): m_pDirectoryRecord(pDirectoryRecord)
{
}

DicomDirEntry::~DicomDirEntry()
{
}

DicomDirEntry& DicomDirEntry::operator=(const DicomDirEntry& right)
{
	m_pDirectoryRecord = right.m_pDirectoryRecord;
	return *this;
}

DataSet DicomDirEntry::getEntryDataSet()
{
	return DataSet(m_pDirectoryRecord->getRecordDataSet());
}

DicomDirEntry DicomDirEntry::getNextEntry()
{
	return DicomDirEntry(m_pDirectoryRecord->getNextRecord());
}

DicomDirEntry DicomDirEntry::getFirstChildEntry()
{
	return DicomDirEntry(m_pDirectoryRecord->getFirstChildRecord());
}
	
void DicomDirEntry::setNextEntry(const DicomDirEntry& nextEntry)
{
    m_pDirectoryRecord->setNextRecord(nextEntry.m_pDirectoryRecord);
}

void DicomDirEntry::setFirstChildEntry(const DicomDirEntry& firstChildEntry)
{
    m_pDirectoryRecord->setFirstChildRecord(firstChildEntry.m_pDirectoryRecord);
}

fileParts_t DicomDirEntry::getFileParts() const
{
    return m_pDirectoryRecord->getFileParts();
}

void DicomDirEntry::setFileParts(const fileParts_t& fileParts)
{
    m_pDirectoryRecord->setFileParts(fileParts);
}

directoryRecordType_t DicomDirEntry::getType() const
{
    return m_pDirectoryRecord->getType();
}

void DicomDirEntry::setType(directoryRecordType_t entryType)
{
    m_pDirectoryRecord->setType(entryType);
}

std::string DicomDirEntry::getTypeString() const
{
	return m_pDirectoryRecord->getTypeString();
}

void DicomDirEntry::setTypeString(const std::string& entryType)
{
    m_pDirectoryRecord->setTypeString(entryType);
}

}
