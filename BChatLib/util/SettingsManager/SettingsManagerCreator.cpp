#include "SettingsManagerCreator.h"



SettingsManagerCreator::SettingsManagerCreator()
{
}


SettingsManagerCreator::~SettingsManagerCreator()
{
}

SettingsManager * SettingsManagerCreator::Create()
{
	return new SettingsManager();
}
