#pragma once

#include "Models/User.h"
#include "Network/TcpClient.h"

/*!
 * \brief Хранит одного пользователя в сессии - сам пользователь и TcpClient для связи
 */
class SessionUser
{
public:

	SessionUser();
	SessionUser(User user, TcpClient client);

	User user;
	TcpClient client;
};
