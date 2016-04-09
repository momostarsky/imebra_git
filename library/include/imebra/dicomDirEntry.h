/*
$fileHeader$
*/

/*! \file dicomDir.h
    \brief Declaration of the class DicomDirEntry
        structure (DicomDir and DirectoryRecord)

*/

#if !defined(imebraDicomDirEntry__INCLUDED_)
#define imebraDicomDirEntry__INCLUDED_

#include <memory>
#include <string>
#include "definitions.h"

#ifndef SWIG

namespace imebra
{
namespace implementation
{
class directoryRecord;
}
}

#endif

namespace imebra
{

class DataSet;

class IMEBRA_API DicomDirEntry
{
    DicomDirEntry(const DicomDirEntry&) = delete;
    DicomDirEntry& operator=(const DicomDirEntry&) = delete;

#ifndef SWIG
	friend class DicomDir;
private:
    DicomDirEntry(std::shared_ptr<imebra::implementation::directoryRecord> pDirectoryRecord);
#endif

public:
    DicomDirEntry(const DataSet& fromDataSet);

    virtual ~DicomDirEntry();

    DataSet* getEntryDataSet();

    DicomDirEntry* getNextEntry();

    DicomDirEntry* getFirstChildEntry();
	
    void setNextEntry(const DicomDirEntry& nextEntry);

    void setFirstChildEntry(const DicomDirEntry& firstChildEntry);

    fileParts_t getFileParts() const;

    void setFileParts(const fileParts_t& fileParts);

    directoryRecordType_t getType() const;

    void setType(directoryRecordType_t entryType);

    std::string getTypeString() const;

    void setTypeString(const std::string& entryType);

#ifndef SWIG
protected:
    std::shared_ptr<imebra::implementation::directoryRecord> m_pDirectoryRecord;
#endif
};

}

#endif // !defined(imebraDicomDirEntry__INCLUDED_)
