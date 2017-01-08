#pragma once

#include <QWidget>
#include <qdialog.h>
#include "ui_SettingsWindow.h"
#include "util\SettingsManager\SettingsManagerContainer.h"

class SettingsWindow : public QDialog
{
	Q_OBJECT

public:
	SettingsWindow(QWidget *parent = Q_NULLPTR);
	~SettingsWindow();

public slots:
	void btnSave_Clicked();

private:
	Ui::SettingsWindow ui;
};
