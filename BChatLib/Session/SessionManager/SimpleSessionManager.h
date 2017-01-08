#pragma once

#include "Session/Session.h"
#include "ISessionManager.h"

#include "Network/TcpClient.h"
#include "Network/TcpListener.h"

#include "NetworkAdapter/INetwork.h"
#include "NetworkAdapter/NetworkAdapter.h"

#include "crypto/cryptoapi.h"
#include "CryptoAdapter/ICrypt.h"
#include "CryptoAdapter/CryptoApiAdapter.h"

#include "util/SettingsManager/SettingsManagerContainer.h"
#include "util/DialogHelper/DialogHelper.h"
#include "UserManager/UserManagerContainer.h"

#include <stdint.h>

#include <qobject>

#include <thread>

/*! 
 * \brief Примитивная реализация менеджера сессий

 Поддерживает только соеднинение один-к-одному, никаких серверов
 и прочего
 */
class SimpleSessionManager : public QObject, public ISessionManager
{
	Q_OBJECT

public:

	SimpleSessionManager();

	/*!
	 * \brief создание чата - запуск TcpListener, генерация сессионного ключа
	 ожидает подключения пользователя, после осуществляет обмен сессионными 
	 ключами, создает цепочку объектов для передачи видео и создает форму чата
	 */
	void CreateChat();

	/*
	 * \breif подключение - просто подключение по заданному IP, обмен ключами
	 подключение к серверу, после осуществляет обмен сессионными 
	 ключами, создает цепочку объектов для передачи видео и создает форму чата
	 */
	void ConnectToUser(uint32_t userId);

	Session& GetSession();

signals:
	void SessionCreated();

private:
	CryptoAPI _cryptoAPI;
	Session _session;
	uint32_t _myId = 0;
	

	void WaitForConnection(int port);
	void AcceptConnection(TcpClient client);

};