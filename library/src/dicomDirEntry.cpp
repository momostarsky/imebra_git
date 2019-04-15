/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement 
 that your application must also be GPL), you may purchase a commercial 
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

/*! \file dicomDir.cpp
    \brief Implementation of the classes that parse/create a DICOMDIR
        structure (DicomDir and DicomDirEntry).

*/

#include "../include/imebra/dicomDirEntry.h"
#include "../include/imebra/dataSet.h"
#include "../implementation/dicomDirImpl.h"
#include "../include/imebra/exceptions.h"

namespace imebra
{

DicomDirEntry::DicomDirEntry(const DicomDirEntry &source): m_pDirectoryRecord(getDicomDirEntryImplementation(source))
{
}

DicomDirEntry::DicomDirEntry(const std::shared_ptr<imebra::implementation::directoryRecord>& pDirectoryRecord): m_pDirectoryRecord(pDirectoryRecord)
{
}

DicomDirEntry& DicomDirEntry::operator=(const DicomDirEntry& source)
{
    m_pDirectoryRecord = getDicomDirEntryImplementation(source);
    return *this;
}

const std::shared_ptr<implementation::directoryRecord>& getDicomDirEntryImplementation(const DicomDirEntry& dicomDirEntry)
{
    return dicomDirEntry.m_pDirectoryRecord;
}

DicomDirEntry::~DicomDirEntry()
{
}

DataSet DicomDirEntry::getEntryDataSet() const
{
    return DataSet(m_pDirectoryRecord->getRecordDataSet());
}

bool DicomDirEntry::hasNextEntry() const
{
    std::shared_ptr<implementation::directoryRecord> pNextEntry(m_pDirectoryRecord->getNextRecord());
    return pNextEntry != 0;
}

DicomDirEntry DicomDirEntry::getNextEntry() const
{
    std::shared_ptr<implementation::directoryRecord> pNextEntry(m_pDirectoryRecord->getNextRecord());
    if(pNextEntry == 0)
    {
        throw DicomDirNoEntryError("Missing sibling entry");;
    }
    return DicomDirEntry(pNextEntry);
}

bool DicomDirEntry::hasChildren() const
{
    std::shared_ptr<implementation::directoryRecord> pChildEntry(m_pDirectoryRecord->getFirstChildRecord());
    return pChildEntry != 0;
}

DicomDirEntry DicomDirEntry::getFirstChildEntry() const
{
    std::shared_ptr<implementation::directoryRecord> pChildEntry(m_pDirectoryRecord->getFirstChildRecord());
    if(pChildEntry == 0)
    {
        throw DicomDirNoEntryError("There isn't any child entry");
    }
    return DicomDirEntry(pChildEntry);
}
	
fileParts_t DicomDirEntry::getFileParts() const
{
    return m_pDirectoryRecord->getFileParts();
}

std::string DicomDirEntry::getTypeString() const
{
    return m_pDirectoryRecord->getTypeString();
}

MutableDicomDirEntry::MutableDicomDirEntry(const MutableDicomDirEntry &source): DicomDirEntry(getDicomDirEntryImplementation(source))
{
}

MutableDicomDirEntry::MutableDicomDirEntry(const std::shared_ptr<imebra::implementation::directoryRecord>& pDirectoryRecord): DicomDirEntry(pDirectoryRecord)
{
}

MutableDicomDirEntry& MutableDicomDirEntry::operator=(const MutableDicomDirEntry& source)
{
    DicomDirEntry::operator =(source);
    return *this;
}

MutableDataSet MutableDicomDirEntry::getEntryDataSet()
{
    return MutableDataSet(getDicomDirEntryImplementation(*this)->getRecordDataSet());
}

void MutableDicomDirEntry::setNextEntry(const DicomDirEntry& nextEntry)
{
    getDicomDirEntryImplementation(*this)->setNextRecord(getDicomDirEntryImplementation(nextEntry));
}

void MutableDicomDirEntry::setFirstChildEntry(const DicomDirEntry& firstChildEntry)
{
    getDicomDirEntryImplementation(*this)->setFirstChildRecord(getDicomDirEntryImplementation(firstChildEntry));
}

void MutableDicomDirEntry::setFileParts(const fileParts_t& fileParts)
{
    getDicomDirEntryImplementation(*this)->setFileParts(fileParts);
}

}
