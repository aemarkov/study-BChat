#ifndef __BYTESTOQIMAGECONVERTER_H__
#define __BYTESTOQIMAGECONVERTER_H__

#include <qobject.h>
#include <qimage.h>
#include "Containers\VideoFrameContainer.h"

namespace Webcam
{

	class ContainerToQImageConverter : public QObject
	{
		Q_OBJECT

	public:

		public slots :
			void DataInput(const Containers::VideoFrameContainer &);

	signals:
		void FrameOutput(QImage&);
	};
}

#endif