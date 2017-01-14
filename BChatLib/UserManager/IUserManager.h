#pragma once
#include "Models/User.h"
#include <map>

class IUserManager
{
public:
	virtual void Clear() = 0;
	virtual void Add(string key, User user) = 0;
	virtual void Remove(string key) = 0;
	virtual void Update(string key, User user) = 0;
	virtual void LoadFromFile() = 0;
	virtual void SaveToFile() = 0;
};

