#include "Session.h"

Session::Session() :
	_frameConverter(QImage::Format_RGB444)
{
}


Session::~Session()
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////


//Подключение к чату
void Session::JoinChat(uint32_t userId)
{
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
	//Я надеюсь, что поток уничтожется после уничтожения оюъекта
	while (true)
	{

		TcpListener listener(_port);
		listener.Start();
		TcpClient client = listener.AcceptClient();

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
		}
		catch(Exception ex)
		{
			//Вывести сообщение, но мы, блин, в другом потоке
		}
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////

void Session::UserConnected(uint32_t userId, INetwork * client)
{
	auto user = UserManagerContainer::Inner()->GetUser(userId);
	SessionUser sessionUser(user, client);
	_users.insert(std::pair<uint32_t, SessionUser>(userId, sessionUser));



	//Зашифровка - сеть
	//connect(&_crypter, SIGNAL(EncryptSignal(uint8_t*, uint32_t)), client, SLOT(SendSlot(uint8_t*, uint32_t)));
	connect(&_multiplexor, SIGNAL(OutputData(uint8_t*, uint32_t)), client, SLOT(SendSlot(uint8_t*, uint32_t)));

	//Сесть - расшифровка
	//connect(client, SIGNAL(RecvSignal(uint8_t*, uint32_t)), &_crypter, SLOT(DecryptSlot(uint8_t*, uint32_t)));
	connect(client, SIGNAL(RecvSignal(uint8_t*, uint32_t)), &_multiplexor, SLOT(InputData(uint8_t*, uint32_t)), Qt::DirectConnection);


	client->start();

	emit UserConnected((int)userId);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

//Настраивает конвейер обработки данных
void Session::SetupPipeline()
{
	//Вспомогательный, проброс слота в сигнао
	connect(this, SIGNAL(__MyFameInput(QVideoFrame)), &_frameConverter, SLOT(FrameInput(QVideoFrame)));

	//Выход конвертера на отображение своей камеры
	connect(&_frameConverter, SIGNAL(FrameOutput(QImage&)), this, SIGNAL(MyFrameOutput(QImage&)));

	//Конвертер - преобразованеи в контейнер
	connect(&_frameConverter, SIGNAL(FrameOutput(QImage&)), &_qimageToContainerConverter, SLOT(FrameInput(QImage&)));

	//Контейнер кадра - мультиплекстор
	connect(&_qimageToContainerConverter, SIGNAL(DataOutput(const Containers::VideoFrameContainer *)), &_multiplexor, SLOT(InputContainer(const Containers::VideoFrameContainer*)));

	//Данные из мультиплексора - шифрование
	//connect(&_multiplexor, SIGNAL(OutputData(uint8_t*, uint32_t)), &_crypter, SLOT(EncryptSlot(uint8_t*, uint32_t)));

	//Расшифрование - мультипелксор
	//connect(&_crypter, SIGNAL(DecryptSignal(uint8_t*, uint32_t)), &_multiplexor, SLOT(InputData(uint8_t*, uint32_t)));

	//Мультипексор - контейнер кадра
	connect(&_multiplexor, SIGNAL(OutputFrame(const Containers::VideoFrameContainer *)), &_containerToQImageConverter, SLOT(DataInput(const Containers::VideoFrameContainer *)));// , Qt::DirectConnection);

																																												 //Контейнер кадра - кадр, вывод
	connect(&_containerToQImageConverter, SIGNAL(FrameOutput(QImage&)), this, SLOT(__OtherFrameOutput(QImage&)));// , Qt::DirectConnection);
}


void Session::__OtherFrameOutput(QImage & frame)
{
	emit OtherFrameOutput(frame);
}


void Session::MyFrameInput(const QVideoFrame & frame)
{
	emit __MyFameInput(frame);
}
