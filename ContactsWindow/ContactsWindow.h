#pragma once

#include <QWidget>
#include "ui_ContactsWindow.h"

#include "Session/Session.h"
#include "util/SettingsManager/SettingsManagerContainer.h"
#include "SettingsWindow/SettingsWindow.h"
#include "ChatWindow/ChatWindow.h"
#include "util/DialogHelper/DialogHelper.h"

class ContactsWindow : public QWidget
{
	Q_OBJECT

public:
	ContactsWindow(QWidget *parent = Q_NULLPTR);
	~ContactsWindow();

public slots:
	void Settings_Click();
	void JoinChat_Click();
	void HostChat_Click();

private:
	Ui::ContactsWindow ui;

	void StartSession(Session* session);
};
