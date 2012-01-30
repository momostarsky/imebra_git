#include "dicomitemmodel.h"

#include "../../library/imebra/include/dicomDict.h"
#include "../../library/imebra/include/dataSet.h"
#include "../../library/imebra/include/dataHandler.h"
#include "../../library/imebra/include/codecFactory.h"
#include "../../library/base/include/streamReader.h"
#include "../../library/base/include/stream.h"

#include <QDate>
#include <QTime>
#include <QDateTime>
#include <QFileDialog>
#include <QDir>

DicomItemModel::DicomItemModel(QObject *parent) :
    QAbstractItemModel(parent)
{
}

int DicomItemModel::columnCount ( const QModelIndex & parent) const
{
	return 1;
	ptr<imebra::directoryRecord> pRecord( GetModelIndexRecord(parent) );

	ptr<imebra::directoryRecord> pFirstChild;
	if(pRecord != 0)
	{
		pFirstChild = pRecord->getFirstChildRecord();
	}
	else if(m_pDicomDir != 0)
	{
		pFirstChild = m_pDicomDir->getFirstRootRecord();
	}

	int numColumns(0);
	int numRows(GetRows(pFirstChild));
	for(int row(0); row != numRows; ++row)
	{
		for(int column(0); /* check in the loop */; ++column)
		{
			if(data(index(row, column, parent), Qt::WhatsThisRole).isNull())
			{
				if(column > numColumns)
				{
					numColumns = column;
				}
				break;
			}
		}
	}
	return numColumns;
}

QVariant DicomItemModel::data ( const QModelIndex & index, int role ) const
{
	ptr<imebra::directoryRecord> pRecord( GetModelIndexRecord(index) );
	if(pRecord == 0)
	{
		return QVariant();
	}

	ptr<imebra::dataSet> pDataSet( pRecord->getRecordDataSet() );

	imbxUint16 group(0), tag(0);
	imbxUint32 bufferId(0);

	QString returnValue;
	imbxInt32 year(0), month(0), day(0), hour(0), minutes(0), seconds(0), nanoseconds(0), offsetHours(0), offsetMinutes(0);
	try
	{
		for(int column(0); GetColumnTag(pRecord->getType(), column, &group, &tag, &bufferId); ++column )
		{
			ptr<imebra::handlers::dataHandler> pHandler(pDataSet->getDataHandler(group, 0, tag, bufferId, false));
			if(pHandler == 0)
			{
				break;
			}

			switch(role)
			{
			case Qt::DisplayRole:
			{
				std::string dataType( pHandler->getDataType() );

				// Handle date and time
				if(dataType == "DA")
				{
					pHandler->getDate(0, &year, &month, &day, &hour, &minutes, &seconds, &nanoseconds, &offsetHours, &offsetMinutes);
					QDate returnDate(year, month, day);
					returnValue += returnDate.toString();
				}
				else if(dataType == "DT")
				{
					pHandler->getDate(0, &year, &month, &day, &hour, &minutes, &seconds, &nanoseconds, &offsetHours, &offsetMinutes);
					QDateTime returnDateTime(QDate(year, month, day), QTime(hour, minutes, seconds, nanoseconds / 1000), Qt::LocalTime);
					returnValue += returnDateTime.toString();
				}
				else if(dataType == "TM")
				{
					pHandler->getDate(0, &year, &month, &day, &hour, &minutes, &seconds, &nanoseconds, &offsetHours, &offsetMinutes);
					QTime returnTime(hour, minutes, seconds, nanoseconds / 1000);
					returnValue += returnTime.toString();
				}
				else
				{
					returnValue += QString::fromStdWString(pHandler->getUnicodeString(0));
				}

				break;
			}

			case Qt::WhatsThisRole:
			case Qt::ToolTipRole:
				returnValue += QString::fromStdWString(imebra::dicomDictionary::getDicomDictionary()->getTagName(group, tag));
				break;
			default:
				return QVariant();

			}
			if(!returnValue.isEmpty() && returnValue.trimmed().right(1) != "/")
			{
				returnValue.push_back(" / ");
			}
		}
	}
	catch(const imebra::dicomDirUnknownDirectoryRecordType& )
	{
		return QVariant();
	}

	QString trimmedValue(returnValue.trimmed());
	if(trimmedValue.right(1) == "/")
	{
		trimmedValue.resize(trimmedValue.size() - 1);
	}

	return trimmedValue.trimmed();
}

QModelIndex	DicomItemModel::index ( int row, int column, const QModelIndex & parent ) const
{
	ptr<imebra::directoryRecord> pFirstSibling(m_pDicomDir->getFirstRootRecord());
	if(parent.isValid())
	{
		ptr<imebra::directoryRecord> pParentRecord(GetModelIndexRecord(parent));
		if(pParentRecord == 0)
		{
			return QModelIndex();
		}
		pFirstSibling = pParentRecord->getFirstChildRecord();
	}

	ptr<imebra::directoryRecord> pSibling(GetSibling(pFirstSibling, row));

	if (pSibling == 0)
	{
		return QModelIndex();
	}

	m_parents[pSibling.get()] = parent;

	return createIndex(row, column, pSibling.get());
}

