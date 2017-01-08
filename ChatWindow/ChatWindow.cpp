#include "ChatWindow.h"

/*ChatWindow::ChatWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}*/

Q_DECLARE_METATYPE(QCameraInfo)

ChatWindow::ChatWindow(Session& session):
	_session(session),
	camera(0)
{
	qRegisterMetaType<QCameraInfo>();
	ui.setupUi(this);

	connect(ui.menuToggleCamera, SIGNAL(triggered()), this, SLOT(ButtonCameraToggle_clicked()));
	connect(&_session, SIGNAL(UserConnected(int)), this, SLOT(UserConnected(int)));
	connect(&_session, SIGNAL(UserDisconnected(int)), this, SLOT(UserDisconnected(int)));

	connect(&_cameraFrameGrabber, SIGNAL(FrameOutput(QVideoFrame)), &_session, SLOT(MyFrameInput(QVideoFrame)));
	connect(&_session, SIGNAL(MyFrameOutput(QImage&)), ui.camYou, SLOT(FrameInput(QImage&)));
	connect(&_session, SIGNAL(OtherFrameOutput(QImage&)), ui.camInterlocutor, SLOT(FrameInput(QImage&)));

	UpdateCameras();
	SetCamera(QCameraInfo::defaultCamera());
}

ChatWindow::~ChatWindow()
{
}



//Отображаает список камер
void ChatWindow::UpdateCameras()
{
	auto group = new QActionGroup(this);
	group->setExclusive(true);

	//Добавляет список камер в меню
	foreach(const QCameraInfo &info, QCameraInfo::availableCameras())
	{
		auto action = new QAction(info.description());
		action->setCheckable(true);
		action->setData(QVariant::fromValue(info));

		if (info == QCameraInfo::defaultCamera())
			action->setChecked(true);

		ui.MenuCamera->addAction(action);
		group->addAction(action);
	}

	//Подключаем обработчик выбора камеры
	connect(group, SIGNAL(triggered(QAction*)), this, SLOT(CameraSelected(QAction*)));
}


//Включает\выключает камеру
//Выбирает камеру
void ChatWindow::SetCamera(const QCameraInfo & info)
{
	delete camera;

	camera = new QCamera(info);
	camera->setViewfinder(&_cameraFrameGrabber);

	//Сигналы камеры
	connect(camera, SIGNAL(stateChanged(QCamera::State)), this, SLOT(UpdateCameraState(QCamera::State)));

	UpdateCameraState(camera->state());

	camera->start();
}

//Управляет элементами интерфейса, связанными с камерой,
//в зависимости от статуса камеры
void ChatWindow::UpdateCameraState(const QCamera::State state)
{
	if (state == QCamera::State::ActiveState)
	{
		//Камера включена
		ui.menuToggleCamera->setText("Turn off camera");
		_isCameraActive = true;
	}
	else if (state == QCamera::State::LoadedState || state == QCamera::State::UnloadedState)
	{
		ui.menuToggleCamera->setText("Turn on camera");
		_isCameraActive = false;
	}
}


void ChatWindow::ButtonCameraToggle_clicked()
{
	if (_isCameraActive)
	{
		camera->stop();
	}
	else
	{
		camera->start();
	}
}


//Событие выбора другой камеры
void ChatWindow::CameraSelected(QAction* action)
{
	SetCamera(qvariant_cast<QCameraInfo>(action->data()));
}


void ChatWindow::UserConnected(int)
{

}

void ChatWindow::UserDisconnected(int)
{

}
