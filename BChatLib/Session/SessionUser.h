#pragma once

#include "Models/User.h"
#include "NetworkAdapter\INetwork.h"
/*!
 * \brief Хранит одного пользователя в сессии - сам пользователь и TcpClient для связи
 */
class SessionUser
{
public:

	//SessionUser();
	SessionUser(User user, INetwork * client);

	User user;
	INetwork* client;
};
