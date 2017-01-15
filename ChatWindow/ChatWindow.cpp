#include "ChatWindow.h"

/*ChatWindow::ChatWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}*/

Q_DECLARE_METATYPE(QCameraInfo)
Q_DECLARE_METATYPE(Containers::VideoFrameContainer)
Q_DECLARE_METATYPE(Containers::ChatMessageContainer)

ChatWindow::ChatWindow(Session* session):
	_session(session),
	camera(0)
{
	qRegisterMetaType<QCameraInfo>();
	qRegisterMetaType<Containers::VideoFrameContainer>();
	qRegisterMetaType<Containers::ChatMessageContainer>();

	ui.setupUi(this);


	connect(ui.menuToggleCamera, SIGNAL(triggered()), this, SLOT(ButtonCameraToggle_clicked()));
	connect(ui.btnSendMessage, SIGNAL(clicked()), this, SLOT(BtnSendMessage_clicked()));

	connect(_session, SIGNAL(UserConnected(int)), this, SLOT(UserConnected(int)));
	connect(_session, SIGNAL(UserDisconnected(int)), this, SLOT(UserDisconnected(int)));

	connect(&_cameraFrameGrabber, SIGNAL(FrameOutput(QVideoFrame)), _session, SLOT(MyFrameInput(QVideoFrame)));
	connect(_session, SIGNAL(MyFrameOutput(QImage&)), ui.camYou, SLOT(FrameInput(QImage&)));
	connect(_session, SIGNAL(OtherFrameOutput(QImage&)), ui.camInterlocutor, SLOT(FrameInput(QImage&)));
	connect(_session, SIGNAL(MessageOutput(const Containers::ChatMessageContainer*)), this, SLOT(MessageInput(const Containers::ChatMessageContainer *)));

	UpdateCameras();
	SetCamera(QCameraInfo::defaultCamera());
}

ChatWindow::~ChatWindow()
{
	delete camera;

	if (_session != nullptr)
		delete _session;
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

//Событие нажатия на кнопку отправки сообщения
void ChatWindow::BtnSendMessage_clicked()
{
	QString message = ui.txtMessage->toPlainText();
	ui.txtChat->append("me:");
	ui.txtChat->append(message);
	ui.txtMessage->setText("");
	_session->SendChatMessage(message);
}


//Полученено сообщение 
void ChatWindow::MessageInput(const Containers::ChatMessageContainer * container)
{
	QString message = container->Get_Message();
	ui.txtChat->append("Bomj:");
	ui.txtChat->append(message);
}

void ChatWindow::UserConnected(int)
{

}

void ChatWindow::UserDisconnected(int)
{

}
