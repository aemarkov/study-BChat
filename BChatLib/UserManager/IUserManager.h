#pragma once
#include "Models/User.h"
#include <vector>

class IUserManager
{
public:
	virtual vector<User> GetUsers() = 0;
	virtual User GetUser(uint32_t id) = 0;
};

