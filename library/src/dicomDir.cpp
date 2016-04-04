/*
$fileHeader$
*/

/*! \file dicomDir.cpp
    \brief Implementation of the classes that parse/create a DICOMDIR
        structure (DicomDir and DicomDirEntry).

*/

#include "../include/imebra/dicomDir.h"
#include "../include/imebra/dataSet.h"
#include "../include/imebra/dicomDirEntry.h"
#include "../implementation/dicomDirImpl.h"

namespace imebra
{

DicomDir::DicomDir()
{
    DataSet emptyDataSet;
    m_pDicomDir = std::make_shared<imebra::implementation::dicomDir>(emptyDataSet.m_pDataSet);
}

DicomDir::DicomDir(const DataSet& fromDataSet): m_pDicomDir(std::make_shared<imebra::implementation::dicomDir>(fromDataSet.m_pDataSet))
{
}

DicomDir::~DicomDir()
{
}

DataSet DicomDir::getDirectoryDataSet() const
{
	return DataSet(m_pDicomDir->getDirectoryDataSet());
}

DicomDirEntry DicomDir::getNewEntry()
{
	return DicomDirEntry(m_pDicomDir->getNewRecord());
}

DicomDirEntry DicomDir::getFirstRootEntry() const
{
	return DicomDirEntry(m_pDicomDir->getFirstRootRecord());
}

void DicomDir::setFirstRootEntry(const DicomDirEntry& firstEntryRecord)
{
    if(firstEntryRecord.m_pDirectoryRecord == 0) throw std::logic_error("Null directoryRecord");
    m_pDicomDir->setFirstRootRecord(firstEntryRecord.m_pDirectoryRecord);
}

DataSet DicomDir::buildDataSet()
{
	return DataSet(m_pDicomDir->buildDataSet());
}

}
