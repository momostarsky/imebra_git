/*
$fileHeader$
*/

/*! \file dicomDir_swig.h
    \brief Declaration of the classes that parse/create a DICOMDIR
		structure (dicomDir and directoryRecord) for SWIG

*/

#ifndef imebraDicomDir_SWIG_93F684BF_0024_4bf3_89BA_D98E82A1F44C__INCLUDED_
#define imebraDicomDir_SWIG_93F684BF_0024_4bf3_89BA_D98E82A1F44C__INCLUDED_

#ifndef SWIG

#include <memory>

namespace puntoexe
{
namespace imebra
{
class directoryRecord;
class dicomDir;
}
}

#endif

#include "dataSet.h"

namespace imebra
{

/// \addtogroup group_swig_bindings
/// @{

class DirectoryRecord
{
#ifndef SWIG
	friend class DicomDir;
#endif
public:
	DirectoryRecord();
	DirectoryRecord(const DirectoryRecord& right);


#ifndef SWIG
	DirectoryRecord(std::shared_ptr<puntoexe::imebra::directoryRecord> pDirectoryRecord);
#endif

	DirectoryRecord& operator=(const DirectoryRecord& right);

	DataSet getRecordDataSet();

	DirectoryRecord getNextRecord();

	DirectoryRecord getFirstChildRecord();
	
	DirectoryRecord getReferencedRecord();

	void setNextRecord(const DirectoryRecord& nextRecord);

	void setFirstChildRecord(const DirectoryRecord& firstChildRecord);

	void setReferencedRecord(const DirectoryRecord& referencedRecord);
	
    std::wstring getFilePart(int part) const;

	void setFilePart(int part, const std::wstring& partName);

    std::wstring getTypeString() const;

	void setTypeString(const std::wstring& recordType);

    bool isNull() const;

#ifndef SWIG
private:
	std::shared_ptr<puntoexe::imebra::directoryRecord> m_pDirectoryRecord;
#endif
};


class DicomDir
{
public:
	DicomDir(DataSet fromDataSet);

	DataSet getDirectoryDataSet();

	DirectoryRecord getNewRecord();

	DirectoryRecord getFirstRootRecord();

	void setFirstRootRecord(DirectoryRecord firstRootRecord);

	DataSet buildDataSet();

#ifndef SWIG
private:
	std::shared_ptr<puntoexe::imebra::dicomDir> m_pDicomDir;
#endif
};

///@}

}

#endif // !defined(imebraDicomDir_SWIG_93F684BF_0024_4bf3_89BA_D98E82A1F44C__INCLUDED_)
