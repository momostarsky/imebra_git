#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QGraphicsScene>
#include <QModelIndex>
#include "../../library/base/include/thread.h"

class ParallelLoad: public puntoexe::thread, QObject
{
	Q_OBJECT

public:
	virtual void threadFunction();

};


class Controller : public QObject
{
	Q_OBJECT
public:
	explicit Controller(QObject *parent = 0);
	
signals:
	
public slots:
	void itemSelected(const QModelIndex& index);

protected:
	QGraphicsScene m_graphicsScene;
	
};



#endif // CONTROLLER_H
