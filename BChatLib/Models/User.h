#pragma once

#include <iostream>
using namespace std;

class User
{
public:
	User(string ip,
		string name,
		string certName);
	User();
	~User();
	
	string		_ip;
	string		_name;
	string		_certName;
};

