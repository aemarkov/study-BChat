#include "Logger.h"
#include <qfile.h>
#include <qtextstream.h>

using namespace Util;

Logger * Logger::_instance = 0;
bool Logger::_writeDebugFlag = 0;
QString Logger::_filename = 0;

Logger::~Logger()
{
}

Logger::Logger()
{

}

void Logger::WriteDebug(QString message)
{
	if (_writeDebugFlag)
	{
		this->Write(QString("DEBUG: ").append(message));
	}
}

bool Logger::SetWriteDebugFlag(bool flag)
{
	_writeDebugFlag = flag;
	return _writeDebugFlag;
}

void Util::Logger::WriteException(QString message)
{
	this->Write(QString("EXCEPTION: ").append(message));
}

void Logger::Write(QString message)
{	
	QFile file(_filename);
	
	if (file.open(QIODevice::WriteOnly | QIODevice::Append))
	{
		QTextStream stream(&file);
		
		stream << QDateTime::currentDateTime()
			.toString("dd.MM.yyyy hh:mm:ss");

		stream << " " << message << "\r\n";
		
		file.close();
	}	
}