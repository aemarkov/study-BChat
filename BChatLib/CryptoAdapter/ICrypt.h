#pragma once

#include <QObject>

namespace Crypto
{

	class ICrypt : public QObject
	{
		Q_OBJECT

	public:

		public slots :

		virtual void EncryptSlot(quint8*, quint32) = 0;
		virtual void DecryptSlot(quint8*, quint32) = 0;

	signals:
		void DecryptSignal(quint8*, quint32);
		void EncryptSignal(quint8*, quint32);
	};

}