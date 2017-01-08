#include "SimpleSessionManager.h"

SimpleSessionManager::SimpleSessionManager()
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

		std::thread waitingThread(&SimpleSessionManager::WaitForConnection, this, settings.GetPort());
		waitingThread.detach();

		emit WaitingForConnection();
	}
	catch (Exception ex)
	{
		DialogHelper::ShowDialog(ex.Message.c_str());
	}
}

void SimpleSessionManager::ConnectToUser(uint32_t userId)
{
}

void SimpleSessionManager::WaitForConnection(int port)
{
	TcpListener listener(port);
	listener.Start();
	TcpClient client = listener.AcceptClient();

	//Соединение установлено
	AcceptConnection(client);

	emit UserConnected();
}

//Обмен ключами и прочей инфомацией с подключенным пользователем
void SimpleSessionManager::AcceptConnection(TcpClient  client)
{
	//Узнать Id подключенного пользователя
	uint32_t userId;
	client.SimpleRecv((char*)&userId, sizeof(userId));
	
	//Получаем пользователя по этому Id
	//auto user = UserMa
}
