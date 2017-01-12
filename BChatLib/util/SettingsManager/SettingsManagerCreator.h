#pragma once

#include "util\FactoryMethod\FactoryMethod.h"
#include "SettingsManager.h"

using namespace Util;


class SettingsManagerCreator : FactoryMethod<SettingsManager>
{
public:
	SettingsManagerCreator();
	~SettingsManagerCreator();

	// Унаследовано через FactoryMethod
	virtual SettingsManager * Create() override;
};

