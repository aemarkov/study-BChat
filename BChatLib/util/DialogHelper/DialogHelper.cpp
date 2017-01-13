#include "DialogHelper.h"


void DialogHelper::ShowDialog(QString text)
{
	QMessageBox box;
	box.setText(text.toStdString().c_str());
	box.exec();
}
