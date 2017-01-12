#include "UserManager.h"



UserManager::UserManager()
{
	User user;
	user._certName = SettingsManagerContainer::Inner()->ReadSettings().GetCertificate();
	user._name = "User1";
	user._id = 1;

	_users.push_back(user);
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
	return _users[0];
}
