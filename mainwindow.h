#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QCamera>
#include <QCameraImageCapture>
#include <QMediaRecorder>
#include <QCameraInfo>
#include <QMediaMetaData>

#include "webcam/CameraFrameGrabber/CameraFrameGrabber.h"
#include "webcam/FrameConverter/FrameConverter.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:

    /*!
     * \brief Событие изменения состояния камеры
     * \param state новое состояние
     */
    void UpdateCameraState(const QCamera::State state);

    /*!
     * \brief событие нажатия на кнопку вкл\выкл камеры
     */
    void ButtonCameraToggle_clicked();

    /*!
     * \brief Событие выбора камеры в пункте меню
     * \param action пункт меню
     */
    void CameraSelected(QAction *action);

    /*!
     * \brief Событие получения кадра с камеры
     * \param frame полученный кадр
     */
    void HandleFrame(const QImage &image);

private:
    Ui::MainWindow *ui;

    /*!
     * \brief Получает все доступные камеры и
     *        отображает их в соотв. пункте меню
     */
    void UpdateCameras();

    /*!
     * \brief Включает выбранную камеру
     * \param info объект QCameraInfo, представляющий выбранную камеру
     */
    void SetCamera(const QCameraInfo & info);


    QCamera *camera;

    //Используется для завхвата кадров с камеры
    CameraFrameGrabber _cameraFrameGrabber;
    FrameConverter _frameConverter;

    bool _isCameraActive;

};

#endif // MAINWINDOW_H
