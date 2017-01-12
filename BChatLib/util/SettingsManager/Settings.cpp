#include "Settings.h"

Settings::Settings(string container,
	string certificate,
	string interlocutorCertificate,
	string ip,
	int port)
{
	_container = container;
	_certificate = certificate;
	_ip = ip;
	_port = port;
	_interlocutorCertificate = interlocutorCertificate;
}

Settings::~Settings()
{
}

string Settings::GetContainer()
{
	return _container;
}

string Settings::GetCertificate()
{
	return _certificate;
}

string Settings::GetInterlocutorCertificate()
{
	return _interlocutorCertificate;
}

string Settings::GetIP()
{
	return _ip;
}

int Settings::GetPort()
{
	return _port;
}
