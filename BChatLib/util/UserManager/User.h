#pragma once

#include <iostream>
using namespace std;

class User
{
public:
	User(uint32_t id,
		string name,
		string certName);
	User();
	~User();

	uint32_t	_id;
	string		_name;
	string		_certName;
};

