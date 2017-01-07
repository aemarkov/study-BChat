#ifndef __BYTESTOQIMAGECONVERTER_H__
#define __BYTESTOQIMAGECONVERTER_H__

#include <qobject.h>
#include <qimage.h>

class BytesToQImageConverter: public QObject
{
	Q_OBJECT

public:

public slots:
	void DataInput(uint8_t* data, uint32_t size);

signals:
	void FrameOutput(QImage& image);
};

#endif