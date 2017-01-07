#include "QImageToBytesConverter.h"

void QImageToBytesConverter::FrameInput(QImage& image)
{
	uint32_t size = image.byteCount();
	uint8_t* data = (uint8_t*)image.bits();
	
	//Есть перегрузка bits(), которая сама копирует, но хз
	//А ведь нам необязательно НЕ МЕНЯТЬ этот массив, ведь
	//QFrame в QImage переводится и так копируованием
	//Но надо быть осторожным

	//ДЛЯ ТЕХ КТО НЕ ПОНЯЛ: МЫ ПЕРЕДАЕМ УКАЗАТЕЛЬ НА ВНУТРЕННИЙ МАССИВ БАЙТ ИЗ QIMAGE,
	//А ПОТОМ ВО ВСЯКИХ МЕСТАХ, ВТЧ В КРИПТОТЕ БУДЕМ ПРЯМО ЭТОТ МАССИВ МЕНЯТЬ

	int width = image.width();
	int height = image.height();

	emit DataOutput(data, size);

}