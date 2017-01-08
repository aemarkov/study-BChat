#pragma once

#include <QWidget>
#include <qdialog>
#include "ui_ChatWindow.h"

#include "Session/Session.h"

class ChatWindow : public QDialog
{
	Q_OBJECT

public:
	//ChatWindow(QWidget *parent = Q_NULLPTR);
	ChatWindow(Session& session);
	~ChatWindow();

public slots:
	void UserConnected(int);
	void UserDisconnected(int);

private:
	Ui::ChatWindow ui;
	Session& _session;
};
