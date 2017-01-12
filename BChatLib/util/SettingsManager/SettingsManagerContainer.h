#pragma once

#include "util\SettingsManager\ISettingsManager.h"
#include "util\SettingsManager\SettingsManagerCreator.h"
#include "util\Singleton\SingletonContainer.h"
using namespace Util;

class SettingsManagerContainer : public SingletonContainer<ISettingsManager, SettingsManagerCreator>
{	
};

