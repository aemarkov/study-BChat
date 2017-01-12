#ifndef __QIMAGETOBYTESCONVERTER_H__
#define __QIMAGETOBYTESCONVERTER_H__

#include <qimage.h>
#include <qobject.h>
#include "common\Exceptions.h"
#include "Containers\VideoFrameContainer.h"


namespace Webcam
{

	/*!
	 * \brief Конвертирует QImage в массив байт
	 *
	 * Массив байт выделяется при первом вызове функции конвертации, и
	 * затем просто изображение QImage каждый раз копируется в него
	 */
	class QImageToContainerConverter : public QObject
	{
		Q_OBJECT

	public:
		QImageToContainerConverter();
		~QImageToContainerConverter();

	public slots:
		void FrameInput(QImage&);

	signals:
		void DataOutput(const Containers::VideoFrameContainer *);

	private:
		Containers::VideoFrameContainer _container;
	};

}
#endif
