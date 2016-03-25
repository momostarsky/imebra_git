/*
$fileHeader$
*/

/*! \file dicomDir.h
    \brief Declaration of the class DicomDirEntry
        structure (DicomDir and DirectoryRecord)

*/

#if !defined(imebraDicomDirEntry__INCLUDED_)
#define imebraDicomDirEntry__INCLUDED_

#ifndef SWIG

#include <memory>
#include <string>
#include "dataSet.h"
#include "definitions.h"

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

class IMEBRA_API DicomDirEntry
{
#ifndef SWIG
	friend class DicomDir;
private:
    DicomDirEntry(std::shared_ptr<imebra::implementation::directoryRecord> pDirectoryRecord);
#endif

public:
    DicomDirEntry(const DataSet& fromDataSet);

    DicomDirEntry(const DicomDirEntry& right);
    virtual ~DicomDirEntry();

    DicomDirEntry& operator=(const DicomDirEntry& right);

    DataSet getEntryDataSet();

    DicomDirEntry getNextEntry();

    DicomDirEntry getFirstChildEntry();
	
    DicomDirEntry getReferencedEntry();

    void setNextEntry(const DicomDirEntry& nextEntry);

    void setFirstChildEntry(const DicomDirEntry& firstChildEntry);

    void setReferencedEntry(const DicomDirEntry& referencedEntry);
	
    fileParts_t getFileParts() const;

    void setFileParts(const fileParts_t& fileParts);

    std::string getTypeString() const;

    void setTypeString(const std::string& entryType);

#ifndef SWIG
protected:
    std::shared_ptr<imebra::implementation::directoryRecord> m_pDirectoryRecord;
#endif
};

}

#endif // !defined(imebraDicomDirEntry__INCLUDED_)