QModelIndex	DicomItemModel::parent ( const QModelIndex & index ) const
{
	tParents::const_iterator findParent(m_parents.find(index.internalPointer()));
	if(findParent == m_parents.end())
	{
		return QModelIndex();
	}
	return findParent->second;
}


int	DicomItemModel::rowCount ( const QModelIndex & parent ) const
{
	ptr<imebra::directoryRecord> pRecord( GetModelIndexRecord(parent) );
	if(pRecord != 0)
	{
		return GetRows(pRecord->getFirstChildRecord());
	}
	if(m_pDicomDir != 0)
	{
		return GetRows(m_pDicomDir->getFirstRootRecord());
	}
	return 0;

}


int DicomItemModel::GetRows(puntoexe::ptr<puntoexe::imebra::directoryRecord> pFirstRecord) const
{
	int numRows(0);
	ptr<imebra::directoryRecord> pNextRecord;
	for(/* uses numRows initialized before */; pFirstRecord != 0; ++numRows)
	{
		pNextRecord = pFirstRecord->getNextRecord();
		pFirstRecord = pNextRecord;
	}

	return numRows;
}

ptr<imebra::directoryRecord> DicomItemModel::GetSibling(ptr<imebra::directoryRecord> pFirstSiblingRecord, int siblingRecordCount) const
{
	ptr<imebra::directoryRecord> pNextRecord;
	while(siblingRecordCount-- != 0 && pFirstSiblingRecord != 0)
	{
		pNextRecord = pFirstSiblingRecord->getNextRecord();
		pFirstSiblingRecord = pNextRecord;
	}
	return pFirstSiblingRecord;
}

ptr<imebra::directoryRecord> DicomItemModel::GetModelIndexRecord(const QModelIndex& index) const
{
	ptr<imebra::directoryRecord> pRecord( (imebra::directoryRecord*) index.internalPointer() );
	return pRecord;
}

bool DicomItemModel::GetColumnTag(imebra::directoryRecord::tDirectoryRecordType recordType, int column, imbxUint16* pGroup, imbxUint16* pTag, imbxUint32* pBufferId)
{
	static const imbxUint16 tags[]={
		(imbxUint16)imebra::directoryRecord::patient, 0x0010, 0x0010, 0x0000, 0x0,
		(imbxUint16)imebra::directoryRecord::study,   0x0008, 0x0020, 0x0000, 0x0008, 0x0030, 0x0000, 0x0008, 0x1030, 0x0000, 0x0,
		(imbxUint16)imebra::directoryRecord::series,  0x0008, 0x0060, 0x0000, 0x0020, 0x000e, 0x0000, 0x0020, 0x0011, 0x0000, 0x0,
		(imbxUint16)imebra::directoryRecord::image,   0x0020, 0x0013, 0x0000, 0x0,
		(imbxUint16)imebra::directoryRecord::rt_dose, 0x0020, 0x0013, 0x0000, 0x3004, 0x000a, 0x0000, 0x3004, 0x0006, 0x0000, 0x0,
		(imbxUint16)imebra::directoryRecord::rt_structure_set, 0x0020, 0x0013, 0x0000, 0x3006, 0x0002, 0x0000, 0x3006, 0x0008, 0x0000, 0x3006, 0x0009, 0x0000, 0x0,
		(imbxUint16)imebra::directoryRecord::rt_plan,          0x0020, 0x0013, 0x0000, 0x300a, 0x0002, 0x0000, 0x300a, 0x0006, 0x0000, 0x300a, 0x0007, 0x0000, 0x0,
		(imbxUint16)imebra::directoryRecord::rt_treat_record,  0x0020, 0x0013, 0x0000, 0x3008, 0x0250, 0x0000, 0x3008, 0x0251, 0x0000, 0x0,
		0xffff
	};
	*pGroup = *pTag = 0;
	*pBufferId = 0;

	for(const imbxUint16* pScanRecords(tags); /* in the loop */; ++pScanRecords)
	{
		if(*pScanRecords == 0xffff)
		{
			return false;
		}
		imebra::directoryRecord::tDirectoryRecordType type = (imebra::directoryRecord::tDirectoryRecordType)*pScanRecords;
		int scanColumn(0);
		while(*(++pScanRecords) != 0)
		{
			*pGroup = *pScanRecords;
			*pTag = *(++pScanRecords);
			*pBufferId = *(++pScanRecords);
			if(scanColumn ++ == column && recordType == type)
			{
				return true;
			}
		}
	}

	return false;
}


void DicomItemModel::load(const QString &fileName)
{
	ptr<puntoexe::stream> pStream(new puntoexe::stream);
	pStream->openFile(QDir::toNativeSeparators(fileName).toStdWString(), std::ios_base::in);
	ptr<puntoexe::streamReader> pStreamReader(new puntoexe::streamReader(pStream));
	m_pDicomDir = new imebra::dicomDir( imebra::codecs::codecFactory::getCodecFactory()->load(pStreamReader) );
	m_parents.clear();

	reset();
	int numRows(GetRows(m_pDicomDir->getFirstRootRecord()));
	if(numRows > 0)
	{
		dataChanged(index(0, 0), index(numRows - 1, 0));
	}
}

