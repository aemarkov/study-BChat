#pragma once

#include <QObject>

namespace Crypto
{

	class ICrypt : public QObject
	{
		Q_OBJECT

	public:

		public slots :

		virtual void EncryptSlot(uint8_t*, uint32_t) = 0;
		virtual void DecryptSlot(uint8_t*, uint32_t) = 0;

	signals:
		void DecryptSignal(uint8_t*, uint32_t);
		void EncryptSignal(uint8_t*, uint32_t);
	};

}