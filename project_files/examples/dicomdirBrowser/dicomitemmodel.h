#ifndef DICOMITEMMODEL_H
#define DICOMITEMMODEL_H

#include <QAbstractItemModel>
#include "../../library/imebra/include/dicomDir.h"

using namespace puntoexe;

class DicomItemModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit DicomItemModel(QObject *parent = 0);

	enum tDicomRole
	{
		dicomFileName = Qt::UserRole

	};

	virtual int columnCount ( const QModelIndex & parent = QModelIndex() ) const;
	virtual QVariant	data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
	virtual QModelIndex	index ( int row, int column, const QModelIndex & parent = QModelIndex() ) const;
	virtual QModelIndex	parent ( const QModelIndex & index ) const;
	virtual int	rowCount ( const QModelIndex & parent = QModelIndex() ) const;

signals:

public slots:
	void load(const QString& fileName);
	void load();

private:
	// Counts the number of sibling records
	int GetRows(puntoexe::ptr<puntoexe::imebra::directoryRecord> pFirstRecord) const;

	ptr<imebra::directoryRecord> GetSibling(ptr<imebra::directoryRecord> pFirstSiblingRecord, int siblingRecordCount) const;

	ptr<imebra::directoryRecord> GetModelIndexRecord(const QModelIndex& index) const;

	static bool GetColumnTag(imebra::directoryRecord::tDirectoryRecordType recordType, int column, imbxUint16* pGroup, imbxUint16* pTag, imbxUint32* pBufferId);

	ptr<imebra::dicomDir> m_pDicomDir;

	QString m_rootFolder;

	typedef std::map<void*, QModelIndex > tParents;
	mutable tParents m_parents;

};

#endif // DICOMITEMMODEL_H
