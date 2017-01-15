#pragma once	

#include <qobject.h>
#include <qimage>
#include <qvideoframe.h>
#include <vector>
#include <string>
#include "SessionUser.h"


#include "webcam/CameraFrameGrabber/CameraFrameGrabber.h"
#include "webcam/FrameConverter/FrameConverter.h"
#include "webcam/QImageConverter/QImageToContainerConverter.h"
#include "webcam/QImageConverter/ContainerToQImageConverter.h"

#include "Containers/SimpleContainerMultiplexor.h"
#include "UserManager/UserManagerContainer.h"

#include "NetworkAdapter/INetwork.h"
#include "Network/TcpListener.h"
#include "NetworkAdapter/NetworkProcessingThread.h"

#include "CryptoAdapter/CryptoApiAdapter.h"
#include "CryptoAdapter/ICrypt.h"
#include "crypto/cryptoapi.h"

#include "util/DialogHelper/DialogHelper.h"

#include "chat/QStringToContainerConverter.h"

//class SimpleSessionManager;

/*!
 * \brief Объект сессии. Инкапсулирует все оерации по обмену данными
          и управлению пользователями в сесиии
 */

//class SimpleSessionManager;

using namespace Crypto;

class Session: public QThread
{
	Q_OBJECT

public:

	Session();
	~Session();

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
	void JoinChat(uint32_t userId);

	//Отправить сообщение в чат
	void SendChatMessage(QString message);

	//Ожидание подключений в отдельном потоке
	void run();

public slots:

	//Получен кадр с вебкамеры
	void MyFrameInput(const QVideoFrame&);
	void MyMessageInput(const QString);

	//Проблемы с подключением у одного из клиентов
	void ConnectionProblem(int, int);

signals:

	//Чтобы пробросить слот на сигнал для внутреннего использования
	void __MyFameInput(const QVideoFrame&);
	void __MyMessageInput(const QString);

	void UserConnected(int);
	void UserDisconnected(int);


	//Видео с моей камеры
	void MyFrameOutput(QImage&);

	//Видео от другого пользователя
	void OtherFrameOutput(QImage&);
	
	//Сообщение
	void MessageOutput(const Containers::ChatMessageContainer*);


private:
	//Подключенные пользователи
	std::vector<SessionUser> _users;
	int _userCnt = 0;
	int _myId = 0;

	//Части конвейера
	Webcam::FrameConverter _frameConverter;
	Webcam::QImageToContainerConverter _qimageToContainerConverter;
	Webcam::ContainerToQImageConverter _containerToQImageConverter;
	QStringToContainerConverter _messageConverter;

	Containers::SimpleContainerMultiplexor _multiplexor;

	//Крипто-апи
	CryptoAPI _cryptoAPI;
	ICrypt* _crypter;

	//Сеть
	int _port;
	static const uint32_t BUFFERS_SIZE;
	//static const uint32_t VIDEO_FRAME_CONTAINER_BUFFER_SIZE;
	//static const uint32_t CHAT_MESSAGE_CONTAINER_BUFFER_SIZE;

	//Добавляет пользователя
	void AddUser(uint32_t userId, TcpClient  client);




	//Настраивает конвейер
	void SetupPipeline();
};