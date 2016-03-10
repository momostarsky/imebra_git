/*
$fileHeader$
*/

/*! \file dicomDir.cpp
    \brief Implementation of the classes that parse/create a DICOMDIR
        structure (DicomDir and DicomDirEntry).

*/

#include "../include/imebra/dicomDirEntry.h"
#include "../implementation/dicomDirImpl.h"

namespace imebra
{

DicomDirEntry::DicomDirEntry(){}

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
	if(m_pDirectoryRecord == 0) throw std::logic_error("Null directoryRecord");
	return DataSet(m_pDirectoryRecord->getRecordDataSet());
}

DicomDirEntry DicomDirEntry::getNextEntry()
{
	if(m_pDirectoryRecord == 0) throw std::logic_error("Null directoryRecord");
	return DicomDirEntry(m_pDirectoryRecord->getNextRecord());
}

DicomDirEntry DicomDirEntry::getFirstChildEntry()
{
	if(m_pDirectoryRecord == 0) throw std::logic_error("Null directoryRecord");
	return DicomDirEntry(m_pDirectoryRecord->getFirstChildRecord());
}
	
DicomDirEntry DicomDirEntry::getReferencedEntry()
{
	if(m_pDirectoryRecord == 0) throw std::logic_error("Null directoryRecord");
	return DicomDirEntry(m_pDirectoryRecord->getReferencedRecord());
}

void DicomDirEntry::setNextEntry(const DicomDirEntry& nextEntry)
{
	if(m_pDirectoryRecord == 0) throw std::logic_error("Null directoryRecord");
    m_pDirectoryRecord->setNextRecord(nextEntry.m_pDirectoryRecord);
}

void DicomDirEntry::setFirstChildEntry(const DicomDirEntry& firstChildEntry)
{
	if(m_pDirectoryRecord == 0) throw std::logic_error("Null directoryRecord");
    m_pDirectoryRecord->setFirstChildRecord(firstChildEntry.m_pDirectoryRecord);
}

void DicomDirEntry::setReferencedEntry(const DicomDirEntry& referencedEntry)
{
	if(m_pDirectoryRecord == 0) throw std::logic_error("Null directoryRecord");
    m_pDirectoryRecord->setReferencedRecord(referencedEntry.m_pDirectoryRecord);
}
	
fileParts_t DicomDirEntry::getFileParts() const
{
	if(m_pDirectoryRecord == 0) throw std::logic_error("Null directoryRecord");
    return m_pDirectoryRecord->getFileParts();
}

void DicomDirEntry::setFileParts(const fileParts_t& fileParts)
{
	if(m_pDirectoryRecord == 0) throw std::logic_error("Null directoryRecord");
    m_pDirectoryRecord->setFileParts(fileParts);
}

std::string DicomDirEntry::getTypeString() const
{
	if(m_pDirectoryRecord == 0) throw std::logic_error("Null directoryRecord");
	return m_pDirectoryRecord->getTypeString();
}

void DicomDirEntry::setTypeString(const std::string& entryType)
{
	if(m_pDirectoryRecord == 0) throw std::logic_error("Null directoryRecord");
    m_pDirectoryRecord->setTypeString(entryType);
}

bool DicomDirEntry::isNull() const
{
	return m_pDirectoryRecord == 0;
}

}
