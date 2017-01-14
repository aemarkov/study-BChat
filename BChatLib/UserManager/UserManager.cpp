#include "UserManager.h"



UserManager::UserManager()
{
}

UserManager::~UserManager()
{
}

void UserManager::Clear()
{
	_users.clear();
}

void UserManager::Add(string key, User user)
{
	_users.insert(pair<string, User>(key, user));
}

void UserManager::Remove(string key)
{
	_users.erase(key);
}

void UserManager::Update(string key, User user)
{
	_users[key] = user;
}

void UserManager::LoadFromFile()
{
}

void UserManager::SaveToFile()
{
}

