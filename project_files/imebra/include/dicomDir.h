/*
$fileHeader$
*/

/*! \file dicomDir.h
    \brief Declaration of the class dicomDir.

*/

#if !defined(imebraDicomDir_93F684BF_0024_4bf3_89BA_D98E82A1F44C__INCLUDED_)
#define imebraDicomDir_93F684BF_0024_4bf3_89BA_D98E82A1F44C__INCLUDED_

#include "../../base/include/baseObject.h"
#include <string>

///////////////////////////////////////////////////////////
//
// Everything is in the namespace puntoexe::imebra
//
///////////////////////////////////////////////////////////
namespace puntoexe
{

namespace imebra
{


class dataSet; // Used in this class
class dicomDir;



///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief directoryRecord represents a single record in
///         a DICOMDIR structure. DICOMDIR is represented
///         by the class dicomDir.
///
/// 
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class directoryRecord: public baseObject
{
	friend class dicomDir;
public:
	enum tDirectoryRecordType
	{
		patient,
		study,
		series,
		image,
		overlay,
		modality_lut,
		voi_lut,
		curve,
		topic,
		visit,
		results,
		interpretation,
		study_component,
        stored_print,
		rt_dose,
		rt_structure_set,
		rt_plan,
		rt_treat_record,
		presentation,
		waveform,
		sr_document,
		key_object_doc,
		spectroscopy,
		raw_data,
		registration,
		fiducial,
		mrdr,
		endOfDirectoryRecordTypes
	};


public:
	/// \brief Returns the dataSet object that contains the
	///         information related to the record.
	///
	/// The DICOMDIR dataSet contains several records' dataSets
	///  embedded into a sequence tag.
	///
	/// @return the dataSet that contains the information 
	///          related to the record.
	///
	///////////////////////////////////////////////////////////
	ptr<dataSet> getRecordDataSet();

	/// \brief Returns the next sibling record.
	///
	/// @return the next sibling record, or 0 if this is the
	///          last record
	///
	///////////////////////////////////////////////////////////
	ptr<directoryRecord> getNextRecord();

	/// \brief Returns the first child record.
	///
	/// @return the first child record, or 0 if the record 
	///          doesn't have any child
	///
	///////////////////////////////////////////////////////////
	ptr<directoryRecord> getFirstChildRecord();
	
	/// \brief Returns the referenced record, if any.
	///
	/// @return the referenced record, or 0 if the record
	///          doesn't reference any other record
	///
	///////////////////////////////////////////////////////////
	ptr<directoryRecord> getReferencedRecord();

	/// \brief Sets the next sibling record.
	///
	/// The new sibling record takes the place of the old
	///  next sibling record, if it was already set.
	///
	/// @param pNextRecord    the next sibling record
	///
	///////////////////////////////////////////////////////////
	void setNextRecord(ptr<directoryRecord> pNextRecord);

	/// \brief Set the first child record.
	///
	/// The new child record takes the place of the old child
	///  record, if it was already set.
	///
	/// @param pFirstChildRecordRecord the first child record
	///
	///////////////////////////////////////////////////////////
	void setFirstChildRecord(ptr<directoryRecord> pFirstChildRecord);

	/// \brief Set the referenced record.
	///
	/// The new referenced record takes the place of the old 
	///  referenced record, if it was already set.
	///
	/// @param pReferencedRecord the referenced record
	///
	///////////////////////////////////////////////////////////
	void setReferencedRecord(ptr<directoryRecord> pReferencedRecord);
	
	/// \brief Get the full path to the  file referenced by
	///         the record.
	///
	/// Several calls to this function may have to be made to 
	///  obtain the full file path.
	///
	/// The full file path is formed by a list of folder and
	///  by the file name; for each call to this function
	///  the caller has to specify a zero based part number.
	///
	/// The last valid part contains the file name, while
	///  the parts before the last one contain the folder
	///  in which the file is stored; each folder is a child
	///  of the folder returned by the previous part.
	///
	/// The function returns an empty string if the
	///  specified part doesn't exist.
	/// 
	/// @param part the part to be returned, 0 based.
	/// @return the part's name (folder or file), or an
	///          empty string if the requested part doesn't
	///          exist
	///
	///////////////////////////////////////////////////////////
	std::wstring getFilePart(imbxUint32 part);

	/// \brief Returns the record's type.
	///
	/// This function calls getTypeString() and convert the
	///  result to an enumerated value.
	///
	/// @return the record's type
	///
	///////////////////////////////////////////////////////////
	tDirectoryRecordType getType();

	/// \brief Returns a string representing the record's type.
	///
	/// @return the record's type
	///
	///////////////////////////////////////////////////////////
	std::wstring getTypeString();

	void setType(tDirectoryRecordType recordType);
	void setTypeString(std::wstring recordType);


protected:
	/// \brief Constructor. A directoryRecord object must be
	///         connected to a dataSet object, which contains
	///         the record's information.
	///
	/// The dataSet object is an item of the sequence tag 
	///  0004,1220
	///
	/// When a directoryRecord is connected to an empty dataSet
	///  then the other constructor must be used, which allows
	///  to define the record type.
	///
	/// @param pDataSet  the dataSet that must be connected
	///                   to the directoryRecord
	///
	///////////////////////////////////////////////////////////
	directoryRecord(ptr<dataSet> pDataSet);

	void checkCircularReference(directoryRecord* pStartRecord);

	void updateOffsets();

	ptr<directoryRecord> m_pNextRecord;
	ptr<directoryRecord> m_pFirstChildRecord;
	ptr<directoryRecord> m_pReferencedRecord;

	ptr<dataSet> m_pDataSet;
};


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief A dicomDir contains the information about the
///        tree structure of the DICOMDIR.
///
/// 
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class dicomDir: public baseObject
{
public:
	/// \brief Build a dicomDir object and attach it to an
	///         existing dataset.
	///
	///////////////////////////////////////////////////////////
	dicomDir(ptr<dataSet> pDataSet);

	ptr<dataSet> getDirectoryDataSet();

	ptr<directoryRecord> getNewRecord();

	ptr<directoryRecord> getFirstRootRecord();
	void setFirstRootRecord(ptr<directoryRecord> pFirstRootRecord);

protected:
	// Destructor
	///////////////////////////////////////////////////////////
	virtual bool preDelete();

	ptr<dataSet> m_pDataSet;

	ptr<directoryRecord> m_pFirstRootRecord;
};


class dicomDirException: public std::runtime_error
{
public:
	/// \brief Build a dicomDirException exception.
	///
	/// @param message the message to store into the exception
	///
	///////////////////////////////////////////////////////////
	dicomDirException(const std::string& message): std::runtime_error(message){}
};

class dicomDirCircularReferenceException: public dicomDirException
{
public:
	/// \brief Build a dicomDirException exception.
	///
	/// @param message the message to store into the exception
	///
	///////////////////////////////////////////////////////////
	dicomDirCircularReferenceException(const std::string& message): dicomDirException(message){}
};

class dicomDirUnknownDirectoryRecordType: public dicomDirException
{
public:
	dicomDirUnknownDirectoryRecordType(const std::string& message): dicomDirException(message){}
};


} // namespace imebra

} // namespace puntoexe

#endif // !defined(imebraDicomDir_93F684BF_0024_4bf3_89BA_D98E82A1F44C__INCLUDED_)
