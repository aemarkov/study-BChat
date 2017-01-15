#include "QStringToContainerConverter.h"

QStringToContainerConverter::QStringToContainerConverter()
{
}

QStringToContainerConverter::~QStringToContainerConverter()
{
}

void QStringToContainerConverter::MessageInput(QString string)
{
	_container.SetMessage(string);
	emit DataOutput(&_container);
}
