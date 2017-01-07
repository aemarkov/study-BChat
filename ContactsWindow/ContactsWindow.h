#pragma once

#include <QWidget>
#include "ui_ContactsWindow.h"

class ContactsWindow : public QWidget
{
	Q_OBJECT

public:
	ContactsWindow(QWidget *parent = Q_NULLPTR);
	~ContactsWindow();

private:
	Ui::ContactsWindow ui;
};
