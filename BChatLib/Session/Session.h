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

//class SimpleSessionManager;

/*!
 * \brief ������ ������. ������������� ��� ������� �� ������ �������
          � ���������� �������������� � ������
 */

//class SimpleSessionManager;

class Session: public QObject
{
	Q_OBJECT

public:

	void AddUser(uint32_t userId, TcpClient client);

public slots:

	void MyFrameInput(const QVideoFrame& frame);

signals:

	void UserConnected(uint32_t);
	void UserDisconnected(uint32_t);

	//����� �� ������� ������������
	void UserFrameOutput(QImage&);

	//����� � ���� ������
	void MyFrameOutput(QImage&);

private:
	std::map<uint32_t, SessionUser> _users;

	CameraFrameGrabber _cameraFrameGrabber;
	Webcam::FrameConverter _frameConverter;
	Webcam::QImageToContainerConverter _qimageToContainerConverter;
	Webcam::ContainerToQImageConverter _containerToQImageConverter;

	Containers::SimpleContainerMultiplexor _multiplexor;
};