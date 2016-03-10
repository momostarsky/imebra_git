/*
$fileHeader$
*/

/*! \file dicomDir.h
    \brief Declaration of the classes that parse/create a DICOMDIR
        structure (DicomDir and DirectoryRecord)

*/

#if !defined(imebraDicomDir__INCLUDED_)
#define imebraDicomDir__INCLUDED_

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
class dicomDir;
}
}

#endif

namespace imebra
{

class IMEBRA_API DirectoryRecord
{
#ifndef SWIG
	friend class DicomDir;
private:
    DirectoryRecord(std::shared_ptr<imebra::implementation::directoryRecord> pDirectoryRecord);
#endif

public:
	DirectoryRecord();
	DirectoryRecord(const DirectoryRecord& right);
    virtual ~DirectoryRecord();

	DirectoryRecord& operator=(const DirectoryRecord& right);

	DataSet getRecordDataSet();

	DirectoryRecord getNextRecord();

	DirectoryRecord getFirstChildRecord();
	
	DirectoryRecord getReferencedRecord();

	void setNextRecord(const DirectoryRecord& nextRecord);

	void setFirstChildRecord(const DirectoryRecord& firstChildRecord);

	void setReferencedRecord(const DirectoryRecord& referencedRecord);
	
    fileParts_t getFileParts() const;

    void setFileParts(const fileParts_t& fileParts);

    std::string getTypeString() const;

    void setTypeString(const std::string& recordType);

    bool isNull() const;

#ifndef SWIG
protected:
    std::shared_ptr<imebra::implementation::directoryRecord> m_pDirectoryRecord;
#endif
};


class IMEBRA_API DicomDir
{
public:
	DicomDir(DataSet fromDataSet);
    virtual ~DicomDir();

	DataSet getDirectoryDataSet();

	DirectoryRecord getNewRecord();

	DirectoryRecord getFirstRootRecord();

	void setFirstRootRecord(DirectoryRecord firstRootRecord);

	DataSet buildDataSet();

#ifndef SWIG
protected:
    std::shared_ptr<imebra::implementation::dicomDir> m_pDicomDir;
#endif
};

}

#endif // !defined(imebraDicomDir__INCLUDED_)
