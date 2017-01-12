#include "SettingsManager.h"
#include <fstream>
#include "common\Exceptions.h"

SettingsManager::SettingsManager()
{
}


SettingsManager::~SettingsManager()
{
}

Settings SettingsManager::ReadSettings()
{
	// Прочитать из файла
	fstream fs;
	fs.open(_filename, std::fstream::in | fstream::binary);
	
	if (fs.is_open())
	{
		// Считать длину сертификата
		int certLength;
		fs.read((char*)&certLength, sizeof(int));
		// Считать сертификат
		char* cert = new char[certLength];
		fs.read(cert, certLength);

		// Считать длину сертификата собеседника
		int interlocutorCertLength;
		fs.read((char*)&interlocutorCertLength, sizeof(int));
		// Считать сертификат собеседника
		char* interlocutorCert = new char[interlocutorCertLength];
		fs.read(interlocutorCert, interlocutorCertLength);


		// Считать длину контейнера
		int containerLength;
		fs.read((char*)&containerLength, sizeof(int));
		// Считать контейнер
		char* container = new char[containerLength];
		fs.read(container, containerLength);

		// Считать длину ip
		int ipLength;
		fs.read((char*)&ipLength, sizeof(int));
		char* ip = new char[ipLength];
		fs.read(ip, ipLength);

		// Считать порт
		int port;
		fs.read((char*)&port, sizeof(int));

		// Создать настройки
		Settings settings = Settings(container, cert, interlocutorCert, ip, port);

		// Освободить память
		delete[] cert;
		delete[] container;
		delete[] ip;
		delete[] interlocutorCert;

		return settings;
	}
	else
	{
		throw Exception("Can't open settings file");
	}
}

void SettingsManager::SaveSettings(Settings settings)
{
	// Сохранить в файл
	fstream fs;
	fs.open(_filename, fstream::out | fstream::trunc | fstream::binary);	
	if (fs.is_open())
	{		
		// Сохранить сертификат
		int tmpLength = settings.GetCertificate().length() + 1;
		fs.write((char*)&tmpLength, sizeof(int));
		fs.write(settings.GetCertificate().c_str(), settings.GetCertificate().length() + 1);

		// Сохранить сертификат собеседника
		tmpLength = settings.GetInterlocutorCertificate().length() + 1;
		fs.write((char*)&tmpLength, sizeof(int));
		fs.write(settings.GetInterlocutorCertificate().c_str(), settings.GetInterlocutorCertificate().length() + 1);

		// Сохранить контейнер
		tmpLength = settings.GetContainer().length() + 1;
		fs.write((char*)&tmpLength, sizeof(int));
		fs.write(settings.GetContainer().c_str(), settings.GetContainer().length() + 1);

		// Сохранить ip
		tmpLength = settings.GetIP().length() + 1;
		fs.write((char*)&tmpLength, sizeof(int));
		fs.write(settings.GetIP().c_str(), settings.GetIP().length() + 1);
				
		// Сохранить порт
		int port = settings.GetPort();
		fs.write((char*)&port, sizeof(int));
		
		fs.close();
	}
	else
	{
		throw Exception("Can't open settings file");
	}
}
