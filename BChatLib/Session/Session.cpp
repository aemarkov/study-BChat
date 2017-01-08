#include "Session.h"


void Session::UserConnected(uint32_t userId, TcpClient client)
{
	auto user = UserManagerContainer::Inner()->GetUser(userId);
	SessionUser sessionUser(user, client);
	_users.insert(std::pair<uint32_t, SessionUser>(userId, sessionUser));

	emit UserConnected((int)userId);
}


void Session::MyFrameInput(const QVideoFrame & frame)
{

}