#include "controller.h"
#include "dicomitemmodel.h"

#include "../../library/imebra/include/codecFactory.h"
#include "../../library/base/include/stream.h"

Controller::Controller(QObject *parent) :
    QObject(parent)
{
}

void Controller::itemSelected(const QModelIndex& index)
{
	QString fileName = index.data(DicomItemModel::dicomFileName).toString();
	if(fileName.isEmpty())
	{
		return;
	}

	puntoexe::ptr<puntoexe::stream> dicomStream(new puntoexe::stream);
	dicomStream->openFile(fileName.toStdWString(), std::ios_base::in);
	puntoexe::ptr<puntoexe::streamReader> streamReader(new puntoexe::streamReader(dicomStream));
	puntoexe::ptr<imebra::dataSet> dataSet(imebra::codecs::codecFactory::getCodecFactory()->load(dicomStream));
	puntoexe::ptr<imebra::image> image(dataSet->getImage(0));
}
