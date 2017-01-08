#pragma once
#include <iostream>
using namespace std;

#include "util\SettingsManager\Settings.h"

#include "util\Singleton\SingletonContainer.h"
using namespace Util;

class ISettingsManager
{
public:
	virtual Settings ReadSettings() = 0;
	virtual void SaveSettings(Settings) = 0;
	
protected:
	string const	_filename = "settings.txt";		// Название файла настроек	
};

