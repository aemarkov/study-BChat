#pragma once

#include <QObject>

class ICrypt : public QObject
{
	Q_OBJECT
		
public:

public slots:
	
	virtual void EncryptSlot(uint8_t* data, uint32_t size) = 0;
	virtual void DecryptSlot(uint8_t* data, uint32_t size) = 0;

signals:
	void DecryptSignal(uint8_t* data, uint32_t size);
	void EncryptSignal(uint8_t* data, uint32_t size);
};
