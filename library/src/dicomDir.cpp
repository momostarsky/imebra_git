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

#include "../include/imebra/dicomDir.h"
#include "../include/imebra/dataSet.h"
#include "../include/imebra/dicomDirEntry.h"
#include "../implementation/dicomDirImpl.h"
#include "../include/imebra/exceptions.h"

namespace imebra
{

DicomDir::DicomDir(const DataSet& fromDataSet): m_pDicomDir(std::make_shared<imebra::implementation::dicomDir>(getDataSetImplementation(fromDataSet)))
{
}

DicomDir::DicomDir(const DicomDir& source): m_pDicomDir(getDicomDirImplementation(source))
{
}

DicomDir& DicomDir::operator=(const DicomDir& source)
{
    m_pDicomDir = getDicomDirImplementation(source);
    return *this;
}

const std::shared_ptr<implementation::dicomDir>& getDicomDirImplementation(const DicomDir& dicomDir)
{
    return dicomDir.m_pDicomDir;
}

DicomDir::DicomDir(const std::shared_ptr<implementation::dicomDir>& pDicomDir): m_pDicomDir(pDicomDir)
{
}

DicomDir::~DicomDir()
{
}

bool DicomDir::hasRootEntry() const
{
    std::shared_ptr<implementation::directoryRecord> pRootRecord(m_pDicomDir->getFirstRootRecord());
    return pRootRecord != 0;
}

DicomDirEntry DicomDir::getFirstRootEntry() const
{
    std::shared_ptr<implementation::directoryRecord> pRootRecord(m_pDicomDir->getFirstRootRecord());
    if(pRootRecord == 0)
    {
        throw DicomDirNoEntryError("Missing root entry");
    }
    return DicomDirEntry(pRootRecord);
}

MutableDicomDir::MutableDicomDir(): DicomDir(std::make_shared<imebra::implementation::dicomDir>())
{
}

MutableDicomDir::MutableDicomDir(MutableDataSet& dataSet): DicomDir(dataSet)
{
}

MutableDicomDir::MutableDicomDir(const MutableDicomDir &source): DicomDir(source)
{
}

MutableDicomDir& MutableDicomDir::operator=(const MutableDicomDir& source)
{
    DicomDir::operator =(source);
    return *this;
}

MutableDicomDirEntry MutableDicomDir::getNewEntry(const std::string& recordType)
{
    return MutableDicomDirEntry(getDicomDirImplementation(*this)->getNewRecord(recordType));
}

void MutableDicomDir::setFirstRootEntry(const DicomDirEntry& firstEntryRecord)
{
    getDicomDirImplementation(*this)->setFirstRootRecord(getDicomDirEntryImplementation(firstEntryRecord));
}

DataSet MutableDicomDir::updateDataSet()
{
    return DataSet(getDicomDirImplementation(*this)->buildDataSet());
}

}
