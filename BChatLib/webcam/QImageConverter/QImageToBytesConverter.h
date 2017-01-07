#ifndef __QIMAGETOBYTESCONVERTER_H__
#define __QIMAGETOBYTESCONVERTER_H__

#include <qimage.h>
#include <qobject.h>

class QImageToBytesConverter : public QObject
{
	Q_OBJECT

public slots:
	void FrameInput(QImage&);

signals:
	void DataOutput(uint8_t* data, uint32_t size);
};

#endif
