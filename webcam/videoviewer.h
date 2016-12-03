#ifndef VIDEOVIEWER_H
#define VIDEOVIEWER_H

#include <QObject>
#include <QWidget>
#include <QVideoFrame>
#include <QLabel>

/*!
 * \brief Визуализация QVideoFrame
 *
 * Этот виджет служит для непосредственной визуализации QVideoFrame,
 * инкопсулирует всю работу по преобразованию QVideoFrame в
 * QImage и дальнейшую отрисовку.
 */
class VideoViewer : public QLabel
{
    Q_OBJECT
public:
    VideoViewer();
    VideoViewer(QWidget *parent=nullptr, Qt::WindowFlags f=0);
    //VideoViewer(QWidget *parent=nullptr, const char* s=nullptr);
    VideoViewer(const QString & text, QWidget* parent=nullptr, Qt::WindowFlags f=0);

public slots:
    void FrameAvailable(const QVideoFrame&);
};

#endif // VIDEOVIEWER_H
