#include "SessionUser.h"

SessionUser::SessionUser()
{
}

SessionUser::SessionUser(User user, TcpClient client)
{
	user = this->user;;
	this->client = client;
}
