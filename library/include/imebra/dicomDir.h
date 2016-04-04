/*
$fileHeader$
*/

/*! \file dicomDir.h
    \brief Declaration of the class DicomDir.

*/

#if !defined(imebraDicomDir__INCLUDED_)
#define imebraDicomDir__INCLUDED_

#include <memory>
#include <string>
#include "definitions.h"

#ifndef SWIG

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

class DataSet;
class DicomDirEntry;

///
/// \brief Represents a DICOMDIR structure.
///
/// It parses a DataSet created from parsing a DICOMDIR file and gives access
/// to the individual DICOMDIR items, each represented by a DicomDirEntry
/// object.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API DicomDir
{
public:
    DicomDir();

    /// \brief Construct a DicomDir from a DataSet object.
    ///
    /// \param fromDataSet the DataSet created from reading a DICOMDIR file
    ///
    ///////////////////////////////////////////////////////////////////////////////
    DicomDir(const DataSet& fromDataSet);
    virtual ~DicomDir();

    /// \brief Return the DataSet that was used to build the DicomDir object, or
    ///        that was updated via buildDataSet().
    ///
    /// \return the DataSet that was used to create the DicomDir, or the last one
    ///         created via buildDataSet
    ///////////////////////////////////////////////////////////////////////////////
    DataSet getDirectoryDataSet() const;

    DicomDirEntry getNewEntry();

    DicomDirEntry getFirstRootEntry() const;

    void setFirstRootEntry(const DicomDirEntry& firstEntryRecord);

	DataSet buildDataSet();

#ifndef SWIG
protected:
    std::shared_ptr<imebra::implementation::dicomDir> m_pDicomDir;
#endif
};

}

#endif // !defined(imebraDicomDir__INCLUDED_)
