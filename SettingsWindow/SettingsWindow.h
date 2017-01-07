#pragma once

#include <QWidget>
#include "ui_SettingsWindow.h"

class SettingsWindow : public QWidget
{
	Q_OBJECT

public:
	SettingsWindow(QWidget *parent = Q_NULLPTR);
	~SettingsWindow();

private:
	Ui::SettingsWindow ui;
};
