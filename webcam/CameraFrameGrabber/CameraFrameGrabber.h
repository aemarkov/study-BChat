#ifndef CAMERAFRAMEGRABBER_H
#define CAMERAFRAMEGRABBER_H

#include <QObject>
#include <QAbstractVideoSurface>
#include <QList>

/*!
 * \brief Замена QCameraViewfinder, но с возможностью захвата
 * получаемых кадров
 *
 * Позволяет захватывать все кадры, получаемые камерой.
 * Источник: http://omg-it.works/how-to-grab-video-frames-directly-from-qcamera/
 *
 * Просто получаем QVideoFrame и отсылаем по сигналу QVideoFrame
 *
 */
class CameraFrameGrabber : public QAbstractVideoSurface
{
    Q_OBJECT
public:
    explicit CameraFrameGrabber(QObject *parent = 0);

    QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const;

    bool present(const QVideoFrame &frame);

signals:

    /*!
     * \brief Выдает очреедной полученный от камеры кадр
     * \param frame кадр
     */
    void FrameOutput(const QVideoFrame &frame);

public slots:

};

#endif // CAMERAFRAMEGRABBER_H
