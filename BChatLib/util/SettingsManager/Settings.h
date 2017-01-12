#pragma once
#include <iostream>
using namespace std;

class Settings
{
public:
	Settings(string container, 
		string certificate, 
		string interlocutorCertificate,
		string ip, 
		int port);

	~Settings();

	string	GetContainer();
	string	GetCertificate();
	string	GetInterlocutorCertificate();
	string	GetIP();
	int		GetPort();

private:
	string			_container;					// Контейнер (Для КриптоПро)
	string			_certificate;				// Сертификат
	string			_interlocutorCertificate;	// Сертификат собеседника
	string			_ip;						// IP сервера
	int				_port;						// Порт сервера
};

