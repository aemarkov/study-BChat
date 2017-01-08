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
#include "webcam/QImageConverter/QImageToContainerConverter.h"
#include "webcam/QImageConverter/ContainerToQImageConverter.h"

#include "crypto/cryptoapi.h"
#include "CryptoAdapter/CryptoApiAdapter.h"
#include "CryptoAdapter/ICrypt.h"

#include "Containers\SimpleContainerMultiplexor.h"

using namespace Webcam;
//using namespace Containers;

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

	QImageToContainerConverter _qimageToContainerConverter;
	ContainerToQImageConverter _containerToQImageConverter;
	Containers::SimpleContainerMultiplexor _multiplexor;

	Crypto::CryptoAPI _cryptoApi;
	CryptoApiAdapter _cryptoAdapter;

    bool _isCameraActive;

};

#endif // MAINWINDOW_H
