#include "FrameConverter.h"

FrameConverter::FrameConverter()
{
    _targetFormat = QImage::Format_RGB30;
}

FrameConverter::FrameConverter(QImage::Format format)
{
    _targetFormat = format;
}

void FrameConverter::FrameInput(const QVideoFrame &frame)
{
    //Преобразовываем QVideoFrame в QImage
    QVideoFrame cloneFrame(frame);
    cloneFrame.map(QAbstractVideoBuffer::ReadOnly);

    QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(frame.pixelFormat());
    QImage image;

    if(imageFormat!=QImage::Format_Invalid)
    {
        image = QImage(cloneFrame.bits(),
                        cloneFrame.width(),
                        cloneFrame.height(),
                        imageFormat);
    }
    else
    {
        int nBytes = cloneFrame.mappedBytes();
        image = QImage::fromData(cloneFrame.bits(), nBytes);
    }


     /* Исходное изображение в RGB32, но неизвестно, так у всех камер
      * или нет.
      * Этот формат вызывает падение (сегфолт). Чтобы работало коррктно, надо
      * сконвертировать в что-нибудь еще:
      *  - Format_RGB444 - работает, но мало цветов
      *  - Format_RGB16 - нормально
      *  - Format_RGB30 - нормально
      */

    QImage imageConverted = image.convertToFormat(_targetFormat);
    emit FrameOutput(imageConverted);

    cloneFrame.unmap();
}
