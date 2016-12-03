#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QCamera>
#include <QCameraImageCapture>
#include <QMediaRecorder>
#include <QCameraInfo>
#include <QMediaMetaData>

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

    //Изменения состояния камеры
    void UpdateCameraState(const QCamera::State state);

    //Нажатие кнопки вкл\выкл камеры
    void ButtonCameraToggle_clicked();

private:
    Ui::MainWindow *ui;

    //Отображет список камер
    void UpdateCameras();

    //Выбирает камеру
    void SetCamera(const QCameraInfo & info);


    QCamera *camera;
    QCameraImageCapture *imageCapture;
    QMediaRecorder* mediaRecorder;

    bool _isCameraActive;

};

#endif // MAINWINDOW_H
