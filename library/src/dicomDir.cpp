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
    m_pDicomDir = std::make_shared<imebra::implementation::dicomDir>();
}

DicomDir::DicomDir(const DataSet& fromDataSet): m_pDicomDir(std::make_shared<imebra::implementation::dicomDir>(fromDataSet.m_pDataSet))
{
}

DicomDir::~DicomDir()
{
}

DicomDirEntry* DicomDir::getNewEntry(directoryRecordType_t recordType)
{
    return new DicomDirEntry(m_pDicomDir->getNewRecord(recordType));
}

DicomDirEntry* DicomDir::getFirstRootEntry() const
{
    std::shared_ptr<implementation::directoryRecord> pRootRecord(m_pDicomDir->getFirstRootRecord());
    if(pRootRecord == 0)
    {
        return 0;
    }
    return new DicomDirEntry(pRootRecord);
}

void DicomDir::setFirstRootEntry(const DicomDirEntry& firstEntryRecord)
{
    m_pDicomDir->setFirstRootRecord(firstEntryRecord.m_pDirectoryRecord);
}

DataSet* DicomDir::updateDataSet()
{
    return new DataSet(m_pDicomDir->buildDataSet());
}

}
