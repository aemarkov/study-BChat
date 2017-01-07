#pragma once

#include <QWidget>
#include "ui_ChatWindow.h"

class ChatWindow : public QWidget
{
	Q_OBJECT

public:
	ChatWindow(QWidget *parent = Q_NULLPTR);
	~ChatWindow();

private:
	Ui::ChatWindow ui;
};
