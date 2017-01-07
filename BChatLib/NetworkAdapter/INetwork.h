#pragma once

#include <QObject>

class INetwork : public QObject
{
	Q_OBJECT

public:

public slots :
	virtual void SendSlot(uint8_t* data, uint32_t size);

signals:
	void RecvSignal(uint8_t* data, uint32_t size);	
};
