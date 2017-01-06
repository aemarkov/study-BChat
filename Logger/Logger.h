#pragma once

#include <QObject>
#include <qdatetime.h>
class Logger : public QObject
{
	Q_OBJECT

public:
		
	void Write(QString);			// Внести запись в лог
	void WriteDebug(QString);		// Внести запись о дебаге в лог
	bool SetWriteDebugFlag(bool);	// Установить флаг записи дебага в лог

	static Logger* Instance()
	{
		if (!_instance)
		{
			// Логгер
			_instance = new Logger();

			// Флаг записи дебага
			_writeDebugFlag = false;

			// Создание имени файла логов
			QString currentTime = QDateTime::currentDateTime()
				.toString("dd.MM.yyyy hh:mm:ss")
				.replace(":", "_");

			_filename = currentTime.append(" Logs.log");
		}
		return _instance;
	}

private:
	Logger(QObject *parent);
	Logger();
	Logger(const Logger&);
	Logger& operator=(Logger&);
	~Logger();
	
	static Logger*		_instance;			// Логгер
	static bool			_writeDebugFlag;	// Флаг записи дебага в лог
	static QString		_filename;			// Имя файла логов
};
