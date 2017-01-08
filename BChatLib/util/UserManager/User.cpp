#include "User.h"

User::User(uint32_t id, string name, string certName)
{
	_id = id;
	_name = name;
	_certName = certName;
}

User::~User()
{
}
