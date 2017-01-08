#pragma once
#include "ISettingsManager.h"
#include "Settings.h"

class SettingsManager : public ISettingsManager
{
public:
	SettingsManager();
	~SettingsManager();

	// Унаследовано через ISettingsManager
	virtual Settings ReadSettings() override;
	virtual void SaveSettings(Settings) override;
};

