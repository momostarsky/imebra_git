/*
$fileHeader$
*/

/*! \file dicomDir_swig.h
    \brief Declaration of the classes that parse/create a DICOMDIR
		structure (dicomDir and directoryRecord) for SWIG

*/

#ifndef imebraDicomDir_SWIG_93F684BF_0024_4bf3_89BA_D98E82A1F44C__INCLUDED_
#define imebraDicomDir_SWIG_93F684BF_0024_4bf3_89BA_D98E82A1F44C__INCLUDED_

#include "../../imebra/include/dicomDir.h"
#include "dataSet_swig.h"

/// \addtogroup group_swig_bindings
/// @{

class directoryRecord
{
#ifndef SWIG
	friend class dicomDir;
#endif
public:
	directoryRecord();
	directoryRecord(const directoryRecord& right);


#ifndef SWIG
	directoryRecord(puntoexe::ptr<puntoexe::imebra::directoryRecord> pDirectoryRecord);
#endif

	directoryRecord& operator=(const directoryRecord& right);

	dataSet getRecordDataSet();

	directoryRecord getNextRecord();

	directoryRecord getFirstChildRecord();
	
	directoryRecord getReferencedRecord();

	void setNextRecord(const directoryRecord& nextRecord);

	void setFirstChildRecord(const directoryRecord& firstChildRecord);

	void setReferencedRecord(const directoryRecord& referencedRecord);
	
	std::wstring getFilePart(unsigned int part);

	void setFilePart(unsigned int part, const std::wstring& partName);

	std::wstring getTypeString();

	void setTypeString(const std::wstring& recordType);

	bool isNull();

#ifndef SWIG
private:
	puntoexe::ptr<puntoexe::imebra::directoryRecord> m_pDirectoryRecord;
#endif
};


class dicomDir
{
public:
	dicomDir(dataSet fromDataSet);

	dataSet getDirectoryDataSet();

	directoryRecord getNewRecord();

	directoryRecord getFirstRootRecord();

	void setFirstRootRecord(directoryRecord firstRootRecord);

	dataSet buildDataSet();

#ifndef SWIG
private:
	puntoexe::ptr<puntoexe::imebra::dicomDir> m_pDicomDir;
#endif
};

///@}

#endif // !defined(imebraDicomDir_SWIG_93F684BF_0024_4bf3_89BA_D98E82A1F44C__INCLUDED_)
