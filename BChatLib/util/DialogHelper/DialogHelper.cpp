#include "DialogHelper.h"

void DialogHelper::ShowDialog(std::string text)
{
	QMessageBox box;
	box.setText(text.c_str());
	box.exec();
}
