#pragma once

#include "IUserManager.h"
#include "util\SettingsManager\SettingsManagerContainer.h"
class UserManager : public IUserManager
{
public:
	UserManager();
	~UserManager();	
	// Унаследовано через IUserManager
	virtual void Clear() override;
	virtual void Add(string key, User user) override;
	virtual void Remove(string key) override;
	virtual void Update(string key, string newKey, User user) override;
	virtual void LoadFromFile() override;
	virtual void SaveToFile() override;
	virtual map<string, User> GetAllUsers() override;	
	virtual User GetUser(string key) override;
private:
	 map<string, User>		_users;
	 string					_filename = "users.txt";
	 	 
	 void refreshUsers();
};

