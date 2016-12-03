#include "videoviewer.h"

VideoViewer::VideoViewer():QLabel()
{

}
VideoViewer::VideoViewer(QWidget *parent, Qt::WindowFlags f):QLabel(parent,f)
{

}

/*VideoViewer::VideoViewer(QWidget *parent, const char* str):QLabel(parent)
{

}*/

VideoViewer::VideoViewer(const QString & text, QWidget* parent, Qt::WindowFlags f):QLabel(text,parent,f)
{

}

//Отрисовывает кадр
void VideoViewer::FrameAvailable(const QVideoFrame & frame)
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

    QImage imageConverted = image.convertToFormat(QImage::Format_RGB30);


    //Отрисовываем
    this->setPixmap(QPixmap::fromImage(imageConverted));

    this->resize(imageConverted.size());

    cloneFrame.unmap();
    this->update();
}