void DicomItemModel::load()
{
	QString fileName ( QFileDialog::getOpenFileName(0, tr("Select a DICOMDIR file"), QString(), "DICOMDIR (DICOMDIR., dicomdir., Dicomdir.)") );
	if(!fileName.isEmpty())
	{
		load(fileName);
	}
}


TagsItemModel::TagsItemModel(QObject* pParent): QAbstractTableModel(pParent), m_cols(0)
{
}

int TagsItemModel::columnCount ( const QModelIndex &  parent /* = QModelIndex() */) const
{
	if(parent.isValid())
	{
		return 0;
	}
	return m_cols;
}

QVariant TagsItemModel::data ( const QModelIndex & index, int role /* = Qt::DisplayRole */ ) const
{
	if(!index.isValid())
	{
		return QVariant();
	}

	// Find the group and tag id
	imbxUint32 groupAndTagId(0);
	;
	int row(index.row());
	for(tValues::const_iterator scanIds(m_values.begin()); scanIds != m_values.end(); ++scanIds, --row)
	{
		if(row != 0)
		{
			continue;
		}

		groupAndTagId = scanIds->first;
		if(groupAndTagId == 0)
		{
			return QVariant();
		}

		imbxUint16 group( (imbxUint16)(groupAndTagId >> 16) );
		imbxUint16 tag( (imbxUint16)(groupAndTagId & 0x0000ffff));


		switch(role)
		{
		case Qt::DisplayRole:
			return QVariant();

		case Qt::WhatsThisRole:
		case Qt::ToolTipRole:
			return QVariant( QString::fromStdWString(imebra::dicomDictionary::getDicomDictionary()->getTagName(group, tag)) );
			break;
		default:
			return QVariant();

		}
	}

	return QVariant();


}


int	TagsItemModel::rowCount ( const QModelIndex & parent /* = QModelIndex() */) const
{
	if(parent.isValid())
	{
		return 0;
	}
	return m_values.size();
}

void TagsItemModel::setDataSet(ptr<imebra::dataSet> pDataSet)
{
	m_pDataSet = pDataSet;

	m_cols = 0;
	m_values.clear();
	if(m_pDataSet != 0)
	{
		ptr<imebra::dataCollectionIterator<imebra::dataGroup> > pGroupIterator(m_pDataSet->getDataIterator());

		imbxInt32 year(0), month(0), day(0), hour(0), minutes(0), seconds(0), nanoseconds(0), offsetHours(0), offsetMinutes(0);

		for(pGroupIterator->reset(); pGroupIterator->isValid(); pGroupIterator->incIterator())
		{
			ptr<imebra::dataGroup> pGroup(pGroupIterator->getData());
			ptr<imebra::dataCollectionIterator<imebra::data> > pTagIterator(pGroup->getDataIterator());
			for(pTagIterator->reset(); pTagIterator->isValid(); pTagIterator->incIterator())
			{
				if(pTagIterator->getId() == 0)
				{
					continue;
				}
				ptr<imebra::data> pTag(pTagIterator->getData());
				ptr<imebra::handlers::dataHandler> pHandler(pTag->getDataHandler(0, false, "OB"));

				std::string dataType(pHandler->getDataType());

				QString value;

				for(imbxUint32 scanTag(0); pHandler->pointerIsValid(scanTag); ++scanTag)
				{

					// Handle date and time
					if(dataType == "DA")
					{
						pHandler->getDate(scanTag, &year, &month, &day, &hour, &minutes, &seconds, &nanoseconds, &offsetHours, &offsetMinutes);
						QDate returnDate(year, month, day);
						value = returnDate.toString();
					}
					else if(dataType == "DT")
					{
						pHandler->getDate(scanTag, &year, &month, &day, &hour, &minutes, &seconds, &nanoseconds, &offsetHours, &offsetMinutes);
						QDateTime returnDateTime(QDate(year, month, day), QTime(hour, minutes, seconds, nanoseconds / 1000), Qt::LocalTime);
						value = returnDateTime.toString();
					}
					else if(dataType == "TM")
					{
						pHandler->getDate(scanTag, &year, &month, &day, &hour, &minutes, &seconds, &nanoseconds, &offsetHours, &offsetMinutes);
						QTime returnTime(hour, minutes, seconds, nanoseconds / 1000);
						value = returnTime.toString();
					}
					else
					{
						value = QString::fromStdWString(pHandler->getUnicodeString(scanTag));
					}

					if(scanTag >= m_cols)
					{
						m_cols = scanTag + 1;
					}

					m_values[( ((imbxUint32)pGroupIterator->getId()) << 16) | pTagIterator->getId()].push_back(value);
				}

			}
		}

	}

	reset();
	if(m_cols > 0 && m_values.size() > 0)
	{
		dataChanged(index(0, 0), index(m_values.size() - 1, m_cols - 1));
	}

}

