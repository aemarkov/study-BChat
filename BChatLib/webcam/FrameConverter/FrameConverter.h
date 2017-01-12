#ifndef FRAMECONVERTER_H
#define FRAMECONVERTER_H

#include <QObject>
#include <QImage>
#include <QVideoFrame>

namespace Webcam
{

	/*!
	 * \brief Преобразует QVideoFrame в QImage
	 *
	 * Преобразует QVideoFrame в QImage. Конвертирует кадры
	 * в заданный формат.
	 */
	class FrameConverter :public QObject
	{
		Q_OBJECT

	public:
		/*!
		 * \brief FrameConverter Создает новый экземпляр FrameConverter,
		 *        который конвертирует кадры в Format_RGB30
		 */
		FrameConverter();

		/*!
		 * \brief FrameConverter Создает новый экземпляр FrameConverter,
		 *        который конвертирует кадры в заданный формат
		 * \param format выходной формат
		 */
		FrameConverter(QImage::Format format);

		public slots:
		/*!
		 * \brief Получение исходного кадра в формате QVideoFrame
		 * \param frame
		 */
		void FrameInput(const QVideoFrame& frame);
	signals:

		/*!
		 * \brief Отправка конвертированного кадра в формате QImage
		 * \param image
		 */
		void FrameOutput(QImage& image);

	private:

		QImage::Format _targetFormat;

	};
}

#endif // FRAMECONVERTER_H
