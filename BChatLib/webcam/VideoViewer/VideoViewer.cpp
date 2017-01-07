#include "VideoViewer.h"

VideoViewer::VideoViewer():QLabel()
{

}
VideoViewer::VideoViewer(QWidget *parent, Qt::WindowFlags f):QLabel(parent,f)
{

}


VideoViewer::VideoViewer(const QString & text, QWidget* parent, Qt::WindowFlags f):QLabel(text,parent,f)
{

}

//Отрисовывает кадр
void VideoViewer::FrameInput(QImage & image)
{
    //Отрисовываем
    this->setPixmap(QPixmap::fromImage(image));
    this->resize(image.size());
    this->update();
}
