#include "SimpleSessionManager.h"

SimpleSessionManager::SimpleSessionManager():
	_cryptoAPIAdapter(_cryptoAPI),
	_session(_cryptoAPIAdapter)
{
}

void SimpleSessionManager::CreateChat()
{
	try
	{
		auto settings = SettingsManagerContainer::Inner()->ReadSettings();

		//Создаем CryptoAPI и генерируем сеансовый ключ
		_cryptoAPI.Init(settings.GetContainer());
		_cryptoAPI.CreateSessionKey();

		
		emit SessionCreated();
		//std::thread waitingThread(&SimpleSessionManager::WaitForConnection, this, settings.GetPort());
		//waitingThread.detach();

		WaitForConnection(settings.GetPort());

		//emit SessionCreated();
	}
	catch (Exception ex)
	{
		DialogHelper::ShowDialog(ex.Message.c_str());
	}
}

//Подключение к другому пользователю
void SimpleSessionManager::ConnectToUser(uint32_t userId)
{
	uint8_t* keyBuffer = nullptr;

	try
	{
		auto settings = SettingsManagerContainer::Inner()->ReadSettings();

		//Создаем CryptoAPI
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

		emit SessionCreated();

		//Передаем свой Id (Это должен быть нормальный Id)
		client.SimpleSend((char*)&_myId, sizeof(_myId));

		//Принимаем Id другого пользователя (в чате могут быть несколько пользователей)
		uint32_t userId;
		client.SimpleRecv((char*)&userId, sizeof(userId));

		//Обмен ключами		
		int keyBufferSize;

		client.Recv((char**)&keyBuffer, &keyBufferSize);
		if (keyBuffer == nullptr)
		{
			Logger::Instance()->WriteException("Can't get session key from server");
			delete[] keyBuffer;
			return;
		}

		_cryptoAPI.ImportSessionKey(keyBuffer, keyBufferSize, settings.GetCertificate(), settings.GetInterlocutorCertificate());

		delete[] keyBuffer;

		_session.UserConnected(userId, CreateTcpClientAdapter(client));

	}
	catch (Exception ex)
	{
		//Может остаться не удаленный keyBuffer
		DialogHelper::ShowDialog(ex.Message.c_str());
	}
}

Session & SimpleSessionManager::GetSession()
{
	return _session;
}







//Ожидание подключение пользователя
void SimpleSessionManager::WaitForConnection(int port)
{
	TcpListener listener(port);
	listener.Start();
	TcpClient client = listener.AcceptClient();

	//Соединение установлено
	AcceptConnection(client);
}


//Обмен ключами и прочей инфомацией с подключенным пользователем
void SimpleSessionManager::AcceptConnection(TcpClient & client)
{
	try
	{
		//Узнать Id подключенного пользователя
		uint32_t userId;
		client.SimpleRecv((char*)&userId, sizeof(userId));

		//Передаем свой Id
		client.SimpleSend((char*)&_myId, sizeof(_myId));

		//Получаем пользователя по этому Id (на самом деле нет, это стандартный пользователь)
		auto user = UserManagerContainer::Inner()->GetUser(userId);

		//Обмен ключами
		uint8_t* keyBuffer;
		uint32_t keyBufferSize;

		_cryptoAPI.ExportSessionKeyForUser(SettingsManagerContainer::Inner()->ReadSettings().GetCertificate(), user._certName, &keyBuffer, &keyBufferSize);

		client.Send((char*)keyBuffer, keyBufferSize);

		delete[] keyBuffer;

		_session.UserConnected(userId, CreateTcpClientAdapter(client));
	}
	catch (Exception ex)
	{
		//Может остаться не удаленный keyBuffer
		DialogHelper::ShowDialog(ex.Message);
	}
}




NetworkProcessingThread* SimpleSessionManager::CreateTcpClientAdapter(TcpClient & client)
{
	auto adapter = new NetworkProcessingThread(client);
	return adapter;
}

/*CryptoApiAdapter * SimpleSessionManager::CreateCryptoAPIAdapter(CryptoAPI & api)
{
	return new CryptoApiAdapter(api);
}*/
