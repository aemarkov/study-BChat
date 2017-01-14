#pragma once	

#include <qobject.h>
#include <qimage>
#include <qvideoframe.h>
#include <map>

#include "SessionUser.h"


#include "webcam/CameraFrameGrabber/CameraFrameGrabber.h"
#include "webcam/FrameConverter/FrameConverter.h"
#include "webcam/QImageConverter/QImageToContainerConverter.h"
#include "webcam/QImageConverter/ContainerToQImageConverter.h"

#include "Containers/SimpleContainerMultiplexor.h"
#include "UserManager/UserManagerContainer.h"

#include "NetworkAdapter/INetwork.h"
#include "Network/TcpListener.h"

#include "CryptoAdapter/ICrypt.h"
#include "crypto/cryptoapi.h"

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

	void UserConnected(uint32_t userId, INetwork * client);

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

	//Ожидание подключений в отдельном потоке
	void run();

public slots:

	void MyFrameInput(const QVideoFrame&);
	void __OtherFrameOutput(QImage&);

signals:

	//Чтобы пробросить слот на сигнал для внутреннего использования
	void __MyFameInput(const QVideoFrame&);

	void UserConnected(int);
	void UserDisconnected(int);

	//Видео от другого пользователя
	void OtherFrameOutput(QImage&);

	//Видео с моей камеры
	void MyFrameOutput(QImage&);



private:
	//Подключенные пользователи
	std::map<uint32_t, SessionUser> _users;
	int _myId = 0;

	//Части конвейера
	Webcam::FrameConverter _frameConverter;
	Webcam::QImageToContainerConverter _qimageToContainerConverter;
	Webcam::ContainerToQImageConverter _containerToQImageConverter;
	Containers::SimpleContainerMultiplexor _multiplexor;

	//Крипто-апи
	CryptoAPI _cryptoAPI;
	ICrypt* _crypter;

	//Сеть
	int _port;

	void SetupPipeline();

};