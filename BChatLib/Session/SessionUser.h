#pragma once

#include "Models/User.h"
#include "Network/TcpClient.h"

class SessionUser
{
public:
	User User;
	TcpClient Client;
};
