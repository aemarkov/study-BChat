#ifndef VIDEOVIEWER_H
#define VIDEOVIEWER_H

#include <QObject>
#include <QWidget>
#include <QVideoFrame>
#include <QLabel>

/*!
 * \brief Визуализация QVideoFrame
 *
 * Этот виджет служит для визуализации QImage.
 * Можно было прямо в форме, ничего сложного нет,
 * но сделано ради использования слотов, так удобнее.
 */
class VideoViewer : public QLabel
{
    Q_OBJECT
public:
    VideoViewer();
    VideoViewer(QWidget *parent=nullptr, Qt::WindowFlags f=0);
    VideoViewer(const QString & text, QWidget* parent=nullptr, Qt::WindowFlags f=0);

public slots:

    /*!
     * \brief FrameInput Получает кадр для отображения
     */
    void FrameInput(QImage&);
};

#endif // VIDEOVIEWER_H
