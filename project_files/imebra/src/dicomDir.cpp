/*
$fileHeader$
*/

/*! \file dataSet.cpp
    \brief Implementation of the class dataSet.

*/

#include "../include/dicomDir.h"
#include "../include/dataSet.h"
#include "../include/dicomCodec.h"
#include "../include/transaction.h"
#include "../../base/include/nullStream.h"
#include "../../base/include/streamWriter.h"
#include <map>
#include <string>

namespace puntoexe
{

namespace imebra
{

	struct tDirectoryRecordTypeDef
	{
		std::wstring m_name;
		directoryRecord::tDirectoryRecordType m_type;
	};
	
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


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Constructor
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
directoryRecord::directoryRecord(ptr<dataSet> pDataSet):
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
ptr<dataSet> directoryRecord::getRecordDataSet()
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
ptr<directoryRecord> directoryRecord::getNextRecord()
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
ptr<directoryRecord> directoryRecord::getFirstChildRecord()
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
ptr<directoryRecord> directoryRecord::getReferencedRecord()
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
void directoryRecord::setNextRecord(ptr<directoryRecord> pNextRecord)
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
void directoryRecord::setFirstChildRecord(ptr<directoryRecord> pFirstChildRecord)
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
void directoryRecord::setReferencedRecord(ptr<directoryRecord> pReferencedRecord)
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
std::wstring directoryRecord::getFilePart(imbxUint32 part)
{
	return getRecordDataSet()->getUnicodeString(0x0004, 0, 0x1500, part);
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
directoryRecord::tDirectoryRecordType directoryRecord::getType()
{
	std::wstring typeString(getTypeString());

	for(size_t scanTypes(0); typesList[scanTypes].m_type != endOfDirectoryRecordTypes; ++scanTypes)
	{
		if(typesList[scanTypes].m_name == typeString)
		{
			return typesList[scanTypes].m_type;
		}
	}

	throw dicomDirUnknownDirectoryRecordType("Unknown directory record type");
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
std::wstring directoryRecord::getTypeString()
{
	return getRecordDataSet()->getUnicodeString(0x0004, 0, 0x1430, 0);
}


void directoryRecord::setType(tDirectoryRecordType recordType)
{
	for(size_t scanTypes(0); typesList[scanTypes].m_type != endOfDirectoryRecordTypes; ++scanTypes)
	{
		if(typesList[scanTypes].m_type == recordType)
		{
			getRecordDataSet()->setUnicodeString(0x0004, 0, 0x1430, 0, typesList[scanTypes].m_name);
			return;
		}
	}

	throw dicomDirUnknownDirectoryRecordType("Unknown directory record type");
}


void directoryRecord::setTypeString(std::wstring recordType)
{
	getRecordDataSet()->setUnicodeString(0x0004, 0, 0x1430, 0, recordType);
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
	if(m_pNextRecord == 0)
	{
		getRecordDataSet()->setUnsignedLong(0x0004, 0, 0x1400, 0, 0);
	}
	else
	{
		getRecordDataSet()->setUnsignedLong(0x0004, 0, 0x1400, 0, m_pNextRecord->getRecordDataSet()->getItemOffset());
		m_pNextRecord->updateOffsets();
	}

	if(m_pFirstChildRecord == 0)
	{
		getRecordDataSet()->setUnsignedLong(0x0004, 0, 0x1420, 0, 0);
	}
	else
	{
		getRecordDataSet()->setUnsignedLong(0x0004, 0, 0x1420, 0, m_pFirstChildRecord->getRecordDataSet()->getItemOffset());
		m_pFirstChildRecord->updateOffsets();
	}

	if(m_pReferencedRecord == 0)
	{
		getRecordDataSet()->setUnsignedLong(0x0004, 0, 0x1504, 0, 0);
	}
	else
	{
		getRecordDataSet()->setUnsignedLong(0x0004, 0, 0x1504, 0, m_pReferencedRecord->getRecordDataSet()->getItemOffset());
		m_pReferencedRecord->updateOffsets();
	}

}


void directoryRecord::checkCircularReference(directoryRecord* pStartRecord)
{
	if(this == pStartRecord)
	{
		throw dicomDirCircularReferenceException("Circular reference detected");
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


dicomDir::dicomDir(ptr<dataSet> pDataSet):
	m_pDataSet(pDataSet)
{
	if(m_pDataSet == 0)
	{
		m_pDataSet =new dataSet;
	}

	// Parse the dataset
	lockObject lockDataSet(pDataSet);

	// Get the DICOMDIR sequence
	typedef std::map<imbxUint32, ptr<directoryRecord> > tOffsetsToRecords;
	tOffsetsToRecords offsetsToRecords;
	for(imbxUint32 scanItems(0); ; ++scanItems)
	{
		ptr<dataSet> pDataSet(m_pDataSet->getSequenceItem(0x0004, 0, 0x1220, scanItems));
		if(pDataSet == 0)
		{
			break;
		}
		offsetsToRecords[pDataSet->getItemOffset()] = new directoryRecord(pDataSet);
	}

	// Scan all the records and update the pointers
	for(tOffsetsToRecords::iterator scanRecords(offsetsToRecords.begin()); scanRecords != offsetsToRecords.end(); ++scanRecords)
	{
		imbxUint32 nextRecordOffset(scanRecords->second->getRecordDataSet()->getUnsignedLong(0x0004, 0, 0x1400, 0));
		imbxUint32 childRecordOffset(scanRecords->second->getRecordDataSet()->getUnsignedLong(0x0004, 0, 0x1420, 0));
		imbxUint32 referencedRecordOffset(scanRecords->second->getRecordDataSet()->getUnsignedLong(0x0004, 0, 0x1504, 0));

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
	tOffsetsToRecords::iterator findRecord(offsetsToRecords.find(m_pDataSet->getUnsignedLong(0x0004, 0, 0x1200, 0)));
	if(findRecord == offsetsToRecords.end())
	{
		return;
	}
	setFirstRootRecord(findRecord->second);
}


ptr<dataSet> dicomDir::getDirectoryDataSet()
{
	return m_pDataSet;
}


ptr<directoryRecord> dicomDir::getNewRecord()
{
	ptr<data> recordsTag(m_pDataSet->getTag(0x0004, 0, 0x1220, true));
	ptr<dataSet> recordDataSet(new dataSet);
	recordsTag->appendDataSet(recordDataSet);

	return new directoryRecord(recordDataSet);
}


bool dicomDir::preDelete()
{
	// Adjust the transfer syntax if it isn't already set
	if(m_pDataSet->getString(2, 0, 16, 0) == "")
	{
		m_pDataSet->setString(2, 0, 16, 0, "1.2.840.10008.1.2.1");
	}

	// Allocate offset fields
	if(m_pFirstRootRecord != 0)
	{
		m_pFirstRootRecord->updateOffsets();
	}
	m_pDataSet->setUnsignedLong(0x0004, 0, 0x1200, 0, 0);


	// Save to a null stream in order to update the offsets
	ptr<nullStream> saveStream(new nullStream);
	ptr<streamWriter> writer(new streamWriter(saveStream));
	ptr<codecs::dicomCodec> writerCodec(new codecs::dicomCodec);
	writerCodec->write(writer, m_pDataSet);

	// Scan all the records and update the pointers
	if(m_pFirstRootRecord != 0)
	{
		m_pFirstRootRecord->updateOffsets();
		m_pDataSet->setUnsignedLong(0x0004, 0, 0x1200, 0, m_pFirstRootRecord->getRecordDataSet()->getItemOffset());
	}

	return true;

}


ptr<directoryRecord> dicomDir::getFirstRootRecord()
{
	return m_pFirstRootRecord;
}


void dicomDir::setFirstRootRecord(ptr<directoryRecord> pFirstRootRecord)
{
	m_pFirstRootRecord = pFirstRootRecord;
}



} // namespace imebra

} // namespace puntoexe
