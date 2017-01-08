#include "SettingsWindow.h"

SettingsWindow::SettingsWindow(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.btnSave, SIGNAL(clicked()), this, SLOT(btnSave_Clicked()));

	auto settings = SettingsManagerContainer::Inner()->ReadSettings();
	
	ui.txtContainer->setText(settings.GetContainer().c_str());
	ui.txtMyCert->setText(settings.GetCertificate().c_str());
	ui.txtInterlocutorCert->setText(settings.GetInterlocutorCertificate().c_str());
	ui.txtIp->setText(settings.GetIP().c_str());
	ui.sbPort->setValue(settings.GetPort());
}

SettingsWindow::~SettingsWindow()
{
}

void SettingsWindow::btnSave_Clicked()
{
	Settings settings(
		ui.txtContainer->text().toStdString(),
		ui.txtMyCert->text().toStdString(),
		ui.txtInterlocutorCert->text().toStdString(),
		ui.txtIp->text().toStdString(),
		ui.sbPort->value()
	);

	SettingsManagerContainer::Inner()->SaveSettings(settings);

	close();
}
