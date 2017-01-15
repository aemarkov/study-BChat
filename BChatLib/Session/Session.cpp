#include "Session.h"

const uint32_t Session::BUFFERS_SIZE = 1000000;
//const uint32_t Session::VIDEO_FRAME_CONTAINER_BUFFER_SIZE = 1000000; //
//const uint32_t Session::CHAT_MESSAGE_CONTAINER_BUFFER_SIZE = 1000000;

Session::Session() :
	_frameConverter(QImage::Format_RGB444),
	_multiplexor(BUFFERS_SIZE)
{
}


Session::~Session()
{
	//Удаляем все подключенные INetwork
	for(int i = 0; i<_users.size(); i++)
	{
		_users[i].client->Stop();
		delete _users[i].client;
		_users[i].client = nullptr;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////


//Подключение к чату
void Session::JoinChat(uint32_t userId)
{
	uint8_t* keyBuffer = nullptr;

	try
	{
		auto settings = SettingsManagerContainer::Inner()->ReadSettings();
		_port = settings.GetPort();

		//Создаем объект cryptoApi
		_cryptoAPI.Init(settings.GetContainer());

		//Настройки куда подключаться должны определять у каждого конкретного пользователя,
		//получиться от сервера итп, но здесь 1 пользолватель

		TcpClient client;
		int result = client.Connect((char*)settings.GetIP().c_str(), settings.GetPort());

		if (result != 0)
		{
			Logger::Instance()->WriteException("Can't join chat");
			DialogHelper::ShowDialog("Can't join chat");
			return;
		}

		//Передаем свой Id (Это должен быть нормальный Id)
		client.Send((uint8_t*)&_myId, sizeof(_myId));

		//Принимаем Id другого пользователя (в чате могут быть несколько пользователей)
		uint32_t userId;
		client.SimpleRecv((uint8_t*)&userId, sizeof(userId));

		//Обмен ключами		
		uint32_t keyBufferSize;

		client.RecvAlloc((uint8_t**)&keyBuffer, &keyBufferSize);
		if (keyBuffer == nullptr)
		{
			Logger::Instance()->WriteException("Can't get session key from server");
			return;
		}

		_cryptoAPI.ImportSessionKey(keyBuffer, keyBufferSize, settings.GetCertificate(), settings.GetInterlocutorCertificate());

		delete[] keyBuffer;

		//Добавляем пользователя в список пользователей
		SetupPipeline();
		AddUser(userId, client);
	}
	catch (Exception ex)
	{
		//Может остаться не удаленный keyBuffer
		DialogHelper::ShowDialog(ex.Message);
		if (keyBuffer != nullptr)
			delete[] keyBuffer;
	}
}

//Отправить сообщение в чат
void Session::SendChatMessage(QString message)
{
	_messageConverter.MessageInput(message);
}

//Создание чата
void Session::CreateChat()
{
	auto settings = SettingsManagerContainer::Inner()->ReadSettings();
	_port = settings.GetPort();

	//Создаем объект cryptoApi и генерируем сеансовый ключ
	_cryptoAPI.Init(settings.GetContainer());
	_cryptoAPI.CreateSessionKey();
	
	SetupPipeline();
	this->start();
}


//Ожидание подключений в отдельном потоке
void Session::run()
{
	TcpListener listener(_port);
	listener.Start();
	Logger::Instance()->Write("Listening started");

	//Я надеюсь, что поток уничтожется после уничтожения оюъекта
	while (true)
	{
		TcpClient client = listener.AcceptClient();

		Logger::Instance()->Write("Client connecting...");

		//Подключен клиент
		try
		{
			//Узнать Id подключенного пользователя
			uint32_t userId;
			client.SimpleRecv((uint8_t*)&userId, sizeof(userId));

			//Передаем свой Id
			client.Send((uint8_t*)&_myId, sizeof(_myId));

			//Получаем пользователя по этому Id (на самом деле нет, это стандартный пользователь)
			auto user = UserManagerContainer::Inner()->GetUser(userId);

			//Обмен ключами
			uint8_t* keyBuffer;
			uint32_t keyBufferSize;

			_cryptoAPI.ExportSessionKeyForUser(SettingsManagerContainer::Inner()->ReadSettings().GetCertificate(), user._certName, &keyBuffer, &keyBufferSize);

			client.SendWithLength((uint8_t*)keyBuffer, keyBufferSize);

			delete[] keyBuffer;

			//Добавляем пользователя в список пользователей
			AddUser(userId, client);
		}
		catch(Exception ex)
		{
			//Вывести сообщение, но мы, блин, в другом потоке
		}
	}
}


//////////////////////////////////////// СЛОТЫ ////////////////////////////////////////////////////


void Session::MyFrameInput(const QVideoFrame & frame)
{
	emit __MyFameInput(frame);
}

void Session::MyMessageInput(const QString string)
{
	emit __MyMessageInput(string);
}

//Проблемы с соединеннием одного из клиентов
void Session::ConnectionProblem(int errorCode, int clientIndex)
{
	Logger::Instance()->Write(QString("Client #%1 disconnected with error code %2").arg(clientIndex).arg(errorCode));

	INetwork* network = _users[clientIndex].client;
	_users.erase(_users.begin() + clientIndex);

	//Удаляем объект соединения, он закроет все сокеты итп
	if (network != nullptr)
		delete network;

	emit UserDisconnected(clientIndex);
}



///////////////////////////////////////////////////////////////////////////////////////////////////

void Session::AddUser(uint32_t userId, TcpClient tcpClient)
{
	INetwork* client = new NetworkProcessingThread(tcpClient, BUFFERS_SIZE, _userCnt++);

	auto user = UserManagerContainer::Inner()->GetUser(userId);
	SessionUser sessionUser(user, client);
	_users.push_back(sessionUser);


	//Зашифровка - сеть
	//connect(&_crypter, SIGNAL(EncryptSignal(uint8_t*, quint32)), client, SLOT(SendSlot(uint8_t*, quint32)));
	connect(&_multiplexor, SIGNAL(OutputData(quint8*, quint32)), client, SLOT(SendSlot(quint8*, quint32)), Qt::DirectConnection);

	//Сесть - расшифровка
	//connect(client, SIGNAL(RecvSignal(quint8*, quint32)), &_crypter, SLOT(DecryptSlot(quint8*, quint32)), Qt::DirectConnection);
	connect(client, SIGNAL(RecvSignal(quint8*, quint32)), &_multiplexor, SLOT(InputData(quint8*, quint32)));// , Qt::DirectConnection);



	//Отключение
	connect(client, SIGNAL(ConnectionProblem(int, int)), this, SLOT(ConnectionProblem(int, int)));

	client->start();

	emit UserConnected((int)userId);

	Logger::Instance()->Write("Client connected");
}


//Настраивает конвейер обработки данных
void Session::SetupPipeline()
{
	//Вспомогательный, проброс слота в сигнал
	connect(this, SIGNAL(__MyFameInput(QVideoFrame)), &_frameConverter, SLOT(FrameInput(QVideoFrame)));
	connect(this, SIGNAL(__MyMessageInput(QString)), &_messageConverter, SLOT(MessageInput(QString)));


	//Выход конвертера на отображение своей камеры
	connect(&_frameConverter, SIGNAL(FrameOutput(QImage&)), this, SIGNAL(MyFrameOutput(QImage&)));

	//Конвертер - преобразованеи в контейнер
	connect(&_frameConverter, SIGNAL(FrameOutput(QImage&)), &_qimageToContainerConverter, SLOT(FrameInput(QImage&)));

	//Контейнер кадра - мультиплекстор
	connect(&_qimageToContainerConverter, SIGNAL(DataOutput(const Containers::VideoFrameContainer *)), &_multiplexor, SLOT(InputVideoContainer(const Containers::VideoFrameContainer*)));

	//Контейнер сообщения - мультиплексор
	connect(&_messageConverter, SIGNAL(DataOutput(const Containers::ChatMessageContainer*)), &_multiplexor, SLOT(InputChatContainer(const Containers::ChatMessageContainer*)));

	//Данные из мультиплексора - шифрование
	//connect(&_multiplexor, SIGNAL(OutputData(uint8_t*, uint32_t)), &_crypter, SLOT(EncryptSlot(uint8_t*, uint32_t)));




	//Расшифрование - мультипелксор
	//connect(&_crypter, SIGNAL(DecryptSignal(uint8_t*, uint32_t)), &_multiplexor, SLOT(InputData(uint8_t*, uint32_t)));

	//Мультипексор - контейнер кадра
	connect(&_multiplexor, SIGNAL(OutputFrame(const Containers::VideoFrameContainer *)), &_containerToQImageConverter, SLOT(DataInput(const Containers::VideoFrameContainer *)));// , Qt::DirectConnection);

	//Контейнер кадра - кадр, вывод
	connect(&_containerToQImageConverter, SIGNAL(FrameOutput(QImage&)), this, SIGNAL(OtherFrameOutput(QImage&)));// , Qt::DirectConnection);

	//Мультиплексор - сообщение
	connect(&_multiplexor, SIGNAL(OutputMessage(const Containers::ChatMessageContainer*)), this, SIGNAL(MessageOutput(const Containers::ChatMessageContainer*)));
}
