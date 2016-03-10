/*
$fileHeader$
*/

/*! \file dicomDir.h
    \brief Declaration of the class DicomDir.

*/

#if !defined(imebraDicomDir__INCLUDED_)
#define imebraDicomDir__INCLUDED_

#ifndef SWIG

#include <memory>
#include <string>
#include "dataSet.h"
#include "definitions.h"
#include "dicomDirEntry.h"

namespace imebra
{
namespace implementation
{
class dicomDir;
}
}

#endif

namespace imebra
{

class IMEBRA_API DicomDir
{
public:
	DicomDir(DataSet fromDataSet);
    virtual ~DicomDir();

	DataSet getDirectoryDataSet();

    DicomDirEntry getNewEntry();

    DicomDirEntry getFirstRootEntry();

    void setFirstRootEntry(DicomDirEntry firstEntryRecord);

	DataSet buildDataSet();

#ifndef SWIG
protected:
    std::shared_ptr<imebra::implementation::dicomDir> m_pDicomDir;
#endif
};

}

#endif // !defined(imebraDicomDir__INCLUDED_)
