/*
$fileHeader$
*/

/*! \file dicomDir.cpp
    \brief Implementation of the classes dicomDir and directoryRecord.

*/

#include "dicomDirImpl.h"
#include "dataSetImpl.h"
#include "dicomCodecImpl.h"
#include "dataHandlerNumericImpl.h"
#include "nullStreamImpl.h"
#include "streamWriterImpl.h"
#include "../include/imebra/exceptions.h"
#include <map>
#include <string>

namespace puntoexe
{

namespace imebra
{


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
//
// directoryRecord
//
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Constructor
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
directoryRecord::directoryRecord(std::shared_ptr<dataSet> pDataSet):
	m_pDataSet(pDataSet)
{
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Return the record's dataset
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::shared_ptr<dataSet> directoryRecord::getRecordDataSet() const
{
	return m_pDataSet;
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Returns the next sibling record
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::shared_ptr<directoryRecord> directoryRecord::getNextRecord() const
{
	return m_pNextRecord;
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Returns the first child record
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::shared_ptr<directoryRecord> directoryRecord::getFirstChildRecord() const
{
	return m_pFirstChildRecord;
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Returns the referenced record
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::shared_ptr<directoryRecord> directoryRecord::getReferencedRecord() const
{
	return m_pReferencedRecord;
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Sets the next sibling record
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void directoryRecord::setNextRecord(std::shared_ptr<directoryRecord> pNextRecord)
{
	if(pNextRecord != 0)
	{
		pNextRecord->checkCircularReference(this);
	}
	m_pNextRecord = pNextRecord;
}
	

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Set the first child record
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void directoryRecord::setFirstChildRecord(std::shared_ptr<directoryRecord> pFirstChildRecord)
{
	if(pFirstChildRecord != 0)
	{
		pFirstChildRecord->checkCircularReference(this);
	}
	m_pFirstChildRecord = pFirstChildRecord;
}
	

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Sets the referenced record
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void directoryRecord::setReferencedRecord(std::shared_ptr<directoryRecord> pReferencedRecord)
{
	if(pReferencedRecord != 0)
	{
		pReferencedRecord->checkCircularReference(this);
	}
	m_pReferencedRecord = pReferencedRecord;
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Returns a part of the full file path
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::wstring directoryRecord::getFilePart(std::uint32_t part) const
{
    return getRecordDataSet()->getUnicodeString(0x0004, 0, 0x1500, 0, part);
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Set a part of the full file path
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void directoryRecord::setFilePart(std::uint32_t part, const std::wstring partName)
{
    getRecordDataSet()->setUnicodeString(0x0004, 0, 0x1500, 0, part, partName);
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Returns the record's type (enum)
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
directoryRecord::tDirectoryRecordType directoryRecord::getType() const
{
	std::wstring typeString(getTypeString());

    const tDirectoryRecordTypeDef* typesList(getRecordTypeMap());
	for(size_t scanTypes(0); typesList[scanTypes].m_type != endOfDirectoryRecordTypes; ++scanTypes)
	{
		if(typesList[scanTypes].m_name == typeString)
		{
			return typesList[scanTypes].m_type;
		}
	}

	// Invalid value found . Throw an exception
	///////////////////////////////////////////////////////////
    throw ::imebra::dicomDirUnknownDirectoryRecordType("Unknown directory record type");
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Returns the record's type (string)
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::wstring directoryRecord::getTypeString() const
{
    return getRecordDataSet()->getUnicodeString(0x0004, 0, 0x1430, 0, 0);
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Set the item's type
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void directoryRecord::setType(tDirectoryRecordType recordType)
{
    const tDirectoryRecordTypeDef* typesList(getRecordTypeMap());
	for(size_t scanTypes(0); typesList[scanTypes].m_type != endOfDirectoryRecordTypes; ++scanTypes)
	{
		if(typesList[scanTypes].m_type == recordType)
		{
            getRecordDataSet()->setUnicodeString(0x0004, 0, 0x1430, 0, 0, typesList[scanTypes].m_name);
			return;
		}
	}

	// Trying to set an invalid type. Throw an exception
	///////////////////////////////////////////////////////////
    throw ::imebra::dicomDirUnknownDirectoryRecordType("Unknown directory record type");
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Set the item's type
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void directoryRecord::setTypeString(const std::wstring& recordType)
{
    getRecordDataSet()->setUnicodeString(0x0004, 0, 0x1430, 0, 0, recordType);
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Update the dataSet's offsets. 
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void directoryRecord::updateOffsets()
{
	// Update offset for the next record
	///////////////////////////////////////////////////////////
	if(m_pNextRecord == 0)
	{
        getRecordDataSet()->setUnsignedLong(0x0004, 0, 0x1400, 0, 0, 0);
	}
	else
	{
        getRecordDataSet()->setUnsignedLong(0x0004, 0, 0x1400, 0, 0, m_pNextRecord->getRecordDataSet()->getItemOffset());
		m_pNextRecord->updateOffsets();
	}

	// Update offset for the first child record
	///////////////////////////////////////////////////////////
	if(m_pFirstChildRecord == 0)
	{
        getRecordDataSet()->setUnsignedLong(0x0004, 0, 0x1420, 0, 0, 0);
	}
	else
	{
        getRecordDataSet()->setUnsignedLong(0x0004, 0, 0x1420, 0, 0, m_pFirstChildRecord->getRecordDataSet()->getItemOffset());
		m_pFirstChildRecord->updateOffsets();
	}

	// Update offset for the referenced record
	///////////////////////////////////////////////////////////
	if(m_pReferencedRecord == 0)
	{
        getRecordDataSet()->setUnsignedLong(0x0004, 0, 0x1504, 0, 0, 0);
	}
	else
	{
        getRecordDataSet()->setUnsignedLong(0x0004, 0, 0x1504, 0, 0, m_pReferencedRecord->getRecordDataSet()->getItemOffset());
		m_pReferencedRecord->updateOffsets();
	}
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Check circular (recursive) references between the
//  dicomdir's items
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void directoryRecord::checkCircularReference(directoryRecord* pStartRecord)
{
	if(this == pStartRecord)
	{
        throw ::imebra::dicomDirCircularReferenceException("Circular reference detected");
	}

	if(m_pNextRecord != 0)
	{
		m_pNextRecord->checkCircularReference(pStartRecord);
	}

	if(m_pFirstChildRecord != 0)
	{
		m_pFirstChildRecord->checkCircularReference(pStartRecord);
	}

	if(m_pReferencedRecord != 0)
	{
		m_pReferencedRecord->checkCircularReference(pStartRecord);
	}
}


const directoryRecord::tDirectoryRecordTypeDef* directoryRecord::getRecordTypeMap()
{
    static const tDirectoryRecordTypeDef typesList[] =
    {
        {L"PATIENT", directoryRecord::patient},
        {L"STUDY", directoryRecord::study},
        {L"SERIES", directoryRecord::series},
        {L"IMAGE", directoryRecord::image},
        {L"OVERLAY", directoryRecord::overlay},
        {L"MODALITY LUT", directoryRecord::modality_lut},
        {L"VOI LUT", directoryRecord::voi_lut},
        {L"CURVE", directoryRecord::curve},
        {L"TOPIC", directoryRecord::topic},
        {L"VISIT", directoryRecord::visit},
        {L"RESULTS", directoryRecord::results},
        {L"INTERPRETATION", directoryRecord::interpretation},
        {L"STUDY COMPONENT", directoryRecord::study_component},
        {L"STORED PRINT", directoryRecord::stored_print},
        {L"RT DOSE", directoryRecord::rt_dose},
        {L"RT STRUCTURE SET", directoryRecord::rt_structure_set},
        {L"RT PLAN", directoryRecord::rt_plan},
        {L"RT TREAT RECORD", directoryRecord::rt_treat_record},
        {L"PRESENTATION", directoryRecord::presentation},
        {L"WAVEFORM", directoryRecord::waveform},
        {L"SR DOCUMENT", directoryRecord::sr_document},
        {L"KEY OBJECT DOC", directoryRecord::key_object_doc},
        {L"SPECTROSCOPY", directoryRecord::spectroscopy},
        {L"RAW DATA", directoryRecord::raw_data},
        {L"REGISTRATION", directoryRecord::registration},
        {L"FIDUCIAL", directoryRecord::fiducial},
        {L"MRDR", directoryRecord::mrdr},
        {L"", directoryRecord::endOfDirectoryRecordTypes}
    };

    return typesList;
}



///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
//
// dicomDir class
//
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Constructor
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
dicomDir::dicomDir(std::shared_ptr<dataSet> pDataSet):
	m_pDataSet(pDataSet)
{
    if(m_pDataSet.get() == 0)
	{
        m_pDataSet = std::make_shared<dataSet>();
	}

	// Get the DICOMDIR sequence
	///////////////////////////////////////////////////////////
	typedef std::map<std::uint32_t, std::shared_ptr<directoryRecord> > tOffsetsToRecords;
	tOffsetsToRecords offsetsToRecords;
	for(std::uint32_t scanItems(0); ; ++scanItems)
	{
		std::shared_ptr<dataSet> pDataSet(m_pDataSet->getSequenceItem(0x0004, 0, 0x1220, scanItems));
		if(pDataSet == 0)
		{
			break;
		}
		std::shared_ptr<directoryRecord> newRecord(new directoryRecord(pDataSet));
		offsetsToRecords[pDataSet->getItemOffset()] = newRecord;
		m_recordsList.push_back(newRecord);
	}

	// Scan all the records and update the pointers
	///////////////////////////////////////////////////////////
	for(tOffsetsToRecords::iterator scanRecords(offsetsToRecords.begin()); scanRecords != offsetsToRecords.end(); ++scanRecords)
	{
        std::uint32_t nextRecordOffset(scanRecords->second->getRecordDataSet()->getUnsignedLong(0x0004, 0, 0x1400, 0, 0));
        std::uint32_t childRecordOffset(scanRecords->second->getRecordDataSet()->getUnsignedLong(0x0004, 0, 0x1420, 0, 0));
        std::uint32_t referencedRecordOffset(scanRecords->second->getRecordDataSet()->getUnsignedLong(0x0004, 0, 0x1504, 0, 0));

		tOffsetsToRecords::iterator findNextRecord(offsetsToRecords.find(nextRecordOffset));
		if(findNextRecord != offsetsToRecords.end())
		{
			scanRecords->second->setNextRecord(findNextRecord->second);
		}

		tOffsetsToRecords::iterator findChildRecord(offsetsToRecords.find(childRecordOffset));
		if(findChildRecord != offsetsToRecords.end())
		{
			scanRecords->second->setFirstChildRecord(findChildRecord->second);
		}

		tOffsetsToRecords::iterator findReferencedRecord(offsetsToRecords.find(referencedRecordOffset));
		if(findReferencedRecord != offsetsToRecords.end())
		{
			scanRecords->second->setReferencedRecord(findReferencedRecord->second);
		}
	}

	// Get the position of the first record
	///////////////////////////////////////////////////////////
    tOffsetsToRecords::iterator findRecord(offsetsToRecords.find(m_pDataSet->getUnsignedLong(0x0004, 0, 0x1200, 0, 0)));
	if(findRecord == offsetsToRecords.end())
	{
		return;
	}
	setFirstRootRecord(findRecord->second);
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Destructor, make sure that the records are released
//  after the root record.
// This resolves a stack overflow when a large number
//  sibling records is present
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
dicomDir::~dicomDir()
{
    m_pFirstRootRecord.reset();
	m_recordsList.clear();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Returns the dataSet
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::shared_ptr<dataSet> dicomDir::getDirectoryDataSet() const
{
	return m_pDataSet;
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Returns a new record that can be inserted in the
//  folder
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::shared_ptr<directoryRecord> dicomDir::getNewRecord()
{
    std::shared_ptr<data> recordsTag(m_pDataSet->getTagCreate(0x0004, 0, 0x1220));
    std::shared_ptr<dataSet> recordDataSet = std::make_shared<dataSet>();
	recordsTag->appendDataSet(recordDataSet);

	std::shared_ptr<directoryRecord> newRecord(new directoryRecord(recordDataSet));
	m_recordsList.push_back(newRecord);

	return newRecord;
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Build the a dicom dataset that contain the directory's
//  information.
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::shared_ptr<dataSet> dicomDir::buildDataSet()
{
	// Adjust the transfer syntax if it isn't already set
	///////////////////////////////////////////////////////////
    if(m_pDataSet->getString(0x2, 0, 0x10, 0, 0) == "")
	{
        m_pDataSet->setString(0x2, 0, 0x10, 0, 0, "1.2.840.10008.1.2.1");
	}

	// Adjust the version if it isn't already set
    ///////////////////////////////////////////////////////////
    {
        std::shared_ptr<handlers::writingDataHandlerRaw> versionHandler(m_pDataSet->getWritingDataHandlerRaw(0x2, 0, 0x1, 0, "OB"));
        versionHandler->setSize(2);
        versionHandler->setUnsignedLong(0, 0);
        versionHandler->setUnsignedLong(1, 1);
    }

	// Adjust the SOP class UID if it isn't already set
	///////////////////////////////////////////////////////////
    m_pDataSet->setString(0x2, 0, 0x2, 0, 0, "1.2.840.10008.1.3.10");

	// Allocate offset fields
	///////////////////////////////////////////////////////////
	if(m_pFirstRootRecord != 0)
	{
		m_pFirstRootRecord->updateOffsets();
	}
    m_pDataSet->setUnsignedLong(0x0004, 0, 0x1200, 0, 0, 0);


	// Save to a null stream in order to update the offsets
	///////////////////////////////////////////////////////////
    std::shared_ptr<nullStreamWriter> saveStream(new nullStreamWriter);
	std::shared_ptr<streamWriter> writer(new streamWriter(saveStream));
	std::shared_ptr<codecs::dicomCodec> writerCodec(new codecs::dicomCodec);
	writerCodec->write(writer, m_pDataSet);

	// Scan all the records and update the pointers
	///////////////////////////////////////////////////////////
	if(m_pFirstRootRecord != 0)
	{
		m_pFirstRootRecord->updateOffsets();
        m_pDataSet->setUnsignedLong(0x0004, 0, 0x1200, 0, 0, m_pFirstRootRecord->getRecordDataSet()->getItemOffset());
	}

	return m_pDataSet;

}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Returns the first root record
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::shared_ptr<directoryRecord> dicomDir::getFirstRootRecord() const
{
	return m_pFirstRootRecord;
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Set the first root record
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void dicomDir::setFirstRootRecord(std::shared_ptr<directoryRecord> pFirstRootRecord)
{
	m_pFirstRootRecord = pFirstRootRecord;
}



} // namespace imebra

} // namespace puntoexe
