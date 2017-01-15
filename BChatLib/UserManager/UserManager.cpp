#include "UserManager.h"
#include <fstream>
#include "common\Exceptions.h"

UserManager::UserManager()
{
}

UserManager::~UserManager()
{
}

void UserManager::refreshUsers()
{
	SaveToFile();
	LoadFromFile();
}

void UserManager::Clear()
{
	_users.clear();
	refreshUsers();
}

void UserManager::Add(string key, User user)
{
	_users.insert(pair<string, User>(key, user));
	refreshUsers();
}

void UserManager::Remove(string key)
{
	_users.erase(key);
	refreshUsers();
}

void UserManager::Update(string key, string newKey, User user)
{
	Remove(key);
	refreshUsers();
	Add(newKey, user);
	refreshUsers();
}

void UserManager::LoadFromFile()
{
	fstream fs;
	fs.open(_filename, fstream::in | fstream::binary);

	if (fs.is_open())
	{
		_users.clear();

		// Считать количество пользователей
		int usersCount;
		fs.read((char*)&usersCount, sizeof(int));		

		// Считать пользователей
		for (int i = 0; i < usersCount; i++)
		{			
			int ipLen, nameLen, certLen;

			// ip
			fs.read((char*)&ipLen, sizeof(int));
			char* ip = new char[ipLen];
			fs.read(ip, ipLen);

			// Имя
			fs.read((char*)&nameLen, sizeof(int));
			char* name = new char[nameLen];
			fs.read(name, nameLen);

			// Название сертификата
			fs.read((char*)&certLen, sizeof(int));
			char* certName = new char[certLen];
			fs.read(certName, certLen);

			User user = User(ip, name, certName);
			_users.insert(pair<string, User>(name, user));
			
			delete[] ip;
			delete[] name;
			delete[] certName;
		}

	}

}

void UserManager::SaveToFile()
{
	fstream fs;
	fs.open(_filename, fstream::out | fstream::trunc | fstream::binary);

	if (fs.is_open())
	{
		// Сохранить количество пользователей
		int usersCount = _users.size();
		fs.write((char*)&usersCount, sizeof(int));

		// Сохранить пользователей
		for (auto user : _users)
		{
			// Сохранить ip			
			int ipLen = user.second._ip.length() + 1;
			fs.write((char*)&ipLen, sizeof(int));
			fs.write(user.second._ip.c_str(), ipLen);
			
			// Сохранить имя
			int nameLen = user.second._name.length() + 1;
			fs.write((char*)&nameLen, sizeof(int));
			fs.write(user.second._name.c_str(), nameLen);
			
			// Сохранить имя сертификата
			int certNameLen = user.second._certName.length() + 1;
			fs.write((char*)&certNameLen, sizeof(int));
			fs.write(user.second._certName.c_str(), certNameLen);
		}

		fs.close();
	}
	else
	{
		throw Exception("Can't open users file");
	}
}

map<string, User> UserManager::GetAllUsers()
{
	return _users;
}

User UserManager::GetUser(string key)
{
	return _users[key];
}
