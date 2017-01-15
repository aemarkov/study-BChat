#pragma once

#include <qobject.h>
#include "Containers/ChatMessageContainer.h"

using namespace Containers;

class QStringToContainerConverter : public QObject
{
	Q_OBJECT

public:

	QStringToContainerConverter();
	~QStringToContainerConverter();

public slots:
	void MessageInput(QString);
	
signals:
	void DataOutput(const Containers::ChatMessageContainer*);

private:
	ChatMessageContainer _container;

};
