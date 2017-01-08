#include "UserManager.h"



UserManager::UserManager()
{
}


UserManager::UserManager()
{
}

UserManager::~UserManager()
{
}

vector<User> UserManager::GetUsers()
{
	return _users;
}

User UserManager::GetUser(uint32_t id)
{
	return _users[id];
}
