#include "mainwindow.h"
#include "ui_mainwindow.h"

Q_DECLARE_METATYPE(QCameraInfo)

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qRegisterMetaType<QCameraInfo>();
    ui->setupUi(this);

    //Слоты
    connect(ui->ButtonCameraToggle, SIGNAL(clicked(bool)),this, SLOT(ButtonCameraToggle_clicked()));

    //Настройка камеры
    UpdateCameras();
    SetCamera(QCameraInfo::defaultCamera());
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Отображаает список камер
void MainWindow::UpdateCameras()
{
    auto group = new QActionGroup(this);
    group->setExclusive(true);

    //Добавляет список камер в меню
    foreach(const QCameraInfo &info, QCameraInfo::availableCameras())
    {
        auto action = new QAction(info.description());
        action->setCheckable(true);
        action->setData(QVariant::fromValue(info));

        if(info==QCameraInfo::defaultCamera())
            action->setChecked(true);

        ui->MenuSelectCamera->addAction(action);
        group->addAction(action);
    }
}

//Включает\выключает камеру
//Выбирает камеру
void MainWindow::SetCamera(const QCameraInfo & info)
{
    delete imageCapture;
    delete mediaRecorder;
    delete camera;

    camera = new QCamera(info);
    mediaRecorder = new QMediaRecorder(camera);
    imageCapture = new QCameraImageCapture(camera);
    mediaRecorder->setMetaData(QMediaMetaData::Title, QVariant(QLatin1String("Test Title")));

    camera->setViewfinder(ui->viewFinder);

    //Сигналы камеры
    connect(camera, SIGNAL(stateChanged(QCamera::State)), this, SLOT(UpdateCameraState(QCamera::State)));

    camera->start();
}

//Управляет элементами интерфейса, связанными с камерой,
//в зависимости от статуса камеры
void MainWindow::UpdateCameraState(const QCamera::State state)
{
    if(state==QCamera::State::ActiveState)
    {
        //Камера включена
        ui->ButtonCameraToggle->setText("Выключить");
        _isCameraActive=true;
    }
    else if(state==QCamera::State::LoadedState || state==QCamera::State::UnloadedState)
    {
        ui->ButtonCameraToggle->setText("Включить");
        _isCameraActive=false;
    }
}


//Нажата кнопка включения\выключения камеры
void MainWindow::ButtonCameraToggle_clicked()
{
    if(_isCameraActive)
    {
        camera->stop();
    }
    else
    {
        camera->start();
    }
}
